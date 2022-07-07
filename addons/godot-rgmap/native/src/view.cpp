#include "rgmap.h"
using namespace godot;

// All functions related to view and pathfinding

void RGMap::calculate_fov(Vector2 view_position) {
    // Define fov zone and resize visibility array
    fov_zone.size = Vector2(1,1)*(fov_radius*2+2);
    fov_zone.position = view_position - Vector2(1,1)*fov_radius - Vector2(1,1);
    visibility.resize(fov_zone.size.x*fov_zone.size.y);
    // Clear visibility values
    for (int i=0; i<visibility.size(); ++i){
        visibility[i] = 0;
    }
    // Get entities in fov zone
    PoolIntArray fov_entities = get_entities_in_rect(fov_zone);
    // Generate FOV obstacles
    fov_obstacles.resize(fov_zone.size.x*fov_zone.size.y);
    for (int i=0; i<fov_obstacles.size(); ++i){
        fov_obstacles[i] = 0;
    }
    for (int i = 0; i < fov_entities.size(); ++i) {
            Entity& entity = entities[fov_entities[i]];
            if (!entity.transparent) {
                Vector2 local_position = entity.position-fov_zone.position;
                int cell_index = local_position.x+local_position.y*fov_zone.size.x;
                fov_obstacles[cell_index] = 1;
            }
    }
    // Get visible cells
    PoolVector2Array visible_cells = rpas_calc_visible_cells_from(view_position, fov_radius);
    for (int i=0; i < visible_cells.size(); ++i) {
        set_visibility(visible_cells[i], true);
        set_discovered(visible_cells[i], true);
    }
    // Memorize entities
    for (int i = 0; i < fov_entities.size(); ++i) {
        Entity& entity = entities[fov_entities[i]];
        Vector2 local_position = entity.position-fov_zone.position;
        int cell_index = local_position.x+local_position.y*fov_zone.size.x;
        if (visibility[cell_index] == 1) {
            entity.discovered = true;
        }
    }
}
void RGMap::add_pathfinding_exception(Vector2 position, bool value) {
    remove_pathfinding_exception(position);
    if (value) {pathfinding_exception_allowed.push_back(position);}
    else {pathfinding_exception_disallowed.push_back(position);}
}
void RGMap::remove_pathfinding_exception(Vector2 position) {
    pathfinding_exception_allowed.erase(std::remove(pathfinding_exception_allowed.begin(), pathfinding_exception_allowed.end(), position), pathfinding_exception_allowed.end());
    pathfinding_exception_disallowed.erase(std::remove(pathfinding_exception_disallowed.begin(), pathfinding_exception_disallowed.end(), position), pathfinding_exception_disallowed.end());
}
PoolVector2Array RGMap::show_pathfinding_exceptions(bool exception_type) { 
    PoolVector2Array exceptions;
    std::vector<Vector2> source;
    if (exception_type) { source = pathfinding_exception_allowed; }
    else { source = pathfinding_exception_disallowed; }
    for (Vector2 point : source) {
        exceptions.append(point);
    }
    return exceptions;
}
PoolVector2Array RGMap::_find_path(Vector2 start, Vector2 end, Rect2 pathfinding_zone, bool exclude_undiscovered) {
    PoolVector2Array path;
    // Convert Rect2 values to integers
    pathfinding_zone.position = Vector2(floor(pathfinding_zone.position.x), floor(pathfinding_zone.position.y));
    pathfinding_zone.size = Vector2(floor(pathfinding_zone.size.x), floor(pathfinding_zone.size.y));
    // Return empty path if out of pathfinding zone
    if (!pathfinding_zone.has_point(start) || !pathfinding_zone.has_point(end)) {return path;}
    // Generate new Astar
    Ref<AStar2D> astar;
    astar.instance();
    for(int i=0; i < pathfinding_zone.size.x*pathfinding_zone.size.y; ++i) {
        int y = floor(i/pathfinding_zone.size.x);
        int x = i - y*pathfinding_zone.size.x;
        Vector2 point = Vector2(x,y) + pathfinding_zone.position;
        astar->add_point(i,point);
        // Connect with left neighbor
        if (x != 0) {
            astar->connect_points(i,i-1);
        }
        // Connect with top neighbor
        if (y != 0) {
            astar->connect_points(i,i-pathfinding_zone.size.x);
        }
        // If diagonal pathfinding is allowed
        if (y != 0 && allow_diagonal_pathfinding) {
            // Connect with top left neighbor
            if (x != 0) {
                astar->connect_points(i,i-pathfinding_zone.size.x-1);
            }
            // Connect with top right neighbor
            if (x != pathfinding_zone.size.x-1) {
                astar->connect_points(i,i-pathfinding_zone.size.x+1);
            }       
        }
        // Disable point if pathfinding not allowed
        if (!is_pathfinding_allowed(point)) {astar->set_point_disabled(i, true);}
        // Disable undiscovered points
        if (exclude_undiscovered == true && !is_discovered(point)) {astar->set_point_disabled(i, true);}
    }
    // Get entities in pathfinding zone
    PoolIntArray pathfinding_entities = get_entities_in_rect(pathfinding_zone);
    // Disable points if entities are on the way
    for (int k = 0; k < pathfinding_entities.size(); ++k) {
        Entity& entity = entities[pathfinding_entities[k]];
        if (!entity.passable) {
            Vector2 local_position = entity.position-pathfinding_zone.position;
            int point_index = local_position.x+local_position.y*pathfinding_zone.size.x;
            astar->set_point_disabled(point_index, true);
        }
    }
    // Define start and end index
    Vector2 local_start = start - pathfinding_zone.position;
    Vector2 local_end = end - pathfinding_zone.position;
    int start_index = local_start.y*pathfinding_zone.size.x+local_start.x;
    int end_index = local_end.y*pathfinding_zone.size.x+local_end.x;
    // Enable end point if it is disabled
    bool end_disabled = astar->is_point_disabled(end_index);
    astar->set_point_disabled(end_index, false);
    // Find path
    PoolIntArray id_path = astar->get_id_path(start_index, end_index);
    // Remove the last point of path if end was disabled
    if (id_path.size() > 0 && end_disabled) {
        id_path.remove(id_path.size()-1);
    }
    // Convert path from ints to Vector2
    for (int i=0; i<id_path.size(); ++i) {
        Vector2 point = astar->get_point_position(id_path[i]);
        path.append(point);
    }
    return path;
}
bool RGMap::is_pathfinding_allowed(Vector2 position) {
    int chunk_index = get_chunk_index(position);
    if (chunk_index >= size.x*size.y || chunk_index < 0) {return false;}
    // Check exceptions
    if(std::find(pathfinding_exception_allowed.begin(), pathfinding_exception_allowed.end(), position) != pathfinding_exception_allowed.end()) {
        return true;
    }
    if (std::find(pathfinding_exception_disallowed.begin(), pathfinding_exception_disallowed.end(), position) != pathfinding_exception_disallowed.end()) {
        return false;
    }
    // Check if cell is passable
    if (is_passable(position)) {return true;}
    return false;
}
PoolVector2Array RGMap::find_path(Vector2 start, Vector2 end, Rect2 pathfinding_zone) {
    return _find_path(start, end, pathfinding_zone, false);
}
PoolVector2Array RGMap::find_discovered_path(Vector2 start, Vector2 end, Rect2 pathfinding_zone) {
    return _find_path(start, end, pathfinding_zone, true);
}
PoolVector2Array RGMap::get_line_bresenham(Vector2 start, Vector2 end, bool allow_diagonal) {
    PoolVector2Array line;
    // Setup initial conditions
    int x1 = start.x;
    int y1 = start.y;
    int x2 = end.x;
    int y2 = end.y;
    int dx = x2 - x1;
    int dy = y2 - y1;
    // Determine how steep the line is
    bool is_steep = abs(dy) > abs(dx);
    // Rotate line
    if (is_steep) {
        std::swap(x1,y1);
        std::swap(x2,y2);
    }
    // Swap start and end points if necessary and store swap state
    bool swapped = false;
    if (x1 > x2) {
        std::swap(x1,x2);
        std::swap(y1,y2);
        swapped = true;
    }   
    // Recalculate differentials
    dx = x2 - x1;
    dy = y2 - y1;
    // Calculate error
    int error = int(dx / 2.0);
    int ystep = (y1 < y2) ? 1 : -1;
    // Iterate over bounding box generating points between start and end
    int y = y1;
    for (int x = x1; x < x2+1; ++x) {
        Vector2 coord = (is_steep) ? Vector2(y,x) : Vector2(x,y);
        line.append(coord);
        error -= abs(dy);
        if (error < 0) {
            y += ystep;
            error += dx;
            if (!allow_diagonal) {
                Vector2 coord2 = (is_steep) ? Vector2(y,x) : Vector2(x,y);
                line.append(coord2);
            }
            
        }
    }
    // Reverse the list if the coordinates were swapped
    if (swapped) { line.invert(); }
    return line;
}
PoolVector2Array RGMap::get_line(Vector2 start, Vector2 end) {return get_line_bresenham(start, end, true);}
PoolVector2Array RGMap::get_line_orthogonal(Vector2 start, Vector2 end) {return get_line_bresenham(start, end, false);}

Vector2 RGMap::raycast_vision(Vector2 start, Vector2 end) {
    PoolVector2Array line = get_line(start, end);
    for (int i = 0; i < line.size(); ++i){
        Vector2 point = line[i];
        if (!is_transparent(point)) {return point;}
    }
    return end;
}

Vector2 RGMap::raycast_path(Vector2 start, Vector2 end) {
    PoolVector2Array line = get_line(start, end);
    for (int i = 0; i < line.size(); ++i){
        Vector2 point = line[i];
        if (!is_passable(point)) {return point;}
    }
    return end;
}

bool RGMap::visibility_between(Vector2 start, Vector2 end, int max_distance) {
    if (start.distance_to(end) > max_distance) {return false;}
    Vector2 raycast = raycast_vision(start,end);
    if (raycast == end) {
        return true;
    } else {
        return false;
    }
}
#include "rgmap.h"

using namespace godot;

/*
    Register Godot properties and methods
*/

void RGMap::_register_methods() {
    register_property<RGMap, Vector2>("size", &RGMap::size, Vector2(3,3));
    register_property<RGMap, Vector2>("chunk_size", &RGMap::chunk_size, Vector2(50,50));
    register_property<RGMap, bool>("allowDiagonalPathfinding", &RGMap::allowDiagonalPathfinding, true);
    register_property<RGMap, RGTileset*>("tileset", &RGMap::tileset, nullptr);
    register_property<RGMap, float>("RPAS_RADIUS_FUDGE", &RGMap::RPAS_RADIUS_FUDGE, 1.0 / 3.0);
    register_property<RGMap, bool>("RPAS_NOT_VISIBLE_BLOCKS_VISION", &RGMap::RPAS_NOT_VISIBLE_BLOCKS_VISION, true);
    register_property<RGMap, int>("RPAS_RESTRICTIVENESS", &RGMap::RPAS_RESTRICTIVENESS, 1);
    register_property<RGMap, bool>("RPAS_VISIBLE_ON_EQUAL", &RGMap::RPAS_VISIBLE_ON_EQUAL, true);

    register_method("initialize", &RGMap::initialize);

    register_method("get_chunk_index", &RGMap::get_chunk_index);
    register_method("chunk_index_v2", &RGMap::chunk_index_v2);
    register_method("is_chunk_in_bounds", &RGMap::is_chunk_in_bounds);
    register_method("is_chunk_loaded", &RGMap::is_chunk_loaded);
    register_method("load_chunk", &RGMap::load_chunk);
    register_method("dump_chunk_data", &RGMap::dump_chunk_data);
    register_method("free_chunk", &RGMap::free_chunk);
    register_method("reset_chunk", &RGMap::reset_chunk);
    register_method("count_chunks", &RGMap::count_chunks);
    register_method("count_loaded_chunks", &RGMap::count_loaded_chunks);

    register_method("get_local_index", &RGMap::get_local_index);
    register_method("get_value", &RGMap::get_value);
    register_method("get_name", &RGMap::get_name);
    register_method("get_display_name", &RGMap::get_display_name);
    register_method("is_transparent", &RGMap::is_transparent);
    register_method("is_passable", &RGMap::is_passable);
    register_method("is_visible", &RGMap::is_visible);
    register_method("is_memorized", &RGMap::is_memorized);
    register_method("is_in_bounds", &RGMap::is_in_bounds);
    register_method("set_value", &RGMap::set_value);
    register_method("set_visibility", &RGMap::set_visibility);
    register_method("set_memorized", &RGMap::set_memorized);

    register_method("rpas_calc_visible_cells_from", &RGMap::rpas_calc_visible_cells_from);
    register_method("calculate_fov", &RGMap::calculate_fov);
    register_method("set_pathfinding", &RGMap::set_pathfinding);
    register_method("find_path", &RGMap::find_path);
    register_method("get_line", &RGMap::get_line);
    register_method("raycast_vision", &RGMap::raycast_vision);
    register_method("raycast_path", &RGMap::raycast_path);
    register_method("visibility_between", &RGMap::visibility_between);

    register_method("place_map", &RGMap::place_map);
    register_method("draw_line", &RGMap::draw_line);
    register_method("draw_rect", &RGMap::draw_rect);
    register_method("fill_rect", &RGMap::fill_rect);
    register_method("draw_ellipse", &RGMap::draw_ellipse);
    register_method("fill_ellipse", &RGMap::fill_ellipse);
    register_method("draw_circle", &RGMap::draw_circle);
    register_method("fill_circle", &RGMap::fill_circle);
    register_method("draw_arc", &RGMap::draw_arc);
    register_method("fill_arc", &RGMap::fill_arc);

    register_method("save_map_data", &RGMap::save_map_data);
    register_method("load_map_data", &RGMap::load_map_data);

}

/*
    Initialization and Utils
*/
RGMap::RGMap() {}

RGMap::~RGMap() {}

void RGMap::_init() {
    size = Vector2(3,3);
    chunk_size = Vector2(50,50);
    size_cells = Vector2(150,150);
    allowDiagonalPathfinding = true;
    astar.instance();
}

void RGMap::initialize(RGTileset* _tileset) {
    // Apply new tileset
    tileset = _tileset;
    // Generate empty chunks
    for (int i=0; i < size.x*size.y; ++i) {
        Chunk chunk;
        int chunk_y = floor(i/size.x);
        int chunk_x = i - chunk_y*size.x;
        chunk.index = Vector2(chunk_x, chunk_y);
        chunk.loaded = false;
        chunks.push_back(chunk);
    }
    // Define size (in cells)
    size_cells = size*chunk_size;
}

int RGMap::get_chunk_index(Vector2 position) {
    int y = floor(position.y/chunk_size.y);
    int x = floor(position.x/chunk_size.x);
    int index = x + y*size.x;
    return index;
}
Vector2 RGMap::chunk_index_v2(int index) {
    int y = floor(index/size.x);
    int x = index - y*size.x;
    return Vector2(x,y);
}
bool RGMap::is_chunk_in_bounds(int index){return index < chunks.size();}
bool RGMap::is_chunk_loaded(int index){
    ERR_FAIL_INDEX_V(index, chunks.size(), false);
    return chunks[index].loaded;
}
void RGMap::load_chunk(int index, PoolIntArray data) {
    // Trow out of bounds error
    ERR_FAIL_INDEX(index, chunks.size());
    int cells_number = chunk_size.x*chunk_size.y;
    Chunk& chunk = chunks[index];
    // Load chunk from data
    if (data.size() > 0) {
        // New chunk from data
        if (!chunk.loaded) {
            for (int i=0; i < cells_number; ++i) {
                chunk.values.push_back(data[i]);
                chunk.memory.push_back(data[i+cells_number]);
            }
        // Apply data to existing chunk
        } else {
            for (int i=0; i < cells_number; ++i) {
                chunk.values[i] = data[i];
                chunk.memory[i] = data[i+cells_number];
            }
        }    
    // Generate new chunk
    } else if (!chunk.loaded) {
        chunk.values.resize(cells_number, 0);
        chunk.memory.resize(cells_number, 0);
    }
    chunk.loaded = true;
}
PoolIntArray RGMap::dump_chunk_data(int index) {
    PoolIntArray data;
    // Trow out of bounds error
    ERR_FAIL_INDEX_V(index, chunks.size(), data);
    Chunk& chunk = chunks[index];
    // Return empty if chunk is not loaded
    if (!chunk.loaded) {return data;}
    // Dump data
    for (int i=0; i < chunk_size.x*chunk_size.y; ++i) {
        data.append(chunk.values[i]);
        data.append(chunk.memory[i]);
    }
    return data;
}
void RGMap::free_chunk(int index) {
    // Trow out of bounds error
    ERR_FAIL_INDEX(index, chunks.size());
    Chunk& chunk = chunks[index];
    // Clear arrays
    if (chunk.loaded) {
        chunk.values.clear();
        chunk.values.shrink_to_fit();
        chunk.memory.clear();
        chunk.memory.shrink_to_fit();
        chunk.loaded = false;
    }
}
void RGMap::reset_chunk(int index) {
    ERR_FAIL_INDEX(index, chunks.size());
    Chunk& chunk = chunks[index];
    if (!is_chunk_loaded(index)) {load_chunk(index);}
    else {
        for (int i=0; i < chunk_size.x*chunk_size.y; ++i) {
            chunk.values[i] = 0;
            chunk.memory[i] = 0;
        } 
    }
}
int RGMap::count_chunks(){return size.x*size.y;}
int RGMap::count_loaded_chunks() {
    int loaded = 0;
    for (Chunk chunk : chunks){
        if (chunk.loaded) {loaded++;}
    }
    return loaded;
}





void RGMap::clean_map_data() {
    // Clear map arrays and astar
    for (int i=0; i<values.size(); ++i) {
        values.remove(0);
        memory.remove(0);
    }
    astar->clear();
}

void RGMap::generate_astar() {
    for (int i=0; i<size.x*size.y; ++i) {
        // Add astar point
        int y = floor(i/size.x);
        int x = i - y*size.x;
        Vector2 point = Vector2(x,y);
        astar->add_point(i,point);
        // Connect with left neighbor
        if (x != 0) {
            astar->connect_points(i,i-1);
        }
        // Connect with top neighbor
        if (y != 0) {
            astar->connect_points(i,i-size.x);
        }
        // If diagonal pathfinding is allowed
        if (y != 0 && allowDiagonalPathfinding) {
            // Connect with top left neighbor
            if (x != 0) {
                astar->connect_points(i,i-size.x-1);
            }
            // Connect with top right neighbor
            if (x != size.x-1) {
                astar->connect_points(i,i-size.x+1);
            }
            
        }
        // Set pathfinding
        astar->set_point_disabled(i, !tileset->is_passable(values[i]));
    }
}







/*
    Cell data getters
*/
int RGMap::get_index(Vector2 position){return 0;}
Vector2 RGMap::get_position(int index){return Vector2(0,0);}
int RGMap::get_local_index(Vector2 position) {
    int chunk_pos_y = floor(position.y/chunk_size.y);
    int chunk_pos_x = floor(position.x/chunk_size.x);
    Vector2 chunk_pos = Vector2(chunk_pos_x, chunk_pos_y);
    Vector2 local_position = position - chunk_pos*chunk_size;
    int index = local_position.x + local_position.y*chunk_size.x;
    return index;
}
bool RGMap::is_in_bounds(Vector2 position) {
    bool x_in_bounds = position.x < size_cells.x && position.x >= 0;
    bool y_in_bounds = position.y < size_cells.y && position.y >= 0;
    return x_in_bounds && y_in_bounds;
}
int RGMap::get_value(Vector2 position) {
    int chunk_index = get_chunk_index(position);
    ERR_FAIL_INDEX_V(chunk_index, chunks.size(), 0);
    Chunk& chunk = chunks[chunk_index];
    if (!chunk.loaded) {return 0;}
    int index = get_local_index(position);
    return chunk.values[index];
}
String RGMap::get_name(Vector2 position) {
    return tileset->get_name(get_value(position));
}
String RGMap::get_display_name(Vector2 position) {
    return tileset->get_display_name(get_value(position));
}
bool RGMap::is_transparent(Vector2 position) {
    return tileset->is_transparent(get_value(position));
}
bool RGMap::is_passable(Vector2 position) {
    return tileset->is_passable(get_value(position));
}
bool RGMap::is_visible(Vector2 position) {
    if (!fov_zone.has_point(position)) {return false;}
    Vector2 local_position = position - fov_zone.position;
    int index = int(local_position.x + local_position.y*fov_zone.size.x);
    ERR_FAIL_INDEX_V(index, visibility.size(), false);
    return visibility[index];
    }
bool RGMap::is_memorized(Vector2 position) {
    int chunk_index = get_chunk_index(position);
    ERR_FAIL_INDEX_V(chunk_index, chunks.size(), false);
    Chunk& chunk = chunks[chunk_index];
    if (!chunk.loaded) {return false;}
    int index = get_local_index(position);
    return chunk.memory[index] == 1;
    }

/*
    Cell data setters
*/

void RGMap::set_value(Vector2 position, int value) {
    int chunk_index = get_chunk_index(position);
    ERR_FAIL_INDEX(chunk_index, chunks.size());
    Chunk& chunk = chunks[chunk_index];
    if (!chunk.loaded) {load_chunk(chunk_index);}
    int index = get_local_index(position);
    chunk.values[index] = value;
    chunk.memory[index] = 0;
}

void RGMap::set_visibility(Vector2 position, bool value) {
    if (!fov_zone.has_point(position)) {return;}
    Vector2 local_position = position - fov_zone.position;
    int index = int(local_position.x + local_position.y*fov_zone.size.x);
    ERR_FAIL_INDEX(index, visibility.size());
    visibility[index] = (value) ? 1 : 0;
}

void RGMap::set_memorized(Vector2 position, bool value) {
    int chunk_index = get_chunk_index(position);
    ERR_FAIL_INDEX(chunk_index, chunks.size());
    Chunk& chunk = chunks[chunk_index];
    if (!chunk.loaded) {load_chunk(chunk_index);}
    int index = get_local_index(position);
    int int_value = (value) ? 1 : 0;
    chunk.memory[index] = int_value;
}

void RGMap::set_pathfinding(Vector2 position, bool value) {
    astar->set_point_disabled(get_index(position), !value);
}


/*
    View and pathfinding
*/
void RGMap::calculate_fov(Vector2 view_position, int max_distance) {
    fov_zone.size = Vector2(1,1)*(max_distance*2+2);
    fov_zone.position = view_position - Vector2(1,1)*max_distance - Vector2(1,1);
    visibility.resize(fov_zone.size.x*fov_zone.size.y);
    for (int i=0; i<visibility.size(); ++i){
        visibility[i] = 0;
    }
    PoolVector2Array visible_cells = rpas_calc_visible_cells_from(view_position, max_distance);
    for (int i=0; i < visible_cells.size(); ++i) {
        set_visibility(visible_cells[i], true);
        set_memorized(visible_cells[i], true);
    }
}
PoolVector2Array RGMap::find_path(Vector2 start, Vector2 end) {
    if (is_in_bounds(start) && is_in_bounds(end)) {
        // Define indexes
        int start_index = start.y*size.x+start.x;
        int end_index = end.y*size.x+end.x;
        // Define if start and end points are disabled
        bool start_disabled = astar->is_point_disabled(start_index);
        bool end_disabled = astar->is_point_disabled(end_index);
        // Temporarily unlock start and end points
        astar->set_point_disabled(start_index, false);
        astar->set_point_disabled(end_index, false);
        // Calculate path
        // PoolVector2Array path = astar->get_point_path(start_index, end_index); // not thread-safe
        PoolIntArray id_path = astar->get_id_path(start_index, end_index);
        // Set points disabled back to original values
        astar->set_point_disabled(start_index, start_disabled);
        astar->set_point_disabled(end_index, end_disabled);
        // Get PoolVector2Array path
        PoolVector2Array path;
        for (int i=0; i<id_path.size(); ++i) {
            Vector2 point = get_position(id_path[i]);
            path.append(point);
        }
        return path;
    }
    else {
        PoolVector2Array empty;
        return empty;
    }
}

PoolVector2Array RGMap::get_line(Vector2 start, Vector2 end, bool allow_diagonal) {
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

bool RGMap::visibility_between(Vector2 start, Vector2 end) {
    Vector2 raycast = raycast_vision(start,end);
    if (raycast == end) {
        return true;
    } else {
        return false;
    }
}


/*
    Editing
*/

void RGMap::place_map(RGMap* another_map, Vector2 start) {
    for (int x=0; x < another_map->size.x; ++x) {
        for (int y=0; y < another_map->size.y; ++y) {
            Vector2 cell = start + Vector2(x,y);
            if  (!is_in_bounds(cell)) { continue; }
            set_value(cell, another_map->get_value(Vector2(x,y)));
            set_memorized(cell, another_map->is_memorized(Vector2(x,y)));
        }
    }
}

void RGMap::draw_line(Vector2 start, Vector2 end, int value, bool allow_diagonal) {
    PoolVector2Array line = get_line(start, end, allow_diagonal);
    for (int i = 0; i < line.size(); ++i){
        Vector2 point = line[i];
        set_value(point, value);
    }
}

void RGMap::draw_rect(Rect2 rect, int value) {
    for (int x = 0; x<rect.size.x; ++x) {
        for (int y = 0; y<rect.size.y; ++y) {
            if (y==0 || y==rect.size.y-1 || x==0 || x==rect.size.x-1){
                Vector2 point = rect.position + Vector2(x,y);
                set_value(point, value);
            }
        }
    }
}

void RGMap::fill_rect(Rect2 rect, int value) {
    for (int x = 0; x<rect.size.x; ++x) {
        for (int y = 0; y<rect.size.y; ++y) {
            Vector2 point = rect.position + Vector2(x,y);
            set_value(point, value);
        }
    }
}

void RGMap::draw_4_way_symmetry(int xc, int yc, int x, int y, int value, float start_angle, float end_angle) {
    Vector2 center = Vector2(xc, yc);
    PoolVector2Array points;
    bool inverse = false;
    points.append(Vector2(x+xc, y+yc));
    points.append(Vector2(-x+xc, y+yc));
    points.append(Vector2(x+xc, -y+yc));
    points.append(Vector2(-x+xc, -y+yc));
    if (start_angle > end_angle) {
        inverse = true;
        float new_start_angle = -M_PI-end_angle;
        end_angle = M_PI-start_angle;
        start_angle = new_start_angle;
    }
    for (int i=0; i<points.size(); ++i) {
        Vector2 point = points[i];
        Vector2 direction = point - center;
        float angle = direction.angle();
        if (inverse) {
            if (angle > 0 || fabs(angle) < FLOAT_EPSILON) {angle = M_PI-angle;}
            else {angle = -M_PI-angle;}
        }
        if ((start_angle < angle || fabs(start_angle - angle) < FLOAT_EPSILON) 
        && (angle < end_angle || fabs(end_angle - angle) < FLOAT_EPSILON)) {
            set_value(point,value);
        }
    }
}

void RGMap::draw_ellipse(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value, bool allow_diagonal) {
    int rx = radius.x;
    int ry = radius.y;
    int xc = center.x;
    int yc = center.y;
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;
    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) +
                     (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;
    // For region 1
    while (dx < dy)
    {
        // Add points based on 4-way symmetry
        draw_4_way_symmetry(xc,yc,x,y,value,start_angle,end_angle);
        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            y--;
            // Add points based on 4-way symmetry (If no diagonals allowed)
            if (!allow_diagonal) {draw_4_way_symmetry(xc,yc,x,y,value,start_angle,end_angle);}
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }
    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
         ((rx * rx) * ((y - 1) * (y - 1))) -
          (rx * rx * ry * ry);
    // Plotting points of region 2
    while (y >= 0)
    {
        // Add points based on 4-way symmetry
        draw_4_way_symmetry(xc,yc,x,y,value,start_angle,end_angle);
        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            // Add points based on 4-way symmetry (If no diagonals allowed)
            if (!allow_diagonal) {draw_4_way_symmetry(xc,yc,x,y,value,start_angle,end_angle);}
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
    // Not full semicircle quickfix
    if (fabs(fabs(start_angle) - M_PI) < FLOAT_EPSILON 
    && fabs(end_angle) < FLOAT_EPSILON) {
        draw_line(center+Vector2(radius.x,0), center-Vector2(radius.x,0), value);
    }
}

void RGMap::fill_ellipse(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value) {
    for (int rx = radius.x; rx >= 0; --rx) {
        draw_ellipse(center, Vector2(rx,radius.y), start_angle, end_angle, value, true);
    }
    // Unfilled center quickfix
    set_value(center, value);
}

void RGMap::draw_circle(Vector2 center, float radius, int value, bool allow_diagonal) {
    draw_ellipse(center, Vector2(radius,radius), -M_PI, M_PI, value, allow_diagonal);
}
void RGMap::fill_circle(Vector2 center, float radius, int value) {
    fill_ellipse(center, Vector2(radius,radius), -M_PI, M_PI, value);
}
void RGMap::draw_arc(Vector2 center, float radius, float start_angle, float end_angle, int value, bool allow_diagonal) {
    draw_ellipse(center, Vector2(radius,radius), start_angle, end_angle, value, allow_diagonal);
}
void RGMap::fill_arc(Vector2 center, float radius, float start_angle, float end_angle, int value) {
    fill_ellipse(center, Vector2(radius,radius), start_angle, end_angle, value);
}
/*
    Saving and Loading
*/

PoolIntArray RGMap::save_map_data() {
    PoolIntArray map_data;
    map_data.append(size.x);
    map_data.append(size.y);
    map_data.append_array(values);
    map_data.append_array(memory);
    return map_data;
}

void RGMap::load_map_data(PoolIntArray map_data) {
    clean_map_data();
    size.x = map_data[0];
    size.y = map_data[1];
    for (int i = 0; i < size.x*size.y; ++i) {
        values.append(map_data[i+2]);
        memory.append(map_data[i+2+size.x*size.y]);
    }
    generate_astar();
}
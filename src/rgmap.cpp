#include "rgmap.h"

using namespace godot;

/*
    Register Godot properties and methods
*/

void RGMap::_register_methods() {
    register_property<RGMap, Vector2>("size", &RGMap::size, Vector2(3,3));
    register_property<RGMap, Vector2>("chunk_size", &RGMap::chunk_size, Vector2(50,50));
    register_property<RGMap, int>("render_distance", &RGMap::render_distance, 1);
    register_property<RGMap, bool>("allow_diagonal_pathfinding", &RGMap::allow_diagonal_pathfinding, true);
    register_property<RGMap, float>("RPAS_RADIUS_FUDGE", &RGMap::RPAS_RADIUS_FUDGE, 1.0 / 3.0);
    register_property<RGMap, bool>("RPAS_NOT_VISIBLE_BLOCKS_VISION", &RGMap::RPAS_NOT_VISIBLE_BLOCKS_VISION, true);
    register_property<RGMap, int>("RPAS_RESTRICTIVENESS", &RGMap::RPAS_RESTRICTIVENESS, 1);
    register_property<RGMap, bool>("RPAS_VISIBLE_ON_EQUAL", &RGMap::RPAS_VISIBLE_ON_EQUAL, true);

    register_signal<RGMap>((char *)"chunks_load_requested", "ids", GODOT_VARIANT_TYPE_POOL_INT_ARRAY);
    register_signal<RGMap>((char *)"chunks_free_requested", "ids", GODOT_VARIANT_TYPE_POOL_INT_ARRAY);
    register_signal<RGMap>((char *)"chunk_loaded", "index", GODOT_VARIANT_TYPE_INT);
    register_signal<RGMap>((char *)"chunk_freed", "index", GODOT_VARIANT_TYPE_INT);

    register_method("clean_map", &RGMap::clean_map);

    register_method("add_tile", &RGMap::add_tile);
    register_method("get_tiles_count", &RGMap::get_tiles_count);
    register_method("get_tile_index", &RGMap::get_tile_index);
    register_method("get_tile_name", &RGMap::get_tile_name);
    register_method("get_tile_display_name", &RGMap::get_tile_display_name);
    register_method("is_tile_passable", &RGMap::is_tile_passable);
    register_method("is_tile_transparent", &RGMap::is_tile_transparent);
    register_method("generate_tileset", &RGMap::generate_tileset);

    register_method("get_chunk_index", &RGMap::get_chunk_index);
    register_method("chunk_index_int_to_v2", &RGMap::chunk_index_int_to_v2);
    register_method("chunk_index_v2_to_int", &RGMap::chunk_index_v2_to_int);
    register_method("is_chunk_in_bounds", &RGMap::is_chunk_in_bounds);
    register_method("is_chunk_loaded", &RGMap::is_chunk_loaded);
    register_method("load_chunk", &RGMap::load_chunk);
    register_method("dump_chunk_data", &RGMap::dump_chunk_data);
    register_method("free_chunk", &RGMap::free_chunk);
    register_method("reset_chunk", &RGMap::reset_chunk);
    register_method("count_chunks", &RGMap::count_chunks);
    register_method("count_loaded_chunks", &RGMap::count_loaded_chunks);
    register_method("get_loaded_chunks", &RGMap::get_loaded_chunks);
    register_method("get_chunks_to_load", &RGMap::get_chunks_to_load);
    register_method("get_chunks_to_free", &RGMap::get_chunks_to_free);
    register_method("request_chunks_update", &RGMap::request_chunks_update);
    
    register_method("get_local_index", &RGMap::get_local_index);
    register_method("get_value", &RGMap::get_value);
    register_method("get_name", &RGMap::get_name);
    register_method("get_display_name", &RGMap::get_display_name);
    register_method("is_transparent", &RGMap::is_transparent);
    register_method("is_passable", &RGMap::is_passable);
    register_method("is_visible", &RGMap::is_visible);
    register_method("is_memorized", &RGMap::is_memorized);
    register_method("is_in_bounds", &RGMap::is_in_bounds);
    register_method("is_pathfinding_allowed", &RGMap::is_pathfinding_allowed);
    register_method("set_value", &RGMap::set_value);
    register_method("set_visibility", &RGMap::set_visibility);
    register_method("set_memorized", &RGMap::set_memorized);

    register_method("rpas_calc_visible_cells_from", &RGMap::rpas_calc_visible_cells_from);
    register_method("calculate_fov", &RGMap::calculate_fov);
    register_method("add_pathfinding_exception", &RGMap::add_pathfinding_exception);
    register_method("remove_pathfinding_exception", &RGMap::remove_pathfinding_exception);
    register_method("show_pathfinding_exceptions", &RGMap::show_pathfinding_exceptions);
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

    register_method("add_entity", &RGMap::add_entity);
    register_method("remove_entity", &RGMap::remove_entity);
    register_method("move_entity", &RGMap::move_entity);
    register_method("set_entity_transparency", &RGMap::set_entity_transparency);
    register_method("set_entity_passability", &RGMap::set_entity_passability);
    register_method("set_entity_memorized", &RGMap::set_entity_memorized);
    register_method("is_entity_visible", &RGMap::is_entity_visible);
    register_method("is_entity_transparent", &RGMap::is_entity_transparent);
    register_method("is_entity_passable", &RGMap::is_entity_passable);
    register_method("is_entity_memorized", &RGMap::is_entity_memorized);
    register_method("is_entity_chunk_loaded", &RGMap::is_entity_chunk_loaded);
    register_method("get_entity_position", &RGMap::get_entity_position);
    register_method("get_entities_in_position", &RGMap::get_entities_in_position);
    register_method("get_entities_in_rect", &RGMap::get_entities_in_rect);
    register_method("get_entities_in_radius", &RGMap::get_entities_in_radius);
    register_method("get_entities_in_chunk", &RGMap::get_entities_in_chunk);

    register_method("dump_map_data", &RGMap::dump_map_data);
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
    allow_diagonal_pathfinding = true;
}

void RGMap::clean_map() {
    chunks.clear();
    chunks.shrink_to_fit();
    pathfinding_exception_allowed.clear();
    pathfinding_exception_allowed.shrink_to_fit();
    pathfinding_exception_disallowed.clear();
    pathfinding_exception_disallowed.shrink_to_fit();
}

/*
    Tiles
*/

void RGMap::add_tile(String name, String display_name, bool passable, bool transparent) {
    RGTile tile;
    tile.name = name;
    tile.display_name = display_name;
    tile.passable = passable;
    tile.transparent = transparent;
    tiles.push_back(tile);
}
int RGMap::get_tiles_count() {
    return tiles.size();
}

int RGMap::get_tile_index(String name) { 
    for (int i=0; i < tiles.size(); ++i) {
        RGTile tile = tiles[i];
        if (tile.name == name) {
            return i;
        }
    }
    return -1; 
}
String RGMap::get_tile_name(int index) { return tiles[index].name; }
String RGMap::get_tile_display_name(int index) { return tiles[index].display_name; }
bool RGMap::is_tile_passable(int index) { return tiles[index].passable; }
bool RGMap::is_tile_transparent(int index) { return tiles[index].transparent; }
Ref<TileSet> RGMap::generate_tileset(String texture_path, String texture_format){
    ResourceLoader* res_loader = ResourceLoader::get_singleton();
    Ref<TileSet> new_tileset;
    new_tileset.instance();
    for (int i=0; i < get_tiles_count(); ++i) {
        new_tileset->create_tile(i);
        String tile_name = get_tile_name(i);
        Ref<Texture> texture = res_loader->load(texture_path+tile_name+texture_format);
        new_tileset->tile_set_texture(i, texture);
    }
    return new_tileset;
}

/*
    Chunks
*/

RGMap::Chunk& RGMap::get_chunk(int index) {
    for (int i=0; i< chunks.size();++i) {
        if (chunks[i].index == index) {return chunks[i];}
    }
}
int RGMap::get_chunk_index(Vector2 position) {
    int y = floor(position.y/chunk_size.y);
    int x = floor(position.x/chunk_size.x);
    int index = x + y*size.x;
    return index;
}
Vector2 RGMap::chunk_index_int_to_v2(int index) {
    int y = floor(index/size.x);
    int x = index - y*size.x;
    return Vector2(x,y);
}
int RGMap::chunk_index_v2_to_int(Vector2 index) {return index.x+index.y*size.x;}

bool RGMap::is_chunk_in_bounds(int index){return index < chunks.size() && index >= 0;}
bool RGMap::is_chunk_loaded(int index){
    ERR_FAIL_INDEX_V(index, size.x*size.y, false);
    for (Chunk chunk : chunks) {
        if (chunk.index == index) {return true;}
    }
    return false;
}
void RGMap::load_chunk(int index, PoolIntArray data) {
    // Trow out of bounds error
    ERR_FAIL_INDEX(index, size.x*size.y);
    int cells_number = chunk_size.x*chunk_size.y;
    if (is_chunk_loaded(index)) {
        Chunk& chunk = get_chunk(index);
        if (data.size() > 0) {
            for (int i=0; i < cells_number; ++i) {
                chunk.values[i] = data[i];
                chunk.memory[i] = data[i+cells_number];
            }
        } else {
            for (int i=0; i < cells_number; ++i) {
                chunk.values[i] = 0;
                chunk.memory[i] = 0;
            }
        }
    } else {
        Chunk chunk;
        chunk.index = index;
        if (data.size() > 0) {
            for (int i=0; i < cells_number; ++i) {
                chunk.values.push_back(data[i]);
                chunk.memory.push_back(data[i+cells_number]);
            }
        } else {
            chunk.values.resize(cells_number, 0);
            chunk.memory.resize(cells_number, 0);
        }
        chunks.push_back(chunk);
        emit_signal("chunk_loaded", index);
    }
}
PoolIntArray RGMap::dump_chunk_data(int index) {
    PoolIntArray data;
    // Trow out of bounds error
    ERR_FAIL_INDEX_V(index, size.x*size.y, data);
    if (!is_chunk_loaded(index)) {ERR_PRINT("Chunk not loaded. Can't dump data"); return data; }
    Chunk& chunk = get_chunk(index);
    // Dump data
    for (int i=0; i < chunk_size.x*chunk_size.y; ++i) {
        data.append(chunk.values[i]);
    }
    for (int i=0; i < chunk_size.x*chunk_size.y; ++i) {
        data.append(chunk.memory[i]);
    }
    return data;
}
void RGMap::free_chunk(int index) {
    // Trow out of bounds error
    ERR_FAIL_INDEX(index, size.x*size.y);
    if (!is_chunk_loaded(index)) {return; }
    for (int i=0; i<chunks.size(); ++i) {
        Chunk& chunk = chunks[i];
        if (chunk.index == index) {
            chunks.erase(chunks.begin() + i);
            chunks.shrink_to_fit();
            emit_signal("chunk_freed", index);
            return;
        }
    }
}
void RGMap::reset_chunk(int index) {
    ERR_FAIL_INDEX(index, size.x*size.y);
    if (!is_chunk_loaded(index)) {load_chunk(index);}
    else {
        Chunk& chunk = get_chunk(index);
        for (int i=0; i < chunk_size.x*chunk_size.y; ++i) {
            chunk.values[i] = 0;
            chunk.memory[i] = 0;
        } 
    }
}
int RGMap::count_chunks(){return size.x*size.y;}
int RGMap::count_loaded_chunks() { return chunks.size();}
PoolIntArray RGMap::get_loaded_chunks() {
    PoolIntArray loaded;
    for (Chunk chunk : chunks) {
        loaded.append(chunk.index);
    }
    return loaded;
}
PoolIntArray RGMap::get_chunks_to_load(Vector2 player_position) {
    PoolIntArray to_load;
    int center_index = get_chunk_index(player_position);
    for (int x = -render_distance; x < render_distance+1; ++x) {
        for (int y = -render_distance; y < render_distance+1; ++y) {
            int index = center_index + x + y*size.x;
            if (index >= 0 && index < size.x*size.y && !is_chunk_loaded(index)) {
                to_load.append(index);
            }
        }
    }
    return to_load;
}
PoolIntArray RGMap::get_chunks_to_free(Vector2 player_position) {
    PoolIntArray to_free;
    int center_index = get_chunk_index(player_position);
    Vector2 center_index_v2 = chunk_index_int_to_v2(center_index);
    PoolIntArray loaded = get_loaded_chunks();
    for (int i = 0; i < loaded.size(); ++i) {
        int index = loaded[i];
        Vector2 index_v2 = chunk_index_int_to_v2(index);
        if (index_v2.x < center_index_v2.x-render_distance || index_v2.y < center_index_v2.y-render_distance
        || index_v2.x > center_index_v2.x+render_distance || index_v2.y > center_index_v2.y+render_distance) {
            to_free.append(index);
        }
    }
    return to_free;
}
void RGMap::request_chunks_update(Vector2 player_position) {
    PoolIntArray to_load = get_chunks_to_load(player_position);
    emit_signal("chunks_load_requested", to_load);
    PoolIntArray to_free = get_chunks_to_free(player_position);
    emit_signal("chunks_free_requested", to_free);
}

/*
    Cells
*/

int RGMap::get_local_index(Vector2 position) {
    int chunk_pos_y = floor(position.y/chunk_size.y);
    int chunk_pos_x = floor(position.x/chunk_size.x);
    Vector2 chunk_pos = Vector2(chunk_pos_x, chunk_pos_y);
    Vector2 local_position = position - chunk_pos*chunk_size;
    int index = local_position.x + local_position.y*chunk_size.x;
    return index;
}
bool RGMap::is_in_bounds(Vector2 position) {
    bool x_in_bounds = position.x < size.x*chunk_size.x && position.x >= 0;
    bool y_in_bounds = position.y < size.y*chunk_size.y && position.y >= 0;
    return x_in_bounds && y_in_bounds;
}
int RGMap::get_value(Vector2 position) {
    int chunk_index = get_chunk_index(position);
    if (chunk_index < 0 || chunk_index > size.x*size.y) {return 0;}
    if (!is_chunk_loaded(chunk_index)) {return 0;}
    Chunk& chunk = get_chunk(chunk_index);
    int index = get_local_index(position);
    return chunk.values[index];
}
String RGMap::get_name(Vector2 position) {
    return get_tile_name(get_value(position));
}
String RGMap::get_display_name(Vector2 position) {
    return get_tile_display_name(get_value(position));
}
bool RGMap::is_transparent(Vector2 position) {
    if (fov_zone.has_point(position)) {
        Vector2 local_position = position - fov_zone.position;
        int index = int(local_position.x + local_position.y*fov_zone.size.x);
        if (fov_obstacles[index] == 1) { return false;}
    }
    return is_tile_transparent(get_value(position));
}
bool RGMap::is_passable(Vector2 position) {
    return is_tile_passable(get_value(position));
}
bool RGMap::is_visible(Vector2 position) {
    if (!fov_zone.has_point(position)) {return false;}
    Vector2 local_position = position - fov_zone.position;
    int index = int(local_position.x + local_position.y*fov_zone.size.x);
    return visibility[index];
    }
bool RGMap::is_memorized(Vector2 position) {
    int chunk_index = get_chunk_index(position);
    if (chunk_index < 0 || chunk_index > size.x*size.y) {return false;}
    if (!is_chunk_loaded(chunk_index)) {return false;}
    Chunk& chunk = get_chunk(chunk_index);
    int index = get_local_index(position);
    return chunk.memory[index] == 1;
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
void RGMap::set_value(Vector2 position, int value) {
    int chunk_index = get_chunk_index(position);
    ERR_FAIL_INDEX(chunk_index, size.x*size.y);
    if (!is_chunk_loaded(chunk_index)) {load_chunk(chunk_index);}
    Chunk& chunk = get_chunk(chunk_index);
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
    ERR_FAIL_INDEX(chunk_index, size.x*size.y);
    if (!is_chunk_loaded(chunk_index)) {return;}
    Chunk& chunk = get_chunk(chunk_index);
    int index = get_local_index(position);
    int int_value = (value) ? 1 : 0;
    chunk.memory[index] = int_value;
}

/*
    View and pathfinding
*/

void RGMap::calculate_fov(Vector2 view_position, int max_distance) {
    // Define fov zone and resize visibility array
    fov_zone.size = Vector2(1,1)*(max_distance*2+2);
    fov_zone.position = view_position - Vector2(1,1)*max_distance - Vector2(1,1);
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
            if (!entity.transparency) {
                Vector2 local_position = entity.position-fov_zone.position;
                int cell_index = local_position.x+local_position.y*fov_zone.size.x;
                fov_obstacles[cell_index] = 1;
            }
    }
    // Get visible cells
    PoolVector2Array visible_cells = rpas_calc_visible_cells_from(view_position, max_distance);
    for (int i=0; i < visible_cells.size(); ++i) {
        set_visibility(visible_cells[i], true);
        set_memorized(visible_cells[i], true);
    }
    // Memorize entities
    for (int i = 0; i < fov_entities.size(); ++i) {
        Entity& entity = entities[fov_entities[i]];
        Vector2 local_position = entity.position-fov_zone.position;
        int cell_index = local_position.x+local_position.y*fov_zone.size.x;
        if (visibility[cell_index] == 1) {
            entity.memorized = true;
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
PoolVector2Array RGMap::find_path(Vector2 start, Vector2 end, Rect2 pathfinding_zone) {
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
    }
    // Get entities in pathfinding zone
    PoolIntArray pathfinding_entities = get_entities_in_rect(pathfinding_zone);
    // Disable points if entities are on the way
    for (int k = 0; k < pathfinding_entities.size(); ++k) {
        Entity& entity = entities[pathfinding_entities[k]];
        if (!entity.passability) {
            Vector2 local_position = entity.position-pathfinding_zone.position;
            int point_index = local_position.x+local_position.y*pathfinding_zone.size.x;
            astar->set_point_disabled(point_index, true);
        }
    }
    // Find path
    Vector2 local_start = start - pathfinding_zone.position;
    Vector2 local_end = end - pathfinding_zone.position;
    int start_index = local_start.y*pathfinding_zone.size.x+local_start.x;
    int end_index = local_end.y*pathfinding_zone.size.x+local_end.x;
    PoolIntArray id_path = astar->get_id_path(start_index, end_index);
    // Convert path from ints to Vector2
    for (int i=0; i<id_path.size(); ++i) {
        Vector2 point = astar->get_point_position(id_path[i]);
        path.append(point);
    }
    return path;
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

bool RGMap::visibility_between(Vector2 start, Vector2 end, int max_distance) {
    if (start.distance_to(end) > max_distance) {return false;}
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
    for (int x=0; x < another_map->size.x*another_map->chunk_size.x; ++x) {
        for (int y=0; y < another_map->size.y*another_map->chunk_size.y; ++y) {
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
    Entities
*/

int RGMap::add_entity(Vector2 position, bool passability, bool transparency) {
    // Rewrite data for entities marked as rewrite
    for (int i = 0; i < entities.size(); ++i) {
        Entity& entity = entities[i];
        if (entity.rewrite) {
            entity.position = position;
            entity.passability = passability;
            entity.transparency = transparency;
            entity.memorized = false;
            entity.rewrite = false;
            return i;
        }
    }
    // Create new entity
    Entity entity;
    entity.position = position;
    entity.passability = passability;
    entity.transparency = transparency;
    entity.memorized = false;
    entities.push_back(entity);
    return entities.size()-1;
}
void RGMap::remove_entity(int id) {
    ERR_FAIL_INDEX(id, entities.size());
    entities[id].rewrite = true;
}
void RGMap::move_entity(int id, Vector2 position) {
    ERR_FAIL_INDEX(id, entities.size());
    entities[id].position = position;
}
void RGMap::set_entity_transparency(int id, bool value) {
    ERR_FAIL_INDEX(id, entities.size());
    entities[id].transparency = value;
}
void RGMap::set_entity_passability(int id, bool value) {
    ERR_FAIL_INDEX(id, entities.size());
    entities[id].passability = value;
}
void RGMap::set_entity_memorized(int id, bool value) {
    ERR_FAIL_INDEX(id, entities.size());
    entities[id].memorized = value;
}
bool RGMap::is_entity_visible(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), false);
    Vector2 position = get_entity_position(id);
    return is_visible(position);
}
bool RGMap::is_entity_transparent(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), true);
    return entities[id].transparency;
}
bool RGMap::is_entity_passable(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), true);
    return entities[id].passability;
}
bool RGMap::is_entity_memorized(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), false);
    return entities[id].memorized;
}
bool RGMap::is_entity_chunk_loaded(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), false);
    int chunk_index = get_chunk_index(entities[id].position);
    return is_chunk_loaded(chunk_index);
}
Vector2 RGMap::get_entity_position(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), Vector2(0,0));
    return entities[id].position;
}
PoolIntArray RGMap::get_entities_in_position(Vector2 position) {
    PoolIntArray ids;
    for (int i = 0; i < entities.size(); ++i) {
        Entity& entity = entities[i];
        if (!entity.rewrite && entity.position == position) {
            ids.append(i);
        }
    }
    return ids;
}
PoolIntArray RGMap::get_entities_in_rect(Rect2 rect) {
    PoolIntArray ids;
    for (int i = 0; i < entities.size(); ++i) {
        Entity& entity = entities[i];
        if (!entity.rewrite && rect.has_point(entity.position)) {
            ids.append(i);
        }
    }
    return ids;
}
PoolIntArray RGMap::get_entities_in_radius(Vector2 position, int radius) {
    PoolIntArray ids;
    for (int i = 0; i < entities.size(); ++i) {
        Entity& entity = entities[i];
        if (!entity.rewrite && entity.position.distance_to(position) <= radius) {
            ids.append(i);
        }
    }
    return ids;
}
PoolIntArray RGMap::get_entities_in_chunk(int chunk_index) {
    PoolIntArray ids;
    Vector2 start = chunk_index_int_to_v2(chunk_index)*chunk_size;
    Vector2 end = start+chunk_size;
    for (int i = 0; i < entities.size(); ++i) {
        Entity& entity = entities[i];
        Vector2 position = entity.position;
        if (!entity.rewrite && position.x >= start.x && position.x < end.x && position.y >= start.x && position.y < end.y) {
            ids.append(i);
        }
    }
    return ids;
}

/*
    Saving and Loading
*/

PoolIntArray RGMap::dump_map_data() {
    PoolIntArray map_data;
    // Save size data
    map_data.append(size.x);
    map_data.append(size.y);
    map_data.append(chunk_size.x);
    map_data.append(chunk_size.y);
    // Dump chunk data
    for (Chunk chunk : chunks) {
        map_data.append(chunk.index);
        map_data.append_array(dump_chunk_data(chunk.index));
    }
    return map_data;
}

void RGMap::load_map_data(PoolIntArray map_data) {
    // Clean loaded data
    clean_map();
    // Reset size
    size.x = map_data[0];
    size.y = map_data[1];
    chunk_size.x = map_data[2];
    chunk_size.y = map_data[3];
    // Calculate number of chunks
    int chunks_number = (map_data.size()-4)/(chunk_size.x*chunk_size.y*NUM_CHUNK_ARRAYS+1);
    // Load chunks
    for (int i = 0; i < chunks_number; ++i) {
        // Get index
        PoolIntArray chunk_data;
        int start = 4 + i*(1+chunk_size.x*chunk_size.y*NUM_CHUNK_ARRAYS);
        // Add chunk data
        for (int k=0; k < chunk_size.x*chunk_size.y*NUM_CHUNK_ARRAYS; ++k) {
            int value = map_data[start + k + 1];
            chunk_data.append(value);
        }
        // Load chunk
        int index = map_data[start];
        load_chunk(index, chunk_data);
    }
}
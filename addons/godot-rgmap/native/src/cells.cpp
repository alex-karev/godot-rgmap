#include "rgmap.h"
using namespace godot;

// All functions related to cells

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
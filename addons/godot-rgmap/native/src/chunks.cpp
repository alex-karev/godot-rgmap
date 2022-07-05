#include "rgmap.h"
using namespace godot;

// All functions related to chunks

RGMap::Chunk& RGMap::get_chunk(int index) {
    return chunks[index];
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
    return chunks[index].loaded;
}
void RGMap::load_chunk(int index, PoolIntArray data) {
    // Trow out of bounds error
    ERR_FAIL_INDEX(index, size.x*size.y);
    int cells_number = chunk_size.x*chunk_size.y;
    Chunk& chunk = get_chunk(index);
    if (is_chunk_loaded(index)) {
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
        if (data.size() > 0) {
            for (int i=0; i < cells_number; ++i) {
                chunk.values.push_back(data[i]);
                chunk.memory.push_back(data[i+cells_number]);
            }
        } else {
            chunk.values.resize(cells_number, 0);
            chunk.memory.resize(cells_number, 0);
        }
        loaded_chunks.push_back(index);
        chunk.loaded = true;
        set_chunk_rendered(index, false);
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
    Chunk& chunk = chunks[index];
    chunk.values.clear();
    chunk.values.shrink_to_fit();
    chunk.memory.clear();
    chunk.memory.shrink_to_fit();
    chunk.loaded = false;
    loaded_chunks.erase(std::remove(loaded_chunks.begin(), loaded_chunks.end(), index), loaded_chunks.end());
    set_chunk_rendered(index, false);
    emit_signal("chunk_freed", index);
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
        set_chunk_rendered(index, false);
    }
}
bool RGMap::is_chunk_rendered(int index) {
    ERR_FAIL_INDEX_V(index, size.x*size.y, false);
    return chunks[index].rendered;
}
void RGMap::set_chunk_rendered(int index, bool value) {
    ERR_FAIL_INDEX(index, size.x*size.y);
    if (!is_chunk_rendered(index) && value) {
        rendered_chunks.push_back(index);
        chunks[index].rendered = true;
    }
    else if (is_chunk_rendered(index) && !value) {
        rendered_chunks.erase(std::remove(rendered_chunks.begin(), rendered_chunks.end(), index), rendered_chunks.end());
        chunks[index].rendered = false;
    }
        
}
PoolIntArray RGMap::get_loaded_chunks() {
    PoolIntArray loaded;
    for (int index : loaded_chunks) {
        loaded.append(index);
    }
    return loaded;
}
PoolIntArray RGMap::get_chunks_in_distance(Vector2 point, int distance){
    PoolIntArray indexes;
    int center_index = get_chunk_index(point);
    for (int x = -distance; x < distance+1; ++x) {
        for (int y = -distance; y < distance+1; ++y) {
            int index = center_index + x + y*size.x;
            if (index >= 0 && index < size.x*size.y) {
                indexes.append(index);
            }
        }
    }
    return indexes;
}

PoolIntArray RGMap::get_chunks_to_load(Vector2 player_position) {
    PoolIntArray to_load;
    PoolIntArray chunk_indexes = get_chunks_in_distance(player_position, load_distance);
    for (int i = 0; i < chunk_indexes.size(); ++i){
        if (!is_chunk_loaded(chunk_indexes[i])) {to_load.append(chunk_indexes[i]);}
    }
    return to_load;
}
PoolIntArray RGMap::get_chunks_to_free(Vector2 player_position) {
    PoolIntArray to_free;
    int center_index = get_chunk_index(player_position);
    Vector2 center_index_v2 = chunk_index_int_to_v2(center_index);
    for (int index : loaded_chunks) {
        Vector2 index_v2 = chunk_index_int_to_v2(index);
        if (index_v2.x < center_index_v2.x-load_distance || index_v2.y < center_index_v2.y-load_distance
        || index_v2.x > center_index_v2.x+load_distance || index_v2.y > center_index_v2.y+load_distance) {
            to_free.append(index);
        }
    }
    return to_free;
}
void RGMap::request_chunks_load(Vector2 player_position) {
    PoolIntArray to_load = get_chunks_to_load(player_position);
    emit_signal("chunks_load_requested", to_load);
    PoolIntArray to_free = get_chunks_to_free(player_position);
    emit_signal("chunks_free_requested", to_free);
}

PoolIntArray RGMap::get_rendered_chunks() {
    PoolIntArray rendered;
    for (int index : rendered_chunks) {
        rendered.append(index);
    }
    return rendered;
}

PoolIntArray RGMap::get_chunks_to_render(Vector2 player_position) {
    PoolIntArray to_render;
    PoolIntArray chunk_indexes = get_chunks_in_distance(player_position, render_distance);
    for (int i = 0; i < chunk_indexes.size(); ++i){
        if (is_chunk_loaded(chunk_indexes[i]) && !is_chunk_rendered(chunk_indexes[i])) {
            to_render.append(chunk_indexes[i]);
        }
    }
    return to_render;
}
PoolIntArray RGMap::get_chunks_to_hide(Vector2 player_position) {
    PoolIntArray to_hide;
    int center_index = get_chunk_index(player_position);
    Vector2 center_index_v2 = chunk_index_int_to_v2(center_index);
    for (int index : rendered_chunks) {
        Vector2 index_v2 = chunk_index_int_to_v2(index);
        if (index_v2.x < center_index_v2.x-render_distance || index_v2.y < center_index_v2.y-render_distance
        || index_v2.x > center_index_v2.x+render_distance || index_v2.y > center_index_v2.y+render_distance) {
            to_hide.append(index);
        }
    }
    return to_hide;
}

void RGMap::request_chunks_render(Vector2 player_position) {
    PoolIntArray to_render = get_chunks_to_render(player_position);
    emit_signal("chunks_render_requested", to_render);
    PoolIntArray to_hide = get_chunks_to_hide(player_position);
    emit_signal("chunks_hide_requested", to_hide);
}
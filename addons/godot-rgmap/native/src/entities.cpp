#include "rgmap.h"
using namespace godot;

// All functions related to entities

int RGMap::add_entity(Vector2 position, bool passability, bool transparency) {
    // Find entity id
    int id = 0;
    while (id < entities.size()) {
        if (entities[id].rewrite) { break; }
        id++;
    }
    // Create new entity if not exists
    if (id == entities.size()) {
        Entity new_entity;
        entities.push_back(new_entity);
    }
    // Set entity properties
    Entity& entity = entities[id];
    entity.position = position;
    entity.passable = passability;
    entity.transparent = transparency;
    entity.discovered = false;
    // Associate entity with chunk
    int chunk_index = get_chunk_index(position);
    Chunk& chunk = chunks[chunk_index];
    chunk.entities.push_back(id);
    return id;
}
void RGMap::remove_entity(int id) {
    ERR_FAIL_INDEX(id, entities.size());
    entities[id].rewrite = true;
    // Diassociate entity with chunk
    int chunk_index = get_chunk_index(entities[id].position);
    Chunk& chunk = chunks[chunk_index];
    chunk.entities.erase(std::remove(chunk.entities.begin(), chunk.entities.end(), id), chunk.entities.end());
}
void RGMap::move_entity(int id, Vector2 position) {
    ERR_FAIL_INDEX(id, entities.size());
    // Check if chunk is different
    int old_chunk_index = get_chunk_index(entities[id].position);
    int new_chunk_index = get_chunk_index(position);
    // Diassociate entity with old chunk and associate with new chunk
    if (old_chunk_index != new_chunk_index) {
        Chunk& old_chunk = chunks[old_chunk_index];
        old_chunk.entities.erase(std::remove(old_chunk.entities.begin(), old_chunk.entities.end(), id), old_chunk.entities.end());
        Chunk& new_chunk = chunks[new_chunk_index];
        new_chunk.entities.push_back(id);
    }
    // Change position
    entities[id].position = position;
}
void RGMap::set_entity_transparency(int id, bool value) {
    ERR_FAIL_INDEX(id, entities.size());
    entities[id].transparent = value;
}
void RGMap::set_entity_passability(int id, bool value) {
    ERR_FAIL_INDEX(id, entities.size());
    entities[id].passable = value;
}
void RGMap::set_entity_discovered(int id, bool value) {
    ERR_FAIL_INDEX(id, entities.size());
    entities[id].discovered = value;
}
bool RGMap::is_entity_visible(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), false);
    Vector2 position = get_entity_position(id);
    return is_visible(position);
}
bool RGMap::is_entity_transparent(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), true);
    return entities[id].transparent;
}
bool RGMap::is_entity_passable(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), true);
    return entities[id].passable;
}
bool RGMap::is_entity_discovered(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), false);
    return entities[id].discovered;
}
bool RGMap::is_entity_chunk_loaded(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), false);
    int chunk_index = get_chunk_index(entities[id].position);
    return is_chunk_loaded(chunk_index);
}
bool RGMap::is_entity_chunk_rendered(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), false);
    int chunk_index = get_chunk_index(entities[id].position);
    return is_chunk_rendered(chunk_index);
}
Vector2 RGMap::get_entity_position(int id) {
    ERR_FAIL_INDEX_V(id, entities.size(), Vector2(0,0));
    return entities[id].position;
}
PoolIntArray RGMap::get_entities_in_position(Vector2 position) {
    PoolIntArray ids;
    int chunk_index = get_chunk_index(position);
    Chunk& chunk = chunks[chunk_index];
    for (int id : chunk.entities) {
        Entity& entity = entities[id];
        if (!entity.rewrite && entity.position == position) {
            ids.append(id);
        }
    }
    return ids;
}
PoolIntArray RGMap::get_entities_in_rect(Rect2 rect) {
    PoolIntArray ids;
    std::vector<int> chunk_ids;
    for (int x = 0; x < floor(rect.size.x); ++x) {
        for (int y = 0; y < floor(rect.size.y); ++y) {
            Vector2 pos = rect.position.floor()+Vector2(x,y);
            int chunk_index = get_chunk_index(pos);
            if(std::find(chunk_ids.begin(), chunk_ids.end(), chunk_index) == chunk_ids.end()) {
                chunk_ids.push_back(chunk_index);
            }
        }
    }
    for (int chunk_index : chunk_ids) {
        Chunk& chunk = chunks[chunk_index];
        for (int id : chunk.entities) {
            Entity& entity = entities[id];
            if (rect.has_point(entity.position)) {
                ids.append(id);
            } 
        }
    }
    return ids;
}
PoolIntArray RGMap::get_entities_in_radius(Vector2 position, int radius) {
    PoolIntArray ids;
    Vector2 rect_position = position-Vector2(radius,radius);
    Vector2 rect_size = Vector2(radius*2+1,radius*2+1);
    Rect2 rect = Rect2(rect_position, rect_size);
    PoolIntArray in_rect = get_entities_in_rect(rect);
    for (int i = 0; i < in_rect.size(); ++i) {
        int id = in_rect[i];
        Entity& entity = entities[id];
        if (entity.position.distance_to(position) <= radius) {
            ids.append(id);
        }
    }
    return ids;
}
PoolIntArray RGMap::get_entities_in_chunk(int chunk_index) {
    PoolIntArray ids;
    Chunk& chunk = chunks[chunk_index];
    for (int id : chunk.entities) {
        ids.append(id);
    }
    return ids;
}
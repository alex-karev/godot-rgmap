---
title: /home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/entities.cpp

---

# /home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/entities.cpp






## Source code

```cpp
#include "rgmap.h"
using namespace godot;

// All functions related to entities

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
```


-------------------------------

Updated on 2022-06-29 at 17:56:25 +0300

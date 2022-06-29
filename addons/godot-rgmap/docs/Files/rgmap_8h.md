---
title: /home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/rgmap.h

---

# /home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/rgmap.h



## Namespaces

| Name           |
| -------------- |
| **[godot](Namespaces/namespacegodot.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[godot::RGMap](Classes/classgodot_1_1RGMap.md)** <br>Class for managing maps for roguelike.  |

## Defines

|                | Name           |
| -------------- | -------------- |
|  | **[_USE_MATH_DEFINES](Files/rgmap_8h.md#define--use-math-defines)**  |




## Macros Documentation

### define _USE_MATH_DEFINES

```cpp
#define _USE_MATH_DEFINES 
```


## Source code

```cpp
#ifndef RGMAP_H
#define RGMAP_H

#define _USE_MATH_DEFINES

#include <Godot.hpp>
#include <Node.hpp>
#include <Vector2.hpp>
#include <Array.hpp>
#include <AStar2D.hpp>
#include <Rect2.hpp>
#include <TileSet.hpp>
#include <Texture.hpp>
#include <ResourceLoader.hpp>
#include <cmath>
#include <vector>
#include <algorithm>

namespace godot {

class RGMap : public Reference {
    GODOT_CLASS(RGMap, Node)

    // Structure needed for RPAS algorithm
    struct CellAngles{
        float near;
        float center;
        float far;
    };

    // Structure that stores data about one type of tile
    struct RGTile {
        String name;
        String display_name;
        bool passable;
        bool transparent;
    };

    // Structure of one chunk
    struct Chunk {
        // Index of chunk
        int index = -1;
        // Flat arrays that contain all data about the cells
        std::vector<int> values;
        std::vector<int> memory;
        bool rendered = false;
    };

    // Structure of entity
    struct Entity {
        Vector2 position = Vector2(0,0);
        bool passability = true;
        bool transparency = true;
        bool memorized = false;
        bool rewrite = false;
    };

private:
    // All tiles in a game
    std::vector<RGTile> tiles;
    // Store all chunks
    std::vector<Chunk> chunks;
    // Epsilon for float error calculation
    const float FLOAT_EPSILON = 0.00001;
    // Visibility of cells within fov radius. Temporary variable
    std::vector<int> visibility;
    // Opaque obstacles for FOV. Temporary variable
    std::vector<int> fov_obstacles;
    // Current fov zone
    Rect2 fov_zone = Rect2(Vector2(0,0), Vector2(0,0));
    std::vector<Vector2> pathfinding_exception_allowed;
    std::vector<Vector2> pathfinding_exception_disallowed;
    // Number of Arrays stored in Chunk structure
    const int NUM_CHUNK_ARRAYS = 2;
    // Array with all registered entities
    std::vector<Entity> entities;

    // Functions for Restrictive Precise Angle Shadowcasting. More details in rpas.cpp
    PoolVector2Array rpas_visible_cells_in_quadrant_from(Vector2 center, Vector2 quad, int radius);
    PoolVector2Array rpas_visible_cells_in_octant_from(Vector2 center, Vector2 quad, int radius, bool is_vertical);
    Vector2 rpas_cell_at(Vector2 center, Vector2 quad, int step, int iteration, bool is_vertical);
    bool rpas_cell_in_radius(Vector2 center, Vector2 cell, int radius);
    bool rpas_cell_is_visible(CellAngles cell_angles, std::vector<CellAngles>& obstructions);
    void rpas_add_obstruction(std::vector<CellAngles> & obstructions, CellAngles new_obstruction);
    bool rpas_combine_obstructions(CellAngles &old_o, CellAngles &new_o);
    // Draw points based on 4-way symmetry (for Bresenham's ellipse algorithm)
    void draw_4_way_symmetry(int xc, int yc, int x, int y, int value, float start_angle, float end_angle);

    // Get loaded chunk
    Chunk& get_chunk(int index);
    // Get indexes of chunks forming a square grid with a given point in its center
    PoolIntArray get_chunks_in_distance(Vector2 point, int distance);

public:
    Vector2 chunk_size = Vector2(50,50);
    Vector2 size = Vector2(3,3);

    int load_distance = 1;

    int render_distance = 1;
    bool allow_diagonal_pathfinding = true;


    float RPAS_RADIUS_FUDGE = 1.0 / 3.0; 
    bool RPAS_NOT_VISIBLE_BLOCKS_VISION = true; 

    int RPAS_RESTRICTIVENESS = 1;
    bool RPAS_VISIBLE_ON_EQUAL = true; 

    // Note: these functions placed here to ease documentation generation with Doxygen
    // Tell me if you know a better way to do so


    PoolIntArray chunks_load_requested() {return PoolIntArray();}
    PoolIntArray chunks_free_requested() {return PoolIntArray();}
    PoolIntArray chunks_render_requested() {return PoolIntArray();}
    PoolIntArray chunks_hide_requested() {return PoolIntArray();}
    int chunk_loaded() {return 0;}
    int chunk_freed() {return 0;}


    static void _register_methods();
    RGMap();
    ~RGMap();
    void _init();

    // tiles.cpp


    void add_tile(String name, String display_name, bool passable, bool transparent);
    int get_tiles_count();
    int get_tile_index(String name);
    String get_tile_name(int index);
    String get_tile_display_name(int index);
    bool is_tile_passable(int index);
    bool is_tile_transparent(int index);

    Ref<TileSet> generate_tileset(String texture_path, String texture_format);

    // chunks.cpp

    
    int get_chunk_index(Vector2 position);
    Vector2 chunk_index_int_to_v2(int index);
    int chunk_index_v2_to_int(Vector2 index);
    bool is_chunk_in_bounds(int index);
    bool is_chunk_loaded(int index);
    void load_chunk(int index, PoolIntArray data = PoolIntArray());
    PoolIntArray dump_chunk_data(int index);
    void free_chunk(int index);
    void reset_chunk(int index);
    bool is_chunk_rendered(int index);
    void set_chunk_rendered(int index, bool value);
    PoolIntArray get_loaded_chunks();

    PoolIntArray get_chunks_to_load(Vector2 player_position);

    PoolIntArray get_chunks_to_free(Vector2 player_position);

    void request_chunks_update(Vector2 player_position);
    PoolIntArray get_rendered_chunks();

    PoolIntArray get_chunks_to_render(Vector2 player_position);

    PoolIntArray get_chunks_to_hide(Vector2 player_position);

    void request_chunks_render(Vector2 player_position);

    // cells.cpp


    int get_local_index(Vector2 position);
    int get_value(Vector2 position);
    String get_name(Vector2 position);
    String get_display_name(Vector2 position);
    bool is_in_bounds(Vector2 position);
    bool is_transparent(Vector2 position);
    bool is_passable(Vector2 position);
    bool is_visible(Vector2 position);
    bool is_memorized(Vector2 position);
    bool is_pathfinding_allowed(Vector2 position);
    void set_value(Vector2 position, int value);
    void set_visibility(Vector2 position, bool value);
    void set_memorized(Vector2 position, bool value);

    // view.cpp


    PoolVector2Array rpas_calc_visible_cells_from(Vector2 center, int radius);
    void calculate_fov(Vector2 view_position, int max_distance);
    void add_pathfinding_exception(Vector2 position, bool value);
    void remove_pathfinding_exception(Vector2 position);

    PoolVector2Array show_pathfinding_exceptions(bool exception_type);

    PoolVector2Array find_path(Vector2 start, Vector2 end, Rect2 pathfinding_zone, bool exclude_undiscovered=false);

    PoolVector2Array get_line(Vector2 start, Vector2 end, bool allow_diagonal = true);
    Vector2 raycast_vision(Vector2 start, Vector2 end);
    Vector2 raycast_path(Vector2 start, Vector2 end);

    bool visibility_between(Vector2 start, Vector2 end, int max_distance);

    // editing.cpp


    void clean_map();
    void place_map(RGMap* another_map, Vector2 start);
    void draw_line(Vector2 start, Vector2 end, int value, bool allow_diagonal = true);
    void draw_rect(Rect2 rect, int value);
    void fill_rect(Rect2 rect, int value);

    void draw_ellipse(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value, bool allow_diagonal = true);
    void fill_ellipse(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value);
    void draw_circle(Vector2 center, float radius, int value, bool allow_diagonal = true);
    void fill_circle(Vector2 center, float radius, int value);
    void draw_arc(Vector2 center, float radius, float start_angle, float end_angle, int value, bool allow_diagonal = true);
    void fill_arc(Vector2 center, float radius, float start_angle, float end_angle, int value);

    // entities.cpp


    int add_entity(Vector2 position, bool passability, bool transparency);
    void remove_entity(int id);
    void move_entity(int id, Vector2 position);
    void set_entity_transparency(int id, bool value);
    void set_entity_passability(int id, bool value);
    void set_entity_memorized(int id, bool value);
    bool is_entity_visible(int id);
    bool is_entity_transparent(int id);
    bool is_entity_passable(int id);
    bool is_entity_memorized(int id);
    bool is_entity_chunk_loaded(int id);
    bool is_entity_chunk_rendered(int id);
    Vector2 get_entity_position(int id);
    PoolIntArray get_entities_in_position(Vector2 position);
    PoolIntArray get_entities_in_rect(Rect2 rect);
    PoolIntArray get_entities_in_radius(Vector2 position, int radius);
    PoolIntArray get_entities_in_chunk(int chunk_index);


    PoolIntArray dump_map_data();
    void load_map_data(PoolIntArray map_data);
};

}

#endif
```


-------------------------------

Updated on 2022-06-29 at 17:56:25 +0300

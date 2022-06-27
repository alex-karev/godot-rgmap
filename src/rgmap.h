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

//! Class for managing maps for roguelike
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

public:
    //! Size of one chunk (Default: 50x50)
    Vector2 chunk_size = Vector2(50,50);
    //! Size of the whole map in chunks (Default: 3x3)
    Vector2 size = Vector2(3,3);
    //! Number of chunks loaded around the player 
    /*! 
    Excluding the chunk where player stands
    Default: 1 (3x3 grid)
    */
    int render_distance = 1;
    //! Allow/Disallow diagonal pathfinding
    bool allow_diagonal_pathfinding = true;

    /** @name FOV
    * Variables related to FOV calculation using RPAS algorithm
    */
    ///@{

    //! How smooth the edges of the vision bubble are. Between 0 and 1.
    float RPAS_RADIUS_FUDGE = 1.0 / 3.0; 
    //! If this is false, some cells will unexpectedly be visible
    bool RPAS_NOT_VISIBLE_BLOCKS_VISION = true; 
    //! Determines how restrictive the algorithm is
    /*!
 	0 - if you have a line to the near, center, or far, it will return as visible \n 
	1 - if you have a line to the center and at least one other corner it will return as visible \n 
	2 - if you have a line to all the near, center, and far, it will return as visible
    */ 
    int RPAS_RESTRICTIVENESS = 1;
    //! If false, an obstruction will obstruct its endpoints
    bool RPAS_VISIBLE_ON_EQUAL = true; 
    ///@}

    // Note: these functions placed here to ease documentation generation with Doxygen
    // Tell me if you know a better way to do so
    /** @name Signals */
    ///@{

    //! **Signal.** Emited when chunk needs to be loaded. Emited on calling request_chunks_update function
    PoolIntArray chunks_load_requested() {return PoolIntArray();}
    //! **Signal.** Emited when chunk needs to be freed. Emited on calling request_chunks_update function
    PoolIntArray chunks_free_requested() {return PoolIntArray();}
    //! **Signal.** Emited when is loaded for the first time. Emited on calling load_chunk function
    int chunk_loaded() {return 0;}
    //! **Signal.** Emited when chunk is freed from memory. Emited on calling free_chunk function
    int chunk_freed() {return 0;}
    ///@}

    /** @name Standard methods */
    ///@{

    static void _register_methods();
    RGMap();
    ~RGMap();
    void _init();
    ///@}

    //! Free all chunks and forget pathfinding exceptions
    void clean_map();

    /** @name Tiles */
    ///@{

    //! Add new tile
    void add_tile(String name, String display_name, bool passable, bool transparent);
    //! Get number of tiles
    int get_tiles_count();
    //! Get tile index by name
    int get_tile_index(String name);
    //! Get tile name (unique)
    String get_tile_name(int index);
    //! Get tile display name
    String get_tile_display_name(int index);
    //! Check if tile is passable
    bool is_tile_passable(int index);
    //! Check if tile is transparent
    bool is_tile_transparent(int index);
    //! Generate Tileset for using with 2d Tilemap
    /*!
    @param texture_path A directory within the project where textures are stored (e.g "res://Textures/")
    @param texture_format A format of textures (e.g ".png")
    */
    Ref<TileSet> generate_tileset(String texture_path, String texture_format);
    ///@{

    /** @name Chunks */
    ///@{
    
    //! Get index of chunk which contains a given position
    int get_chunk_index(Vector2 position);
    //! Convert index of chunk from int to Vector2 format
    Vector2 chunk_index_int_to_v2(int index);
    //! Convert index of chunk from Vector2 to int format
    int chunk_index_v2_to_int(Vector2 index);
    //! Check if chunk is in bounds
    bool is_chunk_in_bounds(int index);
    //! Check if chunk is loaded
    bool is_chunk_loaded(int index);
    //! Load saved chunk to memory or generate a new chunk. "data" argument is optional
    void load_chunk(int index, PoolIntArray data = PoolIntArray());
    //! Returns all cell data for chunk as PoolIntArray
    PoolIntArray dump_chunk_data(int index);
    //! Free chunk from memory
    void free_chunk(int index);
    //! Clear all cell data in chunk
    void reset_chunk(int index);
    //! Get overall number of chunks
    int count_chunks();
    //! Get number of loaded chunks
    int count_loaded_chunks();
    //! Get ids of loaded chunks
    PoolIntArray get_loaded_chunks();
    //! Get ids of chunks around player that needs to be loaded 
    /*!
    @param player_position Vector2 position of the player
    Uses render_distance parameter to define the radius
    Skips chunks that were already loaded
    */
    PoolIntArray get_chunks_to_load(Vector2 player_position);
    //! Get ids of chunks that are loaded, but not needed anymore because player is too far
    /*!
    @param player_position Vector2 position of the player
    Uses render_distance parameter to define the radius
    */
    PoolIntArray get_chunks_to_free(Vector2 player_position);
    //! Request chunk load/unload depending on player_position and render_distance
    /*! Emits several "chunk_load_requested" and "chunk_free_requested" signals
    Will produce the same result until chunks will be loaded/freed from other script
    Does nothing if all needed chunks are loaded and all unneeded chunks are freed
    @param player_position Vector2 position of the player
    Uses render_distance parameter to define the radius
    */
    void request_chunks_update(Vector2 player_position);
    ///@}


    /** @name Cells */
    ///@{

    //! Get local index of cell within a chunk
    int get_local_index(Vector2 position);
    //! Get value of cell
    int get_value(Vector2 position);
    //! Get name of cell
    String get_name(Vector2 position);
    //! Get display name of cell
    String get_display_name(Vector2 position);
    //! Check if cell is in bounds
    bool is_in_bounds(Vector2 position);
    //! Check if cell is transparent
    bool is_transparent(Vector2 position);
    //! Check if cell is passable
    bool is_passable(Vector2 position);
    //! Check if cell is visible
    bool is_visible(Vector2 position);
    //! Check if cell is memorized
    bool is_memorized(Vector2 position);
    //! Check if pathfinding on this cell is allowed
    bool is_pathfinding_allowed(Vector2 position);
    //! Set value of cell
    void set_value(Vector2 position, int value);
    //! Set visibility of cell
    void set_visibility(Vector2 position, bool value);
    //! Set memory state of cell
    void set_memorized(Vector2 position, bool value);
    ///@}

    /** @name View and pathfinding */
    ///@{

    //! Get list of cells visible from position within radius using RPAS algorithm
    PoolVector2Array rpas_calc_visible_cells_from(Vector2 center, int radius);
    //! Calculate visibility from given position and distance
    void calculate_fov(Vector2 view_position, int max_distance);
    //! Allow/disallow patfinding for this cell ignoring passability
    void add_pathfinding_exception(Vector2 position, bool value);
    //! Remove all pathfinding exceptions for this cell if they exist
    void remove_pathfinding_exception(Vector2 position);
    //! Show all pathfinding exceptions of a type
    /*!
    @param exception_type true for allowed cells, false for disallowed cells
    */
    PoolVector2Array show_pathfinding_exceptions(bool exception_type);
    //! Find path from start to end using A* algorithm
    /*!
    Returns PoolVector2Array
    @param start Start point
    @param end Target point
    @param pathfinding_zone Rect2 zone where pathfinding is calculated
    */
    PoolVector2Array find_path(Vector2 start, Vector2 end, Rect2 pathfinding_zone);
    //! Get a set of points in Bresenham's line
    /*! Based on Python implementation from here: http://www.roguebasin.com/index.php/Bresenham%27s_Line_Algorithm */
    PoolVector2Array get_line(Vector2 start, Vector2 end, bool allow_diagonal = true);
    //! Cast ray from start to end and return position where vision is blocked by an obstacle
    Vector2 raycast_vision(Vector2 start, Vector2 end);
    //! Cast ray from start to end and return position where path is blocked by an obstacle
    Vector2 raycast_path(Vector2 start, Vector2 end);
    //! Check if end point is visisble from start point
    /*!
    @param start Start point
    @param end Target point
    @param max_distance Maximum distance at which points are visible
    */
    bool visibility_between(Vector2 start, Vector2 end, int max_distance);
    ///@}

    /** @name Editing*/
    ///@{

    //! Place another map inside this map
    void place_map(RGMap* another_map, Vector2 start);
    //! Draw straight line using Bresenham's line algorithm
    void draw_line(Vector2 start, Vector2 end, int value, bool allow_diagonal = true);
    //! Draw rect borders
    void draw_rect(Rect2 rect, int value);
    //! Fill rect
    void fill_rect(Rect2 rect, int value);
    //! Draw ellipse using Bresenham's midpoint algorithm
    /*! Tweaked version of code from here: https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/ */
    void draw_ellipse(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value, bool allow_diagonal = true);
    //! Fill ellipse
    void fill_ellipse(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value);
    //! Draw circle
    void draw_circle(Vector2 center, float radius, int value, bool allow_diagonal = true);
    //! Fill circle
    void fill_circle(Vector2 center, float radius, int value);
    //! Draw arc
    void draw_arc(Vector2 center, float radius, float start_angle, float end_angle, int value, bool allow_diagonal = true);
    //! Fill arc
    void fill_arc(Vector2 center, float radius, float start_angle, float end_angle, int value);
    ///@}

    /** @name Entities*/
    ///@{

    //! Add new entity to the map. Returns id given to a new entity
    int add_entity(Vector2 position, bool passability, bool transparency);
    //! Remove entity from memory. The id of this entity will also be given to a new entity
    void remove_entity(int id);
    //! Move entity to a new position
    void move_entity(int id, Vector2 position);
    //! Change entity transparency
    void set_entity_transparency(int id, bool value);
    //! Change entity passability
    void set_entity_passability(int id, bool value);
    //! Change memory status of entity
    void set_entity_memorized(int id, bool value);
    //! Check if entity is visible
    bool is_entity_visible(int id);
    //! Check if entity is transparent;
    bool is_entity_transparent(int id);
    //! Check if entity is passable
    bool is_entity_passable(int id);
    //! Check if entity is memorized
    bool is_entity_memorized(int id);
    //! Check if entity is on loaded chunk
    bool is_entity_chunk_loaded(int id);
    //! Get position of the entity
    Vector2 get_entity_position(int id);
    //! Find ids of all entities in position
    PoolIntArray get_entities_in_position(Vector2 position);
    //! Find ids of all entities in rect
    PoolIntArray get_entities_in_rect(Rect2 rect);
    //! Find ids of all entities in radius
    PoolIntArray get_entities_in_radius(Vector2 position, int radius);
    //! Find ids of all entities in chunk
    PoolIntArray get_entities_in_chunk(int chunk_index);
    ///@}

    /** @name Saving and Loading*/
    ///@{

    //! Save map data
    PoolIntArray dump_map_data();
    //! Load map data
    void load_map_data(PoolIntArray map_data);
    ///@}
};

}

#endif

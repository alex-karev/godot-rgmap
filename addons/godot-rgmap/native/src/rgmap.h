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
#include <ShaderMaterial.hpp>
#include <Color.hpp>
#include <Dictionary.hpp>
#include <cmath>
#include <vector>
#include <algorithm>

namespace godot {
/*! @page rgmap_api RGMap Class API
    Signal:
    - @ref Signals

    Properties:
    - @ref Map
    - @ref FOV

    Functions:
    - @ref Tiles
    - @ref Chunks
    - @ref Cells
    - @ref View_Pathfinding
    - @ref Editing
    - @ref Entities
    - @ref Save_Load
*/

//! Class for managing maps for roguelike
class RGMap : public Node {
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
        bool passable = false;
        bool transparent = false;
        Dictionary custom_properties;
        int z_index = 0;
        Ref<Texture> texture;
        Ref<Texture> normal_map;
        Vector2 texture_offset = Vector2(0,0);
        Ref<ShaderMaterial> material;
        Color modulate = Color(1.0,1.0,1.0);
    };

    // Structure of one chunk
    struct Chunk {
        // Flat arrays that contain all data about the cells
        std::vector<int> values;
        std::vector<int> memory;
        std::vector<int> entities;
        bool loaded = false;
        bool rendered = false;
    };

    // Structure of entity
    struct Entity {
        Vector2 position = Vector2(0,0);
        bool passable = true;
        bool transparent = true;
        bool discovered = false;
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
    // Ids of loaded chunks
    std::vector<int> loaded_chunks;
    // Ids of rendered chunks
    std::vector<int> rendered_chunks;
    // Dictionary with custom tile property names as keys and their default values
    Dictionary custom_tile_properties;

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

    // Get a set of points in Bresenham's line
    PoolVector2Array get_line_bresenham(Vector2 start, Vector2 end, bool allow_diagonal);
    // Draw ellipse using Bresenham's midpoint algorithm
    void draw_ellipse_bresenham(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value, bool allow_diagonal);
    // Get loaded chunk
    Chunk& get_chunk(int index);
    // Find path from start to end using A* algorithm
    PoolVector2Array _find_path(Vector2 start, Vector2 end, Rect2 pathfinding_zone, bool exclude_undiscovered=false);

public:
    /** @name Map Properties
    * @anchor Map
    */
    ///@{

    //! Size of one chunk (Default: 50x50)
    Vector2 chunk_size = Vector2(50,50);
    //! Size of the whole map in chunks (Default: 3x3)
    Vector2 size = Vector2(3,3);
    //! Number of chunks loaded around the player 
    /*! 
    Excluding the chunk where player stands
    Default: 1 (3x3 grid)
    */
    int load_distance = 1;
    //! Number of chunks rendered around the player 
    /*! 
    Excluding the chunk where player stands
    Default: 1 (3x3 grid)
    */
    int render_distance = 1;
    //! Allow/Disallow diagonal pathfinding
    bool allow_diagonal_pathfinding = true;
    ///@}

    /** @name FOV Properties
    * @anchor FOV
    */
    ///@{

    //! Radius in which cells are visible for player
    int fov_radius = 15;
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
    /** @name Signals 
    * @anchor Signals
    */
    ///@{

    //! **Signal.** Emited when chunks need to be loaded. Emited on calling request_chunks_load function
    PoolIntArray chunks_load_requested() {return PoolIntArray();}
    //! **Signal.** Emited when chunks need to be freed. Emited on calling request_chunks_load function
    PoolIntArray chunks_free_requested() {return PoolIntArray();}
    //! **Signal.** Emited when chunks need to be rendered. Emited on calling request_chunks_render function
    PoolIntArray chunks_render_requested() {return PoolIntArray();}
    //! **Signal.** Emited when rendered chunks need to be hidden. Emited on calling request_chunks_render function
    PoolIntArray chunks_hide_requested() {return PoolIntArray();}
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
    void _ready();
    ///@}

    // tiles.cpp
    /** @name Tiles 
    * @anchor Tiles
    */
    ///@{

    //! Add new tile. Returns unique tile index
    /*!
    @param name Unique name of the tile. Needed for searching tiles by name
    @param display_name Name that will be shown to the player. Can be a duplicate
    */
    int add_tile(String name, String display_name);
    //! Set transparency of the tile
    void set_tile_transparency(int index, bool value);
    //! Set passability of the tile
    void set_tile_passability(int index, bool value);
    //! Add custom property field for all tiles
    /*!
    @param property_name Name of new property field that will be added to all tiles
    @param default_value Default value for that property. Can be any type
    */
    void add_tile_property(String property_name, Variant default_value);
    //! Set tile's drawing index
    void set_tile_z_index(int index, int z_index);
    //! Set tile's texture offset
    void set_tile_texture_offset(int index, Vector2 offset);
    //! Set tile's texture
    void set_tile_texture(int index, Ref<Texture> texture);
    //! Set tile's normal map
    void set_tile_normal_map(int index, Ref<Texture> texture);
    //! Set tile's material
    void set_tile_material(int index, Ref<Material> material);
    //! Set tile's modulation color
    void set_tile_modulate(int index, Color color);
    //! Set value of custom property for specified tile
    void set_tile_property(int index, String property_name, Variant new_value);
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
    //! Get tile's drawing index
    int get_tile_z_index(int index);
    //! Get tile's texture offset
    Vector2 get_tile_texture_offset(int index);
    //! Get tile's texture
    Ref<Texture> get_tile_texture(int index);
    //! Get tile's normal map
    Ref<Texture> get_tile_normal_map(int index);
    //! Get tile's material
    Ref<Material> get_tile_material(int index);
    //! Get tile's modulation color
    Color get_tile_modulate(int index);
    //! Get value of custom tile property
    Variant get_tile_property(int index, String property_name);
    //! Generate Tileset for using with 2d Tilemap
    Ref<TileSet> generate_tileset();
    ///@{

    // chunks.cpp
    /** @name Chunks 
    * @anchor Chunks
    */
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
    //! Check if chunk is rendered
    bool is_chunk_rendered(int index);
    //! Set rendering status of chunk
    void set_chunk_rendered(int index, bool value);
    //! Get ids of loaded chunks
    PoolIntArray get_loaded_chunks();
    //! Get indexes of chunks forming a square grid with a given point in its center
    PoolIntArray get_chunks_in_distance(Vector2 point, int distance);
    //! Get ids of chunks around player that needs to be loaded 
    /*!
    @param player_position Vector2 position of the player
    Uses load_distance parameter to define the radius
    Skips chunks that were already loaded
    */
    PoolIntArray get_chunks_to_load(Vector2 player_position);
    //! Get ids of chunks that are loaded, but not needed anymore because player is too far
    /*!
    @param player_position Vector2 position of the player
    Uses load_distance parameter to define the radius
    */
    PoolIntArray get_chunks_to_free(Vector2 player_position);
    //! Request chunk load/unload depending on player_position and load_distance
    /*! Emits "chunks_load_requested" and "chunks_free_requested" signals
    Will produce the same result until chunks will be loaded/freed from other script
    Does nothing if all needed chunks are loaded and all unneeded chunks are freed
    @param player_position Vector2 position of the player
    Uses load_distance parameter to define the radius
    */
    void request_chunks_load(Vector2 player_position);
    //! Get ids of rendered chunks
    PoolIntArray get_rendered_chunks();
    //! Get ids of chunks around player that needs to be rendered
    /*!
    @param player_position Vector2 position of the player
    Uses render_distance parameter to define the radius
    Skips chunks that were already rendered
    */
    PoolIntArray get_chunks_to_render(Vector2 player_position);
    //! Get ids of chunks that are rendered, but not needed anymore because player is too far
    /*!
    @param player_position Vector2 position of the player
    Uses render_distance parameter to define the radius
    */
    PoolIntArray get_chunks_to_hide(Vector2 player_position);
    //! Request chunk render/hide depending on player_position and render_distance
    /*! Emits "chunks_render_requested" and "chunks_hide_requested" signals
    Will produce the same result until chunks will be rendered/hidden from other script
    Does nothing if all needed chunks are rendered and all unneeded chunks are hidden
    @param player_position Vector2 position of the player
    Uses render_distance parameter to define the radius
    */
    void request_chunks_render(Vector2 player_position);
    ///@}

    // cells.cpp
    /** @name Cells 
    * @anchor Cells
    */
    ///@{

    //! Get local index of cell within a chunk
    int get_local_index(Vector2 position);
    //! Get value of cell
    int get_value(Vector2 position);
    //! Get name of cell
    String get_name(Vector2 position);
    //! Get display name of cell
    String get_display_name(Vector2 position);
    //! Get custom property value of cell's tile
    Variant get_property(Vector2 position, String property_name);
    //! Check if cell is in bounds
    bool is_in_bounds(Vector2 position);
    //! Check if cell is transparent
    bool is_transparent(Vector2 position);
    //! Check if cell is passable
    bool is_passable(Vector2 position);
    //! Check if cell is visible
    bool is_visible(Vector2 position);
    //! Check if cell is discovered
    bool is_discovered(Vector2 position);
    //! Set value of cell
    void set_value(Vector2 position, int value);
    //! Set visibility of cell
    void set_visibility(Vector2 position, bool value);
    //! Set cell discovered/undiscovered
    void set_discovered(Vector2 position, bool value);
    ///@}

    // view.cpp
    /** @name View and pathfinding 
    * @anchor View_Pathfinding
    */
    ///@{

    //! Get list of cells visible from position within radius using RPAS algorithm
    PoolVector2Array rpas_calc_visible_cells_from(Vector2 center, int radius);
    //! Calculate visibility from given position
    void calculate_fov(Vector2 view_position);
    //! Allow/disallow patfinding for this cell ignoring passability
    void add_pathfinding_exception(Vector2 position, bool value);
    //! Remove all pathfinding exceptions for this cell if they exist
    void remove_pathfinding_exception(Vector2 position);
    //! Show all pathfinding exceptions of a type
    /*!
    @param exception_type true for allowed cells, false for disallowed cells
    */
    PoolVector2Array show_pathfinding_exceptions(bool exception_type);
    //! Check if pathfinding on this cell is allowed
    bool is_pathfinding_allowed(Vector2 position);
    //! Find path from start to end using A* algorithm
    /*!
    Returns PoolVector2Array
    @param start Start point
    @param end Target point
    @param pathfinding_zone Rect2 zone where pathfinding is calculated
    */
    PoolVector2Array find_path(Vector2 start, Vector2 end, Rect2 pathfinding_zone);
    //! Find path from start to end using A* algorithm including only discovered cells
    /*!
    Returns PoolVector2Array
    @param start Start point
    @param end Target point
    @param pathfinding_zone Rect2 zone where pathfinding is calculated
    */
    PoolVector2Array find_discovered_path(Vector2 start, Vector2 end, Rect2 pathfinding_zone);
    //! Get a set of points in Bresenham's line
    /*! Based on Python implementation from here: http://www.roguebasin.com/index.php/Bresenham%27s_Line_Algorithm */
    PoolVector2Array get_line(Vector2 start, Vector2 end);
    //! Get a set of points in Bresenham's line (No diagonals allowed)
    PoolVector2Array get_line_orthogonal(Vector2 start, Vector2 end);
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

    // editing.cpp
    /** @name Editing
    * @anchor Editing
    */
    ///@{

    //! Free all chunks and forget pathfinding exceptions
    void clean_map();
    //! Change size and chunk size of the map.
    void resize_map(Vector2 new_size, Vector2 new_chunk_size);
    //! Place another map inside this map
    void place_map(RGMap* another_map, Vector2 start);
    //! Draw straight line using Bresenham's line algorithm
    void draw_line(Vector2 start, Vector2 end, int value);
    //! Draw orthogonal straight line (No diagonals allowed)
    void draw_line_orthogonal(Vector2 start, Vector2 end, int value);
    //! Draw rect borders
    void draw_rect(Rect2 rect, int value);
    //! Fill rect
    void fill_rect(Rect2 rect, int value);
    //! Draw ellipse using Bresenham's midpoint algorithm
    /*! Tweaked version of code from here: https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/ */
    void draw_ellipse(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value);
    //! Draw orthogonal ellipse (No diagonals allowed)
    void draw_ellipse_orthogonal(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value);
    //! Fill ellipse
    void fill_ellipse(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value);
    //! Draw circle
    void draw_circle(Vector2 center, float radius, int value);
    //! Draw circle (No diagonals allowed)
    void draw_circle_orthogonal(Vector2 center, float radius, int value);
    //! Fill circle
    void fill_circle(Vector2 center, float radius, int value);
    //! Draw arc
    void draw_arc(Vector2 center, float radius, float start_angle, float end_angle, int value);
    //! Draw orthogonal arc (No diagonals allowed)
    void draw_arc_orthogonal(Vector2 center, float radius, float start_angle, float end_angle, int value);
    //! Fill arc
    void fill_arc(Vector2 center, float radius, float start_angle, float end_angle, int value);
    ///@}

    // entities.cpp
    /** @name Entities
    * @anchor Entities
    */
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
    void set_entity_discovered(int id, bool value);
    //! Check if entity is visible
    bool is_entity_visible(int id);
    //! Check if entity is transparent;
    bool is_entity_transparent(int id);
    //! Check if entity is passable
    bool is_entity_passable(int id);
    //! Check if entity is discovered
    bool is_entity_discovered(int id);
    //! Check if entity is on loaded chunk
    bool is_entity_chunk_loaded(int id);
    //! Check if entity is on rendered chunk
    bool is_entity_chunk_rendered(int id);
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

    /** @name Saving and Loading
    * @anchor Save_Load
    */
    ///@{

    //! Save map data
    PoolIntArray dump_map_data();
    //! Load map data
    void load_map_data(PoolIntArray map_data);
    ///@}
};

}

#endif

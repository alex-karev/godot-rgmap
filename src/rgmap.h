#ifndef RGMAP_H
#define RGMAP_H

#define _USE_MATH_DEFINES

#include <Godot.hpp>
#include <Reference.hpp>
#include <Vector2.hpp>
#include <Array.hpp>
#include <AStar2D.hpp>
#include <Rect2.hpp>
#include <cmath>
#include <vector>

#include "rgtileset.h"

namespace godot {

//! Class for managing maps for roguelike
class RGMap : public Reference {
    GODOT_CLASS(RGMap, Reference)

    // Structure needed for RPAS algorithm
    struct CellAngles{
        float near;
        float center;
        float far;
    };

private:
    Ref<AStar2D> astar;
    const float FLOAT_EPSILON = 0.00001;
    
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
    // Generate astar system based on current size and values
    void generate_astar();
    // Clean map data (used initialization and loading)
    void clean_map_data();

public:
    //! Size of the matrix
    Vector2 size;
    //! Allow/Disallow diagonal pathfinding
    bool allowDiagonalPathfinding = true;
    //! RGTileset with information about all tiles
    RGTileset* tileset;
    
    /** @name Matrices
    * Flat arrays that contain all data about the cells
    */

    ///@{
    PoolIntArray values;
    PoolIntArray visibility;
    PoolIntArray memory;
    ///@}

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

    /** @name Standard methods */
    ///@{

    static void _register_methods();
    RGMap();
    ~RGMap();
    void _init();
    ///@}

    //! Fill all cells with 0s using a predefined tileset
    void initialize(RGTileset* _tileset);

    /** @name Data getters */
    ///@{

    //! Get index of cell by Vector2 position
    int get_index(Vector2 position);
    //! Get Vector2 position of cell by index
    Vector2 get_position(int index);
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
    ///@}

    /** @name Data setters */
    ///@{
        
    //! Set value of cell
    void set_value(Vector2 position, int value);
    //! Set visibility of cell
    void set_visibility(Vector2 position, bool value);
    //! Set memory state of cell
    void set_memorized(Vector2 position, bool value);
    //! Allow/disallow pathfinding through this position
    void set_pathfinding(Vector2 position, bool value);
    ///@}

    /** @name View and pathfinding */
    ///@{

    //! Get list of cells visible from position within radius using RPAS algorithm
    PoolVector2Array rpas_calc_visible_cells_from(Vector2 center, int radius);
    //! Calculate visibility from given position and distance
    void calculate_fov(Vector2 view_position, int max_distance);
    //! Find path from start to end using A* algorithm. Returns Array of Vector2 points
    PoolVector2Array find_path(Vector2 start, Vector2 end);
    //! Get a set of points in Bresenham's line
    /*! Based on Python implementation from here: http://www.roguebasin.com/index.php/Bresenham%27s_Line_Algorithm */
    PoolVector2Array get_line(Vector2 start, Vector2 end, bool allow_diagonal = true);
    //! Cast ray from start to end and return position where vision is blocked by an obstacle
    Vector2 raycast_vision(Vector2 start, Vector2 end);
    //! Cast ray from start to end and return position where path is blocked by an obstacle
    Vector2 raycast_path(Vector2 start, Vector2 end);
    //! Check if end point is visisble from start point
    bool visibility_between(Vector2 start, Vector2 end);
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

    /** @name Saving and Loading*/
    ///@{

    //! Save map data
    PoolIntArray save_map_data();
    //! Load map data
    void load_map_data(PoolIntArray map_data);
    ///@}
};

}

#endif

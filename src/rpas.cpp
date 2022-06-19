/*
    Restrictive Precise Angle Shadowcasting implementation
    ---
    This is a C++ translation of original Python code from here: 
        https://github.com/MoyTW/roguebasin_rpas
    The code was also adapted and optimised for Godot Engine and uses 
    functions and data types from godot namespace
    ---
 	The MIT License (MIT)
	
	Copyright (c) 2013 Travis Moy
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/
#include "rgmap.h"
using namespace godot;

PoolVector2Array RGMap::rpas_calc_visible_cells_from(Vector2 center, int radius) {
    PoolVector2Array cells = rpas_visible_cells_in_quadrant_from(center, Vector2(1, 1), radius);
    cells.append_array(rpas_visible_cells_in_quadrant_from(center, Vector2(1, -1), radius));
    cells.append_array(rpas_visible_cells_in_quadrant_from(center, Vector2(-1, -1), radius));
    cells.append_array(rpas_visible_cells_in_quadrant_from(center, Vector2(-1, 1), radius));
	cells.append(center);
	return cells;
}
PoolVector2Array RGMap::rpas_visible_cells_in_quadrant_from(Vector2 center, Vector2 quad, int radius) {
	PoolVector2Array cells = rpas_visible_cells_in_octant_from(center, quad, radius, true);
	cells.append_array(rpas_visible_cells_in_octant_from(center, quad, radius, false));
	return cells;
}

// Utilizes the NOT_VISIBLE_BLOCKS_VISION variable.
PoolVector2Array RGMap::rpas_visible_cells_in_octant_from(Vector2 center, Vector2 quad, int radius, bool is_vertical) {
	PoolVector2Array visible_cells;
    int iteration = 1;
	std::vector<CellAngles> obstructions;
    /* End conditions:
	iteration > radius
	Full obstruction coverage (indicated by one object in the obstruction list covering the full angle from 0 to 1) */
    while (iteration <= radius) {
        if (obstructions.size() > 0 && obstructions[0].near == 0.0 && obstructions[0].far == 1.0) {
            break;
        }
        int num_cells_in_row = iteration + 1;
	    float angle_allocation = 1.0 / float(num_cells_in_row);
	    // Start at the center (vertical or horizontal line) and step outwards
	    for (int step = 0; step < iteration + 1; ++step) {
            Vector2 cell = rpas_cell_at(center, quad, step, iteration, is_vertical);
            if (rpas_cell_in_radius(center, cell, radius)) {
	            CellAngles cell_angles;
                cell_angles.near = float(step) * angle_allocation;
                cell_angles.center = (float(step)+0.5) * angle_allocation;
                cell_angles.far = float(step + 1) * angle_allocation;
                if (rpas_cell_is_visible(cell_angles, obstructions)) {
                    if (is_in_bounds(cell)) {
                        visible_cells.append(cell);
                    }
                    if (!is_in_bounds(cell) || !is_transparent(cell)) {
                        rpas_add_obstruction(obstructions, cell_angles);
                    }
                } else if (RPAS_NOT_VISIBLE_BLOCKS_VISION) {
                        rpas_add_obstruction(obstructions, cell_angles);
                }
            }
        }
        iteration += 1;
    }
    return visible_cells;
}	        

// Returns a cell Vector2.
Vector2 RGMap::rpas_cell_at(Vector2 center, Vector2 quad, int step, int iteration, bool is_vertical) {
	Vector2 cell;
    if (is_vertical) {
        cell = Vector2(center.x + step * quad.x, center.y + iteration * quad.y);
    } else {
        cell = Vector2(center.x + iteration * quad.x, center.y + step * quad.y);
    }
	return cell;
}

// Returns True/False.
bool RGMap::rpas_cell_in_radius(Vector2 center, Vector2 cell, int radius) {
	float cell_distance = sqrt((center.x - cell.x) * (center.x - cell.x) + 
        (center.y - cell.y) * (center.y - cell.y));
    return cell_distance <= float(radius) + RPAS_RADIUS_FUDGE;
}


// Returns True/False. Utilizes the VISIBLE_ON_EQUAL and RESTRICTIVENESS variables.
bool RGMap::rpas_cell_is_visible(CellAngles cell_angles, std::vector<CellAngles> &obstructions) {
	bool near_visible = true;
	bool center_visible = true;
	bool far_visible = true;
    for (CellAngles obstruction : obstructions) {
	    if (RPAS_VISIBLE_ON_EQUAL) {
	        if (obstruction.near < cell_angles.near && cell_angles.near < obstruction.far) {
                near_visible = false;
            }
            if (obstruction.near < cell_angles.center && cell_angles.center < obstruction.far) {
	             center_visible = false;
            }
	        if (obstruction.near < cell_angles.far && cell_angles.far < obstruction.far) {
	             far_visible = false;
            }
        }
	    else {
	        if (obstruction.near <= cell_angles.near && cell_angles.near <= obstruction.far) {
                near_visible = false;
            }
	        if (obstruction.near <= cell_angles.center && cell_angles.center <= obstruction.far) {
                center_visible = false;
            }
	        if (obstruction.near <= cell_angles.far && cell_angles.far <= obstruction.far) {
                far_visible = false;
            }     
        }
    }
	if (RPAS_RESTRICTIVENESS == 0) {
        return center_visible || near_visible || far_visible;
    } else if (RPAS_RESTRICTIVENESS == 1) {
         return (center_visible && near_visible) || (center_visible && far_visible);
    } else {
        return center_visible && near_visible && far_visible;
    }   
}
/* Generates a new list by combining all old obstructions with the new one (removing them if they are combined) and
adding the resulting obstruction to the list. */
void RGMap::rpas_add_obstruction(std::vector<CellAngles> & obstructions, CellAngles new_obstruction) {
    CellAngles new_object;
    new_object.near = new_obstruction.near;
    new_object.center = new_obstruction.center;
    new_object.far = new_obstruction.far;
    std::vector<CellAngles> new_list;
    for (CellAngles obstruction : obstructions) {
        if (!rpas_combine_obstructions(obstruction, new_object)) {
            new_list.push_back(obstruction);
        }
    }
    new_list.push_back(new_object);
    obstructions = new_list;
}
	
//Returns True if you combine, False otherwise
bool RGMap::rpas_combine_obstructions(CellAngles &old_o, CellAngles &new_o) {
	// Pseudo-sort; if their near values are equal, they overlap
    CellAngles low;
    CellAngles high;
	if (old_o.near < new_o.near) {
        low = old_o;
        high = new_o;
    } else if (new_o.near < old_o.near) {
        low = new_o;
        high = old_o;
    } else {
        new_o.far = std::max(old_o.far, new_o.far);
        return true;
    }
	// If they overlap, combine and return True
    if (low.far >= high.near) {
        new_o.near = std::min(low.near, high.near);
        new_o.far = std::max(low.far, high.far);
        return true;
    }
    return false;
}
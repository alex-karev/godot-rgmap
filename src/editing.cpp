#include "rgmap.h"
using namespace godot;

// All functions related to map editing

void RGMap::clean_map() {
    chunks.clear();
    chunks.shrink_to_fit();
    pathfinding_exception_allowed.clear();
    pathfinding_exception_allowed.shrink_to_fit();
    pathfinding_exception_disallowed.clear();
    pathfinding_exception_disallowed.shrink_to_fit();
}

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
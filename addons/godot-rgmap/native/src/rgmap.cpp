#include "rgmap.h"

using namespace godot;

/*
    Register Godot properties and methods
*/

void RGMap::_register_methods() {
    // Properties
    register_property<RGMap, Vector2>("size", &RGMap::size, Vector2(3,3));
    register_property<RGMap, Vector2>("chunk_size", &RGMap::chunk_size, Vector2(50,50));
    register_property<RGMap, int>("load_distance", &RGMap::load_distance, 1);
    register_property<RGMap, int>("render_distance", &RGMap::render_distance, 1);
    register_property<RGMap, bool>("allow_diagonal_pathfinding", &RGMap::allow_diagonal_pathfinding, true);
    register_property<RGMap, int>("fov_radius", &RGMap::fov_radius, 15);
    register_property<RGMap, float>("RPAS_RADIUS_FUDGE", &RGMap::RPAS_RADIUS_FUDGE, 1.0 / 3.0);
    register_property<RGMap, bool>("RPAS_NOT_VISIBLE_BLOCKS_VISION", &RGMap::RPAS_NOT_VISIBLE_BLOCKS_VISION, true);
    register_property<RGMap, int>("RPAS_RESTRICTIVENESS", &RGMap::RPAS_RESTRICTIVENESS, 1);
    register_property<RGMap, bool>("RPAS_VISIBLE_ON_EQUAL", &RGMap::RPAS_VISIBLE_ON_EQUAL, true);
    
    // Signals
    register_signal<RGMap>((char *)"chunks_load_requested", "ids", GODOT_VARIANT_TYPE_POOL_INT_ARRAY);
    register_signal<RGMap>((char *)"chunks_free_requested", "ids", GODOT_VARIANT_TYPE_POOL_INT_ARRAY);
    register_signal<RGMap>((char *)"chunks_render_requested", "ids", GODOT_VARIANT_TYPE_POOL_INT_ARRAY);
    register_signal<RGMap>((char *)"chunks_hide_requested", "ids", GODOT_VARIANT_TYPE_POOL_INT_ARRAY);
    register_signal<RGMap>((char *)"chunk_loaded", "index", GODOT_VARIANT_TYPE_INT);
    register_signal<RGMap>((char *)"chunk_freed", "index", GODOT_VARIANT_TYPE_INT);

    register_method("_ready", &RGMap::_ready);

    // Functions
    // Tiles
    register_method("add_tile", &RGMap::add_tile);
    register_method("set_tile_passability", &RGMap::set_tile_passability);
    register_method("set_tile_transparency", &RGMap::set_tile_transparency);
    register_method("add_tile_property", &RGMap::add_tile_property);
    register_method("set_tile_property", &RGMap::set_tile_property);
    register_method("set_tile_z_index", &RGMap::set_tile_z_index);
    register_method("set_tile_texture", &RGMap::set_tile_texture);
    register_method("set_tile_normal_map", &RGMap::set_tile_normal_map);
    register_method("set_tile_texture_offset", &RGMap::set_tile_texture_offset);
    register_method("set_tile_material", &RGMap::set_tile_material);
    register_method("set_tile_modulate", &RGMap::set_tile_modulate);
    register_method("get_tile_property", &RGMap::get_tile_property);
    register_method("get_tiles_count", &RGMap::get_tiles_count);
    register_method("get_tile_index", &RGMap::get_tile_index);
    register_method("get_tile_name", &RGMap::get_tile_name);
    register_method("get_tile_display_name", &RGMap::get_tile_display_name);
    register_method("get_tile_z_index", &RGMap::get_tile_z_index);
    register_method("get_tile_texture", &RGMap::get_tile_texture);
    register_method("get_tile_normal_map", &RGMap::get_tile_normal_map);
    register_method("get_tile_texture_offset", &RGMap::get_tile_texture_offset);
    register_method("get_tile_material", &RGMap::get_tile_material);
    register_method("get_tile_modulate", &RGMap::get_tile_modulate);
    register_method("is_tile_passable", &RGMap::is_tile_passable);
    register_method("is_tile_transparent", &RGMap::is_tile_transparent);
    register_method("generate_tileset", &RGMap::generate_tileset);
    // Chunks
    register_method("get_chunk_index", &RGMap::get_chunk_index);
    register_method("chunk_index_int_to_v2", &RGMap::chunk_index_int_to_v2);
    register_method("chunk_index_v2_to_int", &RGMap::chunk_index_v2_to_int);
    register_method("is_chunk_in_bounds", &RGMap::is_chunk_in_bounds);
    register_method("is_chunk_loaded", &RGMap::is_chunk_loaded);
    register_method("load_chunk", &RGMap::load_chunk);
    register_method("dump_chunk_data", &RGMap::dump_chunk_data);
    register_method("free_chunk", &RGMap::free_chunk);
    register_method("reset_chunk", &RGMap::reset_chunk);
    register_method("is_chunk_rendered", &RGMap::is_chunk_rendered);
    register_method("set_chunk_rendered", &RGMap::set_chunk_rendered);
    register_method("get_loaded_chunks", &RGMap::get_loaded_chunks);
    register_method("get_chunks_in_distance", &RGMap::get_chunks_in_distance);
    register_method("get_chunks_to_load", &RGMap::get_chunks_to_load);
    register_method("get_chunks_to_free", &RGMap::get_chunks_to_free);
    register_method("request_chunks_load", &RGMap::request_chunks_load);
    register_method("get_rendered_chunks", &RGMap::get_rendered_chunks);
    register_method("get_chunks_to_render", &RGMap::get_chunks_to_render);
    register_method("get_chunks_to_hide", &RGMap::get_chunks_to_hide);
    register_method("request_chunks_render", &RGMap::request_chunks_render);
    // Cells
    register_method("get_local_index", &RGMap::get_local_index);
    register_method("get_value", &RGMap::get_value);
    register_method("get_name", &RGMap::get_name);
    register_method("get_display_name", &RGMap::get_display_name);
    register_method("get_property", &RGMap::get_property);
    register_method("is_transparent", &RGMap::is_transparent);
    register_method("is_passable", &RGMap::is_passable);
    register_method("is_visible", &RGMap::is_visible);
    register_method("is_discovered", &RGMap::is_discovered);
    register_method("is_in_bounds", &RGMap::is_in_bounds);
    register_method("is_pathfinding_allowed", &RGMap::is_pathfinding_allowed);
    register_method("set_value", &RGMap::set_value);
    register_method("set_visibility", &RGMap::set_visibility);
    register_method("set_discovered", &RGMap::set_discovered);
    // View/Pathfinding
    register_method("rpas_calc_visible_cells_from", &RGMap::rpas_calc_visible_cells_from);
    register_method("calculate_fov", &RGMap::calculate_fov);
    register_method("add_pathfinding_exception", &RGMap::add_pathfinding_exception);
    register_method("remove_pathfinding_exception", &RGMap::remove_pathfinding_exception);
    register_method("show_pathfinding_exceptions", &RGMap::show_pathfinding_exceptions);
    register_method("find_path", &RGMap::find_path);
    register_method("find_discovered_path", &RGMap::find_discovered_path);
    register_method("get_line", &RGMap::get_line);
    register_method("get_line_orthogonal", &RGMap::get_line_orthogonal);
    register_method("raycast_vision", &RGMap::raycast_vision);
    register_method("raycast_path", &RGMap::raycast_path);
    register_method("visibility_between", &RGMap::visibility_between);
    // Editing
    register_method("place_map", &RGMap::place_map);
    register_method("draw_line", &RGMap::draw_line);
    register_method("draw_line_orthogonal", &RGMap::draw_line_orthogonal);
    register_method("draw_rect", &RGMap::draw_rect);
    register_method("fill_rect", &RGMap::fill_rect);
    register_method("draw_ellipse_orthogonal", &RGMap::draw_ellipse);
    register_method("draw_ellipse", &RGMap::draw_ellipse);
    register_method("fill_ellipse", &RGMap::fill_ellipse);
    register_method("draw_circle_orthogonal", &RGMap::draw_circle);
    register_method("draw_circle", &RGMap::draw_circle);
    register_method("fill_circle", &RGMap::fill_circle);
    register_method("draw_arc_orthogonal", &RGMap::draw_arc);
    register_method("draw_arc", &RGMap::draw_arc);
    register_method("fill_arc", &RGMap::fill_arc);
    register_method("clean_map", &RGMap::clean_map);
    register_method("resize_map", &RGMap::resize_map);
    // Entities
    register_method("add_entity", &RGMap::add_entity);
    register_method("remove_entity", &RGMap::remove_entity);
    register_method("move_entity", &RGMap::move_entity);
    register_method("set_entity_transparency", &RGMap::set_entity_transparency);
    register_method("set_entity_passability", &RGMap::set_entity_passability);
    register_method("set_entity_discovered", &RGMap::set_entity_discovered);
    register_method("is_entity_visible", &RGMap::is_entity_visible);
    register_method("is_entity_transparent", &RGMap::is_entity_transparent);
    register_method("is_entity_passable", &RGMap::is_entity_passable);
    register_method("is_entity_discovered", &RGMap::is_entity_discovered);
    register_method("is_entity_chunk_loaded", &RGMap::is_entity_chunk_loaded);
    register_method("is_entity_chunk_rendered", &RGMap::is_entity_chunk_rendered);
    register_method("get_entity_position", &RGMap::get_entity_position);
    register_method("get_entities_in_position", &RGMap::get_entities_in_position);
    register_method("get_entities_in_rect", &RGMap::get_entities_in_rect);
    register_method("get_entities_in_radius", &RGMap::get_entities_in_radius);
    register_method("get_entities_in_chunk", &RGMap::get_entities_in_chunk);
    // Save/Load
    register_method("dump_map_data", &RGMap::dump_map_data);
    register_method("load_map_data", &RGMap::load_map_data);
}

/*
    Initialization and Utils
*/
RGMap::RGMap() {}

RGMap::~RGMap() {}

void RGMap::_init() {
    size = Vector2(3,3);
    chunk_size = Vector2(50,50);
    allow_diagonal_pathfinding = true;
}

void RGMap::_ready() {
    chunks.resize(size.x*size.y);
}

/*
    Saving and Loading
*/

PoolIntArray RGMap::dump_map_data() {
    PoolIntArray map_data;
    // Save size data
    map_data.append(size.x);
    map_data.append(size.y);
    map_data.append(chunk_size.x);
    map_data.append(chunk_size.y);
    // Dump chunk data
    for (int index : loaded_chunks) {
        map_data.append(index);
        map_data.append_array(dump_chunk_data(index));
    }
    return map_data;
}

void RGMap::load_map_data(PoolIntArray map_data) {
    // Clean loaded data
    clean_map();
    // Reset size
    size.x = map_data[0];
    size.y = map_data[1];
    chunk_size.x = map_data[2];
    chunk_size.y = map_data[3];
    // Calculate number of chunks
    int chunks_number = (map_data.size()-4)/(chunk_size.x*chunk_size.y*NUM_CHUNK_ARRAYS+1);
    // Load chunks
    for (int i = 0; i < chunks_number; ++i) {
        // Get index
        PoolIntArray chunk_data;
        int start = 4 + i*(1+chunk_size.x*chunk_size.y*NUM_CHUNK_ARRAYS);
        // Add chunk data
        for (int k=0; k < chunk_size.x*chunk_size.y*NUM_CHUNK_ARRAYS; ++k) {
            int value = map_data[start + k + 1];
            chunk_data.append(value);
        }
        // Load chunk
        int index = map_data[start];
        load_chunk(index, chunk_data);
    }
}
#include "rgmap.h"
using namespace godot;

// All functions related to tiles

int RGMap::add_tile(String name, String display_name) {
    RGTile tile;
    tile.name = name;
    tile.display_name = display_name;
    Array custom_property_names = custom_tile_properties.keys();
    Array custom_property_default_values = custom_tile_properties.values();
    for (int i = 0; i < custom_tile_properties.size(); ++i) {
        tile.custom_properties[custom_property_names[i]] = custom_property_default_values[i];
    }
    tiles.push_back(tile);
    return tiles.size()-1;
}
void RGMap::set_tile_transparency(int index, bool value) {
    ERR_FAIL_INDEX(index, tiles.size());
    tiles[index].transparent = value;
}
void RGMap::set_tile_passability(int index, bool value) {
    ERR_FAIL_INDEX(index, tiles.size());
    tiles[index].passable = value;
}
void RGMap::add_tile_property(String property_name, Variant default_value) {
    custom_tile_properties[property_name] = default_value;
    for (int i = 0; i < tiles.size(); ++i) {
        tiles[i].custom_properties[property_name] = default_value;
    }
}
void RGMap::set_tile_property(int index, String property_name, Variant new_value) {
    ERR_FAIL_INDEX(index, tiles.size());
    tiles[index].custom_properties[property_name] = new_value;
}
void RGMap::set_tile_z_index(int index, int z_index) {
    ERR_FAIL_INDEX(index, tiles.size());
    tiles[index].z_index = z_index;
}
void RGMap::set_tile_texture_offset(int index, Vector2 offset) {
    ERR_FAIL_INDEX(index, tiles.size());
    tiles[index].texture_offset = offset;
}
void RGMap::set_tile_texture(int index, Ref<Texture> texture) {
    ERR_FAIL_INDEX(index, tiles.size());
    tiles[index].texture = texture;
}
void RGMap::set_tile_normal_map(int index, Ref<Texture> texture) {
    ERR_FAIL_INDEX(index, tiles.size());
    tiles[index].normal_map = texture;
}
void RGMap::set_tile_material(int index, Ref<Material> material) {
    ERR_FAIL_INDEX(index, tiles.size());
    tiles[index].material = material;
}
void RGMap::set_tile_modulate(int index, Color color) {
    ERR_FAIL_INDEX(index, tiles.size());
    tiles[index].modulate = color;
}
int RGMap::get_tile_z_index(int index) {
    ERR_FAIL_INDEX_V(index, tiles.size(), 0);
    return tiles[index].z_index;
}
Vector2 RGMap::get_tile_texture_offset(int index) {
    ERR_FAIL_INDEX_V(index, tiles.size(), Vector2(0,0));
    return tiles[index].texture_offset;
}
Ref<Texture> RGMap::get_tile_texture(int index) {
    ERR_FAIL_INDEX_V(index, tiles.size(), Ref<Texture>());
    return tiles[index].texture;
}
Ref<Texture> RGMap::get_tile_normal_map(int index) {
    ERR_FAIL_INDEX_V(index, tiles.size(), Ref<Texture>());
    return tiles[index].normal_map;
}
Ref<Material> RGMap::get_tile_material(int index) {
    ERR_FAIL_INDEX_V(index, tiles.size(), Ref<Material>());
    return tiles[index].material;
}
Color RGMap::get_tile_modulate(int index) {
    ERR_FAIL_INDEX_V(index, tiles.size(), Color(1.0,1.0,1.0));
    return tiles[index].modulate;
}
Variant RGMap::get_tile_property(int index, String property_name) {
    Variant empty;
    ERR_FAIL_INDEX_V(index, tiles.size(), empty);
    return tiles[index].custom_properties[property_name];
}
int RGMap::get_tiles_count() {
    return tiles.size();
}

int RGMap::get_tile_index(String name) { 
    for (int i=0; i < tiles.size(); ++i) {
        RGTile tile = tiles[i];
        if (tile.name == name) {
            return i;
        }
    }
    return -1; 
}
String RGMap::get_tile_name(int index) { return tiles[index].name; }
String RGMap::get_tile_display_name(int index) { return tiles[index].display_name; }
bool RGMap::is_tile_passable(int index) { return tiles[index].passable; }
bool RGMap::is_tile_transparent(int index) { return tiles[index].transparent; }
Ref<TileSet> RGMap::generate_tileset(){
    Ref<TileSet> new_tileset;
    new_tileset.instance();
    for (int i=0; i < get_tiles_count(); ++i) {
        new_tileset->create_tile(i);
        new_tileset->tile_set_texture(i, tiles[i].texture);
        new_tileset->tile_set_normal_map(i, tiles[i].normal_map);
        new_tileset->tile_set_name(i, tiles[i].name);
        new_tileset->tile_set_z_index(i, tiles[i].z_index);
        new_tileset->tile_set_texture_offset(i, tiles[i].texture_offset);
        new_tileset->tile_set_material(i, tiles[i].material);
        new_tileset->tile_set_modulate(i, tiles[i].modulate);
    }
    return new_tileset;
}
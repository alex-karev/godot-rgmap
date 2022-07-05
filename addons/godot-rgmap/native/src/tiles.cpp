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
Ref<TileSet> RGMap::generate_tileset(String texture_path, String texture_format){
    ResourceLoader* res_loader = ResourceLoader::get_singleton();
    Ref<TileSet> new_tileset;
    new_tileset.instance();
    for (int i=0; i < get_tiles_count(); ++i) {
        new_tileset->create_tile(i);
        String tile_name = get_tile_name(i);
        Ref<Texture> texture = res_loader->load(texture_path+tile_name+texture_format);
        new_tileset->tile_set_texture(i, texture);
    }
    return new_tileset;
}
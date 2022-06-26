#include "rgtileset.h"

using namespace godot;

void RGTileset::_register_methods() {
    register_signal<RGTileset>((char *)"tile_added", "index", GODOT_VARIANT_TYPE_INT);

    register_method("add_tile", &RGTileset::add_tile);
    register_method("get_tiles_count", &RGTileset::get_tiles_count);
    register_method("get_index", &RGTileset::get_index);
    register_method("get_name", &RGTileset::get_name);
    register_method("get_display_name", &RGTileset::get_display_name);
    register_method("is_passable", &RGTileset::is_passable);
    register_method("is_transparent", &RGTileset::is_transparent);
    register_method("generate_tileset", &RGTileset::generate_tileset);
}

void RGTileset::_init() {

}
RGTileset::RGTileset() {}
RGTileset::~RGTileset() {}

void RGTileset::add_tile(String name, String display_name, bool passable, bool transparent) {
    RGTile tile;
    tile.name = name;
    tile.display_name = display_name;
    tile.passable = passable;
    tile.transparent = transparent;
    tiles.push_back(tile);
}
int RGTileset::get_tiles_count() {
    return tiles.size();
}

int RGTileset::get_index(String name) { 
    for (int i=0; i < tiles.size(); ++i) {
        RGTile tile = tiles[i];
        if (tile.name == name) {
            return i;
        }
    }
    return -1; 
}

String RGTileset::get_name(int index) { return tiles[index].name; }
String RGTileset::get_display_name(int index) { return tiles[index].display_name; }
bool RGTileset::is_passable(int index) { return tiles[index].passable; }
bool RGTileset::is_transparent(int index) { return tiles[index].transparent; }
Ref<TileSet> RGTileset::generate_tileset(String texture_path, String texture_format){
    ResourceLoader* res_loader = ResourceLoader::get_singleton();
    Ref<TileSet> new_tileset;
    new_tileset.instance();
    for (int i=0; i < get_tiles_count(); ++i) {
        new_tileset->create_tile(i);
        String tile_name = get_name(i);
        Ref<Texture> texture = res_loader->load(texture_path+tile_name+texture_format);
        new_tileset->tile_set_texture(i, texture);
    }
    return new_tileset;
}
#include "rgtileset.h"

using namespace godot;

void RGTileSet::_register_methods() {
    register_method("add_tile", &RGTileSet::add_tile);
    register_method("get_tiles_count", &RGTileSet::get_tiles_count);
    register_method("get_name", &RGTileSet::get_name);
    register_method("get_display_name", &RGTileSet::get_display_name);
    register_method("is_passable", &RGTileSet::is_passable);
    register_method("is_transparent", &RGTileSet::is_transparent);
}

RGTileSet::RGTileSet() {
}

RGTileSet::~RGTileSet() {
    // add your cleanup here
}

void RGTileSet::_init() {
}


void RGTileSet::add_tile(String name, String display_name, bool passable, bool transparent) {
    RGTile tile;
    tile.name = name;
    tile.display_name = display_name;
    tile.passable = passable;
    tile.transparent = transparent;
    tiles.push_back(tile);
}
int RGTileSet::get_tiles_count() {
    return tiles.size();
}

String RGTileSet::get_name(int index) { return tiles[index].name; }
String RGTileSet::get_display_name(int index) { return tiles[index].display_name; }
bool RGTileSet::is_passable(int index) { return tiles[index].passable; }
bool RGTileSet::is_transparent(int index) { return tiles[index].transparent; }

---
title: /home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/tiles.cpp

---

# /home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/tiles.cpp






## Source code

```cpp
#include "rgmap.h"
using namespace godot;

// All functions related to tiles

void RGMap::add_tile(String name, String display_name, bool passable, bool transparent) {
    RGTile tile;
    tile.name = name;
    tile.display_name = display_name;
    tile.passable = passable;
    tile.transparent = transparent;
    tiles.push_back(tile);
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
```


-------------------------------

Updated on 2022-06-29 at 17:56:25 +0300

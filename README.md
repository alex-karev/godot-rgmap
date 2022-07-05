# Godot Roguelike Game Map System (RGMap)

A library for managing maps for roguelike games in Godot Engine. It helps with map generation, storing map data, and using pathfinding, raycasting, and FOV

<img src="https://github.com/alex-karev/godot-rgmap/raw/main/addons/godot-rgmap/screenshots/demo.gif">

## Table of Contents

1. [Features](#features)
2. [Usage](#usage)
3. [Example](#example)
4. [Installation](#installation)
5. [Building](#building)
6. [TODO](#tODO)
7. [References](#references)
8. [Contributing](#contributing)
9. [License](#license)

<img src="https://github.com/alex-karev/godot-rgmap/raw/main/addons/godot-rgmap/screenshots/demo2.gif">

## Features
* **FOV** calculation using RPAS algorithm
* **Raycasting** using Bresenham's lines
* **Pathfinding** using Godot built-in A* class
* **Discovering cells** that have been visible at least once
* **Chunk system** loadind/freeing chunks, dumping and restoring chunk data
* **Draw and fill** functions for drawing primitives (lines, ellipse, rects, circles, arcs)
* **Managing tiles** in RGMap class
* **TileSet generator** for Tilemaps based on data from RGMap
* **Merging maps.** Placing one RGMap inside the other map
* **Entity tracking.** Entities and their properties can also be considered while using FOV and pathfinding 
* **Saving and loading** data as a flat array
* **C++, GDNative**

## Usage
A new node is added:

### RGMap
A node for managing map. Use it for editing maps, calculating for, pathfinding, etc.

Tiles should be added before creating a new map

```
# Add tiles:
# var tile_id = rgmap.add_tile("core.game.ground", "Ground") # 'name' and 'display name'
# rgmap.set_tile_passability(tile_id, false) # Entities can not pass through this tile 
# rgmap.set_tile_transparency(tile_id, true) # This tile will be ignored while calculating FOV and checking visibility
```

It is strongly advised to store information about all your tiles in some database (e.g. JSON) and add tiles like this:

```
var file = File.new()
file.open("res://db.json", File.READ)
var txt = file.get_as_text()
var json = parse_json(txt)
for tile_name in json["tiles"].keys():
    var data = json["tiles"][tile_name]
    var tile_id = rgmap.add_tile(tile_name, data["name"])
    rgmap.set_tile_passability(tile_id, data["passable"])
    rgmap.set_tile_transparency(tile_id, data["transparent"])
```

If you want to create a 2d TileSet for your Tilemap, you can use generate_tileset function. 
It searches for images named as your tiles in a specified directory:

```
var tileset = rgmap.generate_tileset("res://Textures/",".png") # Generate new TileSet
myTilemap.tile_set = tileset # Assign new TileSet to Tilemap
```

RGMap has 4 signals that can be helpful for drawing and generating map:

```
chunks_load_requested(PoolIntArray ids) # Returns ids of chunks that needs to be loaded
chunks_free_requested(PoolIntArray ids) # Returns ids of chunks that needs to be freed
chunks_render_requested(PoolIntArray ids) # Returns ids of chunks that needs to be rendered
chunks_hide_requested(PoolIntArray ids) # Returns ids of rendered chunks that needs to be hidden
```

The distances for loading and rendering chunks can be set as load_distance and render_distance variables of RGMap node. 
To emit these 4 signals call these functions:

```
# player_position is position of the player on RGMap grid
request_chunks_load(player_position: Vector2) # For chunks load/free signals
request_chunks_render(player_position: Vector2) # For chunks render/hide signals
```

Don't forget to calculate FOV. It is better to do this in the end of the function connected to chunks_load_requested(PoolIntArray ids) signal:

```
func _on_RGMap_chunks_load_requested(ids):
    ...
    rgmap.calculate_fov(controller.player_position)
```

Please see [Generator.gd](https://github.com/alex-karev/godot-rgmap/blob/main/addons/godot-rgmap/demo/Generator.gd) 
for more detailed example

There are a lot of functions available in RGMap node. You can read more about each function and property in documentation:

[RGMap Class Documentation](https://alex-karev.github.io/godot-rgmap/classgodot_1_1RGMap.html)

Also, you can learn more from demo-project

## Example
You can find an example of usage in demo-project directory

## Installation
Requirements:

* Windows/Linux/Mac
* Godot 3.4.4 or later. May work on earlier versions, but not tested. No Godot 4 support at the moment

Install it the same way as a regular editor plugin. Copy the contents of `addons/godot-rgmap` into the same folder in your project. 

> Since it only adds a new NativeScript class, activation/deactivation of plugin from project settings doesn't work. The nodes added by this plugin are always available

> Currently there are only precompiled binaries for Windows, Linux and OSX, but it can be compiled for any other platform (e.g. Android). Follow instructions in *Building* section

## Building
You will need: C++ compiler and SCons installed in your system

1. Clone this repo and download submodules (godot-cpp):

```
git clone https://github.com/alex-karev/godot-rgmap.git
cd godot-rgmap
git submodule update --init --recursive
```

2. Generate and compile bindings:

```
cd addons/godot-rgmap/native/godot-cpp
scons platform=<platform> generate_bindings=yes target=release 
cd ..
```

> After this step Linux users can simply run `compile.sh` in `/addons/godot-rgmap/native` directory to automatically compile binaries for Window, Linux and OSX

3. Compile project by running scons in `/addons/godot-rgmap/native` directory

```
scons platform=<platform>
```

4. Edit `/addons/godot-rgmap/native/RGMap.gdnlib` manually or using Godot Editor. Link newly compiled binaries in `/addons/godot-rgmap/native/bin` directory

See more about using GDNative modules in [Godot Docs](https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html#using-the-gdnative-module)

## TODO
- [X] Create demo project
- [X] Add gifs and images to README
- [X] Automatic generation of 2D Tileset and Tilemap based on RGTileset
- [X] Better error handling
- [X] Chunk system
- [X] Entity tracking system
- [X] Change project structure and convert it to plugin (add plugin.gd)
- [X] Write bash script for batch compiling binaries for Linux/Windows/Mac
- [X] Custom properties of tiles
- [ ] Add node for rendering RGMap in 2d
- [ ] Cutting and resizing map
- [ ] Tutorial

## References
The code for some parts of this projects was inspired by/copied from these resources:
* RPAS implementation written in Python: <https://github.com/MoyTW/roguebasin_rpas>
* Bresenham's line: <http://www.roguebasin.com/index.php/Bresenham%27s_Line_Algorithm>
* Midpoint ellipse: <https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/>
* Doxygen theme: <https://jothepro.github.io/doxygen-awesome-css/>
* Godot cpp API: <https://github.com/godotengine/godot-cpp>

## Contributing
You are welcome to fork this repo and to create pull requests

## License
Distributed under the MIT License. See LICENSE for more information

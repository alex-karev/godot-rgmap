---
title: Godot Roguelike Game Map System (RGMap)

---

# Godot Roguelike Game Map System (RGMap)



 A library for managing maps for roguelike games in Godot Engine. It helps with map generation, storing map data, and using pathfinding, raycasting, and FOV

![https://github.com/alex-karev/godot-rgmap/raw/main/addons/godot-rgmap/screenshots/demo.gif](images/https://github.com/alex-karev/godot-rgmap/raw/main/addons/godot-rgmap/screenshots/demo.gif)

![https://github.com/alex-karev/godot-rgmap/raw/main/addons/godot-rgmap/screenshots/demo2.gif](images/https://github.com/alex-karev/godot-rgmap/raw/main/addons/godot-rgmap/screenshots/demo2.gif)


# Features



* **FOV** calculation using RPAS algorithm
* **Raycasting** using Bresenham's lines
* **Pathfinding** using Godot built-in A* class
* **Memorizing cells** that have been visible at least once
* **Chunk system** loadind/freeing chunks, dumping and restoring chunk data
* **Draw and fill** functions for drawing primitives (lines, ellipse, rects, circles, arcs)
* **Managing tiles** in RGMap class
* **TileSet generator** for Tilemaps based on data from RGMap
* **Merging maps.** Placing one RGMap inside the other map
* **Entity tracking.** Entities and their properties can also be considered while using FOV and pathfinding
* **Saving and loading** data as a flat array
* **C++, GDNative**

# Why?

To make managing maps for roguelikes easier by uniting all useful functions and properties in one class.

![https://raw.githubusercontent.com/alex-karev/godot-rgmap/main/addons/godot-rgmap/screenshots/code.png](images/https://raw.githubusercontent.com/alex-karev/godot-rgmap/main/addons/godot-rgmap/screenshots/code.png)


# Usage

A new node is added:


## RGMap

A node for managing map. Use it for editing maps, calculating for, pathfinding, etc.

Tiles should be added before creating a new map



```cpp
# Add tiles:
# rgmap.add_tile("core.game.ground", "Ground", true, true)
# Note: First 2 strings are 'name' and 'display name'. Other 2 booleans are 'passability' and 'transparency'
```

It is strongly advised to store information about all your tiles in some database (e.g. JSON) and add tiles like this:



```cpp
var file = File.new()
file.open("res://db.json", File.READ)
var txt = file.get_as_text()
var json = parse_json(txt)
for tile_name in json["tiles"].keys():
    var data = json["tiles"][tile_name]
    rgmap.add_tile(tile_name, data["name"], data["passable"], data["transparent"])
```

If you want to create a 2d TileSet for your Tilemap, you can use generate_tileset function. It searches for images named as your tiles in a specified directory:



```cpp
var tileset = rgmap.generate_tileset("res://Textures/",".png") # Generate new TileSet
myTilemap.tile_set = tileset # Assign new TileSet to Tilemap
```

RGMap has 4 signals that can be helpful for drawing and generating map:



```cpp
chunks_load_requested(PoolIntArray ids) # Returns ids of chunks that needs to be loaded
chunks_free_requested(PoolIntArray ids) # Returns ids of chunks that needs to be freed
chunks_render_requested(PoolIntArray ids) # Returns ids of chunks that needs to be rendered
chunks_hide_requested(PoolIntArray ids) # Returns ids of rendered chunks that needs to be hidden
```

The distances for loading and rendering chunks can be set as load_distance and render_distance variables of RGMap node. To emit these 4 signals call these functions:



```cpp
# player_position is position of the player on RGMap grid
request_chunks_update(player_position: Vector2) # For chunks load/free signals
request_chunks_render(player_position: Vector2) # For chunks render/hide signals
```

Don't forget to calculate FOV. It is better to do this in the end of the function connected to chunks_load_requested(PoolIntArray ids) signal:



```cpp
func _on_RGMap_chunks_load_requested(ids):
    ...
    rgmap.calculate_fov(controller.player_position, 30) # 30 is a radius
```

Please see [Generator.gd](https://github.com/alex-karev/godot-rgmap/blob/main/demo-project/Generator.gd) for more detailed example

There are a lot of functions available in RGMap node. You can read more about each function and variable here:

[https://alex-karev.github.io/godot-rgmap/classgodot_1_1RGMap.html](https://alex-karev.github.io/godot-rgmap/classgodot_1_1RGMap.html)

Also, you can learn more from demo-project


# Example

You can find an example of usage in demo-project directory


# Installation

Requirements:



* Windows or Linux
* Godot 3.4.4 or later. May work on earlier versions, but not tested. No Godot 4 support at the moment
Install it the same way as a regular editor plugin. Copy the contents of `addons/godot-rgmap` into the same folder in your project.



> Since it is just a new NativeScript class, activation/deactivation from project settings doesn't work. The nodes of this plugin are always available 
> 
> 



> Currently there are only precompiled binaries for Windows and Linux, but it can be compiled for any other platform (e.g. OSX). Follow instructions in _Building_ section 
> 
> 


# Building

You will need: C++ compiler and SCons installed in your system



1. Generate and compile bindings:


```cpp
cd addons/godot-rgmap/native/godot-cpp
scons platform=<platform> generate_bindings=yes
cd ..
```



1. Compile project


```cpp
cd addons/godot-rgmap/native
scons platform=<platform>
```



1. Create new NativeScript and GDNativeLibrary. Link it to binaries you have copied from /bin directory
See more about using GDNative modules here: [https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html#using-the-gdnative-module](https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html#using-the-gdnative-module)


# TODO



* [X] Create demo project
* [X] Add gifs and images to README
* [X] Automatic generation of 2D Tileset and Tilemap based on RGTileset
* [X] Better error handling
* [X] Chunk system
* [X] Entity tracking system
* [X] Change project structure and convert it to plugin (add plugin.gd)
* [ ] Write bash script for batch compiling binaries for Linux/Windows/Mac
* [ ] Custom properties of tiles
* [ ] Tutorial
* [ ] Add node for rendering RGMap in 2d
* [ ] Cutting and resizing map

# References

The code for some parts of this projects was inspired by/copied from these resources:

* RPAS implementation written in Python: [https://github.com/MoyTW/roguebasin_rpas](https://github.com/MoyTW/roguebasin_rpas)
* Bresenham's line: [http://www.roguebasin.com/index.php/Bresenham%27s_Line_Algorithm](http://www.roguebasin.com/index.php/Bresenham%27s_Line_Algorithm)
* Midpoint ellipse: [https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/](https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/)
* Doxygen theme: [https://jothepro.github.io/doxygen-awesome-css/](https://jothepro.github.io/doxygen-awesome-css/)
* Godot cpp API: [https://github.com/godotengine/godot-cpp](https://github.com/godotengine/godot-cpp)

# Contributing

You are welcome to fork this repo and to create pull requests


# License

Distributed under the MIT License. See LICENSE for more information 

-------------------------------

Updated on 2022-06-29 at 17:56:25 +0300

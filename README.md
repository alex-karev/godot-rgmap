# Godot <ins>R</ins>oguelike <ins>G</ins>ame <ins>M</ins>ap System (RGMap)

A library for managing maps for roguelike games in Godot Engine. It helps with map generation, storing map data, and using pathfinding, raycasting, and FOV

<img src="https://github.com/alex-karev/godot-rgmap/raw/main/screenshots/demo.gif">

<img src="https://github.com/alex-karev/godot-rgmap/raw/main/screenshots/demo2.gif">

## Features
* **FOV** calculation using RPAS algorithm
* **Raycasting** using Bresenham's lines
* **Pathfinding** using Godot built-in A* class
* **Memorizing cells** that have been visible at least once
* **Chunk system** loadind/freeing chunks, dumping and restoring chunk data
* **Draw and fill** functions for drawing primitives (lines, ellipse, rects, circles, arcs)
* **Managing tiles** in RGMap class
* **TileSet generator** for Tilemaps based on data from RGMap
* **Merging maps.** Placing one RGMap inside the other map
* **Saving and loading** data as a flat array
* **C++, GDNative**

## Why?
To make managing maps for roguelikes easier by uniting all useful functions and properties in one class.

<img src="https://raw.githubusercontent.com/alex-karev/godot-rgmap/main/screenshots/code.png">

## Usage
A new node is added:

### RGMap
A node for managing map. Use it for editing maps, calculating for, pathfinding, etc.

Tiles should be added before creating a new map

```
# Add tiles:
# rgmap.add_tile("core.game.ground", "Ground", true, true)
# Note: First 2 strings are 'name' and 'display name'. Other 2 booleans are 'passability' and 'transparency'
```

It is strongly advised to store information about all your tiles in some database (e.g. JSON) and add tiles like this:

```
var file = File.new()
file.open("res://db.json", File.READ)
var txt = file.get_as_text()
var json = parse_json(txt)
for tile_name in json["tiles"].keys():
    var data = json["tiles"][tile_name]
    rgmap.add_tile(tile_name, data["name"], data["passable"], data["transparent"])
```

If you want to create a 2d TileSet for your Tilemap, you can use generate_tileset function. 
It searches for images named as your tiles in a specified directory:

```
var tileset = rgmap.generate_tileset("res://Textures/",".png") # Generate new TileSet
myTilemap.tile_set = tileset # Assign new TileSet to Tilemap
```

RGMap has 2 signals that can be helpful for drawing and generating map:

```
chunks_load_requested(PoolIntArray ids) # Returns ids of chunks that needs to be loaded
chunks_free_requested(PoolIntArray ids) # Returns ids of chunks that needs to be freed
```

To emit these 2 signals call this function

```
request_chunks_update(player_position: Vector2) # Player_position is position of the player on RGMap grid
```

Don't forget to calculate FOV. It is better to do this in the end of the function connected to chunks_load_requested(PoolIntArray ids) signal:

```
func _on_RGMap_chunks_load_requested(ids):
    ...
    rgmap.calculate_fov(controller.player_position, 30) # 30 is a radius
```

Please see [Generator.gd](https://github.com/alex-karev/godot-rgmap/blob/main/demo-project/Generator.gd) 
for more detailed example

There are a lot of functions available in RGMap node. You can read more about each function and variable  here:

<https://alex-karev.github.io/godot-rgmap/classgodot_1_1RGMap.html>

Also, you can learn more from demo-project

## Example
You can find an example of usage in demo-project directory

## Compilation
You will need: C++ compiler and SCons installed in your system

1. Generate and compile bindings:

```
cd godot-cpp
scons platform=<platform> generate_bindings=yes
cd ..
```

2. Compile project

```
mkdir bin
scons platform=<platform>
```

3. Copy everything from /bin directory to your godot project
4. Create new NativeScript and GDNativeLibrary. Link it to binaries you have copied from /bin directory

See more about using GDNative modules here: <https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html#using-the-gdnative-module>

## TODO
- [X] Create demo project
- [X] Add gifs and images to README
- [X] Automatic generation of 2D Tileset and Tilemap based on RGTileset
- [X] Better error handling
- [X] Chunk system
- [ ] Cutting and resizing map

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

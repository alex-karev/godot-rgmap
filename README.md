# Godot Roguelike Map System (RGMap)

A library for managing maps for roguelike games in Godot Engine. It helps with map generation, storing map data, and using pathfinding, raycasting, and FOV



## Features
* **FOV** calculation using RPAS algorithm
* **Raycasting** using Bresenham's lines
* **Pathfinding** using Godot built-in A* class
* **"Memorizing" cells** that have been visible at least once
* **Draw and fill** functions for drawing primitives (lines, ellipse, rects, circles, arcs)
* **Custom RGTileset** class to store data about all tiles in a game
* **Merging maps.** Placing one RGMap inside the other map
* **Saving and loading** data as a flat array
* **C++, GDNative**

## Why?

To make managing maps for roguelikes easier by uniting all useful functions and properties in one class.

## Usage
There are some new classes inherited from Reference:

### RGTileset
A class for storing data about tiles. A proper RGTileset object should be created before creating a new map, as it stores all necessary data about tiles used in-game.

Should be created like this:

```
var tileset = RGTileset.new()
# Add tiles:
# tileset.add_tile("core.game.ground", "Ground", true, true)
# Note: First 2 strings are 'name' and 'display name'. Other 2 booleans are 'passability' and 'transparency'
```

It is strongly advised to store information about all your tiles in some database (e.g. JSON) and add tiles to RGTileset like this:

```
var file = File.new()
file.open("res://db.json", File.READ)
var txt = file.get_as_text()
var json = parse_json(txt)
for tile_name in json["tiles"].keys():
	var data = json["tiles"][tile_name]
    tileset.add_tile(tile_name, data["name"], data["passable"], data["transparent"])
```

Here you can find all functions available inside in RGTileset: 

<https://alex-karev.github.io/godot-rgmap/classgodot_1_1RGTileSet.html>

### RGMap
A class for managing map. Use it for editing maps, calculating for, pathfinding, etc.

Should be initialized before usage like this:
```
var map = RGMap.new()
map.size = Vector2(100,100)
map.initialize(tileset) # RGTileset object created earlier
```

You can read more about each function and variable available in RGMap here:

<https://alex-karev.github.io/godot-rgmap/classgodot_1_1RGMap.html>

## Compilation
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

## Example
You can find a short example of usage in demo-project directory

## TODO
- [ ] Create demo project
- [ ] Add gifs and images to README
- [ ] Cutting and resizing map
- [ ] Automatic generation of 2D Tileset and Tilemap based on RGTileset
- [ ] Better error handling

## License
Distributed under the MIT License. See LICENSE for more information
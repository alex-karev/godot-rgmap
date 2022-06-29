---
title: godot::RGMap
summary: Class for managing maps for roguelike. 

---

# godot::RGMap



Class for managing maps for roguelike. 


`#include <rgmap.h>`

Inherits from Reference

## Public Functions

|                | Name           |
| -------------- | -------------- |
| PoolIntArray | **[chunks_load_requested](Classes/classgodot_1_1RGMap.md#function-chunks-load-requested)**()<br>**Signal.** Emited when chunks need to be loaded. Emited on calling request_chunks_update function  |
| PoolIntArray | **[chunks_free_requested](Classes/classgodot_1_1RGMap.md#function-chunks-free-requested)**()<br>**Signal.** Emited when chunks need to be freed. Emited on calling request_chunks_update function  |
| PoolIntArray | **[chunks_render_requested](Classes/classgodot_1_1RGMap.md#function-chunks-render-requested)**()<br>**Signal.** Emited when chunks need to be rendered. Emited on calling request_chunks_render function  |
| PoolIntArray | **[chunks_hide_requested](Classes/classgodot_1_1RGMap.md#function-chunks-hide-requested)**()<br>**Signal.** Emited when rendered chunks need to be hidden. Emited on calling request_chunks_render function  |
| int | **[chunk_loaded](Classes/classgodot_1_1RGMap.md#function-chunk-loaded)**()<br>**Signal.** Emited when is loaded for the first time. Emited on calling load_chunk function  |
| int | **[chunk_freed](Classes/classgodot_1_1RGMap.md#function-chunk-freed)**()<br>**Signal.** Emited when chunk is freed from memory. Emited on calling free_chunk function  |
| | **[RGMap](Classes/classgodot_1_1RGMap.md#function-rgmap)**() |
| | **[~RGMap](Classes/classgodot_1_1RGMap.md#function-~rgmap)**() |
| void | **[_init](Classes/classgodot_1_1RGMap.md#function--init)**() |
| void | **[_register_methods](Classes/classgodot_1_1RGMap.md#function--register-methods)**() |
| void | **[add_tile](Classes/classgodot_1_1RGMap.md#function-add-tile)**(String name, String display_name, bool passable, bool transparent)<br>Add new tile.  |
| int | **[get_tiles_count](Classes/classgodot_1_1RGMap.md#function-get-tiles-count)**()<br>Get number of tiles.  |
| int | **[get_tile_index](Classes/classgodot_1_1RGMap.md#function-get-tile-index)**(String name)<br>Get tile index by name.  |
| String | **[get_tile_name](Classes/classgodot_1_1RGMap.md#function-get-tile-name)**(int index)<br>Get tile name (unique)  |
| String | **[get_tile_display_name](Classes/classgodot_1_1RGMap.md#function-get-tile-display-name)**(int index)<br>Get tile display name.  |
| bool | **[is_tile_passable](Classes/classgodot_1_1RGMap.md#function-is-tile-passable)**(int index)<br>Check if tile is passable.  |
| bool | **[is_tile_transparent](Classes/classgodot_1_1RGMap.md#function-is-tile-transparent)**(int index)<br>Check if tile is transparent.  |
| Ref< TileSet > | **[generate_tileset](Classes/classgodot_1_1RGMap.md#function-generate-tileset)**(String texture_path, String texture_format)<br>Generate Tileset for using with 2d Tilemap.  |
| int | **[get_chunk_index](Classes/classgodot_1_1RGMap.md#function-get-chunk-index)**(Vector2 position)<br>Get index of chunk which contains a given position.  |
| Vector2 | **[chunk_index_int_to_v2](Classes/classgodot_1_1RGMap.md#function-chunk-index-int-to-v2)**(int index)<br>Convert index of chunk from int to Vector2 format.  |
| int | **[chunk_index_v2_to_int](Classes/classgodot_1_1RGMap.md#function-chunk-index-v2-to-int)**(Vector2 index)<br>Convert index of chunk from Vector2 to int format.  |
| bool | **[is_chunk_in_bounds](Classes/classgodot_1_1RGMap.md#function-is-chunk-in-bounds)**(int index)<br>Check if chunk is in bounds.  |
| bool | **[is_chunk_loaded](Classes/classgodot_1_1RGMap.md#function-is-chunk-loaded)**(int index)<br>Check if chunk is loaded.  |
| void | **[load_chunk](Classes/classgodot_1_1RGMap.md#function-load-chunk)**(int index, PoolIntArray data =PoolIntArray())<br>Load saved chunk to memory or generate a new chunk. "data" argument is optional.  |
| PoolIntArray | **[dump_chunk_data](Classes/classgodot_1_1RGMap.md#function-dump-chunk-data)**(int index)<br>Returns all cell data for chunk as PoolIntArray.  |
| void | **[free_chunk](Classes/classgodot_1_1RGMap.md#function-free-chunk)**(int index)<br>Free chunk from memory.  |
| void | **[reset_chunk](Classes/classgodot_1_1RGMap.md#function-reset-chunk)**(int index)<br>Clear all cell data in chunk.  |
| bool | **[is_chunk_rendered](Classes/classgodot_1_1RGMap.md#function-is-chunk-rendered)**(int index)<br>Check if chunk is rendered.  |
| void | **[set_chunk_rendered](Classes/classgodot_1_1RGMap.md#function-set-chunk-rendered)**(int index, bool value)<br>Set rendering status of chunk.  |
| PoolIntArray | **[get_loaded_chunks](Classes/classgodot_1_1RGMap.md#function-get-loaded-chunks)**()<br>Get ids of loaded chunks.  |
| PoolIntArray | **[get_chunks_to_load](Classes/classgodot_1_1RGMap.md#function-get-chunks-to-load)**(Vector2 player_position)<br>Get ids of chunks around player that needs to be loaded.  |
| PoolIntArray | **[get_chunks_to_free](Classes/classgodot_1_1RGMap.md#function-get-chunks-to-free)**(Vector2 player_position)<br>Get ids of chunks that are loaded, but not needed anymore because player is too far.  |
| void | **[request_chunks_update](Classes/classgodot_1_1RGMap.md#function-request-chunks-update)**(Vector2 player_position)<br>Request chunk load/unload depending on player_position and load_distance.  |
| PoolIntArray | **[get_rendered_chunks](Classes/classgodot_1_1RGMap.md#function-get-rendered-chunks)**()<br>Get ids of rendered chunks.  |
| PoolIntArray | **[get_chunks_to_render](Classes/classgodot_1_1RGMap.md#function-get-chunks-to-render)**(Vector2 player_position)<br>Get ids of chunks around player that needs to be rendered.  |
| PoolIntArray | **[get_chunks_to_hide](Classes/classgodot_1_1RGMap.md#function-get-chunks-to-hide)**(Vector2 player_position)<br>Get ids of chunks that are rendered, but not needed anymore because player is too far.  |
| void | **[request_chunks_render](Classes/classgodot_1_1RGMap.md#function-request-chunks-render)**(Vector2 player_position)<br>Request chunk render/hide depending on player_position and render_distance.  |
| int | **[get_local_index](Classes/classgodot_1_1RGMap.md#function-get-local-index)**(Vector2 position)<br>Get local index of cell within a chunk.  |
| int | **[get_value](Classes/classgodot_1_1RGMap.md#function-get-value)**(Vector2 position)<br>Get value of cell.  |
| String | **[get_name](Classes/classgodot_1_1RGMap.md#function-get-name)**(Vector2 position)<br>Get name of cell.  |
| String | **[get_display_name](Classes/classgodot_1_1RGMap.md#function-get-display-name)**(Vector2 position)<br>Get display name of cell.  |
| bool | **[is_in_bounds](Classes/classgodot_1_1RGMap.md#function-is-in-bounds)**(Vector2 position)<br>Check if cell is in bounds.  |
| bool | **[is_transparent](Classes/classgodot_1_1RGMap.md#function-is-transparent)**(Vector2 position)<br>Check if cell is transparent.  |
| bool | **[is_passable](Classes/classgodot_1_1RGMap.md#function-is-passable)**(Vector2 position)<br>Check if cell is passable.  |
| bool | **[is_visible](Classes/classgodot_1_1RGMap.md#function-is-visible)**(Vector2 position)<br>Check if cell is visible.  |
| bool | **[is_memorized](Classes/classgodot_1_1RGMap.md#function-is-memorized)**(Vector2 position)<br>Check if cell is memorized.  |
| bool | **[is_pathfinding_allowed](Classes/classgodot_1_1RGMap.md#function-is-pathfinding-allowed)**(Vector2 position)<br>Check if pathfinding on this cell is allowed.  |
| void | **[set_value](Classes/classgodot_1_1RGMap.md#function-set-value)**(Vector2 position, int value)<br>Set value of cell.  |
| void | **[set_visibility](Classes/classgodot_1_1RGMap.md#function-set-visibility)**(Vector2 position, bool value)<br>Set visibility of cell.  |
| void | **[set_memorized](Classes/classgodot_1_1RGMap.md#function-set-memorized)**(Vector2 position, bool value)<br>Set memory state of cell.  |
| PoolVector2Array | **[rpas_calc_visible_cells_from](Classes/classgodot_1_1RGMap.md#function-rpas-calc-visible-cells-from)**(Vector2 center, int radius)<br>Get list of cells visible from position within radius using RPAS algorithm.  |
| void | **[calculate_fov](Classes/classgodot_1_1RGMap.md#function-calculate-fov)**(Vector2 view_position, int max_distance)<br>Calculate visibility from given position and distance.  |
| void | **[add_pathfinding_exception](Classes/classgodot_1_1RGMap.md#function-add-pathfinding-exception)**(Vector2 position, bool value)<br>Allow/disallow patfinding for this cell ignoring passability.  |
| void | **[remove_pathfinding_exception](Classes/classgodot_1_1RGMap.md#function-remove-pathfinding-exception)**(Vector2 position)<br>Remove all pathfinding exceptions for this cell if they exist.  |
| PoolVector2Array | **[show_pathfinding_exceptions](Classes/classgodot_1_1RGMap.md#function-show-pathfinding-exceptions)**(bool exception_type)<br>Show all pathfinding exceptions of a type.  |
| PoolVector2Array | **[find_path](Classes/classgodot_1_1RGMap.md#function-find-path)**(Vector2 start, Vector2 end, Rect2 pathfinding_zone, bool exclude_undiscovered =false)<br>Find path from start to end using A* algorithm.  |
| PoolVector2Array | **[get_line](Classes/classgodot_1_1RGMap.md#function-get-line)**(Vector2 start, Vector2 end, bool allow_diagonal =true)<br>Get a set of points in Bresenham's line.  |
| Vector2 | **[raycast_vision](Classes/classgodot_1_1RGMap.md#function-raycast-vision)**(Vector2 start, Vector2 end)<br>Cast ray from start to end and return position where vision is blocked by an obstacle.  |
| Vector2 | **[raycast_path](Classes/classgodot_1_1RGMap.md#function-raycast-path)**(Vector2 start, Vector2 end)<br>Cast ray from start to end and return position where path is blocked by an obstacle.  |
| bool | **[visibility_between](Classes/classgodot_1_1RGMap.md#function-visibility-between)**(Vector2 start, Vector2 end, int max_distance)<br>Check if end point is visisble from start point.  |
| void | **[clean_map](Classes/classgodot_1_1RGMap.md#function-clean-map)**()<br>Free all chunks and forget pathfinding exceptions.  |
| void | **[place_map](Classes/classgodot_1_1RGMap.md#function-place-map)**([RGMap](Classes/classgodot_1_1RGMap.md) * another_map, Vector2 start)<br>Place another map inside this map.  |
| void | **[draw_line](Classes/classgodot_1_1RGMap.md#function-draw-line)**(Vector2 start, Vector2 end, int value, bool allow_diagonal =true)<br>Draw straight line using Bresenham's line algorithm.  |
| void | **[draw_rect](Classes/classgodot_1_1RGMap.md#function-draw-rect)**(Rect2 rect, int value)<br>Draw rect borders.  |
| void | **[fill_rect](Classes/classgodot_1_1RGMap.md#function-fill-rect)**(Rect2 rect, int value)<br>Fill rect.  |
| void | **[draw_ellipse](Classes/classgodot_1_1RGMap.md#function-draw-ellipse)**(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value, bool allow_diagonal =true)<br>Draw ellipse using Bresenham's midpoint algorithm.  |
| void | **[fill_ellipse](Classes/classgodot_1_1RGMap.md#function-fill-ellipse)**(Vector2 center, Vector2 radius, float start_angle, float end_angle, int value)<br>Fill ellipse.  |
| void | **[draw_circle](Classes/classgodot_1_1RGMap.md#function-draw-circle)**(Vector2 center, float radius, int value, bool allow_diagonal =true)<br>Draw circle.  |
| void | **[fill_circle](Classes/classgodot_1_1RGMap.md#function-fill-circle)**(Vector2 center, float radius, int value)<br>Fill circle.  |
| void | **[draw_arc](Classes/classgodot_1_1RGMap.md#function-draw-arc)**(Vector2 center, float radius, float start_angle, float end_angle, int value, bool allow_diagonal =true)<br>Draw arc.  |
| void | **[fill_arc](Classes/classgodot_1_1RGMap.md#function-fill-arc)**(Vector2 center, float radius, float start_angle, float end_angle, int value)<br>Fill arc.  |
| int | **[add_entity](Classes/classgodot_1_1RGMap.md#function-add-entity)**(Vector2 position, bool passability, bool transparency)<br>Add new entity to the map. Returns id given to a new entity.  |
| void | **[remove_entity](Classes/classgodot_1_1RGMap.md#function-remove-entity)**(int id)<br>Remove entity from memory. The id of this entity will also be given to a new entity.  |
| void | **[move_entity](Classes/classgodot_1_1RGMap.md#function-move-entity)**(int id, Vector2 position)<br>Move entity to a new position.  |
| void | **[set_entity_transparency](Classes/classgodot_1_1RGMap.md#function-set-entity-transparency)**(int id, bool value)<br>Change entity transparency.  |
| void | **[set_entity_passability](Classes/classgodot_1_1RGMap.md#function-set-entity-passability)**(int id, bool value)<br>Change entity passability.  |
| void | **[set_entity_memorized](Classes/classgodot_1_1RGMap.md#function-set-entity-memorized)**(int id, bool value)<br>Change memory status of entity.  |
| bool | **[is_entity_visible](Classes/classgodot_1_1RGMap.md#function-is-entity-visible)**(int id)<br>Check if entity is visible.  |
| bool | **[is_entity_transparent](Classes/classgodot_1_1RGMap.md#function-is-entity-transparent)**(int id)<br>Check if entity is transparent;.  |
| bool | **[is_entity_passable](Classes/classgodot_1_1RGMap.md#function-is-entity-passable)**(int id)<br>Check if entity is passable.  |
| bool | **[is_entity_memorized](Classes/classgodot_1_1RGMap.md#function-is-entity-memorized)**(int id)<br>Check if entity is memorized.  |
| bool | **[is_entity_chunk_loaded](Classes/classgodot_1_1RGMap.md#function-is-entity-chunk-loaded)**(int id)<br>Check if entity is on loaded chunk.  |
| bool | **[is_entity_chunk_rendered](Classes/classgodot_1_1RGMap.md#function-is-entity-chunk-rendered)**(int id)<br>Check if entity is on rendered chunk.  |
| Vector2 | **[get_entity_position](Classes/classgodot_1_1RGMap.md#function-get-entity-position)**(int id)<br>Get position of the entity.  |
| PoolIntArray | **[get_entities_in_position](Classes/classgodot_1_1RGMap.md#function-get-entities-in-position)**(Vector2 position)<br>Find ids of all entities in position.  |
| PoolIntArray | **[get_entities_in_rect](Classes/classgodot_1_1RGMap.md#function-get-entities-in-rect)**(Rect2 rect)<br>Find ids of all entities in rect.  |
| PoolIntArray | **[get_entities_in_radius](Classes/classgodot_1_1RGMap.md#function-get-entities-in-radius)**(Vector2 position, int radius)<br>Find ids of all entities in radius.  |
| PoolIntArray | **[get_entities_in_chunk](Classes/classgodot_1_1RGMap.md#function-get-entities-in-chunk)**(int chunk_index)<br>Find ids of all entities in chunk.  |
| PoolIntArray | **[dump_map_data](Classes/classgodot_1_1RGMap.md#function-dump-map-data)**()<br>Save map data.  |
| void | **[load_map_data](Classes/classgodot_1_1RGMap.md#function-load-map-data)**(PoolIntArray map_data)<br>Load map data.  |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| float | **[RPAS_RADIUS_FUDGE](Classes/classgodot_1_1RGMap.md#variable-rpas-radius-fudge)** <br>How smooth the edges of the vision bubble are. Between 0 and 1.  |
| bool | **[RPAS_NOT_VISIBLE_BLOCKS_VISION](Classes/classgodot_1_1RGMap.md#variable-rpas-not-visible-blocks-vision)** <br>If this is false, some cells will unexpectedly be visible.  |
| int | **[RPAS_RESTRICTIVENESS](Classes/classgodot_1_1RGMap.md#variable-rpas-restrictiveness)** <br>Determines how restrictive the algorithm is.  |
| bool | **[RPAS_VISIBLE_ON_EQUAL](Classes/classgodot_1_1RGMap.md#variable-rpas-visible-on-equal)** <br>If false, an obstruction will obstruct its endpoints.  |
| Vector2 | **[chunk_size](Classes/classgodot_1_1RGMap.md#variable-chunk-size)** <br>Size of one chunk (Default: 50x50)  |
| Vector2 | **[size](Classes/classgodot_1_1RGMap.md#variable-size)** <br>Size of the whole map in chunks (Default: 3x3)  |
| int | **[load_distance](Classes/classgodot_1_1RGMap.md#variable-load-distance)** <br>Number of chunks loaded around the player.  |
| int | **[render_distance](Classes/classgodot_1_1RGMap.md#variable-render-distance)** <br>Number of chunks rendered around the player.  |
| bool | **[allow_diagonal_pathfinding](Classes/classgodot_1_1RGMap.md#variable-allow-diagonal-pathfinding)** <br>Allow/Disallow diagonal pathfinding.  |

## Public Functions Documentation

### function chunks_load_requested

```cpp
inline PoolIntArray chunks_load_requested()
```

**Signal.** Emited when chunks need to be loaded. Emited on calling request_chunks_update function 

### function chunks_free_requested

```cpp
inline PoolIntArray chunks_free_requested()
```

**Signal.** Emited when chunks need to be freed. Emited on calling request_chunks_update function 

### function chunks_render_requested

```cpp
inline PoolIntArray chunks_render_requested()
```

**Signal.** Emited when chunks need to be rendered. Emited on calling request_chunks_render function 

### function chunks_hide_requested

```cpp
inline PoolIntArray chunks_hide_requested()
```

**Signal.** Emited when rendered chunks need to be hidden. Emited on calling request_chunks_render function 

### function chunk_loaded

```cpp
inline int chunk_loaded()
```

**Signal.** Emited when is loaded for the first time. Emited on calling load_chunk function 

### function chunk_freed

```cpp
inline int chunk_freed()
```

**Signal.** Emited when chunk is freed from memory. Emited on calling free_chunk function 

### function RGMap

```cpp
RGMap()
```


### function ~RGMap

```cpp
~RGMap()
```


### function _init

```cpp
void _init()
```


### function _register_methods

```cpp
static void _register_methods()
```


### function add_tile

```cpp
void add_tile(
    String name,
    String display_name,
    bool passable,
    bool transparent
)
```

Add new tile. 

### function get_tiles_count

```cpp
int get_tiles_count()
```

Get number of tiles. 

### function get_tile_index

```cpp
int get_tile_index(
    String name
)
```

Get tile index by name. 

### function get_tile_name

```cpp
String get_tile_name(
    int index
)
```

Get tile name (unique) 

### function get_tile_display_name

```cpp
String get_tile_display_name(
    int index
)
```

Get tile display name. 

### function is_tile_passable

```cpp
bool is_tile_passable(
    int index
)
```

Check if tile is passable. 

### function is_tile_transparent

```cpp
bool is_tile_transparent(
    int index
)
```

Check if tile is transparent. 

### function generate_tileset

```cpp
Ref< TileSet > generate_tileset(
    String texture_path,
    String texture_format
)
```

Generate Tileset for using with 2d Tilemap. 

**Parameters**: 

  * **texture_path** A directory within the project where textures are stored (e.g "res://Textures/") 
  * **texture_format** A format of textures (e.g ".png") 


### function get_chunk_index

```cpp
int get_chunk_index(
    Vector2 position
)
```

Get index of chunk which contains a given position. 

### function chunk_index_int_to_v2

```cpp
Vector2 chunk_index_int_to_v2(
    int index
)
```

Convert index of chunk from int to Vector2 format. 

### function chunk_index_v2_to_int

```cpp
int chunk_index_v2_to_int(
    Vector2 index
)
```

Convert index of chunk from Vector2 to int format. 

### function is_chunk_in_bounds

```cpp
bool is_chunk_in_bounds(
    int index
)
```

Check if chunk is in bounds. 

### function is_chunk_loaded

```cpp
bool is_chunk_loaded(
    int index
)
```

Check if chunk is loaded. 

### function load_chunk

```cpp
void load_chunk(
    int index,
    PoolIntArray data =PoolIntArray()
)
```

Load saved chunk to memory or generate a new chunk. "data" argument is optional. 

### function dump_chunk_data

```cpp
PoolIntArray dump_chunk_data(
    int index
)
```

Returns all cell data for chunk as PoolIntArray. 

### function free_chunk

```cpp
void free_chunk(
    int index
)
```

Free chunk from memory. 

### function reset_chunk

```cpp
void reset_chunk(
    int index
)
```

Clear all cell data in chunk. 

### function is_chunk_rendered

```cpp
bool is_chunk_rendered(
    int index
)
```

Check if chunk is rendered. 

### function set_chunk_rendered

```cpp
void set_chunk_rendered(
    int index,
    bool value
)
```

Set rendering status of chunk. 

### function get_loaded_chunks

```cpp
PoolIntArray get_loaded_chunks()
```

Get ids of loaded chunks. 

### function get_chunks_to_load

```cpp
PoolIntArray get_chunks_to_load(
    Vector2 player_position
)
```

Get ids of chunks around player that needs to be loaded. 

**Parameters**: 

  * **player_position** Vector2 position of the player Uses load_distance parameter to define the radius Skips chunks that were already loaded 


### function get_chunks_to_free

```cpp
PoolIntArray get_chunks_to_free(
    Vector2 player_position
)
```

Get ids of chunks that are loaded, but not needed anymore because player is too far. 

**Parameters**: 

  * **player_position** Vector2 position of the player Uses load_distance parameter to define the radius 


### function request_chunks_update

```cpp
void request_chunks_update(
    Vector2 player_position
)
```

Request chunk load/unload depending on player_position and load_distance. 

**Parameters**: 

  * **player_position** Vector2 position of the player Uses load_distance parameter to define the radius 


Emits "chunks_load_requested" and "chunks_free_requested" signals Will produce the same result until chunks will be loaded/freed from other script Does nothing if all needed chunks are loaded and all unneeded chunks are freed 


### function get_rendered_chunks

```cpp
PoolIntArray get_rendered_chunks()
```

Get ids of rendered chunks. 

### function get_chunks_to_render

```cpp
PoolIntArray get_chunks_to_render(
    Vector2 player_position
)
```

Get ids of chunks around player that needs to be rendered. 

**Parameters**: 

  * **player_position** Vector2 position of the player Uses render_distance parameter to define the radius Skips chunks that were already rendered 


### function get_chunks_to_hide

```cpp
PoolIntArray get_chunks_to_hide(
    Vector2 player_position
)
```

Get ids of chunks that are rendered, but not needed anymore because player is too far. 

**Parameters**: 

  * **player_position** Vector2 position of the player Uses render_distance parameter to define the radius 


### function request_chunks_render

```cpp
void request_chunks_render(
    Vector2 player_position
)
```

Request chunk render/hide depending on player_position and render_distance. 

**Parameters**: 

  * **player_position** Vector2 position of the player Uses render_distance parameter to define the radius 


Emits "chunks_render_requested" and "chunks_hide_requested" signals Will produce the same result until chunks will be rendered/hidden from other script Does nothing if all needed chunks are rendered and all unneeded chunks are hidden 


### function get_local_index

```cpp
int get_local_index(
    Vector2 position
)
```

Get local index of cell within a chunk. 

### function get_value

```cpp
int get_value(
    Vector2 position
)
```

Get value of cell. 

### function get_name

```cpp
String get_name(
    Vector2 position
)
```

Get name of cell. 

### function get_display_name

```cpp
String get_display_name(
    Vector2 position
)
```

Get display name of cell. 

### function is_in_bounds

```cpp
bool is_in_bounds(
    Vector2 position
)
```

Check if cell is in bounds. 

### function is_transparent

```cpp
bool is_transparent(
    Vector2 position
)
```

Check if cell is transparent. 

### function is_passable

```cpp
bool is_passable(
    Vector2 position
)
```

Check if cell is passable. 

### function is_visible

```cpp
bool is_visible(
    Vector2 position
)
```

Check if cell is visible. 

### function is_memorized

```cpp
bool is_memorized(
    Vector2 position
)
```

Check if cell is memorized. 

### function is_pathfinding_allowed

```cpp
bool is_pathfinding_allowed(
    Vector2 position
)
```

Check if pathfinding on this cell is allowed. 

### function set_value

```cpp
void set_value(
    Vector2 position,
    int value
)
```

Set value of cell. 

### function set_visibility

```cpp
void set_visibility(
    Vector2 position,
    bool value
)
```

Set visibility of cell. 

### function set_memorized

```cpp
void set_memorized(
    Vector2 position,
    bool value
)
```

Set memory state of cell. 

### function rpas_calc_visible_cells_from

```cpp
PoolVector2Array rpas_calc_visible_cells_from(
    Vector2 center,
    int radius
)
```

Get list of cells visible from position within radius using RPAS algorithm. 

### function calculate_fov

```cpp
void calculate_fov(
    Vector2 view_position,
    int max_distance
)
```

Calculate visibility from given position and distance. 

### function add_pathfinding_exception

```cpp
void add_pathfinding_exception(
    Vector2 position,
    bool value
)
```

Allow/disallow patfinding for this cell ignoring passability. 

### function remove_pathfinding_exception

```cpp
void remove_pathfinding_exception(
    Vector2 position
)
```

Remove all pathfinding exceptions for this cell if they exist. 

### function show_pathfinding_exceptions

```cpp
PoolVector2Array show_pathfinding_exceptions(
    bool exception_type
)
```

Show all pathfinding exceptions of a type. 

**Parameters**: 

  * **exception_type** true for allowed cells, false for disallowed cells 


### function find_path

```cpp
PoolVector2Array find_path(
    Vector2 start,
    Vector2 end,
    Rect2 pathfinding_zone,
    bool exclude_undiscovered =false
)
```

Find path from start to end using A* algorithm. 

**Parameters**: 

  * **start** Start point 
  * **end** Target point 
  * **pathfinding_zone** Rect2 zone where pathfinding is calculated 
  * **exclude_undiscovered** True to exclude undiscovered cells (Fefault: False) 


Returns PoolVector2Array 


### function get_line

```cpp
PoolVector2Array get_line(
    Vector2 start,
    Vector2 end,
    bool allow_diagonal =true
)
```

Get a set of points in Bresenham's line. 

Based on Python implementation from here: [http://www.roguebasin.com/index.php/Bresenham%27s_Line_Algorithm](http://www.roguebasin.com/index.php/Bresenham%27s_Line_Algorithm)


### function raycast_vision

```cpp
Vector2 raycast_vision(
    Vector2 start,
    Vector2 end
)
```

Cast ray from start to end and return position where vision is blocked by an obstacle. 

### function raycast_path

```cpp
Vector2 raycast_path(
    Vector2 start,
    Vector2 end
)
```

Cast ray from start to end and return position where path is blocked by an obstacle. 

### function visibility_between

```cpp
bool visibility_between(
    Vector2 start,
    Vector2 end,
    int max_distance
)
```

Check if end point is visisble from start point. 

**Parameters**: 

  * **start** Start point 
  * **end** Target point 
  * **max_distance** Maximum distance at which points are visible 


### function clean_map

```cpp
void clean_map()
```

Free all chunks and forget pathfinding exceptions. 

### function place_map

```cpp
void place_map(
    RGMap * another_map,
    Vector2 start
)
```

Place another map inside this map. 

### function draw_line

```cpp
void draw_line(
    Vector2 start,
    Vector2 end,
    int value,
    bool allow_diagonal =true
)
```

Draw straight line using Bresenham's line algorithm. 

### function draw_rect

```cpp
void draw_rect(
    Rect2 rect,
    int value
)
```

Draw rect borders. 

### function fill_rect

```cpp
void fill_rect(
    Rect2 rect,
    int value
)
```

Fill rect. 

### function draw_ellipse

```cpp
void draw_ellipse(
    Vector2 center,
    Vector2 radius,
    float start_angle,
    float end_angle,
    int value,
    bool allow_diagonal =true
)
```

Draw ellipse using Bresenham's midpoint algorithm. 

Tweaked version of code from here: [https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/](https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/)


### function fill_ellipse

```cpp
void fill_ellipse(
    Vector2 center,
    Vector2 radius,
    float start_angle,
    float end_angle,
    int value
)
```

Fill ellipse. 

### function draw_circle

```cpp
void draw_circle(
    Vector2 center,
    float radius,
    int value,
    bool allow_diagonal =true
)
```

Draw circle. 

### function fill_circle

```cpp
void fill_circle(
    Vector2 center,
    float radius,
    int value
)
```

Fill circle. 

### function draw_arc

```cpp
void draw_arc(
    Vector2 center,
    float radius,
    float start_angle,
    float end_angle,
    int value,
    bool allow_diagonal =true
)
```

Draw arc. 

### function fill_arc

```cpp
void fill_arc(
    Vector2 center,
    float radius,
    float start_angle,
    float end_angle,
    int value
)
```

Fill arc. 

### function add_entity

```cpp
int add_entity(
    Vector2 position,
    bool passability,
    bool transparency
)
```

Add new entity to the map. Returns id given to a new entity. 

### function remove_entity

```cpp
void remove_entity(
    int id
)
```

Remove entity from memory. The id of this entity will also be given to a new entity. 

### function move_entity

```cpp
void move_entity(
    int id,
    Vector2 position
)
```

Move entity to a new position. 

### function set_entity_transparency

```cpp
void set_entity_transparency(
    int id,
    bool value
)
```

Change entity transparency. 

### function set_entity_passability

```cpp
void set_entity_passability(
    int id,
    bool value
)
```

Change entity passability. 

### function set_entity_memorized

```cpp
void set_entity_memorized(
    int id,
    bool value
)
```

Change memory status of entity. 

### function is_entity_visible

```cpp
bool is_entity_visible(
    int id
)
```

Check if entity is visible. 

### function is_entity_transparent

```cpp
bool is_entity_transparent(
    int id
)
```

Check if entity is transparent;. 

### function is_entity_passable

```cpp
bool is_entity_passable(
    int id
)
```

Check if entity is passable. 

### function is_entity_memorized

```cpp
bool is_entity_memorized(
    int id
)
```

Check if entity is memorized. 

### function is_entity_chunk_loaded

```cpp
bool is_entity_chunk_loaded(
    int id
)
```

Check if entity is on loaded chunk. 

### function is_entity_chunk_rendered

```cpp
bool is_entity_chunk_rendered(
    int id
)
```

Check if entity is on rendered chunk. 

### function get_entity_position

```cpp
Vector2 get_entity_position(
    int id
)
```

Get position of the entity. 

### function get_entities_in_position

```cpp
PoolIntArray get_entities_in_position(
    Vector2 position
)
```

Find ids of all entities in position. 

### function get_entities_in_rect

```cpp
PoolIntArray get_entities_in_rect(
    Rect2 rect
)
```

Find ids of all entities in rect. 

### function get_entities_in_radius

```cpp
PoolIntArray get_entities_in_radius(
    Vector2 position,
    int radius
)
```

Find ids of all entities in radius. 

### function get_entities_in_chunk

```cpp
PoolIntArray get_entities_in_chunk(
    int chunk_index
)
```

Find ids of all entities in chunk. 

### function dump_map_data

```cpp
PoolIntArray dump_map_data()
```

Save map data. 

### function load_map_data

```cpp
void load_map_data(
    PoolIntArray map_data
)
```

Load map data. 

## Public Attributes Documentation

### variable RPAS_RADIUS_FUDGE

```cpp
float RPAS_RADIUS_FUDGE = 1.0 / 3.0;
```

How smooth the edges of the vision bubble are. Between 0 and 1. 

### variable RPAS_NOT_VISIBLE_BLOCKS_VISION

```cpp
bool RPAS_NOT_VISIBLE_BLOCKS_VISION = true;
```

If this is false, some cells will unexpectedly be visible. 

### variable RPAS_RESTRICTIVENESS

```cpp
int RPAS_RESTRICTIVENESS = 1;
```

Determines how restrictive the algorithm is. 

0 - if you have a line to the near, center, or far, it will return as visible 

 1 - if you have a line to the center and at least one other corner it will return as visible 

 2 - if you have a line to all the near, center, and far, it will return as visible 


### variable RPAS_VISIBLE_ON_EQUAL

```cpp
bool RPAS_VISIBLE_ON_EQUAL = true;
```

If false, an obstruction will obstruct its endpoints. 

### variable chunk_size

```cpp
Vector2 chunk_size = Vector2(50,50);
```

Size of one chunk (Default: 50x50) 

### variable size

```cpp
Vector2 size = Vector2(3,3);
```

Size of the whole map in chunks (Default: 3x3) 

### variable load_distance

```cpp
int load_distance = 1;
```

Number of chunks loaded around the player. 

Excluding the chunk where player stands Default: 1 (3x3 grid) 


### variable render_distance

```cpp
int render_distance = 1;
```

Number of chunks rendered around the player. 

Excluding the chunk where player stands Default: 1 (3x3 grid) 


### variable allow_diagonal_pathfinding

```cpp
bool allow_diagonal_pathfinding = true;
```

Allow/Disallow diagonal pathfinding. 

-------------------------------

Updated on 2022-06-29 at 17:56:25 +0300
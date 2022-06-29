# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`godot`](#namespacegodot) | 
`struct `[`godot::RGMap::CellAngles`](#structgodot_1_1RGMap_1_1CellAngles) | 
`struct `[`godot::RGMap::Chunk`](#structgodot_1_1RGMap_1_1Chunk) | 
`struct `[`godot::RGMap::Entity`](#structgodot_1_1RGMap_1_1Entity) | 
`struct `[`godot::RGMap::RGTile`](#structgodot_1_1RGMap_1_1RGTile) | 

# namespace `godot` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`godot::RGMap`](#classgodot_1_1RGMap) | Class for managing maps for roguelike.

# class `godot::RGMap` 

```
class godot::RGMap
  : public Reference
```  

Class for managing maps for roguelike.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public Vector2 `[`chunk_size`](#classgodot_1_1RGMap_1a3fba15a031ad1bd976b281cefe90bc79) | Size of one chunk (Default: 50x50)
`public Vector2 `[`size`](#classgodot_1_1RGMap_1a4a8e96884242e6b83b2417d127a814a8) | Size of the whole map in chunks (Default: 3x3)
`public int `[`load_distance`](#classgodot_1_1RGMap_1ab097624100d11699293844ead170dab9) | Number of chunks loaded around the player.
`public int `[`render_distance`](#classgodot_1_1RGMap_1aef65b060d5dbda0c47f00d2431921b49) | Number of chunks rendered around the player.
`public bool `[`allow_diagonal_pathfinding`](#classgodot_1_1RGMap_1a092151ec6eda7be42513f17eb9ebfe1f) | Allow/Disallow diagonal pathfinding.

## Members

#### `public Vector2 `[`chunk_size`](#classgodot_1_1RGMap_1a3fba15a031ad1bd976b281cefe90bc79) 

Size of one chunk (Default: 50x50)

#### `public Vector2 `[`size`](#classgodot_1_1RGMap_1a4a8e96884242e6b83b2417d127a814a8) 

Size of the whole map in chunks (Default: 3x3)

#### `public int `[`load_distance`](#classgodot_1_1RGMap_1ab097624100d11699293844ead170dab9) 

Number of chunks loaded around the player.

Excluding the chunk where player stands Default: 1 (3x3 grid)

#### `public int `[`render_distance`](#classgodot_1_1RGMap_1aef65b060d5dbda0c47f00d2431921b49) 

Number of chunks rendered around the player.

Excluding the chunk where player stands Default: 1 (3x3 grid)

#### `public bool `[`allow_diagonal_pathfinding`](#classgodot_1_1RGMap_1a092151ec6eda7be42513f17eb9ebfe1f) 

Allow/Disallow diagonal pathfinding.

# struct `godot::RGMap::CellAngles` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public float `[`near`](#structgodot_1_1RGMap_1_1CellAngles_1af1a398f285f58942d48d0f51d1d60140) | 
`public float `[`center`](#structgodot_1_1RGMap_1_1CellAngles_1a4df431df66f448de8b63a64313d9a7db) | 
`public float `[`far`](#structgodot_1_1RGMap_1_1CellAngles_1a2d94503a8823ba36b7e4099a1350e404) | 

## Members

#### `public float `[`near`](#structgodot_1_1RGMap_1_1CellAngles_1af1a398f285f58942d48d0f51d1d60140) 

#### `public float `[`center`](#structgodot_1_1RGMap_1_1CellAngles_1a4df431df66f448de8b63a64313d9a7db) 

#### `public float `[`far`](#structgodot_1_1RGMap_1_1CellAngles_1a2d94503a8823ba36b7e4099a1350e404) 

# struct `godot::RGMap::Chunk` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`index`](#structgodot_1_1RGMap_1_1Chunk_1ac928dc4640ea3284513031035ed0cb46) | 
`public std::vector< int > `[`values`](#structgodot_1_1RGMap_1_1Chunk_1a762bff10471ac2f417833e71765ac74b) | 
`public std::vector< int > `[`memory`](#structgodot_1_1RGMap_1_1Chunk_1ad87bd69b873a0dbc48fce10853d120ba) | 
`public bool `[`rendered`](#structgodot_1_1RGMap_1_1Chunk_1aa500cf02272ed5b9406ccba61e6cf2ce) | 

## Members

#### `public int `[`index`](#structgodot_1_1RGMap_1_1Chunk_1ac928dc4640ea3284513031035ed0cb46) 

#### `public std::vector< int > `[`values`](#structgodot_1_1RGMap_1_1Chunk_1a762bff10471ac2f417833e71765ac74b) 

#### `public std::vector< int > `[`memory`](#structgodot_1_1RGMap_1_1Chunk_1ad87bd69b873a0dbc48fce10853d120ba) 

#### `public bool `[`rendered`](#structgodot_1_1RGMap_1_1Chunk_1aa500cf02272ed5b9406ccba61e6cf2ce) 

# struct `godot::RGMap::Entity` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public Vector2 `[`position`](#structgodot_1_1RGMap_1_1Entity_1a415858af3f366b8f7ec5b1caa95dc207) | 
`public bool `[`passability`](#structgodot_1_1RGMap_1_1Entity_1a0fcbd7aaf10988ce3a1378295dbd10f1) | 
`public bool `[`transparency`](#structgodot_1_1RGMap_1_1Entity_1afff27fb9366c63506c71b013b648262c) | 
`public bool `[`memorized`](#structgodot_1_1RGMap_1_1Entity_1adfd4f983c5b8bce13e1853dce91fd48f) | 
`public bool `[`rewrite`](#structgodot_1_1RGMap_1_1Entity_1a061f580c5da2ea878092acceb487bbfd) | 

## Members

#### `public Vector2 `[`position`](#structgodot_1_1RGMap_1_1Entity_1a415858af3f366b8f7ec5b1caa95dc207) 

#### `public bool `[`passability`](#structgodot_1_1RGMap_1_1Entity_1a0fcbd7aaf10988ce3a1378295dbd10f1) 

#### `public bool `[`transparency`](#structgodot_1_1RGMap_1_1Entity_1afff27fb9366c63506c71b013b648262c) 

#### `public bool `[`memorized`](#structgodot_1_1RGMap_1_1Entity_1adfd4f983c5b8bce13e1853dce91fd48f) 

#### `public bool `[`rewrite`](#structgodot_1_1RGMap_1_1Entity_1a061f580c5da2ea878092acceb487bbfd) 

# struct `godot::RGMap::RGTile` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public String `[`name`](#structgodot_1_1RGMap_1_1RGTile_1afbc0eab1a5fbdad9e98cf2f78b22f11a) | 
`public String `[`display_name`](#structgodot_1_1RGMap_1_1RGTile_1a42eec52245916ac39eeeea863e96d7f2) | 
`public bool `[`passable`](#structgodot_1_1RGMap_1_1RGTile_1a97692965423dab469a67b3a54dddd042) | 
`public bool `[`transparent`](#structgodot_1_1RGMap_1_1RGTile_1a766f2e820b1557d5f3e1b1af625bcfa1) | 

## Members

#### `public String `[`name`](#structgodot_1_1RGMap_1_1RGTile_1afbc0eab1a5fbdad9e98cf2f78b22f11a) 

#### `public String `[`display_name`](#structgodot_1_1RGMap_1_1RGTile_1a42eec52245916ac39eeeea863e96d7f2) 

#### `public bool `[`passable`](#structgodot_1_1RGMap_1_1RGTile_1a97692965423dab469a67b3a54dddd042) 

#### `public bool `[`transparent`](#structgodot_1_1RGMap_1_1RGTile_1a766f2e820b1557d5f3e1b1af625bcfa1) 

Generated by [Moxygen](https://sourcey.com/moxygen)
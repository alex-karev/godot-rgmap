::: {#classgodot_1_1RGMap}
:::

[]{#classgodot_1_1RGMap label="classgodot_1_1RGMap"}

Class for managing maps for roguelike.

#include $<$rgmap.h$>$

Inheritance diagram for godot::RGMap:

::: center
![image](classgodot_1_1RGMap){height="2.000000cm"}
:::

::: Indent
**Signals**

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_afd1aae74dc064d42ccf5b934472294cf
label="classgodot_1_1RGMap_afd1aae74dc064d42ccf5b934472294cf"}
PoolIntArray **chunks_load_requested** ()

::: DoxyCompactList
***Signal.** Emited when chunks need to be loaded. Emited on calling
request_chunks_update function*
:::

[]{#classgodot_1_1RGMap_a2d061a66f56eb6392e41f4f9028d16fc
label="classgodot_1_1RGMap_a2d061a66f56eb6392e41f4f9028d16fc"}
PoolIntArray **chunks_free_requested** ()

::: DoxyCompactList
***Signal.** Emited when chunks need to be freed. Emited on calling
request_chunks_update function*
:::

[]{#classgodot_1_1RGMap_abf1c8ce2971af113a8513d1b018e07cc
label="classgodot_1_1RGMap_abf1c8ce2971af113a8513d1b018e07cc"}
PoolIntArray **chunks_render_requested** ()

::: DoxyCompactList
***Signal.** Emited when chunks need to be rendered. Emited on calling
request_chunks_render function*
:::

[]{#classgodot_1_1RGMap_ab011bf3701f536742a9b37530c327312
label="classgodot_1_1RGMap_ab011bf3701f536742a9b37530c327312"}
PoolIntArray **chunks_hide_requested** ()

::: DoxyCompactList
***Signal.** Emited when rendered chunks need to be hidden. Emited on
calling request_chunks_render function*
:::

[]{#classgodot_1_1RGMap_a8f3bb2de68b7d4a239516015a86db8db
label="classgodot_1_1RGMap_a8f3bb2de68b7d4a239516015a86db8db"} int
**chunk_loaded** ()

::: DoxyCompactList
***Signal.** Emited when is loaded for the first time. Emited on calling
load_chunk function*
:::

[]{#classgodot_1_1RGMap_a74f8456f280ddaa8a3f3b3161a6ad63f
label="classgodot_1_1RGMap_a74f8456f280ddaa8a3f3b3161a6ad63f"} int
**chunk_freed** ()

::: DoxyCompactList
***Signal.** Emited when chunk is freed from memory. Emited on calling
free_chunk function*
:::
:::
:::

::: Indent
**Tiles**

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_a55c55e1a5e1386093860a634c33cee3d
label="classgodot_1_1RGMap_a55c55e1a5e1386093860a634c33cee3d"} void
**add_tile** (String name, String display_name, bool passable, bool
transparent)

::: DoxyCompactList
*Add new tile.*
:::

[]{#classgodot_1_1RGMap_a0a6742a8d89a003db699ba02cd2f965a
label="classgodot_1_1RGMap_a0a6742a8d89a003db699ba02cd2f965a"} int
**get_tiles_count** ()

::: DoxyCompactList
*Get number of tiles.*
:::

[]{#classgodot_1_1RGMap_ac7e85ab8ca5c1b3580a773b35a8386fd
label="classgodot_1_1RGMap_ac7e85ab8ca5c1b3580a773b35a8386fd"} int
**get_tile_index** (String name)

::: DoxyCompactList
*Get tile index by name.*
:::

[]{#classgodot_1_1RGMap_a9d0347ce24c61097eaca4292816b7ce3
label="classgodot_1_1RGMap_a9d0347ce24c61097eaca4292816b7ce3"} String
**get_tile_name** (int index)

::: DoxyCompactList
*Get tile name (unique)*
:::

[]{#classgodot_1_1RGMap_a30d5d2ff82cbb7b163b4f2f960180539
label="classgodot_1_1RGMap_a30d5d2ff82cbb7b163b4f2f960180539"} String
**get_tile_display_name** (int index)

::: DoxyCompactList
*Get tile display name.*
:::

[]{#classgodot_1_1RGMap_ad407df53a5d381f958965c34acae88b1
label="classgodot_1_1RGMap_ad407df53a5d381f958965c34acae88b1"} bool
**is_tile_passable** (int index)

::: DoxyCompactList
*Check if tile is passable.*
:::

[]{#classgodot_1_1RGMap_a217ae3cae06583ad6e0eaf4c4a7ccf36
label="classgodot_1_1RGMap_a217ae3cae06583ad6e0eaf4c4a7ccf36"} bool
**is_tile_transparent** (int index)

::: DoxyCompactList
*Check if tile is transparent.*
:::

Ref$<$ TileSet $>$
[generate_tileset](#classgodot_1_1RGMap_a819587d899569b840a3f417aa9fd0c2f)
(String texture_path, String texture_format)

::: DoxyCompactList
*Generate Tileset for using with 2d Tilemap.*
:::
:::
:::

::: Indent
**Chunks**

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_a17d00e1acf01120ad1324704960ea528
label="classgodot_1_1RGMap_a17d00e1acf01120ad1324704960ea528"} int
**get_chunk_index** (Vector2 position)

::: DoxyCompactList
*Get index of chunk which contains a given position.*
:::

[]{#classgodot_1_1RGMap_aa042aaa2c6cbc4f67473574c4861cbf2
label="classgodot_1_1RGMap_aa042aaa2c6cbc4f67473574c4861cbf2"} Vector2
**chunk_index_int_to_v2** (int index)

::: DoxyCompactList
*Convert index of chunk from int to Vector2 format.*
:::

[]{#classgodot_1_1RGMap_a3ede385c9811d5c189943e42416af746
label="classgodot_1_1RGMap_a3ede385c9811d5c189943e42416af746"} int
**chunk_index_v2_to_int** (Vector2 index)

::: DoxyCompactList
*Convert index of chunk from Vector2 to int format.*
:::

[]{#classgodot_1_1RGMap_ac47d550255055871d8b15ea21ccd7227
label="classgodot_1_1RGMap_ac47d550255055871d8b15ea21ccd7227"} bool
**is_chunk_in_bounds** (int index)

::: DoxyCompactList
*Check if chunk is in bounds.*
:::

[]{#classgodot_1_1RGMap_af9b781ce0c7fe4ccefa66fdcace66a0f
label="classgodot_1_1RGMap_af9b781ce0c7fe4ccefa66fdcace66a0f"} bool
**is_chunk_loaded** (int index)

::: DoxyCompactList
*Check if chunk is loaded.*
:::

[]{#classgodot_1_1RGMap_aff48c6694c9a7229c7603ec56fa19e8e
label="classgodot_1_1RGMap_aff48c6694c9a7229c7603ec56fa19e8e"} void
**load_chunk** (int index, PoolIntArray data=PoolIntArray())

::: DoxyCompactList
*Load saved chunk to memory or generate a new chunk. '̈data'̈ argument is
optional.*
:::

[]{#classgodot_1_1RGMap_a05f17a76987156e6694a858d3dee1c49
label="classgodot_1_1RGMap_a05f17a76987156e6694a858d3dee1c49"}
PoolIntArray **dump_chunk_data** (int index)

::: DoxyCompactList
*Returns all cell data for chunk as PoolIntArray.*
:::

[]{#classgodot_1_1RGMap_a97e1bbbce76aca2a37e08db6d793907e
label="classgodot_1_1RGMap_a97e1bbbce76aca2a37e08db6d793907e"} void
**free_chunk** (int index)

::: DoxyCompactList
*Free chunk from memory.*
:::

[]{#classgodot_1_1RGMap_af16dce1ae917a6a42c237d7e7eebda92
label="classgodot_1_1RGMap_af16dce1ae917a6a42c237d7e7eebda92"} void
**reset_chunk** (int index)

::: DoxyCompactList
*Clear all cell data in chunk.*
:::

[]{#classgodot_1_1RGMap_a12e1b530faa11809a3fb965924166324
label="classgodot_1_1RGMap_a12e1b530faa11809a3fb965924166324"} bool
**is_chunk_rendered** (int index)

::: DoxyCompactList
*Check if chunk is rendered.*
:::

[]{#classgodot_1_1RGMap_a05420fcbc688769a4f97f4e068036609
label="classgodot_1_1RGMap_a05420fcbc688769a4f97f4e068036609"} void
**set_chunk_rendered** (int index, bool value)

::: DoxyCompactList
*Set rendering status of chunk.*
:::

[]{#classgodot_1_1RGMap_aaff3bdcfb3484ab4807bf536aa126e11
label="classgodot_1_1RGMap_aaff3bdcfb3484ab4807bf536aa126e11"}
PoolIntArray **get_loaded_chunks** ()

::: DoxyCompactList
*Get ids of loaded chunks.*
:::

PoolIntArray
[get_chunks_to_load](#classgodot_1_1RGMap_af81558e0a4b18590aea6f385f6fa345f)
(Vector2 player_position)

::: DoxyCompactList
*Get ids of chunks around player that needs to be loaded.*
:::

PoolIntArray
[get_chunks_to_free](#classgodot_1_1RGMap_ad292a1d8e79b597004643fbcf2e588f8)
(Vector2 player_position)

::: DoxyCompactList
*Get ids of chunks that are loaded, but not needed anymore because
player is too far.*
:::

void
[request_chunks_update](#classgodot_1_1RGMap_a2c565c4b9124368ebdaae851afd13585)
(Vector2 player_position)

::: DoxyCompactList
*Request chunk load/unload depending on player_position and
load_distance.*
:::

[]{#classgodot_1_1RGMap_a2e9616170d0d2bb4e1e5946c4f9f8d60
label="classgodot_1_1RGMap_a2e9616170d0d2bb4e1e5946c4f9f8d60"}
PoolIntArray **get_rendered_chunks** ()

::: DoxyCompactList
*Get ids of rendered chunks.*
:::

PoolIntArray
[get_chunks_to_render](#classgodot_1_1RGMap_a742bfc37a17e36f017d52f2bac8b698f)
(Vector2 player_position)

::: DoxyCompactList
*Get ids of chunks around player that needs to be rendered.*
:::

PoolIntArray
[get_chunks_to_hide](#classgodot_1_1RGMap_a251886c67ff84873042b83e836585203)
(Vector2 player_position)

::: DoxyCompactList
*Get ids of chunks that are rendered, but not needed anymore because
player is too far.*
:::

void
[request_chunks_render](#classgodot_1_1RGMap_af97b719797501ed8525d3aad37ed83d7)
(Vector2 player_position)

::: DoxyCompactList
*Request chunk render/hide depending on player_position and
render_distance.*
:::
:::
:::

::: Indent
**Cells**

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_ab201f09297e368756c390a122a94fc97
label="classgodot_1_1RGMap_ab201f09297e368756c390a122a94fc97"} int
**get_local_index** (Vector2 position)

::: DoxyCompactList
*Get local index of cell within a chunk.*
:::

[]{#classgodot_1_1RGMap_a0608386ad66cec9e4257808022da5038
label="classgodot_1_1RGMap_a0608386ad66cec9e4257808022da5038"} int
**get_value** (Vector2 position)

::: DoxyCompactList
*Get value of cell.*
:::

[]{#classgodot_1_1RGMap_a4113d609f2d8b8ae8986b5261d72589a
label="classgodot_1_1RGMap_a4113d609f2d8b8ae8986b5261d72589a"} String
**get_name** (Vector2 position)

::: DoxyCompactList
*Get name of cell.*
:::

[]{#classgodot_1_1RGMap_a4016e0965171c95fd867bd7eb01b65d9
label="classgodot_1_1RGMap_a4016e0965171c95fd867bd7eb01b65d9"} String
**get_display_name** (Vector2 position)

::: DoxyCompactList
*Get display name of cell.*
:::

[]{#classgodot_1_1RGMap_a37429fe0e0426653916667725477e01b
label="classgodot_1_1RGMap_a37429fe0e0426653916667725477e01b"} bool
**is_in_bounds** (Vector2 position)

::: DoxyCompactList
*Check if cell is in bounds.*
:::

[]{#classgodot_1_1RGMap_a9722afa05ac0d4efe1146a9f8b70908b
label="classgodot_1_1RGMap_a9722afa05ac0d4efe1146a9f8b70908b"} bool
**is_transparent** (Vector2 position)

::: DoxyCompactList
*Check if cell is transparent.*
:::

[]{#classgodot_1_1RGMap_a6bc13a61c915adcfcd1c74d75b9a786a
label="classgodot_1_1RGMap_a6bc13a61c915adcfcd1c74d75b9a786a"} bool
**is_passable** (Vector2 position)

::: DoxyCompactList
*Check if cell is passable.*
:::

[]{#classgodot_1_1RGMap_a2ae7a1232b97d00c21a38a1073cb7b53
label="classgodot_1_1RGMap_a2ae7a1232b97d00c21a38a1073cb7b53"} bool
**is_visible** (Vector2 position)

::: DoxyCompactList
*Check if cell is visible.*
:::

[]{#classgodot_1_1RGMap_a735635c94c0913ffb0198dd51681986f
label="classgodot_1_1RGMap_a735635c94c0913ffb0198dd51681986f"} bool
**is_memorized** (Vector2 position)

::: DoxyCompactList
*Check if cell is memorized.*
:::

[]{#classgodot_1_1RGMap_a90bbf21a0a0084bc3cada939c5b84848
label="classgodot_1_1RGMap_a90bbf21a0a0084bc3cada939c5b84848"} bool
**is_pathfinding_allowed** (Vector2 position)

::: DoxyCompactList
*Check if pathfinding on this cell is allowed.*
:::

[]{#classgodot_1_1RGMap_abf819377354f5deaf670605175243442
label="classgodot_1_1RGMap_abf819377354f5deaf670605175243442"} void
**set_value** (Vector2 position, int value)

::: DoxyCompactList
*Set value of cell.*
:::

[]{#classgodot_1_1RGMap_a0aad3be6e33070ebedb8ea3eb81789cf
label="classgodot_1_1RGMap_a0aad3be6e33070ebedb8ea3eb81789cf"} void
**set_visibility** (Vector2 position, bool value)

::: DoxyCompactList
*Set visibility of cell.*
:::

[]{#classgodot_1_1RGMap_ad15eb7048c2b0bdefcc22a6215e4eb36
label="classgodot_1_1RGMap_ad15eb7048c2b0bdefcc22a6215e4eb36"} void
**set_memorized** (Vector2 position, bool value)

::: DoxyCompactList
*Set memory state of cell.*
:::
:::
:::

::: Indent
**View and pathfinding**

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_abc95ec5b234f69d9f372483f22b8f602
label="classgodot_1_1RGMap_abc95ec5b234f69d9f372483f22b8f602"}
PoolVector2Array **rpas_calc_visible_cells_from** (Vector2 center, int
radius)

::: DoxyCompactList
*Get list of cells visible from position within radius using RPAS
algorithm.*
:::

[]{#classgodot_1_1RGMap_a449daffbdf681516e8a340e060edd0ef
label="classgodot_1_1RGMap_a449daffbdf681516e8a340e060edd0ef"} void
**calculate_fov** (Vector2 view_position, int max_distance)

::: DoxyCompactList
*Calculate visibility from given position and distance.*
:::

[]{#classgodot_1_1RGMap_a4a4b116053d6722cbb2bd325db94327e
label="classgodot_1_1RGMap_a4a4b116053d6722cbb2bd325db94327e"} void
**add_pathfinding_exception** (Vector2 position, bool value)

::: DoxyCompactList
*Allow/disallow patfinding for this cell ignoring passability.*
:::

[]{#classgodot_1_1RGMap_a6ec099f81053cdd7782a9ccac45ea54d
label="classgodot_1_1RGMap_a6ec099f81053cdd7782a9ccac45ea54d"} void
**remove_pathfinding_exception** (Vector2 position)

::: DoxyCompactList
*Remove all pathfinding exceptions for this cell if they exist.*
:::

PoolVector2Array
[show_pathfinding_exceptions](#classgodot_1_1RGMap_a637933f2b9bb946f4a7b295fddaaf452)
(bool exception_type)

::: DoxyCompactList
*Show all pathfinding exceptions of a type.*
:::

PoolVector2Array
[find_path](#classgodot_1_1RGMap_a0a0c87b9c381e59d241c298bbc7efd65)
(Vector2 start, Vector2 end, Rect2 pathfinding_zone, bool
exclude_undiscovered=false)

::: DoxyCompactList
*Find path from start to end using A$\ast$ algorithm.*
:::

PoolVector2Array
[get_line](#classgodot_1_1RGMap_af5df74ee697c11151876e230fcfc2c09)
(Vector2 start, Vector2 end, bool allow_diagonal=true)

::: DoxyCompactList
*Get a set of points in Bresenhams line.*
:::

[]{#classgodot_1_1RGMap_af8078e95e12994ce402bd4a3880008db
label="classgodot_1_1RGMap_af8078e95e12994ce402bd4a3880008db"} Vector2
**raycast_vision** (Vector2 start, Vector2 end)

::: DoxyCompactList
*Cast ray from start to end and return position where vision is blocked
by an obstacle.*
:::

[]{#classgodot_1_1RGMap_a71f82c2deaa4c5ea9ec5ca0e43176d4a
label="classgodot_1_1RGMap_a71f82c2deaa4c5ea9ec5ca0e43176d4a"} Vector2
**raycast_path** (Vector2 start, Vector2 end)

::: DoxyCompactList
*Cast ray from start to end and return position where path is blocked by
an obstacle.*
:::

bool
[visibility_between](#classgodot_1_1RGMap_aa0e99aed1a2d145536439b9a88b9ae30)
(Vector2 start, Vector2 end, int max_distance)

::: DoxyCompactList
*Check if end point is visisble from start point.*
:::
:::
:::

::: Indent
**Editing**

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_a831fb561ec538f9dd241174079927b62
label="classgodot_1_1RGMap_a831fb561ec538f9dd241174079927b62"} void
**clean_map** ()

::: DoxyCompactList
*Free all chunks and forget pathfinding exceptions.*
:::

[]{#classgodot_1_1RGMap_a6e4b777d25b43065a5e2092d084099ee
label="classgodot_1_1RGMap_a6e4b777d25b43065a5e2092d084099ee"} void
**place_map** ([RGMap](#classgodot_1_1RGMap) $\ast$another_map, Vector2
start)

::: DoxyCompactList
*Place another map inside this map.*
:::

[]{#classgodot_1_1RGMap_af9d1f6508a2ad834c7050d12759342fd
label="classgodot_1_1RGMap_af9d1f6508a2ad834c7050d12759342fd"} void
**draw_line** (Vector2 start, Vector2 end, int value, bool
allow_diagonal=true)

::: DoxyCompactList
*Draw straight line using Bresenhams line algorithm.*
:::

[]{#classgodot_1_1RGMap_a17af65d748b00d68c9403e6c016508c6
label="classgodot_1_1RGMap_a17af65d748b00d68c9403e6c016508c6"} void
**draw_rect** (Rect2 rect, int value)

::: DoxyCompactList
*Draw rect borders.*
:::

[]{#classgodot_1_1RGMap_a04245c368f06c61fad83c181b91592a6
label="classgodot_1_1RGMap_a04245c368f06c61fad83c181b91592a6"} void
**fill_rect** (Rect2 rect, int value)

::: DoxyCompactList
*Fill rect.*
:::

void
[draw_ellipse](#classgodot_1_1RGMap_ade0f1244d005d7440fe0d3731b863b36)
(Vector2 center, Vector2 radius, float start_angle, float end_angle, int
value, bool allow_diagonal=true)

::: DoxyCompactList
*Draw ellipse using Bresenhams midpoint algorithm.*
:::

[]{#classgodot_1_1RGMap_acc0515cfaf9bbe8d65c9c374899fd8f8
label="classgodot_1_1RGMap_acc0515cfaf9bbe8d65c9c374899fd8f8"} void
**fill_ellipse** (Vector2 center, Vector2 radius, float start_angle,
float end_angle, int value)

::: DoxyCompactList
*Fill ellipse.*
:::

[]{#classgodot_1_1RGMap_a366bf4bff59dfef02e8997f1b67a1eb5
label="classgodot_1_1RGMap_a366bf4bff59dfef02e8997f1b67a1eb5"} void
**draw_circle** (Vector2 center, float radius, int value, bool
allow_diagonal=true)

::: DoxyCompactList
*Draw circle.*
:::

[]{#classgodot_1_1RGMap_ade7a912c5bbcc60f398f16fd264dc464
label="classgodot_1_1RGMap_ade7a912c5bbcc60f398f16fd264dc464"} void
**fill_circle** (Vector2 center, float radius, int value)

::: DoxyCompactList
*Fill circle.*
:::

[]{#classgodot_1_1RGMap_ae123137e6645f64ac5b8a5fba6598e0f
label="classgodot_1_1RGMap_ae123137e6645f64ac5b8a5fba6598e0f"} void
**draw_arc** (Vector2 center, float radius, float start_angle, float
end_angle, int value, bool allow_diagonal=true)

::: DoxyCompactList
*Draw arc.*
:::

[]{#classgodot_1_1RGMap_ae51cf8952917fd840f67d62ce129df71
label="classgodot_1_1RGMap_ae51cf8952917fd840f67d62ce129df71"} void
**fill_arc** (Vector2 center, float radius, float start_angle, float
end_angle, int value)

::: DoxyCompactList
*Fill arc.*
:::
:::
:::

::: Indent
**Entities**

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_ae7a3643c8a808a0860b62dbd672d9311
label="classgodot_1_1RGMap_ae7a3643c8a808a0860b62dbd672d9311"} int
**add_entity** (Vector2 position, bool passability, bool transparency)

::: DoxyCompactList
*Add new entity to the map. Returns id given to a new entity.*
:::

[]{#classgodot_1_1RGMap_adf896538adc5e7bcd5f8cb584fe0cf5c
label="classgodot_1_1RGMap_adf896538adc5e7bcd5f8cb584fe0cf5c"} void
**remove_entity** (int id)

::: DoxyCompactList
*Remove entity from memory. The id of this entity will also be given to
a new entity.*
:::

[]{#classgodot_1_1RGMap_a8108573f1cf887b3f8263102ae2a3e39
label="classgodot_1_1RGMap_a8108573f1cf887b3f8263102ae2a3e39"} void
**move_entity** (int id, Vector2 position)

::: DoxyCompactList
*Move entity to a new position.*
:::

[]{#classgodot_1_1RGMap_a9c399e3eecf2729291e145b8f330b18b
label="classgodot_1_1RGMap_a9c399e3eecf2729291e145b8f330b18b"} void
**set_entity_transparency** (int id, bool value)

::: DoxyCompactList
*Change entity transparency.*
:::

[]{#classgodot_1_1RGMap_a30bc4ade51798b8208d17a33d890422d
label="classgodot_1_1RGMap_a30bc4ade51798b8208d17a33d890422d"} void
**set_entity_passability** (int id, bool value)

::: DoxyCompactList
*Change entity passability.*
:::

[]{#classgodot_1_1RGMap_a4dff79eace0ca3c3468429d71bf7b1b0
label="classgodot_1_1RGMap_a4dff79eace0ca3c3468429d71bf7b1b0"} void
**set_entity_memorized** (int id, bool value)

::: DoxyCompactList
*Change memory status of entity.*
:::

[]{#classgodot_1_1RGMap_a06d853a154fb9288f0eaa051cfd5c27f
label="classgodot_1_1RGMap_a06d853a154fb9288f0eaa051cfd5c27f"} bool
**is_entity_visible** (int id)

::: DoxyCompactList
*Check if entity is visible.*
:::

[]{#classgodot_1_1RGMap_aca51c1b240ff80577646ddbe74edf31b
label="classgodot_1_1RGMap_aca51c1b240ff80577646ddbe74edf31b"} bool
**is_entity_transparent** (int id)

::: DoxyCompactList
*Check if entity is transparent;.*
:::

[]{#classgodot_1_1RGMap_a712b3f1d95d44c000949829def9b6e91
label="classgodot_1_1RGMap_a712b3f1d95d44c000949829def9b6e91"} bool
**is_entity_passable** (int id)

::: DoxyCompactList
*Check if entity is passable.*
:::

[]{#classgodot_1_1RGMap_abe18e0c06bc081071a56d9d216186421
label="classgodot_1_1RGMap_abe18e0c06bc081071a56d9d216186421"} bool
**is_entity_memorized** (int id)

::: DoxyCompactList
*Check if entity is memorized.*
:::

[]{#classgodot_1_1RGMap_a97be562b35c3daf51f49e134b93dbc9d
label="classgodot_1_1RGMap_a97be562b35c3daf51f49e134b93dbc9d"} bool
**is_entity_chunk_loaded** (int id)

::: DoxyCompactList
*Check if entity is on loaded chunk.*
:::

[]{#classgodot_1_1RGMap_a0a39e73b2e10796ffe72c590f3347989
label="classgodot_1_1RGMap_a0a39e73b2e10796ffe72c590f3347989"} bool
**is_entity_chunk_rendered** (int id)

::: DoxyCompactList
*Check if entity is on rendered chunk.*
:::

[]{#classgodot_1_1RGMap_a000af6feda1d67bcc014fc52a5871e50
label="classgodot_1_1RGMap_a000af6feda1d67bcc014fc52a5871e50"} Vector2
**get_entity_position** (int id)

::: DoxyCompactList
*Get position of the entity.*
:::

[]{#classgodot_1_1RGMap_a1030a2d395f2773dba6950096d60fdf9
label="classgodot_1_1RGMap_a1030a2d395f2773dba6950096d60fdf9"}
PoolIntArray **get_entities_in_position** (Vector2 position)

::: DoxyCompactList
*Find ids of all entities in position.*
:::

[]{#classgodot_1_1RGMap_a2742fb3f44caa25d078abe67feec9d77
label="classgodot_1_1RGMap_a2742fb3f44caa25d078abe67feec9d77"}
PoolIntArray **get_entities_in_rect** (Rect2 rect)

::: DoxyCompactList
*Find ids of all entities in rect.*
:::

[]{#classgodot_1_1RGMap_a74c42c8fc68967a33b970c27457e9abf
label="classgodot_1_1RGMap_a74c42c8fc68967a33b970c27457e9abf"}
PoolIntArray **get_entities_in_radius** (Vector2 position, int radius)

::: DoxyCompactList
*Find ids of all entities in radius.*
:::

[]{#classgodot_1_1RGMap_a3101593907cf4928bbffc94a1e5f950f
label="classgodot_1_1RGMap_a3101593907cf4928bbffc94a1e5f950f"}
PoolIntArray **get_entities_in_chunk** (int chunk_index)

::: DoxyCompactList
*Find ids of all entities in chunk.*
:::
:::
:::

::: Indent
**Saving and Loading**

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_a673f7f9e37f280588ccff46b1f46d38e
label="classgodot_1_1RGMap_a673f7f9e37f280588ccff46b1f46d38e"}
PoolIntArray **dump_map_data** ()

::: DoxyCompactList
*Save map data.*
:::

[]{#classgodot_1_1RGMap_aa2accf67955f8a3fb5fb30a649e6132d
label="classgodot_1_1RGMap_aa2accf67955f8a3fb5fb30a649e6132d"} void
**load_map_data** (PoolIntArray map_data)

::: DoxyCompactList
*Load map data.*
:::
:::
:::

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_a3fba15a031ad1bd976b281cefe90bc79
label="classgodot_1_1RGMap_a3fba15a031ad1bd976b281cefe90bc79"} Vector2
**chunk_size** = Vector2(50,50)

::: DoxyCompactList
*Size of one chunk (Default: 50x50)*
:::

[]{#classgodot_1_1RGMap_a4a8e96884242e6b83b2417d127a814a8
label="classgodot_1_1RGMap_a4a8e96884242e6b83b2417d127a814a8"} Vector2
**size** = Vector2(3,3)

::: DoxyCompactList
*Size of the whole map in chunks (Default: 3x3)*
:::

int
[load_distance](#classgodot_1_1RGMap_ab097624100d11699293844ead170dab9)
= 1

::: DoxyCompactList
*Number of chunks loaded around the player.*
:::

int
[render_distance](#classgodot_1_1RGMap_aef65b060d5dbda0c47f00d2431921b49)
= 1

::: DoxyCompactList
*Number of chunks rendered around the player.*
:::

[]{#classgodot_1_1RGMap_a092151ec6eda7be42513f17eb9ebfe1f
label="classgodot_1_1RGMap_a092151ec6eda7be42513f17eb9ebfe1f"} bool
**allow_diagonal_pathfinding** = true

::: DoxyCompactList
*Allow/Disallow diagonal pathfinding.*
:::
:::

::: Indent
**FOV**

*Variables related to FOV calculation using RPAS algorithm*

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_ad6b261d97c61db7c511faa45905eea3d
label="classgodot_1_1RGMap_ad6b261d97c61db7c511faa45905eea3d"} float
**RPAS_RADIUS_FUDGE** = 1. / 3.

::: DoxyCompactList
*How smooth the edges of the vision bubble are. Between 0 and 1.*
:::

[]{#classgodot_1_1RGMap_abfab661cb4533aee01402a3a7b1acb7b
label="classgodot_1_1RGMap_abfab661cb4533aee01402a3a7b1acb7b"} bool
**RPAS_NOT_VISIBLE_BLOCKS_VISION** = true

::: DoxyCompactList
*If this is false, some cells will unexpectedly be visible.*
:::

int
[RPAS_RESTRICTIVENESS](#classgodot_1_1RGMap_a98a2a7a44cf00487360159e89be37401)
= 1

::: DoxyCompactList
*Determines how restrictive the algorithm is.*
:::

[]{#classgodot_1_1RGMap_ac743a18b1c2c2193e92aac307f1c1478
label="classgodot_1_1RGMap_ac743a18b1c2c2193e92aac307f1c1478"} bool
**RPAS_VISIBLE_ON_EQUAL** = true

::: DoxyCompactList
*If false, an obstruction will obstruct its endpoints.*
:::
:::
:::

::: DoxyCompactItemize
[]{#classgodot_1_1RGMap_a07f1fef452ab37ad0bc6a5a46ed65834
label="classgodot_1_1RGMap_a07f1fef452ab37ad0bc6a5a46ed65834"} **RGMap**
()

[]{#classgodot_1_1RGMap_aa2f66b3c45e245abd84fca56ae7097a2
label="classgodot_1_1RGMap_aa2f66b3c45e245abd84fca56ae7097a2"}
**$\sim$RGMap** ()

[]{#classgodot_1_1RGMap_a6a124ddb92eb57514b32f106babd40eb
label="classgodot_1_1RGMap_a6a124ddb92eb57514b32f106babd40eb"} void
**\_init** ()

[]{#classgodot_1_1RGMap_af167d83fed1892421dd86f2089d45fef
label="classgodot_1_1RGMap_af167d83fed1892421dd86f2089d45fef"} static
void **\_register_methods** ()
:::

Class for managing maps for roguelike.

[]{#classgodot_1_1RGMap_ade0f1244d005d7440fe0d3731b863b36
label="classgodot_1_1RGMap_ade0f1244d005d7440fe0d3731b863b36"}

void RGMap::draw_ellipse (

::: DoxyParamCaption
center,

radius,

start_angle,

end_angle,

value,

allow_diagonal = true
:::

)

Draw ellipse using Bresenhams midpoint algorithm.

Tweaked version of code from here:
[` https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/`](https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/)
[]{#classgodot_1_1RGMap_a0a0c87b9c381e59d241c298bbc7efd65
label="classgodot_1_1RGMap_a0a0c87b9c381e59d241c298bbc7efd65"}

PoolVector2Array RGMap::find_path (

::: DoxyParamCaption
start,

end,

pathfinding_zone,

exclude_undiscovered = false
:::

)

Find path from start to end using A$\ast$ algorithm.

Returns PoolVector2Array

::: DoxyParams
Parameters *start* & Start point\
*end* & Target point\
*pathfinding_zone* & Rect2 zone where pathfinding is calculated\
*exclude_undiscovered* & True to exclude undiscovered cells (Fefault:
False)\
:::

[]{#classgodot_1_1RGMap_a819587d899569b840a3f417aa9fd0c2f
label="classgodot_1_1RGMap_a819587d899569b840a3f417aa9fd0c2f"}

Ref$<$ TileSet $>$ RGMap::generate_tileset (

::: DoxyParamCaption
texture_path,

texture_format
:::

)

Generate Tileset for using with 2d Tilemap.

::: DoxyParams
Parameters *texture_path* & A directory within the project where
textures are stored (e.g '̈res://Textures/'̈)\
*texture_format* & A format of textures (e.g '̈.png'̈)\
:::

[]{#classgodot_1_1RGMap_ad292a1d8e79b597004643fbcf2e588f8
label="classgodot_1_1RGMap_ad292a1d8e79b597004643fbcf2e588f8"}

PoolIntArray RGMap::get_chunks_to_free (

::: DoxyParamCaption
player_position
:::

)

Get ids of chunks that are loaded, but not needed anymore because player
is too far.

::: DoxyParams
Parameters *player_position* & Vector2 position of the player Uses
load_distance parameter to define the radius\
:::

[]{#classgodot_1_1RGMap_a251886c67ff84873042b83e836585203
label="classgodot_1_1RGMap_a251886c67ff84873042b83e836585203"}

PoolIntArray RGMap::get_chunks_to_hide (

::: DoxyParamCaption
player_position
:::

)

Get ids of chunks that are rendered, but not needed anymore because
player is too far.

::: DoxyParams
Parameters *player_position* & Vector2 position of the player Uses
render_distance parameter to define the radius\
:::

[]{#classgodot_1_1RGMap_af81558e0a4b18590aea6f385f6fa345f
label="classgodot_1_1RGMap_af81558e0a4b18590aea6f385f6fa345f"}

PoolIntArray RGMap::get_chunks_to_load (

::: DoxyParamCaption
player_position
:::

)

Get ids of chunks around player that needs to be loaded.

::: DoxyParams
Parameters *player_position* & Vector2 position of the player Uses
load_distance parameter to define the radius Skips chunks that were
already loaded\
:::

[]{#classgodot_1_1RGMap_a742bfc37a17e36f017d52f2bac8b698f
label="classgodot_1_1RGMap_a742bfc37a17e36f017d52f2bac8b698f"}

PoolIntArray RGMap::get_chunks_to_render (

::: DoxyParamCaption
player_position
:::

)

Get ids of chunks around player that needs to be rendered.

::: DoxyParams
Parameters *player_position* & Vector2 position of the player Uses
render_distance parameter to define the radius Skips chunks that were
already rendered\
:::

[]{#classgodot_1_1RGMap_af5df74ee697c11151876e230fcfc2c09
label="classgodot_1_1RGMap_af5df74ee697c11151876e230fcfc2c09"}

PoolVector2Array RGMap::get_line (

::: DoxyParamCaption
start,

end,

allow_diagonal = true
:::

)

Get a set of points in Bresenhams line.

Based on Python implementation from here:
[` http://www.roguebasin.com/index.php/Bresenham%27s_Line_Algorithm`](http://www.roguebasin.com/index.php/Bresenham%27s_Line_Algorithm)
[]{#classgodot_1_1RGMap_af97b719797501ed8525d3aad37ed83d7
label="classgodot_1_1RGMap_af97b719797501ed8525d3aad37ed83d7"}

void RGMap::request_chunks_render (

::: DoxyParamCaption
player_position
:::

)

Request chunk render/hide depending on player_position and
render_distance.

Emits '̈chunks_render_requested'̈ and '̈chunks_hide_requested'̈ signals Will
produce the same result until chunks will be rendered/hidden from other
script Does nothing if all needed chunks are rendered and all unneeded
chunks are hidden

::: DoxyParams
Parameters *player_position* & Vector2 position of the player Uses
render_distance parameter to define the radius\
:::

[]{#classgodot_1_1RGMap_a2c565c4b9124368ebdaae851afd13585
label="classgodot_1_1RGMap_a2c565c4b9124368ebdaae851afd13585"}

void RGMap::request_chunks_update (

::: DoxyParamCaption
player_position
:::

)

Request chunk load/unload depending on player_position and
load_distance.

Emits '̈chunks_load_requested'̈ and '̈chunks_free_requested'̈ signals Will
produce the same result until chunks will be loaded/freed from other
script Does nothing if all needed chunks are loaded and all unneeded
chunks are freed

::: DoxyParams
Parameters *player_position* & Vector2 position of the player Uses
load_distance parameter to define the radius\
:::

[]{#classgodot_1_1RGMap_a637933f2b9bb946f4a7b295fddaaf452
label="classgodot_1_1RGMap_a637933f2b9bb946f4a7b295fddaaf452"}

PoolVector2Array RGMap::show_pathfinding_exceptions (

::: DoxyParamCaption
exception_type
:::

)

Show all pathfinding exceptions of a type.

::: DoxyParams
Parameters *exception_type* & true for allowed cells, false for
disallowed cells\
:::

[]{#classgodot_1_1RGMap_aa0e99aed1a2d145536439b9a88b9ae30
label="classgodot_1_1RGMap_aa0e99aed1a2d145536439b9a88b9ae30"}

bool RGMap::visibility_between (

::: DoxyParamCaption
start,

end,

max_distance
:::

)

Check if end point is visisble from start point.

::: DoxyParams
Parameters *start* & Start point\
*end* & Target point\
*max_distance* & Maximum distance at which points are visible\
:::

[]{#classgodot_1_1RGMap_ab097624100d11699293844ead170dab9
label="classgodot_1_1RGMap_ab097624100d11699293844ead170dab9"} int
godot::RGMap::load_distance = 1

Number of chunks loaded around the player.

Excluding the chunk where player stands Default: 1 (3x3 grid)
[]{#classgodot_1_1RGMap_aef65b060d5dbda0c47f00d2431921b49
label="classgodot_1_1RGMap_aef65b060d5dbda0c47f00d2431921b49"} int
godot::RGMap::render_distance = 1

Number of chunks rendered around the player.

Excluding the chunk where player stands Default: 1 (3x3 grid)
[]{#classgodot_1_1RGMap_a98a2a7a44cf00487360159e89be37401
label="classgodot_1_1RGMap_a98a2a7a44cf00487360159e89be37401"} int
godot::RGMap::RPAS_RESTRICTIVENESS = 1

Determines how restrictive the algorithm is.

0 - if you have a line to the near, center, or far, it will return as
visible   - if you have a line to the center and at least one other
corner it will return as visible   - if you have a line to all the near,
center, and far, it will return as visible

The documentation for this class was generated from the following files:

::: DoxyCompactItemize
/home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/rgmap.h

/home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/cells.cpp

/home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/chunks.cpp

/home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/editing.cpp

/home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/entities.cpp

/home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/rgmap.cpp

/home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/rpas.cpp

/home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/tiles.cpp

/home/data/Documents/Gamedev/Godot/GDNative/godot-rgmap/addons/godot-rgmap/native/src/view.cpp
:::

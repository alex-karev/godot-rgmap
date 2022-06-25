extends Control
export var map_size = Vector2(3000,3000)
export var chunk_size = Vector2(10,10)
export var player_position_center = true
export var player_position = Vector2(5,5)

var rgmap: RGMap
var rgtileset: RGTileset
var ready = true
var player_path = []
var noise: OpenSimplexNoise
var visible_zone: Rect2

func _ready():
	# Initialization
	## Create new RGTileset
	rgtileset = RGTileset.new()
	rgtileset.add_tile("ocean", "Ocean", false, true)
	rgtileset.add_tile("grass", "Grass", true, true) # true for passable and true for transparent
	rgtileset.add_tile("wall", "Wall", false, false)
	## Generate tileset
	var tileset = rgtileset.generate_tileset("res://Textures/", ".png")
	$Visible.tile_set = tileset
	$Memorized.tile_set = tileset
	## Create new RGMap
	rgmap = RGMap.new()
	rgmap.allow_diagonal_pathfinding = true
	rgmap.size = map_size
	rgmap.chunk_size = chunk_size
	rgmap.initialize(rgtileset)
	## Move player and update visible zone
	if player_position_center:
		player_position = (map_size*chunk_size/2).floor()
	$Camera.position = player_position*16
	update_visible_zone()
	## Generate noize
	noise = OpenSimplexNoise.new()
	noise.seed = 1
	noise.period = 10
	## Generate and draw nearby chunks
	update_map()
	
	# Drawing
	# NOTE: This drawings will dissapear once chunks with them are removed from memory
	# To save and load chunks use dump_chunk_data and load_chunk functions
	# Saving and loading chunks is not implemented in this demo
	# Get tile indexes
	var wall_index = rgtileset.get_index("wall")
	var grass_index = rgtileset.get_index("grass")
	# Draw floor
	rgmap.fill_circle(player_position, 10, grass_index)
	# Draw room
	rgmap.draw_rect(Rect2(Vector2(-5,-5)+player_position, Vector2(10,10)), wall_index)
	rgmap.set_value(Vector2(0,4)+player_position, grass_index)

	# Redraw map
	update_map()

# Update visible_zone Rect2
func update_visible_zone():
	var visible_zone_size = (get_viewport().size/16).floor()
	var visible_zone_position = (player_position - visible_zone_size/2).floor()
	visible_zone = Rect2(visible_zone_position, visible_zone_size)

# Draw tiles
func update_map():
	var wall_index = rgtileset.get_index("wall")
	var grass_index = rgtileset.get_index("grass")
	# Load chunks
	for chunk_index in rgmap.get_chunks_to_load(player_position):
		var start = rgmap.chunk_index_int_to_v2(chunk_index)*chunk_size
		# Loop through each cell
		for x in chunk_size.x:
			for y in chunk_size.y:
				var pos = Vector2(x,y)+start
				# Generate values from noise
				var noise_value = noise.get_noise_2dv(pos)
				if noise_value < 0.2:
					rgmap.set_value(pos, grass_index)
				else:
					rgmap.set_value(pos, wall_index)
	# Recalculate fov
	rgmap.calculate_fov(player_position, 60)
	# Draw chunks on tilemap
	for chunk_index in rgmap.get_loaded_chunks():
		var start = rgmap.chunk_index_int_to_v2(chunk_index)*chunk_size
		for x in chunk_size.x:
			for y in chunk_size.y:
				var pos = Vector2(x,y)+start
				# Clear cells
				$Visible.set_cellv(pos,-1)
				$Memorized.set_cellv(pos, -1)
				# Draw cells
				var value = rgmap.get_value(pos)
				if rgmap.is_visible(pos):
					$Visible.set_cellv(pos, value)
				elif rgmap.is_memorized(pos):
					$Memorized.set_cellv(pos, value)
	# Free chunks and clear cells
	for chunk_index in rgmap.get_chunks_to_free(player_position):
		rgmap.free_chunk(chunk_index);
		var start = rgmap.chunk_index_int_to_v2(chunk_index)*chunk_size
		for x in chunk_size.x:
			for y in chunk_size.y:
				var pos = Vector2(x,y)+start
				$Visible.set_cellv(pos, -1)
				$Memorized.set_cellv(pos, -1)
	# Draw player
	$Player.position = player_position*16+Vector2.ONE*8

# Move player using pathfinding
func _process(delta):
	# Update visible zone
	update_visible_zone()
	# Move camera
	$Camera.position = $Camera.position.linear_interpolate(player_position*16, delta*10)
	# Calculate target position and move cursor
	var mousepos = get_global_mouse_position()
	var target = Vector2(floor(mousepos.x/16), floor(mousepos.y/16))
	$Cursor.position = target*16+Vector2(8,8)
	# Check if target is known and passable
	if !rgmap.is_passable(target) or !rgmap.is_memorized(target):
		$Cursor.play("cross")
		return
	else: $Cursor.play("default")
	# On mouse click calculate path: and start timer
	if Input.is_action_just_pressed("move") and ready:
		for point in rgmap.find_path(player_position, target, visible_zone):
			player_path.append(point)
		ready = false
		$Cursor.hide()
		$Update.start()

# Render move
func _on_Update_timeout():
	if player_path.size() > 0:
		player_position = player_path[0]
		player_path.pop_front()
		update_map()
		$Update.start()
	else:
		ready = true
		$Cursor.show()

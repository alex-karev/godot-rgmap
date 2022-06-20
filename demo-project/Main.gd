extends Control

export var player_position = Vector2(5,5)
export var fov_radius = 10
export var map_size = Vector2(50,70)

var rgmap: RGMap 
var rgtileset: RGTileset
var ready = true
var player_path = []

func _ready():
	# Initialization
	## Create new RGTileset
	rgtileset = RGTileset.new()
	rgtileset.add_tile("grass", "Grass", true, true) # true for passable and true for transparent
	rgtileset.add_tile("wall", "Wall", false, false)
	## Create new RGMap
	rgmap = RGMap.new()
	rgmap.allowDiagonalPathfinding = true
	rgmap.size = map_size
	rgmap.initialize(rgtileset)
	
	# Drawing
	# Get tile indexes
	var wall_index = rgtileset.get_index("wall")
	var grass_index = rgtileset.get_index("grass")
	# Draw room
	rgmap.draw_rect(Rect2(Vector2(2,2), Vector2(10,10)), wall_index)
	rgmap.set_value(Vector2(7,11), grass_index)
	# Draw lines
	rgmap.draw_line(Vector2(18,15), Vector2(45,25), wall_index)
	rgmap.draw_line(Vector2(18,25), Vector2(28,35), wall_index, true)
	# Note: true/false at the end of draw functions means allowing/disallowing diagonal step
	# Draw arena
	rgmap.fill_rect(Rect2(Vector2(2,20),Vector2(13,9)), wall_index)
	rgmap.fill_ellipse(Vector2(8,24), Vector2(5,3), -PI, PI, grass_index)
	rgmap.draw_line(Vector2(7,20),Vector2(7,21), grass_index)
	# Draw semicircles
	rgmap.draw_arc(Vector2(10,35), 3, -PI, PI/2, wall_index, true)
	rgmap.fill_arc(Vector2(10,45), 3, PI/2, -PI/2, wall_index)
	rgmap.draw_arc(Vector2(20,38), 4, -PI, PI/2, wall_index, false)
	
	# Initial map draw
	generate_tileset()
	draw()

# Move player using pathfinding
func _process(delta):
	# Calculate target position and move cursor
	var mousepos = get_global_mouse_position()
	var target = Vector2(floor(mousepos.x/16), floor(mousepos.y/16))
	$Cursor.position = target*16+Vector2(8,8)
	# On mouse click calculate path: and start timer
	if Input.is_action_just_pressed("move") and ready:
		for point in rgmap.find_path(player_position, target):
			if rgmap.is_passable(point):
				player_path.append(point)
		ready = false
		$Cursor.hide()
		$Update.start()
	# Move camera
	$Camera.position = $Camera.position.linear_interpolate(player_position*16, delta*10)

# Generate Tileset
func generate_tileset():
	var tileset = TileSet.new()
	for i in rgtileset.get_tiles_count():
		tileset.create_tile(i)
		var tile_name = rgtileset.get_name(i)
		var texture = load("res://Textures/"+tile_name+".png")
		tileset.tile_set_texture(i, texture)
	tileset.create_tile(rgtileset.get_tiles_count())
	var texture = load("res://Textures/player.png")
	tileset.tile_set_texture(rgtileset.get_tiles_count(), texture)
	$Visible.tile_set = tileset
	$Memorized.tile_set = tileset
	
# Draw tiles
func draw():
	# Calculate fov
	rgmap.calculate_fov(player_position, 10)
	for x in rgmap.size.x:
		for y in rgmap.size.y:
			var pos = Vector2(x,y)
			var value = rgmap.get_value(pos)
			# Clean map
			$Visible.set_cellv(pos, -1)
			$Memorized.set_cellv(pos, -1)
			# Set values
			if rgmap.is_visible(pos):
				$Visible.set_cellv(pos, value)
			elif rgmap.is_memorized():
				$Memorized.set_cellv(pos, value)
	# Show player
	$Visible.set_cellv(player_position, rgtileset.get_tiles_count())

# Render move
func _on_Update_timeout():
	if player_path.size() > 0:
		player_position = player_path[0]
		player_path.pop_front()
		draw()
	else:
		ready = true
		$Cursor.show()

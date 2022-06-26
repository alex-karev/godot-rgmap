extends Node2D
export(NodePath) var rgmap_path
export var player_position_center = true
export var player_position = Vector2(5,5)
var rgmap: RGMap
var visible_zone: Rect2
var ready = true
var player_path = []

func _ready():
	# Connect nodes
	rgmap = get_node(rgmap_path)
	# Move player and update visible zone
	if player_position_center:
		player_position = (rgmap.size*rgmap.chunk_size/2).floor()
	$Player.position = player_position*16+Vector2.ONE*8
	$Camera.position = player_position*16
	update_visible_zone()
	# Request chunk update
	rgmap.request_chunks_update(player_position)

# Update visible_zone Rect2
func update_visible_zone():
	var visible_zone_size = (get_viewport().size/16).floor()
	var visible_zone_position = (player_position - visible_zone_size/2).floor()
	visible_zone = Rect2(visible_zone_position, visible_zone_size)

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
		# Move player
		player_position = player_path[0]
		$Player.position = player_position*16+Vector2.ONE*8
		player_path.pop_front()
		# Update map
		rgmap.request_chunks_update(player_position)
		# Restart timer
		$Update.start()
	else:
		ready = true
		$Cursor.show()

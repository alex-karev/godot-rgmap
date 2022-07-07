extends Node2D

export(NodePath) var rgmap_path
export(NodePath) var rgtileset_path
export(NodePath) var controller_path
var rgmap: RGMap
var noise: OpenSimplexNoise
var controller
var trees = PoolIntArray([])

func _ready():
	# Connect nodes
	controller = get_node(controller_path)
	rgmap = get_node(rgmap_path)
	
	# Connect signals
	# Note: Signals are already connected in editor
	# Alternatively they can be connected like this:
	#rgmap.connect("chunk_load_requested", self, "_on_RGMap_chunk_load_requested")
	
	# Add tiles to RGTileset
	rgmap.add_tile("ocean", "Ocean")
	rgmap.set_tile_passability(0, false)
	rgmap.set_tile_transparency(0, true)
	rgmap.set_tile_texture(0, load("res://addons/godot-rgmap/demo/Textures/ocean.png"))
	rgmap.set_tile_material(0, load("res://addons/godot-rgmap/demo/water.material"))
	rgmap.add_tile("grass", "Grass")
	rgmap.set_tile_passability(1, true)
	rgmap.set_tile_transparency(1, true)
	rgmap.set_tile_texture(1, load("res://addons/godot-rgmap/demo/Textures/grass.png"))
	rgmap.add_tile("wall", "Wall")
	rgmap.set_tile_passability(2, false)
	rgmap.set_tile_transparency(2, false)
	rgmap.set_tile_texture(2, load("res://addons/godot-rgmap/demo/Textures/wall.png"))
	
	# Generate 2d TileSet for Tilemap
	var tileset = rgmap.generate_tileset()
	$Tilemap.tile_set = tileset

	# Generate noize
	noise = OpenSimplexNoise.new()
	noise.seed = 1
	noise.period = 10
	
	# Set player position
	controller.player_position = (rgmap.size*rgmap.chunk_size/2).floor()
	# Add some trees
	var rng = RandomNumberGenerator.new()
	for i in range(2000):
		var x = rng.randi_range(-100,100)
		var y = rng.randi_range(-100,100)
		var tree_pos = controller.player_position+Vector2(x,y)
		if noise.get_noise_2dv(tree_pos) > -0.3 \
		and noise.get_noise_2dv(tree_pos) < 0.2:
			# Add entity to rgmap
			# So it will be considered while calculating FOV and pathfinding
			# Unlike tiles, there can be multiple entities in one place
			# Entities can move, change transparency and passability
			var tree_id = rgmap.add_entity(tree_pos, false, false) # false for passability and false for transparency
			trees.append(tree_id)
			# Note: add_entity creates an entity and returns its unique id
			# Save this id if you want to access it later
			# For example: rgmap.move_entity(4, Vector2(0,0)) 
			# Will move entity with id 4 to Vector2(0,0)
	
# Generate new chunks. Emited after request_chunks_load of RGMap function was called
func _on_RGMap_chunks_load_requested(ids):
	# Define tile ids
	var ocean_index = rgmap.get_tile_index("ocean")
	var wall_index = rgmap.get_tile_index("wall")
	var grass_index = rgmap.get_tile_index("grass")
	# Loop through all chunks
	for id in ids:
		# Find top left corner of chunk
		var start = rgmap.chunk_index_int_to_v2(id)*rgmap.chunk_size
		# Loop through each cell
		for x in rgmap.chunk_size.x:
			for y in rgmap.chunk_size.y:
				var pos = Vector2(x,y)+start
				# Generate values from noise
				var noise_value = noise.get_noise_2dv(pos)
				if noise_value < -0.3:
					rgmap.set_value(pos, ocean_index)
				elif noise_value < 0.2:
					rgmap.set_value(pos, grass_index)
				else:
					rgmap.set_value(pos, wall_index)
	# Recalculate FOV after loading all chunks
	rgmap.calculate_fov(controller.player_position)
	# Request chunk rendering
	rgmap.request_chunks_render(controller.player_position)

# Remove unneeded chunks. Emited after request_chunks_load of RGMap function was called
func _on_RGMap_chunks_free_requested(ids):
	for id in ids:
		# Free chunk
		rgmap.free_chunk(id)
		# Note: Additionaly you can save chunk's data using dump_chunk_data
		# And later restore it using load_chunk(index,data) in chunks_load_requested

# Render chunks. Emited after request_chunks_render of RGMap function was called
func _on_RGMap_chunks_render_requested(ids):
	for id in ids:
		# Find top left corner of chunk
		var start = rgmap.chunk_index_int_to_v2(id)*rgmap.chunk_size
		# Loop through each cell
		for x in rgmap.chunk_size.x:
			for y in rgmap.chunk_size.y:
				var pos = Vector2(x,y)+start
				var value = rgmap.get_value(pos)
				$Tilemap.set_cellv(pos, value)
		# Update rendering status
		rgmap.set_chunk_rendered(id, true)
	# Draw fog and sprites
	for id in rgmap.get_rendered_chunks():
		# Find top left corner of chunk
		var start = rgmap.chunk_index_int_to_v2(id)*rgmap.chunk_size
		# Loop through each cell
		for x in rgmap.chunk_size.x:
			for y in rgmap.chunk_size.y:
				var pos = Vector2(x,y)+start
				# Set values
				if rgmap.is_visible(pos):
					$Fog.set_cellv(pos, -1)
				elif rgmap.is_discovered(pos):
					$Fog.set_cellv(pos, 1)
				else:
					$Fog.set_cellv(pos, 0)
		# Show entities
		for tree_id in rgmap.get_entities_in_chunk(id):
			var node_name = "Tree"+str(tree_id)
			if not has_node(node_name) \
			and rgmap.is_entity_discovered(tree_id):
				# Create new sprite
				var tree = Sprite.new()
				tree.name = node_name
				tree.texture = load("res://addons/godot-rgmap/demo/Textures/tree.png")
				tree.position = rgmap.get_entity_position(tree_id)*16+Vector2.ONE*8
				add_child(tree)	
			
# Hide chunks that are not needed to be rendered. Emited after request_chunks_render of RGMap function was called
func _on_RGMap_chunks_hide_requested(ids):
	for id in ids:
		# Find top left corner of chunk
		var start = rgmap.chunk_index_int_to_v2(id)*rgmap.chunk_size
		# Loop through each cell
		for x in rgmap.chunk_size.x:
			for y in rgmap.chunk_size.y:
				var pos = Vector2(x,y)+start
				# Clear cell
				$Tilemap.set_cellv(pos, -1)
				$Fog.set_cellv(pos, -1)
		# Update rendering status
		rgmap.set_chunk_rendered(id, false)
		# Free entities
		for tree_id in rgmap.get_entities_in_chunk(id):
			var node_name = "Tree"+str(tree_id)
			if has_node(node_name):
				get_node(node_name).queue_free()

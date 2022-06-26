extends Node2D

export(NodePath) var rgmap_path
export(NodePath) var rgtileset_path
export(NodePath) var controller_path
var rgmap: RGMap
var rgtileset: RGTileset
var noise: OpenSimplexNoise
var controller

func _ready():
	# Connect nodes
	controller = get_node(controller_path)
	rgmap = get_node(rgmap_path)
	rgtileset = get_node(rgtileset_path)
	
	# Connect signals
	# Note: Signals are already connected in editor
	# Alternatively they can be connected like this:
	#rgmap.connect("chunk_load_requested", self, "_on_RGMap_chunk_load_requested")
	#rgmap.connect("chunk_free_requested", self, "_on_RGMap_chunk_load_requested")
	
	# Add tiles to RGTileset
	rgtileset.add_tile("ocean", "Ocean", false, true)
	rgtileset.add_tile("grass", "Grass", true, true) # true for passable and true for transparent
	rgtileset.add_tile("wall", "Wall", false, false)
	# Generate 2d TileSet for Tilemaps
	var tileset = rgtileset.generate_tileset("res://Textures/",".png")
	$Memorized.tile_set = tileset
	$Visible.tile_set = tileset

	# Initialize RGMap with RGTileset
	rgmap.initialize(rgtileset)

	# Generate noize
	noise = OpenSimplexNoise.new()
	noise.seed = 1
	noise.period = 10

# Generate new chunks. Emited after request_chunks_update of RGMap function was called
func _on_RGMap_chunks_load_requested(ids):
	# Define tile ids
	var ocean_index = rgtileset.get_index("ocean")
	var wall_index = rgtileset.get_index("wall")
	var grass_index = rgtileset.get_index("grass")
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
	rgmap.calculate_fov(controller.player_position, 60)
	# Draw tiles
	draw()

# Draw tiles
func draw():
	# Draw tiles
	for id in rgmap.get_loaded_chunks():
		# Find top left corner of chunk
		var start = rgmap.chunk_index_int_to_v2(id)*rgmap.chunk_size
		# Loop through each cell
		for x in rgmap.chunk_size.x:
			for y in rgmap.chunk_size.y:
				var pos = Vector2(x,y)+start
				# Clear previous values
				$Memorized.set_cellv(pos, -1)
				$Visible.set_cellv(pos, -1)
				# Set values
				var value = rgmap.get_value(pos)
				if rgmap.is_visible(pos):
					$Visible.set_cellv(pos, value)
				elif rgmap.is_memorized(pos):
					$Memorized.set_cellv(pos, value)


# Remove unneeded chunks. Emited after request_chunks_update of RGMap function was called
func _on_RGMap_chunks_free_requested(ids):
	for id in ids:
		# Free chunk
		rgmap.free_chunk(id)
		# Note: Additionaly you can save chunk's data using dump_chunk_data
		# And later restore it using load_chunk(index,data) in chunks_load_requested
		
		# Clear cells
		var start = rgmap.chunk_index_int_to_v2(id)*rgmap.chunk_size
		# Loop through each cell
		for x in rgmap.chunk_size.x:
			for y in rgmap.chunk_size.y:
				var pos = Vector2(x,y)+start
				$Memorized.set_cellv(pos, -1)
				$Visible.set_cellv(pos, -1)

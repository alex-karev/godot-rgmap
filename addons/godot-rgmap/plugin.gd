tool
extends EditorPlugin

func _enter_tree():
	add_custom_type("RGMap", "Node", load("res://addons/godot-rgmap/native/RGMap.gdns"), load("res://addons/godot-rgmap/rgmap.png"))

func _exit_tree():
	remove_custom_type("RGMap")

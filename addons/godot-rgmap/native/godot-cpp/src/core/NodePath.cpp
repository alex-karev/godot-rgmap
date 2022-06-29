/*************************************************************************/
/*  NodePath.cpp                                                         */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "NodePath.hpp"
#include "GodotGlobal.hpp"
#include "String.hpp"

#include <gdnative/node_path.h>

namespace godot {

NodePath::NodePath() {
	String from = "";
	godot::api->godot_node_path_new(&_node_path, (godot_string *)&from);
}

NodePath::NodePath(const NodePath &other) {
	String from = other;
	godot::api->godot_node_path_new(&_node_path, (godot_string *)&from);
}

NodePath::NodePath(const String &from) {
	godot::api->godot_node_path_new(&_node_path, (godot_string *)&from);
}

NodePath::NodePath(const char *contents) {
	String from = contents;
	godot::api->godot_node_path_new(&_node_path, (godot_string *)&from);
}

String NodePath::get_name(const int idx) const {
	godot_string str = godot::api->godot_node_path_get_name(&_node_path, idx);
	return String(str);
}

int NodePath::get_name_count() const {
	return godot::api->godot_node_path_get_name_count(&_node_path);
}

String NodePath::get_subname(const int idx) const {
	godot_string str = godot::api->godot_node_path_get_subname(&_node_path, idx);
	return String(str);
}

int NodePath::get_subname_count() const {
	return godot::api->godot_node_path_get_subname_count(&_node_path);
}

bool NodePath::is_absolute() const {
	return godot::api->godot_node_path_is_absolute(&_node_path);
}

bool NodePath::is_empty() const {
	return godot::api->godot_node_path_is_empty(&_node_path);
}

NodePath NodePath::get_as_property_path() const {
	godot_node_path path = godot::core_1_1_api->godot_node_path_get_as_property_path(&_node_path);
	return NodePath(path);
}
String NodePath::get_concatenated_subnames() const {
	godot_string str = godot::api->godot_node_path_get_concatenated_subnames(&_node_path);
	return String(str);
}

NodePath::operator String() const {
	godot_string str = godot::api->godot_node_path_as_string(&_node_path);
	return String(str);
}

bool NodePath::operator==(const NodePath &other) {
	return godot::api->godot_node_path_operator_equal(&_node_path, &other._node_path);
}

void NodePath::operator=(const NodePath &other) {
	godot::api->godot_node_path_destroy(&_node_path);

	String other_string = (String)other;

	godot::api->godot_node_path_new(&_node_path, (godot_string *)&other_string);
}

NodePath::~NodePath() {
	godot::api->godot_node_path_destroy(&_node_path);
}

} // namespace godot

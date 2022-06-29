/*************************************************************************/
/*  Array.hpp                                                            */
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

#ifndef ARRAY_H
#define ARRAY_H

#include <gdnative/array.h>

#include "String.hpp"

namespace godot {

namespace helpers {
template <typename T, typename ValueT>
T append_all(T appendable, ValueT value) {
	appendable.append(value);
	return appendable;
}

template <typename T, typename ValueT, typename... Args>
T append_all(T appendable, ValueT value, Args... args) {
	appendable.append(value);
	return append_all(appendable, args...);
}

template <typename T>
T append_all(T appendable) {
	return appendable;
}

template <typename KV, typename KeyT, typename ValueT>
KV add_all(KV kv, KeyT key, ValueT value) {
	kv[key] = value;
	return kv;
}

template <typename KV, typename KeyT, typename ValueT, typename... Args>
KV add_all(KV kv, KeyT key, ValueT value, Args... args) {
	kv[key] = value;
	return add_all(kv, args...);
}

template <typename KV>
KV add_all(KV kv) {
	return kv;
}
} // namespace helpers

class Variant;
class PoolByteArray;
class PoolIntArray;
class PoolRealArray;
class PoolStringArray;
class PoolVector2Array;
class PoolVector3Array;
class PoolColorArray;

class Object;

class Array {
	godot_array _godot_array;

	friend class Variant;
	friend class Dictionary;
	friend class String;
	inline explicit Array(const godot_array &other) {
		_godot_array = other;
	}

public:
	Array();
	Array(const Array &other);
	Array &operator=(const Array &other);

	Array(const PoolByteArray &a);

	Array(const PoolIntArray &a);

	Array(const PoolRealArray &a);

	Array(const PoolStringArray &a);

	Array(const PoolVector2Array &a);

	Array(const PoolVector3Array &a);

	Array(const PoolColorArray &a);

	template <class... Args>
	static Array make(Args... args) {
		return helpers::append_all(Array(), args...);
	}

	Variant &operator[](const int idx);

	const Variant &operator[](const int idx) const;

	void append(const Variant &v);

	void clear();

	int count(const Variant &v);

	bool empty() const;

	void erase(const Variant &v);

	Variant front() const;

	Variant back() const;

	int find(const Variant &what, const int from = 0) const;

	int find_last(const Variant &what) const;

	bool has(const Variant &what) const;

	uint32_t hash() const;

	void insert(const int pos, const Variant &value);

	void invert();

	bool is_shared() const;

	Variant pop_back();

	Variant pop_front();

	void push_back(const Variant &v);

	void push_front(const Variant &v);

	void remove(const int idx);

	int size() const;

	void resize(const int size);

	int rfind(const Variant &what, const int from = -1) const;

	void sort();

	void sort_custom(Object *obj, const String &func);

	int bsearch(const Variant &value, const bool before = true);

	int bsearch_custom(const Variant &value, const Object *obj,
			const String &func, const bool before = true);

	Array duplicate(const bool deep = false) const;

	Variant max() const;

	Variant min() const;

	void shuffle();

	~Array();
};

} // namespace godot

#endif // ARRAY_H

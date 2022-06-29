/*************************************************************************/
/*  Color.hpp                                                            */
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

#ifndef COLOR_H
#define COLOR_H

#include <gdnative/color.h>

#include <cmath>

#include "Defs.hpp"
#include "String.hpp"

namespace godot {

struct Color {
private:
	// static float _parse_col(const String& p_str, int p_ofs);
public:
	union {
		struct {
			float r;
			float g;
			float b;
			float a;
		};
		float components[4];
	};

	inline bool operator==(const Color &p_color) const { return (r == p_color.r && g == p_color.g && b == p_color.b && a == p_color.a); }
	inline bool operator!=(const Color &p_color) const { return (r != p_color.r || g != p_color.g || b != p_color.b || a != p_color.a); }

	uint32_t to_32() const;

	uint32_t to_ARGB32() const;

	uint32_t to_ABGR32() const;

	uint64_t to_ABGR64() const;

	uint64_t to_ARGB64() const;

	uint32_t to_RGBA32() const;

	uint64_t to_RGBA64() const;

	float gray() const;

	uint8_t get_r8() const;

	uint8_t get_g8() const;

	uint8_t get_b8() const;

	uint8_t get_a8() const;

	float get_h() const;

	float get_s() const;

	float get_v() const;

	void set_hsv(float p_h, float p_s, float p_v, float p_alpha = 1.0);

	Color darkened(const float amount) const;

	Color lightened(const float amount) const;

	Color from_hsv(float p_h, float p_s, float p_v, float p_a = 1.0) const;

	inline float &operator[](int idx) {
		return components[idx];
	}
	inline const float &operator[](int idx) const {
		return components[idx];
	}

	Color operator+(const Color &p_color) const;
	void operator+=(const Color &p_color);

	Color operator-() const;
	Color operator-(const Color &p_color) const;
	void operator-=(const Color &p_color);

	Color operator*(const Color &p_color) const;
	Color operator*(const real_t &rvalue) const;
	void operator*=(const Color &p_color);
	void operator*=(const real_t &rvalue);

	Color operator/(const Color &p_color) const;
	Color operator/(const real_t &rvalue) const;
	void operator/=(const Color &p_color);
	void operator/=(const real_t &rvalue);

	void invert();

	void contrast();

	Color inverted() const;

	Color contrasted() const;

	Color linear_interpolate(const Color &p_b, float p_t) const;

	Color blend(const Color &p_over) const;

	Color to_linear() const;

	static Color hex(uint32_t p_hex);

	static Color html(const String &p_color);

	static bool html_is_valid(const String &p_color);

	String to_html(bool p_alpha = true) const;

	bool operator<(const Color &p_color) const; //used in set keys

	operator String() const;

	/**
	 * No construct parameters, r=0, g=0, b=0. a=255
	 */
	inline Color() {
		r = 0;
		g = 0;
		b = 0;
		a = 1.0;
	}

	/**
	 * RGB / RGBA construct parameters. Alpha is optional, but defaults to 1.0
	 */
	inline Color(float p_r, float p_g, float p_b, float p_a = 1.0) {
		r = p_r;
		g = p_g;
		b = p_b;
		a = p_a;
	}
};

} // namespace godot

#endif // COLOR_H

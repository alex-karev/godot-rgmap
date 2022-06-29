/*************************************************************************/
/*  Quat.hpp                                                             */
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

#ifndef QUAT_H
#define QUAT_H

#include <cmath>

#include "Vector3.hpp"

// #include "Basis.h"

namespace godot {

class Quat {
public:
	static const Quat IDENTITY;

	real_t x, y, z, w;

	real_t length_squared() const;
	real_t length() const;

	void normalize();

	Quat normalized() const;

	bool is_normalized() const;

	Quat inverse() const;

	void set_euler_xyz(const Vector3 &p_euler);
	Vector3 get_euler_xyz() const;
	void set_euler_yxz(const Vector3 &p_euler);
	Vector3 get_euler_yxz() const;

	inline void set_euler(const Vector3 &p_euler) { set_euler_yxz(p_euler); }
	inline Vector3 get_euler() const { return get_euler_yxz(); }

	real_t dot(const Quat &q) const;

	Quat slerp(const Quat &q, const real_t &t) const;

	Quat slerpni(const Quat &q, const real_t &t) const;

	Quat cubic_slerp(const Quat &q, const Quat &prep, const Quat &postq, const real_t &t) const;

	void get_axis_and_angle(Vector3 &r_axis, real_t &r_angle) const;

	void set_axis_angle(const Vector3 &axis, const float angle);

	void operator*=(const Quat &q);
	Quat operator*(const Quat &q) const;

	Quat operator*(const Vector3 &v) const;

	Vector3 xform(const Vector3 &v) const;

	void operator+=(const Quat &q);
	void operator-=(const Quat &q);
	void operator*=(const real_t &s);
	void operator/=(const real_t &s);
	Quat operator+(const Quat &q2) const;
	Quat operator-(const Quat &q2) const;
	Quat operator-() const;
	Quat operator*(const real_t &s) const;
	Quat operator/(const real_t &s) const;

	bool operator==(const Quat &p_quat) const;
	bool operator!=(const Quat &p_quat) const;

	operator String() const;

	inline void set(real_t p_x, real_t p_y, real_t p_z, real_t p_w) {
		x = p_x;
		y = p_y;
		z = p_z;
		w = p_w;
	}
	inline Quat(real_t p_x, real_t p_y, real_t p_z, real_t p_w) {
		x = p_x;
		y = p_y;
		z = p_z;
		w = p_w;
	}
	Quat(const Vector3 &axis, const real_t &angle);

	Quat(const Vector3 &v0, const Vector3 &v1);

	inline Quat() {
		x = y = z = 0;
		w = 1;
	}
};

} // namespace godot

#endif // QUAT_H

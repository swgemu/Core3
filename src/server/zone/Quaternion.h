 /*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Vector3.h"

class Quaternion {
protected:
	float w;
	float x;
	float y;
	float z;

public:
	static const Quaternion ZERO;
	static const Quaternion IDENTITY;

public:
	/**
	* Creates a quaternion initialized to the quaternion identity.
	*/
	inline Quaternion() {
		w = 1.0f;
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	/**
	* Create a quaternion based on four scalar values.
	* float fx = vector x
	* float fy = vector y
	* float fz = vector z
	* float fw = scalar
	*/
	inline Quaternion(float fw, float fx, float fy, float fz) {
		w = fw;
		x = fx;
		y = fy;
		z = fz;
	}

	/**
	* Create a quaternion based on a vector and an angle of direction.
	* \param v The vector to base rotation off of. Should be a UNIT vector.
	* \param angle The angle in radians.
	*/
	inline Quaternion(const Vector3& axis, float angle) {
		// Based on the formula q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k).
		float halfangle = angle * .5;
		float fsin = Math::sin(halfangle);

		w = Math::cos(halfangle);
		x = axis.x * fsin;
		y = axis.y * fsin;
		z = axis.z * fsin;
	}

	//inline explicit Quaternion(const Matrix4& matrix) {
	//}

	virtual ~Quaternion() {

	}

	/**
	 * Returns the string representation of the vector in (x, y, z) format.
	 */
	inline String toString() {
		StringBuffer sb;
		sb <<"(x:" << x << ", y:" << y << ", z:" << z << ", w:" << w << ")";
		return sb.toString();
	}

	inline Quaternion& operator = (const Quaternion& q) {
		w = q.w;
		x = q.x;
		y = q.y;
		z = q.z;

		return *this;
	}

	inline Quaternion operator + (const Quaternion& q) const {
		return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
	}

	inline Quaternion operator - (const Quaternion& q) const {
		return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
	}

	inline Quaternion operator * (const Quaternion& q) const {
		return Quaternion(
			w * q.w - x * q.x - y * q.y - z * q.z,
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y - x * q.z + y * q.w + z * q.x,
			w * q.z + x * q.y - y * q.x + z * q.w);
	}

	inline Quaternion operator * (const float scalar) const {
		return Quaternion(scalar * w, scalar * x, scalar * y, scalar * z);
	}

	inline bool operator == (const Quaternion& q) const {
		return (w == q.w && x == q.x && y == q.y && z == q.z);
	}

	inline bool operator != (const Quaternion& q) const {
		return (w != q.w || x != q.x || y != q.y || z != q.z);
	}

	inline float dotProduct(const Quaternion& q) const {
		return (w * q.w + x * q.x + y * q.y + z * q.z);
	}

	inline float length() const {
		return (w * w + x * x + y * y + z * z);
	}

	inline float normalize() {
		float len = length();

		float magnitude = Math::sqrt(len);
		w /= magnitude;
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;

		return len;
	}

	/**
	* Rotates the quaternion on an axis of rotation n degrees.
	* \param axis The unit axis of rotation.
	* \param degrees How many degrees to rotate the quaternion.
	* \return Returns this quaternion, rotated.
	*/
	inline Quaternion& rotate(const Vector3& axis, float degrees) {
		Quaternion qrotate(axis, Math::deg2rad(degrees));
		*this = qrotate * *this;
		return *this;
	}

	/**
	* Converts this quaternion to a matrix4.
	* \return Matrix4 The matrix4 equivalent of this quaternion.
	*/
	//inline Matrix4 toMatrix() { }

	inline float getX() {
		return x;
	}

	inline float getY() {
		return y;
	}

	inline float getZ() {
		return z;
	}

	inline float getW() {
		return w;
	}

	inline bool isIdentity() {
		return (*this == IDENTITY);
	}
};

const Quaternion Quaternion::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const Quaternion Quaternion::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f);

#endif /* QUATERNION_H_ */

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

#ifndef VECTOR3_H_
#define VECTOR3_H_

//TODO: Need to figure out how to make this class distributable :-/

class Vector3 {
protected:
	float x;
	float y;
	float z;

public:
	static const Vector3 ZERO;

	//Axis Representations
	static const Vector3 UNIT_X;
	static const Vector3 UNIT_Y;
	static const Vector3 UNIT_Z;

public:
	inline Vector3() {
		x = 0;
		y = 0;
		z = 0;
	}

	inline Vector3(const float fx, const float fy, const float fz) {
		x = fx;
		y = fy;
		z = fz;
	}

	/**
	 * Converts a 3 dimensional float array into a Vector3.
	 */
	inline explicit Vector3(const float coord[3]) {
		x = coord[0];
		y = coord[1];
		z = coord[2];
	}

	/**
	 * Converts a 3 dimensional int array into a Vector3.
	 */
	inline explicit Vector3(const int coord[3]) {
		x = (float) coord[0];
		y = (float) coord[1];
		z = (float) coord[2];
	}

	/**
	 * Converts a float scalar to a Vector3.
	 */
	inline explicit Vector3(const float scalar) {
		x = scalar;
		y = scalar;
		z = scalar;;
	}

	~Vector3() {
	}

public:
	/// Serialize aka save
	virtual void serialize() {
		//TODO: Write x, y, and z with BinaryWriter::writeFloat(x); etc.
		//TODO: Other option would be to add a method to BinaryWriter::writeVector3(const Vector3& v);
	}

	/// Deserialize aka load
	virtual void deserialize() {
	}

	/**
	 * Returns the exact length of the vector. Should be used sparingly as it
	 * uses much CPU power. Use squaredLength for comparing lengths.
	 */
	inline float length() const {
		return Math::sqrt(x * x + y * y + z * z);
	}

	/**
	 * Returns the length before being squared. Good for comparing lengths.
	 */
	inline float squaredLength() const {
		return (x * x + y * y + z * z);
	}

	/**
	 * Returns the real distance to another vector. Should not be used for comparisons.
	 * See squaredDistanceTo(.
	 * \param v The vector to get the distance to.
	 * \return Returns the float representation of the distance between the two vectors.
	 */
	inline float distanceTo(const Vector3& v) const {
		return (*this - v).length();
	}

	/**
	 * Good for comparisons of distance. Saves the cpu usage needed for sqrt.
	 * \param v The vector to get the distance to.
	 * \return Returns the float representation of the distance between two points prior to application of a square root.
	 */
	inline float squaredDistanceTo(const Vector3& v) const {
		return (*this - v).squaredLength();
	}

	/**
	 * This method returns the midpoint between this vector and another vector.
	 * \param v The vector to find a midpoint in conjunction with.
	 * \return Returns a vector half way in between this vector and the passed in vector.
	 */
	inline Vector3 midPoint(const Vector3& v) const {
		return Vector3((x + v.x) * 0.5f, (y + v.y) * 0.5f, (z + v.z) * 0.5f);
	}

	/**
	 * This method is used to calculate the angle between two vectors. If both
	 * are unit vectors then the product is the cosine of the angle; otherwise,
	 * the dot product must be divided by the product of the length
	 */
	inline float dotProduct(const Vector3& v) const {
		return (x * v.x + y * v.y + z * v.z);
	}

	/**
	 * The cross product returns the vector which is perpendicular to this vector
	 * and the vector passed in. For example, if you have two vectors in the same
	 * geometric plane, then the vector would be on the plane perpendicular to that
	 * plane, and the vector perpendicular to the two vectors. Imagine a 3D o
	 */
	inline Vector3 crossProduct(const Vector3& v) const {
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	/**
	 * Returns the string representation of the vector in (x, y, z) format.
	 */
	inline String toString() {
		StringBuffer sb;
		sb <<"(x:" << x << ", y:" << y << ", z:" << z << ")";
		return sb.toString();
	}

	inline float operator [] (uint32 index) const {
		if (index > 2)
			throw ArrayIndexOutOfBoundsException(index);

		return *(&x+index);
	}

	inline float& operator [] (uint32 index) {
		if (index > 2)
			throw ArrayIndexOutOfBoundsException(index);

		return *(&x+index);
	}

	inline Vector3& operator = (const Vector3& v) {
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	inline Vector3& operator = (const float scalar) {
		x = scalar;
		y = scalar;
		z = scalar;

		return *this;
	}

	inline Vector3 operator + (const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline Vector3 operator - (const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 operator * (const Vector3& v) const {
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	inline Vector3 operator / (const Vector3& v) const {
		return Vector3(x / v.x, y / v.y, z / v.z);
	}

	inline Vector3& operator += (const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	inline Vector3& operator -= (const Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	inline Vector3& operator *= (const Vector3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;

		return *this;
	}

	inline Vector3& operator /= (const Vector3& v) {
		x /= v.x;
		y /= v.y;
		z /= v.y;

		return *this;
	}

	inline friend Vector3 operator + (const Vector3& v, const float scalar) {
		return Vector3(v.x + scalar, v.y + scalar, v.z + scalar);
	}

	inline friend Vector3 operator + (const float scalar, const Vector3& v) {
		return Vector3(scalar + v.x, scalar + v.y, scalar + v.z);
	}

	inline friend Vector3 operator - (const Vector3& v, const float scalar) {
		return Vector3(v.x - scalar, v.y - scalar, v.z - scalar);
	}

	inline friend Vector3 operator - (const float scalar, const Vector3& v) {
		return Vector3(scalar - v.x, scalar - v.y, scalar - v.z);
	}

	inline friend Vector3 operator * (const Vector3& v, const float scalar) {
		return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
	}

	inline friend Vector3 operator * (const float scalar, const Vector3& v) {
		return Vector3(scalar * v.x, scalar * v.y, scalar * v.z);
	}

	inline friend Vector3 operator / (const Vector3& v, const float scalar) {
		if (scalar == 0.0f)
			throw DivisionByZeroException();

		return Vector3(v.x / scalar, v.y / scalar, v.z / scalar);
	}

	inline friend Vector3 operator / (const float scalar, const Vector3& v) {
		return Vector3(scalar / v.x, scalar / v.y, scalar / v.z);
	}

	//Boolean operators
	inline bool operator == (const Vector3& v) const {
		return (x == v.x && y == v.y && z == v.z);
	}

	inline bool operator != (const Vector3& v) const {
		return (x != v.x || y != v.y || z != v.z);
	}

	inline bool operator < (const Vector3& v) const {
		if (x < v.x && y < v.y && z < v.z)
			return true;

		return false;
	}

	inline bool operator > (const Vector3& v) const {
		if (x > v.x && y > v.y && z > v.z)
			return true;

		return false;
	}

	//Getters
	inline float getX() {
		return x;
	}

	inline float getY() {
		return y;
	}

	inline float getZ() {
		return z;
	}

	friend class Quaternion;
};

//TODO: Temporary until we can add .cpp to the engine
const Vector3 Vector3::ZERO(0,0,0);
const Vector3 Vector3::UNIT_X(1,0,0);
const Vector3 Vector3::UNIT_Y(0,1,0);
const Vector3 Vector3::UNIT_Z(0,0,1);

#endif /* VECTOR3_H_ */

/*
 * CreateClientPathMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef CREATECLIENTPATHMESSAGE_H_
#define CREATECLIENTPATHMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class CreateClientPathMessage : public BaseMessage {
	int coordinateCount;
public:
	CreateClientPathMessage() : BaseMessage() {

		coordinateCount = 0;

		insertShort(0x05);
		insertInt(0x71957628);  // CRC

		insertInt(0); //Coordinate Count.

		setCompression(true);

	}

	void addCoordinate(float x, float z, float y) {
		insertFloat(x); //Float PosX
		insertFloat(z); //Float PosZ
		insertFloat(y); //Float PosY
		updateCount();
	}

	void addCoordinate(const Vector3& position) {
		insertFloat(position.getX()); //Float PosX
		insertFloat(position.getZ()); //Float PosZ
		insertFloat(position.getY()); //Float PosY
		updateCount();
	}

	void updateCount() {
		insertInt(10, ++coordinateCount);
	}

	void drawBoundingSphere(const Vector3& position, const Matrix4& rotation, const Sphere& sphere, float divisions = 6) {
		const Vector3& center = sphere.getCenter();
		float radius = sphere.getRadius();

		float latAngleIncrement = Math::PI / divisions;
		float lonAngleIncrement = 2.0f * Math::PI / divisions;

		for (int lat = 0; lat <= divisions; ++lat) {
			float theta = lat * latAngleIncrement;
			float sinTheta = Math::sin(theta);
			float cosTheta = Math::cos(theta);

			for (int lon = 0; lon <= divisions; ++lon) {
				float phi = lon * lonAngleIncrement;
				float sinPhi = Math::sin(phi);
				float cosPhi = Math::cos(phi);

				Vector3 point = Vector3(
						center.getX() + radius * sinTheta * cosPhi,
						center.getY() + radius * cosTheta,
						center.getZ() + radius * sinTheta * sinPhi);

				point = point * rotation;
				point = Vector3(point.getX(), point.getZ(), point.getY());

				addCoordinate(point + position);
			}
		}

		addCoordinate(position);
	}

	void drawBoundingBox(const Vector3& position, const Matrix4& rotation, const AABB& box) {
		const Vector3& maxBound = *box.getMaxBound();
		const Vector3& minBound = *box.getMinBound();

		int vertIndices[8][3] = { { 0, 0, 0 }, { 1, 0, 0 }, { 1, 0, 1 }, { 0, 0, 1 }, { 0, 1, 0 }, { 1, 1, 0 }, { 1, 1, 1 }, { 0, 1, 1 } };
		int faceIndices[6][4] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 0, 1, 5, 4 }, { 1, 2, 6, 5 }, { 2, 3, 7, 6 }, { 0, 3, 7, 4 } };

		for (int face = 0; face < 6; ++face) {
			for (int i = 0; i < 4; ++i) {
				int vertexIndex = faceIndices[face][i];

				Vector3 point = Vector3(
						vertIndices[vertexIndex][0] ? maxBound.getX() : minBound.getX(),
						vertIndices[vertexIndex][1] ? maxBound.getY() : minBound.getY(),
						vertIndices[vertexIndex][2] ? maxBound.getZ() : minBound.getZ());

				point = point * rotation;
				point = Vector3(point.getX(), point.getZ(), point.getY());

				addCoordinate(point + position);
			}
		}

		addCoordinate(position);
	}
};

#endif /* CREATECLIENTPATHMESSAGE_H_ */

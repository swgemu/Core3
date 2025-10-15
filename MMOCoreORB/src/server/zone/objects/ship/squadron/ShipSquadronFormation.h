#ifndef SHIPSQUADRONFORMATION_H_
#define SHIPSQUADRONFORMATION_H_

#include "engine/engine.h"

class ShipSquadronFormation {
public:
	enum Type : int {
		NONE = -1,
		LINE = 0,
		WALL = 1,
		WEDGE = 2,
		SIZE,
	};

	static Vector3 getPosition(int type, int index, float radius = 1.f, int size = -1) {
		if (index <= 0) {
			return Vector3::ZERO;
		}

		switch (type) {
			case Type::LINE: {
				return getFormationLine(index, radius);
			}
			case Type::WALL: {
				return getFormationWall(index, radius);
			}
			case Type::WEDGE: {
				return getFormationWedge(index, radius);
			}
			default: {
				return Vector3::ZERO;
			}
		}
	}

private:
	static Vector3 getFormationLine(int index, float radius) {
		int step = (index + 1) / 2;
		float x = step * radius;

		if (index % 2 == 1) {
			x = -x;
		}

		return Vector3(x, 0.f, 0.f);
	}

	static Vector3 getFormationWall(int index, float radius, int size = 25) {
		int columns = 5; // sqrtf(size);
		int rows = 5; // size / columns;

		int col = index % columns;
		int stepX = (col + 1) / 2;
		float x = stepX * radius;

		if (col % 2 == 1) {
			x = -x;
		}

		int row = (index / columns) % rows;
		int stepY = (row + 1) / 2;
		float y = stepY * radius;

		if (row % 2 == 1) {
			y = -y;
		}

		int layer = index / (rows * columns);
		int stepZ = (layer + 1) / 2;
		float z = stepZ * radius;

		if (layer % 2 == 1) {
			z = -z;
		}

		return Vector3(x, y, z);
	}

	static Vector3 getFormationWedge(int index, float radius) {
		int step = (index + 1) / 2;
		float x = step * radius;
		float z = -step * radius;

		if (index % 2 == 1) {
			x = -x;
		}

		return Vector3(x, 0.f, z);
	}
};

#endif // SHIPSQUADRONFORMATION_H_

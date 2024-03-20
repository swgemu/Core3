#ifndef PLAYERLAUNCHPOINTS_H_
#define PLAYERLAUNCHPOINTS_H_

#include "system/lang/Object.h"
#include "engine/util/u3d/Vector3.h"
#include "system/util/VectorMap.h"

class PlayerLaunchPoints : public Object {
protected:
	VectorMap<String, Vector<Vector3>> spawnLocations;

public:
	PlayerLaunchPoints() {
	}

	PlayerLaunchPoints(const PlayerLaunchPoints& points) : Object() {
		spawnLocations = points.spawnLocations;
	}

	PlayerLaunchPoints& operator=(const PlayerLaunchPoints& points) {
		if (this == &points)
			return *this;

		spawnLocations = points.spawnLocations;

		return *this;
	}

	void addLaunchPoint(String cellName, Vector3 location) {
		Vector<Vector3> cellLocs = spawnLocations.get(cellName);

		cellLocs.add(location);
		spawnLocations.put(cellName, cellLocs);
	}

	inline int getTotalLaunchCells() {
		return spawnLocations.size();
	}

	const inline String getRandomCell() {
		int totalCells = getTotalLaunchCells();

		if (totalCells <= 0) {
			return "";
		} else if (totalCells == 1) {
			return spawnLocations.elementAt(0).getKey();
		}

		int random = System::random((totalCells - 1));
		String cellName = spawnLocations.elementAt(random).getKey();

		return cellName;
	}

	const inline Vector<Vector3>& getSpawnLocations(String cellName) {
		return spawnLocations.get(cellName);
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		spawnLocations.toBinaryStream(stream);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		spawnLocations.parseFromBinaryStream(stream);

		return true;
	}
};

#endif /* PLAYERLAUNCHPOINTS_H_ */

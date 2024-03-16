#ifndef DAMAGESPARKLOCATIONS_H_
#define DAMAGESPARKLOCATIONS_H_

#include "system/lang/Object.h"
#include "engine/util/u3d/Vector3.h"
#include "system/util/VectorMap.h"

class DamageSparkLocations : public Object, public Logger {

protected:
	VectorMap<String, Vector<Vector3>> sparkLocations;

public:
	DamageSparkLocations() : Object() {
		setLoggingName("DamageSparkLocations");
	}

	~DamageSparkLocations() {
	}

	DamageSparkLocations& operator=(const DamageSparkLocations& points) {
		if (this == &points)
			return *this;

		sparkLocations = points.sparkLocations;

		return *this;
	}

	void addSparkLocation(String cellName, Vector3 location) {
		Vector<Vector3> cellLocs = sparkLocations.get(cellName);
		cellLocs.add(location);

		sparkLocations.put(cellName, cellLocs);
	}

	inline int getTotalSparkCells() {
		return sparkLocations.size();
	}

	const inline String getRandomCell() {
		int totalCells = getTotalSparkCells();
		int random = System::random(totalCells - 1);
		String cellName = sparkLocations.elementAt(random).getKey();

		return cellName;
	}

	const inline Vector<Vector3> &getSparkLocations(String cellName) {
		return sparkLocations.get(cellName);
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		sparkLocations.toBinaryStream(stream);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		sparkLocations.parseFromBinaryStream(stream);

		return true;
	}
};

#endif /* DAMAGESPARKLOCATIONS_H_ */

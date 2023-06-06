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
		setLoggingName("PlayerLaunchPoints");
	}

	~DamageSparkLocations() {
	}

	void addSparkLocation(String cellName, Vector3 location) {
		Vector<Vector3> cellLocs = sparkLocations.get(cellName);
		cellLocs.add(location);
	}

	inline int getTotalLaunchCells() {
		return sparkLocations.size();
	}

	const inline String getRandomCell() {
		int totalCells = getTotalLaunchCells();
		int random = System::random(totalCells - 1);
		String cellName = sparkLocations.elementAt(random).getKey();

		return cellName;
	}

	const inline Vector<Vector3> &getSparkLocations(String cellName) {
		return sparkLocations.get(cellName);
	}
};

#endif /* DAMAGESPARKLOCATIONS_H_ */

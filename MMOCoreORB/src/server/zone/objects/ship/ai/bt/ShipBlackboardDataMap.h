#ifndef SHIPBLACKBOARDDATAMAP_H_
#define SHIPBLACKBOARDDATAMAP_H_

#include "system/util/VectorMap.h"
#include "ShipBlackboardData.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace bt {

class ShipBlackboardDataMap : public VectorMap<String, ShipBlackboardData> {
public:
	ShipBlackboardDataMap() {
		setNoDuplicateInsertPlan();
	}

	ShipBlackboardDataMap(const ShipBlackboardDataMap& b) : VectorMap<String, ShipBlackboardData>(b) {
		setNoDuplicateInsertPlan();
	}

	~ShipBlackboardDataMap() {
	}

	ShipBlackboardDataMap& operator=(const ShipBlackboardDataMap& b) {
		if (this == &b)
			return *this;

		VectorMap<String, ShipBlackboardData>::operator=(b);
		setNoDuplicateInsertPlan();

		return *this;
	}
};

} // namespace bt
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // SHIPBLACKBOARDDATAMAP_H_

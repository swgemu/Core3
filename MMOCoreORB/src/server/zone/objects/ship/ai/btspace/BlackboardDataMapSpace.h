#ifndef BLACKBOARDDATAMAPSPACE_H_
#define BLACKBOARDDATAMAPSPACE_H_

#include "system/util/VectorMap.h"
#include "BlackboardDataSpace.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {

class BlackboardDataMapSpace : public VectorMap<String, BlackboardDataSpace> {
public:
	BlackboardDataMapSpace() {
		setNoDuplicateInsertPlan();
	}

	BlackboardDataMapSpace(const BlackboardDataMapSpace& b) : VectorMap<String, BlackboardDataSpace>(b) {
		setNoDuplicateInsertPlan();
	}

	~BlackboardDataMapSpace() {
	}

	BlackboardDataMapSpace& operator=(const BlackboardDataMapSpace& b) {
		if (this == &b)
			return *this;

		VectorMap<String, BlackboardDataSpace>::operator=(b);
		setNoDuplicateInsertPlan();

		return *this;
	}
};

} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // SHIPBLACKBOARDDATAMAP_H_

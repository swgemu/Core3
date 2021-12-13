#ifndef BLACKBOARDDATAMAP_H_
#define BLACKBOARDDATAMAP_H_

#include "system/util/VectorMap.h"
#include "BlackboardData.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

class BlackboardDataMap : public VectorMap<String, BlackboardData> {
public:
	BlackboardDataMap() {
		setNoDuplicateInsertPlan();
	}

	BlackboardDataMap(const BlackboardDataMap& b) : VectorMap<String, BlackboardData>(b) {
		setNoDuplicateInsertPlan();
	}

	~BlackboardDataMap() {}

	BlackboardDataMap& operator=(const BlackboardDataMap& b) {
		if (this == &b)
			return *this;

		VectorMap<String, BlackboardData>::operator=(b);
		setNoDuplicateInsertPlan();

		return *this;
	}
};

}
}
}
}
}
}

#endif // BLACKBOARDDATAMAP_H_

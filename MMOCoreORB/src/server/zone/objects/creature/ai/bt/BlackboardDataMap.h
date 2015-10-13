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
        setNullValue(NULL);
        setNoDuplicateInsertPlan();
    }

    BlackboardDataMap(const BlackboardDataMap& b) : VectorMap<String, BlackboardData>(b) {
        setNullValue(NULL);
        setNoDuplicateInsertPlan();
    }

    ~BlackboardDataMap() {}

    BlackboardDataMap& operator=(const BlackboardDataMap& b) {
        if (this == &b)
            return *this;

        VectorMap<String, BlackboardData>::operator=(b);
        setNullValue(NULL);
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

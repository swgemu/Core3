/*
 * ThreatMatrix.h
 *
 *  Created on: 1/23/2012
 *      Author: Kyle
 */

#ifndef THREATMATRIX_H_
#define THREATMATRIX_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
class TangibleObject;
}
}
}
}

using namespace server::zone::objects::tangible;

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace threat {

class ThreatMapEntry;

//#define DEBUG

class ThreatMatrix {
protected:
	ManagedReference<TangibleObject*> tauntThreat;
	ManagedReference<TangibleObject*> focusedThreat;

	VectorMap<uint32, ManagedReference<TangibleObject*>> damageMap;
	VectorMap<int, ManagedReference<TangibleObject*>> aggroMap;
	VectorMap<int, ManagedReference<TangibleObject*>> healMap;

public:
	ThreatMatrix();
	~ThreatMatrix();

	ThreatMatrix(const ThreatMatrix& e);

	ThreatMatrix& operator=(const ThreatMatrix& e);

	void clear();

	void add(TangibleObject* threat, ThreatMapEntry* entry);

	TangibleObject* getLargestThreat();

	void print();
};
}
}
}
}
}

using namespace server::zone::objects::tangible::threat;

#endif /* THREATMATRIX_H_ */

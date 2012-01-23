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
   namespace creature {
    class CreatureObject;
   }
  }
 }
}

using namespace server::zone::objects::creature;

namespace server {
 namespace zone {
  namespace objects {
   namespace tangible {
   	namespace threat {

   class ThreatMapEntry;
   class ThreatMap;

//#define DEBUG

class ThreatMatrix {
protected:

	   CreatureObject* tauntThreat;
	   CreatureObject* focusedThreat;

	   VectorMap<uint32, CreatureObject*> damageMap;
	   VectorMap<int, CreatureObject*> aggroMap;
	   VectorMap<int, CreatureObject*> healMap;

public:
	ThreatMatrix();
	~ThreatMatrix();

	ThreatMatrix(const ThreatMatrix& e);

	ThreatMatrix& operator=(const ThreatMatrix& e);

	void clear();

	void add(CreatureObject* creature, ThreatMapEntry* entry);

	CreatureObject* getLargestThreat();

	void print();

};


}
}
}
}
}

using namespace server::zone::objects::tangible::threat;

#endif /* THREATMATRIX_H_ */

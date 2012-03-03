/*
 * Uint64VectorDeltaVector.h
 *
 *  Created on: Feb 24, 2012
 *      Author: kyle
 */

#ifndef UINT64VECTORDELTAVECTOR_H_
#define UINT64VECTORDELTAVECTOR_H_

#include "server/zone/objects/scene/variables/DeltaVector.h"

namespace server {
namespace zone {
namespace objects {
namespace manufactureschematic {
namespace variables {

class Uint64VectorDeltaVector: public DeltaVector<Vector<uint64> > {
public:
	Uint64VectorDeltaVector() {
		
	}
	
	~Uint64VectorDeltaVector() {
		
	}
};

}
}
}
}
}

using namespace server::zone::objects::manufactureschematic::variables;


#endif /* UINT64VECTORDELTAVECTOR_H_ */

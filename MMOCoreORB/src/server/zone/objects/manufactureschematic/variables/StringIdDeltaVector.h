/*
 * StringIdDeltaVector.h
 *
 *  Created on: Feb 24, 2012
 *      Author: kyle
 */

#ifndef STRINGIDDELTAVECTOR_H_
#define STRINGIDDELTAVECTOR_H_

#include "server/zone/objects/scene/variables/StringId.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"

namespace server {
namespace zone {
namespace objects {
namespace manufactureschematic {
namespace variables {

class StringIdDeltaVector: public DeltaVector<StringId> {
public:
	StringIdDeltaVector() {
		
	}
	
	~StringIdDeltaVector() {
		
	}

};

}
}
}
}
}

using namespace server::zone::objects::manufactureschematic::variables;


#endif /* STRINGIDDELTAVECTOR_H_ */

/*
 * ZoneReference.h
 *
 *  Created on: May 19, 2011
 *      Author: crush
 */

#ifndef ZONEREFERENCE_H_
#define ZONEREFERENCE_H_

#include "engine/engine.h"

namespace server {
namespace zone {

class Zone;

class ZoneReference : public ManagedReference<Zone*> {
public:
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
	Zone* operator=(Zone* obj);
};

}
}


using namespace server::zone;


#endif /* ZONEREFERENCE_H_ */

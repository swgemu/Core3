/*
 * SpaceZoneReference.h
 *
 *  Created on: May 19, 2011
 *      Author: crush
 */

#ifndef SPACEZONEREFERENCE_H_
#define SPACEZONEREFERENCE_H_

#include "engine/engine.h"
#include "engine/util//json_utils.h"

namespace server {
namespace zone {

class SpaceZone;

class SpaceZoneReference : public ManagedReference<SpaceZone*> {
#ifdef ODB_SERIALIZATION
protected:
	String zoneName;
#endif
public:
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
	SpaceZone* operator=(SpaceZone* obj);
#ifdef ODB_SERIALIZATION
	const String& getZoneName() const {
		return zoneName;
	}
#endif
};

void to_json(nlohmann::json& j, const SpaceZoneReference& p);

}
}


using namespace server::zone;


#endif /* SPACEZONEREFERENCE_H_ */

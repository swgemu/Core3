/*
 * ZoneReference.h
 *
 *  Created on: May 19, 2011
 *      Author: crush
 */

#ifndef ZONEREFERENCE_H_
#define ZONEREFERENCE_H_

#include "engine/engine.h"
#include "engine/util//json_utils.h"

namespace server {
namespace zone {

class Zone;

class ZoneReference : public ManagedReference<Zone*> {
#ifdef ODB_SERIALIZATION
protected:
	String zoneName;
#endif
public:
	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);
	Zone* operator=(Zone* obj);
#ifdef ODB_SERIALIZATION
	const String& getZoneName() const {
		return zoneName;
	}
#endif
};

void to_json(nlohmann::json& j, const ZoneReference& p);

}
}

using namespace server::zone;

#endif /* ZONEREFERENCE_H_ */

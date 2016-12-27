/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESOURCECONTAINEROBJECTMESSAGE6_H_
#define RESOURCECONTAINEROBJECTMESSAGE6_H_

#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/packets/BaseLineMessage.h"

class ResourceContainerObjectMessage6 : public BaseLineMessage {
public:
	ResourceContainerObjectMessage6(ResourceContainer* rcno)
			: BaseLineMessage(rcno->getObjectID(), 0x52434E4F, 6, 0x05) {
		insertAscii(""); // Resource Container: "resource_container_d"
		insertInt(0);
		insertAscii(""); // Resource Type: "organic_food_small"
		UnicodeString u_str = UnicodeString("");
		insertUnicode(u_str); // Container Name
		insertInt(ResourceContainer::MAXSIZE); // Max stack size
		insertAscii(rcno->getSpawnType()); // Resource Type: planet specific
		insertUnicode(rcno->getSpawnName());  // Resource name.
		setSize();
	}
};

#endif /*RESOURCECONTAINEROBJECTMESSAGE6_H_*/

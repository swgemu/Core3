/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESOURCECONTAINEROBJECTDELTAMESSAGE6_H_
#define RESOURCECONTAINEROBJECTDELTAMESSAGE6_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/resource/ResourceContainer.h"

class ResourceContainerObjectDeltaMessage6 : public DeltaMessage {
public:
	ResourceContainerObjectDeltaMessage6(ResourceContainer* rcno)
			: DeltaMessage(rcno->getObjectID(), 0x52434E4F, 6) {
		// Causes CTD, needs research.
		//setResourceName(rcno->getName());
		//setResourceType(rcno->getTemplateName());
		//close();
	}

	void setResourceName(UnicodeString& resource_name) {
		startUpdate(0x06);
		insertUnicode(resource_name);
	}
	
	void setResourceType(String& resource_type) {
		startUpdate(0x05);
		insertAscii(resource_type);
	}
	
};
#endif /*RESOURCECONTAINEROBJECTDELTAMESSAGE6_H_*/

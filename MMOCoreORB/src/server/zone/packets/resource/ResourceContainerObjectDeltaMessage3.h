/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESOURCECONTAINEROBJECTDELTAMESSAGE3_H_
#define RESOURCECONTAINEROBJECTDELTAMESSAGE3_H_

#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/packets/DeltaMessage.h"

class ResourceContainerObjectDeltaMessage3 : public DeltaMessage {
private:
	ManagedReference<ResourceContainer*> container;

public:
	ResourceContainerObjectDeltaMessage3(ResourceContainer* rcno)
			: DeltaMessage(rcno->getObjectID(), 0x52434E4F, 3) {
		container = rcno;
	}
	/*
	 * Need More Research.
	 * 
	 * void setContainerType(String& file, String& ctype) {
	 * 	startUpdate(0x01);
	 * 	insertAscii(file);
	 * 	insertInt(0);
	 * 	insertAscii(ctype);
	 * }
	 * 
	 * void setResourceID(uint64 rid) {
	 * 	addLongUpdate(0x0E, rid);
	 * }
	 */
		
	void updateQuantity() {
		addIntUpdate(0x0B, container->getQuantity());
	}
	
};

#endif /*RESOURCECONTAINEROBJECTDELTAMESSAGE3_H_*/

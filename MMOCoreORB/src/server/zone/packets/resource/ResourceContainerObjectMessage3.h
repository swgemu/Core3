/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESOURCECONTAINEROBJECTMESSAGE3_H_
#define RESOURCECONTAINEROBJECTMESSAGE3_H_

#include "server/zone/objects/resource/ResourceContainer.h"
#include "../BaseLineMessage.h"

#include "../tangible/TangibleObjectMessage3.h"

class ResourceContainerObjectMessage3 : public TangibleObjectMessage3 {
public:
	ResourceContainerObjectMessage3(ResourceContainer* rcno)
			: TangibleObjectMessage3(rcno, 0x52434E4F, 0x0F) {

		insertInt(rcno->getQuantity()); // Stack Size
		insertLong(rcno->getSpawnID()); // ResourceID

		setSize();
	}
};

#endif /*RESOURCECONTAINEROBJECTMESSAGE3_H_*/

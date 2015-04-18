/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#ifndef MANUFACTURESCHEMATICOBJECTDELTAMESSAGE6_H_
#define MANUFACTURESCHEMATICOBJECTDELTAMESSAGE6_H_

#include "../BaseLineMessage.h"

class ManufactureSchematicObjectDeltaMessage6 : public DeltaMessage {
public:
	ManufactureSchematicObjectDeltaMessage6(SceneObject* schematic)
			: DeltaMessage(schematic->getObjectID(), 0x4D53434F, 6) {
	}
	
	void insertToResourceSlot(int slotNumber){
		addByteUpdate(5, slotNumber);
	}
};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE6_H_*/

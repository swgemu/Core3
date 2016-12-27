/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef MANUFACTURESCHEMATICOBJECTMESSAGE7_H_
#define MANUFACTURESCHEMATICOBJECTMESSAGE7_H_

#include "server/zone/packets/BaseLineMessage.h"

class ManufactureSchematicObjectMessage7: public BaseLineMessage {
public:
	ManufactureSchematicObjectMessage7(SceneObject* schematic) :
			BaseLineMessage(schematic->getObjectID(), 0x4D53434F, 7, 0x15) {

	}

};

#endif /*MANUFACTURESCHEMATICOBJECTMESSAGE7_H_*/

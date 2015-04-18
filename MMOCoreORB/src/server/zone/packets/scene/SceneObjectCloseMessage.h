/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SCENEOBJECTCLOSEMESSAGE_H_
#define SCENEOBJECTCLOSEMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/SceneObject.h"

class SceneObjectCloseMessage : public BaseMessage {
public:
	SceneObjectCloseMessage(SceneObject* scno) : BaseMessage(18) {
		insertShort(0x02);
		insertInt(0x2C436037);  // CRC
		insertLong(scno->getObjectID());  // ObjectID

		/*StringBuffer msg;
		msg << hex << "SceneObjectCloseMessage [Object = " << scno->getObjectID() << "]" << " of (" << scno->getObjectCRC() << ")\n";
		System::out << msg.toString();*/
	}

	SceneObjectCloseMessage(uint64 oid) : BaseMessage() {
		insertShort(0x02);
		insertInt(0x2C436037);  // CRC
		insertLong(oid);  // ObjectID

		/*StringBuffer msg;
		msg << hex << "SceneObjectCloseMessage [Object = " << oid  << "]\n";
		System::out << msg.toString(); */

	}

};

#endif /*SCENEOBJECTCLOSEMESSAGE_H_*/

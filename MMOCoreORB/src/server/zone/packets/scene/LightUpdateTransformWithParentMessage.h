/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LIGHTUPDATETRANSFORMWITHPARENTMESSAGE_H_
#define LIGHTUPDATETRANSFORMWITHPARENTMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/SceneObject.h"

class LightUpdateTransformWithParentMessage : public BaseMessage {
public:
	LightUpdateTransformWithParentMessage(SceneObject* object) : BaseMessage(50) {
		insertShort(0x08);
		insertInt(0xC867AB5A);
		insertLong(object->getParentID());
	    insertLong(object->getObjectID());

		// add coordinates
		insertSignedShort((int16) (object->getPositionX() * 8));
		insertSignedShort((int16) (object->getPositionZ() * 8));
		insertSignedShort((int16) (object->getPositionY() * 8));

		// add movement counter
		insertInt(object->getMovementCounter());
		
		insertByte(0); // unknown
		
		// add direction
		insertByte((byte) object->getSpecialDirectionAngle());
		
		/*System::out << "Position Update [" << player->getObjectID() << "] (" 
			 << (int) (player->getPositionX()) << "," << (int) (player->getPositionZ()) << "," 
			 << (int) (player->getPositionY()) << ") - Dir = " << (int) (player->getDirectionAngle()) << "\n";*/
	}

	LightUpdateTransformWithParentMessage(SceneObject* object, float posX, float posZ, float posY, uint64 cellID) : BaseMessage(50) {
		insertShort(0x08);
		insertInt(0xC867AB5A);
		insertLong(cellID);
		insertLong(object->getObjectID());

		// add coordinates
		insertSignedShort((int16) (posX * 8));
		insertSignedShort((int16) (posZ * 8));
		insertSignedShort((int16) (posY * 8));

		// add movement counter
		insertInt(object->getMovementCounter());

		insertByte(0); // unknown

		// add direction
		insertByte((byte) object->getSpecialDirectionAngle());

		/*System::out << "Position Update [" << player->getObjectID() << "] ("
				 << (int) (player->getPositionX()) << "," << (int) (player->getPositionZ()) << ","
				 << (int) (player->getPositionY()) << ") - Dir = " << (int) (player->getDirectionAngle()) << "\n";*/
	}

};


#endif /*LIGHTUPDATETRANSFORMWITHPARENTMESSAGE_H_*/

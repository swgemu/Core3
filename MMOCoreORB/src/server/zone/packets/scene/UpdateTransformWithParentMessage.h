/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UPDATETRANSFORMWITHPARENTMESSAGE_H_
#define UPDATETRANSFORMWITHPARENTMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

class UpdateTransformWithParentMessage : public BaseMessage {
public:
	UpdateTransformWithParentMessage(SceneObject* object) : BaseMessage(50) {
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

		if (object->isCreatureObject())
			insertByte((int8)object->asCreatureObject()->getCurrentSpeed());
		else
			insertByte(0);
		
		// add direction
		insertByte((int8) object->getSpecialDirectionAngle());
		
		/*System::out << "Position Update [" << player->getObjectID() << "] (" 
			 << (int) (player->getPositionX()) << "," << (int) (player->getPositionZ()) << "," 
			 << (int) (player->getPositionY()) << ") - Dir = " << (int) (player->getDirectionAngle()) << "\n";*/
	}
	
	UpdateTransformWithParentMessage(SceneObject* object, float posX, float posZ, float posY, uint64 parentID) : 
		BaseMessage(50) {
		
		insertShort(0x08);
		insertInt(0xC867AB5A);
		insertLong(parentID);
		insertLong(object->getObjectID());

		// add coordinates
		insertSignedShort((int16) (posX * 8));
		insertSignedShort((int16) (posZ * 8));
		insertSignedShort((int16) (posY * 8));

		// add movement counter
		insertInt(object->getMovementCounter());

		if (object->isCreatureObject())
			insertByte((int8)object->asCreatureObject()->getCurrentSpeed());
		else
			insertByte(0);

		// add direction
		insertByte((int8) object->getSpecialDirectionAngle());

		/*System::out << "Position Update [" << player->getObjectID() << "] (" 
				 << (int) (player->getPositionX()) << "," << (int) (player->getPositionZ()) << "," 
				 << (int) (player->getPositionY()) << ") - Dir = " << (int) (player->getDirectionAngle()) << "\n";*/
	}

};

#endif /*UPDATETRANSFORMWITHPARENTMESSAGE_H_*/

/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LIGHTUPDATETRANSFORMMESSAGE_H_
#define LIGHTUPDATETRANSFORMMESSAGE_H_

#include "engine/service/proto/StandaloneBaseMessage.h"

#include "server/zone/objects/scene/SceneObject.h"

//#define UNRELIABLE_LIGHT_TRANSFORMS

#ifdef UNRELIABLE_LIGHT_TRANSFORMS
#define UNRELIABLE_LIGHT_BASE_CLASS StandaloneBaseMessage
#else
#define UNRELIABLE_LIGHT_BASE_CLASS BaseMessage
#endif

class LightUpdateTransformMessage : public UNRELIABLE_LIGHT_BASE_CLASS {
public:
	LightUpdateTransformMessage(SceneObject* scno) : UNRELIABLE_LIGHT_BASE_CLASS(50) {
		insertShort(0x08);
		insertInt(0x1B24F808);
	    insertLong(scno->getObjectID());

		// add coordinates
		insertSignedShort((int16) (scno->getPositionX() * 4));
		insertSignedShort((int16) (scno->getPositionZ() * 4));
		insertSignedShort((int16) (scno->getPositionY() * 4));

		// add movement counter
		insertInt(scno->getMovementCounter());

		auto creo = scno->asCreatureObject();

		if (creo)
			insertByte((int8)creo->getCurrentSpeed());
		else
			insertByte(0);
		
		// add direction
		insertByte((byte) scno->getSpecialDirectionAngle());
		
		/*System::out << "Position Update [" << player->getObjectID() << "] (" 
			 << (int) (player->getPositionX()) << "," << (int) (player->getPositionZ()) << "," 
			 << (int) (player->getPositionY()) << ") - Dir = " << (int) (player->getDirectionAngle()) << "\n";*/
	}
	
	LightUpdateTransformMessage(SceneObject* scno, float posX, float posZ, float posY) : UNRELIABLE_LIGHT_BASE_CLASS(50) {
		insertShort(0x08);
		insertInt(0x1B24F808);
		insertLong(scno->getObjectID());

		// add coordinates
		insertSignedShort((int16) (posX * 4));
		insertSignedShort((int16) (posZ * 4));
		insertSignedShort((int16) (posY * 4));

		// add movement counter
		insertInt(scno->getMovementCounter());

		auto creo = scno->asCreatureObject();

		if (creo)
			insertByte((int8)creo->getCurrentSpeed());
		else
			insertByte(0);

		// add direction
		insertByte((byte) scno->getSpecialDirectionAngle());

		/*System::out << "Position Update [" << player->getObjectID() << "] (" 
				 << (int) (player->getPositionX()) << "," << (int) (player->getPositionZ()) << "," 
				 << (int) (player->getPositionY()) << ") - Dir = " << (int) (player->getDirectionAngle()) << "\n";*/
	}

};

#endif /*LIGHTUPDATETRANSFORMMESSAGE_H_*/

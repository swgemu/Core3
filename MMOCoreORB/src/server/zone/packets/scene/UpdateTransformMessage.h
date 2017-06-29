/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UPDATETRANSFORMMESSAGE_H_
#define UPDATETRANSFORMMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

class UpdateTransformMessage : public BaseMessage {
public:
	UpdateTransformMessage(SceneObject* scno) : BaseMessage(50) {
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
		insertByte((int8)scno->getSpecialDirectionAngle());
	}

	UpdateTransformMessage(SceneObject* scno, float posX, float posZ, float posY) : BaseMessage(50) {
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
		insertByte((int8) scno->getSpecialDirectionAngle());
	}

	static void parse(Packet* pack, SceneObject* scno) {
		float x = pack->parseSignedShort() / 4;
		float y = pack->parseSignedShort() / 4;
		float z = pack->parseSignedShort() / 4;

		scno->setPosition(x, y, z);
	}
};

#endif /*UPDATETRANSFORMMESSAGE_H_*/

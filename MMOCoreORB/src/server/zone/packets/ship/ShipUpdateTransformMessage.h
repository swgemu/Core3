/*
 * ShipUpdateTransformMessage.h
 *
 *  Created on: 01/09/2011
 *	  Author: TheAnswer
 */

#ifndef SHIPUPDATETRANSFORMMESSAGE_H_
#define SHIPUPDATETRANSFORMMESSAGE_H_

#include "server/zone/objects/ship/ShipObject.h"

#include "PackedVelocity.h"
#include "PackedPosition.h"
#include "PackedRotationRate.h"

class ShipUpdateTransformMessage : public BaseMessage {
public:
	ShipUpdateTransformMessage(ShipObject* ship, PackedVelocity& velocity, PackedRotationRate& rA, PackedRotationRate& rB, PackedRotationRate& rC) : BaseMessage(50) {
		//Logger::console.info("shipUpdateTransformMessage NEW", true);

		insertShort(0x08); //Opcode
		insertInt(0x76026fb9); //Message
		insertShort(ship->getUniqueID());

		//direction
		insertSignedByte((byte)ship->getDirectionW());
		insertSignedByte((byte)ship->getDirectionX());
		insertSignedByte((byte)ship->getDirectionY());
		insertSignedByte((byte)ship->getDirectionZ());

		PackedPosition packed;
		packed.set(ship->getPosition());
		packed.write(this);

		velocity.write(this);

		rA.write(this);
		rB.write(this);
		rC.write(this);

		insertInt(ship->getMovementCounter());
	}

	ShipUpdateTransformMessage(ShipObject* scno, int8 dirX, int8 dirY, int8 dirZ, int8 dirW, int16 posX, int16 posZ, int16 posY, int16 velA, int16 velB, int8 rA, int8 rB, int8 rC) : BaseMessage(50) {
		//Logger::console.info("shipUpdateTransformMessage 1", true);

		float positionMultiplier = 4.0958748f;

		insertShort(0x08); //Opcode
		insertInt(0x76026fb9); //Message
		insertShort(scno->getUniqueID());

		//direction
		insertSignedByte((byte)dirW);
		insertSignedByte((byte)dirX);
		insertSignedByte((byte)dirY);
		insertSignedByte((byte)dirZ);

		insertSignedShort((int16)posX * positionMultiplier);
		insertSignedShort((int16)posY * positionMultiplier);
		insertSignedShort((int16)posZ * positionMultiplier);

		insertSignedShort(velA);
		insertSignedShort(velB);

		insertSignedByte(rA);
		insertSignedByte(rB);
		insertSignedByte(rC);

		insertInt(scno->getMovementCounter());
	}

	ShipUpdateTransformMessage(ShipObject* scno, Quaternion direction, Vector3 position, PackedVelocity& velocity, PackedRotationRate& rA, PackedRotationRate& rB, PackedRotationRate& rC) : BaseMessage(50) {
		//Logger::console.info("shipUpdateTransformMessage2", true);

		float positionMultiplier = 4.0958748f;
		insertShort(0x08); //opcode

		insertInt(0x76026fb9); //Message
		insertShort(scno->getUniqueID());

		//direction
		insertSignedByte((byte)direction.getW());
		insertSignedByte((byte)direction.getX());
		insertSignedByte((byte)direction.getY());
		insertSignedByte((byte)direction.getZ());

		insertSignedShort((int16)position.getX() * positionMultiplier);
		insertSignedShort((int16)position.getY() * positionMultiplier);
		insertSignedShort((int16)position.getZ() * positionMultiplier);

		velocity.write(this);

		rA.write(this);
		rB.write(this);
		rC.write(this);

		insertInt(scno->getMovementCounter());
	}
};

#endif /* SHIPUPDATETRANSFORMMESSAGE_H_ */

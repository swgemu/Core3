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
	ShipUpdateTransformMessage(ShipObject* ship) : BaseMessage(50) {
		insertShort(0x08); //Opcode
		insertInt(0x76026fb9); //Message
		insertShort(ship->getUniqueID());

		writePackedDirection(ship->getDirection());
		writePackedPosition(ship->getPosition());

		insertShort(0);
		insertShort(0);

		insertSignedByte(0);
		insertSignedByte(0);
		insertSignedByte(0);

		insertInt(ship->getMovementCounter());
	}

	ShipUpdateTransformMessage(ShipObject* ship, PackedVelocity& velocity, PackedRotationRate& rA, PackedRotationRate& rB, PackedRotationRate& rC) : BaseMessage(50) {
		insertShort(0x08); //Opcode
		insertInt(0x76026fb9); //Message
		insertShort(ship->getUniqueID());

		writePackedDirection(ship->getDirection());
		writePackedPosition(ship->getPosition());

		velocity.write(this);

		rA.write(this);
		rB.write(this);
		rC.write(this);

		insertInt(ship->getMovementCounter());
	}

	ShipUpdateTransformMessage(ShipObject* ship, const Vector3& position, PackedVelocity& velocity, PackedRotationRate& rA, PackedRotationRate& rB, PackedRotationRate& rC) : BaseMessage(50) {
		insertShort(0x08); //Opcode
		insertInt(0x76026fb9); //Message
		insertShort(ship->getUniqueID());

		writePackedDirection(ship->getDirection());
		writePackedPosition(position);

		velocity.write(this);

		rA.write(this);
		rB.write(this);
		rC.write(this);

		insertInt(ship->getMovementCounter());
	}

	ShipUpdateTransformMessage(ShipObject* scno, const Quaternion* direction, const Vector3& position, PackedVelocity& velocity, PackedRotationRate& rA, PackedRotationRate& rB, PackedRotationRate& rC) : BaseMessage(50) {
		insertShort(0x08); //opcode
		insertInt(0x76026fb9); //Message
		insertShort(scno->getUniqueID());

		writePackedDirection(direction);
		writePackedPosition(position);

		velocity.write(this);

		rA.write(this);
		rB.write(this);
		rC.write(this);

		insertInt(scno->getMovementCounter());
	}

	ShipUpdateTransformMessage(ShipObject* scno, int8 dirX, int8 dirY, int8 dirZ, int8 dirW, int16 posX, int16 posZ, int16 posY, int16 velA, int16 velB, int8 rA, int8 rB, int8 rC) : BaseMessage(50) {
		insertShort(0x08); //Opcode
		insertInt(0x76026fb9); //Message
		insertShort(scno->getUniqueID());

		//direction
		insertSignedByte(dirW);
		insertSignedByte(dirX);
		insertSignedByte(dirY);
		insertSignedByte(dirZ);

		insertSignedShort(posX);
		insertSignedShort(posY);
		insertSignedShort(posZ);

		insertSignedShort(velA);
		insertSignedShort(velB);

		insertSignedByte(rA);
		insertSignedByte(rB);
		insertSignedByte(rC);

		insertInt(scno->getMovementCounter());
	}

	void writePackedPosition(const Vector3& position) {
		PackedPosition packed;
		packed.set(position);
		packed.write(this);
	}

	void writePackedDirection(const Quaternion* direction) {
		insertSignedByte((int8)(direction->getW() * 127.f));
		insertSignedByte((int8)(direction->getX() * 127.f));
		insertSignedByte((int8)(direction->getY() * 127.f));
		insertSignedByte((int8)(direction->getZ() * 127.f));
	}
};

#endif /* SHIPUPDATETRANSFORMMESSAGE_H_ */

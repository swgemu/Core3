/*
 * ShipUpdateTransformMessage.h
 *
 *  Created on: 01/09/2011
 *      Author: TheAnswer
 */

#ifndef SHIPUPDATETRANSFORMMESSAGE_H_
#define SHIPUPDATETRANSFORMMESSAGE_H_

#include "server/zone/objects/ship/ShipObject.h"

#include "PackedVelocity.h"
#include "PackedRotationRate.h"

class ShipUpdateTransformMessage : public BaseMessage {
public:
	ShipUpdateTransformMessage(ShipObject* scno, int8 dirX, int8 dirY, int8 dirZ, int8 dirW, int16 posX, int16 posZ, int16 posY, int16 velA, int16 velB, int8 rA, int8 rB, int8 rC) : BaseMessage(50) {

		Logger::console.info("shipUpdateTransformMessage1", true);

		float positionMultiplier = 4.0958748f;

		insertShort(0x08); //Opcode
		insertInt(0x76026fb9); //Message
	    insertShort(scno->getUniqueID());


	    //direction
	    insertByte((byte)dirX);
	    insertByte((byte)dirZ);
	    insertByte((byte)dirY);
	    insertByte((byte)dirW);

		insertShort((int16)posX*positionMultiplier);
	    insertShort((int16)posY*positionMultiplier);
		insertShort((int16)posZ*positionMultiplier);

	    insertShort(0);
	    insertShort(0);

	    insertByte(0);
	    insertByte(0);
	    insertByte(0);

	    insertInt(scno->getMovementCounter());
	}

	ShipUpdateTransformMessage(ShipObject* scno, int8 dirX, int8 dirY, int8 dirZ, int8 dirW,
			int16 posX, int16 posZ, int16 posY,
			PackedVelocity& velocity, PackedRotationRate& rA, PackedRotationRate& rB, PackedRotationRate& rC) : BaseMessage(50) {

			//Logger::console.info("shipUpdateTransformMessage2", true);

			float positionMultiplier = 4.0958748f;
			insertShort(0x08); //opcode

			insertInt(0x76026fb9); //Message
			insertShort(scno->getUniqueID());

		    //direction
		    insertByte((byte)dirW);
		    insertByte((byte)dirX);
		    insertByte((byte)dirZ);
		    insertByte((byte)dirY);

			insertShort((int16)posX*positionMultiplier);
			insertShort((int16)posY*positionMultiplier);
			insertShort((int16)posZ*positionMultiplier);

		    velocity.write(this);

		    rA.write(this);
		    rB.write(this);
		    rC.write(this);

			insertInt(scno->getMovementCounter());
		}

};

#endif /* SHIPUPDATETRANSFORMMESSAGE_H_ */

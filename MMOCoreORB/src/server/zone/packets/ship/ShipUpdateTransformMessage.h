/*
 * ShipUpdateTransformMessage.h
 *
 *  Created on: 01/09/2011
 *      Author: TheAnswer
 */

#ifndef SHIPUPDATETRANSFORMMESSAGE_H_
#define SHIPUPDATETRANSFORMMESSAGE_H_


#include "server/zone/objects/ship/ShipObject.h"

class ShipUpdateTransformMessage : public BaseMessage {
public:
	ShipUpdateTransformMessage(ShipObject* scno, int8 dirX, int8 dirY, int8 dirZ, int8 dirW, int16 posX, int16 posZ, int16 posY, int16 velA, int16 velB, int8 rA, int8 rB, int8 rC) : BaseMessage(50) {
		insertShort(0x08);
		insertInt(0x76026fb9);
	   // insertLong(scno->getObjectID());

	    insertShort(scno->getUniqueID());

		// add coordinates

	    //direction
	    insertByte((byte)dirX);
	    insertByte((byte)dirY);
	    insertByte((byte)dirZ);
	    insertByte((byte)dirW);


	    insertShort((int16)posX);
	    insertShort((int16)posZ);
	    insertShort((int16)posY);

	    insertShort(0);
	    insertShort(0);

	    insertByte(0);
	    insertByte(0);
	    insertByte(0);

	    insertInt(scno->getMovementCounter());
	}

};

#endif /* SHIPUPDATETRANSFORMMESSAGE_H_ */

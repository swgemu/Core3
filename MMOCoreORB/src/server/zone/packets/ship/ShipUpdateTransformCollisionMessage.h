/*
 * ShipUpdateTransformCollisionMessage.h
 *
 *  Created on: 01/09/2011
 *      Author: TheAnswer
 */

#ifndef SHIPUPDATETRANSFORMCOLLISIONMESSAGE_H_
#define SHIPUPDATETRANSFORMCOLLISIONMESSAGE_H_

#include "server/zone/objects/scene/SceneObject.h"

class ShipUpdateTransformCollisionMessage : public BaseMessage {
public:
	ShipUpdateTransformCollisionMessage(SceneObject* scno) : BaseMessage(50) {
		insertShort(0x08);
		insertInt(0x763648d0);
	    insertLong(scno->getObjectID());

		// add coordinates
		/*insertSignedShort((i(scno->getPositionX() * 4));
		insertSignedShort((int16) (scno->getPositionZ() * 4));
		insertSignedShort((int16) (scno->getPositionY() * 4));*/
	    //direction
	    insertFloat(scno->getDirectionX());
	    insertFloat(scno->getDirectionY());
	    insertFloat(scno->getDirectionZ());
	    insertFloat(scno->getDirectionW());

		insertFloat(scno->getPositionX());
	    insertFloat(scno->getPositionZ());
	    insertFloat(scno->getPositionY());

	    insertFloat(0);
	    insertFloat(0);
	    insertFloat(0);

		// add movement counter
		//insertInt(scno->getMovementCounter());

	    //collision?
	   
	    insertInt(scno->getMovementCounter());
	}

};


#endif /* SHIPUPDATETRANSFORMCOLLISIONMESSAGE_H_ */

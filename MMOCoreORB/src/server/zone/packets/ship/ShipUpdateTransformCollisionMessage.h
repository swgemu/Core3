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

		float positionMultiplier = 4.0958748f;

		Logger::console.info("ShipCollision", true);

		// add coordinates
		/*insertSignedShort((i(scno->getPositionX() * 4));
		insertSignedShort((int16) (scno->getPositionZ() * 4));
		insertSignedShort((int16) (scno->getPositionY() * 4));*/
		//direction
		insertFloat(scno->getDirectionX());
		insertFloat(scno->getDirectionZ());
		insertFloat(scno->getDirectionY());
		insertFloat(scno->getDirectionW());

		insertFloat(scno->getPositionX() * positionMultiplier);
		insertFloat(scno->getPositionY() * positionMultiplier);
		insertFloat(scno->getPositionZ() * positionMultiplier);

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

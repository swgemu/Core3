/*
 * ClientMfdStatusUpdateMessage.h
 *
 *  Created on: Nov 24, 2008
 *      Author: swgemu
 */

#ifndef CLIENTMFDSTATUSUPDATEMESSAGE_H_
#define CLIENTMFDSTATUSUPDATEMESSAGE_H_
#include "server/zone/Zone.h"

class ClientMfdStatusUpdateMessage : public BaseMessage {

public:
	ClientMfdStatusUpdateMessage() : BaseMessage() {
		insertShort(0x06);
		insertInt(0x2D2D6EE1);  // CRC

   }

	ClientMfdStatusUpdateMessage(SceneObject* sceno) : BaseMessage() {
		insertShort(0x06);
		insertInt(0x2D2D6EE1);  // CRC
		insertAscii(sceno->getZone()->getZoneName());
		insertLong(sceno->getObjectID());
		insertFloat(sceno->getWorldPositionX()); //x
		insertFloat(sceno->getWorldPositionZ()); //z
		insertFloat(sceno->getWorldPositionY()); //y
   }

   void UpdateMember(CreatureObject* cr, const String& planet, float x, float y, float z) {
		//Updates player info on other planets.
			insertAscii(planet); //Planet name
			insertLong(cr->getObjectID()); //Object id
			insertFloat(cr->getWorldPositionX()); //x
			insertFloat(cr->getWorldPositionZ()); //z
			insertFloat(cr->getWorldPositionY()); //y
   }
};
#endif /* CLIENTMFDSTATUSUPDATEMESSAGE_H_ */

/*
 * ClientMfdStatusUpdateMessage.h
 *
 *  Created on: Nov 24, 2008
 *      Author: swgemu
 */

#ifndef CLIENTMFDSTATUSUPDATEMESSAGE_H_
#define CLIENTMFDSTATUSUPDATEMESSAGE_H_

class ClientMfdUpdateStatusMessage : public BaseMessage {

public:
   ClientMfdUpdateStatusMessage() : BaseMessage() {
		insertShort(0x06);
		insertInt(0x2D2D6EE1);  // CRC

   }

   void UpdateMember(CreatureObject* cr, const String& planet, float x, float y, float z) {
		//Updates player info on other planets.
			insertAscii(planet); //Planet name
			insertLong(cr->getObjectID()); //Object id
			insertFloat(cr->getPositionX()); //x
			insertFloat(cr->getPositionY()); //y
			insertFloat(cr->getPositionZ()); //z
   }
};
#endif /* CLIENTMFDSTATUSUPDATEMESSAGE_H_ */

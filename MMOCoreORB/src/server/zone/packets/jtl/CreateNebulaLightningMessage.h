/*
 * CreateNebulaLightningMessage.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef CREATENEBULALIGHTNINGMESSAGE_H_
#define CREATENEBULALIGHTNINGMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "engine/util/u3d/Vector3.h"
#include "server/zone/packets/ship/PackedPosition.h"

class CreateNebulaLightningMessage : public BaseMessage {
public:
	CreateNebulaLightningMessage(uint16 lightningCount, int nebulaID, int startMili, int endMili, Vector3 startPoint, Vector3 endPoint) : BaseMessage() {
		insertShort(0xB);
		insertInt(STRING_HASHCODE("CreateNebulaLightningMessage")); // CRC

		insertShort(lightningCount); // Lightning ID
		insertInt(nebulaID); // Nebula #

		insertInt(startMili); // Timestamp start
		insertInt(endMili); // Timestamp end

		startPoint.toBinaryStream(this);

		endPoint.toBinaryStream(this);
	}
};

#endif /* CREATENEBULALIGHTNINGMESSAGE_H_ */

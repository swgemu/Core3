/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UPDATEPVPSTATUSMESSAGE_H_
#define UPDATEPVPSTATUSMESSAGE_H_

#include "engine/engine.h"

#include "server/zone/objects/tangible/TangibleObject.h"

class UpdatePVPStatusMessage : public BaseMessage {
public:
	UpdatePVPStatusMessage(TangibleObject* tano) : BaseMessage() {
		insertShort(0x04);
		insertInt(0x08A1C126);  //UpdatePVPStatusMessage
		insertInt(tano->getPvpStatusBitmask());
		insertInt(tano->getFaction());
		insertLong(tano->getObjectID());
	}

	UpdatePVPStatusMessage(TangibleObject* tano, uint32 pvpStatusBitmask) : BaseMessage() {
		insertShort(0x04);
		insertInt(0x08A1C126);  //UpdatePVPStatusMessage
		insertInt(pvpStatusBitmask);
		insertInt(tano->getFaction());
		insertLong(tano->getObjectID());
	}
};
#endif /*UPDATEPVPSTATUSMESSAGE_H_*/

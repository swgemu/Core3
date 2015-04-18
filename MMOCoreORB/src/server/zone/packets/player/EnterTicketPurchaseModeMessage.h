/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ENTERTICKETPURCHASEMODEMESSAGE_H_
#define ENTERTICKETPURCHASEMODEMESSAGE_H_

#include "engine/engine.h"
#include "server/zone/managers/planet/PlanetTravelPoint.h"

class EnterTicketPurchaseModeMessage : public BaseMessage {
public:
    EnterTicketPurchaseModeMessage(PlanetTravelPoint* ptp) {
		insertShort(0x04);
		insertInt(0x904DAE1A);  // CRC
        insertAscii(ptp->getPointZone());
        insertAscii(ptp->getPointName());
        insertByte(0);
    }
};

#endif /*ENTERTICKETPURCHASEMODEMESSAGE_H_*/

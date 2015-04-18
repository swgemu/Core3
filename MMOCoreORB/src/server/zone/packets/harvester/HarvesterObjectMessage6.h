/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTEROBJECTMESSAGE6_H_
#define HARVESTEROBJECTMESSAGE6_H_

#include "../BaseLineMessage.h"

#include "../../objects/installation/harvester/HarvesterObject.h"

class HarvesterObjectMessage6 : public BaseLineMessage {
public:
	HarvesterObjectMessage6(HarvesterObject * hino)
			: BaseLineMessage(hino->getObjectID(), 0x4F4E4948, 6, 0x05) {
		insertInt(0x42);
		
		insertInt(0); //counter of uint64's I believe.
		insertInt(0); //update count.
		
		setSize();
	}
};
#endif /*HARVESTEROBJECTMESSAGE6_H_*/

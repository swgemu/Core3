/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LAIROBJECTMESSAGE6_H_
#define LAIROBJECTMESSAGE6_H_

#include "../BaseLineMessage.h"

#include "../../objects/tangible/lair/LairObject.h"

class LairObjectMessage6 : public BaseLineMessage {
public:
	LairObjectMessage6(LairObject* tano)
			: BaseLineMessage(tano->getObjectID(), 0x54414E4F, 6, 0x04) {
		insertInt(0x59);
		insertAscii(tano->getTemplateDetailName());
		insertInt(0);
		insertAscii(tano->getTemplateDetail());
		insertInt(0);
		insertInt(0);
		insertByte(0);

		setSize();
	}

};

#endif /*ATTACKABLEOBJECTMESSAGE6_H_*/

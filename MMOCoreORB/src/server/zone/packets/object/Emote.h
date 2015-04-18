/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EMOTE_H_
#define EMOTE_H_

#include "ObjectControllerMessage.h"

class Emote : public ObjectControllerMessage {
public:
	Emote(CreatureObject* creo, CreatureObject* play, uint64 target, uint32 emoteid, bool showtext)
			: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0x12E) {

		insertLong(play->getObjectID());
		insertLong(target);
		insertInt(emoteid);

		if (showtext)
			insertByte(3);
		else
			insertByte(1);
	}

	Emote(CreatureObject* emoter, uint64 targetid, uint32 emoteid, bool showtext)
			: ObjectControllerMessage(emoter->getObjectID(), 0x0B, 0x12E) {

		insertLong(emoter->getObjectID());
		insertLong(targetid);
		insertInt(emoteid);

		if (showtext)
			insertByte(3);
		else
			insertByte(1);
	}

};

#endif /*EMOTE_H_*/

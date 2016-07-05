/*
 * AreaTrackSuiCallback.h
 *
 *  Created on: Feb 5, 2012
 *      Author: Kyle
 */

#ifndef AREATRACKSUICALLBACK_H_
#define AREATRACKSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/events/AreaTrackTask.h"
#include "server/zone/packets/object/Emote.h"


class AreaTrackSuiCallback : public SuiCallback {
	String nodeName;

public:
	AreaTrackSuiCallback(ZoneServer* serv, const String& name) : SuiCallback(serv) {
		nodeName = name;
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( sui);

		if(!creature->isPlayerCreature())
			return;

		if(!cancelPressed) {

			int index = Integer::valueOf(args->get(0).toString());

			if(index < 0 || index > 2)
				return;

			if(server != NULL) {
				uint64 objectID = creature->getObjectID();
				Emote* emsg = new Emote(objectID, objectID, 0, 72, true, false);
				creature->broadcastMessage(emsg, true);
				creature->sendSystemMessage("@skl_use:sys_scan_begin"); // You begin to examine the environment for information.

				Reference<AreaTrackTask*> att = new AreaTrackTask(creature, index);
				creature->addPendingTask("areatrack", att, 6000);
				creature->addCooldown("areatrack", 6000);
			}
		}
	}
};

#endif /* AREATRACKSUICALLBACK_H_ */

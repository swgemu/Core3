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

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
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

				Emote* emsg = new Emote(creature, creature, 0, 72, false);
				creature->broadcastMessage(emsg, true);

				AreaTrackTask* att = new AreaTrackTask(creature, index);
				creature->addPendingTask("areatrack", att, 6000);
				creature->addCooldown("areatrack", 6000);
			}
		}
	}
};

#endif /* AREATRACKSUICALLBACK_H_ */

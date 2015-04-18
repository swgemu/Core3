/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYEROBJECTMESSAGE8_H_
#define PLAYEROBJECTMESSAGE8_H_

#include "../BaseLineMessage.h"

#include "server/zone/objects/player/PlayerObject.h"
#include "../../objects/player/variables/WaypointList.h"


class PlayerObjectMessage8 : public BaseLineMessage {
public:
	PlayerObjectMessage8(PlayerObjectImplementation* play)
			: BaseLineMessage(play->getObjectID(), 0x504C4159, 8, 0x07) {
		// experiences
		DeltaVectorMap<String, int>* xpList = play->getExperienceList();
		xpList->insertToMessage(this);

		// waypoints
		play->insertWaypointListToMessage(this);

		// force bar stats
		insertInt(play->getForcePower());
		insertInt(play->getForcePowerMax());

		// completed quests
		DeltaBitArray* completedQuests = play->getCompletedQuests();
		completedQuests->insertToMessage(this);

		// active quests
		DeltaBitArray* activeQuests = play->getActiveQuests();
		activeQuests->insertToMessage(this);

		// quests
		DeltaVectorMap<uint32, PlayerQuestData>* quests = play->getPlayerQuestsData();
		quests->insertToMessage(this);

		//
		insertInt(0);
		insertInt(0);

		setSize();
	}

};

#endif /*PLAYEROBJECTMESSAGE8_H_*/

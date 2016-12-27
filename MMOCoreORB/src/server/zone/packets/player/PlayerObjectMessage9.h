/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLAYEROBJECTMESSAGE9_H_
#define PLAYEROBJECTMESSAGE9_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/variables/AbilityList.h"

class PlayerObjectMessage9 : public BaseLineMessage {
public:
	PlayerObjectMessage9(PlayerObjectImplementation* play)
			: BaseLineMessage(play->getObjectID(), 0x504C4159, 9, 0x13) {
		// certifications && skills
		AbilityList* skills = play->getAbilityList();
		skills->insertToMessage(this);

		// crafting states
		insertInt(0);
		insertInt(0);

		// Nearest crafting station
		insertLong(0);

		// datapad draft schematics
		DeltaVector<ManagedReference<DraftSchematic* > >* schematics = play->getSchematics();
		schematics->insertToMessage(this);

		// crafting?
		insertInt(0);

		// species data
		insertInt(0);

		// friends list
		/*DeltaVector<String>* friends = play->getFriendList();
		friends->insertToMessage(this);*/
		insertInt(0);
		insertInt(0);

		// ignore list
		/*DeltaVector<String>* ignores = play->getIgnoreList();
		ignores->insertToMessage(this);*/
		insertInt(0);
		insertInt(0);

		// language
		insertInt(play->getLanguageID());

		// stomach fillings
		insertInt(play->getFoodFilling());
		insertInt(play->getFoodFillingMax());
		insertInt(play->getDrinkFilling());
		insertInt(play->getDrinkFillingMax());

		//
		insertInt(0);
		insertInt(0);

		// waypoint list?
		insertInt(0);
		insertInt(0);

		// jedi state
		insertInt(play->getJediState());

		setSize();
	}
};

#endif /*PLAYEROBJECTMESSAGE9_H_*/

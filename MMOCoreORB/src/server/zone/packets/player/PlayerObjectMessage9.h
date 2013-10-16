/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef PLAYEROBJECTMESSAGE9_H_
#define PLAYEROBJECTMESSAGE9_H_

#include "../BaseLineMessage.h"

#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/variables/AbilityList.h"

//#include "../../objects/draftschematic/DraftSchematic.h"

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

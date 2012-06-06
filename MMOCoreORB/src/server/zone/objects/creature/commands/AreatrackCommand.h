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

#ifndef AREATRACKCOMMAND_H_
#define AREATRACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/callbacks/AreaTrackSuiCallback.h"

class AreatrackCommand : public QueueCommand {
public:

	AreatrackCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if(!creature->isPlayerCreature())
			return GENERALERROR;

		if(!creature->hasSkill("outdoors_ranger_novice"))
			return GENERALERROR;

		if(creature->getParent() != NULL && creature->getParent().get()->isCellObject()) {
			creature->sendSystemMessage("@skl_use:sys_scan_inside");
			return GENERALERROR;
		}

		CooldownTimerMap* cooldownTimerMap = creature->getCooldownTimerMap();
		if(cooldownTimerMap == NULL || !cooldownTimerMap->isPast("areatrack"))
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		if (ghost == NULL || ghost->hasSuiBoxWindowType(SuiWindowType::RANGER_TRACK_OPTIONS)) {
			return 0;
		}

		ManagedReference<SuiListBox*> chooseTrackTarget = new SuiListBox(creature, SuiWindowType::RANGER_TRACK_OPTIONS);
		chooseTrackTarget->setUsingObject(creature);
		chooseTrackTarget->setCallback(new AreaTrackSuiCallback(server->getZoneServer(), "AreaTrack"));

		chooseTrackTarget->setPromptTitle("@skl_use:scan_type_t");
		chooseTrackTarget->setPromptText("What do you want to track?");

		chooseTrackTarget->addMenuItem("@cmd_n:areatrack_animal");

		if(creature->hasSkill("outdoors_ranger_harvest_01"))
			chooseTrackTarget->addMenuItem("@cmd_n:areatrack_npc");

		if(creature->hasSkill("outdoors_ranger_harvest_04"))
			chooseTrackTarget->addMenuItem("@cmd_n:areatrack_player");

		chooseTrackTarget->setCancelButton(true, "");
		chooseTrackTarget->setOkButton(true, "@ok");

		ghost->addSuiBox(chooseTrackTarget);
		creature->sendMessage(chooseTrackTarget->generateMessage());

		return SUCCESS;
	}

};

#endif //AREATRACKCOMMAND_H_

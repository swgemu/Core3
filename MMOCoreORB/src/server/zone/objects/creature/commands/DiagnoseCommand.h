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

#ifndef DIAGNOSECOMMAND_H_
#define DIAGNOSECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

class DiagnoseCommand : public QueueCommand {
	float range;
public:

	DiagnoseCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		range = 6;
		//defaultTime = 0;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isCreatureObject()) {
			creature->sendSystemMessage("You can only diagnose a player or a creature.");
			return GENERALERROR;
		}

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if (!creatureTarget->isInRange(creature, range))
			return TOOFAR;

		if (creatureTarget == creature) {
			creature->sendSystemMessage("You can't diagnose yourself.");
			return GENERALERROR;
		}

		/*TODO: Close an already opened Diagnose box before sending a new one??
				if (player->hasSuiBox(SuiWindowType::DIAGNOSE))
					player->removeSuiBox(SuiWindowType::DIAGNOSE);
		 */

		/*UnicodeString UnicodeStringName = UnicodeString("");
		UnicodeStringName = creatureTarget->getFirstName();*/
		StringId* objectName = creatureTarget->getObjectName();

		String targetName = objectName->getCustomString().toString();

		if (targetName.isEmpty()) {
			 objectName->getFullPath(targetName);
		}

		CreatureObject* player = cast<CreatureObject*>(creature);

		ManagedReference<SuiListBox*> sui = new SuiListBox(player, SuiWindowType::MEDIC_DIAGNOSE);
		StringBuffer title;
		title << "Patient " << targetName.toCharArray();
		sui->setPromptTitle(title.toString());

		StringBuffer text;
		text << "Below is a listing of the wound and Battle Fatigue levels of " << targetName.toCharArray() << ". Wounds are healed through /tendwound or use of wound Medpacks. High levels of Battle Fatigue can inhibit the healing process, and Battle Fatigue can only be healed by the patient choosing to watch performing entertainers.";
		sui->setPromptText(text.toString());
		sui->setCancelButton(false, "");

		StringBuffer health;
		health << "Health -- " << creatureTarget->getWounds(CreatureAttribute::HEALTH);
		sui->addMenuItem(health.toString());

		StringBuffer strength;
		strength << "Strength -- " << creatureTarget->getWounds(CreatureAttribute::STRENGTH);
		sui->addMenuItem(strength.toString());

		StringBuffer constitution;
		constitution << "Constitution -- " << creatureTarget->getWounds(CreatureAttribute::CONSTITUTION);
		sui->addMenuItem(constitution.toString());

		StringBuffer action;
		action << "Action -- " << creatureTarget->getWounds(CreatureAttribute::ACTION);
		sui->addMenuItem(action.toString());

		StringBuffer quickness;
		quickness << "Quickness -- " << creatureTarget->getWounds(CreatureAttribute::QUICKNESS);
		sui->addMenuItem(quickness.toString());

		StringBuffer stamina;
		stamina << "Stamina -- " << creatureTarget->getWounds(CreatureAttribute::STAMINA);
		sui->addMenuItem(stamina.toString());

		StringBuffer mind;
		mind << "Mind -- " << creatureTarget->getWounds(CreatureAttribute::MIND);
		sui->addMenuItem(mind.toString());

		StringBuffer focus;
		focus << "Focus -- " << creatureTarget->getWounds(CreatureAttribute::FOCUS);
		sui->addMenuItem(focus.toString());

		StringBuffer willpower;
		willpower << "Willpower -- " << creatureTarget->getWounds(CreatureAttribute::WILLPOWER);
		sui->addMenuItem(willpower.toString());

		StringBuffer battlefatigue;
		battlefatigue << "Battle Fatigue -- " << creatureTarget->getShockWounds();
		sui->addMenuItem(battlefatigue.toString());

		player->getPlayerObject()->addSuiBox(sui);
		player->sendMessage(sui->generateMessage());

		return SUCCESS;
	}

};

#endif //DIAGNOSECOMMAND_H_

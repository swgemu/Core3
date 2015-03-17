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

#ifndef SETPLAYERAPPEARANCECOMMAND_H_
#define SETPLAYERAPPEARANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetPlayerAppearanceCommand : public QueueCommand {
public:

	SetPlayerAppearanceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PlayerObject* ghost = creature->getPlayerObject();
		if (!ghost->isPrivileged())
			return INSUFFICIENTPERMISSION;

		ManagedReference<CreatureObject*> targetCreature = NULL;
		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();

		UnicodeTokenizer tokenizer(arguments);
		String templateName = "";
		String targetName = "";
		String argument;

		if (creature->getTargetID() != 0) {
			targetCreature = server->getZoneServer()->getObject(creature->getTargetID()).castTo<CreatureObject*>();
		} else {
			if (!tokenizer.hasMoreTokens()) {
				sendSyntax(creature);
				return GENERALERROR;
			}

			tokenizer.getStringToken(targetName);
			targetCreature = playerManager->getPlayer(targetName);
		}

		if (targetCreature == NULL || !targetCreature->isPlayerCreature()) {
			sendSyntax(creature);
			return INVALIDTARGET;
		}

		if (tokenizer.hasMoreTokens())
			tokenizer.getStringToken(argument);

		if (argument != "" && (argument.indexOf(".iff") == -1 || argument.indexOf("object/mobile/shared_") == -1)) {
			creature->sendSystemMessage("Invalid template. Template must be in object/mobile and have shared_ in its filename or left blank to reset to the default template. Example: object/mobile/shared_darth_vader.iff");
			return GENERALERROR;
		} else if (argument != "") {
			TemplateManager* templateManager = TemplateManager::instance();
			String templateTest = argument.replaceFirst("shared_", "");
			SharedObjectTemplate* templateData = templateManager->getTemplate(templateTest.hashCode());
			if (templateData == NULL) {
				creature->sendSystemMessage("Unable to find template. Template must be in object/mobile and have shared_ in its filename or left blank to reset to the default template. Example: object/mobile/shared_darth_vader.iff");
				return GENERALERROR;
			}
			templateName = argument;
		}

		targetCreature->setAlternateAppearance(templateName, true);

		// Required to reset a target to its normal template
		if (templateName == "") {
			creature->sendSystemMessage("The target's player appearance temple has been reset to its default.");
			targetCreature->switchZone(targetCreature->getZone()->getZoneName(), targetCreature->getPositionX(), targetCreature->getPositionZ(), targetCreature->getPositionY(), targetCreature->getParentID());
		}

		return SUCCESS;
	}

	void sendSyntax(CreatureObject* creature) {
		creature->sendSystemMessage("SYNTAX: /setPlayerAppearance [player] [mobile object template with shared in filename or blank to reset]");
		creature->sendSystemMessage("EXAMPLE: /setPlayerAppearance playerName object/mobile/shared_darth_vader.iff");
		creature->sendSystemMessage("EXAMPLE RESET: /setPlayerAppearance playerName");
	}

};

#endif //SETPLAYERAPPEARANCECOMMAND_H_

/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETPLAYERAPPEARANCECOMMAND_H_
#define SETPLAYERAPPEARANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetPlayerAppearanceCommand : public QueueCommand {
public:

	SetPlayerAppearanceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

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

		if (target != 0) {
			targetCreature = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();
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

		Locker targetLocker(targetCreature, creature);

		targetCreature->setAlternateAppearance(templateName, true);

		// Required to reset a target to its normal template
		if (templateName == "") {
			creature->sendSystemMessage("The target's player appearance temple has been reset to its default.");
			targetCreature->switchZone(targetCreature->getZone()->getZoneName(), targetCreature->getPositionX(), targetCreature->getPositionZ(), targetCreature->getPositionY(), targetCreature->getParentID());
		}

		return SUCCESS;
	}

	void sendSyntax(CreatureObject* creature) const {
		creature->sendSystemMessage("SYNTAX: /setPlayerAppearance [player] [mobile object template with shared in filename or blank to reset]");
		creature->sendSystemMessage("EXAMPLE: /setPlayerAppearance playerName object/mobile/shared_darth_vader.iff");
		creature->sendSystemMessage("EXAMPLE RESET: /setPlayerAppearance playerName");
	}

};

#endif //SETPLAYERAPPEARANCECOMMAND_H_

/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PRONECOMMAND_H_
#define PRONECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/terminal/characterbuilder/CharacterBuilderTerminal.h"

class ProneCommand : public QueueCommand {
public:

	ProneCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->hasAttackDelay())
			return GENERALERROR;

		// TODO: DELETE STARTING HERE
		UnicodeTokenizer args(arguments);

		if (args.hasMoreTokens()) {
			if (creature->isPlayerCreature()) {
				PlayerObject* ghost = creature->getPlayerObject();

				if (ghost == NULL)
					return GENERALERROR;

				if (!ghost->hasAbility("admin")) {
					if (creature->isDizzied() && System::random(100) < 85) {
						creature->queueDizzyFallEvent();
					} else {
						creature->setPosture(CreaturePosture::PRONE);
					}

					return SUCCESS;
				}

				ZoneServer* zserv = server->getZoneServer();

				String blueFrogTemplate = "object/tangible/terminal/terminal_character_builder.iff";
				ManagedReference<CharacterBuilderTerminal*> blueFrog = ( zserv->createObject(blueFrogTemplate.hashCode(), 0)).castTo<CharacterBuilderTerminal*>();

				if (blueFrog == NULL)
					return GENERALERROR;

				Locker clocker(blueFrog, creature);

				float x = creature->getPositionX();
				float y = creature->getPositionY();
				float z = creature->getPositionZ();//creature->getZone()->getHeight(x, y);

				ManagedReference<SceneObject*> parent = creature->getParent().get();

				blueFrog->initializePosition(x, z, y);
								blueFrog->setDirection(creature->getDirectionW(), creature->getDirectionX(), creature->getDirectionY(), creature->getDirectionZ());

				if (parent != NULL && parent->isCellObject())
					parent->transferObject(blueFrog, -1);
				else
					creature->getZone()->transferObject(blueFrog, -1, true);

				info("blue frog created", true);
			}
		} else {// TODO STOP DELETE HERE
			if (creature->isDizzied() && System::random(100) < 85) {
				creature->queueDizzyFallEvent();
			} else {
				creature->setPosture(CreaturePosture::PRONE);
			}
		}// TODO DELETE THIS LINE

		return SUCCESS;
	}

};

#endif //PRONECOMMAND_H_

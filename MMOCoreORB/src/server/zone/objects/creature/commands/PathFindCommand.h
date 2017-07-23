//
// Created by theanswer on 6/18/17.
//

#ifndef CORE3_PATHFINDCOMMAND_H
#define CORE3_PATHFINDCOMMAND_H

#include "engine/engine.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/managers/collision/PathFinderManager.h"
#include "server/zone/managers/collision/CollisionManager.h"

#include "server/zone/packets/ui/CreateClientPathMessage.h"
#include "server/zone/packets/ui/DestroyClientPathMessage.h"

class PathFindCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		PlayerObject* ghost = creature->getPlayerObject();
		Zone* zone = creature->getZone();

		if (ghost == nullptr || ghost->getAdminLevel() < 15 || zone == nullptr)
			return 1;

		if (arguments == "clear") {
			DestroyClientPathMessage* msg = new DestroyClientPathMessage();

			creature->sendMessage(msg);
			return 0;
		}

		try {
			StringTokenizer args(arguments.toString());

			Vector3 position;

			position.setX(args.getFloatToken());
			position.setY(args.getFloatToken());

			if (args.hasMoreTokens()) {
				position.setZ(args.getFloatToken());
			} else {
				position.setZ(CollisionManager::getWorldFloorCollision(position.getX(), position.getY(), zone, false));
			}

			Reference<Vector<WorldCoordinates>*> path = PathFinderManager::instance()->findPath(WorldCoordinates(creature), WorldCoordinates(position, nullptr), zone);

			if (path != nullptr && path->size()) {
				CreateClientPathMessage* msg = new CreateClientPathMessage();
				StringBuffer messageBoxText;

				for (int i = 0; i < path->size(); i++) {
					WorldCoordinates& point = path->get(i);
					msg->addCoordinate(point.getX(), point.getZ(), point.getY());

					messageBoxText << point.toString() << endl;
				}

				creature->sendMessage(msg);

				SuiMessageBox* box = new SuiMessageBox(creature, 0);

				box->setPromptTitle("World path find results");
				box->setPromptText(messageBoxText.toString());

				ghost->addSuiBox(box);
				creature->sendMessage(box->generateMessage());
			} else {
				creature->sendSystemMessage("Path was null!");
			}

		} catch (Exception& e) {
			sendSyntax(creature);
		}

		return 0;
	}

	static void sendSyntax(CreatureObject* player) {
		player->sendSystemMessage("Syntax: /server pathfind <x> <y>");
	}
};

#endif //CORE3_PATHFINDCOMMAND_H

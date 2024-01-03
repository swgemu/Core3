/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TELEPORTCOMMAND_H_
#define TELEPORTCOMMAND_H_

#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/intangible/tasks/LaunchShipTask.h"
#include "server/zone/objects/intangible/tasks/StoreShipTask.h"

class TeleportCommand : public QueueCommand {
public:

	TeleportCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (creature == nullptr)
			return GENERALERROR;

		ZoneServer* zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		Vector3 newPosition;

		String zoneName;
		uint64 parentID = 0;

		try {
			UnicodeTokenizer tokenizer(arguments);

			newPosition.setX(tokenizer.getFloatToken());
			newPosition.setY(tokenizer.getFloatToken());

			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(zoneName);

			if (tokenizer.hasMoreTokens()) {
				newPosition.setZ(tokenizer.getFloatToken());
				parentID = tokenizer.getLongToken();
			}

			if (zoneName == "") {
				auto zone = creature->getZone();

				if (zone != nullptr)
					zoneName = zone->getZoneName();
			}

			bool newZoneIsSpace = zoneName.contains("space");
			ManagedReference<ShipObject*> ship = nullptr;

			// Handle a player that is piloting a ship
			if (creature->isPilotingShip()) {
				SceneObject* datapad = creature->getSlottedObject("datapad");
				ShipControlDevice* shipControlDevice = nullptr;

				if (datapad != nullptr) {
					for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
						SceneObject* datapadObject = datapad->getContainerObject(i);

						if (datapadObject == nullptr || !datapadObject->isShipControlDevice())
							continue;

						shipControlDevice = cast<ShipControlDevice*>(datapadObject);

						if (shipControlDevice == nullptr)
							continue;

						if (shipControlDevice->isShipLaunched()) {
							break;
						}

						shipControlDevice = nullptr;
					}
				}

				if (!newZoneIsSpace) {
					if (shipControlDevice != nullptr) {
						StoreShipTask* storeTask = new StoreShipTask(creature, shipControlDevice, zoneName, newPosition);

						if (storeTask == nullptr)
							return GENERALERROR;

						storeTask->execute();
					}
				} else {
					if (shipControlDevice != nullptr) {
						Vector<uint64> dummyVec;
						LaunchShipTask* launchTask = new LaunchShipTask(creature, shipControlDevice, dummyVec);

						if (launchTask == nullptr)
							return GENERALERROR;

						launchTask->execute();
						return SUCCESS;
					}
				}
			}

			// Get the world floor and set players direction in the ground zone
			if (!newZoneIsSpace) {
				auto newZone = zoneServer->getZone(zoneName);

				if (newZone != nullptr) {
					newPosition.setZ(CollisionManager::getWorldFloorCollision(newPosition.getX(), newPosition.getY(), newZone, false));
					creature->setDirection(0);
				}
			}

			creature->switchZone(zoneName, newPosition.getX(), newPosition.getZ(), newPosition.getY(), parentID);
		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /teleport <x> <y> [<planet>] [<z> <parentID>]");
		}

		return SUCCESS;
	}

};

#endif //TELEPORTCOMMAND_H_

/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETOBJVARSCOMMAND_H_
#define GETOBJVARSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

class GetObjVarsCommand : public QueueCommand {
public:
	GetObjVarsCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!creature->isPlayerCreature())
			return GENERALERROR;

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		uint64 objectID = 0;
		UnicodeTokenizer tokenizer(arguments);
		tokenizer.setDelimeter(" ");

		// if we have an argument passed, use it
		if (tokenizer.hasMoreTokens()) {
			try {
				objectID = tokenizer.getLongToken();
			} catch (Exception& err) {
				creature->sendSystemMessage("INVALID OBJECT.  Please specify a valid object name or objectid");
				return INVALIDPARAMETERS;
			}
		} else {
			objectID = target;
		}

		if (objectID == 0) {
			creature->sendSystemMessage("You need to target an object or specify an object id: /getobjvars <objectID> ");
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(objectID, false);

		if (object == nullptr) {
			creature->sendSystemMessage("ERROR GETTIGN OBJECT - nullptr " + String::valueOf(objectID));
		} else {
			String nameString = object->getObjectNameStringIdName();
			String strDescription = object->getDetailedDescription();
			bool bMarkedForDelete = object->_isMarkedForDeletion();

			bool bIsUpdated = object->_isUpdated();
			int rCount = object.get()->getReferenceCount();
			uint64 parentID = object->getParentID();
			StringBuffer msg;
			msg << endl << "OBJECTID: " << String::valueOf(objectID) << endl;
			msg << "OBJECTTYPE: " << String::valueOf(object->getGameObjectType()) << endl;

			if (object->isCreatureObject()) {
				msg << "Creature First Name: " << object.castTo<CreatureObject*>()->getFirstName() << endl;
			}

			msg << "Object Name String: " << nameString << endl;
			msg << "_className: " << object->_getClassName() << endl;
			msg << "Marked for deletion: " << String::valueOf(bMarkedForDelete) << endl;
			msg << "IsUpdated: " << String::valueOf(bIsUpdated) << endl;
			msg << "REFERENCE COUNT " << String::valueOf(rCount) << endl;
			msg << "Path: " << object->getObjectTemplate()->getFullTemplateString() << endl;
			msg << "Children: " << String::valueOf(object->getChildObjects()->size()) << endl;
			msg << "PARENT OBJECTID: " << String::valueOf(parentID) << endl;

			if (object->isCreatureObject()) {
				CreatureObject* creoObject = object->asCreatureObject();

				if (creoObject != nullptr) {
					String aiEnabled = (creoObject->getOptionsBitmask() & OptionBitmask::AIENABLED ? "True" : "False");
					msg << "AI Enabled: " << aiEnabled << endl;
					msg << "PvP Status Bitmask: " << creoObject->getPvpStatusBitmask() << endl;
					msg << "Options Bitmask: " << creoObject->getOptionsBitmask() << endl;

					if (object->isAiAgent()) {
						AiAgent* objectAgent = object->asAiAgent();

						if (objectAgent != nullptr) {
							msg << "Creature Bitmask: " << objectAgent->getCreatureBitmask() << endl;
							msg << "Creature Movement State: " << objectAgent->getMovementState() << endl;

							ManagedReference<SceneObject*> followCopy = objectAgent->getFollowObject();
							StringBuffer hasFollow;

							if (followCopy != nullptr) {
								hasFollow << "True - " << " OID: " << followCopy->getObjectID();
							} else {
								hasFollow << "False";
							}

							msg << "Has Follow Object: " << hasFollow.toString() << endl;
							msg << "Current total Patrol Points: " << objectAgent->getPatrolPointSize() << endl;
							msg << "In Navmesh: " << (objectAgent->isInNavMesh() ? "True" : "False") << endl;

							msg << "\n\n";

							msg << "Current Weapon: ";

							if (objectAgent->getCurrentWeapon() != nullptr) {
								msg << objectAgent->getCurrentWeapon()->getObjectTemplate()->getTemplateFileName() << " ID: " << objectAgent->getCurrentWeapon()->getObjectID() << endl;
							} else {
								msg << "nullptr" << endl;
							}

							msg << "Default Weapon: ";

							if (objectAgent->getDefaultWeapon() != nullptr) {
								msg << objectAgent->getDefaultWeapon()->getObjectTemplate()->getTemplateFileName() << " ID: " << objectAgent->getDefaultWeapon()->getObjectID() << endl;
							} else {
								msg << "nullptr" << endl;
							}

							msg << "Primary Weapon: ";

							if (objectAgent->getPrimaryWeapon() != nullptr) {
								msg << objectAgent->getPrimaryWeapon()->getObjectTemplate()->getTemplateFileName() << " ID: " << objectAgent->getPrimaryWeapon()->getObjectID() << endl;
							} else {
								msg << "nullptr" << endl;
							}

							msg << "Secondary Weapon: ";

							if (objectAgent->getSecondaryWeapon() != nullptr) {
								msg << objectAgent->getSecondaryWeapon()->getObjectTemplate()->getTemplateFileName() << " ID: " << objectAgent->getSecondaryWeapon()->getObjectID() << endl;
							} else {
								msg << "nullptr" << endl;
							}

							// Space output
							msg << "\n";

							// Inventory Contents
							auto inventory = objectAgent->getInventory();

							if (inventory != nullptr) {
								msg << "Agent Inventory size: " << inventory->getContainerObjectsSize() << endl;

								for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
									auto invObject = inventory->getContainerObject(i);

									if (invObject != nullptr) {
										msg << "Inventory - #" << i << " Item: " << invObject->getObjectNameStringIdName() << " -- " << invObject->getObjectTemplate()->getTemplateFileName() << " ID: " << invObject->getObjectID() << endl;
									}
								}
							}

							// Space output
							msg << "\n";

							// Home Object - Lairs
							uint64 homeID = 0;
							String homeName = "none";
							ManagedReference<SceneObject*> homeLair = objectAgent->getHomeObject().get();

							if (homeLair != nullptr) {
								homeID = homeLair->getObjectID();
								homeName = homeLair->getObjectNameStringIdName();
							}

							msg << "Home Object: " << homeName << " ID: " << homeID << endl;

							// Space output
							msg << "\n";
						}
					} else if (creoObject->isPlayerCreature()) {
						auto playerManager = server->getPlayerManager();

						if (playerManager != nullptr) {
							int playerLevel = playerManager->calculatePlayerLevel(creoObject);

							msg << "Player Level: " << playerLevel << endl;
						}
					}

					if (creoObject->isGrouped()) {
						GroupObject* group = creoObject->getGroup();

						if (group != nullptr)
							msg << "Group Level: " << group->getGroupLevel() << endl;
					}

					SortedVector<ManagedReference<ActiveArea*>>* areas = creoObject->getActiveAreas();

					if (areas != nullptr) {
						for (int i = 0; i < areas->size(); i++) {
							ActiveArea* area = areas->get(i);

							if (area == nullptr)
								continue;

							msg << "Area #" << i << " -- " << area->getAreaName() << endl;
						}
					}
				}
			} else if (object->isShipObject()) {
				ShipObject* ship = object->asShipObject();

				if (ship != nullptr) {
					String aiEnabled = (ship->getOptionsBitmask() & OptionBitmask::AIENABLED ? "True" : "False");
					msg << "AI Enabled: " << aiEnabled << endl;
					msg << "PvP Status Bitmask: " << ship->getPvpStatusBitmask() << endl;
					msg << "Options Bitmask: " << ship->getOptionsBitmask() << endl;

					if (ship->isShipAiAgent()) {
						ShipAiAgent* shipAgent = ship->asShipAiAgent();

						if (shipAgent != nullptr) {
							msg << "Ship Agent Movement State: " << shipAgent->getMovementState() << endl;

							ManagedReference<ShipObject*> followCopy = shipAgent->getFollowShipObject();
							StringBuffer hasFollow;

							if (followCopy != nullptr) {
								hasFollow << "True - " << " OID: " << followCopy->getObjectID();
							} else {
								hasFollow << "False";
							}

							msg << "Has Follow Object: " << hasFollow.toString() << endl;

							ManagedReference<ShipObject*> targetCopy = shipAgent->getTargetShipObject();
							StringBuffer hasTarget;

							if (targetCopy != nullptr) {
								hasTarget << "True - " << " OID: " << targetCopy->getObjectID();
							} else {
								hasTarget << "False";
							}

							msg << "Has Target Object: " << hasTarget.toString() << endl;
							msg << "Current total Patrol Points: " << shipAgent->getPatrolPointSize() << endl;
						}

					}
				}
			}

			if (object->getZone() != nullptr) {
				msg << "Location: " << object->getPosition().toString() << " " << object->getZone()->getZoneName() << endl;
				msg << "Direction Angle - Radians: " << object->getDirection()->getRadians() << endl;
			}

			ManagedReference<CityRegion*> city = object->getCityRegion().get();

			if (city != nullptr)
				msg << "City Region oid: " << String::valueOf(city->getObjectID()) << ", name: " << city->getRegionDisplayedName() << endl;

			creature->sendSystemMessage(msg.toString());

			ChatManager* chatManager = server->getZoneServer()->getChatManager();
			String title = "getObjVars - " + String::valueOf(objectID);
			chatManager->sendMail("System", title, msg.toString(), creature->getFirstName());

			ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);

			if (box != nullptr) {
				StringBuffer titleStr;
				titleStr << "GetObjVars: " << objectID;

				box->setPromptTitle(titleStr.toString());
				box->setPromptText(msg.toString());

				ghost->addSuiBox(box);
				creature->sendMessage(box->generateMessage());
			}
		}

		return SUCCESS;
	}
};

#endif // GETOBJVARSCOMMAND_H_

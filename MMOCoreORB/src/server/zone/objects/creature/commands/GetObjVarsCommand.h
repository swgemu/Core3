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
		if (!creature->isPlayerCreature()) {
			return GENERALERROR;
		}

		auto ghost = creature->getPlayerObject();

		if (ghost == nullptr) {
			return GENERALERROR;
		}

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

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(objectID, false);

		if (object == nullptr) {
			creature->sendSystemMessage("ERROR GETTIGN OBJECT - nullptr " + String::valueOf(objectID));
			return INVALIDTARGET;
		}

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);

		if (box == nullptr) {
			return GENERALERROR;
		}

		/*
		*	General Object Information
		*/

		String nameString = object->getObjectNameStringIdName();
		String strDescription = object->getDetailedDescription();
		bool bMarkedForDelete = object->_isMarkedForDeletion();

		bool bIsUpdated = object->_isUpdated();
		int rCount = object.get()->getReferenceCount();
		uint64 parentID = object->getParentID();

		uint32 covSize = 0;
		auto closeObjectsVector = object->getCloseObjects();

		if (closeObjectsVector != nullptr) {
			covSize = closeObjectsVector->size();
		}

		StringBuffer msg;
		msg << endl << "General Object Information:" << endl << endl <<
		"Object ID: " << objectID << endl << endl <<
		"Parent ID: " << parentID << endl <<
		"Child Objects Size: " << object->getChildObjects()->size() << endl <<
		"Close Objects Vector COV Size: " << covSize << endl <<

		endl << // Spacer

		"Object Type: " << object->getGameObjectType() << endl <<
		"Object Name String: " << nameString << endl <<
		"_className: " << object->_getClassName() << endl <<
		"Template Path: " << object->getObjectTemplate()->getFullTemplateString() << endl <<

		endl << // Spacer

		"Reference Count: " << rCount << endl <<
		"Marked for deletion: " << bMarkedForDelete << endl <<
		"IsUpdated: " << bIsUpdated << endl << endl <<
		"TreeNode is null: " << (object->getNode() == nullptr ? "true" : "false") << endl;


		if (object->isCreatureObject()) {
			auto creoObject = object->asCreatureObject();

			if (creoObject != nullptr) {
				/*
				*	CreatureObject Information
				*/

				msg << endl << "Creature Object Information:" << endl << endl <<
				"Displayed Name: " << creoObject->getDisplayedName() << endl <<
				"PvP Status Bitmask: " << creoObject->getPvpStatusBitmask() << endl <<
				"Options Bitmask: " << creoObject->getOptionsBitmask() << endl;

 				if (creoObject->isPlayerCreature()) {
					auto playerManager = server->getPlayerManager();

					if (playerManager != nullptr) {
						int playerLevel = playerManager->calculatePlayerLevel(creoObject);

						msg << "Player Level: " << playerLevel << endl;
					}
				}

				if (creoObject->isGrouped()) {
					GroupObject* group = creoObject->getGroup();

					if (group != nullptr) {
						msg << "Group Level: " << group->getGroupLevel() << endl;
					}
				}

				msg << endl;

				/*
				*	AiAgentObject Information
				*/
				if (creoObject->isAiAgent()) {
					auto objectAgent = creoObject->asAiAgent();

					if (objectAgent != nullptr) {
						msg << endl << "AiAgent Object Information:" << endl << endl;

						String aiEnabled = ((objectAgent->getOptionsBitmask() & OptionBitmask::AIENABLED) ? "True" : "False");
						msg << "AI Enabled: " << aiEnabled << endl;

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

						msg << endl; // Spacing

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

						msg << endl; // Spacing

						// Home Object - Lairs
						uint64 homeID = 0;
						String homeName = "none";
						ManagedReference<SceneObject*> homeLair = objectAgent->getHomeObject().get();

						if (homeLair != nullptr) {
							homeID = homeLair->getObjectID();
							homeName = homeLair->getObjectNameStringIdName();
						}

						msg << "Home Object: " << homeName << " ID: " << homeID << endl;

						msg << endl; // Spacing
					}
				}

				// List the active areas
				SortedVector<ManagedReference<ActiveArea*>>* areas = creoObject->getActiveAreas();

				if (areas != nullptr) {
					msg << endl << endl << "Current Active Areas:" << endl << endl;

					for (int i = 0; i < areas->size(); i++) {
						ActiveArea* area = areas->get(i);

						if (area == nullptr)
							continue;

						msg << "Area #" << i << " -- " << area->getAreaName() << endl;
					}
				}
			}
		/*
			ShipObject Information
		*/
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

		// Send information in a system message
		creature->sendSystemMessage(msg.toString());

		StringBuffer titleStr;
		titleStr << "GetObjVars: " << objectID;

		ChatManager* chatManager = zoneServer->getChatManager();

		if (chatManager != nullptr) {
			// Send information as in game mail
			chatManager->sendMail("System", titleStr.toString(), msg.toString(), creature->getFirstName());
		}

		box->setPromptTitle(titleStr.toString());
		box->setPromptText(msg.toString());

		ghost->addSuiBox(box);

		// Send information via sui box
		creature->sendMessage(box->generateMessage());

		return SUCCESS;
	}
};

#endif // GETOBJVARSCOMMAND_H_

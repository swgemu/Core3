/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETOBJVARSCOMMAND_H_
#define GETOBJVARSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"

class GetObjVarsCommand : public QueueCommand {
public:

	GetObjVarsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		uint64 objectID = 0;
		UnicodeTokenizer tokenizer(arguments);
		tokenizer.setDelimeter(" ");

		// if we have an argument passed, use it
		if (tokenizer.hasMoreTokens()) {
			try {
				objectID = tokenizer.getLongToken();
			} catch ( Exception& err ) {
				creature->sendSystemMessage("INVALID OBJECT.  Please specify a valid object name or objectid");
				return INVALIDPARAMETERS;
			}
		} else {
			objectID = target;
		}

		if ( objectID == 0 ) {
			creature->sendSystemMessage("You need to target an object or specify an object id: /getobjvars <objectID> ");
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(objectID, false);

		if ( object == nullptr) {
			creature->sendSystemMessage("ERROR GETTIGN OBJECT - nullptr " + String::valueOf(objectID));
		} else {

			String strClassName = object->getObjectNameStringIdName();
			String strDescription = object->getDetailedDescription();
			bool bMarkedForDelete = object->_isMarkedForDeletion();
			bool bIsUpdated = object->_isUpdated();
			int rCount = object.get()->getReferenceCount();
			uint64 parentID = object->getParentID();
			StringBuffer msg;
			msg << endl << "OBJECTID: " << String::valueOf(objectID) << endl;
			msg << "OBJECTTYPE: " << String::valueOf(object->getGameObjectType()) << endl;

			if(object->isCreatureObject()) {
				msg << "Creature First Name: " << object.castTo<CreatureObject*>()->getFirstName() << endl;
			}

			msg << "CLASS: " << strClassName << endl;
			msg << "Marked for deletion: " << String::valueOf(bMarkedForDelete) << endl;
			msg << "IsUpdated: " <<  String::valueOf(bIsUpdated) << endl;
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
							msg << "Creature Movement Sate: " << objectAgent->getMovementState() << endl;

							ManagedReference<SceneObject*> followCopy = objectAgent->getFollowObject();
							StringBuffer hasFollow;

							if (followCopy != nullptr) {
								hasFollow << "True - " << " OID: " << followCopy->getObjectID();
							} else {
								hasFollow << "False";
							}

							msg << "Has Follow Object: " << hasFollow.toString() << endl;
							msg << "Current total Patrol Points: " << objectAgent->getPatrolPointSize() << endl;
							msg << "Is in navmesh: " << (objectAgent->isInNavMesh() ? "True" : "False") << endl;
						}
					}

					SortedVector<ManagedReference<ActiveArea*> >* areas = creoObject->getActiveAreas();

					if (areas != nullptr) {
						for (int i = 0; i < areas->size(); i++) {
							ActiveArea* area = areas->get(i);

							if (area == nullptr)
								continue;

							msg << "Area #" << i << " -- " << area->getAreaName() << endl;
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
			chatManager->sendMail("System", title , msg.toString(), creature->getFirstName());
		}


		return SUCCESS;
	}

};

#endif //GETOBJVARSCOMMAND_H_

/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETATTRIBUTESBATCHCOMMAND_H_
#define GETATTRIBUTESBATCHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/Zone.h"

class GetAttributesBatchCommand : public QueueCommand {
public:

	GetAttributesBatchCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if(ghost == NULL)
			return GENERALERROR;

		StringTokenizer ids(arguments.toString());

		Zone* zone = creature->getZone();

		if (zone == NULL)
			return GENERALERROR;

		int incr = 0;

		while (ids.hasMoreTokens()) {
			uint64 objid = 0;

			try {
				objid = ids.getLongToken();

			} catch (Exception& e) {
				error(e.getMessage());
			}

			if (objid == 0)
				continue;

			ManagedReference<SceneObject*> object = zone->getZoneServer()->getObject(objid);

			if (object != NULL) {
				ManagedReference<SceneObject*> parent = object->getParent().get();

				if (parent != NULL && parent->isCreatureObject() &&
					!ghost->isPrivileged() && !object->isASubChildOf(creature)) {

					sendEmptyAttributes(creature, objid);
				} else {
					int count = (incr == 0 && !ids.hasMoreTokens()) ? 0 : incr;

					sendAttributes(creature, object, count);
				}

			} else {
				sendEmptyAttributes(creature, objid);
			}

			if ((incr++) > 200) {
				creature->info("Objects attribute limit exceeded!");

				return GENERALERROR;
			}
		}

		return SUCCESS;
	}

	void sendEmptyAttributes(CreatureObject* creature, uint64 objid) const {
		AttributeListMessage* msg = new AttributeListMessage(objid);
		creature->sendMessage(msg);
	}

	void sendAttributes(CreatureObject* creature, SceneObject* object, int incr) const {
		object->sendAttributeListTo(creature);

		creature->notifyObservers(ObserverEventType::GETATTRIBUTESBATCHCOMMAND, object, incr);
	}

};

#endif //GETATTRIBUTESBATCHCOMMAND_H_

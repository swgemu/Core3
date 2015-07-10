/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EXTRACTOBJECTCOMMAND_H_
#define EXTRACTOBJECTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class ExtractObjectCommand : public QueueCommand {
public:

	ExtractObjectCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		try {

			ManagedReference<SceneObject* > object = server->getZoneServer()->getObject(target);

			if(object == NULL || !object->isFactoryCrate()) {
				creature->sendSystemMessage("Trying to 'ExtractObjectCommand' on item that isn't a factory crate");
				return GENERALERROR;
			}

			if (!object->isASubChildOf(creature))
				return GENERALERROR;

			ManagedReference<FactoryCrate*> crate = cast<FactoryCrate*>( object.get());

			if (!crate->extractObjectToInventory(creature)) {
				//error("Error extracting object in ExtractObjectCommand");
			}

		} catch (Exception& e) {
			error("Unhandled Exception in ExtractObjectCommand");
			creature->sendSystemMessage("Unhandled Exception in ExtractObjectCommand");
		}


		return SUCCESS;
	}

};

#endif //EXTRACTOBJECTCOMMAND_H_

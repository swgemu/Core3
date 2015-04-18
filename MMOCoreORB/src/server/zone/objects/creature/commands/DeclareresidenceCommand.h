/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DECLARERESIDENCECOMMAND_H_
#define DECLARERESIDENCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/structure/StructureManager.h"

class DeclareresidenceCommand : public QueueCommand {
public:

	DeclareresidenceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> obj = creature->getParentRecursively(SceneObjectType::BUILDING);
		ManagedReference<SceneObject*> tobj = creature->getParentRecursively(SceneObjectType::THEATERBUILDING);
		if ( obj == NULL || !obj->isStructureObject() ){
			// wasnt a building is it a threatre as theatre has differnet object flag
			if (tobj == NULL || !tobj->isStructureObject()) {
				return INVALIDPARAMETERS;
			}
		}
		if (obj != NULL) {
			StructureObject* structure = cast<StructureObject*>(obj.get());
			StructureManager::instance()->declareResidence(creature, structure);
		} else {
			StructureObject* structure = cast<StructureObject*>(tobj.get());
			StructureManager::instance()->declareResidence(creature, structure);
		}

		return SUCCESS;
	}

};

#endif //DECLARERESIDENCECOMMAND_H_

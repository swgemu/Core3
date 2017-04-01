/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DECLARERESIDENCECOMMAND_H_
#define DECLARERESIDENCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/building/BuildingObject.h"

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

		ManagedReference<SceneObject*> object = creature->getRootParent();
		if (object == NULL || !object->isBuildingObject()) {
			creature->sendSystemMessage("@player_structure:must_be_in_building"); //You must be in a building to do that.
			return INVALIDTARGET;
		}

		BuildingObject* building = cast<BuildingObject*>( object.get());

		Locker clocker(building, creature);
		if (building->isGCWBase()) {
			creature->sendSystemMessage("@player_structure:no_hq_residence"); // You may not declare residence at a factional headquarters.
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> obj = creature->getParentRecursively(SceneObjectType::BUILDING);
		ManagedReference<SceneObject*> tobj = creature->getParentRecursively(SceneObjectType::THEATERBUILDING);
		if ( obj == NULL || !obj->isStructureObject() ){
			// wasn't a building. Is it a theater, as theater has different object flag
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

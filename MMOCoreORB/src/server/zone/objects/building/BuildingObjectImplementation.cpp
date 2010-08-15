/*
 * BuildingObjectImplementation.cpp
 *
 *  Created on: 23/07/2009
 *      Author: TheAnswer
 */

#include "BuildingObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/player/PlayerCreature.h"

#include "../../templates/tangible/SharedBuildingObjectTemplate.h"
#include "../tangible/terminal/structure/StructureTerminal.h"

#include "../player/sui/listbox/SuiListBox.h"
#include "../player/sui/inputbox/SuiInputBox.h"

#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"

void BuildingObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("BuildingObject");
}

void BuildingObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SharedBuildingObjectTemplate* buildingData = dynamic_cast<SharedBuildingObjectTemplate*>(templateData);

	totalCellNumber = buildingData->getTotalCellNumber();

	containerVolumeLimit = 0xFFFFFFFF;

	containerType = 2;

	lotSize = buildingData->getLotSize();

	optionsBitmask = 0x00000100;
}

void BuildingObjectImplementation::sendContainerObjectsTo(SceneObject* player) {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		cell->setCellNumber(i + 1);
		cell->sendTo(player, true);
	}
}

void BuildingObjectImplementation::sendTo(SceneObject* player, bool doClose) {
	info("building sendto..");

	if (!isStaticBuilding()) { // send Baselines etc..
		info("sending building object create");

		SceneObjectImplementation::sendTo(player, doClose);
	} else { // just send the objects that are in the building, without the cells because they are static in the client
		for (int i = 0; i < cells.size(); ++i) {
			CellObject* cell = cells.get(i);

			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				SceneObject* childStub = cell->getContainerObject(j);

				if (!childStub->isInQuadTree())
					childStub->sendTo(player, true);
			}
		}
	}
}

void BuildingObjectImplementation::removeFromZone() {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		while (cell->getContainerObjectsSize() > 0) {
			ManagedReference<SceneObject*> obj = cell->getContainerObject(0);

			obj->removeFromZone();

			cell->removeObject(obj);
		}
	}

	TangibleObjectImplementation::removeFromZone();
}

void BuildingObjectImplementation::sendDestroyTo(SceneObject* player) {
	if (!isStaticBuilding()) {
		info("sending building object destroy");

		SceneObjectImplementation::destroy(player->getClient());
	}
}

void BuildingObjectImplementation::createChildObjects() {
}

void BuildingObjectImplementation::sendBaselinesTo(SceneObject* player) {
	//send buios here
	info("sending building baselines");

	BaseMessage* buio3 = new TangibleObjectMessage3(_this);
	player->sendMessage(buio3);

	BaseMessage* buio6 = new TangibleObjectMessage6(_this);
	player->sendMessage(buio6);
}

void BuildingObjectImplementation::notifyInsertToZone(SceneObject* object) {
	//info("BuildingObjectImplementation::notifyInsertToZone");
	SceneObjectImplementation* creoImpl = (SceneObjectImplementation*) object->_getImplementation();

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		QuadTreeEntry* obj = getInRangeObject(i);
		SceneObjectImplementation* objImpl = (SceneObjectImplementation*) obj;

		creoImpl->addInRangeObject(obj, true);
		obj->addInRangeObject(creoImpl, true);
	}

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* childStub = cell->getContainerObject(j);
			SceneObjectImplementation* child = (SceneObjectImplementation*) childStub->_getImplementation();

			//if (childStub->isInRange(object, 128)) {
				child->addInRangeObject(creoImpl, false);

				if (childStub != object) {
					creoImpl->notifyInsert(child);
					//child->sendTo(object, true);
				}

				creoImpl->addInRangeObject(child, false);

				if (childStub != object) {
					//object->sendTo(childStub, true);
					child->notifyInsert(creoImpl);
				}

			//}
		}
	}

	creoImpl->addInRangeObject(this, false);
	addInRangeObject(creoImpl, false);
	//this->sendTo(object, true);
}

void BuildingObjectImplementation::notifyInsert(QuadTreeEntry* obj) {
	//info("BuildingObjectImplementation::notifyInsert");
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* childStub = cell->getContainerObject(j);

			/*if (childStub->isCreatureObject()
					|| (scno->getRootParent() == _this) && (scno->isInRange(childStub, 128))) {*/

				SceneObjectImplementation* child = (SceneObjectImplementation*) childStub->_getImplementation();

				child->addInRangeObject(obj, false);
				obj->addInRangeObject(child, false);
			//}
		}
	}
}

void BuildingObjectImplementation::notifyDissapear(QuadTreeEntry* obj) {
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	SceneObject* scnoStub = (SceneObject*) scno->_getStub();

	removeNotifiedSentObject(scnoStub);

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			SceneObject* childStub = cell->getContainerObject(j);
			SceneObjectImplementation* child = (SceneObjectImplementation*) childStub->_getImplementation();

			child->removeInRangeObject(obj);
			obj->removeInRangeObject(child);
		}
	}
}

void BuildingObjectImplementation::insert(QuadTreeEntry* entry) {
	QuadTree::insert(entry);
}

void BuildingObjectImplementation::remove(QuadTreeEntry* entry) {
	QuadTree::remove(entry);
}

void BuildingObjectImplementation::update(QuadTreeEntry* entry) {
	QuadTree::update(entry);
}

void BuildingObjectImplementation::inRange(QuadTreeEntry* entry, float range) {
	QuadTree::inRange(entry, range);
}

void BuildingObjectImplementation::addCell(CellObject* cell) {
	cells.add(cell);

	cell->setCellNumber(cells.size());

	if (!addObject(cell, -1))
		error("could not add cell");
}

void BuildingObjectImplementation::handleSetObjectName(PlayerCreature* player) {
	ManagedReference<SuiInputBox*> setTheName = new SuiInputBox(player, SuiWindowType::OBJECT_NAME, 0x00);

	setTheName->setPromptTitle("@sui:set_name_title");
	setTheName->setPromptText("@sui:set_name_prompt");
	setTheName->setUsingObject(_this);

	player->addSuiBox(setTheName);
	player->sendMessage(setTheName->generateMessage());
}

void BuildingObjectImplementation::handlePrivacyChange(PlayerCreature* player) {
	//Toggle privacy.
	publicStructure = !publicStructure;

	if (publicStructure)
		player->sendSystemMessage("@player_structure:structure_now_public"); //This structure is now public
	else
		player->sendSystemMessage("@player_structure:structure_now_private"); //This structure is now private
}

void BuildingObjectImplementation::handleDeclareResidency(PlayerCreature* player) {
	//Register the building with the city if possible...

	if (player->getObjectID() != ownerObjectID) {
		player->sendSystemMessage("@player_structure:declare_must_be_owner"); //You must be the owner of the building to declare residence.
		return;
	}

	if (declaredResidency) {
		player->sendSystemMessage("@player_structure:already_residence"); //This building is already your residence.
		return;
	}

	declaredResidency = true;

	player->sendSystemMessage("@player_structure:change_residence"); //You change your residence to this building.

	//TODO: Input time limit on changing residence.
}

void BuildingObjectImplementation::handleStructureStatus(PlayerCreature* player) {
	//Close any existing structure status window.
	//Create a status sui and send it to the player.
	ManagedReference<SuiListBox*> statusBox = new SuiListBox(player, SuiWindowType::STRUCTURE_STATUS);
	statusBox->setPromptTitle("@player_structure:structure_status_t"); //Structure Status

	String full;
	if (getCustomObjectName().isEmpty())
		objectName.getFullPath(full);
	else
		full = getCustomObjectName().toString();

	statusBox->setPromptText("@player_structure:structure_name_prompt " + full); //Structure Name:

	ManagedReference<PlayerCreature*> playerCreature = (PlayerCreature*) getZoneServer()->getObject(ownerObjectID);
	statusBox->addMenuItem("@player_structure:owner_prompt  " + playerCreature->getFirstName());

	if (declaredResidency)
		statusBox->addMenuItem("@player_structure:declared_residency"); //You have declared your residency here.

	if (publicStructure)
		statusBox->addMenuItem("@player_structure:structure_public"); //This structure is public
	else
		statusBox->addMenuItem("@player_structure:structure_private"); //This structure is private

	StringBuffer sscond, ssmpool, ssmrate, ssppool, ssnitems;

	sscond << dec << "@player_structure:condition_prompt " << ((int) (((maxCondition - conditionDamage) / maxCondition) * 100)) << "%";
	statusBox->addMenuItem(sscond.toString());

	ssmpool << dec << "@player_structure:maintenance_pool_prompt " << (int) surplusMaintenance; //Maintenance Pool:
	statusBox->addMenuItem(ssmpool.toString());

	ssmrate << dec << "@player_structure:maintenance_rate_prompt " << (int) baseMaintenanceRate << " @player_structure:units_per_hour";
	statusBox->addMenuItem(ssmrate.toString());

	//TODO: Count items that can be picked up by the player (exclude terminals like structure, elevator, guild)...
	ssnitems << dec << "@player_structure:items_in_building_prompt " << (int) 0; //Number of Items in Building:

	player->addSuiBox(statusBox);
	player->sendMessage(statusBox->generateMessage());
}

void BuildingObjectImplementation::handleStructureDestroyRequest(PlayerCreature* player) {
	//This should send the confirm box. If confirmed, then destroy in sui/structure manager?

	if (ownerObjectID != player->getObjectID()) {
		player->sendSystemMessage("@player_structure:destroy_must_be_owner"); //You must be the owner to destroy a structure.
		return;
	}

	//ManagedReference<SuiBox*> destroyBox = new SuiBox(player, SuiWindowType::)

	//removeFromZone();

	//int lotsRemaining = player->getLotsRemaining();

	//player->setLotsRemaining(lotsRemaining + lotSize);

	//destroyObjectFromDatabase(true);
}

void BuildingObjectImplementation::handleStructureDestroyConfirm(PlayerCreature* player, bool confirm) {

}

void BuildingObjectImplementation::handlePayMaintenance(PlayerCreature* player) {
}

/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "DraftSchematic.h"

#include "server/zone/ZoneServer.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"

#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectMessage3.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectMessage6.h"
#include "server/zone/objects/intangible/IntangibleObject.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectMessage8.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectMessage9.h"
/*#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage3.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage6.h"
#include "server/zone/packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage7.h"*/

void DraftSchematicImplementation::initializeTransientMembers() {
	IntangibleObjectImplementation::initializeTransientMembers();

	setGlobalLogging(true);
	setLogging(false);

	setLoggingName("DraftSchematic");
}

void DraftSchematicImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	IntangibleObjectImplementation::loadTemplateData(templateData);

	schematicTemplate = dynamic_cast<DraftSchematicObjectTemplate*>(templateData);
}

void DraftSchematicImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {


}

void DraftSchematicImplementation::sendBaselinesTo(SceneObject* player) {
	if (!player->isPlayerCreature())
		return;

	error("Trying to send DraftSchematic baselines, should not be sending");
}

void DraftSchematicImplementation::sendDraftSlotsTo(CreatureObject* player) {

	CreatureObject* playerCreature = cast<CreatureObject*>( player);

	ObjectControllerMessage* msg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BF);

	msg->insertInt(schematicID);
	msg->insertInt(clientObjectCRC);

	msg->insertInt(schematicTemplate->getComplexity()); // ex: 3
	msg->insertInt(schematicTemplate->getSize()); // ex: 1
	msg->insertByte(2);

	insertIngredients(msg);

	player->sendMessage(msg);

}

void DraftSchematicImplementation::insertIngredients(ObjectControllerMessage* msg) {

	Vector<Reference<DraftSlot* > >* draftSlots = schematicTemplate->getDraftSlots();

	msg->insertInt(draftSlots->size());

	for(int i = 0; i < draftSlots->size(); ++i) {
		draftSlots->get(i)->insertToMessage(msg);
	}

	msg->insertShort(0);
}

void DraftSchematicImplementation::sendResourceWeightsTo(CreatureObject* player) {

	Vector<Reference<ResourceWeight* > >* resourceWeights = schematicTemplate->getResourceWeights();

	ObjectControllerMessage* msg = new ObjectControllerMessage(player->getObjectID(), 0x1B, 0x0207);

	msg->insertInt(schematicID);
	msg->insertInt(clientObjectCRC);

	msg->insertByte(resourceWeights->size());

	//Send all the resource batch property data
	for (int i = 0; i < resourceWeights->size(); i++)
		resourceWeights->get(i)->insertBatchToMessage(msg);

	msg->insertByte(resourceWeights->size());

	//Send all the resource property data
	for (int i = 0; i < resourceWeights->size(); i++)
		resourceWeights->get(i)->insertToMessage(msg);

	player->sendMessage(msg);
}

SceneObject* DraftSchematicImplementation::createManufactureSchematic(SceneObject* craftingTool) {

	ManufactureSchematic* manuSchematic =
			dynamic_cast<ManufactureSchematic* > (getZoneServer()->createObject(0xF75E04C2, 0));

	if(manuSchematic == NULL) {
		error("Could not create ManufactureSchematic for " + getObjectNameStringIdName());
		return NULL;
	}

	if(craftingTool != NULL)
		manuSchematic->setDraftSchematic(craftingTool, _this);

	return manuSchematic;
}

int DraftSchematicImplementation::getDraftSlotCount() {
	return schematicTemplate->getDraftSlots()->size();
}

DraftSlot* DraftSchematicImplementation::getDraftSlot(int i) {
	return schematicTemplate->getDraftSlots()->get(i);
}

int DraftSchematicImplementation::getResourceWeightCount() {
	return schematicTemplate->getResourceWeights()->size();
}

ResourceWeight* DraftSchematicImplementation::getResourceWeight(int i) {
	return schematicTemplate->getResourceWeights()->get(i);
}


float DraftSchematicImplementation::getComplexity() {
	return (float)schematicTemplate->getComplexity();
}

uint32 DraftSchematicImplementation::getToolTab() {
	return (uint32)schematicTemplate->getCraftingToolTab();
}

float DraftSchematicImplementation::getSize() {
	return (float)schematicTemplate->getSize();
}

String DraftSchematicImplementation::getXpType() {
	return schematicTemplate->getXpType();
}

int DraftSchematicImplementation::getXpAmount() {
	return schematicTemplate->getXp();
}

String DraftSchematicImplementation::getAssemblySkill() {
	return schematicTemplate->getAssemblySkill();
}

String DraftSchematicImplementation::getExperimentationSkill() {
	return schematicTemplate->getExperimentingSkill();
}

String DraftSchematicImplementation::getCustomizationSkill() {
	return schematicTemplate->getCustomizationSkill();
}

Vector<String>* DraftSchematicImplementation::getCustomizationStringNames() {
	return schematicTemplate->getCustomizationStringNames();
}

Vector<byte>* DraftSchematicImplementation::getCustomizationOptions() {
	return schematicTemplate->getCustomizationOptions();
}

Vector<byte>* DraftSchematicImplementation::getCustomizationDefaultValues() {
	return schematicTemplate->getCustomizationDefaultValues();
}

String DraftSchematicImplementation::getCustomName() {
	return schematicTemplate->getCustomObjectName();
}

uint32 DraftSchematicImplementation::getTanoCRC() {
	return schematicTemplate->getTanoCRC();
}

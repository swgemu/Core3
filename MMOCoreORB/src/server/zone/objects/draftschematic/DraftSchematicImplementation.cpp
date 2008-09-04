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

#include "DraftSchematicImplementation.h"

#include "../../packets.h"

DraftSchematicImplementation::DraftSchematicImplementation(uint32 schematicID, const string& objName,
		uint32 objCRC, const string& groupName, uint32 complexity,
		uint32 schematicSize, int craftingToolTab) :
			DraftSchematicServant() {
	DraftSchematicImplementation::schematicID = schematicID;
	DraftSchematicImplementation::objName = objName;
	DraftSchematicImplementation::schematicCRC = objCRC;
	DraftSchematicImplementation::groupName = groupName;
	DraftSchematicImplementation::complexity = complexity;
	DraftSchematicImplementation::schematicSize = schematicSize;
	DraftSchematicImplementation::craftingToolTab = craftingToolTab;

	craftingValues = new DraftSchematicValues();

	persistent = false;
	expPointsUsed = 0;

	finished = false;
}

DraftSchematicImplementation::DraftSchematicImplementation(DraftSchematic* draftSchematic) :
	DraftSchematicServant() {

	//draftSchematic->toString();

	schematicID = draftSchematic->getSchematicID();
	objName = draftSchematic->getName();
	schematicCRC = draftSchematic->getSchematicCRC();
	groupName = draftSchematic->getGroupName();
	complexity = draftSchematic->getComplexity();
	schematicSize = draftSchematic->getSchematicSize();
	craftingToolTab = draftSchematic->getCraftingToolTab();

	craftingValues = new DraftSchematicValues();

	persistent = false;

	finished = false;

	for (int i = 0; i < draftSchematic->getIngredientListSize(); ++i) {
		dsIngredients.add(draftSchematic->getIngredient(i));
	}

	for (int i = 0; i < draftSchematic->getExpPropGroupListSize(); ++i) {
		dsExpPropGroups.add(draftSchematic->getExpPropGroup(i));
	}

	string title;
	string subtitle;

	for (int i = 0; i < draftSchematic->getCraftingValues()->getExperimentalPropertyTitleSize(); ++i) {
		title = draftSchematic->getCraftingValues()->getExperimentalPropertyTitle(i);

		for (int j = 0; j < draftSchematic->getCraftingValues()->getExperimentalPropertySubtitleSize(title); ++j) {
			subtitle = draftSchematic->getCraftingValues()->getExperimentalPropertySubtitle(title, j);

			craftingValues->addExperimentalPropertySubtitle(title, subtitle);
		}
	}

	for (int i = 0; i < draftSchematic->getAttributesToSetListSize(); ++i) {
		attributesToSet.add(draftSchematic->getAttributeToSet(i));
	}

	tanoAttributes = draftSchematic->getTanoAttributes();
	xpType = draftSchematic->getXpType();
	xp = draftSchematic->getXp();

	experimentingSkill = draftSchematic->getExperimentingSkill();
	assemblySkill = draftSchematic->getAssemblySkill();

	//toString();
}

DraftSchematicImplementation::~DraftSchematicImplementation(){
	while (dsExpPropGroups.size() > 0)
		dsExpPropGroups.remove(0)->finalize();

	while (attributesToSet.size() > 0)
		attributesToSet.remove(0)->finalize();

	while (dsIngredients.size() > 0)
		dsIngredients.remove(0)->finalize();

	experimentalProperties.removeAll();

	craftingValues->finalize();
	craftingValues = NULL;
}

DraftSchematic* DraftSchematicImplementation::dsClone(DraftSchematic* draftSchematic) {
	if (draftSchematic != NULL) {
		return new DraftSchematic(draftSchematic);
	} else {
		return NULL;
	}
}

void DraftSchematicImplementation::close(Player* player) {
	if (player == NULL)
		return;

	BaseMessage* msg = new SceneObjectCloseMessage(_this->getObjectID());
	player->sendMessage(msg);
}

void DraftSchematicImplementation::destroy(Player* player) {
	if (player == NULL)
		return;

	BaseMessage* msg = new SceneObjectDestroyMessage(_this->getObjectID());
	player->sendMessage(msg);
}

void DraftSchematicImplementation::sendTo(Player* player) {
	// This sends the initial DraftSchematic data to begin the crafting Session
	if (player == NULL)
		return;

	// Scene Create
	BaseMessage* create = new SceneObjectCreateMessage(_this->getObjectID(), 0x3819C409);
	player->sendMessage(create);

	// Link to Crafting Tool
	BaseMessage* link = new UpdateContainmentMessage(_this->getObjectID(), _this->getContainer()->getObjectID(), 4);
	player->sendMessage(link);

	// MSCO3
	unicode& uniPlayerName = player->getCharacterName();

	ManufactureSchematicObjectMessage3* msco3 =
		new ManufactureSchematicObjectMessage3(_this->getObjectID(), _this->getComplexity(), uniPlayerName);
	player->sendMessage(msco3);

	// MSCO6
	ManufactureSchematicObjectMessage6* msco6 =
		new ManufactureSchematicObjectMessage6(_this->getObjectID(), _this->getSchematicCRC());
	player->sendMessage(msco6);

	// MSCO8
	ManufactureSchematicObjectMessage8* msco8 =
		new ManufactureSchematicObjectMessage8(_this->getObjectID());
	player->sendMessage(msco8);

	// MSCO9
	ManufactureSchematicObjectMessage9* msco9 =
		new ManufactureSchematicObjectMessage9(_this->getObjectID());
	player->sendMessage(msco9);

	// Scene Close
	BaseMessage* close = new SceneObjectCloseMessage(_this->getObjectID());
	player->sendMessage(close);

}

// Ingredient Methods
void DraftSchematicImplementation::addIngredient(const string& ingredientTemplateName, const string& ingredientTitleName,
		bool optional, const string& resourceType, uint32 resourceQuantity) {
	DraftSchematicIngredient* ingreedient = new DraftSchematicIngredient(ingredientTemplateName,
			ingredientTitleName, optional, resourceType, resourceQuantity);

	dsIngredients.add(ingreedient);
}

// THERE IS A BUG WHEN YOU LEAVE YOUR DATAPAD UP AND SURRENDER A SKILL, THE DRAFT SCHEMATICS
// STILL ARE IN YOUR DATAPAD, SO IF YOU CLICK THEM, IT WILL SAY SCHEMATIC NOT FOUND AND WILL
// SCREW UP THE CLIENT TRYING TO GET THE INGREDIENTS AND EXP PROPS FROM THERE ON UNTIL THE CLIENT
// FULLY EXITS THE GAME
void DraftSchematicImplementation::sendIngredientsToPlayer(Player* player) {
	ObjectControllerMessage* msg = new ObjectControllerMessage(player->getObjectID(), 0x0B, 0x01BF);

	msg->insertInt(schematicID); // ex: 0x838FF623838FF623 (objID is always the crc value in the upper 4 bytes and the lower 4 bytes)
	msg->insertInt(schematicCRC);
	msg->insertInt(complexity); // ex: 3
	msg->insertInt(schematicSize); // ex: 1
	msg->insertByte(1);

	helperSendIngredientsToPlayer(msg);

	player->sendMessage(msg);
}

void DraftSchematicImplementation::helperSendIngredientsToPlayer(ObjectControllerMessage* objMsg) {
	int listSize = dsIngredients.size();
	objMsg->insertInt(listSize);

	// Send all the ingredient data
	for (int i = 0; i < listSize; i++) {
		DraftSchematicIngredient* dsi = dsIngredients.get(i);
		dsi->helperSendToPlayer(objMsg);
	}

	/* for debugging
		 stringstream ss;
		 ss << msg->toString();
		 player->info(ss.str());*/

	objMsg->insertShort(0);
}

// Experimental Property Methods
// UPDATE THIS METHOD WHEN WE CAN PASS VECTORS AROUND IN IDL
void DraftSchematicImplementation::addExperimentalProperty(uint32 groupNumber,
		const string& experimentalProperty, uint32 weight) {
	if (groupNumber < dsExpPropGroups.size()) {
		dsExpPropGroups.get(groupNumber)->addExperimentalProperty(experimentalProperty,	weight);
	} else {
		DraftSchematicExpPropGroup* dsEpg = new DraftSchematicExpPropGroup();
		dsEpg->addExperimentalProperty(experimentalProperty, weight);

		dsExpPropGroups.add(dsEpg);
	}
}

void DraftSchematicImplementation::sendExperimentalPropertiesToPlayer(Player* player) {
	ObjectControllerMessage* msg = new ObjectControllerMessage(player->getObjectID(), 0x1B, 0x0207);

	msg->insertInt(schematicID);
	msg->insertInt(schematicCRC);

	uint8 listSize = dsExpPropGroups.size();

	/*uint32 padding = 0;
		 if (draftSchematicIngredients.size() > 0) {
		 string templateName = draftSchematicIngredients.get(0)->getTemplateName();

		 if( templateName == "craft_chemical_ingredients_n" || templateName == "craft_droid_ingredients_n"
		 || templateName == "craft_munition_ingredients_n" || templateName == "craft_structure_ingredients_n"
		 || templateName == "craft_tissue_ingredients_n" || templateName == "craft_vehicle_ingredients_n"
		 || templateName == "craft_weapon_ingredients_n") {
		 padding = 2;
		 } else {
		 padding = 3;
		 }
		 }*/

	// Have to run the loop twice.  Ask soe why :/

	for (int soeFtl = 0; soeFtl < 2; soeFtl++) {
		// The +3 is for the padding
		//msg->insertByte(listSize + padding);

		msg->insertByte(listSize);

		/* This loop adds the padding required for this packet to work
			 for (int soeIsDumb = 0; soeIsDumb < padding; soeIsDumb++) {
			 msg->insertByte(1);
			 msg->insertByte(0);
			 }*/

		int count = getRequiredIngredientCount();

		// Send all the experimental property data
		for (int i = 0; i < listSize; i++) {
			DraftSchematicExpPropGroup* dsEpg = dsExpPropGroups.get(i);
			// OLD dsEpg->sendToPlayer(msg);
			dsEpg->sendToPlayer(msg, count);
			count++;
		}
	}

	player->sendMessage(msg);
}

int DraftSchematicImplementation::getRequiredIngredientCount() {
	DraftSchematicIngredient* dsi;
	int count = 0;

	for (int i = 0; i < dsIngredients.size(); i++) {
		dsi = dsIngredients.get(i);

		if (!dsi->getOptional())
			count++;
	}

	return count;
}

void DraftSchematicImplementation::toString() {
	cout << "Name: " << objName;
	cout << "\nSchematicID: " << schematicID;
	cout << "\nobjectID: " << objectID;
	cout << "\nschematicCRC: " << schematicCRC;
	cout << "\ngroupName: " << groupName;
	cout << "\ncomplexity: " << complexity;
	cout << "\nschematicSize: " << schematicSize;
	cout << "\ncraftingToolTab: " << craftingToolTab;

	cout << "\nxpType: " << xpType;
	cout << "\nxp: " << xp;
	cout << "\ntanoAttributes: " << tanoAttributes;

	cout << "\nAssembly Skill: " << assemblySkill;
	cout << "\nExperimenting Skill: " << experimentingSkill;

	DraftSchematicIngredient* ingredient;
	for (int i = 0;i < dsIngredients.size(); ++i) {
		ingredient = dsIngredients.get(i);

		cout << "\n*************************" << endl;
		cout << "Ingredient " << i << endl;
		cout << "Title: " << ingredient->getTitleName() << endl;
		cout << "Resource Type: " << ingredient->getResourceType() << endl;
		cout << "Template Name: " << ingredient->getTemplateName() << endl;
		cout << "Quantity: " << ingredient->getResourceQuantity() << endl;
		cout << "Optional: " << ingredient->getOptional() << endl;
		cout << "**************************" << endl;
	}

	DraftSchematicExpPropGroup* tempGroup;
	for (int i = 0;i < dsExpPropGroups.size(); ++i) {
		tempGroup = dsExpPropGroups.get(i);

		cout << "\n*************************" << endl;
		cout << "Exp Property " << i << endl;
		cout << "Type and Weight: " << tempGroup->getTypeAndWeight(i) << endl;
		cout << "Percentage: " << tempGroup->getExpPropPercentage(i) << endl;
		cout << "**************************" << endl;
	}

	DraftSchematicAttribute* tempAttribute;
	for (int i = 0;i < attributesToSet.size(); ++i) {
		tempAttribute = attributesToSet.get(i);

		cout << "\n*************************" << endl;
		cout << "Attribute " << i << endl;
		cout << "Name: " << tempAttribute->getAttributeName() << endl;
		cout << "Property: " << tempAttribute->getAttributeExperimentalProperty() << endl;
		cout << "Min: " << tempAttribute->getMinValue() << endl;
		cout << "Max: " << tempAttribute->getMaxValue() << endl;
		cout << "Range: " << tempAttribute->getRange() << endl;
		cout << "**************************" << endl;
	}

	float tempProperty;
	for (int i = 0;i < experimentalProperties.size(); ++i) {
		tempProperty = experimentalProperties.get(i);

		cout << "*************************" << endl;
		cout << "Prop " << i << endl;
		cout << "Prop: " << tempProperty << endl;
		cout << "**************************" << endl;
	}

	craftingValues->toString();
}

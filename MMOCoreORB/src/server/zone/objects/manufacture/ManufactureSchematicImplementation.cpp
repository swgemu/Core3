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

#include "ManufactureSchematic.h"
#include "ManufactureSchematicImplementation.h"

#include "../../packets/manufactureschematic/ManufactureSchematicObjectMessage3.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectMessage6.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectMessage7.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectMessage8.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectMessage9.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage3.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage6.h"
#include "../../packets/manufactureschematic/ManufactureSchematicObjectDeltaMessage7.h"

#include "../../packets/scene/SceneObjectCreateMessage.h"
#include "../../packets/scene/SceneObjectDestroyMessage.h"
#include "../../packets/scene/SceneObjectCloseMessage.h"
#include "../../packets/scene/UpdateContainmentMessage.h"

ManufactureSchematicImplementation::ManufactureSchematicImplementation(uint64 oid, String n, String stfFile, String stfName, uint32 crc) :
	ManufactureSchematicServant(oid, SceneObjectImplementation::MANUFACTURESCHEMATIC) {

	templateTypeName = stfFile;
	templateName = stfName;
	customName = UnicodeString(n);
	objectCRC = crc;

	init();
}

ManufactureSchematicImplementation::ManufactureSchematicImplementation(uint64 oid, DraftSchematic* draftSchematic, CraftingTool* craftingTool) :
	ManufactureSchematicServant(oid, SceneObjectImplementation::MANUFACTURESCHEMATIC) {

	init();

	setComplexity(draftSchematic->getComplexity());
	templateTypeName = draftSchematic->getStringFile();
	templateName = draftSchematic->getStringName();
	customName = draftSchematic->getName();
	objectCRC = draftSchematic->getSchematicCRC();
	setDataSize(draftSchematic->getSchematicSize());
	setManufacturingLimit(draftSchematic->getManufacturingLimit());

	addObject(craftingTool->getWorkingTano());

	craftingTool->clearWorkingTano();

	setIngredients(draftSchematic, craftingTool);
}

ManufactureSchematicImplementation::~ManufactureSchematicImplementation() {

}

void ManufactureSchematicImplementation::init() {

	itemAttributes = new ItemAttributes();

	complexity = 0;
	dataSize = 0;
	manufacturingLimit = 0;
}

void ManufactureSchematicImplementation::setIngredients(DraftSchematic* draftSchematic, CraftingTool* craftingTool) {

	String name;
	int value;
	StringBuffer resourceString, componentString;

	try {

		craftingTool->wlock();

		for(int i = 0; i < craftingTool->getSlotCount(); ++i) {
			ManagedReference<TangibleObject> itemInSlot = craftingTool->getIngredientInSlot(i);
			DraftSchematicIngredient* dsi = draftSchematic->getIngredient(i);

			if (itemInSlot == NULL)
				continue;

			if(itemInSlot->isResource()) {
				ResourceContainer* rcno = (ResourceContainer*) itemInSlot.get();
				name = rcno->getResourceName();
				value = rcno->getContents();

				if(value == 0)
					value = 1;

				ingredientMap.put(name, value);
				resourceString << name << "=" << value << ";";
			} else {

				if(itemInSlot->getCustomName().isEmpty())
					name = "@" + itemInSlot->getTemplateTypeName() + "#" + itemInSlot->getTemplateName() + " ";
				else
					name = itemInSlot->getCustomName().toString();

				name = name.concat(itemInSlot->getCraftedSerial());

				value = itemInSlot->getObjectCount();

				if(value == 0)
					value = 1;

				ingredientMap.put(name, value);
				componentString << name << "=" << value << ";";
			}
		}

		String name = "resources";
		String newValue = resourceString.toString();
		itemAttributes->setStringAttribute(name, newValue);

		name = "components";
		newValue = componentString.toString();
		itemAttributes->setStringAttribute(name, newValue);

		craftingTool->unlock();
	} catch(Exception& ex) {
		ex.printStackTrace();
		craftingTool->unlock();
	}
}

void ManufactureSchematicImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();

	if (client == NULL)
		return;

	// Scene Create
	BaseMessage* create = new SceneObjectCreateMessage(_this->getObjectID(), 0x3819C409);  // generic_schematic.iff CRC
	client->sendMessage(create);

	BaseMessage* link = new UpdateContainmentMessage(_this->getObjectID(), _this->getParent()->getObjectID(), 0xFFFFFFFF);
	player->sendMessage(link);

	// MSCO3
	UnicodeString& uniPlayerName = player->getCharacterName();

	ManufactureSchematicObjectMessage3* msco3 = new ManufactureSchematicObjectMessage3(_this, uniPlayerName);
	client->sendMessage(msco3);

	// MSCO6
	ManufactureSchematicObjectMessage6* msco6 = new ManufactureSchematicObjectMessage6(_this->getObjectID(), objectCRC);
	client->sendMessage(msco6);

	// MSCO8
	ManufactureSchematicObjectMessage8* msco8 = new ManufactureSchematicObjectMessage8(_this->getObjectID());
	client->sendMessage(msco8);

	// MSCO9
	ManufactureSchematicObjectMessage9* msco9 = new ManufactureSchematicObjectMessage9(_this->getObjectID());
	client->sendMessage(msco9);

	if (doClose) {
		// Scene Close
		BaseMessage* close = new SceneObjectCloseMessage(_this->getObjectID());
		client->sendMessage(close);
	}
}

void ManufactureSchematicImplementation::sendDestroyTo(Player* player) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	destroy(client);
}

void ManufactureSchematicImplementation::parseItemAttributes() {

	String name = "complexity";
	complexity = itemAttributes->getIntAttribute(name);

	name = "datasize";
	dataSize = itemAttributes->getIntAttribute(name);

	name = "manufacturinglimit";
	manufacturingLimit = itemAttributes->getIntAttribute(name);

	name = "resources";
	parseResources(itemAttributes->getStringAttribute(name));

	name = "components";
	parseComponents(itemAttributes->getStringAttribute(name));
}

void ManufactureSchematicImplementation::parseResources(String resources) {

	String temp, key;
	int value;

	StringTokenizer maintokenizer(resources);
	maintokenizer.setDelimeter(";");

	while(maintokenizer.hasMoreTokens()) {
		maintokenizer.getStringToken(temp);

		StringTokenizer propertytokenizer(temp);
		propertytokenizer.setDelimeter("=");

		if (propertytokenizer.hasMoreTokens()) {

			propertytokenizer.getStringToken(key);
			value = propertytokenizer.getIntToken();

			ingredientMap.put(key, value);
		}
	}
}

void ManufactureSchematicImplementation::parseComponents(String components) {
	String temp, key;
	int value;

	StringTokenizer maintokenizer(components);
	maintokenizer.setDelimeter(";");

	while(maintokenizer.hasMoreTokens()) {
		maintokenizer.getStringToken(temp);

		StringTokenizer propertytokenizer(temp);
		propertytokenizer.setDelimeter("=");

		if (propertytokenizer.hasMoreTokens()) {

			propertytokenizer.getStringToken(key);
			value = propertytokenizer.getIntToken();

			ingredientMap.put(key, value);
		}
	}
}

void ManufactureSchematicImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage(_this);
	addAttributes(alm);

	player->sendMessage(alm);
}


void ManufactureSchematicImplementation::addAttributes(AttributeListMessage* alm) {

	String dataSizeString = "data_volume";
	alm->insertAttribute(dataSizeString, dataSize);

	String resourceHead = "cat_manf_schem_ing_resource.\"";

	for(int i = 0; i < ingredientMap.size(); ++i) {

		String theName = resourceHead + ingredientMap.getKey(i);

		theName.replaceAll("#", ":");

		int value = ingredientMap.get(i);

		alm->insertAttribute(theName, value);
	}

	String count = "manf_limit";
	alm->insertAttribute(count, manufacturingLimit);

	SceneObject* scno = (SceneObject*) getObject(0);
	if(scno != NULL)
		scno->addAttributes(alm);
}

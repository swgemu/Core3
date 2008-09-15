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

#include "../../../../packets.h"
#include "../../../../objects.h"
#include "Component.h"
#include "ComponentImplementation.h"
#include "../../../../ZoneClientSession.h"
 
ComponentImplementation::ComponentImplementation(uint64 object_id, uint32 tempCRC, 
		const unicode& n, const string& tempn) : ComponentServant(object_id, tempCRC, n, tempn, 
				COMPONENT) {
	objectCRC = tempCRC;
	templateTypeName = "obj_n";
	templateName = tempn;
	name = n;
	init();
}
 
ComponentImplementation::ComponentImplementation(CreatureObject* creature, uint32 tempCRC, 
		const unicode& n, const string& tempn) : ComponentServant(creature, tempCRC, n, tempn, 
				COMPONENT) {
	objectCRC = tempCRC;
	templateTypeName = "obj_n";
	templateName = tempn;
	name = n;
	init();
}


ComponentImplementation::~ComponentImplementation(){
	attributeMap.removeAll();
	precisionMap.removeAll();
	keyList.removeAll();
}

void ComponentImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	omr->finish();

	player->sendMessage(omr);
}

void ComponentImplementation::init() {
	objectSubType = TangibleObjectImplementation::COMPONENT;
	parseAttributeString();
	parsePrecisionString();
}

int ComponentImplementation::useObject(Player* player) {

	return 0;
}

void ComponentImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (container != NULL)
		link(client, container);

	BaseMessage* fcty3 = new FactoryCrateObjectMessage3((TangibleObject*) _this);
	client->sendMessage(fcty3);

	BaseMessage* fcty6 = new FactoryCrateObjectMessage6((TangibleObject*) _this);
	client->sendMessage(fcty6);

	if (pvpStatusBitmask != 0) {
		UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
		client->sendMessage(msg);
	}

	if (doClose)
		SceneObjectImplementation::close(client);

}

void ComponentImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	string attribute;
	float value;
	double power;
	int precision;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage(_this);
	alm->insertAttribute("volume", "1");

	attribute = "craftersname";
	alm->insertAttribute("crafter", craftersName);

	attribute = "craftedserial";
	alm->insertAttribute("serial_number", craftedSerial);

	for(int i = 0; i < keyList.size(); ++i){

		attribute = keyList.get(i);
		value = attributeMap.get(attribute);
		precision = precisionMap.get(attribute);

		alm->insertAttribute(attribute, getPrecision(value, precision));

	}

	player->sendMessage(alm);
}

void ComponentImplementation::parseItemAttributes(){

	parseAttributeString();
	parsePrecisionString();

	string temp = "craftersname";
	craftersName = itemAttributes->getStringAttribute(temp);

	temp = "craftedserial";
	craftedSerial = itemAttributes->getStringAttribute(temp);

}

Component* ComponentImplementation::cloneComponent(Component* oldComp, uint64 oid) {

	if (oldComp != NULL) {

		uint32 newCRC = _this->getObjectCRC();
		unicode newName = _this->getName();
		string newTemplate = _this->getTemplateName();

		return new Component(oid, newCRC, newName, newTemplate);
	} else {
		return NULL;
	}

}

float ComponentImplementation::getAttributeValue(string& attributeName){

	return attributeMap.get(attributeName);

}

void ComponentImplementation::updateCraftingValues(DraftSchematic* draftSchematic){

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();
	string attribute;
	float value;
	int precision;
	attributeMap.removeAll();
	precisionMap.removeAll();
	keyList.removeAll();

	int start = draftSchematic->getAttributesToSetListSize() - 1;

	for(int i = 0; i < draftSchematic->getAttributesToSetListSize(); ++i){

		value = craftingValues->getAttributeAndValue(draftSchematic, attribute, i);
		precision = craftingValues->getPrecision(draftSchematic, i);

		keyList.add(attribute);

		itemAttributes->setFloatAttribute(attribute, value);

		attributeMap.put(attribute, value);
		precisionMap.put(attribute, precision);

	}

	savePrecisionList();

}

void ComponentImplementation::savePrecisionList(){

	stringstream ss;
	string element;

	for(int i = 0; i < keyList.size(); ++i){

		element = keyList.get(i);

		ss << element << "=" << precisionMap.get(element) << ";";

	}

	string attribute = "precision";
	string value = ss.str();

	itemAttributes->setStringAttribute(attribute, value);

}

void ComponentImplementation::parsePrecisionString() {

	int index1 = 0;
	int index2;
	int index3;
	precisionMap.removeAll();
	keyList.removeAll();

	string attribute = "precision";
	string precisionString = itemAttributes->getStringAttribute(attribute);


	while ((index2 = precisionString.find(";", index1)) != string::npos) {

		string attrPair = precisionString.substr(index1, index2 - index1);

		if ((index3 = attrPair.find("=", 0)) != string::npos) {

			string key = attrPair.substr(0, index3);
			string value = attrPair.substr(index3 + 1, attrPair.length()
					- index3);

			precisionMap.put(key, atoi(value.c_str()));
			keyList.add(key);

		}

		index1 = index2 + 1;
	}
}

void ComponentImplementation::parseAttributeString() {

	int index1 = 0;
	int index2;
	int index3;
	attributeMap.removeAll();
	itemAttributes->getAttributeString(attributeString);

	while ((index2 = attributeString.find(":", index1)) != string::npos) {

		string attrPair = attributeString.substr(index1, index2 - index1);

		if ((index3 = attrPair.find("=", 0)) != string::npos) {

			string key = attrPair.substr(0, index3);
			string value = attrPair.substr(index3 + 1, attrPair.length()
					- index3);

			attributeMap.put(key, atof(value.c_str()));

		}

		index1 = index2 + 1;
	}

}


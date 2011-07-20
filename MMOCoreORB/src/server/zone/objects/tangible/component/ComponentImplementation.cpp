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

#include "Component.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"


void ComponentImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	attributeMap.setAllowOverwriteInsertPlan();
	precisionMap.setAllowOverwriteInsertPlan();
	titleMap.setAllowOverwriteInsertPlan();
	hiddenMap.setAllowOverwriteInsertPlan();

	setOptionsBitmask(0x2100);
}

void ComponentImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
}

void ComponentImplementation::fillAttributeList(AttributeListMessage* alm,
		CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	if (craftersName != "") {
		alm->insertAttribute("crafter", craftersName);
	}

	if (craftersSerial != "") {
		if (gameObjectType != LIGHTSABERCRYSTAL)
			alm->insertAttribute("serial_number", craftersSerial);
	}

	String attribute;

	float value;
	double power;
	int precision;
	bool hidden;

	String footer;

	for (int i = 0; i < keyList.size(); ++i) {
		footer = "";

		attribute = keyList.get(i);
		value = attributeMap.get(attribute);
		precision = precisionMap.get(attribute);
		hidden = hiddenMap.get(attribute);

		if (precision >= 0 && !hidden) {
			if (precision >= 10) {
				footer = "%";
				precision -= 10;
			}

			StringBuffer displayvalue;

			displayvalue << Math::getPrecision(value, precision);

			displayvalue << footer;

			alm->insertAttribute(attribute, displayvalue.toString());
		}
	}
}

float ComponentImplementation::getAttributeValue(String& attributeName){
	return attributeMap.get(attributeName);
}

int ComponentImplementation::getAttributePrecision(String& attributeName){
	return precisionMap.get(attributeName);
}

String ComponentImplementation::getAttributeTitle(String& attributeName){
	return titleMap.get(attributeName);
}

bool ComponentImplementation::getAttributeHidden(String& attributeName){
	return hiddenMap.get(attributeName);
}

void ComponentImplementation::setPropertyToHidden(const String& property) {
	for (int i = 0; i < keyList.size(); ++i) {
		if (keyList.get(i) == property) {
			hiddenMap.drop(property);
			hiddenMap.put(property, true);
		}
	}
}

void ComponentImplementation::updateCraftingValues(ManufactureSchematic* schematic) {

	CraftingValues* craftingValues = schematic->getCraftingValues();

	String attribute;
	float value;
	int precision;
	String title;
	bool hidden;

	attributeMap.removeAll();
	precisionMap.removeAll();
	titleMap.removeAll();
	keyList.removeAll();

	for (int i = 0; i < craftingValues->getExperimentalPropertySubtitleSize(); ++i) {
		attribute = craftingValues->getExperimentalPropertySubtitle(i);

		value = craftingValues->getCurrentValue(attribute);
		precision = craftingValues->getPrecision(attribute);
		title = craftingValues->getExperimentalPropertyTitle(attribute);
		hidden = craftingValues->isHidden(attribute);

		if (!hasKey(attribute))
			keyList.add(attribute);

		attributeMap.put(attribute, value);
		precisionMap.put(attribute, precision);
		titleMap.put(attribute, title);

		if(schematic->isFirstCraftingUpdate())
			hiddenMap.put(attribute, hidden);
	}
}

void ComponentImplementation::addProperty(const String& attributeName, const float value,
		const int precision, const String& craftingTitle, const bool hidden) {

	if (!hasKey(attributeName))
		keyList.add(attributeName);

	attributeMap.put(attributeName, value);
	precisionMap.put(attributeName, precision);
	titleMap.put(attributeName, craftingTitle);
	hiddenMap.put(attributeName, hidden);
}

void ComponentImplementation::addProperty(const String& attribute, const float value, const int precision, const String& title) {

	if (!attributeMap.contains(attribute)) {

		keyList.add(attribute);

		attributeMap.put(attribute, value);
		precisionMap.put(attribute, precision);
		titleMap.put(attribute, title);
		hiddenMap.put(attribute, false);
	} else {

		attributeMap.put(attribute, value);
	}
}

bool ComponentImplementation::changeAttributeValue(String& property, float value) {

	if (!hasKey(property))
		return false;

	attributeMap.drop(property);
	attributeMap.put(property, value);
	return true;
}

int ComponentImplementation::getPropertyCount() {
	return keyList.size();
}

String ComponentImplementation::getProperty(const int j){
	return keyList.get(j);
}

bool ComponentImplementation::compare(Component* inCmpo){
	for (int i = 0; i < attributeMap.size(); ++i){
		//if(attributeMap.elementAt(i).compareTo(inCmpo->getProperty(i)) != 0)
		if(_this->getProperty(i) != inCmpo->getProperty(i))
			return false;
	}
	return true;
}

void ComponentImplementation::generateLootStats(const String& lootstring, int level) {
	/*float luck = 0;

	StringTokenizer tokenizer1(lootstring);
	tokenizer1.setDelimeter(":");

	while (tokenizer1.hasMoreTokens()) {
		String token;
		tokenizer1.getStringToken(token);

		if (token.isEmpty())
			continue;

		StringTokenizer tokenizer2(token);
		tokenizer2.setDelimeter("=");

		String key;
		tokenizer2.getStringToken(key);

		if (!tokenizer2.hasMoreTokens())
			continue;

		String expvalue;
		tokenizer2.getStringToken(expvalue);

		if (!tokenizer2.hasMoreTokens())
			continue;

		int precision = tokenizer2.getIntToken();

		if (!tokenizer2.hasMoreTokens())
			continue;

		float min = tokenizer2.getFloatToken();

		if (!tokenizer2.hasMoreTokens())
			continue;

		float max = tokenizer2.getFloatToken();

		luck = calculateLuck(level);

		float finalvalue = (max - min) * (luck - 1.0f) + min;

		addProperty(key, finalvalue, precision, expvalue, false);
	}*/
}

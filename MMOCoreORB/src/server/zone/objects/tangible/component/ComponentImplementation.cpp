/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/tangible/component/Component.h"


void ComponentImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	attributeMap.setAllowOverwriteInsertPlan();
	precisionMap.setAllowOverwriteInsertPlan();
	titleMap.setAllowOverwriteInsertPlan();
	hiddenMap.setAllowOverwriteInsertPlan();
}

void ComponentImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
}

void ComponentImplementation::fillAttributeList(AttributeListMessage* alm,
		CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

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

float ComponentImplementation::getAttributeValue(const String& attributeName){
	return attributeMap.get(attributeName);
}

int ComponentImplementation::getAttributePrecision(const String& attributeName){
	return precisionMap.get(attributeName);
}

String ComponentImplementation::getAttributeTitle(const String& attributeName){
	return titleMap.get(attributeName);
}

bool ComponentImplementation::getAttributeHidden(const String& attributeName){
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

void ComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	String attribute;
	float value;
	int precision;
	String title;
	bool hidden;

	attributeMap.removeAll();
	precisionMap.removeAll();
	titleMap.removeAll();
	keyList.removeAll();

	if(firstUpdate && values->hasProperty("useCount")) {
		int count = values->getCurrentValue("useCount");

		// Crafting components dropped or crafted with a single use do not display a "1" (#6924)
		if(count > 1)
			setUseCount(count);
	}

	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		attribute = values->getExperimentalPropertySubtitle(i);

		if(attribute == "useCount")
			continue;

		value = values->getCurrentValue(attribute);
		precision = values->getPrecision(attribute);
		title = values->getExperimentalPropertyTitle(attribute);
		hidden = values->isHidden(attribute);

		if (!hasKey(attribute))
			keyList.add(attribute);

		attributeMap.put(attribute, value);
		precisionMap.put(attribute, precision);
		titleMap.put(attribute, title);

		if(firstUpdate)
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

bool ComponentImplementation::changeAttributeValue(const String& property, float value) {

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
		if(getProperty(i) != inCmpo->getProperty(i))
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

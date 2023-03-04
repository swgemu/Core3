/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "ValuesMap.h"

float ValuesMap::VALUENOTFOUND = -999999;
const String ValuesMap::EMPTY;

#define DEBUG_VALUES_MAP

/*
	The Values Map Constsist of the following:

	Attributes List
	Visible Attribute Group List

	attributeGroups VectorMap
	Contains the property and the group that it is effected by. Example <maxdamage, expDamage>

	attributeValues VectorMap
	Contains the property and the Value Object to store the data for that property.
*/

void ValuesMap::addExperimentalAttribute(const String& attribute, const String& group, const float min, const float max, const int precision, const bool filler, const int combine) {
#ifdef DEBUG_VALUES_MAP
	info(true) << "ValuesMap::addExperimentalAttribute called for: " << attribute << " Group: " << group;
#endif

	// The attribute is not on the map, add it.
	if (!attributes.contains(attribute)) {
		attributes.add(attribute);
		attributeGroups.put(attribute, group);

		Values* value = new Values(attribute, min, max, precision, filler, combine);
		attributeValues.put(attribute, value);
	} else {
		// The attribute is already on the map, we only want to update its values
		Reference<Values*> attValues = attributeValues.get(attribute);

		if (attValues == nullptr) {
			error() << "Values are nullptr for Experimental Attribute: " << attribute << " with group: " << group;
		}

		attValues->setMinValue(min);
		attValues->setMaxValue(max);
		attValues->setPrecision(precision);
		attValues->setFiller(filler);
		attValues->setCombineType(combine);
	}

	if (!filler && !visibleGroups.contains(group)) {
		visibleGroups.add(group);
	}
}

const String& ValuesMap::getAttribute(const int i) const {
	if (attributes.size() <= i)
		return EMPTY;

	return attributes.get(i);
}

const String& ValuesMap::getAttributeGroup(const String& attribute) const {
	if (attributeGroups.contains(attribute))
		return attributeGroups.get(attribute);

	return EMPTY;
}

const String& ValuesMap::getAttributeGroup(const int i) const {
	if (attributeGroups.size() > i)
		return attributeGroups.elementAt(i).getValue();

	return EMPTY;
}

const String& ValuesMap::getVisibleAttributeGroup(const int i) const {
	return visibleGroups.get(i);
}

int ValuesMap::getTotalVisibleAttributeGroups() const {
	return visibleGroups.size();
}

bool ValuesMap::hasAttribute(const String& attribute) const {
	return attributes.contains(attribute);
}

bool ValuesMap::isHidden(const String& attribute) const {
	Reference<Values*> values = attributeValues.get(attribute);

	if (values == nullptr)
		return false;

	return values->isFiller();
}

void ValuesMap::setHidden(const String& attribute) {
	Reference<Values*> values = attributeValues.get(attribute);

	if (values == nullptr)
		return;

	values->setFiller(true);

	String group;

	if (visibleGroups.contains(attribute)) {
		visibleGroups.drop(attribute);
	}
}

void ValuesMap::unsetHidden(const String& attribute) {
	Reference<Values*> values = attributeValues.get(attribute);

	if (values == nullptr)
		return;

	values->setFiller(false);
}

short ValuesMap::getCombineType(const String& attribute) const {
	Reference<Values*> values = attributeValues.get(attribute);

	if (values == nullptr)
		return (int)VALUENOTFOUND;

	return values->getCombineType();
}

void ValuesMap::setCurrentValue(const String& attribute, const float value) {
	Reference<Values*> values = attributeValues.get(attribute);

	if (values == nullptr)
		return;

	values->setValue(value);
}

void ValuesMap::setCurrentValue(const String& attribute, const float value, const float min, const float max) {
	Reference<Values*> values = attributeValues.get(attribute);

	if (values == nullptr)
		return;

	values->setValue(value);
	values->setMaxValue(max);
	values->setMinValue(min);
}

float ValuesMap::getCurrentValue(const String& attribute) const {
	Reference<Values*> values = attributeValues.get(attribute);

	if (values == nullptr)
		return VALUENOTFOUND;

	info(true) << " ValuesMap::getCurrentValue called for " << attribute << " with a value of " << values->getValue();

	return values->getValue();
}

float ValuesMap::getCurrentValue(const int i) const {
	const Values* value = attributeValues.get(i);

	if (value == nullptr)
		return VALUENOTFOUND;

	return value->getValue();
}

void ValuesMap::lockValue(const String& attribute) {
	Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return;

	value->lockValue();
}

void ValuesMap::unlockValue(const String& attribute) {
	Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return;

	value->unlockValue();
}

void ValuesMap::resetValue(const String& attribute) {
	Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return;

	value->resetValue();
}

void ValuesMap::setCurrentPercentage(const String& attribute, float amount) {
	Reference<Values*> value = attributeValues.get(attribute);

	info(true) << "---------- ValuesMap::setCurrentPercentage 1 for " << attribute << " setting amount: " << amount;

	if (value == nullptr)
		return;

	float max = value->getMaxPercentage();

	if (amount > max)
		amount = max;

	value->setPercentage(amount);

	info(true) << "---------- END ValuesMap::setCurrentPercentage 1";
}

void ValuesMap::setCurrentPercentage(const String& attribute, float amount, float max) {
	Reference<Values*> value = attributeValues.get(attribute);

	info(true) << "---------- ValuesMap::setCurrentPercentage 2 for " << attribute << " setting amount: " << amount;

	if (value == nullptr)
		return;

	if (amount > max)
		amount = max;

	value->setMaxPercentage(max);
	value->setPercentage(amount);

	info(true) << "---------- END ValuesMap::setCurrentPercentage 2";
}

float ValuesMap::getCurrentPercentage(const String& attribute) const {
	const Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return VALUENOTFOUND;

	return value->getPercentage();
}

float ValuesMap::getCurrentPercentage(const int i) const {
	const Reference<Values*> value = attributeValues.get(i);

	if (value == nullptr)
		return VALUENOTFOUND;

	return value->getPercentage();
}

float ValuesMap::getCurrentVisiblePercentage(const String group) const {
	float value = 0.f;

	info(true) << "---------- ValuesMap::getCurrentVisiblePercentage called for group: " << group << " with attribute value size: " << attributeValues.size() << " ----------";

	// shouldnt this show the avg so with 1 item who cares, but more than 1 we wanna should avg of all not the LAST one
	for (int j = 0; j < attributeValues.size(); ++j) {
		const Values* values = attributeValues.get(j);

		if (values == nullptr)
			continue;

		info(true) << " Checking attribute: " << attributeValues.elementAt(j).getKey() << " with a percentage of " << values->getPercentage();

		if (values->getMinValue() != values->getMaxValue() && values->getMaxPercentage() <= 1.0f && !values->isFiller()) {
			float item = values->getPercentage();

			if (item > value)
				value = item;
		}
	}

	info(true) << "---------- END ValuesMap::getCurrentVisiblePercentage ----------";

	return value;
}

void ValuesMap::setMaxPercentage(const String& attribute, float amount) {
	Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return;

	value->setMaxPercentage(amount);
}

float ValuesMap::getMaxPercentage(const String& attribute) const {
	const Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return VALUENOTFOUND;

	return value->getMaxPercentage();
}

float ValuesMap::getMaxPercentage(const int i) const {
	const Reference<Values*> value = attributeValues.get(i);

	if (value == nullptr)
		return VALUENOTFOUND;

	return value->getMaxPercentage();
}

float ValuesMap::getMaxVisiblePercentage(const int i) const {
	float value = 0;
	String group = getVisibleAttributeGroup(i);

	info(true) << "---------- ValuesMap::getMaxVisiblePercentage called for group: " << group << " with attribute value size: " << attributeValues.size() << " ----------";

	for (int j = 0; j < attributeValues.size(); ++j) {
		const Values* values = attributeValues.get(j);

		if (values == nullptr || values->isFiller())
			continue;

		if ((values->getMinValue() != values->getMaxValue()) && (values->getMaxPercentage() <= 1.0f) && (values->getMaxPercentage() > value)) {
			value = values->getMaxPercentage();
		}
	}

	return value;
}

float ValuesMap::getMinValue(const String& attribute) const {
	const Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return VALUENOTFOUND;

	info(true) << " ValuesMap::getMinValue called for " << attribute << " with a value of " << value->getMinValue();

	return value->getMinValue();
}

float ValuesMap::getMaxValue(const String& attribute) const {
	const Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return VALUENOTFOUND;

	info(true) << " ValuesMap::getMaxValue called for " << attribute << " with a value of " << value->getMaxValue();

	return value->getMaxValue();
}

void ValuesMap::setMinValue(const String& attribute, const float min) {
	Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return;

	info(true) << " ValuesMap::setMaxValue for " << attribute << " setting a value of " << min;

	value->setMinValue(min);
}

void ValuesMap::setMaxValue(const String& attribute, const float max) {
	Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return;

	info(true) << " ValuesMap::setMaxValue for " << attribute << " setting a value of " << max;

	value->setMaxValue(max);
}

int ValuesMap::getPrecision(const String& attribute) const {
	const Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return (int)VALUENOTFOUND;

	return value->getPrecision();
}

void ValuesMap::setPrecision(const String& attribute, const int amount) {
	Reference<Values*> value = attributeValues.get(attribute);

	if (value == nullptr)
		return;

	value->setPrecision(amount);
}

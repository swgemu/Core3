/*
 * PowerupStat.h
 *
 *  Created on: Mar 06, 2012
 *      Author: kyle
 */

#ifndef POWERUPSTAT_H_
#define POWERUPSTAT_H_

#include "engine/engine.h"

#include "engine/util/json_utils.h"

class PowerupStat: public virtual Serializable {
protected:
	SerializableString attributeToModify;
	SerializableString name;
	SerializableString pupAttribute;
	float value;
public:

	PowerupStat() {
		value = 0;

		addSerializableVariables();
	}

	PowerupStat(const PowerupStat& p) : Object(), Serializable() {
		attributeToModify = p.attributeToModify;
		name = p.name;
		pupAttribute = p.pupAttribute;
		value = p.value;

		addSerializableVariables();
	}

	PowerupStat(const String& att, const String& n, const String& p) {
		attributeToModify = att;
		name = n;
		pupAttribute = p;
		value = 0;

		addSerializableVariables();
	}

	PowerupStat& operator=(const PowerupStat& p) {
		if (this == &p)
			return *this;

		attributeToModify = p.attributeToModify;
		name = p.name;
		pupAttribute = p.pupAttribute;
		value = p.value;

		return *this;
	}

	bool operator==(const PowerupStat& stat) {
		if (this == &stat)
			return true;

		return ((attributeToModify == stat.attributeToModify)
				&& (name == stat.name) && (pupAttribute == stat.pupAttribute));
	}

	friend void to_json(nlohmann::json& j, const PowerupStat& s) {
		j["attributeToModify"] = s.attributeToModify;
		j["name"] = s.name;
		j["pupAttribute"] = s.pupAttribute;
		j["value"] = s.value;
	}

	void addSerializableVariables() {
		addSerializableVariable("attributeToModify", &attributeToModify);
		addSerializableVariable("name", &name);
		addSerializableVariable("pupAttribute", &pupAttribute);
		addSerializableVariable("value", &value);
	}

	const String& getAttributeToModify() const {
		return attributeToModify;
	}

	const String& getName() const {
		return name;
	}

	const String& getPupAttribute() const {
		return pupAttribute;
	}

	float getValue() const {
		return value;
	}

	void setValue(float v) {
		value = v;
	}
};

#endif /* POWERUPSTAT_H_ */

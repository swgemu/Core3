/*
 * PowerupStat.h
 *
 *  Created on: Mar 06, 2012
 *      Author: kyle
 */

#ifndef POWERUPSTAT_H_
#define POWERUPSTAT_H_

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

	void addSerializableVariables() {
		addSerializableVariable("attributeToModify", &attributeToModify);
		addSerializableVariable("name", &name);
		addSerializableVariable("pupAttribute", &pupAttribute);
		addSerializableVariable("value", &value);
	}

	String getAttributeToModify() {
		return attributeToModify;
	}

	String getName() {
		return name;
	}

	String getPupAttribute() {
		return pupAttribute;
	}

	float getValue() {
		return value;
	}

	void setValue(float v) {
		value = v;
	}
};

#endif /* POWERUPSTAT_H_ */

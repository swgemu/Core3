/*
 * NonPlayerCreatureObjectTemplate.h
 *
 *  Created on: 10/07/2010
 *      Author: victor
 */

#ifndef NONPLAYERCREATUREOBJECTTEMPLATE_H_
#define NONPLAYERCREATUREOBJECTTEMPLATE_H_

#include "SharedCreatureObjectTemplate.h"

class NonPlayerCreatureObjectTemplate : public SharedCreatureObjectTemplate {
	unsigned int armor;

	float kinetic;
	float energy;
	float electricity;
	float stun;
	float blast;
	float heat;
	float cold;
	float acid;
	float lightSaber;

	bool stalker;
	bool baby;
	bool killer;

	float tame;

	String meatType;
	String boneType;
	String hideType;

	float milk;
	float hideMax;
	float boneMax;
	float meatMax;

	unsigned int ferocity;

public:

	NonPlayerCreatureObjectTemplate() : SharedCreatureObjectTemplate() {
		armor = 0;

		kinetic = 0;
		energy = 0;
		electricity = 0;
		stun = 0;
		blast = 0;
		heat = 0;
		cold = 0;
		acid = 0;
		lightSaber = 0;

		stalker = false;
		baby = false;
		killer = false;
	}

	~NonPlayerCreatureObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedCreatureObjectTemplate::readObject(templateData);

		armor = templateData->getIntField("armor");

		kinetic = templateData->getFloatField("kinetic");
		energy = templateData->getFloatField("energy");
		electricity = templateData->getFloatField("electricity");
		stun = templateData->getFloatField("stun");
		blast = templateData->getFloatField("blast");
		heat = templateData->getFloatField("heat");
		cold = templateData->getFloatField("cold");
		acid = templateData->getFloatField("acid");
		lightSaber = templateData->getFloatField("lightSaber");

		stalker = templateData->getByteField("stalker");
		baby = templateData->getByteField("baby");
		killer = templateData->getByteField("killer");

		meatType = templateData->getStringField("meatType");
		boneType = templateData->getStringField("boneType");
		hideType = templateData->getStringField("hideType");
	}

	inline float getKinetic() {
		return kinetic;
	}

	inline float getEnergy() {
		return energy;
	}

	inline float getElectricity() {
		return electricity;
	}

	inline float getStun() {
		return stun;
	}

	inline float getBlast() {
		return blast;
	}

	inline float getHeat() {
		return heat;
	}

	inline float getCold() {
		return cold;
	}

	inline float getAcid() {
		return acid;
	}

	inline float getLightSaber() {
		return lightSaber;
	}

	inline bool isStalker() {
		return stalker;
	}

	inline bool isBaby() {
		return baby;
	}

	inline bool isKiller() {
		return killer;
	}

	inline float getTame() {
		return tame;
	}

	inline String& getMeatType() {
		return meatType;
	}

	inline String& getBoneType() {
		return boneType;
	}

	inline String& getHideType() {
		return hideType;
	}

	inline float getMilk() {
		return milk;
	}

	inline float getHideMax() {
		return hideMax;
	}

	inline float getBoneMax() {
		return boneMax;
	}

	inline float getMeatMax() {
		return meatMax;
	}

	inline unsigned int getFerocity() {
		return ferocity;
	}

	inline unsigned int getArmor() {
		return armor;
	}

	bool isNonPlayerCreatureObjectTemplate() {
		return true;
	}
};

#endif /* NONPLAYERCREATUREOBJECTTEMPLATE_H_ */

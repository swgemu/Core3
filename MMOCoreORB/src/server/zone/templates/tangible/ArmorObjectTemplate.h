/*
 * ArmorObjectTemplate.h
 *
 *  Created on: 01/06/2010
 *      Author: victor
 */

#ifndef ARMOROBJECTTEMPLATE_H_
#define ARMOROBJECTTEMPLATE_H_


#include "server/zone/templates/SharedTangibleObjectTemplate.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/managers/combat/CombatManager.h"

class ArmorObjectTemplate : public SharedTangibleObjectTemplate {
	int healthEncumbrance;
	int actionEncumbrance;
	int mindEncumbrance;

	int rating;

	float kinetic;
	float energy;
	float electricity;
	float stun;
	float blast;
	float heat;
	float cold;
	float acid;
	float lightSaber;

	int vulnerabilites;
	int specialResists;

	uint8 hitLocation;

public:
	ArmorObjectTemplate() {
		hitLocation = CombatManager::NOLOCATION;
	}

	~ArmorObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		vulnerabilites = templateData->getIntField("vulnerability");
		specialResists = templateData->getIntField("specialResists");

		healthEncumbrance = templateData->getIntField("healthEncumbrance");
		actionEncumbrance = templateData->getIntField("actionEncumbrance");
		mindEncumbrance = templateData->getIntField("mindEncumbrance");

		rating = templateData->getIntField("rating");

		kinetic = templateData->getFloatField("kinetic");
		energy = templateData->getFloatField("energy");
		electricity = templateData->getFloatField("electricity");
		stun = templateData->getFloatField("stun");
		blast = templateData->getFloatField("blast");
		heat = templateData->getFloatField("heat");
		cold = templateData->getFloatField("cold");
		acid = templateData->getFloatField("acid");
		lightSaber = templateData->getFloatField("lightSaber");

		hitLocation = templateData->getIntField("hitLocation");
	}

	inline float getAcid() const {
		return acid;
	}

	inline int getActionEncumbrance() const {
		return actionEncumbrance;
	}

	inline float getBlast() const {
		return blast;
	}

	inline float getCold() const {
		return cold;
	}

	inline float getElectricity() const {
		return electricity;
	}

	inline float getEnergy() const {
		return energy;
	}

	inline int getHealthEncumbrance() const {
		return healthEncumbrance;
	}

	inline float getHeat() const {
		return heat;
	}

	inline float getKinetic() const {
		return kinetic;
	}

	inline float getLightSaber() const {
		return lightSaber;
	}

	inline int getMindEncumbrance() const {
		return mindEncumbrance;
	}

	inline int getRating() const {
		return rating;
	}

	float getStun() const {
		return stun;
	}

	int getVulnerabilites() const {
		return vulnerabilites;
	}

	int getSpecialResists() const {
		return specialResists;
	}

	int getHitLocation() const {
		return hitLocation;
	}

	void setAcid(float acid) {
		this->acid = acid;
	}

	void setActionEncumbrance(int actionEncumbrance) {
		this->actionEncumbrance = actionEncumbrance;
	}

	void setBlast(float blast) {
		this->blast = blast;
	}

	void setCold(float cold) {
		this->cold = cold;
	}

	void setElectricity(float electricity) {
		this->electricity = electricity;
	}

	void setEnergy(float energy) {
		this->energy = energy;
	}

	void setHealthEncumbrance(int healthEncumbrance) {
		this->healthEncumbrance = healthEncumbrance;
	}

	void setHeat(float heat) {
		this->heat = heat;
	}

	void setKinetic(float kinetic) {
		this->kinetic = kinetic;
	}

	void setLightSaber(float lightSaber) {
		this->lightSaber = lightSaber;
	}

	void setMindEncumbrance(int mindEncumbrance) {
		this->mindEncumbrance = mindEncumbrance;
	}

	void setRating(int rating) {
		this->rating = rating;
	}

	void setStun(float stun) {
		this->stun = stun;
	}

	void setHitLocation(int hitLocation) {
		this->hitLocation = hitLocation;
	}

	bool isArmorObjectTemplate() {
		return true;
	}
};


#endif /* ARMOROBJECTTEMPLATE_H_ */

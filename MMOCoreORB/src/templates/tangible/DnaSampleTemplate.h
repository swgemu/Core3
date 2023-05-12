/*
 * DiceTemplate.h
 *
 *  Created on: March 16, 2012
 *	  Author: kyle
 */

#ifndef DNASAMPLETEMPLATE_H_
#define DNASAMPLETEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class DnaSampleTemplate: public SharedTangibleObjectTemplate {
protected:

	float cleverness;
	float endurance;
	float fierceness;
	float power;
	float intellect;
	float courage;
	float dependability;
	float dexterity;
	float fortitude;
	float hardiness;

	String source;
	String special1;
	String special2;
	bool ranged;
	String quality;

	int armorRating;
	float kinResist;
	float energyResist;
	float blastResist;
	float coldResist;
	float heatResist;
	float elecResist;
	float acidResist;
	float stunResist;
	float saberResist;

public:
	DnaSampleTemplate() {
		cleverness = 0.f;
		endurance = 0.f;
		fierceness = 0.f;
		power = 0.f;
		intellect = 0.f;
		courage = 0.f;
		dependability = 0.f;
		dexterity = 0.f;
		fortitude = 0.f;
		hardiness = 0.f;

		source = "unknown";
		ranged = false;
		special1 = "";
		special2 = "";
		quality = "Low";
		armorRating = 0;
		kinResist = -1;
		energyResist = -1;
		blastResist = -1;
		coldResist = -1;
		heatResist = -1;
		elecResist = -1;
		acidResist = -1;
		stunResist = -1;
		saberResist = -1;
	}

	~DnaSampleTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);
		quality = templateData->getStringField("quality");
	}

	float getAcidResist() const {
		return acidResist;
	}

	float getSaberResist() const {
		return saberResist;
	}

	int getArmorRating() const {
		return armorRating;
	}

	float getBlastResist() const {
		return blastResist;
	}

	float getCleverness() const {
		return cleverness;
	}

	float getColdResist() const {
		return coldResist;
	}

	float getCourage() const {
		return courage;
	}

	float getDependability() const {
		return dependability;
	}

	float getDexterity() const {
		return dexterity;
	}

	float getElecResist() const {
		return elecResist;
	}

	float getEndurance() const {
		return endurance;
	}

	float getEnergyResist() const {
		return energyResist;
	}

	float getFierceness() const {
		return fierceness;
	}

	float getFortitude() const {
		return fortitude;
	}

	float getHardiness() const {
		return hardiness;
	}

	float getHeatResist() const {
		return heatResist;
	}

	float getIntellect() const {
		return intellect;
	}

	float getKinResist() const {
		return kinResist;
	}

	float getPower() const {
		return power;
	}

	String getQuality() const {
		return quality;
	}

	bool getRanged() const {
		return ranged;
	}

	String getSource() const {
		return source;
	}

	String getSpecial1() const {
		return special1;
	}

	String getSpecial2() const {
		return special2;
	}

	float getStunResist() const {
		return stunResist;
	}

	void setAcidResist(float acidResist) {
		this->acidResist = acidResist;
	}

	void setSaberResist(float value) {
		this->saberResist = value;
	}

	void setArmorRating(int armorRating) {
		this->armorRating = armorRating;
	}

	void setBlastResist(float blastResist) {
		this->blastResist = blastResist;
	}

	void setCleverness(float cleverness) {
		this->cleverness = cleverness;
	}

	void setColdResist(float coldResist) {
		this->coldResist = coldResist;
	}

	void setCourage(float courage) {
		this->courage = courage;
	}

	void setDependability(float dependability) {
		this->dependability = dependability;
	}

	void setDexterity(float dexterity) {
		this->dexterity = dexterity;
	}

	void setElecResist(float elecResist) {
		this->elecResist = elecResist;
	}

	void setEndurance(float endurance) {
		this->endurance = endurance;
	}

	void setEnergyResist(int energyResist) {
		this->energyResist = energyResist;
	}

	void setFierceness(float fierceness) {
		this->fierceness = fierceness;
	}

	void setFortitude(float fortitude) {
		this->fortitude = fortitude;
	}

	void setHardiness(float hardiness) {
		this->hardiness = hardiness;
	}

	void setHeatResist(float heatResist) {
		this->heatResist = heatResist;
	}

	void setIntellect(float intellect) {
		this->intellect = intellect;
	}

	void setKinResist(float kinResist) {
		this->kinResist = kinResist;
	}

	void setPower(float power) {
		this->power = power;
	}

	void setQuality(String quality) {
		this->quality = quality;
	}

	void setRanged(bool ranged) {
		this->ranged = ranged;
	}

	void setSource(String source) {
		this->source = source;
	}

	void setSpecial1(String special1) {
		this->special1 = special1;
	}

	void setSpecial2(String special2) {
		this->special2 = special2;
	}

	void setStunResist(float stunResist) {
		this->stunResist = stunResist;
	}

	bool isDnaSampleTemplate() {
		return true;
	}
};

#endif /* DNASAMPLETEMPLATE_H_ */

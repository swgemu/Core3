/*
 * DiceTemplate.h
 *
 *  Created on: March 16, 2012
 *      Author: kyle
 */

#ifndef DNASAMPLETEMPLATE_H_
#define DNASAMPLETEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class DnaSampleTemplate: public SharedTangibleObjectTemplate {
protected:

	uint32 cleverness;
	uint32 endurance;
	uint32 fierceness;
	uint32 power;
	uint32 intelligence;
	uint32 courage;
	uint32 dependency;
	uint32 dexterity;
	uint32 fortitude;
	uint32 hardiness;
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
		cleverness = 0;
		endurance = 0;
		fierceness = 0;
		power = 0;
		intelligence = 0;
		courage = 0;
		dependency = 0;
		dexterity = 0;
		fortitude = 0;
		hardiness = 0;
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

	float getAcidResist() const
	{
	    return acidResist;
	}

	float getSaberResist() const
	{
	    return saberResist;
	}

	int getArmorRating() const
	{
	    return armorRating;
	}

	float getBlastResist() const
	{
	    return blastResist;
	}

	uint32 getCleverness() const
	{
	    return cleverness;
	}

	float getColdResist() const
	{
	    return coldResist;
	}

	uint32 getCourage() const
	{
	    return courage;
	}

	uint32 getDependency() const
	{
	    return dependency;
	}

	uint32 getDexterity() const
	{
	    return dexterity;
	}

	float getElecResist() const
	{
	    return elecResist;
	}

	uint32 getEndurance() const
	{
	    return endurance;
	}

	float getEnergyResist() const
	{
	    return energyResist;
	}

	uint32 getFierceness() const
	{
	    return fierceness;
	}

	uint32 getFortitude() const
	{
	    return fortitude;
	}

	uint32 getHardiness() const
	{
	    return hardiness;
	}

	float getHeatResist() const
	{
	    return heatResist;
	}

	uint32 getIntelligence() const
	{
	    return intelligence;
	}

	float getKinResist() const
	{
	    return kinResist;
	}

	uint32 getPower() const
	{
	    return power;
	}

	String getQuality() const
	{
	    return quality;
	}

	bool getRanged() const
	{
	    return ranged;
	}

	String getSource() const
	{
	    return source;
	}

	String getSpecial1() const
	{
	    return special1;
	}

	String getSpecial2() const
	{
	    return special2;
	}

	int getStunResist() const
	{
	    return stunResist;
	}

	void setAcidResist(float acidResist)
	{
	    this->acidResist = acidResist;
	}

	void setSaberResist(float value)
	{
	    this->saberResist = value;
	}

	void setArmorRating(int armorRating)
	{
	    this->armorRating = armorRating;
	}

	void setBlastResist(float blastResist)
	{
	    this->blastResist = blastResist;
	}

	void setCleverness(uint32 cleverness)
	{
	    this->cleverness = cleverness;
	}

	void setColdResist(float coldResist)
	{
	    this->coldResist = coldResist;
	}

	void setCourage(uint32 courage)
	{
	    this->courage = courage;
	}

	void setDependency(uint32 dependency)
	{
	    this->dependency = dependency;
	}

	void setDexterity(uint32 dexterity)
	{
	    this->dexterity = dexterity;
	}

	void setElecResist(int elecResist)
	{
	    this->elecResist = elecResist;
	}

	void setEndurance(uint32 endurance)
	{
	    this->endurance = endurance;
	}

	void setEnergyResist(int energyResist)
	{
	    this->energyResist = energyResist;
	}

	void setFierceness(uint32 fierceness)
	{
	    this->fierceness = fierceness;
	}

	void setFortitude(uint32 fortitude)
	{
	    this->fortitude = fortitude;
	}

	void setHardiness(uint32 hardiness)
	{
	    this->hardiness = hardiness;
	}

	void setHeatResist(float heatResist)
	{
	    this->heatResist = heatResist;
	}

	void setIntelligence(uint32 intelligence)
	{
	    this->intelligence = intelligence;
	}

	void setKinResist(float kinResist)
	{
	    this->kinResist = kinResist;
	}

	void setPower(uint32 power)
	{
	    this->power = power;
	}

	void setQuality(String quality)
	{
	    this->quality = quality;
	}

	void setRanged(bool ranged)
	{
	    this->ranged = ranged;
	}

	void setSource(String source)
	{
	    this->source = source;
	}

	void setSpecial1(String special1)
	{
	    this->special1 = special1;
	}

	void setSpecial2(String special2)
	{
	    this->special2 = special2;
	}

	void setStunResist(float stunResist)
	{
	    this->stunResist = stunResist;
	}
	bool isDnaSampleTemplate() {
		return true;
	}
};
#endif /* DNASAMPLETEMPLATE_H_ */

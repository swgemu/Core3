/*
 * SharedInstallationObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: victor
 */

#ifndef SHAREDINSTALLATIONOBJECTTEMPLATE_H_
#define SHAREDINSTALLATIONOBJECTTEMPLATE_H_

#include "templates/tangible/SharedStructureObjectTemplate.h"

class SharedInstallationObjectTemplate : public SharedStructureObjectTemplate {
	uint32 installationType;
	unsigned int armorRating;
	float kinetic;
	float energy;
	float electricity;
	float stun;
	float blast;
	float heat;
	float cold;
	float acid;
	float lightSaber;
	float chanceHit;
	String weapon;
	String factionString;

public:
	SharedInstallationObjectTemplate() {
		installationType = 0;

		armorRating = 0;
		kinetic = 0;
		energy = 0;
		electricity = 0;
		stun = 0;
		blast = 0;
		heat = 0;
		cold = 0;
		acid = 0;
		lightSaber = 0;
		weapon = "";
		chanceHit = 0;
		factionString = "";
	}

	~SharedInstallationObjectTemplate() {
	}

	void readObject(LuaObject* templateData) {
		SharedStructureObjectTemplate::readObject(templateData);

		installationType = templateData->getIntField("installationType");

		armorRating = templateData->getIntField("rating");
		kinetic = templateData->getFloatField("kinetic");
		energy = templateData->getFloatField("energy");
		electricity = templateData->getFloatField("electricity");
		stun = templateData->getFloatField("stun");
		blast = templateData->getFloatField("blast");
		heat = templateData->getFloatField("heat");
		cold = templateData->getFloatField("cold");
		acid = templateData->getFloatField("acid");
		lightSaber = templateData->getFloatField("lightSaber");
		weapon = templateData->getStringField("weapon");
		chanceHit = templateData->getFloatField("chanceHit");
		factionString = templateData->getStringField("factionString");
	}

	void readObject(IffStream* iffStream) {
		uint32 nextType = iffStream->getNextFormType();

		if (nextType != 'SIOT') {
			//Logger::console.error("expecting SHOT got " + String::hexvalueOf((int)nextType));

			SharedTangibleObjectTemplate::readObject(iffStream);

			return;
		}

		iffStream->openForm('SIOT');

		uint32 derv = iffStream->getNextFormType();

		if (derv == 'DERV') {
			loadDerv(iffStream);

			derv = iffStream->getNextFormType();
		}

		/*while (derv != 0) {
							if (derv != '
						}*/

		iffStream->openForm(derv);

		try {
			//parseFileData(iffStream);
		} catch (Exception& e) {
			String msg;
			msg += "exception caught parsing file data ->";
			msg += e.getMessage();

			Logger::console.error(msg);
		}

		iffStream->closeForm(derv);

		if (iffStream->getRemainingSubChunksNumber() > 0) {
			readObject(iffStream);
		}

		iffStream->closeForm('SIOT');
	}

	virtual bool isSharedInstallationObjectTemplate() {
		return true;
	}

	inline uint32 getInstallationType() {
		return installationType;
	}

	inline unsigned int getArmorRating() {
		return armorRating;
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

	inline const String& getWeapon() {
		return weapon;
	}

	inline float getChanceHit() {
		return chanceHit;
	}

	inline const String& getFactionString() {
		return factionString;
	}
};


#endif /* SHAREDINSTALLATIONOBJECTTEMPLATE_H_ */

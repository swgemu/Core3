/*
 * LightsaberCrystalObjectTemplate.h
 *
 *  Created on: Sep 28, 2010
 *      Author: swgemu
 */

#ifndef LIGHTSABERCRYSTALOBJECTTEMPLATE_H_
#define LIGHTSABERCRYSTALOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class LightsaberCrystalObjectTemplate : public SharedTangibleObjectTemplate {

public:
	LightsaberCrystalObjectTemplate() {

	}

	~LightsaberCrystalObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);


    }

	bool isLightsaberCrystalTemplate() {
		return true;
	}
};


#endif /* LIGHTSABERCRYSTALOBJECTTEMPLATE_H_ */

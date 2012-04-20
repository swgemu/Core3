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
	String postTunedName;

public:
	LightsaberCrystalObjectTemplate() {

	}

	~LightsaberCrystalObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		postTunedName = templateData->getStringField("postTunedName");
    }

	bool isLightsaberCrystalTemplate() {
		return true;
	}

	inline String& getPostTunedName() {
		return postTunedName;
	}
};


#endif /* LIGHTSABERCRYSTALOBJECTTEMPLATE_H_ */

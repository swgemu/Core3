/*
 * CreatureHabitatTemplate.h
 *
 *  Created on: March 16, 2012
 *      Author: kyle
 */

#ifndef CREATUREHABITATTEMPLATE_H_
#define CREATUREHABITATTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class CreatureHabitatTemplate: public SharedTangibleObjectTemplate {

public:
	CreatureHabitatTemplate() {

	}

	~CreatureHabitatTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

	}

	bool isCreatureHabitatTemplate() {
		return true;
	}

};






#endif /* CREATUREHABITATTEMPLATE_H_ */

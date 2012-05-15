/*
 * NonPlayerCreatureObjectTemplate.h
 *
 *  Created on: 10/07/2010
 *      Author: victor
 */

#ifndef NONPLAYERCREATUREOBJECTTEMPLATE_H_
#define NONPLAYERCREATUREOBJECTTEMPLATE_H_

#include "SharedCreatureObjectTemplate.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/objects/creature/CreatureFlag.h"
#include "server/zone/objects/creature/variables/CreatureAttackMap.h"

class NonPlayerCreatureObjectTemplate : public SharedCreatureObjectTemplate {

public:

	NonPlayerCreatureObjectTemplate() {
	}

	virtual ~NonPlayerCreatureObjectTemplate() {
	}

	void readObject(LuaObject* templateData) {
		SharedCreatureObjectTemplate::readObject(templateData);
	}

	bool isNonPlayerCreatureObjectTemplate() {
		return true;
	}
};

#endif /* NONPLAYERCREATUREOBJECTTEMPLATE_H_ */

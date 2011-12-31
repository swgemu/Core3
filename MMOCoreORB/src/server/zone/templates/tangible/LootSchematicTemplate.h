/*
 * LootSchematicTemplate.h
 *
 *  Created on: Dec 29, 2011
 *      Author: kyle
 */

#ifndef LOOTSCHEMATICTEMPLATE_H_
#define LOOTSCHEMATICTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class LootSchematicTemplate: public SharedTangibleObjectTemplate {
protected:

	String targetDraftSchematic;
	int targetUseCount;


public:
	LootSchematicTemplate() {
		targetDraftSchematic = "";
		targetUseCount = 1;
	}

	~LootSchematicTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		targetDraftSchematic = templateData->getStringField("targetDraftSchematic");
		targetUseCount = templateData->getIntField("targetUseCount");
	}

	const String& getTargetDraftSchematic() {
		return targetDraftSchematic;
	}

	int getTargetUseCount() {
		return targetUseCount;
	}

};


#endif /* LOOTSCHEMATICTEMPLATE_H_ */

/*
 * SchematicFragmentTemplate.h
 *
 *  Created on: 02/06/2025
 *      Author: Halyn
 */

#ifndef SCHEMATICFRAGMENTTEMPLATE_H_
#define SCHEMATICFRAGMENTTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class SchematicFragmentTemplate : public SharedTangibleObjectTemplate {
protected:
	int totalFragments;
	unsigned int fragmentBitmask;
	uint32 targetSchematic;


public:
	SchematicFragmentTemplate() {
		totalFragments = 0;
		fragmentBitmask = 0;
		targetSchematic = 0;
	}

	~SchematicFragmentTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		totalFragments = templateData->getIntField("totalFragments");
		fragmentBitmask = templateData->getIntField("fragmentBitmask");
		targetSchematic = templateData->getStringField("targetSchematic").hashCode();
	}

	inline int getTotalFragments() {
		return totalFragments;
	}

	inline unsigned int getfragmentBitmask() {
		return fragmentBitmask;
	}

	bool isSchematicFragmentTemplate() {
		return true;
	}

	inline uint32 getTargetSchematic() {
		return targetSchematic;
	}
};

#endif

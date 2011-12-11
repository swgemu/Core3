/*
 * SpawnGroup.h
 *
 *  Created on: Nov 3, 2010
 *      Author: da
 */

#ifndef SPAWNGROUP_H_
#define SPAWNGROUP_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class SpawnGroup : public Object {
protected:
	String templateName;

	float wanderRadius;
	int commandLevel;

	unsigned int type;

public:
	SpawnGroup() {}

	SpawnGroup(const String& tempName, LuaObject& group) {
		templateName = tempName;
		wanderRadius = group.getFloatField("wanderRadius");
		commandLevel = group.getIntField("commandLevel");
		type = group.getIntField("type");
	}

	SpawnGroup(const SpawnGroup& gr) : Object() {
		templateName = gr.templateName;
		wanderRadius = gr.wanderRadius;
		commandLevel = gr.commandLevel;
		type = gr.type;
	}

	virtual ~SpawnGroup() {}

	SpawnGroup& operator=(const SpawnGroup& gr) {
		if (this == &gr)
			return *this;

		templateName = gr.templateName;
		wanderRadius = gr.wanderRadius;
		commandLevel = gr.commandLevel;
		type = gr.type;

		return *this;
	}

	String getTemplateName() const {
		return templateName;
	}

	float getWanderRadius() const {
		return wanderRadius;
	}

	int getCommandLevel() const {
		return commandLevel;
	}

	unsigned int getType() const {
		return type;
	}

	void setWanderRadius(float wanderRadius) {
		this->wanderRadius = wanderRadius;
	}

	void setTemplateName(String templateName) {
		this->templateName = templateName;
	}

	void setCommandLevel(int commandLevel) {
		this->commandLevel = commandLevel;
	}

	void setType(unsigned int type) {
		this->type = type;
	}

	virtual bool isStaticGroup() {
		return false;
	}

	virtual bool isDynamicGroup() {
		return false;
	}
};

}
}
}
}

#endif /* SPAWNGROUP_H_ */

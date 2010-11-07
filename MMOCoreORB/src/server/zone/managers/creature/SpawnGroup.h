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

	int wanderRadius;
	int commandLevel;

	int size;

	unsigned int type;

	Vector<String> scoutTemplates;
	float scoutWeight;

	Vector<String> protectorTemplates;
	float protectorWeight;

	Vector<String> babyTemplates;
	float babyWeight;

	String lairTemplate;

public:
	SpawnGroup() {}

	SpawnGroup(String tempName, LuaObject group) {
		templateName = tempName;

		wanderRadius = group.getIntField("wanderRadius");
		commandLevel = group.getIntField("commandLevel");

		size = group.getIntField("size");

		type = group.getIntField("type");

		LuaObject scouts(group.getObjectField("scout"));
		if (scouts.isValidTable()) {
			for (int i = 1; i <= scouts.getTableSize(); ++i)
				scoutTemplates.add(scouts.getStringAt(i));
		}

		scouts.pop();

		scoutWeight = group.getFloatField("scoutWeight");

		LuaObject protectors(group.getObjectField("protector"));
		if (protectors.isValidTable()) {
			for (int i = 1; i <= protectors.getTableSize(); ++i)
				protectorTemplates.add(protectors.getStringAt(i));
		}

		protectors.pop();

		protectorWeight = group.getFloatField("protectorWeight");

		LuaObject babies(group.getObjectField("baby"));
		if (babies.isValidTable()) {
			for (int i = 1; i <= babies.getTableSize(); ++i)
				babyTemplates.add(babies.getStringAt(i));
		}

		babies.pop();

		babyWeight = group.getFloatField("babyWeight");

		lairTemplate = group.getStringField("lairTemplate");
	}

	virtual ~SpawnGroup() {}

	Vector<String> getBabyTemplates() const {
		return babyTemplates;
	}

	float getBabyWeight() const {
		return babyWeight;
	}

	String getLairTemplate() const {
		return lairTemplate;
	}

	Vector<String> getProtectorTemplates() const {
		return protectorTemplates;
	}

	float getProtectorWeight() const {
		return protectorWeight;
	}

	Vector<String> getScoutTemplates() const {
		return scoutTemplates;
	}

	float getScoutWeight() const {
		return scoutWeight;
	}

	String getTemplateName() const {
		return templateName;
	}

	int getWanderRadius() const {
		return wanderRadius;
	}

	int getCommandLevel() const {
		return commandLevel;
	}

	int getSize() const {
		return size;
	}

	unsigned int getType() const {
		return type;
	}

	void setBabyTemplates(Vector<String> babyTemplates) {
		this->babyTemplates = babyTemplates;
	}

	void setBabyWeight(float babyWeight) {
		this->babyWeight = babyWeight;
	}

	void setLairTemplate(String lairTemplate) {
		this->lairTemplate = lairTemplate;
	}

	void setProtectorTemplates(Vector<String> protectorTemplates) {
		this->protectorTemplates = protectorTemplates;
	}

	void setProtectorWeight(float protectorWeight) {
		this->protectorWeight = protectorWeight;
	}

	void setScoutTemplates(Vector<String> scoutTemplates) {
		this->scoutTemplates = scoutTemplates;
	}

	void setScoutWeight(float scoutWeight) {
		this->scoutWeight = scoutWeight;
	}

	void setTemplateName(String templateName) {
		this->templateName = templateName;
	}

	void setWanderRadius(int wanderRadius) {
		this->wanderRadius = wanderRadius;
	}

	void setCommandLevel(int commandLevel) {
		this->commandLevel = commandLevel;
	}

	void setSize(int size) {
		this->size = size;
	}

	void setType(unsigned int type) {
		this->type = type;
	}
};

}
}
}
}

#endif /* SPAWNGROUP_H_ */

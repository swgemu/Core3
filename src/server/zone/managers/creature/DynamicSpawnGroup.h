/*
 * DynamicSpawnGroup.h
 *
 *  Created on: Nov 13, 2010
 *      Author: da
 */

#ifndef DYNAMICSPAWNGROUP_H_
#define DYNAMICSPAWNGROUP_H_

#include "SpawnGroup.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {

class DynamicSpawnGroup : public SpawnGroup {
protected:
	int size;

	Vector<String> scoutTemplates;
	float scoutWeight;

	Vector<String> protectorTemplates;
	float protectorWeight;

	Vector<String> babyTemplates;
	float babyWeight;

	String lairTemplate;

public:
	DynamicSpawnGroup() {}

	DynamicSpawnGroup(const DynamicSpawnGroup& ds) : SpawnGroup(ds) {
		size = ds.size;

		scoutTemplates = ds.scoutTemplates;

		scoutWeight = ds.scoutWeight;

		protectorTemplates = ds.protectorTemplates;
		protectorWeight = ds.protectorWeight;

		babyTemplates = ds.babyTemplates;
		babyWeight = ds.babyWeight;

		lairTemplate = ds.lairTemplate;
	}

	DynamicSpawnGroup(String tempName, LuaObject group) : SpawnGroup(tempName, group) {
		size = group.getIntField("size");

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

	virtual ~DynamicSpawnGroup() {}

	DynamicSpawnGroup& operator=(const DynamicSpawnGroup& ds) {
		if (this == &ds)
			return *this;

		size = ds.size;

		scoutTemplates = ds.scoutTemplates;

		scoutWeight = ds.scoutWeight;

		protectorTemplates = ds.protectorTemplates;
		protectorWeight = ds.protectorWeight;

		babyTemplates = ds.babyTemplates;
		babyWeight = ds.babyWeight;

		lairTemplate = ds.lairTemplate;

		return *this;
	}

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

	int getSize() const {
		return size;
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

	void setSize(int size) {
		this->size = size;
	}

	bool isDynamicGroup() {
		return true;
	}
};

}
}
}
}

#endif /* DYNAMICSPAWNGROUP_H_ */

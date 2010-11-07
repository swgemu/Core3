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

	int commandLevel;

	unsigned int type;

public:
	SpawnGroup() {}

	SpawnGroup(String tempName, LuaObject group) {
		templateName = tempName;
		commandLevel = group.getIntField("commandLevel");
		type = group.getIntField("type");
	}

	virtual ~SpawnGroup() {}

	String getTemplateName() const {
		return templateName;
	}

	int getCommandLevel() const {
		return commandLevel;
	}

	unsigned int getType() const {
		return type;
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

class SpawnCoordinate : public Coordinate, public Quaternion {
protected:
	String templateName;
	uint64 cellID;

public:
	SpawnCoordinate() {}
	virtual ~SpawnCoordinate() {}

	uint64 getCellID() const {
		return cellID;
	}

	String getTemplateName() const {
		return templateName;
	}

	void setCellID(uint64 cellID) {
		this->cellID = cellID;
	}

	void setTemplateName(String templateName) {
		this->templateName = templateName;
	}

};

class StaticSpawnGroup : public SpawnGroup {
protected:
	Vector<SpawnCoordinate> spawnMap;

public:
	StaticSpawnGroup() {}

	StaticSpawnGroup(String tempName, LuaObject group) : SpawnGroup(tempName, group) {
		LuaObject spawns = group.getObjectField("spawns");
		if (spawns.isValidTable()) {
			lua_State* L = spawns.getLuaState();

			for (int i = 1; i <= spawns.getTableSize(); ++i) {
				lua_rawgeti(L, -1, i);
				LuaObject templ(L);

				if (templ.isValidTable()) {
					if (templ.getTableSize() >= 9) {
						SpawnCoordinate coord;

						coord.setTemplateName(templ.getStringField("name"));

						coord.setPosition(templ.getFloatField("x"), templ.getFloatField("y"), templ.getFloatField("z"));

						coord.set(templ.getFloatField("ow"), templ.getFloatField("ox"), templ.getFloatField("oy"), templ.getFloatField("oz"));

						coord.setCellID(templ.getLongField("cellID"));
					}
				}

				templ.pop();
			}
		}

		spawns.pop();
	}

	virtual ~StaticSpawnGroup() {}

	Vector<SpawnCoordinate> getSpawnList() {
		return spawnMap;
	}

	bool isStaticGroup() {
		return true;
	}
};

class DynamicSpawnGroup : public SpawnGroup {
protected:
	int wanderRadius;

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

	DynamicSpawnGroup(String tempName, LuaObject group) : SpawnGroup(tempName, group) {
		wanderRadius = group.getIntField("wanderRadius");

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

	int getWanderRadius() const {
		return wanderRadius;
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

	void setWanderRadius(int wanderRadius) {
		this->wanderRadius = wanderRadius;
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

#endif /* SPAWNGROUP_H_ */

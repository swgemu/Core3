/*
 * SharedResourceContainerObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef CRAFTINGTOOLTEMPLATE_H_
#define CRAFTINGTOOLTEMPLATE_H_

#include "templates/SharedTangibleObjectTemplate.h"

class CraftingToolTemplate : public SharedTangibleObjectTemplate {
private:

	int toolType, complexityLevel, forceCritAssembly, forceCritExperiment;
	Vector<uint32> tabs;

public:
	CraftingToolTemplate() : toolType(0), complexityLevel(0), forceCritAssembly(0), forceCritExperiment(0) {

	}

	~CraftingToolTemplate() {

	}

	void readObject(LuaObject* templateData) override {
		SharedTangibleObjectTemplate::readObject(templateData);

		toolType = templateData->getIntField("toolType");
		complexityLevel = templateData->getIntField("complexityLevel");
		forceCritAssembly = templateData->getIntField("forceCriticalAssembly");
		forceCritExperiment = templateData->getIntField("forceCriticalExperiment");

		LuaObject tabList = templateData->getObjectField("enabledTabs");

		for (int i = 1; i <= tabList.getTableSize(); ++i) {
			tabs.add(tabList.getIntAt(i));
		}

		tabList.pop();
	}

	int getToolType() const {
		return toolType;
	}

	int getComplexityLevel() const {
		return complexityLevel;
	}

	int getForceCriticalAssembly() const {
		return forceCritAssembly;
	}

	int getForceCriticalExperiment() const {
		return forceCritExperiment;
	}

	const Vector<uint32>& getTabs() const {
		return tabs;
	}

};

#endif /* CRAFTINGTOOLTEMPLATE_H_ */

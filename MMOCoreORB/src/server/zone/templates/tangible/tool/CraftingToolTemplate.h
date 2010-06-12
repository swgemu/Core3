/*
 * SharedResourceContainerObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef CRAFTINGTOOLTEMPLATE_H_
#define CRAFTINGTOOLTEMPLATE_H_

#include "../../SharedTangibleObjectTemplate.h"

class CraftingToolTemplate : public SharedTangibleObjectTemplate {
private:

	int toolType;
	Vector<uint32> tabs;

public:
	CraftingToolTemplate() {

	}

	~CraftingToolTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedTangibleObjectTemplate::readObject(templateData);

		toolType = templateData->getIntField("toolType");

		LuaObject tabList = templateData->getObjectField("enabledTabs");

		for (int i = 1; i <= tabList.getTableSize(); ++i) {
			tabs.add(tabList.getIntAt(i));
		}

		tabList.pop();
	}

	int getToolType() {
		return toolType;
	}

	Vector<uint32> getTabs() {
		return tabs;
	}

};

#endif /* CRAFTINGTOOLTEMPLATE_H_ */

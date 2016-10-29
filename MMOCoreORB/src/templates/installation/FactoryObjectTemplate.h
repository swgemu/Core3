/*
 * SharedFactoryObjectTemplate.h
 *
 *  Created on: 06/05/2010
 *      Author: kyle
 */

#ifndef FACTORYOBJECTTEMPLATE_H_
#define FACTORYOBJECTTEMPLATE_H_

#include "templates/installation/SharedInstallationObjectTemplate.h"

class FactoryObjectTemplate : public SharedInstallationObjectTemplate {
public:
	Vector<int> craftingTabsSupported;

public:
	FactoryObjectTemplate() {

	}

	~FactoryObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedInstallationObjectTemplate::readObject(templateData);

		LuaObject craftingTabsSupportedList = templateData->getObjectField("craftingTabsSupported");

		for (int i = 1; i < craftingTabsSupportedList.getTableSize() + 1; ++i)
			craftingTabsSupported.add(craftingTabsSupportedList.getIntAt(i));

		craftingTabsSupportedList.pop();
	}

	Vector<int> getCraftingTabsSupported()
	{
	    return craftingTabsSupported;
	}

	bool isFactoryObjectTemplate() {
		return true;
	}
};

#endif /* FACTORYOBJECTTEMPLATE_H_ */

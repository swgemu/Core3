/*
 * TemplateManager.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TEMPLATEMANAGER_H_
#define TEMPLATEMANAGER_H_

#include "engine/engine.h"
#include "TemplateCRCMap.h"

#include "engine/util/ObjectFactory.h"

class TemplateManager : public Singleton<TemplateManager>, public Logger {
	TemplateCRCMap templateCRCMap;

	ObjectFactory<SharedObjectTemplate* (), uint32> templateFactory;

public:
	TemplateManager();

	~TemplateManager();

	void registerTemplateObjects();

	void addTemplate(uint32 key, const String& fullName, LuaObject* templateData);

	String getTemplateFile(uint32 key) {
		SharedObjectTemplate* templateData = templateCRCMap.get(key);

		if (templateData == NULL)
			throw Exception("TemplateManager::getTemplateFile exception unknown template key 0x" + String::hexvalueOf((int)key));

		return templateData->getFullTemplateString();
	}

	SharedObjectTemplate* getTemplate(uint32 key) {
		return templateCRCMap.get(key);
	}

	bool existsTemplate(uint32 key) {
		return templateCRCMap.containsKey(key);
	}

};


#endif /* TEMPLATEMANAGER_H_ */

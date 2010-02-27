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

class TemplateManager : public Singleton<TemplateManager> {
	TemplateCRCMap templateCRCMap;

public:
	TemplateManager() {

	}

	void addTemplate(uint32 key, const String& templateFile) {
		templateCRCMap.put(key, templateFile);
	}

	String getTemplateFile(uint32 key) {
		return templateCRCMap.get(key);
	}

	bool existsTemplate(uint32 key) {
		return templateCRCMap.containsKey(key);
	}

};


#endif /* TEMPLATEMANAGER_H_ */

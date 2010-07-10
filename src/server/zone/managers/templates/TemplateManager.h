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
	ClientTemplateCRCMap clientTemplateCRCMap;

public:
	static Lua* luaTemplatesInstance;

public:
	TemplateManager();
	~TemplateManager();

	void registerTemplateObjects();

	void loadLuaTemplates() {
		info("loading object templates...", true);

		try {
			luaTemplatesInstance->runFile("scripts/object/main.lua");
		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		} catch (...) {
			error("unreported exception caught while loading templates");
		}

		info("done loading object templates", true);
	}

	void addTemplate(uint32 key, const String& fullName, LuaObject* templateData);

	String getTemplateFile(uint32 key) {
		SharedObjectTemplate* templateData = templateCRCMap.get(key);

		if (templateData == NULL) {
			String ascii = clientTemplateCRCMap.get(key);

			if (ascii.isEmpty())
				throw Exception("TemplateManager::getTemplateFile exception unknown template key 0x" + String::hexvalueOf((int)key));
			else
				return ascii;
		}

		return templateData->getFullTemplateString();
	}

	SharedObjectTemplate* getTemplate(uint32 key) {
		return templateCRCMap.get(key);
	}

	bool existsTemplate(uint32 key) {
		return templateCRCMap.containsKey(key);
	}

	// LUA
	void registerFunctions();
	void registerGlobals();
	static int includeFile(lua_State* L);
	static int crcString(lua_State* L);
	static int addTemplateCRC(lua_State* L);
	static int addClientTemplate(lua_State* L);

};


#endif /* TEMPLATEMANAGER_H_ */

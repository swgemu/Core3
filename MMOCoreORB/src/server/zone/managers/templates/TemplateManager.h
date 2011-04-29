/*
 * TemplateManager.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef TEMPLATEMANAGER_H_
#define TEMPLATEMANAGER_H_

#include "engine/engine.h"

#include "engine/util/ObjectFactory.h"
#include "server/zone/templates/SharedObjectTemplate.h"

#include "treLib/treArchive.hpp"
#include "tre3/TreeArchive.h"

#include "PlanetMapCategoryList.h"
#include "PlanetMapCategory.h"

class TemplateCRCMap;
class ClientTemplateCRCMap;
class PortalLayoutMap;
class FloorMeshMap;
class AppearanceMap;

class FloorMesh;
class PortalLayout;
class AppearanceTemplate;
class TreeDirectory;

class TemplateManager : public Singleton<TemplateManager>, public Logger {
	TemplateCRCMap* templateCRCMap;

	ObjectFactory<SharedObjectTemplate* (), uint32> templateFactory;
	ClientTemplateCRCMap* clientTemplateCRCMap;
	PortalLayoutMap* portalLayoutMap;
	FloorMeshMap* floorMeshMap;
	AppearanceMap* appearanceMap;

	PlanetMapCategoryList planetMapCategoryList;

	//treArchive* treeDirectory;
	TreeArchive* treeDirectory;

	ReadWriteLock appearanceMapLock;

	void loadTreArchive();
	void loadPlanetMapCategories();

public:
	static Lua* luaTemplatesInstance;

public:
	TemplateManager();
	~TemplateManager();

	void registerTemplateObjects();

	void loadLuaTemplates();

	void addTemplate(uint32 key, const String& fullName, LuaObject* templateData);

	String getTemplateFile(uint32 key);

	SharedObjectTemplate* getTemplate(uint32 key);

	IffStream* openIffFile(const String& fileName);

	TreeDirectory* getTreeDirectory(const String& path) {
		return treeDirectory->getDirectory(path);
	}

	FloorMesh* getFloorMesh(const String& fileName);
	PortalLayout* getPortalLayout(const String& fileName);
	AppearanceTemplate* getAppearanceTemplate(const String& fileName);
	AppearanceTemplate* instantiateAppearanceTemplate(IffStream* iffStream);

	bool existsTemplate(uint32 key);

	// LUA
	void registerFunctions();
	void registerGlobals();
	static int includeFile(lua_State* L);
	static int crcString(lua_State* L);
	static int addTemplateCRC(lua_State* L);
	static int addClientTemplate(lua_State* L);

	PlanetMapCategory* getPlanetMapCategoryByName(const String& name) {
		if (!planetMapCategoryList.contains(name))
			return NULL;

		return planetMapCategoryList.get(name);
	}

	PlanetMapCategory* getPlanetMapCategoryById(int idx) {
		for (int i = 0; i < planetMapCategoryList.size(); ++i) {
			Reference<PlanetMapCategory*> pmc = planetMapCategoryList.get(i);

			if (pmc->getIndex() == idx)
				return pmc;
		}

		return NULL;
	}

};


#endif /* TEMPLATEMANAGER_H_ */

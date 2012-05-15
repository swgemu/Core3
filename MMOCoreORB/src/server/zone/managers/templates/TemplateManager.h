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

#include "server/zone/templates/footprint/StructureFootprint.h"
#include "server/zone/templates/slots/SlotId.h"
#include "server/zone/templates/slots/SlotDescriptor.h"
#include "server/zone/templates/slots/ArrangementDescriptor.h"

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
class PaletteTemplate;

class TemplateManager : public Singleton<TemplateManager>, public Logger, public Object {
	TemplateCRCMap* templateCRCMap;

	ObjectFactory<SharedObjectTemplate* (), uint32> templateFactory;
	ClientTemplateCRCMap* clientTemplateCRCMap;
	PortalLayoutMap* portalLayoutMap;
	FloorMeshMap* floorMeshMap;
	AppearanceMap* appearanceMap;

	PlanetMapCategoryList planetMapCategoryList;

	VectorMap<String, Reference<StructureFootprint*> > structureFootprints;

	VectorMap<String, Reference<SlotId*> > slotDefinitions;
	VectorMap<String, Reference<SlotDescriptor*> > slotDescriptors;
	VectorMap<String, Reference<ArrangementDescriptor*> > arrangementDescriptors;

	//treArchive* treeDirectory;
	TreeArchive* treeDirectory;

	ReadWriteLock appearanceMapLock;

	void loadTreArchive();
	void loadSlotDefinitions();
	void loadPlanetMapCategories();
	void loadAssetCustomizationManager();

public:
	static Lua* luaTemplatesInstance;
	static AtomicInteger loadedTemplatesCount;

protected:
	//this is only to be used when loading client dervs
	LuaObject* getLuaObject(const String& iffTemplateName);

public:
	TemplateManager();
	~TemplateManager();

	void registerTemplateObjects();

	void loadLuaTemplates();

	/**
	 * Attempts to get the slot descriptor. If the slot descriptor isn't loaded, attempt to load it.
	 */
	Reference<SlotDescriptor*> getSlotDescriptor(const String& filename);
	Reference<ArrangementDescriptor*> getArrangementDescriptor(const String& filename);

	/**
	 * Attempts to load a Structure Footprint file from the TRE, and places it in the map.
	 * If the structure footprint already exists in the map, then it is simply returned.
	 * If the structure footprint cannot be found, then a warning is displayed, and NULL is returned
	 * @param filePath The TRE path to the Structure Footprint file from the root directory.
	 * @return Returns NULL if not found, else returns the StructureFootprint.
	 */
	StructureFootprint* loadStructureFootprint(const String& filePath);

	void addTemplate(uint32 key, const String& fullName, LuaObject* templateData);

	String getTemplateFile(uint32 key);

	SharedObjectTemplate* getTemplate(uint32 key);

	IffStream* openIffFile(const String& fileName);

	TreeDirectory* getTreeDirectory(const String& path) {
		return treeDirectory->getDirectory(path);
	}

	TreeArchive* getTreeArchive() {
		return treeDirectory;
	}

	ObjectInputStream* openTreFile(const String& filePath);

	inline bool containsTemplateType(uint32 type) {
		return templateFactory.containsObject(type);
	}

	FloorMesh* getFloorMesh(const String& fileName);
	PortalLayout* getPortalLayout(const String& fileName);
	AppearanceTemplate* getAppearanceTemplate(const String& fileName);
	AppearanceTemplate* instantiateAppearanceTemplate(IffStream* iffStream);
	PaletteTemplate* getPaletteTemplate(const String& fileName);

	bool existsTemplate(uint32 key);

	// LUA
	void registerFunctions();
	void registerGlobals();
	static int includeFile(lua_State* L);
	static int crcString(lua_State* L);
	static int addTemplateCRC(lua_State* L);
	static int addClientTemplate(lua_State* L);

	PlanetMapCategory* getPlanetMapCategoryByName(const String& name) {
		return planetMapCategoryList.get(name);
	}

	PlanetMapCategory* getPlanetMapCategoryByCrc(int crc) {
		return planetMapCategoryList.get(crc);
	}

	PlanetMapCategory* getPlanetMapCategoryById(int index) {
		HashTableIterator<int, Reference<PlanetMapCategory*> > iterator(planetMapCategoryList);

		while (iterator.hasNext()) {
			Reference<PlanetMapCategory*>& cat = iterator.getNextValue();

			if (cat->getIndex() == index)
				return cat.get();
		}

		return NULL;
	}

	/**
	 * This method should only be called after Templates have been loaded.
	 * It attempts to return the StructureFootprint that resides at the specified filepath, but requires
	 * that it has been loaded previously.
	 * @param filePath The TRE path of the desired Structure Footprint file.
	 * @return Returns the StructureFootprint object, or NULL if it does not exist.
	 */
	StructureFootprint* getStructureFootprint(const String& filePath) {
		return structureFootprints.get(filePath);
	}

	bool structureFootprintExists(const String& filePath) {
		return structureFootprints.contains(filePath);
	}

	SlotId* getSlotId(const String& slotName) {
		return slotDefinitions.get(slotName);
	}

	friend class server::zone::templates::SharedObjectTemplate;
};


#endif /* TEMPLATEMANAGER_H_ */

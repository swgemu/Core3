/*
 * ComponentMap.h
 *
 *  Created on: Apr 1, 2015
 *      Author: swgemu
 */

#ifndef COMPONENTMAP_H_
#define COMPONENTMAP_H_

#include "engine/log/Logger.h"
#include "engine/util/iffstream/IffStream.h"
#include "engine/util/Singleton.h"

#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"

#include "system/util/VectorMap.h"
#include "system/lang/String.h"

class ComponentMapEntry : public Object {
	uint32 id;
	String templateFilename;
	String hardpoint;

public:

	ComponentMapEntry() {
		id = 0;
		templateFilename = "";
		hardpoint = "";
	}

	ComponentMapEntry(const ComponentMapEntry& e) : Object() {
		id = e.id;
		templateFilename = e.templateFilename;
		hardpoint = e.hardpoint;
	}

	ComponentMapEntry& operator=(const ComponentMapEntry& e) {
		if (this == &e)
			return *this;

		id = e.id;
		templateFilename = e.templateFilename;
		hardpoint = e.hardpoint;

		return *this;
	}

	ComponentMapEntry(uint32 _id, String _templateFilename, String _hardpoint) {
		id = _id;
		templateFilename = _templateFilename;
		hardpoint = _hardpoint;
	}

	const String& getHardpoint() const {
		return hardpoint;
	}

	void setHardpoint(const String& hardpoint) {
		this->hardpoint = hardpoint;
	}

	uint32 getId() const {
		return id;
	}

	void setId(uint32 id) {
		this->id = id;
	}

	const String& getTemplateFilename() const {
		return templateFilename;
	}

	void setTemplateFilename(const String& templateFilename) {
		this->templateFilename = templateFilename;
	}
};

class ComponentMap : public VectorMap<uint32, ComponentMapEntry>, public Singleton<ComponentMap>, public Logger {
	VectorMap<uint32, VectorMap<uint32, Vector<uint32> > > visibleComponentMap;

public:
	ComponentMap() {
		Logger::setLoggingName("ComponentMap");

		setNullValue(ComponentMapEntry(0, "", ""));

		IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/crafting/component.iff");

		if (iffStream == NULL) {
			Logger::info("Could not open datatables/crafting/component.iff", true);
			return;
		}

		DataTableIff dtiff;
		dtiff.readObject(iffStream);

		uint32 id;
		String templateFilename, hardpoint;

		for (int i = 0; i < dtiff.getTotalRows(); ++i) {

			DataTableRow* row = dtiff.getRow(i);

			row->getCell(0)->getValue(id);
			row->getCell(1)->getValue(templateFilename);
			row->getCell(2)->getValue(hardpoint);

			put(templateFilename.hashCode(), ComponentMapEntry(id, templateFilename, hardpoint));
		}

		delete iffStream;

		loadVisibleComponentsFile();
	}

	ComponentMapEntry getFromID(uint32 id) {
		for (int i = 0; i < size(); i++) {
			ComponentMapEntry entry = elementAt(i).getValue();
			if (entry.getId() == id)
				return entry;
		}

		return ComponentMapEntry(0, "", "");
	}

	void loadVisibleComponentsFile() {
		Lua luaInstance;
		luaInstance.init();

		if (!luaInstance.runFile("scripts/managers/crafting/visible_components.lua"))
			return;

		// Read and create all the items in the config unless they
		// were already loaded from database.

		LuaObject componentList = luaInstance.getGlobalObject("visibleComponents");

		if (!componentList.isValidTable())
			return;

		int size = componentList.getTableSize();
		int count = 0;
		uint32 muzzleTitle = STRING_HASHCODE("muzzle"), scopeTitle = STRING_HASHCODE("scope"), stockTitle = STRING_HASHCODE("stock");

		lua_State* L = componentList.getLuaState();

		for (int i = 0; i < size; ++i) {

			lua_rawgeti(L, -1, i + 1);
			LuaObject luaObject(L);

			uint32 tempCRC = luaObject.getStringField("template").hashCode();

			LuaObject muzzles = luaObject.getObjectField("muzzle");
			Vector<uint32> muzzleVector;

			for (int j = 1; j <= muzzles.getTableSize(); ++j) {
				uint32 muzzle = muzzles.getStringAt(j).hashCode();
				muzzleVector.add(muzzle);
			}

			muzzles.pop();

			LuaObject scopes = luaObject.getObjectField("scope");
			Vector<uint32> scopeVector;

			for (int j = 1; j <= scopes.getTableSize(); ++j) {
				uint32 scope = scopes.getStringAt(j).hashCode();
				scopeVector.add(scope);
			}

			scopes.pop();

			LuaObject stocks = luaObject.getObjectField("stock");
			Vector<uint32> stockVector;

			for (int j = 1; j <= stocks.getTableSize(); ++j) {
				uint32 stock = stocks.getStringAt(j).hashCode();
				stockVector.add(stock);
			}

			stocks.pop();

			luaObject.pop();

			if (tempCRC == 0)
				continue;

			VectorMap<uint32, Vector<uint32> > visibleMap;

			visibleMap.put(muzzleTitle, muzzleVector);
			visibleMap.put(scopeTitle, scopeVector);
			visibleMap.put(stockTitle, stockVector);

			visibleComponentMap.put(tempCRC, visibleMap);

			count++;
		}

		componentList.pop();

		Logger::info("Loaded visible components from scripts for " + String::valueOf(count) + " weapons.", true);
	}

	Vector<uint32> getVisibleCRC(uint32 tempCRC, uint32 slotCRC) {
		return visibleComponentMap.get(tempCRC).get(slotCRC);
	}
};

#endif /* COMPONENTMAP_H_ */

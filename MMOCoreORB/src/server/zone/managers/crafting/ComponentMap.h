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

#include "templates/manager/TemplateManager.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"

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
	VectorMap<uint32, VectorMap<uint32, VectorMap<uint32, uint32> > > visibleComponentMap;

public:
	ComponentMap() {
		Logger::setLoggingName("ComponentMap");

		setNullValue(ComponentMapEntry(0, "", ""));

		IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/crafting/component.iff");

		if (iffStream == nullptr) {
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

		uint32 barrelCRC = STRING_HASHCODE("barrel"), scopeCRC = STRING_HASHCODE("scope"), stockCRC = STRING_HASHCODE("stock");

		for (int i = 1; i <= componentList.getTableSize(); ++i) {
			LuaObject luaObject = componentList.getObjectAt(i);

			if (!luaObject.isValidTable()) {
				continue;
			}

			uint32 weaponCRC = luaObject.getStringField("template").hashCode();

			VectorMap<uint32, uint32> barrelVector, scopeVector, stockVector;

			LuaObject muzzles = luaObject.getObjectField("barrel");

			for (int j = 1; j <= muzzles.getTableSize(); ++j) {
				LuaObject row = luaObject.getObjectAt(j);

				if (row.isValidTable() && row.getTableSize() == 2) {
					uint32 shotCRC = row.getStringAt(1).hashCode();
					uint32 apprCRC = row.getStringAt(2).hashCode();
					barrelVector.put(shotCRC, apprCRC);
				}

				row.pop();
			}

			muzzles.pop();

			LuaObject scopes = luaObject.getObjectField("scope");

			for (int j = 1; j <= scopes.getTableSize(); ++j) {
				LuaObject row = luaObject.getObjectAt(j);

				if (row.isValidTable() && row.getTableSize() == 2) {
					uint32 shotCRC = row.getStringAt(1).hashCode();
					uint32 apprCRC = row.getStringAt(2).hashCode();
					scopeVector.put(shotCRC, apprCRC);
				}

				row.pop();
			}

			scopes.pop();

			LuaObject stocks = luaObject.getObjectField("stock");

			for (int j = 1; j <= stocks.getTableSize(); ++j) {
				LuaObject row = luaObject.getObjectAt(j);

				if (row.isValidTable() && row.getTableSize() == 2) {
					uint32 shotCRC = row.getStringAt(1).hashCode();
					uint32 apprCRC = row.getStringAt(2).hashCode();
					stockVector.put(shotCRC, apprCRC);
				}

				row.pop();
			}

			stocks.pop();

			luaObject.pop();

			VectorMap<uint32, VectorMap<uint32, uint32> > visibleMap;

			visibleMap.put(barrelCRC, barrelVector);
			visibleMap.put(scopeCRC, scopeVector);
			visibleMap.put(stockCRC, stockVector);

			visibleComponentMap.put(weaponCRC, visibleMap);
		}

		componentList.pop();

		Logger::info("Loaded visible components from scripts for " + String::valueOf(visibleComponentMap.size()) + " weapons.", true);
	}

	VectorMap<uint32, uint32> getVisibleCRC(uint32 tempCRC, uint32 slotCRC) {
		return visibleComponentMap.get(tempCRC).get(slotCRC);
	}
};

#endif /* COMPONENTMAP_H_ */

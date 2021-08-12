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

		LuaObject weapons = luaInstance.getGlobalObject("weapons");

		if (!weapons.isValidTable()) {
			return;
		}

		uint32 barrelCrc = STRING_HASHCODE("barrel"), scopeCrc = STRING_HASHCODE("scope"), stockCrc = STRING_HASHCODE("stock");

		for (int i = 1; i <= weapons.getTableSize(); ++i) {
			LuaObject weaponRow = weapons.getObjectAt(i);

			if (weaponRow.isValidTable() && weaponRow.getTableSize() == 4) {
				String weapon = weaponRow.getStringAt(1);
				String barrel = weaponRow.getStringAt(2);
				String scope = weaponRow.getStringAt(3);
				String stock = weaponRow.getStringAt(4);

				VectorMap<uint32, uint32> barrelMap, scopeMap, stockMap;

				if (!barrel.isEmpty()) {
					LuaObject barrelScript = luaInstance.getGlobalObject(barrel);

					for (int ii = 1; ii <= barrelScript.getTableSize(); ++ii) {
						LuaObject barrelRow = barrelScript.getObjectAt(ii);

						if (barrelRow.isValidTable() && barrelRow.getTableSize() == 2) {
							uint32 compCrc = barrelRow.getStringAt(1).hashCode();
							uint32 compApp = barrelRow.getStringAt(2).hashCode();

							barrelMap.put(compCrc, compApp);
						}

						barrelRow.pop();
					}

					barrelScript.pop();
				}

				if (!scope.isEmpty()) {
					LuaObject scopeScript = luaInstance.getGlobalObject(scope);

					for (int ii = 1; ii <= scopeScript.getTableSize(); ++ii) {
						LuaObject scopeRow = scopeScript.getObjectAt(ii);

						if (scopeRow.isValidTable() && scopeRow.getTableSize() == 2) {
							uint32 compCrc = scopeRow.getStringAt(1).hashCode();
							uint32 compApp = scopeRow.getStringAt(2).hashCode();

							scopeMap.put(compCrc, compApp);
						}

						scopeRow.pop();
					}

					scopeScript.pop();
				}

				if (!stock.isEmpty()) {
					LuaObject stockScript = luaInstance.getGlobalObject("stock");

					for (int ii = 1; ii <= stockScript.getTableSize(); ++ii) {
						LuaObject stockRow = stockScript.getObjectAt(ii);

						if (stockRow.isValidTable() && stockRow.getTableSize() == 2) {
							uint32 compCrc = stockRow.getStringAt(1).hashCode();
							uint32 compApp = stockRow.getStringAt(2).hashCode();

							if (stock.hashCode() == compApp) {
								stockMap.put(compCrc, compApp);
							}
						}

						stockRow.pop();
					}

					stockScript.pop();
				}

				VectorMap<uint32, VectorMap<uint32, uint32> > weaponEntryMap;

				weaponEntryMap.put(barrelCrc, barrelMap);
				weaponEntryMap.put(scopeCrc, scopeMap);
				weaponEntryMap.put(stockCrc, stockMap);

				visibleComponentMap.put(weapon.hashCode(), weaponEntryMap);
			}

			weaponRow.pop();
		}

		weapons.pop();

		info("Loaded visible components from scripts for " + String::valueOf(visibleComponentMap.size()) + " weapons.", true);
	}

	const VectorMap<uint32, uint32>& getVisibleCRC(uint32 tempCRC, uint32 slotCRC) const {
		return visibleComponentMap.get(tempCRC).get(slotCRC);
	}
};

#endif /* COMPONENTMAP_H_ */

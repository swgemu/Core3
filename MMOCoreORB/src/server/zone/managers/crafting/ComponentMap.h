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
public:
	ComponentMap() {
		setLoggingName("ComponentMap");

		setNullValue(ComponentMapEntry(0, "", ""));

		IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/crafting/component.iff");

		if (iffStream == NULL) {
			info("Could not open datatables/crafting/component.iff", true);
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
	}

	ComponentMapEntry getFromID(uint32 id) {
		for (int i = 0; i < size(); i++) {
			ComponentMapEntry entry = elementAt(i).getValue();
			if (entry.getId() == id)
				return entry;
		}

		return ComponentMapEntry(0, "", "");
	}
};

#endif /* COMPONENTMAP_H_ */

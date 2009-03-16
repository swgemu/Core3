/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef MANUFACTURESCHEMATICIMPLEMENTATION_H_
#define MANUFACTURESCHEMATICIMPLEMENTATION_H_

#include "engine/engine.h"

#include "ManufactureSchematic.h"
#include "../draftschematic/DraftSchematic.h"
#include "../draftschematic/DraftSchematicIngredient.h"
#include "../tangible/crafting/component/Component.h"
#include "../tangible/crafting/CraftingTool.h"
#include "../tangible/resource/ResourceContainer.h"
#include "../player/Player.h"

#include "../../objects.h"

#include "ManufactureSchematicIngredientMap.h"


class ManufactureSchematicImplementation : public ManufactureSchematicServant {

private:

	ManufactureSchematicIngredientMap ingredientMap;

	int complexity;
	int dataSize;
	int manufacturingLimit;

public:

	ManufactureSchematicImplementation(uint64 oid, String n, String stfFile, String stfName, uint32 crc);
	ManufactureSchematicImplementation(uint64 oid, DraftSchematic* draftSchematic, CraftingTool* craftingTool);

	~ManufactureSchematicImplementation();

	void init();
	void setIngredients(DraftSchematic* draftSchematic, CraftingTool* craftingTool);

	void sendTo(Player* player, bool doClose = true);
	void sendDestroyTo(Player* player);

	void parseItemAttributes();
	void generateAttributes(SceneObject* obj);
	void addAttributes(AttributeListMessage* alm);

	void parseResources(String resources);
	void parseComponents(String components);

	int getComplexity() {
		return complexity;
	}

	int getManufacturingLimit() {
		return manufacturingLimit;
	}

	int getDataSize() {
		return dataSize;
	}

	TangibleObject* getTangibleObject() {
		return (TangibleObject*) getObject(0);
	}

	void setManufacturingLimit(int value) {
		manufacturingLimit = value;
		String name = "manufacturinglimit";
		itemAttributes->setIntAttribute(name, manufacturingLimit);
	}

	void setComplexity(int value) {
		complexity = value;
		String name = "complexity";
		itemAttributes->setIntAttribute(name, complexity);
	}

	void setDataSize(int value) {
		dataSize = value;
		String name = "datasize";
		itemAttributes->setIntAttribute(name, dataSize);
	}

	inline void setTangibleObject(TangibleObject* inTano) {
		while(getContainerObjectsSize() > 0)
			removeObject(0);

		addObject(inTano);
	}
};

#endif /*MANUFACTURESCHEMATICIMPLEMENTATION_H_*/

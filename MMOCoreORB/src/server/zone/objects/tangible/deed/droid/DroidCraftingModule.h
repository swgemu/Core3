/*
Copyright (C) 2013 <SWGEmu>

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

#ifndef DROIDCRAFTINGMODULE_H_
#define DROIDCRAFTINGMODULE_H_

#include "DroidModule.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include <iostream>

namespace server {
	namespace zone {
		namespace objects {
			namespace tangible {
				namespace deed {
					namespace droid {


class DroidCraftingModule : public DroidModule {

	// craftingType is a base-10 mask of all installed crafting modules
	int craftingType;

public:

	// Each module type has their min/max experimental value set to a different number in the crafting lua so we can differentiate them here
	// If multiple modules are present, the values are added together.   This makes it work like a mask.
	static const int WEAPON_DROID_GENERIC = 1;
	static const int FOOD_CHEMICAL = 10;
	static const int CLOTHING_ARMOR = 100;
	static const int STRUCTURE_FURNITURE = 1000;
	static const int SHIP = 10000;

public:
	DroidCraftingModule();
	DroidCraftingModule(CraftingValues* values);
	DroidCraftingModule(const DroidCraftingModule& module);
	~DroidCraftingModule();

	void fillAttributeList(AttributeListMessage* alm, CreatureObject* object);

	bool isWeaponDroidGeneric();
	bool isFoodChemical();
	bool isClothingArmor();
	bool isStructureFurniture();
	bool isShip();

	bool toBinaryStream(ObjectOutputStream* stream) {
		std::cout << "DroidCraftingModule::toBinaryStream()\n";

		DroidModule::toBinaryStream( stream );
		stream->writeInt(craftingType);
		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		std::cout << "DroidCraftingModule::parseFromBinaryStream()\n";

		DroidModule::parseFromBinaryStream( stream );
		craftingType = stream->readInt();
		return true;
	}

};

} //droid
} //deed
} //tangible
} //objects
} //zone
} //server

using namespace server::zone::objects::tangible::deed::droid;

#endif /*DROIDCRAFTINGMODULE_H_*/

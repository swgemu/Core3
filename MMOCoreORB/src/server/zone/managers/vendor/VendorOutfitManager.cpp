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

#include "VendorOutfitManager.h"

void VendorOutfitManager::initialize() {

	setLoggingName("VendorOutfitManager");
	outfits.setNoDuplicateInsertPlan();
	outfits.setNullValue(NULL);

	loadLuaOutfits();

}

void VendorOutfitManager::loadLuaOutfits() {
	info("Loading Outfits...");
	String outfitName;
	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/mobile/wearables/outfits.lua");

	LuaObject Luaoutfits = lua->getGlobalObject("Outfits");

	for (int i = 1; i < Luaoutfits.getTableSize() + 1; ++i) {
		lua_State* L = Luaoutfits.getLuaState();
		lua_rawgeti(L, -1, i);
		LuaObject outfit(L);

		outfitName = outfit.getStringField("outfitName");

		//info("Loaded " + outfit.getStringField("outfitName"), true); // OutfitName
		LuaObject clothing = outfit.getObjectField("clothing"); // Clothing Object

		Reference<Outfit*> oFit = new Outfit();

		for (int j = 1; j <= clothing.getTableSize(); ++j) {
			//info("Added " + clothing.getStringAt(j), true);
			oFit->addClothingCRC(clothing.getStringAt(j).hashCode());
		}

		outfits.put(outfitName, oFit);

		clothing.pop();

		outfit.pop();
	}

	info("Loaded " + String::valueOf(outfits.size()) + " unique outfits", true);

	Luaoutfits.pop();
}


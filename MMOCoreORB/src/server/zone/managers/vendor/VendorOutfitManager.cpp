/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
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

	delete lua;
	lua = NULL;
}


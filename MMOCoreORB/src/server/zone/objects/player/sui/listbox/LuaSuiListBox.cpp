
#include "LuaSuiListBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

const char LuaSuiListBox::className[] = "LuaSuiListBox";

Luna<LuaSuiListBox>::RegType LuaSuiListBox::Register[] = {
		{ "_setObject", &LuaSuiListBox::_setObject },
		{ "getMenuSize", &LuaSuiListBox::getMenuSize },
		{ "getMenuItemName", &LuaSuiListBox::getMenuItemName },
		{ "getMenuObjectID", &LuaSuiListBox::getMenuObjectID },
		{ "getUsingObject", &LuaSuiBox::getUsingObject },
		{ 0, 0 }
};

LuaSuiListBox::LuaSuiListBox(lua_State *L) : LuaSuiBox(L) {
	realObject = static_cast<SuiListBox*>(lua_touserdata(L, 1));
}

LuaSuiListBox::~LuaSuiListBox(){
}

int LuaSuiListBox::_setObject(lua_State* L) {
	realObject = static_cast<SuiListBox*>(lua_touserdata(L, -1));

	return 0;
}

int LuaSuiListBox::getMenuSize(lua_State* L) {
	int size = realObject->getMenuSize();

	lua_pushinteger(L, size);

	return 1;
}

int LuaSuiListBox::getMenuItemName(lua_State* L) {
	int index = lua_tointeger(L, -1);
	String name = realObject->getMenuItemName(index);

	lua_pushstring(L, name.toCharArray());

	return 1;
}

int LuaSuiListBox::getMenuObjectID(lua_State* L) {
	int index = lua_tointeger(L, -1);
	uint64 oid = realObject->getMenuObjectID(index);

	lua_pushinteger(L, oid);

	return 1;
}

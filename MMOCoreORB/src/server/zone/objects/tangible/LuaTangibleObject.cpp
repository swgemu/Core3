/*
 * LuaTangibleObject.cpp
 *
 *  Created on: 24/01/2012
 *      Author: xyborn
 */

#include "LuaTangibleObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "templates/params/PaletteColorCustomizationVariable.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "templates/appearance/PaletteTemplate.h"
#include "server/zone/objects/player/FactionStatus.h"

const char LuaTangibleObject::className[] = "LuaTangibleObject";

Luna<LuaTangibleObject>::RegType LuaTangibleObject::Register[] = {
		{ "_setObject", &LuaTangibleObject::_setObject },
		{ "_getObject", &LuaSceneObject::_getObject },
		{ "setOptionsBitmask", &LuaTangibleObject::setOptionsBitmask },
		{ "setPvpStatusBitmask", &LuaTangibleObject::setPvpStatusBitmask },
		{ "setPvpStatusBit", &LuaTangibleObject::setPvpStatusBit },
		{ "getPvpStatusBitmask", &LuaTangibleObject::getPvpStatusBitmask },
		{ "isChangingFactionStatus", &LuaTangibleObject::isChangingFactionStatus },
		{ "setFutureFactionStatus", &LuaTangibleObject::setFutureFactionStatus },
		{ "isOnLeave", &LuaTangibleObject::isOnLeave },
		{ "isOvert", &LuaTangibleObject::isOvert },
		{ "isCovert", &LuaTangibleObject::isCovert },
		{ "setCustomizationVariable", &LuaTangibleObject::setCustomizationVariable },
		{ "getPaletteColorCount", &LuaTangibleObject::getPaletteColorCount },
		{ "setConditionDamage", &LuaTangibleObject::setConditionDamage },
		{ "setMaxCondition", &LuaTangibleObject::setMaxCondition },
		{ "setFaction", &LuaTangibleObject::setFaction },
		{ "getFaction", &LuaTangibleObject::getFaction },
		{ "setFactionStatus", &LuaTangibleObject::setFactionStatus },
		{ "isImperial", &LuaTangibleObject::isImperial },
		{ "isRebel", &LuaTangibleObject::isRebel },
		{ "isNeutral", &LuaTangibleObject::isNeutral },
		{ "hasActiveArea", &LuaTangibleObject::hasActiveArea},
		{ "isInvisible", &LuaTangibleObject::isInvisible },
		{ "getLuaStringData", &LuaTangibleObject::getLuaStringData },
		{ "setLuaStringData", &LuaTangibleObject::setLuaStringData },
		{ "deleteLuaStringData", &LuaTangibleObject::deleteLuaStringData },
		{ "setOptionBit", &LuaTangibleObject::setOptionBit},
		{ "clearOptionBit", &LuaTangibleObject::clearOptionBit},
		{ "hasOptionBit", &LuaTangibleObject::hasOptionBit},
		{ "getCraftersName", &LuaTangibleObject::getCraftersName},
		{ "getJunkDealerNeeded", &LuaTangibleObject::getJunkDealerNeeded},
		{ "getJunkValue", &LuaTangibleObject::getJunkValue},
		{ "isBroken", &LuaTangibleObject::isBroken},
		{ "isSliced", &LuaTangibleObject::isSliced},
		{ "isNoTrade", &LuaTangibleObject::isNoTrade},
		{ 0, 0 }
};

LuaTangibleObject::LuaTangibleObject(lua_State *L) : LuaSceneObject(L) {
#ifdef DYNAMIC_CAST_LUAOBJECTS
	realObject = dynamic_cast<TangibleObject*>(_getRealSceneObject());

	assert(!_getRealSceneObject() || realObject != NULL);
#else
	realObject = static_cast<TangibleObject*>(lua_touserdata(L, 1));
#endif
}

LuaTangibleObject::~LuaTangibleObject(){
}

int LuaTangibleObject::_setObject(lua_State* L) {
	LuaSceneObject::_setObject(L);

#ifdef DYNAMIC_CAST_LUAOBJECTS
	auto obj = dynamic_cast<TangibleObject*>(_getRealSceneObject());

	if (realObject != obj)
		realObject = obj;

	assert(!_getRealSceneObject() || realObject != NULL);
#else
	auto obj = static_cast<TangibleObject*>(lua_touserdata(L, -1));

	if (realObject != obj)
		realObject = obj;
#endif

	return 0;
}

int LuaTangibleObject::setCustomizationVariable(lua_State* L) {
	String type = lua_tostring(L, -2);
	int value = lua_tonumber(L, -1);

	Locker locker(realObject);

	realObject->setCustomizationVariable(type, value, true);

	return 0;
}

int LuaTangibleObject::getPaletteColorCount(lua_State* L) {
	String variableName = lua_tostring(L, -1);

	String appearanceFilename = realObject->getObjectTemplate()->getAppearanceFilename();
	VectorMap<String, Reference<CustomizationVariable*> > variables;
	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);

	int colors = 0;

	for (int i = 0; i< variables.size(); ++i) {
		String varkey = variables.elementAt(i).getKey();

		if (varkey.contains(variableName)) {
			CustomizationVariable* customizationVariable = variables.get(varkey).get();

			if (customizationVariable == NULL)
				continue;

			PaletteColorCustomizationVariable* palette = dynamic_cast<PaletteColorCustomizationVariable*>(customizationVariable);

			if (palette != NULL) {
				String paletteFileName = palette->getPaletteFileName();
				PaletteTemplate* paletteTemplate = TemplateManager::instance()->getPaletteTemplate(paletteFileName);

				if (paletteTemplate == NULL)
					continue;

				colors = paletteTemplate->getColorCount();
				break;
			}
		}
	}

	lua_pushinteger(L, colors);

	return 1;
}

int LuaTangibleObject::setOptionsBitmask(lua_State* L) {
	uint32 bitmask = lua_tointeger(L, -1);

	realObject->setOptionsBitmask(bitmask, true);

	return 0;
}

int LuaTangibleObject::setPvpStatusBitmask(lua_State* L) {
	uint32 bitmask = lua_tointeger(L, -1);

	realObject->setPvpStatusBitmask(bitmask, true);

	return 0;
}

int LuaTangibleObject::setPvpStatusBit(lua_State* L) {
	uint32 bit = lua_tointeger(L, -1);

	realObject->setPvpStatusBit(bit, true);

	return 0;
}

int LuaTangibleObject::getPvpStatusBitmask(lua_State* L) {
	uint32 bitmask = realObject->getPvpStatusBitmask();

	lua_pushinteger(L, bitmask);

	return 1;
}

int LuaTangibleObject::isChangingFactionStatus(lua_State* L) {
	lua_pushboolean(L, realObject->getFutureFactionStatus() >= 0);

	return 1;
}

int LuaTangibleObject::setFutureFactionStatus(lua_State* L) {
	float status = lua_tonumber(L, -1);

	realObject->setFutureFactionStatus(status);

	return 0;
}

int LuaTangibleObject::isOnLeave(lua_State* L) {
	lua_pushboolean(L, realObject->getFactionStatus() == FactionStatus::ONLEAVE);

	return 1;
}

int LuaTangibleObject::isOvert(lua_State* L) {
	lua_pushboolean(L, realObject->getFactionStatus() == FactionStatus::OVERT);

	return 1;
}

int LuaTangibleObject::isCovert(lua_State* L) {
	lua_pushboolean(L, realObject->getFactionStatus() == FactionStatus::COVERT);

	return 1;
}

int LuaTangibleObject::setConditionDamage(lua_State* L) {
	float damage = lua_tonumber(L, -1);

	Locker locker(realObject);

	realObject->setConditionDamage(damage, true);

	return 0;
}

int LuaTangibleObject::setMaxCondition(lua_State* L) {
	float damage = lua_tonumber(L, -1);

	realObject->setMaxCondition(damage, true);

	return 0;
}

int LuaTangibleObject::setFaction(lua_State* L){
	uint32 faction = lua_tointeger(L, -1);

	realObject->setFaction(faction);

	return 0;
}

int LuaTangibleObject::getFaction(lua_State* L){
	uint32 faction = realObject->getFaction();

	lua_pushinteger(L, faction);

	return 1;
}

int LuaTangibleObject::isImperial(lua_State* L){
	lua_pushboolean(L, realObject->isImperial());

	return 1;
}

int LuaTangibleObject::isRebel(lua_State* L){
	lua_pushboolean(L, realObject->isRebel());

	return 1;
}

int LuaTangibleObject::isNeutral(lua_State* L){
	lua_pushboolean(L, realObject->isNeutral());

	return 1;
}

int LuaTangibleObject::hasActiveArea(lua_State* L) {
	uint64 objectid = lua_tointeger(L, -1);

	bool res = realObject->hasActiveArea(objectid);

	lua_pushboolean(L, res);

	return 1;
}

int LuaTangibleObject::isInvisible(lua_State* L) {
	bool retVal = realObject->isInvisible();
	lua_pushboolean(L, retVal);

	return 1;
}

int LuaTangibleObject::setLuaStringData(lua_State *L) {
	Locker locker(realObject);

	String key = lua_tostring(L, -2);
	String data = lua_tostring(L, -1);

	realObject->setLuaStringData(key, data);
	return 0;
}

int LuaTangibleObject::deleteLuaStringData(lua_State* L) {
	Locker locker(realObject);

	String key = lua_tostring(L, -1);

	realObject->deleteLuaStringData(key);

	return 0;
}

int LuaTangibleObject::getLuaStringData(lua_State *L) {
	String key = lua_tostring(L, -1);
	String data = realObject->getLuaStringData(key);

	lua_pushstring(L, data.toCharArray());

	return 1;
}

int LuaTangibleObject::setOptionBit(lua_State* L) {
	uint32 bit = lua_tointeger(L, -1);

	Locker locker(realObject);

	realObject->setOptionBit(bit, true);

	return 0;
}

int LuaTangibleObject::clearOptionBit(lua_State* L) {
	uint32 bit = lua_tointeger(L, -1);

	Locker locker(realObject);

	realObject->clearOptionBit(bit, true);

	return 0;
}

int LuaTangibleObject::hasOptionBit(lua_State* L) {
	uint32 bit = lua_tointeger(L, -1);

	bool retVal = realObject->getOptionsBitmask() & bit;
	lua_pushboolean(L, retVal);

	return 1;
}

int LuaTangibleObject::getCraftersName(lua_State* L) {
	lua_pushstring(L, realObject->getCraftersName().toCharArray());

	return 1;
}

int LuaTangibleObject::setFactionStatus(lua_State* L) {
	int status = lua_tointeger(L, -1);

	realObject->setFactionStatus(status);

	return 0;
}

int LuaTangibleObject::getJunkDealerNeeded(lua_State* L){
	int dealer = realObject->getJunkDealerNeeded();

	lua_pushinteger(L, dealer);

	return 1;
}

int LuaTangibleObject::getJunkValue(lua_State* L){
	int value = realObject->getJunkValue();

	lua_pushinteger(L, value);

	return 1;
}

int LuaTangibleObject::isBroken(lua_State* L){
	bool broken = realObject->isBroken();

	lua_pushboolean(L, broken);

	return 1;
}

int LuaTangibleObject::isSliced(lua_State* L){
	bool sliced = realObject->isSliced();

	lua_pushboolean(L, sliced);

	return 1;
}

int LuaTangibleObject::isNoTrade(lua_State* L){
	bool noTrade = realObject->isNoTrade();

	lua_pushboolean(L, noTrade);

	return 1;
}

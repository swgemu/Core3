/*
 * LuaCreatureObject.cpp
 *
 *  Created on: 31/08/2009
 *      Author: victor
 */

#include "LuaCreatureObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/player/sessions/ConversationSession.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"

const char LuaCreatureObject::className[] = "LuaCreatureObject";

Luna<LuaCreatureObject>::RegType LuaCreatureObject::Register[] = {
		{ "_setObject", &LuaCreatureObject::_setObject },
		{ "_getObject", &LuaSceneObject::_getObject },
		{ "getBankCredits", &LuaCreatureObject::getBankCredits },
		{ "setBankCredits", &LuaCreatureObject::setBankCredits },
		{ "sendSystemMessage", &LuaCreatureObject::sendSystemMessage },
		{ "sendSystemMessageWithDI", &LuaCreatureObject::sendSystemMessageWithDI },
		{ "sendSystemMessageWithTO", &LuaCreatureObject::sendSystemMessageWithTO },
		{ "sendGroupMessage", &LuaCreatureObject::sendGroupMessage },
		{ "playMusicMessage", &LuaCreatureObject::playMusicMessage },
		{ "sendNewbieTutorialRequest", &LuaCreatureObject::sendNewbieTutorialRequest },
		{ "hasScreenPlayState", &LuaCreatureObject::hasScreenPlayState },
		{ "setScreenPlayState", &LuaCreatureObject::setScreenPlayState },
		{ "getScreenPlayState", &LuaCreatureObject::getScreenPlayState },
		{ "playEffect", &LuaSceneObject::playEffect },
		{ "sendNewbieTutorialEnableHudElement", &LuaCreatureObject::sendNewbieTutorialEnableHudElement },
		{ "getInCellNumber", &LuaCreatureObject::getInCellNumber },
		{ "getBuildingParentID", &LuaCreatureObject::getBuildingParentID },
		{ "sendOpenHolocronToPageMessage", &LuaCreatureObject::sendOpenHolocronToPageMessage },
		{ "inflictDamage", &LuaCreatureObject::inflictDamage },
		{ "setHAM", &LuaCreatureObject::setHAM },
		{ "setBaseHAM", &LuaCreatureObject::setBaseHAM },
		{ "setMaxHAM", &LuaCreatureObject::setMaxHAM },
		{ "getHAM", &LuaCreatureObject::getHAM },
		{ "getMaxHAM", &LuaCreatureObject::getMaxHAM },
		{ "getTargetID", &LuaCreatureObject::getTargetID },
		{ "clearCombatState", &LuaCreatureObject::clearCombatState },
		{ "getParent", &LuaSceneObject::getParent },
		{ "getZoneName", &LuaSceneObject::getZoneName },
		{ "getObjectID", &LuaSceneObject::getObjectID },
		{ "getPositionX", &LuaSceneObject::getPositionX },
		{ "getPositionY", &LuaSceneObject::getPositionY },
		{ "getPositionZ", &LuaSceneObject::getPositionZ },
		{ "getDirectionAngle", &LuaSceneObject::getDirectionAngle },
		{ "getWorldPositionX", &LuaSceneObject::getWorldPositionX },
		{ "getWorldPositionY", &LuaSceneObject::getWorldPositionY },
		{ "getWorldPositionZ", &LuaSceneObject::getWorldPositionZ },
		{ "getParentID", &LuaSceneObject::getParentID },
		{ "isInRangeWithObject", &LuaSceneObject::isInRangeWithObject },
		{ "getDistanceTo", &LuaSceneObject::getDistanceTo },
		{ "getServerObjectCRC", &LuaSceneObject::getServerObjectCRC },
		{ "setState", &LuaCreatureObject::setState},
		{ "setLootRights", &LuaCreatureObject::setLootRights},
		{ "getPosture", &LuaCreatureObject::getPosture},
		{ "setPosture", &LuaCreatureObject::setPosture},
		{ "setMoodString", &LuaCreatureObject::setMoodString},
		{ "hasSkill", &LuaCreatureObject::hasSkill},
		{ "removeSkill", &LuaCreatureObject::removeSkill},
		{ "getConversationSession", &LuaCreatureObject::getConversationSession},
		{ "doAnimation", &LuaCreatureObject::doAnimation},
		{ "engageCombat", &LuaCreatureObject::engageCombat},
		{ "getPlayerObject", &LuaCreatureObject::getPlayerObject},
		{ "setCustomObjectName", &LuaSceneObject::setCustomObjectName},
		{ "getFaction", &LuaCreatureObject::getFaction},
		{ "setFaction", &LuaCreatureObject::setFaction},
		{ "isRebel", &LuaCreatureObject::isRebel},
		{ "isImperial", &LuaCreatureObject::isImperial},
		{ "isNeutral", &LuaCreatureObject::isNeutral},
		{ "teleport", &LuaSceneObject::teleport},
		{ "getFirstName", &LuaCreatureObject::getFirstName},
		{ "isAiAgent", &LuaCreatureObject::isAiAgent},
		{ "setFactionRank", &LuaCreatureObject::setFactionRank},
		{ "getFactionRank", &LuaCreatureObject::getFactionRank},
		{ "getCashCredits", &LuaCreatureObject::getCashCredits},
		{ "subtractCashCredits", &LuaCreatureObject::subtractCashCredits},
		{ "addCashCredits", &LuaCreatureObject::addCashCredits},
		{ "removeScreenPlayState", &LuaCreatureObject::removeScreenPlayState},
		{ "isGrouped", &LuaCreatureObject::isGrouped},
		{ "isGroupedWith", &LuaCreatureObject::isGroupedWith},
		{ "getGroupSize", &LuaCreatureObject::getGroupSize},
		{ "getGroupMember", &LuaCreatureObject::getGroupMember},
		{ "setOptionsBitmask", &LuaCreatureObject::setOptionsBitmask},
		{ "setPvpStatusBitmask", &LuaCreatureObject::setPvpStatusBitmask},
		{ "addDotState", &LuaCreatureObject::addDotState},
		{ "getSlottedObject", &LuaSceneObject::getSlottedObject},
		{ "checkCooldownRecovery", &LuaCreatureObject::checkCooldownRecovery},
		{ "addCooldown", &LuaCreatureObject::addCooldown},
		{ "isDead", &LuaCreatureObject::isDead},
		{ "isIncapacitated", &LuaCreatureObject::isIncapacitated },
		{ "getLevel", &LuaCreatureObject::getLevel},
		{ "getQueueSize", &LuaCreatureObject::getQueueSize },
		{ "isDancing", &LuaCreatureObject::isDancing},
		{ "isPlayingMusic", &LuaCreatureObject::isPlayingMusic},
		{ "getPerformanceName", &LuaCreatureObject::getPerformanceName},
		{ "getWalkSpeed", &LuaCreatureObject::getWalkSpeed },
		{ "isAttackableBy", &LuaCreatureObject::isAttackableBy },
		{ "getSpecies", &LuaCreatureObject::getSpecies },
		{ "isDroidPet", &LuaCreatureObject::isDroidPet },
		{ "isCombatDroidPet", &LuaCreatureObject::isCombatDroidPet },
		{ "awardExperience", &LuaCreatureObject::awardExperience },
		{ "getOwner", &LuaCreatureObject::getOwner },
		{ "getCurrentSpeed", &LuaCreatureObject::getCurrentSpeed },
		{ 0, 0 }
};

LuaCreatureObject::LuaCreatureObject(lua_State *L) : LuaSceneObject(L) {
#ifdef DYNAMIC_CAST_LUAOBJECTS
	realObject = dynamic_cast<CreatureObject*>(_getRealSceneObject());

	assert(!_getRealSceneObject() || realObject != NULL);
#else
	realObject = static_cast<CreatureObject*>(lua_touserdata(L, 1));
#endif
}

LuaCreatureObject::~LuaCreatureObject(){
}

int LuaCreatureObject::_setObject(lua_State* L) {
	LuaSceneObject::_setObject(L);

#ifdef DYNAMIC_CAST_LUAOBJECTS
	realObject = dynamic_cast<CreatureObject*>(_getRealSceneObject());

	assert(!_getRealSceneObject() || realObject != NULL);
#else
	realObject = static_cast<CreatureObject*>(lua_touserdata(L, -1));
#endif

	return 0;
}

int LuaCreatureObject::getFirstName(lua_State* L) {
	String text = realObject->getFirstName();
	lua_pushstring(L, text.toCharArray());
	return 1;
}

int LuaCreatureObject::addDotState(lua_State* L) {
	//addDotState(unsigned long dotType, unsigned int strength, byte type, unsigned int duration, float potency, unsigned int defense)
	uint32 defense = lua_tointeger(L, -1);
	uint32 objectID = lua_tointeger(L, -2);
	float potency = lua_tonumber(L, -3);
	uint32 duration = lua_tointeger(L, -4);
	byte type = lua_tointeger(L, -5);
	uint32 strength = lua_tointeger(L, -6);
	uint64 dotType = lua_tointeger(L, -7);
	CreatureObject* attacker = (CreatureObject*)lua_touserdata(L, -8);

	Locker locker(realObject);

	realObject->addDotState(attacker, dotType, objectID, strength, type, duration, potency, defense);

	return 0;
}

int LuaCreatureObject::setState(lua_State* L) {
	uint32 state = (uint32) lua_tonumber(L, -1);

	Locker locker(realObject);

	realObject->setState(state, true);

	return 0;
}

int LuaCreatureObject::getPosture(lua_State* L) {
	lua_pushnumber(L, realObject->getPosture());

	return 1;
}

int LuaCreatureObject::setPosture(lua_State* L) {
	uint32 posture = (uint32) lua_tonumber(L, -1);

	realObject->setPosture(posture, true);

	return 0;
}

int LuaCreatureObject::setMoodString(lua_State* L) {
	String value = lua_tostring(L, -1);

	Locker locker(realObject);

	realObject->setMoodString(value);

	return 0;
}

int LuaCreatureObject::setPvpStatusBitmask(lua_State* L) {
	int bitmask = lua_tonumber(L, -1);
	realObject->setPvpStatusBitmask(bitmask, true);

	return 0;
}

int LuaCreatureObject::sendOpenHolocronToPageMessage(lua_State* L) {
	realObject->sendOpenHolocronToPageMessage();

	return 0;
}

int LuaCreatureObject::sendSystemMessage(lua_State* L) {
	if (lua_islightuserdata(L, -1)) {
		StringIdChatParameter* message = (StringIdChatParameter*)lua_touserdata(L, -1);
		realObject->sendSystemMessage(*message);
	} else {
		String value = lua_tostring(L, -1);
		realObject->sendSystemMessage(value);
	}
	return 0;
}

int LuaCreatureObject::sendSystemMessageWithDI(lua_State* L) {
	String text = lua_tostring(L, -2);
	uint32 value = (uint32) lua_tonumber(L, -1);

	StringIdChatParameter param(text);
	param.setDI(value);

	realObject->sendSystemMessage(param);

	return 0;
}

int LuaCreatureObject::sendSystemMessageWithTO(lua_State* L) {
	String text = lua_tostring(L, -2);
	String value = lua_tostring(L, -1);

	StringIdChatParameter param(text);
	param.setTO(value);

	realObject->sendSystemMessage(param);

	return 0;
}

int LuaCreatureObject::sendGroupMessage(lua_State* L) {
	String value = lua_tostring(L, -1);

	if (realObject == NULL)
		return 0;

	if (!realObject->isGrouped()) {
		realObject->sendSystemMessage(value);
	} else {
		GroupObject* group = realObject->getGroup();

		group->sendSystemMessage(value);
	}

	return 0;
}

int LuaCreatureObject::setHAM(lua_State* L) {
	uint32 type = (uint32) lua_tonumber(L, -2);
	uint32 value = (uint32) lua_tonumber(L, -1);

	Locker locker(realObject);

	realObject->setHAM(type, value);

	return 0;
}

int LuaCreatureObject::setBaseHAM(lua_State* L) {
	uint32 type = (uint32) lua_tonumber(L, -2);
	uint32 value = (uint32) lua_tonumber(L, -1);

	Locker locker(realObject);

	realObject->setBaseHAM(type, value);

	return 0;
}

int LuaCreatureObject::setMaxHAM(lua_State* L) {
	uint32 type = (uint32) lua_tonumber(L, -2);
	uint32 value = (uint32) lua_tonumber(L, -1);

	Locker locker(realObject);

	realObject->setMaxHAM(type, value);

	return 0;
}

int LuaCreatureObject::playMusicMessage(lua_State *L) {
	String value = lua_tostring(L, -1);
	realObject->playMusicMessage(value);

	return 0;
}

int LuaCreatureObject::setBankCredits(lua_State *L) {
	uint32 credits = (uint32) lua_tonumber(L, -1);

	realObject->setBankCredits(credits);

	return 0;
}

int LuaCreatureObject::sendNewbieTutorialRequest(lua_State *L) {
	String value = lua_tostring(L, -1);
	realObject->sendNewbieTutorialRequest(value);

	return 0;
}

int LuaCreatureObject::hasScreenPlayState(lua_State *L) {
	String play = lua_tostring(L, -1);
	uint64 stateToCheck = lua_tointeger(L, -2);

	uint64 state = realObject->getScreenPlayState(play);

	bool check = state & stateToCheck;

	lua_pushboolean(L, check);

	return 1;
}

int LuaCreatureObject::getScreenPlayState(lua_State *L) {
	String play = lua_tostring(L, -1);
	uint64 state = realObject->getScreenPlayState(play);

	lua_pushinteger(L, state);

	return 1;
}

int LuaCreatureObject::sendNewbieTutorialEnableHudElement(lua_State* L) {
	String ui = lua_tostring(L, -3);
	int enable = lua_tonumber(L, -2);
	float blinkCount = lua_tonumber(L, -1);

	realObject->sendNewbieTutorialEnableHudElement(ui, enable, blinkCount);

	return 0;
}

int LuaCreatureObject::hasSkill(lua_State* L) {
	String value = lua_tostring(L, -1);

	bool check = realObject->hasSkill(value);

	lua_pushboolean(L, check);

	return 1;
}

int LuaCreatureObject::removeSkill(lua_State* L) {
	String value = lua_tostring(L, -1);

	realObject->removeSkill(value, true);
	return 0;
}

int LuaCreatureObject::getInCellNumber(lua_State* L) {
	SceneObject* parent = realObject->getParent().get().get();

	if (parent == NULL || !parent->isCellObject())
		lua_pushnumber(L, -1);
	else {
		int cellId = ((CellObject*)parent)->getCellNumber();

		lua_pushnumber(L, cellId);
	}

	return 1; // we return the number of vars pushed to the L stack
}

int LuaCreatureObject::getBuildingParentID(lua_State* L) {
	SceneObject* parent = realObject->getParentRecursively(SceneObjectType::BUILDING).get().get();

	if (parent == NULL)
		lua_pushnumber(L, 0);
	else
		lua_pushnumber(L, parent->getObjectID());

	return 1;
}

int LuaCreatureObject::setScreenPlayState(lua_State *L) {
	String play = lua_tostring(L, -1);
	uint64 stateToSet = lua_tointeger(L, -2);

	realObject->setScreenPlayState(play, stateToSet | realObject->getScreenPlayState(play));
	realObject->notifyObservers(ObserverEventType::SCREENPLAYSTATECHANGED, realObject);
	return 0;
}

int LuaCreatureObject::removeScreenPlayState(lua_State* L) {
	String play = lua_tostring(L, -1);
	uint64 stateToClear = lua_tointeger(L, -2);

	if (realObject != NULL) {
		realObject->setScreenPlayState(play, realObject->getScreenPlayState(play) & (~stateToClear));
		realObject->notifyObservers(ObserverEventType::SCREENPLAYSTATECHANGED, realObject);
	}
	return 0;
}

int LuaCreatureObject::getTargetID(lua_State* L) {
	uint64 targetID = realObject->getTargetID();

	lua_pushinteger(L, targetID);

	return 1;
}

int LuaCreatureObject::clearCombatState(lua_State* L) {
	bool clearDef = lua_tonumber(L, -1);

	Locker locker(realObject);

	realObject->clearCombatState(clearDef);

	return 0;
}

int LuaCreatureObject::getHAM(lua_State* L) {
	int type = lua_tonumber(L, -1);

	int value = realObject->getHAM(type);

	lua_pushnumber(L, value);

	return 1;
}

int LuaCreatureObject::getMaxHAM(lua_State* L) {
	int type = lua_tonumber(L, -1);

	int value = realObject->getMaxHAM(type);

	lua_pushnumber(L, value);

	return 1;
}

int LuaCreatureObject::inflictDamage(lua_State* L) {
 //int inflictDamage(TangibleObject attacker, int damageType, int damage, boolean destroy, boolean notifyClient = true);
	int destroy = lua_tonumber(L, -1);
	int damage = lua_tonumber(L, -2);
	int damageType = lua_tonumber(L, -3);
	TangibleObject* attacker = (TangibleObject*) lua_touserdata(L, -4);

	realObject->inflictDamage(attacker, damageType, damage, destroy);

	return 0;
}

int LuaCreatureObject::getBankCredits(lua_State *L) {
	lua_pushnumber(L, realObject->getBankCredits());

	return 1; // we return the number of vars pushed to the L stack
}

int LuaCreatureObject::getConversationSession(lua_State* L) {
	Reference<ConversationSession*> session = realObject->getActiveSession(SessionFacadeType::CONVERSATION).castTo<ConversationSession*>();

	if (session != NULL) {
		session->_setUpdated(true);
		lua_pushlightuserdata(L, session);
	} else
		lua_pushnil(L);

	return 1;
}

int LuaCreatureObject::doAnimation(lua_State* L) {
	String animString = lua_tostring(L, -1);

	if (realObject != NULL)
		realObject->doAnimation(animString);

	return 0;
}

int LuaCreatureObject::engageCombat(lua_State* L) {
	CreatureObject* enemy = (CreatureObject*)lua_touserdata(L, -1);

	Locker locker(realObject);

	if (enemy != NULL)
		realObject->addDefender(enemy);

	return 0;
}

int LuaCreatureObject::getPlayerObject(lua_State* L) {
	Reference<PlayerObject*> obj = realObject->getPlayerObject();

	if (obj != NULL) {
		obj->_setUpdated(true);
		lua_pushlightuserdata(L, obj);
	} else
		lua_pushnil(L);

	return 1;
}

int LuaCreatureObject::getFaction(lua_State* L) {
	uint32 faction = realObject->getFaction();

	lua_pushinteger(L, faction);

	return 1;
}

int LuaCreatureObject::isRebel(lua_State* L) {
	lua_pushboolean(L, realObject->isRebel());

	return 1;
}

int LuaCreatureObject::isNeutral(lua_State* L) {
	lua_pushboolean(L, realObject->isNeutral());

	return 1;
}

int LuaCreatureObject::isImperial(lua_State* L) {
	lua_pushboolean(L, realObject->isImperial());

	return 1;
}

int LuaCreatureObject::setFaction(lua_State* L) {
	uint32 faction = lua_tointeger(L, -1);

	Locker locker(realObject);

	realObject->setFaction(faction);

	return 0;
}

int LuaCreatureObject::setFactionRank(lua_State* L) {
	int rank = lua_tointeger(L, -1);

	Locker locker(realObject);

	realObject->setFactionRank(rank);

	return 0;
}

int LuaCreatureObject::getFactionRank(lua_State* L) {
	lua_pushinteger(L, realObject->getFactionRank());

	return 1;
}

int LuaCreatureObject::getCashCredits(lua_State* L) {
	lua_pushinteger(L, realObject->getCashCredits());

	return 1;
}

int LuaCreatureObject::subtractCashCredits(lua_State* L) {
	realObject->subtractCashCredits(lua_tointeger(L, -1));

	return 0;
}

int LuaCreatureObject::addCashCredits(lua_State* L) {
	bool notifyClient = lua_toboolean(L, -1);
	int credits = lua_tonumber(L, -2);
	realObject->addCashCredits(credits, notifyClient);

	return 0;
}

int LuaCreatureObject::isAiAgent(lua_State* L) {
	bool val = realObject->isAiAgent();

	lua_pushboolean(L, val);

	return 1;
}

int LuaCreatureObject::isGrouped(lua_State* L) {
	bool val = realObject->isGrouped();

	lua_pushboolean(L, val);

	return 1;
}

int LuaCreatureObject::isGroupedWith(lua_State* L) {
	CreatureObject* groupMember = (CreatureObject*) lua_touserdata(L, -1);

	if (realObject == NULL || groupMember == NULL || !realObject->isGrouped())
		return 0;

	GroupObject* group = realObject->getGroup();

	lua_pushboolean(L, group != NULL && group->hasMember(groupMember));

	return 1;
}

int LuaCreatureObject::setLootRights(lua_State* L) {
	CreatureObject* player = (CreatureObject*) lua_touserdata(L, -1);

	if (realObject == NULL || player == NULL)
		return 0;

	uint64 ownerID = player->getObjectID();
	SceneObject* inventory = realObject->getSlottedObject("inventory");

	if (inventory == NULL)
		return 0;

	inventory->setContainerOwnerID(ownerID);
	return 1;
}

int LuaCreatureObject::getGroupSize(lua_State* L) {
	Locker locker(realObject);

	GroupObject* group = realObject->getGroup();

	if (group == NULL) {
		lua_pushnumber(L, 0);
		return 1;
	}

	Locker lock(group, realObject);

	lua_pushnumber(L, group->getGroupSize());

	return 1;
}

int LuaCreatureObject::setOptionsBitmask(lua_State* L) {
	uint32 bitmask = lua_tointeger(L, -1);

	realObject->setOptionsBitmask(bitmask, true);

	return 0;
}

int LuaCreatureObject::getGroupMember(lua_State* L) {
	int i = lua_tonumber(L, -1);

	if (i < 0)
		i = 0;

	Locker locker(realObject);

	GroupObject* group = realObject->getGroup();

	if (group == NULL) {
		lua_pushnil(L);
		return 1;
	}

	Locker lock(group, realObject);

	if (group->getGroupSize() < i) {
		lua_pushnil(L);
		return 1;
	}

	SceneObject* creo = group->getGroupMember(i);

	if (creo == NULL) {
		realObject->info("LuaCreatureObject::getGroupMember GroupMember is NULL.");
		lua_pushnil(L);
	} else {
		creo->_setUpdated(true);
		lua_pushlightuserdata(L, creo);
	}

	return 1;
}

int LuaCreatureObject::checkCooldownRecovery(lua_State* L) {
	String cooldownName = lua_tostring(L, -1);

	lua_pushboolean(L, realObject->checkCooldownRecovery(cooldownName));

	return 1;
}

int LuaCreatureObject::addCooldown(lua_State* L) {
	String cooldownName = lua_tostring(L, -2);
	int milliseconds = lua_tointeger(L, -1);

	realObject->addCooldown(cooldownName, milliseconds);

	return 0;
}

int LuaCreatureObject::isDead(lua_State* L) {
	bool retVal = realObject->isDead();

	lua_pushboolean(L, retVal);

	return 1;
}

int LuaCreatureObject::isIncapacitated(lua_State* L) {
	lua_pushboolean(L, realObject->isIncapacitated());
	return 1;
}

int LuaCreatureObject::getLevel(lua_State* L) {
	int level = realObject->getLevel();

	lua_pushinteger(L, level);

	return 1;
}

int LuaCreatureObject::getQueueSize(lua_State* L) {
	int size = realObject->getCommandQueueSize();

	lua_pushinteger(L, size);

	return 1;
}

int LuaCreatureObject::isDancing(lua_State* L) {
	bool retVal = realObject->isDancing();

	lua_pushboolean(L, retVal);

	return 1;
}

int LuaCreatureObject::isPlayingMusic(lua_State* L) {
	bool retVal = realObject->isPlayingMusic();

	lua_pushboolean(L, retVal);

	return 1;
}

int LuaCreatureObject::getPerformanceName(lua_State* L) {
	ManagedReference<Facade*> facade = realObject->getActiveSession(SessionFacadeType::ENTERTAINING);

	if (facade == NULL) {
		lua_pushnil(L);
		return 1;
	}

	ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*> (facade.get());

	if (session == NULL) {
		lua_pushnil(L);;
		return 1;
	}

	if (!session->isPlayingMusic() && !session->isDancing())
		lua_pushnil(L);
	else
		lua_pushstring(L, session->getPerformanceName().toCharArray());

	return 1;
}

int LuaCreatureObject::getWalkSpeed(lua_State* L) {
	lua_pushnumber(L, realObject->getWalkSpeed());
	return 1;
}

int LuaCreatureObject::isAttackableBy(lua_State* L) {
	TangibleObject* obj = (TangibleObject*) lua_touserdata(L, -1);

	bool retVal = realObject->isAttackableBy(obj);
	lua_pushboolean(L, retVal);

	return 1;
}

int LuaCreatureObject::getSpecies(lua_State* L) {
	lua_pushinteger(L, realObject->getSpecies());

	return 1;
}

int LuaCreatureObject::isDroidPet(lua_State* L) {
	bool retVal = realObject->isDroidObject() && realObject->isPet();
	lua_pushboolean(L, retVal);

	return 1;
}

int LuaCreatureObject::isCombatDroidPet(lua_State* L) {
	bool retVal = realObject->isDroidObject() && realObject->isPet();
	if (retVal) {
		DroidObject* d = cast<DroidObject*>(realObject);
		retVal = d->isCombatDroid();
	}
	lua_pushboolean(L, retVal);
	return 1;
}

int LuaCreatureObject::awardExperience(lua_State* L) {
	String experienceType = lua_tostring(L, -2);
	int experienceAmount = lua_tointeger(L, -1);

	PlayerManager* playerManager = realObject->getZoneServer()->getPlayerManager();
	playerManager->awardExperience(realObject, experienceType, experienceAmount, false);

	return 0;
}

int LuaCreatureObject::getOwner(lua_State* L) {
	CreatureObject* retVal = realObject->getLinkedCreature().get();

	if (retVal == NULL)
		lua_pushnil(L);
	else
		lua_pushlightuserdata(L, retVal);
	return 1;
}

int LuaCreatureObject::getCurrentSpeed(lua_State* L) {
	float currentSpeed = realObject->getCurrentSpeed();

	lua_pushnumber(L, currentSpeed);

	return 1;
}

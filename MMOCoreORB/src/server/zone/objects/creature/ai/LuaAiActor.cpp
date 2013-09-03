/*
 * LuaAiActor.cpp
 *
 *  Created on: Sep 1, 2013
 *      Author: swgemu
 */

#include "LuaAiActor.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {

const char LuaAiActor::className[] = "LuaAiActor";

Luna<LuaAiActor>::RegType LuaAiActor::Register[] = {
	{ "_getObject", &LuaAiActor::_getObject },
	{ "doAwarenessCheck", &LuaAiActor::doAwarenessCheck },
	{ "getNpcTemplate", &LuaAiActor::getNpcTemplate },
	{ "isCamouflaged", &LuaAiActor::isCamouflaged },
	{ "isScentMasked", &LuaAiActor::isScentMasked },
	{ "isConcealed", &LuaAiActor::isConcealed },
	{ "activateRecovery", &LuaAiActor::activateRecovery },
	{ "activateMovementEvent", &LuaAiActor::activateMovementEvent },
	{ "activateAwarenessEvent", &LuaAiActor::activateAwarenessEvent },
	{ "activatePostureRecovery", &LuaAiActor::activatePostureRecovery },
	{ "queueDizzyFallEvent", &LuaAiActor::queueDizzyFallEvent },
	{ "setNextPosition", &LuaAiActor::setNextPosition },
	{ "setNextStepPosition", &LuaAiActor::setNextStepPosition },
	{ "getNextStepPosition", &LuaAiActor::getNextStepPosition },
	{ "setShowNextPosition", &LuaAiActor::setShowNextPosition },
	{ "isShowNextPosition", &LuaAiActor::isShowNextPosition },
	{ "getMovementMarkers", &LuaAiActor::getMovementMarkers },
	{ "getMovementMarkersSize", &LuaAiActor::getMovementMarkersSize },
	{ "getMovementMarker", &LuaAiActor::getMovementMarker },
	{ "dropMovementMarker", &LuaAiActor::dropMovementMarker },
	{ "dropAllMovemementMarkers", &LuaAiActor::dropAllMovemementMarkers },
	{ "addMovementMarker", &LuaAiActor::addMovementMarker },
	{ "clearPatrolPoints", &LuaAiActor::clearPatrolPoints },
	{ "getPatrolPoints", &LuaAiActor::getPatrolPoints },
	{ "addPatrolPoint", &LuaAiActor::addPatrolPoint },
	{ "setHomeLocation", &LuaAiActor::setHomeLocation },
	{ "getHomeLocation", &LuaAiActor::getHomeLocation },
	{ "getNumberOfPlayersInRange", &LuaAiActor::getNumberOfPlayersInRange },
	{ "getFollowObject", &LuaAiActor::getFollowObject },
	{ "setFollowObject", &LuaAiActor::setFollowObject },
	{ "setTargetObject", &LuaAiActor::setTargetObject },
	{ "setOblivious", &LuaAiActor::setOblivious },
	{ "setDefender", &LuaAiActor::setDefender },
	{ "addDefender", &LuaAiActor::addDefender },
	{ "removeDefender", &LuaAiActor::removeDefender },
	{ "isAttackableBy", &LuaAiActor::isAttackableBy },
	{ "isAggressiveTo", &LuaAiActor::isAggressiveTo },
	{ "getKinetic", &LuaAiActor::getKinetic },
	{ "getEnergy", &LuaAiActor::getEnergy },
	{ "getElectricity", &LuaAiActor::getElectricity },
	{ "getStun", &LuaAiActor::getStun },
	{ "getBlast", &LuaAiActor::getBlast },
	{ "getHeat", &LuaAiActor::getHeat },
	{ "getCold", &LuaAiActor::getCold },
	{ "getAcid", &LuaAiActor::getAcid },
	{ "getLightSaber", &LuaAiActor::getLightSaber },
	{ "isStalker", &LuaAiActor::isStalker },
	{ "isKiller", &LuaAiActor::isKiller },
	{ "getFerocity", &LuaAiActor::getFerocity },
	{ "getArmor", &LuaAiActor::getArmor },
	{ "getFactionString", &LuaAiActor::getFactionString },
	{ "getSocialGroup", &LuaAiActor::getSocialGroup },
	{ "getChanceHit", &LuaAiActor::getChanceHit },
	{ "getDamageMin", &LuaAiActor::getDamageMin },
	{ "getDamageMax", &LuaAiActor::getDamageMax },
	{ "getBaseXp", &LuaAiActor::getBaseXp },
	{ "getDiet", &LuaAiActor::getDiet },
	{ "getAttackMap", &LuaAiActor::getAttackMap },
	{ "getCreatureTemplate", &LuaAiActor::getCreatureTemplate },
	{ 0, 0 }
};

LuaAiActor::LuaAiActor(lua_State *L) {
	realObject = static_cast<AiActor*>(lua_touserdata(L, 1));
}

LuaAiActor::~LuaAiActor() {
}

int LuaAiActor::_getObject(lua_State* L) {
	lua_pushlightuserdata(L, realObject.get());
	return 1;
}

int LuaAiActor::_setObject(lua_State* L) {
	realObject = static_cast<AiActor*>(lua_touserdata(L, -1));

	return 0;
}


int LuaAiActor::doAwarenessCheck(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	return 0;
}

int LuaAiActor::getNpcTemplate(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		CreatureTemplateReference* result = realObject->getNpcTemplate();

		if (result != NULL)
			lua_pushlightuserdata(L, result);
		else
			lua_pushnil(L);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getNpcTemplate()'");
	}
	return 0;
}

int LuaAiActor::isCamouflaged(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			CreatureObject* target = static_cast<CreatureObject*>(lua_touserdata(L, -1));

			bool result = realObject->isCamouflaged(target);

			lua_pushboolean(L, result);
			return 1;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:isCamouflaged(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:isCamouflaged(userdata)'");
	}
	return 0;
}

int LuaAiActor::isScentMasked(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			CreatureObject* target = static_cast<CreatureObject*>(lua_touserdata(L, -1));

			bool result = realObject->isScentMasked(target);

			lua_pushboolean(L, result);
			return 1;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:isScentMasked(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:isScentMasked(userdata)'");
	}
	return 0;
}

int LuaAiActor::isConcealed(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			CreatureObject* target = static_cast<CreatureObject*>(lua_touserdata(L, -1));

			bool result = realObject->isConcealed(target);

			lua_pushboolean(L, result);
			return 1;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:isConcealed(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:isConcealed(userdata)'");
	}
	return 0;
}

int LuaAiActor::activateRecovery(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		realObject->activateRecovery();

		return 0;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:activateRecovery()'");
	}
	return 0;
}

int LuaAiActor::activateMovementEvent(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		realObject->activateMovementEvent();

		return 0;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:activateMovementEvent()'");
	}
	return 0;
}

int LuaAiActor::activateAwarenessEvent(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			CreatureObject* target = static_cast<CreatureObject*>(lua_touserdata(L, -1));

			realObject->activateAwarenessEvent(target);

			return 0;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:activateAwarenessEvent(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:activateAwarenessEvent(userdata)'");
	}
	return 0;
}

int LuaAiActor::activatePostureRecovery(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		realObject->activatePostureRecovery();

		return 0;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:activatePostureRecovery()'");
	}
	return 0;
}

int LuaAiActor::queueDizzyFallEvent(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		realObject->queueDizzyFallEvent();

		return 0;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:queueDizzyFallEvent()'");
	}
	return 0;
}

int LuaAiActor::setNextPosition(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	return 0;
}

int LuaAiActor::setNextStepPosition(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (lua_isnumber(L, -2)) {
			if (lua_isnumber(L, -3)) {
				if (lua_isnumber(L, -4)) {
					if (parameterCount == 4) {
						float x = lua_tonumber(L, -4);
						float z = lua_tonumber(L, -3);
						float y = lua_tonumber(L, -2);
						SceneObject* cell = static_cast<SceneObject*>(lua_touserdata(L, -1));

						realObject->setNextStepPosition(x, z, y, cell);

						return 0;
					} else {
						throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:setNextStepPosition(number, number, number, userdata)'");
					}
				} else {
					throw LuaCallbackException(L, "invalid argument at 3 for lua method 'AiActor:setNextStepPosition(number, number, number, userdata)'");
				}
			} else {
				throw LuaCallbackException(L, "invalid argument at 2 for lua method 'AiActor:setNextStepPosition(number, number, number, userdata)'");
			}
		} else {
			throw LuaCallbackException(L, "invalid argument at 1 for lua method 'AiActor:setNextStepPosition(number, number, number, userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:setNextStepPosition(number, number, number, userdata)'");
	}
	return 0;
}

int LuaAiActor::getNextStepPosition(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		PatrolPoint* result = realObject->getNextStepPosition();

		if (result != NULL)
			lua_pushlightuserdata(L, result);
		else
			lua_pushnil(L);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getNextStepPosition()'");
	}
	return 0;
}

int LuaAiActor::setShowNextPosition(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isboolean(L, -1)) {
		if (parameterCount == 1) {
			bool val = lua_toboolean(L, -1);

			realObject->setShowNextPosition(val);

			return 0;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:setShowNextPosition(boolean)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:setShowNextPosition(boolean)'");
	}
	return 0;
}

int LuaAiActor::isShowNextPosition(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		bool result = realObject->isShowNextPosition();

		lua_pushboolean(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:isShowNextPosition()'");
	}
	return 0;
}

int LuaAiActor::getMovementMarkers(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		Vector<ManagedReference<SceneObject* > >* result = realObject->getMovementMarkers();

		if (result != NULL)
			lua_pushlightuserdata(L, result);
		else
			lua_pushnil(L);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getMovementMarkers()'");
	}
	return 0;
}

int LuaAiActor::getMovementMarkersSize(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		int result = realObject->getMovementMarkersSize();

		lua_pushinteger(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getMovementMarkersSize()'");
	}
	return 0;
}

int LuaAiActor::getMovementMarker(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isnumber(L, -1)) {
		if (parameterCount == 1) {
			int i = lua_tointeger(L, -1);

			SceneObject* result = realObject->getMovementMarker(i);

			if (result != NULL)
				lua_pushlightuserdata(L, result);
			else
				lua_pushnil(L);
			return 1;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getMovementMarker(integer)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:getMovementMarker(integer)'");
	}
	return 0;
}

int LuaAiActor::dropMovementMarker(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			SceneObject* marker = static_cast<SceneObject*>(lua_touserdata(L, -1));

			realObject->dropMovementMarker(marker);

			return 0;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:dropMovementMarker(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:dropMovementMarker(userdata)'");
	}
	return 0;
}

int LuaAiActor::dropAllMovemementMarkers(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		realObject->dropAllMovemementMarkers();

		return 0;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:dropAllMovemementMarkers()'");
	}
	return 0;
}

int LuaAiActor::addMovementMarker(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			SceneObject* marker = static_cast<SceneObject*>(lua_touserdata(L, -1));

			realObject->addMovementMarker(marker);

			return 0;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:addMovementMarker(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:addMovementMarker(userdata)'");
	}
	return 0;
}

int LuaAiActor::clearPatrolPoints(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		realObject->clearPatrolPoints();

		return 0;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:clearPatrolPoints()'");
	}
	return 0;
}

int LuaAiActor::getPatrolPoints(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		PatrolPointsVector* result = realObject->getPatrolPoints();

		if (result != NULL)
			lua_pushlightuserdata(L, result);
		else
			lua_pushnil(L);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getPatrolPoints()'");
	}
	return 0;
}

int LuaAiActor::addPatrolPoint(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	return 0;
}

int LuaAiActor::setHomeLocation(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (lua_isnumber(L, -2)) {
			if (lua_isnumber(L, -3)) {
				if (lua_isnumber(L, -4)) {
					if (parameterCount == 4) {
						float x = lua_tonumber(L, -4);
						float z = lua_tonumber(L, -3);
						float y = lua_tonumber(L, -2);
						SceneObject* cell = static_cast<SceneObject*>(lua_touserdata(L, -1));

						realObject->setHomeLocation(x, z, y, cell);

						return 0;
					} else {
						throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:setHomeLocation(number, number, number, userdata)'");
					}
				} else {
					throw LuaCallbackException(L, "invalid argument at 3 for lua method 'AiActor:setHomeLocation(number, number, number, userdata)'");
				}
			} else {
				throw LuaCallbackException(L, "invalid argument at 2 for lua method 'AiActor:setHomeLocation(number, number, number, userdata)'");
			}
		} else {
			throw LuaCallbackException(L, "invalid argument at 1 for lua method 'AiActor:setHomeLocation(number, number, number, userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:setHomeLocation(number, number, number, userdata)'");
	}
	return 0;
}

int LuaAiActor::getHomeLocation(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		PatrolPoint* result = realObject->getHomeLocation();

		if (result != NULL)
			lua_pushlightuserdata(L, result);
		else
			lua_pushnil(L);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getHomeLocation()'");
	}
	return 0;
}

int LuaAiActor::getNumberOfPlayersInRange(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		int result = realObject->getNumberOfPlayersInRange();

		lua_pushinteger(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getNumberOfPlayersInRange()'");
	}
	return 0;
}

int LuaAiActor::getFollowObject(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		SceneObject* result = realObject->getFollowObject();

		if (result != NULL)
			lua_pushlightuserdata(L, result);
		else
			lua_pushnil(L);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getFollowObject()'");
	}
	return 0;
}

int LuaAiActor::setFollowObject(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			SceneObject* targ = static_cast<SceneObject*>(lua_touserdata(L, -1));

			realObject->setFollowObject(targ);

			return 0;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:setFollowObject(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:setFollowObject(userdata)'");
	}
	return 0;
}

int LuaAiActor::setTargetObject(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			SceneObject* obj = static_cast<SceneObject*>(lua_touserdata(L, -1));

			realObject->setTargetObject(obj);

			return 0;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:setTargetObject(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:setTargetObject(userdata)'");
	}
	return 0;
}

int LuaAiActor::setOblivious(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		realObject->setOblivious();

		return 0;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:setOblivious()'");
	}
	return 0;
}

int LuaAiActor::setDefender(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			SceneObject* defender = static_cast<SceneObject*>(lua_touserdata(L, -1));

			realObject->setDefender(defender);

			return 0;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:setDefender(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:setDefender(userdata)'");
	}
	return 0;
}

int LuaAiActor::addDefender(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			SceneObject* defender = static_cast<SceneObject*>(lua_touserdata(L, -1));

			realObject->addDefender(defender);

			return 0;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:addDefender(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:addDefender(userdata)'");
	}
	return 0;
}

int LuaAiActor::removeDefender(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			SceneObject* defender = static_cast<SceneObject*>(lua_touserdata(L, -1));

			realObject->removeDefender(defender);

			return 0;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:removeDefender(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:removeDefender(userdata)'");
	}
	return 0;
}

int LuaAiActor::isAttackableBy(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			CreatureObject* object = static_cast<CreatureObject*>(lua_touserdata(L, -1));

			bool result = realObject->isAttackableBy(object);

			lua_pushboolean(L, result);
			return 1;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:isAttackableBy(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:isAttackableBy(userdata)'");
	}
	return 0;
}

int LuaAiActor::isAggressiveTo(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (lua_isuserdata(L, -1)) {
		if (parameterCount == 1) {
			CreatureObject* object = static_cast<CreatureObject*>(lua_touserdata(L, -1));

			bool result = realObject->isAggressiveTo(object);

			lua_pushboolean(L, result);
			return 1;
		} else {
			throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:isAggressiveTo(userdata)'");
		}
	} else {
		throw LuaCallbackException(L, "invalid argument at 0 for lua method 'AiActor:isAggressiveTo(userdata)'");
	}
	return 0;
}

int LuaAiActor::getKinetic(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		float result = realObject->getKinetic();

		lua_pushnumber(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getKinetic()'");
	}
	return 0;
}

int LuaAiActor::getEnergy(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		float result = realObject->getEnergy();

		lua_pushnumber(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getEnergy()'");
	}
	return 0;
}

int LuaAiActor::getElectricity(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		float result = realObject->getElectricity();

		lua_pushnumber(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getElectricity()'");
	}
	return 0;
}

int LuaAiActor::getStun(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		float result = realObject->getStun();

		lua_pushnumber(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getStun()'");
	}
	return 0;
}

int LuaAiActor::getBlast(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		float result = realObject->getBlast();

		lua_pushnumber(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getBlast()'");
	}
	return 0;
}

int LuaAiActor::getHeat(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		float result = realObject->getHeat();

		lua_pushnumber(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getHeat()'");
	}
	return 0;
}

int LuaAiActor::getCold(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		float result = realObject->getCold();

		lua_pushnumber(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getCold()'");
	}
	return 0;
}

int LuaAiActor::getAcid(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		float result = realObject->getAcid();

		lua_pushnumber(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getAcid()'");
	}
	return 0;
}

int LuaAiActor::getLightSaber(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		float result = realObject->getLightSaber();

		lua_pushnumber(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getLightSaber()'");
	}
	return 0;
}

int LuaAiActor::isStalker(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		bool result = realObject->isStalker();

		lua_pushboolean(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:isStalker()'");
	}
	return 0;
}

int LuaAiActor::isKiller(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		bool result = realObject->isKiller();

		lua_pushboolean(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:isKiller()'");
	}
	return 0;
}

int LuaAiActor::getFerocity(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		unsigned int result = realObject->getFerocity();

		lua_pushinteger(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getFerocity()'");
	}
	return 0;
}

int LuaAiActor::getArmor(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		unsigned int result = realObject->getArmor();

		lua_pushinteger(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getArmor()'");
	}
	return 0;
}

int LuaAiActor::getFactionString(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		String result = realObject->getFactionString();

		lua_pushstring(L, result.toCharArray());
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getFactionString()'");
	}
	return 0;
}

int LuaAiActor::getSocialGroup(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		String result = realObject->getSocialGroup();

		lua_pushstring(L, result.toCharArray());
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getSocialGroup()'");
	}
	return 0;
}

int LuaAiActor::getChanceHit(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		float result = realObject->getChanceHit();

		lua_pushnumber(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getChanceHit()'");
	}
	return 0;
}

int LuaAiActor::getDamageMin(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		int result = realObject->getDamageMin();

		lua_pushinteger(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getDamageMin()'");
	}
	return 0;
}

int LuaAiActor::getDamageMax(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		int result = realObject->getDamageMax();

		lua_pushinteger(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getDamageMax()'");
	}
	return 0;
}

int LuaAiActor::getBaseXp(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		int result = realObject->getBaseXp();

		lua_pushinteger(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getBaseXp()'");
	}
	return 0;
}

int LuaAiActor::getDiet(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		unsigned int result = realObject->getDiet();

		lua_pushinteger(L, result);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getDiet()'");
	}
	return 0;
}

int LuaAiActor::getAttackMap(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		CreatureAttackMap* result = realObject->getAttackMap();

		if (result != NULL)
			lua_pushlightuserdata(L, result);
		else
			lua_pushnil(L);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getAttackMap()'");
	}
	return 0;
}

int LuaAiActor::getCreatureTemplate(lua_State *L) {
	int parameterCount = lua_gettop(L) - 1;

	if (parameterCount == 0) {
		CreatureTemplate* result = realObject->getCreatureTemplate();

		if (result != NULL)
			lua_pushlightuserdata(L, result);
		else
			lua_pushnil(L);
		return 1;
	} else {
		throw LuaCallbackException(L, "invalid argument count " + String::valueOf(parameterCount) + " for lua method 'AiActor:getCreatureTemplate()'");
	}
	return 0;
}

}
}
}
}
}

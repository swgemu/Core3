/*
 * LuaCreatureObject.h
 *
 *  Created on: 31/08/2009
 *      Author: victor
 */

#ifndef LUACREATUREOBJECT_H_
#define LUACREATUREOBJECT_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/LuaSceneObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;

	class LuaCreatureObject : public LuaSceneObject {
	public:
		// Constants
		static const char className[];
		static Luna<LuaCreatureObject>::RegType Register[];

		// Initialize the pointer
		LuaCreatureObject(lua_State *L);
		~LuaCreatureObject();

		int _setObject(lua_State* L);
		// Methods we will need to use
		int getBankCredits(lua_State *L);
		int setBankCredits(lua_State* L);
		int setHAM(lua_State* L);
		int sendSystemMessage(lua_State* L);
		int playMusicMessage(lua_State *L);
		int sendNewbieTutorialRequest(lua_State *L);
		int hasScreenPlayState(lua_State *L);
		int setScreenPlayState(lua_State *L);
		int sendNewbieTutorialEnableHudElement(lua_State* L);
		int getInCellNumber(lua_State* L);
		int sendOpenHolocronToPageMessage(lua_State* L);
		int getTargetID(lua_State* L);

	private:
		// The pointer to the 'real object' defined in object.cc
		Reference<CreatureObject*> realObject;
	};

}
}
}
}

using namespace server::zone::objects::creature;


#endif /* LUACREATUREOBJECT_H_ */

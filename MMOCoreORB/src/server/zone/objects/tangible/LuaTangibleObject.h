/*
 * LuaTangibleObject.cpp
 *
 *  Created on: 24/01/2012
 *      Author: xyborn
 */

#ifndef LUATANGIBLEOBJECT_H_
#define LUATANGIBLEOBJECT_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/LuaSceneObject.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
	class TangibleObject;

	class LuaTangibleObject : public LuaSceneObject {
	public:
		static const char className[];
		static Luna<LuaTangibleObject>::RegType Register[];

		LuaTangibleObject(lua_State *L);
		~LuaTangibleObject();

		int _setObject(lua_State* L);
		int setOptionsBitmask(lua_State *L);
		int setPvpStatusBitmask(lua_State *L);
		int setPvpStatusBit(lua_State *L);
		int getPvpStatusBitmask(lua_State *L);
		int isChangingFactionStatus(lua_State* L);
		int setCustomizationVariable(lua_State *L);
		int getPaletteColorCount(lua_State *L);
		int setConditionDamage(lua_State *L);
		int setMaxCondition(lua_State *L);
		int setFaction(lua_State *L);
		int getFaction(lua_State *L);
		int isImperial(lua_State *L);
		int isRebel(lua_State *L);
		int hasActiveArea(lua_State* L);
		int isInvisible(lua_State* L);

	protected:
		TangibleObject* realObject;
	};

}
}
}
}

using namespace server::zone::objects::tangible;


#endif /* LUATANGIBLEOBJECT_H_ */

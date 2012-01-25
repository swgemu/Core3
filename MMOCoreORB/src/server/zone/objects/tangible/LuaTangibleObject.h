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

		int setOptionsBitmask(lua_State *L);

	private:
		Reference<TangibleObject*> realObject;
	};

}
}
}
}

using namespace server::zone::objects::tangible;


#endif /* LUATANGIBLEOBJECT_H_ */

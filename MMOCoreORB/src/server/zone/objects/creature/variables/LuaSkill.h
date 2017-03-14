#ifndef LUASKILL_H_
#define LUASKILL_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/variables/Skill.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace variables {
	class LuaSkill {
	public:
		static const char className[];
		static Luna<LuaSkill>::RegType Register[];

		LuaSkill(lua_State *L);
		~LuaSkill();

		int _setObject(lua_State* L);
		int getName(lua_State* L);
		int getMoneyRequired(lua_State* L);
		int getSkillPointsRequired(lua_State* L);
		int getSkillsRequired(lua_State* L);
		int getXpType(lua_State* L);
		int getXpCost(lua_State* L);

	private:
		Reference<Skill*> realObject;
	};

}
}
}
}
}

using namespace server::zone::objects::creature::variables;


#endif /* LUASKILL_H_ */

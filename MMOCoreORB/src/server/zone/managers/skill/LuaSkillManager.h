#ifndef LUASKILLMANAGER_H_
#define LUASKILLMANAGER_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace managers {
namespace sui {
	class SuiManager;

	class LuaSkillManager {
	public:
		static const char className[];
		static Luna<LuaSkillManager>::RegType Register[];

		LuaSkillManager(lua_State *L);
		~LuaSkillManager();

		int fulfillsSkillPrerequisitesAndXp(lua_State* L);
		int fulfillsSkillPrerequisites(lua_State* L);
		int getSkill(lua_State* L);
		int awardSkill(lua_State* L);
		int canLearnSkill(lua_State* L);

	private:
		Reference<SkillManager*> realObject;
	};
}
}
}
}

using namespace server::zone::managers::sui;

#endif /* LUASKILLMANAGER_H_ */

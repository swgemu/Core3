#ifndef LUASKILLMANAGER_H_
#define LUASKILLMANAGER_H_

#include "engine/engine.h"
#include "engine/lua/Luna.h"

#include "system/lang/ref/Reference.h"

namespace server {
namespace zone {
namespace managers {
namespace skill {
class SkillManager;
}  // namespace skill
}  // namespace managers
}  // namespace zone
}  // namespace server

namespace server {
namespace zone {
namespace managers {
namespace sui {
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
		Reference<server::zone::managers::skill::SkillManager*> realObject;
	};
}
}
}
}

using namespace server::zone::managers::sui;

#endif /* LUASKILLMANAGER_H_ */

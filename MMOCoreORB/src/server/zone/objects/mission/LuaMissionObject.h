/*
 * LuaMissionObject.h
 *
 * Created on: 2024-12-29
 * Author: Hakry
*/

#ifndef LUAMISSIONOBJECT_H_
#define LUAMISSIONOBJECT_H_

#include "engine/engine.h"
#include "server/zone/objects/intangible/LuaIntangibleObject.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {

	class MissionObject;

	class LuaMissionObject : public LuaIntangibleObject {
	public:
		//Constants
		static const char className[];
		static Luna<LuaMissionObject>::RegType Register[];

		//Initialize the pointer
		LuaMissionObject(lua_State *L);
		~LuaMissionObject();

		int _setObject(lua_State* L);
		int setTemplateStrings(lua_State* L);
		int setTypeCRC(lua_State* L);
		int setQuestType(lua_State* L);
		int setQuestName(lua_State* L);
		int setFaction(lua_State* L);
		int setCreatorName(lua_State* L);
		int setMissionTitle(lua_State* L);
		int setMissionDescription(lua_State* L);
		int setStartPosition(lua_State* L);
		int setEndPosition(lua_State* L);
		int setMissionTargetName(lua_State* L);
		int setTargetTemplate(lua_State* L);
		int setMissionNumber(lua_State* L);
		int setRewardCredits(lua_State* L);
		int setMissionDifficulty(lua_State* L);
		int setSpaceDutyMission(lua_State* L);

		int getQuestCRC(lua_State* L);
		int isSpaceDutyMission(lua_State* L);

	private:
		MissionObject* realObject;
	};

}
}
}
}

using namespace server::zone::objects::mission;

#endif /* LUAMISSIONOBJECT_H_ */
/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef SKILLMANAGER_H_
#define SKILLMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/player/variables/Ability.h"

class Skill;
class PerformanceManager;
class ImageDesignManager;

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
}
}
}

using namespace server::zone::objects::creature;

namespace server {
namespace zone {
namespace objects {
namespace player {
	class PlayerObject;
}
}
}
}

using namespace server::zone::objects::player;

namespace server {
namespace zone {
namespace managers {
namespace skill {

class SkillManager : public Singleton<SkillManager>, public Logger, public Object {
	PerformanceManager* performanceManager;

	HashTable<String, Reference<Ability*> > abilityMap;
	HashTable<uint32, Reference<Skill*> > skillMap;

	Reference<Skill*> rootNode;

	VectorMap<String, int> defaultXpLimits;

	bool apprenticeshipEnabled;

public:
	SkillManager();
	~SkillManager();

	static int includeFile(lua_State* L);
	static int addSkill(lua_State* L);

	void loadLuaConfig();
	void loadClientData();
	void loadFromLua();
	void loadSkill(LuaObject* skill);
	void loadXpLimits();

	void addAbility(PlayerObject* ghost, const String& abilityName, bool notifyClient = true);
	void removeAbility(PlayerObject* ghost, const String& abilityName, bool notifyClient = true);

	void addAbilities(PlayerObject* ghost, Vector<String>& abilityNames, bool notifyClient = true);
	void removeAbilities(PlayerObject* ghost, Vector<String>& abilityNames, bool notifyClient = true);

	bool awardSkill(const String& skillName, CreatureObject* creature, bool notifyClient = true, bool awardRequiredSkills = false, bool noXpRequired = false);
	void awardDraftSchematics(Skill* skill, PlayerObject* ghost, bool notifyClient = true);

	bool surrenderSkill(const String& skillName, CreatureObject* creature, bool notifyClient = true);
	void surrenderAllSkills(CreatureObject* creature, bool notifyClient = true);

	/**
	 * Checks if the player can learn the skill (fullfills skill prerequisites, enough skill points and enough XP).
	 * @param skillName the name of the skill to check if the player can learn.
	 * @param creature the player creatur.
	 * @param noXpRequired XP check is skipped if this is set to true (used for character builder terminals and
	 * grant skill command).
	 * @return true if the player fullfills the requirements.
	 */
	bool canLearnSkill(const String& skillName, CreatureObject* creature, bool noXpRequired);

	/**
	 * Checks if the player fullfills the skill prerequisites and has enough XP for the skill.
	 * @param skillName the name of the skill to check.
	 * @param creature the player creatur.
	 * @return true if the player fullfills the requirements.
	 */
	bool fullfillsSkillPrerequisitesAndXp(const String& skillName, CreatureObject* creature);

	/**
	 * Checks if the player fullfills the skill prerequisites.
	 * @param skillName the name of the skill to check.
	 * @param creature the player creatur.
	 * @return true if the player fullfills the requirements.
	 */
	bool fullfillsSkillPrerequisites(const String& skillName, CreatureObject* creature);

	void updateXpLimits(PlayerObject* ghost);

	Skill* getSkill(const String& skillName) {
		return skillMap.get(skillName.hashCode());
	}

	Skill* getSkill(uint32 hashCode) {
		return skillMap.get(hashCode);
	}

	Ability* getAbility(const String& abilityName) {
		return abilityMap.get(abilityName);
	}

	PerformanceManager* getPerformanceManager() {
		return performanceManager;
	}

	inline bool isApprenticeshipEnabled() {
		return apprenticeshipEnabled;
	}
};

}
}
}
}

using namespace server::zone::managers::skill;

#endif // SKILLMANAGER_H_

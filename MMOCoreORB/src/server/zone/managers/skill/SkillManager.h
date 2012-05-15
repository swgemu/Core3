/*
Copyright (C) 2007 <SWGEmu>
This File is part of Core3.
This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.

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
	HashTable<String, Reference<Skill*> > skillMap;

	Reference<Skill*> rootNode;

	VectorMap<String, int> defaultXpLimits;

public:
	SkillManager();
	~SkillManager();

	static int includeFile(lua_State* L);
	static int addSkill(lua_State* L);

	void loadClientData();
	void loadAdminCommands();
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
		return skillMap.get(skillName);
	}

	Ability* getAbility(const String& abilityName) {
		return abilityMap.get(abilityName);
	}

	PerformanceManager* getPerformanceManager() {
		return performanceManager;
	}
};

}
}
}
}

using namespace server::zone::managers::skill;

#endif // SKILLMANAGER_H_

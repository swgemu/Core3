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

#ifndef SKILLMODMANAGER_H_
#define SKILLMODMANAGER_H_

#include "engine/engine.h"

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
namespace objects {
namespace tangible {
	class TangibleObject;
}
}
}
}

using namespace server::zone::objects::tangible;

namespace server {
namespace zone {
namespace managers {
namespace skill {

class SkillModManager : public Singleton<SkillModManager>, public Logger, public Object {

public:
	///Permanent Mods
	const static int PERMANENTMOD = 0x100;
	const static int TEMPLATE = 0x101; /// From LUA templates
	const static int SKILLBOX = 0x103; /// From Skills learned

	///Bonus Mods
	const static int BONUSMOD = 0x1000;
	const static int WEARABLE = 0x1001; /// From Wearable items
	const static int STRUCTURE = 0x1002; /// From Structures creature is in
	const static int CITY = 0x1003; // From Cities
	const static int DROID = 0x1004; // From medical droid modules

	// Temp Mod
	const static int TEMPORARYMOD = 0x10000;
	const static int BUFF = 0x10001; /// From temporary buffs
	const static int ABILITYBONUS = 0x10002; /// From CombatQueueCommands

private:
	VectorMap<uint32, int> skillModMax;
	VectorMap<uint32, int> skillModMin;
	SortedVector<String> disabledWearableSkillMods;
public:
	SkillModManager();
	~SkillModManager();

private:

	void init();

	void setDefaults();

	bool compareMods(VectorMap<String, int> mods, CreatureObject* creature, uint32 type);


public:
	void verifyWearableSkillMods(CreatureObject* creature);

	void verifyStructureSkillMods(TangibleObject* tano);

	void verifySkillBoxSkillMods(CreatureObject* creature);

	void verifyBuffSkillMods(CreatureObject* creature);

	inline int getMinSkill(const uint32 modType) {
		return skillModMin.get(modType);
	}

	inline int getMaxSkill(const uint32 modType) {
		return skillModMax.get(modType);
	}

	inline bool isWearableModDisabled(String mod) {
		return disabledWearableSkillMods.contains(mod);
	}
};

}
}
}
}

using namespace server::zone::managers::skill;

#endif // SKILLMODMANAGER_H_

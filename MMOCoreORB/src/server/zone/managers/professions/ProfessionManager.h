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

#ifndef PROFESSIONMANAGER_H_
#define PROFESSIONMANAGER_H_

#include "engine/engine.h"
#include "ProfessionMap.h"

/*namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace professions {

class SkillBox;

} // namespace professions
} // namespace creature
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::creature::professions;*/

#include "server/zone/objects/creature/professions/SkillBox.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
class PlayerCreature;
class PlayerObject;
}
}
}
}
using namespace server::zone::objects::player;


class Certification;
class Skill;

namespace server {
	namespace zone {
		namespace managers {
			namespace objectcontroller {
				class ObjectController;
			}
		}
	}
}

using namespace server::zone::managers::objectcontroller;

class PerformanceManager;
class ImageDesignManager;

namespace server {
 namespace zone {
  namespace managers {
   namespace professions {

	class ProfessionManager : public Mutex, public Logger, public Singleton<ProfessionManager>, public Object {
		ObjectController* objectController;
		PerformanceManager* performanceManager;
		ImageDesignManager* imageDesignManager;

		VectorMap<String, Reference<SkillBox*> > skillBoxMap;
		VectorMap<String, Reference<Certification*> > certificationMap;

		ProfessionMap professionMap;

		const static int professionHams[7][9];

	private:
		// load at startup DB methods
		void loadProfessionsFromDatabase();
		Profession* loadProfession(ResultSet* result);
		SkillBox* loadSkillBox(ResultSet* result, Profession* profession);
		void loadSkillRequirements(SkillBox* skillBox, String& skillRequirements);
		void loadSkillPreclusions(SkillBox* skillBox, String& skillPreclusions);
		void loadSkillSpeciesRequired(SkillBox* skillBox, String& skillSpeciesRequired);
		void loadSkillCommands(SkillBox* skillBox, String& skillCommands);
		void loadSkillMods(SkillBox* skillBox, String& skillMods);
		void loadDraftSchematics(SkillBox* skillBox, String& grantedDraftSchematics);

		SkillBox* loadBox(const String& name, Profession* profession);

		bool checkPrerequisites(SkillBox* skillBox, PlayerCreature* player);
		void awardSkillMods(SkillBox* skillBox, PlayerCreature* player, bool updateClient);
		void removeSkillMods(SkillBox* skillBox, PlayerCreature* player, bool updateClient);

		void awardDraftSchematics(SkillBox* skillBox, PlayerCreature* player, bool updateClient);
		void removeDraftSchematics(SkillBox* skillBox, PlayerCreature* player, bool updateClient);

		bool checkRequisitesToSurrender(SkillBox* skillBox, PlayerCreature* player, bool removeChildren);

		uint8 getLangFromRace(int race);

	public:
		ProfessionManager();
		~ProfessionManager();

		void initialize() {
			loadProfessionsFromDatabase();
		}

		//void surrenderAll(PlayerImplementation* player);
		bool isValidStartingProfession(const String& profession);
		void setStartingProfession(const String& startingProfession, int raceID, PlayerCreature* player);

		bool trainSkillBox(SkillBox* skillBox, PlayerCreature* player, bool updateClient);
		bool trainSkillBox(const String& skillBox, PlayerCreature* player, bool updateClient);

		bool playerTeachSkill(const String& name, PlayerCreature* player, PlayerCreature* teacher);

		void awardSkillBox(SkillBox* skillBox, PlayerCreature* player, bool awardRequired, bool updateClient);
		void awardDraftSchematics(SkillBox* skillBox, PlayerObject* player, bool updateClient);

		inline void awardSkillBox(const String& skillBox, PlayerCreature* player, bool awardRequired, bool updateClient) {
			SkillBox* sBox = skillBoxMap.get(skillBox);

			if (sBox != NULL)
				awardSkillBox(sBox, player, awardRequired, updateClient);
		}

		void loadXpTypeCap(PlayerCreature* player);

		bool surrenderSkillBox(SkillBox* skillBox, PlayerCreature* player, bool removeChildren, bool updateClient);
		bool surrenderSkillBox(const String& skillBox, PlayerCreature* player, bool removeChildren, bool updateClient);

		void surrenderAll(PlayerCreature* player);

		Skill* getSkill(const String& name);

		inline SkillBox* getSkillBox(const String& prof) {
			return skillBoxMap.get(prof);
		}

		inline Profession* getProfession(const String& prof) {
			return professionMap.get(prof);
		}

		inline PerformanceManager* getPerformanceManager() {
			return performanceManager;
		}

		inline ImageDesignManager* getImageDesignManager() {
			return imageDesignManager;
		}

		inline void setObjectController(ObjectController* objectControl) {
			objectController = objectControl;
		}

		friend class SkillManager;
		friend class CreatureManagerImplementation;
	};


   }
  }
 }
}

using namespace server::zone::managers::professions;

#endif /*PROFESSIONMANAGER_H_*/

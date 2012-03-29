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

#ifndef PLAYERCREATIONMANAGER_H_
#define PLAYERCREATIONMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"

class Skill;

namespace server {
namespace zone {
	class ZoneServer;
}
}

using namespace server::zone;

namespace server {
namespace zone {
namespace packets {
	class MessageCallback;
}
}
}

using namespace server::zone::packets;

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
namespace scene {
	class SceneObject;
}
}
}
}

using namespace server::zone::objects::scene;

namespace server {
namespace zone {
namespace managers {
namespace player {
namespace creation {

class RacialCreationData;
class HairStyleInfo;
class ProfessionDefaultsInfo;

class PlayerCreationManager : public Singleton<PlayerCreationManager>, public Logger, public Object {
	ManagedWeakReference<ZoneServer*> zoneServer;

	VectorMap<String, Reference<RacialCreationData*> > racialCreationData;
	VectorMap<String, Reference<ProfessionDefaultsInfo*> > professionDefaultsInfo;
	VectorMap<String, SortedVector<String> > defaultCharacterEquipment;
	VectorMap<String, Reference<HairStyleInfo*> > hairStyleInfo;

	/**
	 * Vector containing starting items common for all races and professions.
	 */
	Vector<String> commonStartingItems;

	int startingCash;
	int startingBank;
	int skillPoints;

	bool freeGodMode;

	void loadLuaConfig();
	void loadRacialCreationData();
	void loadDefaultCharacterItems();
	void loadProfessionDefaultsInfo();
	void loadHairStyleInfo();

	/**
	 * Loads all starting items (profession specific, race specific, common) and
	 * starting clothes.
	 * @param lua pointer to a Lua object which contains the starting items and clothes.
	 */
	void loadLuaStartingItems(Lua* lua);

	void addCustomization(CreatureObject* creature, const String& customizationString, const String& appearanceFilename);
	void addHair(CreatureObject* creature, const String& hairTemplate, const String& hairCustomization);
	void addRacialMods(CreatureObject* creature, const String& race, Vector<String>* startingSkills, Vector<String>* startingItems, bool equipmentOnly);
	void addStartingItems(CreatureObject* creature, const String& clientTemplate, bool equipmentOnly);
	void addProfessionStartingItems(CreatureObject* creature, const String& profession, const String& clientTemplate, bool equipmentOnly);
	bool validateCreationCustomizationString(CustomizationVariables* data, const String& appearanceFilename);
	//void generateHologrindProfessions(CreatureObject* creature);

public:
	PlayerCreationManager();
	~PlayerCreationManager();

	/**
	 * Validates the character's name.
	 * @param characterName The character's name.
	 */
	bool validateCharacterName(const String& characterName);
	/**
	 * Attempts to create a character, validating the information passed back by the client.
	 */
	bool createCharacter(MessageCallback* data);

	/**
	 * Returns the requested maximum attribute limit for the specified race.
	 * @param race the race of interest.
	 * @param attributeNumber The attribute number (starting from 0).
	 * @return maximum attribute limit.
	 */
	int getMaximumAttributeLimit(const String& race, int attributeNumber);

	/**
	 * Returns the requested minimum attribute limit for the specified race.
	 * @param race the race of interest.
	 * @param attributeNumber The attribute number (starting from 0).
	 * @return minimum attribute limit.
	 */
	int getMinimumAttributeLimit(const String& race, int attributeNumber);

	/**
	 * Returns the total attribute limit for the specified race.
	 * @param race the race of interest.
	 * @return total attribute limit.
	 */
	int getTotalAttributeLimit(const String& race);

	/**
	 * Adds starting Weapons into the target container
	 * @param creature the player creature
	 * @param container the target container
	 */
	void addStartingWeaponsInto(CreatureObject* creature, SceneObject* container);

	/**
	 * Adds starting Items except Weapons into the target container
	 * @param creature the player creature
	 * @param container the target container
	 */
	void addStartingItemsInto(CreatureObject* creature, SceneObject* container);
};

}
}
}
}
}

using namespace server::zone::managers::player::creation;

#endif // PLAYERCREATIONMANAGER_H_

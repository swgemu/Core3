/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "server/zone/objects/creature/ai/HelperDroidObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/director/DirectorManager.h"

void HelperDroidObjectImplementation::initializeTransientMembers() {
	AiAgentImplementation::initializeTransientMembers();
}

void HelperDroidObjectImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* object) {
}

int HelperDroidObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	// Handle all helper droid selections here unless Store is selected
	if (selectedID != 59) {
		if (player == nullptr)
			return 0;

		Lua* lua = DirectorManager::instance()->getLuaInstance();

		if (lua == nullptr)
			return 0;

		if (selectedID >= 182 && selectedID <= 185) {
			// Space Information
			Reference<LuaFunction*> luaSpaceInfo = lua->createFunction("HelperDroid", "spaceInformation", 0);

			if (luaSpaceInfo == nullptr)
				return 0;

			*luaSpaceInfo << asAiAgent();
			*luaSpaceInfo << player;
			String selection = "";

			if (selectedID == 182) {
				selection = "findShip";
			} else if (selectedID == 183) {
				selection = "checkEmail";
			} else if (selectedID == 184) {
				selection = "travel";
			} else if (selectedID == 185) {
				selection = "makeMoney";
			}

			*luaSpaceInfo << selection;
			luaSpaceInfo->callFunction();
			return 0;
		}

		if (selectedID >= 111 && selectedID <= 116) {
			// Quests called from Lua Here
			Reference<LuaFunction*> luaProfessionQuest = lua->createFunction("HelperDroid", "professionQuest", 0);

			if (luaProfessionQuest == nullptr)
				return 0;

			*luaProfessionQuest << asAiAgent();
			*luaProfessionQuest << player;
			String profession = "";

			if (selectedID == 111) {
				// Brawler
				profession = "brawler";
			} else if (selectedID == 112) {
				// Marksman
				profession = "marksman";
			} else if (selectedID == 113) {
				// Scout
				profession = "scout";
			} else if (selectedID == 114) {
				// Artisan
				profession = "artisan";
			} else if (selectedID == 115) {
				// Medic
				profession = "medic";
			} else if (selectedID == 116) {
				// Entertainer
				profession = "entertainer";
			}

			*luaProfessionQuest << profession;
			luaProfessionQuest->callFunction();
			return 0;
		}

		if (selectedID >= 170 && selectedID <= 172) {
			// Helper Information called here
			Reference<LuaFunction*> luaHelperInfo = lua->createFunction("HelperDroid", "helperInformation", 0);

			if (luaHelperInfo == nullptr)
				return 0;

			*luaHelperInfo << asAiAgent();
			*luaHelperInfo << player;
			String selection = "";

			if (selectedID == 170) {
				// General Help
				selection = "general";
			} else if (selectedID == 171) {
				// Cloning
				selection = "cloning";
			} else if (selectedID == 172) {
				// Travel
				selection = "travel";
			}

			*luaHelperInfo << selection;
			luaHelperInfo->callFunction();
			return 0;
		}

		return 0;
	}

	return SceneObjectImplementation::handleObjectMenuSelect(player, selectedID); // PetMenuComponent
}

void HelperDroidObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player == nullptr)
		return;

	if (getLinkedCreature().get() == player) {
		// Droid Options
		menuResponse->addRadialMenuItem(132, 3, "@pet/pet_menu:droid_options");
		menuResponse->addRadialMenuItemToRadialID(132, 59, 3, "@pet/pet_menu:menu_store"); // Store

		// Starship Pilot Help
		menuResponse->addRadialMenuItem(181, 3, "@new_player:menu_space");
		menuResponse->addRadialMenuItemToRadialID(181, 182, 3, "@new_player:space_option_how_to_find_ship");
		menuResponse->addRadialMenuItemToRadialID(181, 183, 3, "@new_player:space_option_how_to_check_email");
		menuResponse->addRadialMenuItemToRadialID(181, 184, 3, "@new_player:space_option_how_to_travel");
		menuResponse->addRadialMenuItemToRadialID(181, 185, 3, "@new_player:space_option_how_to_make_money");

		// Profession Quests
		menuResponse->addRadialMenuItem(110, 3, "@new_player:menu_quests");

		if (player->hasSkill("combat_brawler_novice"))
			menuResponse->addRadialMenuItemToRadialID(110, 111, 3, "@new_player:submenu_brawler");
		if (player->hasSkill("combat_marksman_novice"))
			menuResponse->addRadialMenuItemToRadialID(110, 112, 3, "@new_player:submenu_marksman");
		if (player->hasSkill("outdoors_scout_novice"))
			menuResponse->addRadialMenuItemToRadialID(110, 113, 3, "@new_player:submenu_scout");
		if (player->hasSkill("crafting_artisan_novice"))
			menuResponse->addRadialMenuItemToRadialID(110, 114, 3, "@new_player:submenu_artisan");
		if (player->hasSkill("science_medic_novice"))
			menuResponse->addRadialMenuItemToRadialID(110, 115, 3, "@new_player:submenu_medic");
		if (player->hasSkill("social_entertainer_novice"))
			menuResponse->addRadialMenuItemToRadialID(110, 116, 3, "@new_player:submenu_entertainer");

		// General Help
		menuResponse->addRadialMenuItem(170, 3, "@new_player:menu_other");
		menuResponse->addRadialMenuItemToRadialID(170, 171, 3, "@new_player:submenu_cloning");
		menuResponse->addRadialMenuItemToRadialID(170, 172, 3, "@new_player:submenu_travel");

		return;
	}
}

void HelperDroidObjectImplementation::onCall() {
	Lua* lua = DirectorManager::instance()->getLuaInstance();

	if (lua == nullptr)
		return;

	Reference<LuaFunction*> luaGreetPlayer = lua->createFunction("HelperDroid", "greetPlayer", 0);

	if (luaGreetPlayer != nullptr) {
		ManagedReference<CreatureObject*> player = getLinkedCreature().get();

		if (player != nullptr) {
			*luaGreetPlayer << player;
			*luaGreetPlayer << asAiAgent();
			luaGreetPlayer->callFunction();
		}
	}
}

void HelperDroidObjectImplementation::notifyHelperDroidSkillTrained(CreatureObject* player, const String& skillString) {
	if (player == nullptr)
		return;

	Lua* lua = DirectorManager::instance()->getLuaInstance();

	if (lua == nullptr)
		return;

	Reference<LuaFunction*> luaSkillTrained = lua->createFunction("HelperDroid", "skillTrained", 0);

	if (luaSkillTrained == nullptr)
		return;

	*luaSkillTrained << asAiAgent();
	*luaSkillTrained << player;
	*luaSkillTrained << skillString;
	luaSkillTrained->callFunction();
}

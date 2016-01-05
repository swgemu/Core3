local ObjectManager = require("managers.object.object_manager")
local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")
local VillageJediManagerTownship = require("managers.jedi.village.village_jedi_manager_township")
local QuestManager = require("managers.quest.quest_manager")

SensorArrayAccessTerminalMenuComponent = {}

function SensorArrayAccessTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3, "@quest/force_sensitive/fs_crafting:menu_access_terminal")
end

function SensorArrayAccessTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil) then
		return 0
	end

	if (selectedID == 20) then
		if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00)) then
			CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:msg_cant_use_yet")
			return 0
		end
		SuiPhase1AccessTerminal:openAccessTerminal(pPlayer, pSceneObject)
	end

	return 0
end

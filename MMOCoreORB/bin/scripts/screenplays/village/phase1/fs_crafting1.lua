local ObjectManager = require("managers.object.object_manager")
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

FsCrafting1AnalyzerMenuComponent = {}

function FsCrafting1AnalyzerMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3, "@quest/force_sensitive/fs_crafting:menu_use_analyzer")
end

function FsCrafting1AnalyzerMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil) then
		return 0
	end

	if (selectedID == 20) then
		if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00)) then
			CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:msg_cant_use_yet")
			return 0
		end
		SuiFsCrafting1Analyzer:openAnalyzer(pPlayer, pSceneObject)
	end

	return 0
end

FsCrafting1CalibratorMenuComponent = {}

function FsCrafting1CalibratorMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3, "@quest/force_sensitive/fs_crafting:menu_use_calibrator")
end

function FsCrafting1CalibratorMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil) then
		return 0
	end

	if (selectedID == 20) then
		if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00)) then
			CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:msg_cant_use_yet")
			return 0
		end
		SuiFsCrafting1Calibrator:openCalibrator(pPlayer, pSceneObject)
	end

	return 0
end

FsCrafting1 = {}

function FsCrafting1:doPhaseChangeFail(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:phase1_msg_quest_fail_phase_done")

	for i = 0, 3, 1 do
		local questName = "fs_craft_puzzle_quest_0" .. i
		local questID = getPlayerQuestID(questName)

		QuestManager.resetQuest(pPlayer, questID)
	end
end

return FsCrafting1
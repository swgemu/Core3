local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageQuharekPhase1ConvoHandler = conv_handler:new {}

function villageQuharekPhase1ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 1) then
		return convoTemplate:getScreen("intro_wrong_phase")
	elseif (not VillageJediManagerCommon.isVillageEligible(pPlayer)) then
		return convoTemplate:getScreen("intro_not_eligible")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_03)) then
		return convoTemplate:getScreen("intro_completed_quest")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00)) then
		return convoTemplate:getScreen("intro_inprogress")
	elseif (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_completed_other_quest")
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_other_quest")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageQuharekPhase1ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "get_to_work") then
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00)
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE1_QUHAREK)
		FsCrafting1Goto1:start(pPlayer)
	end

	return pConvScreen
end

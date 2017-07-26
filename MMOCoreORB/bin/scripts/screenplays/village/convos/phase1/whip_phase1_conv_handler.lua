local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageWhipPhase1ConvoHandler = conv_handler:new {}

function villageWhipPhase1ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if (VillageJediManagerTownship:getCurrentPhase() ~= 1 or not VillageJediManagerCommon.isVillageEligible(pPlayer)) then
		return convoTemplate:getScreen("intro_not_eligible")
	elseif (readData(SceneObject(pPlayer):getObjectID() .. ":failedWhipPhase1") == 1) then
		return convoTemplate:getScreen("intro_quest_failed")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)) then
		return convoTemplate:getScreen("intro_quest_inprogress")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)) then
		return convoTemplate:getScreen("intro_quest_continue")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)) then
		return convoTemplate:getScreen("intro_quest_completed")
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer) or VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_other_quest")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageWhipPhase1ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "good_place_to_start") then
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE1_WHIP)
		FsReflex1:setRescueCount(pPlayer, 0)
		FsReflex1:startQuest(pPlayer)
	elseif (screenID == "intro_quest_failed" or screenID == "intro_quest_inprogress") then
		FsReflex1:restartQuest(pPlayer)
	elseif (screenID == "intro_quest_continue") then
		clonedConversation:setDialogTextDI(5 - FsReflex1:getRescueCount(pPlayer))
		FsReflex1:startNextRescue(pPlayer)
	end

	return pConvScreen
end

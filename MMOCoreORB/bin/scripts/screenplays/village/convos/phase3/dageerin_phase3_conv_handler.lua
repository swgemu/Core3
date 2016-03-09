local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageDageerinPhase3ConvoHandler = {  }

function villageDageerinPhase3ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 3) then
		return convoTemplate:getScreen("intro_not_eligible")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_FINISH)) then
		return convoTemplate:getScreen("intro_completed_quest")
	elseif (FsSad2:hasActiveNonReturnTask(pPlayer)) then
		return convoTemplate:getScreen("intro_on_task")
	elseif (FsSad2:hasActiveReturnTask(pPlayer) and FsSad2:hasExceededLimit(pPlayer)) then
		return convoTemplate:getScreen("intro_max_tasks_for_day")
	elseif ((FsSad2:hasActiveNonReturnTask(pPlayer) or FsSad2:hasActiveReturnTask(pPlayer)) and not SuiRadiationSensor:hasSensor(pPlayer)) then
		return convoTemplate:getScreen("intro_need_new_sensor")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN1)) then
		return convoTemplate:getScreen("intro_completed_one")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN2)) then
		return convoTemplate:getScreen("intro_completed_two")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN3)) then
		return convoTemplate:getScreen("intro_completed_three")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN4)) then
		return convoTemplate:getScreen("intro_completed_four")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN5)) then
		return convoTemplate:getScreen("intro_completed_five")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN6)) then
		return convoTemplate:getScreen("intro_completed_six")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN7)) then
		return convoTemplate:getScreen("intro_completed_seven")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN8)) then
		if (FsSad2:hasFullInventory(pPlayer)) then
			return convoTemplate:getScreen("intro_full_inventory")
		else
			return convoTemplate:getScreen("intro_reward")
		end
	elseif (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_completed_other_quest")
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_other_quest")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageDageerinPhase3ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "good_luck" or screenID == "intro_need_new_sensor") then
		SuiRadiationSensor:giveSensor(conversingPlayer)

		if (screenID == "good_luck") then
			FsSad2:acceptNextTask(conversingPlayer)
		end
	elseif (screenID == "come_back_when_eliminated" or screenID == "intro_reward") then
		FsSad2:acceptNextTask(conversingPlayer)
	end

	return conversationScreen
end

function villageDageerinPhase3ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()
	local pLastConversationScreen = nil
	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)
		return conversationTemplate:getScreen(optionLink)
	end
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end

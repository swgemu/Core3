local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageSarguilloPhase3ConvoHandler = {  }

function villageSarguilloPhase3ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 3) then
		return convoTemplate:getScreen("intro_not_available")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CS_QUEST_DONE)) then
		return convoTemplate:getScreen("intro_not_available")
	elseif (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_completed_other_quest")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CS_INTRO)) then
		return convoTemplate:getScreen("intro")
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_other_quest")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageSarguilloPhase3ConvoHandler:canTurnInDatapad(pPlayer, datapadTemplate)
	local pInventory =  CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return false
	end

	local pDatapad = getContainerObjectByTemplate(pInventory, datapadTemplate, true)

	if (pDatapad == nil) then
		return false
	end

	local csItem = LuaFsCsObject(pDatapad)

	return csItem:getDecayPercent() < 100
end

function villageSarguilloPhase3ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "intro") then
		if (not QuestManager.hasActiveQuest(conversingPlayer, QuestManager.quests.FS_CS_INTRO)) then
			clonedConversation:addOption("@conversation/combat_quest_p3:s_43c7c81c", "crucial_information")
			clonedConversation:addOption("@conversation/combat_quest_p3:s_ab0e6060", "if_still_interested")
		end
		if (self:canTurnInDatapad(conversingPlayer, "object/tangible/loot/quest/force_sensitive/camp_frequency_datapad.iff")) then
			clonedConversation:addOption("@conversation/combat_quest_p3:s_d403b674", "here_is_remote")
		end
		if (self:canTurnInDatapad(conversingPlayer, "object/tangible/loot/quest/force_sensitive/camp_waypoint_datapad.iff")) then
			clonedConversation:addOption("@conversation/combat_quest_p3:s_5d6c3f37", "simple_encryption")
		end
		if (QuestManager.hasActiveQuest(conversingPlayer, QuestManager.quests.FS_CS_INTRO)) then
			clonedConversation:addOption("@conversation/combat_quest_p3:s_f3864fa4", "work_with_friend")
		end
	elseif (screenID == "excellent") then
		VillageJediManagerCommon.setActiveQuestThisPhase(conversingPlayer)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_CS_INTRO)
	elseif (screenID == "here_is_remote") then
		FsCounterStrike:giveCampRemote(conversingPlayer)
	elseif (screenID == "simple_encryption") then
		FsCounterStrike:giveCampWaypoint(conversingPlayer)
	end

	return conversationScreen
end

function villageSarguilloPhase3ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

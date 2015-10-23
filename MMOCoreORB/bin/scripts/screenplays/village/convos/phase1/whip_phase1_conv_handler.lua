local ObjectManager = require("managers.object.object_manager")
local FsReflex1 = require("managers.jedi.village.phase1.fs_reflex1")
local QuestManager = require("managers.quest.quest_manager")

villageWhipPhase1ConvoHandler = {  }

function villageWhipPhase1ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if (VillageJediManagerTownship:getCurrentPhase() ~= 1) then
		return convoTemplate:getScreen("intro_not_eligible")
	elseif (readData(SceneObject(pPlayer):getObjectID() .. ":failedWhipPhase1") == 1) then
		return convoTemplate:getScreen("intro_quest_failed")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00) and not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)) then
		return convoTemplate:getScreen("intro_quest_inprogress")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)) then
		return convoTemplate:getScreen("intro_quest_continue")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05)) then
		return convoTemplate:getScreen("intro_quest_completed")
	end
	return convoTemplate:getScreen("intro")
end

function villageWhipPhase1ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "good_place_to_start") then
		FsReflex1:setRescueCount(conversingPlayer, 0)
		FsReflex1:startQuest(conversingPlayer)
	elseif (screenID == "intro_quest_failed") then
		FsReflex1:restartQuest(conversingPlayer)
	elseif (screenID == "intro_quest_continue") then
		clonedConversation:setDialogTextDI(5 - FsReflex1:getRescueCount(conversingPlayer))
		FsReflex1:startNextRescue(conversingPlayer)
	end

	return conversationScreen
end

function villageWhipPhase1ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

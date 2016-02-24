local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageWhipPhase2ConvoHandler = {  }

function villageWhipPhase2ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if (VillageJediManagerTownship:getCurrentPhase() ~= 2) then
		return convoTemplate:getScreen("intro_not_eligible")
	elseif (readData(SceneObject(pPlayer):getObjectID() .. ":failedWhipPhase2") == 1) then
		return convoTemplate:getScreen("intro_quest_failed")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)) then
		return convoTemplate:getScreen("intro_quest_completed")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00) and not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03)) then
		return convoTemplate:getScreen("intro_quest_inprogress")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03) and not self:hasSupplies(pPlayer)) then
		return convoTemplate:getScreen("intro_quest_inprogress")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03) and self:hasSupplies(pPlayer) and FsReflex2:getFetchCount(pPlayer) < 4) then
		return convoTemplate:getScreen("intro_quest_continue")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03) and self:hasSupplies(pPlayer) and FsReflex2:getFetchCount(pPlayer) == 4) then
		return convoTemplate:getScreen("intro_quest_completed")
	elseif (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_completed_other_quest")
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_other_quest")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageWhipPhase2ConvoHandler:hasSupplies(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return false
	end

	local pSupplies = getContainerObjectByTemplate(pInventory, "object/tangible/item/quest/force_sensitive/fs_reflex_supply_crate.iff", false)

	return pSupplies ~= nil
end

function villageWhipPhase2ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "here_is_location") then
		VillageJediManagerCommon.setActiveQuestThisPhase(conversingPlayer)
		FsReflex2:setFetchCount(conversingPlayer, 0)
		FsReflex2:startQuest(conversingPlayer)
	elseif (screenID == "intro_quest_failed" or screenID == "beacons_not_reliable") then
		FsReflex2:restartQuest(conversingPlayer)
	elseif ((screenID == "intro_quest_completed" or screenID == "intro_quest_continue") and FsReflex2:getFetchCount(conversingPlayer) < 5 and self:hasSupplies(conversingPlayer)) then
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")

		if pInventory ~= nil then
			local pSupplies = getContainerObjectByTemplate(pInventory, "object/tangible/item/quest/force_sensitive/fs_reflex_supply_crate.iff", false)

			if (pSupplies ~= nil) then
				SceneObject(pSupplies):destroyObjectFromWorld()
				SceneObject(pSupplies):destroyObjectFromDatabase()
			end
		end

		FsReflex2:completeSupplyFetch(conversingPlayer)

		if (screenID == "intro_quest_continue") then
			local fetchCount = FsReflex2:getFetchCount(conversingPlayer)
			clonedConversation:setDialogTextDI(5 - fetchCount)
			FsReflex2:startNextFetch(conversingPlayer)
		end
	end

	return conversationScreen
end

function villageWhipPhase2ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
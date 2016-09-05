local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageQtQcPhase2ConvoHandler = {  }

function villageQtQcPhase2ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 2) then
		return convoTemplate:getScreen("intro_communitycrafting_inactive")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageQtQcPhase2ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	printf("screenid: " .. screenID .. "\n")
	if (screenID == "intro") then
		if (VillageCommunityCrafting:isOnActiveCrafterList(conversingPlayer) and not QuestManager.hasCompletedQuest(conversingPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_01)) then
			clonedConversation:addOption("@conversation/qtqc_phase_2:s_3a6af75d", "schematics_given") -- I need the schematics for the village defenses.
		end

		clonedConversation:addOption("@conversation/qtqc_phase_2:s_20141151", "explain_resources") -- Tell me about these special resources again.

		if (VillageCommunityCrafting:isOnActiveCrafterList(conversingPlayer)) then
			clonedConversation:addOption("@conversation/qtqc_phase_2:s_ebcb651f", "put_in_inventory") -- I'd like to add an ingredient to the village defenses.
			
			--TODO: add item count check
			clonedConversation:addOption("@conversation/qtqc_phase_2:s_2ce1f012", "needs_multiple_items") -- How many more items do I need to contribute?
		end

		clonedConversation:addOption("@conversation/qtqc_phase_2:s_baf57f52", "what_you_want_to_know") -- I'd like to get the status of the village defenses.
	elseif (screenID == "schematics_given") then
		VillageCommunityCrafting:giveSchematics(conversingPlayer)
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_01)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_02)
	elseif (screenID == "see_attributes") then
		VillageCommunityCrafting:sendPlayerProjectAttributes(conversingPlayer, conversingNPC)
	elseif (string.match(screenID, "_slot_")) then
		local startPos, endPos = string.find(screenID, "_slot_")
		local tableType = string.sub(screenID, 1, startPos - 1)
		local slotNum = string.sub(screenID, endPos + 1)

		VillageCommunityCrafting:sendPlayerProjectSlotAttributes(conversingPlayer, conversingNPC, tableType, slotNum)
	end

	return conversationScreen
end

function villageQtQcPhase2ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

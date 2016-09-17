local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageQuharekPhase2ConvoHandler = {  }

function villageQuharekPhase2ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 2) then
		return convoTemplate:getScreen("intro_communitycrafting_inactive")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_02) and VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
		return convoTemplate:getScreen("intro_questcompleted_activecrafter")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_02) and not VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
		return convoTemplate:getScreen("intro_questcompleted_notactivecrafter")
	else
		return convoTemplate:getScreen("intro_communitycrafting_active")
	end
end

function villageQuharekPhase2ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "intro_questcompleted_activecrafter" or screenID == "intro_questcompleted_notactivecrafter" or screenID == "intro_communitycrafting_active") then
		if (VillageCommunityCrafting:getCurrentActiveCrafters() >= VillageCommunityCrafting:getMaxCraftersPerPhase()) then
			clonedConversation:addOption("@conversation/quharek_phase_2:s_955b2ddb", "max_crafters") -- I hear you're looking for crafters.
		else
			if (not CreatureObject(conversingPlayer):hasSkill("crafting_artisan_novice")) then
				clonedConversation:addOption("@conversation/quharek_phase_2:s_955b2ddb", "not_skilled") -- I hear you're looking for crafters.
			else
				clonedConversation:addOption("@conversation/quharek_phase_2:s_955b2ddb", "need_people_to_help") -- I hear you're looking for crafters.
			end
		end
		clonedConversation:addOption("@conversation/quharek_phase_2:s_baf57f52", "what_you_want_to_know") -- I'd like to get the status of the village defenses.
	elseif (screenID == "need_people_to_help") then
		clonedConversation:setDialogTextDI(VillageCommunityCrafting:getMinimumIngredients())
	elseif (screenID == "talk_to_qtqc") then
		VillageJediManagerCommon.setActiveQuestThisPhase(conversingPlayer)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_MAIN)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_01)
		VillageCommunityCrafting:addToActiveCrafterList(conversingPlayer)
		VillageCommunityCrafting:incrementCurrentActiveCrafters()
		VillageCommunityCrafting:addDefaultPlayerStatsToStatTables(conversingPlayer)

		local pGhost = CreatureObject(conversingPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			PlayerObject(pGhost):addWaypoint("dathomir", "@npc_name:qtqc", "", 5193, -4195, WAYPOINTYELLOW, true, true, 0)
		end
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

function villageQuharekPhase2ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

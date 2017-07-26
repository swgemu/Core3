local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageQuharekPhase3ConvoHandler = conv_handler:new {}

function villageQuharekPhase3ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 3) then
		return convoTemplate:getScreen("intro_communitycrafting_inactive")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_02) and VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
		return convoTemplate:getScreen("intro_questcompleted_activecrafter")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_02) and not VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
		return convoTemplate:getScreen("intro_questcompleted_notactivecrafter")
	else
		return convoTemplate:getScreen("intro_communitycrafting_active")
	end
end

function villageQuharekPhase3ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "intro_questcompleted_activecrafter" or screenID == "intro_questcompleted_notactivecrafter" or screenID == "intro_communitycrafting_active") then
		if (screenID ~= "intro_questcompleted_notactivecrafter" and not VillageCommunityCrafting:isOnActiveCrafterList(pPlayer) and not VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer) and not VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer) and VillageJediManagerCommon.isVillageEligible(pPlayer)) then
			if (VillageCommunityCrafting:getCurrentActiveCrafters() >= VillageCommunityCrafting:getMaxCraftersPerPhase()) then
				clonedConversation:addOption("@conversation/quharek_phase_3:s_955b2ddb", "max_crafters") -- I hear you're looking for crafters.
			else
				if (not CreatureObject(pPlayer):hasSkill("crafting_artisan_novice")) then
					clonedConversation:addOption("@conversation/quharek_phase_3:s_955b2ddb", "not_skilled") -- I hear you're looking for crafters.
				else
					clonedConversation:addOption("@conversation/quharek_phase_3:s_955b2ddb", "need_people_to_help") -- I hear you're looking for crafters.
				end
			end
		end
		clonedConversation:addOption("@conversation/quharek_phase_3:s_c266e38f", "what_you_want_to_know") -- I'd like to get the status of the village shields.
	elseif (screenID == "need_people_to_help") then
		clonedConversation:setDialogTextDI(VillageCommunityCrafting:getMinimumIngredients())
	elseif (screenID == "talk_to_qtqc") then
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE3_QUHAREK)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_MAIN)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_01)
		VillageCommunityCrafting:addToActiveCrafterList(pPlayer)
		VillageCommunityCrafting:incrementCurrentActiveCrafters()
		VillageCommunityCrafting:addDefaultPlayerStatsToStatTables(pPlayer)

		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			PlayerObject(pGhost):addWaypoint("dathomir", "@npc_name:qtqc", "", 5193, -4195, WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)
		end
	elseif (screenID == "see_attributes") then
		VillageCommunityCrafting:sendPlayerProjectAttributes(pPlayer, pNpc)
	elseif (string.match(screenID, "_slot_")) then
		local startPos, endPos = string.find(screenID, "_slot_")
		local tableType = string.sub(screenID, 1, startPos - 1)
		local slotNum = string.sub(screenID, endPos + 1)

		VillageCommunityCrafting:sendPlayerProjectSlotAttributes(pPlayer, pNpc, tableType, slotNum)
	end

	return pConvScreen
end

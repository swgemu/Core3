local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageQtQcPhase2ConvoHandler = conv_handler:new {}

function villageQtQcPhase2ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 2) then
		return convoTemplate:getScreen("intro_communitycrafting_inactive")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageQtQcPhase2ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "intro") then
		if (VillageCommunityCrafting:isOnActiveCrafterList(pPlayer) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_01)) then
			clonedConversation:addOption("@conversation/qtqc_phase_2:s_3a6af75d", "schematics_given") -- I need the schematics for the village defenses.
		end

		clonedConversation:addOption("@conversation/qtqc_phase_2:s_20141151", "explain_resources") -- Tell me about these special resources again.

		if (VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
			clonedConversation:addOption("@conversation/qtqc_phase_2:s_ebcb651f", "put_in_inventory") -- I'd like to add an ingredient to the village defenses.

			local ingredientsNeeded = VillageCommunityCrafting:getIngredientsNeededByPlayer(pPlayer)
			if (ingredientsNeeded > 1) then
				clonedConversation:addOption("@conversation/qtqc_phase_2:s_2ce1f012", "needs_multiple_items") -- How many more items do I need to contribute?
			elseif (ingredientsNeeded == 1) then
				clonedConversation:addOption("@conversation/qtqc_phase_2:s_2ce1f012", "needs_one_item") -- How many more items do I need to contribute?
			else
				clonedConversation:addOption("@conversation/qtqc_phase_2:s_2ce1f012", "needs_no_items") -- How many more items do I need to contribute?
			end
		end

		clonedConversation:addOption("@conversation/qtqc_phase_2:s_baf57f52", "what_you_want_to_know") -- I'd like to get the status of the village defenses.
	elseif (screenID == "needs_multiple_items") then
		clonedConversation:setDialogTextDI(VillageCommunityCrafting:getIngredientsNeededByPlayer(pPlayer))
	elseif (screenID == "schematics_given") then
		local result = VillageCommunityCrafting:giveSchematics(pPlayer)

		if (result) then
			local pGhost = CreatureObject(pPlayer):getPlayerObject()

			if (pGhost ~= nil) then
				PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
			end
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_01)
			QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_02)
		else
			VillageCommunityCrafting:removeSchematics(pPlayer, VillageJediManagerTownship:getCurrentPhase())
			clonedConversation:setDialogTextStringId("@conversation/qtqc_phase_2:s_31b4836a")
			clonedConversation:removeAllOptions()
			clonedConversation:setStopConversation(true)
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

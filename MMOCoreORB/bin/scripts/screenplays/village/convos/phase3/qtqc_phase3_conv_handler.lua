local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageQtQcPhase3ConvoHandler = conv_handler:new {}

function villageQtQcPhase3ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 3) then
		return convoTemplate:getScreen("intro_communitycrafting_inactive")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageQtQcPhase3ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "intro") then
		if (VillageCommunityCrafting:isOnActiveCrafterList(pPlayer) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_01)) then
			clonedConversation:addOption("@conversation/qtqc_phase_3:s_cbc4b5f7", "schematics_given") -- I need the schematics for the village shields.
		end

		clonedConversation:addOption("@conversation/qtqc_phase_3:s_20141151", "explain_resources") -- Tell me about these special resources again.

		if (VillageCommunityCrafting:isOnActiveCrafterList(pPlayer)) then
			clonedConversation:addOption("@conversation/qtqc_phase_3:s_5f230d28", "put_in_inventory") -- I'd like to add an ingredient to the village shields.

			local ingredientsNeeded = VillageCommunityCrafting:getIngredientsNeededByPlayer(pPlayer)
			if (ingredientsNeeded > 1) then
				clonedConversation:addOption("@conversation/qtqc_phase_3:s_2ce1f012", "needs_multiple_items") -- How many more items do I need to contribute?
			elseif (ingredientsNeeded == 1) then
				clonedConversation:addOption("@conversation/qtqc_phase_3:s_2ce1f012", "needs_one_item") -- How many more items do I need to contribute?
			else
				clonedConversation:addOption("@conversation/qtqc_phase_3:s_2ce1f012", "needs_no_items") -- How many more items do I need to contribute?
			end
		end

		clonedConversation:addOption("@conversation/qtqc_phase_3:s_c266e38f", "what_you_want_to_know") -- I'd like to get the status of the village shields.
	elseif (screenID == "needs_multiple_items") then
		clonedConversation:setDialogTextDI(VillageCommunityCrafting:getIngredientsNeededByPlayer(pPlayer))
	elseif (screenID == "schematics_given") then
		local result = VillageCommunityCrafting:giveSchematics(pPlayer)

		if (result) then
			local pGhost = CreatureObject(pPlayer):getPlayerObject()

			if (pGhost ~= nil) then
				PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
			end
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_01)
			QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_02)
		else
			VillageCommunityCrafting:removeSchematics(pPlayer, VillageJediManagerTownship:getCurrentPhase())
			clonedConversation:setDialogTextStringId("@conversation/qtqc_phase_3:s_31b4836a")
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

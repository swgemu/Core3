local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageWhipPhase2ConvoHandler = conv_handler:new {}

function villageWhipPhase2ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if (VillageJediManagerTownship:getCurrentPhase() ~= 2 or not VillageJediManagerCommon.isVillageEligible(pPlayer)) then
		return convoTemplate:getScreen("intro_not_eligible")
	elseif (readData(SceneObject(pPlayer):getObjectID() .. ":failedWhipPhase2") == 1) then
		return convoTemplate:getScreen("intro_quest_failed")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_04)) then
		return convoTemplate:getScreen("intro_quest_completed")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_00) and not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03)) then
		return convoTemplate:getScreen("intro_quest_inprogress")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03) and not self:hasSupplies(pPlayer)) then
		return convoTemplate:getScreen("intro_quest_inprogress")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03) and self:hasSupplies(pPlayer) and FsReflex2:getFetchCount(pPlayer) < 5) then
		return convoTemplate:getScreen("intro_quest_continue")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_REFLEX_FETCH_QUEST_03) and self:hasSupplies(pPlayer) and FsReflex2:getFetchCount(pPlayer) == 5) then
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

function villageWhipPhase2ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "here_is_location") then
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE2_WHIP)
		FsReflex2:setFetchCount(pPlayer, 0)
		FsReflex2:startQuest(pPlayer)
	elseif (screenID == "intro_quest_failed" or screenID == "beacons_not_reliable") then
		FsReflex2:restartQuest(pPlayer)
	elseif ((screenID == "intro_quest_completed" or screenID == "intro_quest_continue") and FsReflex2:getFetchCount(pPlayer) < 6 and self:hasSupplies(pPlayer)) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if pInventory ~= nil then
			local pSupplies = getContainerObjectByTemplate(pInventory, "object/tangible/item/quest/force_sensitive/fs_reflex_supply_crate.iff", false)

			if (pSupplies ~= nil) then
				SceneObject(pSupplies):destroyObjectFromWorld()
				SceneObject(pSupplies):destroyObjectFromDatabase()
			end
		end

		FsReflex2:completeSupplyFetch(pPlayer)

		if (screenID == "intro_quest_continue") then
			local fetchCount = FsReflex2:getFetchCount(pPlayer)
			clonedConversation:setDialogTextDI(6 - fetchCount)
			FsReflex2:startNextFetch(pPlayer)
		end
	end

	return pConvScreen
end

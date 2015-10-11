local ObjectManager = require("managers.object.object_manager")
local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")
local FsMedicPuzzle = require("managers.jedi.village.phase1.fs_medic_puzzle")
local QuestManager = require("managers.quest.quest_manager")

villageSivarraPhase1ConvoHandler = {  }

function villageSivarraPhase1ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 1) then
		return convoTemplate:getScreen("intro_cant_talk")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_FINISH)) then
		return convoTemplate:getScreen("intro_did_all_sets")
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
		return convoTemplate:getScreen("intro_inv_full")
	end

	local curedCount = FsMedicPuzzle:getCuredVillagerCount(pPlayer)
	if (curedCount >= 15 and QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03)) then
		return convoTemplate:getScreen("intro_completed_third_set")
	elseif (curedCount >= 10 and QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02)) then
		return convoTemplate:getScreen("intro_completed_second_set")
	elseif (curedCount >= 5 and QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01)) then
		return convoTemplate:getScreen("intro_completed_first_set")
	elseif ((QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03) and curedCount < 15) or
		(QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02) and curedCount < 10) or
		(QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01) and curedCount < 5)) then
		return convoTemplate:getScreen("intro_in_progress")
	elseif (not CreatureObject(pPlayer):hasSkill("science_medic_master")) then
		convoTemplate:getScreen("intro_not_master_medic")
	elseif (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03) and
		QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02)) then
		return convoTemplate:getScreen("intro_start_third_set")
	elseif (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02) and
		QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01)) then
		return convoTemplate:getScreen("intro_start_second_set")
	end

	return convoTemplate:getScreen("intro")
end

function villageSivarraPhase1ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "great_explain") then
		QuestManager.setCurrentQuestID(conversingPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01)
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01)
		FsMedicPuzzle:setCuredVillagerCount(conversingPlayer, 0)

		ObjectManager.withCreaturePlayerObject(conversingPlayer, function(playerObject)
			playerObject:addRewardedSchematic("object/draft_schematic/item/quest_item/fs_medic_puzzle_heal_pack.iff", 2, -1, true)
		end)
	elseif (screenID == "intro_completed_first_set") then
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01)
		VillageJediManagerCommon.unlockBranch(conversingPlayer, "force_sensitive_heightened_senses_persuasion")
	elseif (screenID == "intro_completed_second_set") then
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02)

		local pInventory = SceneObject(conversingPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pPendant = giveItem(pInventory, "object/tangible/wearables/necklace/necklace_ice_pendant.iff", -1, true)

			if (pPendant == nil) then
				CreatureObject(conversingPlayer):sendSystemMessage("Error: Unable to generate item.")
			end
		end
	elseif (screenID == "intro_completed_third_set") then
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03)
		QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_FINISH)

		local pInventory = SceneObject(conversingPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pPlant = giveItem(pInventory, "object/tangible/loot/plant_grow/plant_stage_1.iff", -1, true)

			if (pPlant == nil) then
				CreatureObject(conversingPlayer):sendSystemMessage("Error: Unable to generate item.")
			end
		end

		FsMedicPuzzle:cleanUp(conversingPlayer)
	elseif (screenID == "talk_droids_again") then
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02)
	elseif (screenID == "talk_droids_round_three") then
		QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03)
	elseif (screenID == "intro_in_progress") then
		local count = tostring(FsMedicPuzzle:getPatientsLeftToTreat(conversingPlayer))
		clonedConversation:setDialogTextTO(count)
	end

	return conversationScreen
end

function villageSivarraPhase1ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

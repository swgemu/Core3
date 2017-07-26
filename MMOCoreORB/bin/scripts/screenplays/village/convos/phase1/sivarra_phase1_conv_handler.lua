local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageSivarraPhase1ConvoHandler = conv_handler:new {}

function villageSivarraPhase1ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 1 or not VillageJediManagerCommon.isVillageEligible(pPlayer)) then
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
		return convoTemplate:getScreen("intro_not_master_medic")
	elseif (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03) and
		QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02)) then
		return convoTemplate:getScreen("intro_start_third_set")
	elseif (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02) and
		QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01)) then
		return convoTemplate:getScreen("intro_start_second_set")
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer) or VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_another_quest")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageSivarraPhase1ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "great_explain") then
		QuestManager.setCurrentQuestID(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01)
		FsMedicPuzzle:setCuredVillagerCount(pPlayer, 0)
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE1_SIVARRA)

		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			PlayerObject(pGhost):addRewardedSchematic("object/draft_schematic/item/quest_item/fs_medic_puzzle_heal_pack.iff", 2, -1, true)
		end
	elseif (screenID == "intro_completed_first_set") then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01)
		VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_heightened_senses_persuasion")
	elseif (screenID == "intro_completed_second_set") then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02)

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			createLoot(pInventory, "sivarra_reward_necklace", -1, true)
		end
	elseif (screenID == "intro_completed_third_set") then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03)
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_FINISH)

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pPlant = giveItem(pInventory, "object/tangible/loot/plant_grow/plant_stage_1.iff", -1, true)

			if (pPlant == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
			end
		end
		VillageJediManagerCommon.setCompletedQuestThisPhase(pPlayer)
		FsMedicPuzzle:cleanUp(pPlayer)
	elseif (screenID == "talk_droids_again") then
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02)
	elseif (screenID == "talk_droids_round_three") then
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03)
	elseif (screenID == "intro_in_progress") then
		local count = tostring(FsMedicPuzzle:getPatientsLeftToTreat(pPlayer))
		clonedConversation:setDialogTextTO(count)
	end

	return pConvScreen
end

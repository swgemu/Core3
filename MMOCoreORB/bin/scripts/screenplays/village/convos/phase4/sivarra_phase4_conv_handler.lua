local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageSivarraPhase4ConvoHandler = conv_handler:new {}

function villageSivarraPhase4ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local healCount = FsVillageDefense:getVillageHealingCount(pPlayer)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (VillageJediManagerTownship:getCurrentPhase() ~= 4 or not VillageJediManagerCommon.isVillageEligible(pPlayer)) then
		return convoTemplate:getScreen("intro_not_eligible")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_FINISH)) then
		return convoTemplate:getScreen("intro_completed_quest")
	elseif ((QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1) and healCount < 50) or (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_2) and healCount < 100)) then
		return convoTemplate:getScreen("intro_in_progress")
	elseif (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
		return convoTemplate:getScreen("intro_full_inventory")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_2) and healCount >= 100) then
		return convoTemplate:getScreen("intro_give_second_set_reward")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1) and healCount >= 50) then
		return convoTemplate:getScreen("intro_give_first_set_reward")
	elseif (not CreatureObject(pPlayer):hasSkill("science_medic_novice")) then
		return convoTemplate:getScreen("intro_has_no_medic")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1)) then
		return convoTemplate:getScreen("intro_start_second_set")
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer) or VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_otherquest")
	else
		return convoTemplate:getScreen("intro_begin")
	end
end

function villageSivarraPhase4ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "intro_in_progress") then
		local healCount = FsVillageDefense:getVillageHealingCount(pPlayer)

		local stringTO
		if healCount == 0 then
			stringTO = getStringId("@quest/force_sensitive/fs_medic:combat_healing_just_started")
		else
			stringTO = getStringId("@quest/force_sensitive/fs_medic:combat_healing_count_part1") .. " " .. healCount .. " " .. getStringId("@quest/force_sensitive/fs_medic:combat_healing_count_part2")
		end
		clonedConversation:setDialogTextTO(stringTO)
	elseif (screenID == "intro_give_second_set_reward") then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_2)
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_FINISH)

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pSculpture = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/bacta_tank.iff", -1, true)

			if (pSculpture == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
			end
		end

	elseif (screenID == "intro_give_first_set_reward") then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_1)
		VillageJediManagerCommon.unlockBranch(pPlayer, "force_sensitive_heightened_senses_healing")
	elseif (screenID == "choose_certain") then
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE4_SIVARRA)
		FsVillageDefense:acceptHealingQuest(pPlayer)
	elseif (screenID == "choose_continue") then
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_COMBAT_HEALING_2)
	end

	return pConvScreen
end

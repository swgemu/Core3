local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageDageerinPhase3ConvoHandler = conv_handler:new {}

function villageDageerinPhase3ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (FsSad2:hasActiveReturnTask(pPlayer)) then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTQUESTTASK)
		end
	end

	if (VillageJediManagerTownship:getCurrentPhase() ~= 3 or not VillageJediManagerCommon.isVillageEligible(pPlayer)) then
		return convoTemplate:getScreen("intro_not_eligible")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_FINISH)) then
		return convoTemplate:getScreen("intro_completed_quest")
	elseif ((FsSad2:hasActiveNonReturnTask(pPlayer) or FsSad2:hasActiveReturnTask(pPlayer)) and not SuiRadiationSensor:hasSensor(pPlayer)) then
		return convoTemplate:getScreen("intro_need_new_sensor")
	elseif (FsSad2:hasActiveNonReturnTask(pPlayer)) then
		return convoTemplate:getScreen("intro_on_task")
	elseif (FsSad2:hasActiveReturnTask(pPlayer) and FsSad2:hasExceededLimit(pPlayer)) then
		return convoTemplate:getScreen("intro_max_tasks_for_day")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN1)) then
		return convoTemplate:getScreen("intro_completed_one")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN2)) then
		return convoTemplate:getScreen("intro_completed_two")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN3)) then
		return convoTemplate:getScreen("intro_completed_three")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN4)) then
		return convoTemplate:getScreen("intro_completed_four")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN5)) then
		return convoTemplate:getScreen("intro_completed_five")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN6)) then
		return convoTemplate:getScreen("intro_completed_six")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN7)) then
		return convoTemplate:getScreen("intro_completed_seven")
	elseif (QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_QUESTS_SAD2_RETURN8)) then
		if (FsSad2:hasFullInventory(pPlayer)) then
			return convoTemplate:getScreen("intro_full_inventory")
		else
			return convoTemplate:getScreen("intro_reward")
		end
	elseif (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_completed_other_quest")
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_other_quest")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageDageerinPhase3ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "good_luck" or screenID == "intro_need_new_sensor") then
		SuiRadiationSensor:giveSensor(pPlayer)

		if (screenID == "intro_need_new_sensor") then
			FsSad2:despawnCamp(pPlayer)
			FsSad2:recreateCampIfDespawned(pPlayer)
		elseif (screenID == "good_luck") then
			FsSad2:acceptNextTask(pPlayer)
		end
	elseif (screenID == "intro_max_tasks_for_day") then
		FsSad2:despawnCamp(pPlayer)
	elseif (screenID == "come_back_when_eliminated" or screenID == "intro_reward") then
		FsSad2:acceptNextTask(pPlayer)
	elseif (screenID == "intro_on_task") then
		SuiRadiationSensor:giveSensor(pPlayer)
		FsSad2:despawnCamp(pPlayer)
		FsSad2:recreateCampIfDespawned(pPlayer)
	end

	return pConvScreen
end

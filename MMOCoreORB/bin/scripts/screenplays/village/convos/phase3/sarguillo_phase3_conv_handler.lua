local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageSarguilloPhase3ConvoHandler = conv_handler:new {}

function villageSarguilloPhase3ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (VillageJediManagerTownship:getCurrentPhase() ~= 3 or not VillageJediManagerCommon.isVillageEligible(pPlayer)) then
		return convoTemplate:getScreen("intro_not_available")
	elseif (QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CS_QUEST_DONE)) then
		return convoTemplate:getScreen("intro_not_available")
	elseif (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_completed_other_quest")
	elseif (FsCounterStrike:isOnQuest(pPlayer)) then
		return convoTemplate:getScreen("intro")
	elseif (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return convoTemplate:getScreen("intro_has_other_quest")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageSarguilloPhase3ConvoHandler:canTurnInDatapad(pPlayer, datapadTemplate)
	local pInventory =  CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return false
	end

	local pDatapad = getContainerObjectByTemplate(pInventory, datapadTemplate, true)

	if (pDatapad == nil) then
		return false
	end

	local csItem = LuaFsCsObject(pDatapad)

	return csItem:getDecayPercent() < 100
end

function villageSarguilloPhase3ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "intro") then
		if (not FsCounterStrike:isOnQuest(pPlayer)) then
			clonedConversation:addOption("@conversation/combat_quest_p3:s_43c7c81c", "crucial_information")
			clonedConversation:addOption("@conversation/combat_quest_p3:s_ab0e6060", "if_still_interested")
		end
		if (self:canTurnInDatapad(pPlayer, "object/tangible/loot/quest/force_sensitive/camp_frequency_datapad.iff")) then
			clonedConversation:addOption("@conversation/combat_quest_p3:s_d403b674", "here_is_remote")
		end
		if (self:canTurnInDatapad(pPlayer, "object/tangible/loot/quest/force_sensitive/camp_waypoint_datapad.iff")) then
			clonedConversation:addOption("@conversation/combat_quest_p3:s_5d6c3f37", "simple_encryption")
		end
		if (FsCounterStrike:isOnQuest(pPlayer)) then
			clonedConversation:addOption("@conversation/combat_quest_p3:s_f3864fa4", "work_with_friend")
		end
	elseif (screenID == "excellent") then
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE3_SARGUILLO)
		FsCounterStrike:startQuest(pPlayer)
	elseif (screenID == "here_is_remote") then
		FsCounterStrike:giveCampRemote(pPlayer)
	elseif (screenID == "simple_encryption") then
		FsCounterStrike:giveCampWaypoint(pPlayer)
	end

	return pConvScreen
end

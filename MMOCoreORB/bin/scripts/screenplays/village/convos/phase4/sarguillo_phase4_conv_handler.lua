local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageSarguilloPhase4ConvoHandler = conv_handler:new {}

function villageSarguilloPhase4ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (FsVillageDefense:hasCompletedSarguilloQuest(pPlayer)) then
		return convoTemplate:getScreen("update_all_done")
	elseif (FsVillageDefense:completedSarguilloQuestPercent(pPlayer) >= .5) then
		return convoTemplate:getScreen("update_back_for_more")
	elseif (FsVillageDefense:hasActiveSarguilloQuest(pPlayer)) then
		return convoTemplate:getScreen("quest_in_progress")
	elseif (FsVillageDefense:canAcceptSarguilloQuest(pPlayer)) then
		return convoTemplate:getScreen("intro_begin")
	else
		return convoTemplate:getScreen("intro_has_otherquest")
	end
end

function villageSarguilloPhase4ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "intro_begin") then
		if (FsVillageDefense:canAcceptRangedQuest(pPlayer) and VillageJediManagerCommon.isVillageEligible(pPlayer)) then
			clonedConversation:addOption("@conversation/defend_the_village:s_6e8bed18", "choose_ranged")
		end
		
		if (FsVillageDefense:canAcceptMeleeQuest(pPlayer) and VillageJediManagerCommon.isVillageEligible(pPlayer)) then
			clonedConversation:addOption("@conversation/defend_the_village:s_95fe56b2", "choose_melee")
		end
		
		clonedConversation:addOption("@conversation/defend_the_village:s_64cad97c", "choose_neither")
	elseif (screenID == "fantastic_accept_ranged" or screenID == "accept_quest_ranged") then
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE4_SARGUILLO_CP)
		FsVillageDefense:acceptRangedQuest(pPlayer)
	elseif (screenID == "fantastic_accept_melee" or screenID == "accept_quest_melee") then
		VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE4_SARGUILLO_ER)
		FsVillageDefense:acceptMeleeQuest(pPlayer)
	end

	return pConvScreen
end

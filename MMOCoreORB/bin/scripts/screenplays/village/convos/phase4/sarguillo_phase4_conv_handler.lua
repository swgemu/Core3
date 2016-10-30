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

	if (screenID == "fantastic_accept_ranged" or screenID == "accept_quest_ranged") then
		FsVillageDefense:acceptRangedQuest(pPlayer)
	elseif (screenID == "fantastic_accept_melee" or screenID == "accept_quest_melee") then
		FsVillageDefense:acceptMeleeQuest(pPlayer)
	end

	return pConvScreen
end

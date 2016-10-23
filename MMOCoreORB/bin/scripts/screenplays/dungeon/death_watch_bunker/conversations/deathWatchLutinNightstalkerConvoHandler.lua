local ObjectManager = require("managers.object.object_manager")

deathWatchLutinNightstalkerConvoHandler = conv_handler:new {}

function deathWatchLutinNightstalkerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):isOnLeave() or not CreatureObject(pPlayer):isRebel()) then
		return convoTemplate:getScreen("wrong_faction")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(4, "death_watch_bunker_rebel_sidequest")) then
		return convoTemplate:getScreen("quest_already_completed")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest")) then
		return convoTemplate:getScreen("return_intro")
	else
		return convoTemplate:getScreen("intro")
	end

end

function deathWatchLutinNightstalkerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "excellent_travel_to_bunker") then
		CreatureObject(pPlayer):setScreenPlayState(1, "death_watch_bunker_rebel_sidequest")
	elseif (screenID == "return_intro") then
		if (CreatureObject(pPlayer):hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest")) then
			clonedConversation:addOption("@conversation/death_watch_rebel_herald:s_9b06da0", "excellent_reward")
		end
		clonedConversation:addOption("@conversation/death_watch_rebel_herald:s_dc839e59", "please_be_quick")
		clonedConversation:addOption("@conversation/death_watch_rebel_herald:s_6f2c6f44", "more_information")
		clonedConversation:addOption("@conversation/death_watch_rebel_herald:s_f70821a3", "this_distresses_me")
	elseif (screenID == "this_distresses_me") then
		CreatureObject(pPlayer):removeScreenPlayState(1, "death_watch_bunker_rebel_sidequest")
		CreatureObject(pPlayer):removeScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
	elseif (screenID == "excellent_reward") then
		PlayerObject(pGhost):increaseFactionStanding("rebel", 30)
		CreatureObject(pPlayer):setScreenPlayState(4, "death_watch_bunker_rebel_sidequest")
	end

	return pConvScreen
end

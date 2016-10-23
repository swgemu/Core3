local ObjectManager = require("managers.object.object_manager")

deathWatchCommanderDkrnConvoHandler = conv_handler:new {}

function deathWatchCommanderDkrnConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):isOnLeave() or not CreatureObject(pPlayer):isImperial()) then
		return convoTemplate:getScreen("wrong_faction")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(2, "death_watch_bunker_imperial_sidequest")) then
		return convoTemplate:getScreen("quest_already_completed")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "death_watch_bunker_imperial_sidequest")) then
		return convoTemplate:getScreen("return_intro")
	else
		return convoTemplate:getScreen("intro")
	end
end

function deathWatchCommanderDkrnConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "good_now_go") then
		CreatureObject(pPlayer):setScreenPlayState(1, "death_watch_bunker_imperial_sidequest")
	elseif (screenID == "return_intro") then
		local pInventory =  CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pSample = getContainerObjectByTemplate(pInventory, "object/tangible/loot/dungeon/death_watch_bunker/blood_vial.iff", true)
			if (pSample ~= nil) then
				clonedConversation:addOption("@conversation/death_watch_imperial_herald:s_4f1e472e", "excellent_reward")
			end
		end
		clonedConversation:addOption("@conversation/death_watch_imperial_herald:s_dc839e59", "very_well_be_quick")
		clonedConversation:addOption("@conversation/death_watch_imperial_herald:s_55aa1278", "more_info")
		clonedConversation:addOption("@conversation/death_watch_imperial_herald:s_f70821a3", "sorry_to_hear")
	elseif (screenID == "sorry_to_hear") then
		CreatureObject(pPlayer):removeScreenPlayState(1, "death_watch_bunker_imperial_sidequest")
	elseif (screenID == "excellent_reward") then
		PlayerObject(pGhost):increaseFactionStanding("imperial", 500)
		CreatureObject(pPlayer):setScreenPlayState(2, "death_watch_bunker_imperial_sidequest")
	end

	return pConvScreen
end

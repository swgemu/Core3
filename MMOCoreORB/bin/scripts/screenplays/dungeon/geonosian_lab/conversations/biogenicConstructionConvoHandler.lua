local ObjectManager = require("managers.object.object_manager")

BiogenicContructionConvoHandler = conv_handler:new {}

function BiogenicContructionConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "get_wits_back" or screenID == "dont_have_much" or screenID == "excavating_passage" or screenID == "getting_out_too") then
		if (CreatureObject(pPlayer):hasScreenPlayState(1, "geonosian_lab_datapad_delivered")) then
			clonedConversation:addOption("@conversation/biogenic_construction:s_5fe23666", "bye_good_luck")
		else
			clonedConversation:addOption("@conversation/biogenic_construction:s_5fe23666", "bye_check_engineering")
		end
	elseif (screenID == "bye_check_engineering") then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geo_construction_talked", 1)
	end

	return pConvScreen
end

function BiogenicContructionConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local hasTalked = readData(CreatureObject(pPlayer):getObjectID() .. ":geo_construction_talked")

	if (CreatureObject(pPlayer):hasScreenPlayState(1, "geonosian_lab_datapad_delivered")) then
		return convoTemplate:getScreen("intro_assistant_done")
	elseif (hasTalked ~= nil and hasTalked == 1) then
		return convoTemplate:getScreen("intro_check_engineering")
	end

	return convoTemplate:getScreen("intro")
end

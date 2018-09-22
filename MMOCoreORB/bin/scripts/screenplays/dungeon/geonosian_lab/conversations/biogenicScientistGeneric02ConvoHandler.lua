local ObjectManager = require("managers.object.object_manager")

BiogenicScientistGeneric02ConvoHandler = conv_handler:new {}

function BiogenicScientistGeneric02ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "in_your_debt") then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geo_generic_02_talked", 1)
	elseif (screenID == "we_created_problem") then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geo_generic_02_talked", 2)
	end

	return pConvScreen
end

function BiogenicScientistGeneric02ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local hasTalked = readData(CreatureObject(pPlayer):getObjectID() .. ":geo_generic_02_talked")

	if (hasTalked == nil or hasTalked == 0) then
		return convoTemplate:getScreen("init_talk")
	elseif (hasTalked == 1) then
		return convoTemplate:getScreen("init_helping")
	elseif (hasTalked == 2) then
		return convoTemplate:getScreen("init_not_helping")
	end

	return convoTemplate:getScreen("init_talk")
end

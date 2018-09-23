local ObjectManager = require("managers.object.object_manager")

BiogenicScientistGeneric02ConvoHandler = conv_handler:new {}

function BiogenicScientistGeneric02ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "in_your_debt") then
<<<<<<< Updated upstream
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geo_generic_02_talked", 1)
	elseif (screenID == "we_created_problem") then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geo_generic_02_talked", 2)
=======
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geoGeneric02State", 1)
	elseif (screenID == "we_created_problem") then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geoGeneric02State", 2)
>>>>>>> Stashed changes
	end

	return pConvScreen
end

function BiogenicScientistGeneric02ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
<<<<<<< Updated upstream
	local hasTalked = readData(CreatureObject(pPlayer):getObjectID() .. ":geo_generic_02_talked")

	if (hasTalked == nil or hasTalked == 0) then
		return convoTemplate:getScreen("init_talk")
	elseif (hasTalked == 1) then
		return convoTemplate:getScreen("init_helping")
	elseif (hasTalked == 2) then
=======
	local convoState = readData(CreatureObject(pPlayer):getObjectID() .. ":geoGeneric02State")

	if (convoState == nil or convoState == 0) then
		return convoTemplate:getScreen("init_talk")
	elseif (convoState == 1) then
		return convoTemplate:getScreen("init_helping")
	elseif (convoState == 2) then
>>>>>>> Stashed changes
		return convoTemplate:getScreen("init_not_helping")
	end

	return convoTemplate:getScreen("init_talk")
end

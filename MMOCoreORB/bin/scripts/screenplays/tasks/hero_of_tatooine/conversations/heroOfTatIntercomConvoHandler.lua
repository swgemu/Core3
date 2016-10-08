local ObjectManager = require("managers.object.object_manager")

heroOfTatIntercomConvoHandler = conv_handler:new {}

function heroOfTatIntercomConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local playerID = CreatureObject(pPlayer):getObjectID()
	local inProgressID = readData("hero_of_tat:ranch_player_id")
	if (inProgressID ~= 0 and inProgressID ~= playerID) then
		return convoTemplate:getScreen("intro_noquest")
	elseif (readData(playerID .. ":hero_of_tat_honor:accepted") == 1) then
		if (readData(playerID .. ":hero_of_tat_honor:distract_wife") == 1) then
			return convoTemplate:getScreen("intro_alreadytalked")
		else
			return convoTemplate:getScreen("intro")
		end
	else
		return convoTemplate:getScreen("intro_noquest")
	end
end

function heroOfTatIntercomConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "blast_it" or screenID == "go_talk_to_her") then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":hero_of_tat_honor:distracting_wife", 1)
	end

	return pConvScreen
end

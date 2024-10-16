local SpaceHelpers = require("utils.space_helpers")

jPaiBrekConvoHandler = conv_handler:new {}

function jPaiBrekConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()

	if (not SpaceHelpers:isPilot(pPlayer)) then
		if (faction ~= FACTIONREBEL) then
			return convoTemplate:getScreen("nothing_i_can")
		else
			return convoTemplate:getScreen("is_there_something")
		end
	elseif (faction ~= FACTIONREBEL or CreatureObject(pPlayer):getFactionStatus() < COVERT) then
		return convoTemplate:getScreen("i_said_good")
	end

	-- Player is a rebel pilot
	return convoTemplate:getScreen("hello_friend_its")
end

function jPaiBrekConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local stringFile = "@conversation/rebel_broker"
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	return pConvScreen
end


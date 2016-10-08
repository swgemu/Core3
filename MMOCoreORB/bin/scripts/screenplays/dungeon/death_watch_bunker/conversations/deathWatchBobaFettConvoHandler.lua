local ObjectManager = require("managers.object.object_manager")

deathWatchBobaFettConvoHandler = conv_handler:new {}

function deathWatchBobaFettConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "dont_give_opinions") then
		CreatureObject(pPlayer):setScreenPlayState(1, "death_watch_bunker")
	end

	return pConvScreen
end

function deathWatchBobaFettConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, "death_watch_bunker")) then
		return convoTemplate:getScreen("back_again")
	else
		return convoTemplate:getScreen("intro")
	end
end

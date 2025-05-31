local SpaceHelpers = require("utils.space_helpers")

tutorialImperialBrokerConvoHandler = conv_handler:new {}

function tutorialImperialBrokerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()

	-- Black Epsilon
	if (screenID == "more_black_epsilon") then
		SpaceHelpers:addBlackEpsilonSquadWaypoint(pPlayer)

	-- Storm Squadron
	elseif (screenID == "more_storm") then
		SpaceHelpers:addStormSquadWaypoint(pPlayer)

	-- Imperial Inquisition
	elseif (screenID == "more_inquisition") then
		SpaceHelpers:addImperialInquisitionSquadWaypoint(pPlayer)
	end

	return pConvScreen
end

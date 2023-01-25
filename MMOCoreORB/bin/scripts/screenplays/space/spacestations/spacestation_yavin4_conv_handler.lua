local Logger = require("utils.logger")
require("utils.helpers")

spacestation_yavin4_conv_handler = Object:new {
}

function spacestation_yavin4_conv_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	lastConversation = nil
	local conversation = LuaConversationTemplate(conversationTemplate)
	local nextConversationScreen

	if (conversation ~= nil) then
		if (convosession ~= nil) then
			local session = LuaConversationSession(convosession)
			if (session ~= nil) then
				lastConversationScreen = session:getLastConversationScreen()
			end
		end
	end

	if (lastConversationScreen == nil) then
		nextConversationScreen = conversation:getScreen("spacestation_yavin4_greeting")
	else
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		nextConversationScreen = conversation:getScreen(optionLink)

	end

	return nextConversationScreen
end

function spacestation_yavin4_conv_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local player = LuaSceneObject(conversingPlayer)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()

	local pShip = SceneObject(conversingPlayer):getParent()

	if (pShip == nil or not SceneObject(pShip):isShipObject()) then
		return pConvScreen
	end

	if (screenID == "spacestation_yavin4_land_mining_land") then
		createEvent(1 * 1000, "SpaceStationScreenPlay", "landShip", conversingPlayer, "yavin4_mining")

	elseif (screenID == "spacestation_yavin4_land_labor_land") then
		createEvent(1 * 1000, "SpaceStationScreenPlay", "landShip", conversingPlayer, "labor")

	elseif (screenID == "spacestation_yavin4_land_imperial_land") then
		createEvent(1 * 1000, "SpaceStationScreenPlay", "landShip", conversingPlayer, "yavin4_imperial")
	end

	return pConvScreen
end

local Logger = require("utils.logger")
require("utils.helpers")

spacestation_rori_conv_handler = Object:new {}

function spacestation_rori_conv_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
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
		nextConversationScreen = conversation:getScreen("spacestation_rori_greeting")
	else
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		nextConversationScreen = conversation:getScreen(optionLink)

	end

	return nextConversationScreen
end

function spacestation_rori_conv_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local player = LuaSceneObject(conversingPlayer)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()

	local pShip = SceneObject(conversingPlayer):getParent()

	if (pShip == nil or not SceneObject(pShip):isShipObject()) then
		return pConvScreen
	end

	if (screenID == "spacestation_rori_land_narmle_complete") then
		createEvent(1 * 1000, "SpaceStationScreenPlay", "landShip", conversingPlayer, "narmle")

	elseif (screenID == "spacestation_rori_land_restuss_complete") then
		createEvent(1 * 1000, "SpaceStationScreenPlay", "landShip", conversingPlayer, "restuss")
	end

	return pConvScreen
end

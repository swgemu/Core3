local Logger = require("utils.logger")
require("utils.helpers")

spacestation_corellia_conv_handler = Object:new {}

function spacestation_corellia_conv_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
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
		nextConversationScreen = conversation:getScreen("spacestation_corellia_greeting")
	else
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		nextConversationScreen = conversation:getScreen(optionLink)

	end

	return nextConversationScreen
end

function spacestation_corellia_conv_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local player = LuaSceneObject(conversingPlayer)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	clonedConversation:setDialogTextTU(CreatureObject(conversingPlayer):getFirstName())

	if (screenID == "spacestation_corellia_land_coronet_complete") then
		createEvent(1 * 1000, "SpaceStationScreenPlay", "landShip", conversingPlayer, "coronet")

	elseif (screenID == "spacestation_corellia_land_kor_vella_complete") then
		createEvent(1 * 1000, "SpaceStationScreenPlay", "landShip", conversingPlayer, "kor_vella")

	elseif (screenID == "spacestation_corellia_land_doaba_guerfel_complete") then
		createEvent(1 * 1000, "SpaceStationScreenPlay", "landShip", conversingPlayer, "doaba_guerfel")

	elseif (screenID == "spacestation_corellia_land_tyrena_complete") then
		createEvent(1 * 1000, "SpaceStationScreenPlay", "landShip", conversingPlayer, "tyrena")
	end

	return pConvScreen
end

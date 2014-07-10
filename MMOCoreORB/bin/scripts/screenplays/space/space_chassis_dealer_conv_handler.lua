local Logger = require("utils.logger")
require("utils.helpers")
local ChassisDealer = require("screenplays.space.chassis_dealer")

chassis_dealer_conv_handler = Object:new{ }

function chassis_dealer_conv_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()

	local lastConversationScreen = nil

	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end

	local conversation = LuaConversationTemplate(conversationTemplate)

	local nextConversationScreen

	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)

		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)

		nextConversationScreen = conversation:getScreen(optionLink)

		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
		else
			nextConversationScreen = conversation:getScreen("init")
		end
	else
		nextConversationScreen = conversation:getScreen("init")
	end
	return nextConversationScreen

end

function chassis_dealer_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)

	local screenID = screen:getScreenID()

	if (screenID == "init") then
		pConversationScreen = chassis_dealer_conv_handler.handleInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif (screenID == "chassis_dealer_buy_chassis") then
		local creo = LuaSceneObject(pConversingPlayer)
		local inventory = creo:getSlottedObject("inventory")

		local pBlueprint = ChassisDealer.getValidBlueprints(pConversingPlayer)
		local blueprint = LuaSceneObject(pBlueprint)

		Logger:log("Calling getChassisFromBlueprint for " .. pBlueprint, LT_INFO)

		local pChassis = ChassisDealer.getChassisFromBlueprint(pBlueprint)
		local chassis = giveItem(inventory, pChassis, -1)

		if (chassis ~= nil) then
			local ochassis = LuaSceneObject(chassis)
			ochassis:sendTo(pConversingPlayer)
		end

		if (blueprint ~= nil) then
			blueprint:destroyObjectFromWorld()
			blueprint:destroyObjectFromDatabase()
		end
	end

	return pConversationScreen
end

function chassis_dealer_conv_handler.handleInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	local nextScreen = nil

	-- See if they have blueprints.
	if (ChassisDealer.playerHasValidBlueprints(pConversingPlayer) == true) then
		nextScreen = "chassis_dealer_buy_chassis"
	elseif (ChassisDealer.playerHasValidBlueprints(pConversingPlayer) == false) then
		nextScreen = "chassis_dealer_no_blueprint"
	end

	return conversationTemplate:getScreen(nextScreen)
end

local Logger = require("utils.logger")
require("utils.helpers")

SpacestationYavin4ConvoHandler = Object:new {}

function SpacestationYavin4ConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption)
	if (pPlayer == nil or pConvTemplate == nil) then
		return
	end

	local pConvoSession = CreatureObject(pPlayer):getConversationSession()
	local pConversation = LuaConversationTemplate(pConvTemplate)

	if (pConversation == nil)  then
		return
	end

	local pLastScreen
	local pNextScreen

	if (pConvoSession ~= nil) then
		pLastScreen = LuaConversationSession(pConvoSession):getLastConversationScreen()
	end

	if (pLastScreen ~= nil) then
		local pOptionLink = LuaConversationScreen(pLastScreen):getOptionLink(selectedOption)

		if (pOptionLink ~= nil) then
			pNextScreen = pConversation:getScreen(pOptionLink)
		end
	end

	if (pNextScreen == nil) then
		pNextScreen = pConversation:getScreen("spacestation_yavin4_greeting")
	end

	return pNextScreen
end

function SpacestationYavin4ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pScreenClone = screen:cloneScreen()
	local pClonedConvo = LuaConversationScreen(pScreenClone)

	pClonedConvo:setDialogTextTU(CreatureObject(pPlayer):getFirstName())

	local pShip = SceneObject(pPlayer):getRootParent()

	if (pShip == nil or not SceneObject(pShip):isShipObject()) then
		return
	end

	if (screenID == "spacestation_yavin4_land_mining_land") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "yavin4_mining")
	elseif (screenID == "spacestation_yavin4_land_labor_land") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "labor")
	elseif (screenID == "spacestation_yavin4_land_imperial_land") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "yavin4_imperial")
	end

	return pScreenClone
end

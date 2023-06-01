local Logger = require("utils.logger")
require("utils.helpers")

SpacestationDantooineConvoHandler = Object:new {}

function SpacestationDantooineConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption)
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
		pNextScreen = pConversation:getScreen("spacestation_dantooine_greeting")
	end

	return pNextScreen
end

function SpacestationDantooineConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	if (screenID == "spacestation_dantooine_land_mining_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "dantooine_mining")
	elseif (screenID == "spacestation_dantooine_land_agro_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "agro")
	elseif (screenID == "spacestation_dantooine_land_imperial_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "dantooine_imperial")
	elseif (screenID == "spacestation_dantooine_land_rebel_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "abandoned_rebel")
	end

	return pScreenClone
end

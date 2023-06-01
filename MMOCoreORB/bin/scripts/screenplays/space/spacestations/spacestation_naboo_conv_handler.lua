local Logger = require("utils.logger")
require("utils.helpers")

SpacestationNabooConvoHandler = Object:new {}

function SpacestationNabooConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption)
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
		pNextScreen = pConversation:getScreen("spacestation_naboo_greeting")
	end

	return pNextScreen
end

function SpacestationNabooConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	if (screenID == "spacestation_naboo_land_theed_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "theed")
	elseif (screenID == "spacestation_naboo_land_kaadara_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "kaadara")
	elseif (screenID == "spacestation_naboo_land_keren_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "keren")
	elseif (screenID == "spacestation_naboo_land_moenia_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "moenia")
	end

	return pScreenClone
end

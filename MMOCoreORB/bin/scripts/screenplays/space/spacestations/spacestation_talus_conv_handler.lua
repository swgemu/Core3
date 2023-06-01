local Logger = require("utils.logger")
require("utils.helpers")

SpacestationTalusConvoHandler = Object:new {}

function SpacestationTalusConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption)
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
		pNextScreen = pConversation:getScreen("spacestation_talus_greeting")
	end

	return pNextScreen
end

function SpacestationTalusConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	if (screenID == "spacestation_talus_land_dearic_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "dearic")
	elseif (screenID == "spacestation_talus_land_nashal_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "nashal")
	elseif (screenID == "spacestation_talus_land_imperial_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "talus_imperial")
	end

	return pScreenClone
end

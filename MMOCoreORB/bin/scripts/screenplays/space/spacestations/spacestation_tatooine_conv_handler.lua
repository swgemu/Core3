local Logger = require("utils.logger")
require("utils.helpers")

SpacestationTatooineConvoHandler = Object:new {}

function SpacestationTatooineConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption)
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
		pNextScreen = pConversation:getScreen("spacestation_tatooine_greeting")
	end

	return pNextScreen
end

function SpacestationTatooineConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	if (screenID == "spacestation_tatooine_land_bestine_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "bestine")
	elseif (screenID == "spacestation_tatooine_land_eisley_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "eisley")
	elseif (screenID == "spacestation_tatooine_land_espa_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "espa")
	elseif (screenID == "spacestation_tatooine_land_entha_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "entha")
	end

	return pScreenClone
end

local Logger = require("utils.logger")
require("utils.helpers")

SpacestationCorelliaConvoHandler = Object:new {}

function SpacestationCorelliaConvoHandler:getNextConversationScreen(pConvTemplate, pPlayer, selectedOption)
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
		pNextScreen = pConversation:getScreen("spacestation_corellia_greeting")
	end

	return pNextScreen
end

function SpacestationCorelliaConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	if (screenID == "spacestation_corellia_land_coronet_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "coronet")
	elseif (screenID == "spacestation_corellia_land_kor_vella_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "kor_vella")
	elseif (screenID == "spacestation_corellia_land_doaba_guerfel_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "doaba_guerfel")
	elseif (screenID == "spacestation_corellia_land_tyrena_complete") then
		createEvent(1000, "SpaceStationScreenPlay", "landShip", pPlayer, "tyrena")
	end

	return pScreenClone
end

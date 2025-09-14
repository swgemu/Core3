local Logger = require("utils.logger")
require("utils.helpers")

SpacestationRebelConvoHandler = conv_handler:new {}

function SpacestationRebelConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil or pConvTemplate == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pShip = SceneObject(pPlayer):getRootParent()

	if (pShip == nil or not SceneObject(pShip):isShipObject()) then
		return
	end

	if (not SceneObject(pShip):checkInConversationRange(pNpc)) then
		return convoTemplate:getScreen("out_of_range")
	end

	if (TangibleObject(pPlayer):isImperial()) then
		return convoTemplate:getScreen("spacestation_imperial_greeting")
	end

	if (not TangibleObject(pPlayer):isRebel()) then
		return convoTemplate:getScreen("spacestation_neutral_greeting")
	end

	return convoTemplate:getScreen("spacestation_rebel_greeting")
end

function SpacestationRebelConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	-- Only show request repairs if the player has enough credits for the smallest repair
	if (screenID == "spacestation_rebel_declare") then
		createEvent((30 * 1000), "SpaceHelpers", "declareOvert", pShip, "rebel")
	end

	return pScreenClone
end

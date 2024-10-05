local Logger = require("utils.logger")
require("utils.helpers")

SpacestationLokConvoHandler = conv_handler:new {}

function SpacestationLokConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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


	return convoTemplate:getScreen("spacestation_lok_greeting")
end

function SpacestationLokConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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
	if (screenID == "spacestation_lok_greeting" and SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.25)) then
		pClonedConvo:addOption("@conversation/station_lok:s_6c8ffad8", "spacestation_lok_repair") --I need repairs.
	end

	-- Handle Landing
	if (screenID == "spacestation_lok_land_nym_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "nym")
	end

	-- Handle Repair Options
	if (screenID == "spacestation_lok_repair") then
		-- We already checked if player has enough credits for at least 25% repair, add that option
		pClonedConvo:addOption("@conversation/station_lok:s_bf151ca2", "repair_small") -- No, just fix a little.

		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.50)) then
			pClonedConvo:addOption("@conversation/station_lok:s_c80840ca", "repair_half") -- Just fix half of it.
		end
		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.75)) then
			pClonedConvo:addOption("@conversation/station_lok:s_2d1962b", "repair_most") -- Repair most of it.
		end
		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 1.00)) then
			pClonedConvo:addOption("@conversation/station_lok:s_445607d0", "repair_full") -- Repair all of it.
		end

		pClonedConvo:addOption("@conversation/station_lok:s_169df3bb", "spacestation_lok_repair_deny") -- Never mind.
	end

	-- Repair selection
	if (screenID == "repair_small") then
		pClonedConvo:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 0.25))
	elseif (screenID == "repair_half") then
		pClonedConvo:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 0.50))
	elseif (screenID == "repair_most") then
		pClonedConvo:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 0.75))
	elseif (screenID == "repair_full") then
		pClonedConvo:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 1.0))
	end

	-- Handle Repairing Ship
	if (screenID == "accept_repair_25") then
		SpaceStationScreenPlay:repairShip(pPlayer, pShip, 0.25, pNpc, true)
	elseif (screenID == "accept_repair_50") then
		SpaceStationScreenPlay:repairShip(pPlayer, pShip, 0.50, pNpc, true)
	elseif (screenID == "accept_repair_75") then
		SpaceStationScreenPlay:repairShip(pPlayer, pShip, 0.75, pNpc, true)
	elseif (screenID == "accept_repair_full") then
		SpaceStationScreenPlay:repairShip(pPlayer, pShip, 1.0, pNpc, true)
	end

	return pScreenClone
end

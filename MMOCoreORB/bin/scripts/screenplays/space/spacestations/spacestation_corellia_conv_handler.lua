local Logger = require("utils.logger")
require("utils.helpers")

SpacestationCorelliaConvoHandler = conv_handler:new {}

function SpacestationCorelliaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	return convoTemplate:getScreen("spacestation_corellia_greeting")
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

	-- Only show request repairs if the player has enough credits for the smallest repair
	if (screenID == "spacestation_corellia_greeting" and SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.25)) then
		pClonedConvo:addOption("@conversation/station_corellia:s_c358d041", "spacestation_corellia_repair") -- (Request Repairs)
	end

	-- Handle Landing
	if (screenID == "spacestation_corellia_land_coronet_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "coronet")
	elseif (screenID == "spacestation_corellia_land_kor_vella_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "kor_vella")
	elseif (screenID == "spacestation_corellia_land_doaba_guerfel_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "doaba_guerfel")
	elseif (screenID == "spacestation_corellia_land_tyrena_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "tyrena")
	end

	-- Handle Repair Options
	if (screenID == "spacestation_corellia_repair") then
		-- We already checked if player has enough credits for at least 25% repair, add that option
		pClonedConvo:addOption("@conversation/station_corellia:s_d8f24b5b", "repair_small") -- Repair a little of the damage

		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.50)) then
			pClonedConvo:addOption("@conversation/station_corellia:s_37b5c504", "repair_half") -- Repair half the damage
		end
		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.75)) then
			pClonedConvo:addOption("@conversation/station_corellia:s_82701bb4", "repair_most") -- Repair most of the damage
		end
		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 1.00)) then
			pClonedConvo:addOption("@conversation/station_corellia:s_61071474", "repair_full") -- Repair all of the damage
		end

		pClonedConvo:addOption("@conversation/station_corellia:s_383d79b3", "spacestation_corellia_repair_deny") -- Nevermind
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

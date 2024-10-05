local Logger = require("utils.logger")
require("utils.helpers")

SpacestationTatooineConvoHandler = conv_handler:new {}

function SpacestationTatooineConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	return convoTemplate:getScreen("spacestation_tatooine_greeting")
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

	-- Only show request repairs if the player has enough credits for the smallest repair
	if (screenID == "spacestation_tatooine_greeting" and SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.25)) then
		pClonedConvo:addOption("@conversation/station_tatooine:s_6c8ffad8", "spacestation_tatooine_repair") -- (Request Repairs)
	end

	-- Handle Landing
	if (screenID == "spacestation_tatooine_land_bestine_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "bestine")
	elseif (screenID == "spacestation_tatooine_land_eisley_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "eisley")
	elseif (screenID == "spacestation_tatooine_land_espa_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "espa")
	elseif (screenID == "spacestation_tatooine_land_entha_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "entha")
	end

	-- Handle Repair Options
	if (screenID == "spacestation_tatooine_repair") then
		-- We already checked if player has enough credits for at least 25% repair, add that option
		pClonedConvo:addOption("@conversation/station_tatooine:s_696719e4", "repair_small") -- Minor repairs.

		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.50)) then
			pClonedConvo:addOption("@conversation/station_tatooine:s_6aea6f34", "repair_half") -- Repair half the damage.
		end
		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.75)) then
			pClonedConvo:addOption("@conversation/station_tatooine:s_5cf3921", "repair_most") -- Repair most of the damage.
		end
		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 1.00)) then
			pClonedConvo:addOption("@conversation/station_tatooine:s_d1076b9d", "repair_full") -- Repair all the damage.
		end

		pClonedConvo:addOption("@conversation/station_tatooine:s_da196589", "spacestation_tatooine_repair_deny") -- Nevermind.
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

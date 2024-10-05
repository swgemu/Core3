local Logger = require("utils.logger")
require("utils.helpers")

SpacestationDathomirConvoHandler = conv_handler:new {}

function SpacestationDathomirConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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


	return convoTemplate:getScreen("spacestation_dathomir_greeting")
end

function SpacestationDathomirConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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
	if (screenID == "spacestation_dathomir_greeting" and SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.25)) then
		pClonedConvo:addOption("@conversation/station_dathomir:s_797", "spacestation_dathomir_repair") -- (Request Repairs)
	end

	-- Handle Landing
	if (screenID == "spacestation_dathomir_land_trade_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "trade")
	elseif (screenID == "spacestation_dathomir_land_science_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "science")
	end

	-- Handle Repair Options
	if (screenID == "spacestation_dathomir_repair") then
		local timeNow = getTimestampMilli()
		local lastRepair = readData(SceneObject(pNpc):getObjectID() .. ":SpaceStation:repairDelay:")

		-- Timer for station repair
		if (timeNow < lastRepair) then
			local pNewScreen = LuaConversationTemplate(pConvTemplate):getScreen("repair_recent")
			LuaConversationScreen(pNewScreen):setDialogTextTU(CreatureObject(pPlayer):getFirstName())

			return pNewScreen
		end

		-- We already checked if player has enough credits for at least 25% repair, add that option
		pClonedConvo:addOption("@conversation/station_dathomir:s_841", "repair_small") -- Just a little.

		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.50)) then
			pClonedConvo:addOption("@conversation/station_dathomir:s_859", "repair_half") -- Half?
		end
		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 1.00)) then
			pClonedConvo:addOption("@conversation/station_dathomir:s_869", "repair_full") -- All of it.
		end

		pClonedConvo:addOption("@conversation/station_dathomir:s_897", "spacestation_dathomir_repair_deny") -- Never mind.
	end

	-- Repair selection
	if (screenID == "repair_small") then
		pClonedConvo:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 0.25))
	elseif (screenID == "repair_half") then
		pClonedConvo:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 0.50))
	elseif (screenID == "repair_most") then
		pClonedConvo:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 0.75))
	elseif (screenID == "repair_full") then
		-- Placeholder for quest status check
		local completedQuests = false

		if (not completedQuests) then
			local pRepairMost2 = LuaConversationTemplate(pConvTemplate):getScreen("repair_most_two")
			local pNewClone = LuaConversationScreen(pRepairMost2):cloneScreen()

			local pClonedRepairMost2 = LuaConversationScreen(pNewClone)
			pClonedRepairMost2:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 0.75))

			return pNewClone
		end

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

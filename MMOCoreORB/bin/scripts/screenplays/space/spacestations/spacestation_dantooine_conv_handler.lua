local Logger = require("utils.logger")
require("utils.helpers")

SpacestationDantooineConvoHandler = conv_handler:new {}

function SpacestationDantooineConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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


	return convoTemplate:getScreen("spacestation_dantooine_greeting")
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

	-- Only show request repairs if the player has enough credits for the smallest repair
	if (screenID == "spacestation_dantooine_greeting" and SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.25)) then
		pClonedConvo:addOption("@conversation/station_dantooine:s_54c04765", "spacestation_dantooine_repair") --I need repairs!
	end

	if (screenID == "spacestation_dantooine_land_mining_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "dantooine_mining")
	elseif (screenID == "spacestation_dantooine_land_agro_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "agro")
	elseif (screenID == "spacestation_dantooine_land_imperial_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "dantooine_imperial")
	elseif (screenID == "spacestation_dantooine_land_rebel_complete") then
		createEvent(3500, "SpaceStationScreenPlay", "landShip", pPlayer, "abandoned_rebel")
	end

	-- Handle Repair Options
	if (screenID == "spacestation_dantooine_repair") then
		local timeNow = getTimestampMilli()
		local lastRepair = readData(SceneObject(pNpc):getObjectID() .. ":SpaceStation:repairDelay:")

		-- Timer for station repair
		if (timeNow < lastRepair) then
			return LuaConversationTemplate(pConvTemplate):getScreen("repair_recent")
		end

		-- We already checked if player has enough credits for at least 25% repair, add that option
		pClonedConvo:addOption("@conversation/station_dantooine:s_90ee7f5d", "repair_small") -- Just a little.

		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 0.50)) then
			pClonedConvo:addOption("@conversation/station_dantooine:s_245c7c6d", "repair_half") -- Repair half.
		end
		if (SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, 1.00)) then
			pClonedConvo:addOption("@conversation/station_dantooine:s_70876928", "repair_full") -- All of it.
		end

		pClonedConvo:addOption("@conversation/station_dantooine:s_169df3bb", "spacestation_dantooine_repair_deny") -- Never mind.
	end

	-- Repair selection
	if (screenID == "repair_small") then
		pClonedConvo:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 0.25))
	elseif (screenID == "repair_half") then
		pClonedConvo:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 0.50))
	elseif (screenID == "repair_full") then
		pClonedConvo:setDialogTextDI(SpaceStationScreenPlay:getRepairCost(pShip, 1.0))
	end

	-- Handle Repairing Ship
	if (screenID == "accept_repair_25") then
		SpaceStationScreenPlay:repairShip(pPlayer, pShip, 0.25, pNpc, true)
	elseif (screenID == "accept_repair_50") then
		SpaceStationScreenPlay:repairShip(pPlayer, pShip, 0.50, pNpc, true)
	elseif (screenID == "accept_repair_full") then
		SpaceStationScreenPlay:repairShip(pPlayer, pShip, 1.0, pNpc, true)
	end

	return pScreenClone
end

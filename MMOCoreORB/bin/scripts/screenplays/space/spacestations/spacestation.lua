SpaceStationScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SpaceStationScreenPlay",

	DEBUG_STATION_REPAIR = false,

	REPAIR_COST = 1,
	REPAIR_DELAY = 360 * 1000, -- 6 Minutes in miliseconds

	travelPoints = {
		coronet = {"corellia", -66, 28, -4705},
		kor_vella = {"corellia", -3155, 31, 2880},
		doaba_guerfel = {"corellia", 3349, 308, 5598},
		tyrena = {"corellia", -5001, 21, -2228},
		dantooine_mining = {"dantooine", -640, 3, 2505},
		agro = {"dantooine", 1575, 4, -6420},
		dantooine_imperial = {"dantooine", -4205, 3, -2350},
		abandoned_rebel = {"dantooine", -6792, 46, 5575},
		trade = {"dathomir", 620, 7, 3090},
		science = {"dathomir", -50, 18, -1580},
		research = {"endor", 3200, 24, -3470},
		smuggler = {"endor", -950, 73, 1550},
		nym = {"lok", 480, 9, 5510},
		theed = {"naboo", -4860, 6, 4165},
		kaadara = {"naboo", 5280, -192, 6688},
		keren = {"naboo", 1370, 13, 2750},
		moenia = {"naboo", 4730, 4.2, -4678},
		narmle = {"rori", -5372, 80, -2191},
		restuss = {"rori", 5341, 80, 5735},
		dearic = {"talus", 265, 6, -2950},
		nashal = {"talus", 4452, 2, 5355},
		talus_imperial = {"talus", -2215, 20, 2305},
		bestine = {"tatooine", -1360, 12, -3600},
		eisley = {"tatooine", 3600, 5, -4785},
		espa = {"tatooine", -2835, 5, 2105},
		entha = {"tatooine", 1265, 7, 3065},
		yavin4_mining = {"yavin4", -267, 35, 4896},
		labor = {"yavin4", -6921, 73, -5726},
		yavin4_imperial = {"yavin4", 4054, 37, -6216},
	},
}

function SpaceStationScreenPlay:landShip(pPlayer, destination)
	if (pPlayer == nil or destination == nil) then
		return
	end

	local pShip = SceneObject(pPlayer):getRootParent()

	if (pShip == nil or not SceneObject(pShip):isShipObject()) then
		return
	end

	local destinationTable = self.travelPoints
	local destinationInfo = destinationTable[destination]

	-- Check if zone is disabled
	if (not isZoneEnabled(destinationInfo[1])) then
		CreatureObject(pPlayer):sendSystemMessage("You cannot land on this planet at this time.")
		return
	end

	local ownerID = ShipObject(pShip):getOwnerID()

	-- Player is the pilot of the ship or the owner
	if (CreatureObject(pPlayer):isPilotingShip() or SceneObject(pPlayer):getObjectID() == ownerID) then
		ShipObject(pShip):storeShip(pPlayer, destinationInfo[1], destinationInfo[2], destinationInfo[3], destinationInfo[4])
	else
		-- Players onboard a pob can /comm a nearby station and be transported to the ground
		SceneObject(pPlayer):switchZone(destinationInfo[1], destinationInfo[2], destinationInfo[3], destinationInfo[4], 0)
	end
end

function SpaceStationScreenPlay:hasCreditsForRepair(pPlayer, pShip, repairPercent)
	if (pPlayer == nil or pShip == nil) then
		return false
	end

	-- Calculate cost
	local totalCost = self:getRepairCost(pShip, repairPercent)

	if (totalCost <= 0) then
		return false
	end

	local playerCash = CreatureObject(pPlayer):getCashCredits()

	if (self.DEBUG_STATION_REPAIR) then
		print("hasCreditsForRepair -- Repair Percentage: " .. repairPercent .. " Total repair cost estimate = " .. totalCost .. " Player Cash Balance: " .. playerCash)
	end

	if (playerCash < totalCost) then
		return false
	end

	return true;
end

function SpaceStationScreenPlay:getRepairCost(pShip, repairPercent)
	if (pShip == nil) then
		return 0
	end

	local shipName = SceneObject(pShip):getObjectName()

	-- Get overall total damage to the ship
	local totalDamage = ShipObject(pShip):getTotalShipDamage()

	-- Adjust based on the percent chosen from conversation
	totalDamage = totalDamage * repairPercent

	local totalCost = math.floor(totalDamage * self.REPAIR_COST)

	if (string.find("basic", shipName) or string.find("prototype", shipName)) then
		totalCost = math.floor((repairPercent * 100) * self.REPAIR_COST)
	end

	if (self.DEBUG_STATION_REPAIR) then
		print("getRepairCost -- Total repair cost estimate = " .. totalCost)
	end

	return totalCost
end

function SpaceStationScreenPlay:repairShip(pPlayer, pShip, repairPercent, pSpaceStation, decay)
	if (pPlayer == nil or pShip == nil) then
		return
	end

	-- Calculate cost
	local totalCost = self:getRepairCost(pShip, repairPercent)

	if (totalCost <= 0) then
		return
	end

	local playerCash = CreatureObject(pPlayer):getCashCredits()

	if (self.DEBUG_STATION_REPAIR) then
		print("Repairing Ship -- Total Cost: " .. totalCost .. " Repair Percent: " .. repairPercent .. " Player Cash: " .. playerCash)
	end

	if (playerCash < totalCost) then
		return
	end

	-- Pass all of the information to cpp for ease of lock and trx
	ShipObject(pShip):repairShip(pPlayer, repairPercent, totalCost, decay)

	if (pSpaceStation ~= nil) then
		self:addRepairDelay(pSpaceStation)
	end
end

function SpaceStationScreenPlay:addRepairDelay(pSpaceStation)
	if (pSpaceStation == nil) then
		return
	end

	local stationID = SceneObject(pSpaceStation):getObjectID()
	local timeDelay = getTimestampMilli() + self.REPAIR_DELAY

	deleteData(stationID .. ":SpaceStation:repairDelay:")
	writeData(stationID .. ":SpaceStation:repairDelay:", timeDelay)
end

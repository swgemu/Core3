Coa3Screenplay = ScreenPlay:new {
	-- Quest Steps
	PRE_INFO_OFFICER = 1, -- Sent to info officer
	PRE_RETURN = 2, -- Return to coordinator
	M1_FIND_LOOKOUT = 3, -- Sent to lookout
	M1_SPOKE_TO_LOOKOUT = 4, -- Made Contact with lookout
	M1_TRIAL_COMPLETED = 5, -- Passed convo trial
	M1_REFUSED = 6, -- Refused to do repairs
	M2_FIND_CARAVAN_LEADER = 7, -- Sent to caravan leader
	M2_RETURNED_UNIT = 8,	-- Returned repaired grav unit
	M3_TACTICAL_OFFICER = 9, -- Sent to tactical officer
	M3_SENT_TO_WAREHOUSE = 10, -- Tactical officer sent player to flora warehouse
	M3_LOOTED_FLORA = 11, -- Flora looted
	M3_WAREHOUSE_DESTROYED = 12, -- Warehouse destroyed, return to tactical officer
	M3_COMPLETE = 13, -- Flora turned in
	M4_COMMANDER = 14, -- Sent to princess/veers
	M5_GO_TO_FACILITY = 15, -- Sent to defend facility
	M5_DEFENDING = 16, -- Defense in progress
	M5_COMPLETE = 17, -- Defense complete

	-- Missions
	LOOKOUT_MISSION = 1,
	CARAVAN_MISSION = 2,
	FLORA_MISSION = 3,
	COMMANDER_MISSION = 4,

	-- Extra Flora Missions
	FLORA_MISSION_ACCEPTED = 1,
	FLORA_WAREHOUSE_DESTROYED = 2,

	warehouseMobiles = {
		-- {template, x, z, y, cellName}
		-- room3
		{"coa3_warehouse_captain", -3.19, 0.12, -4.6, "room3"},
		{"coa3_warehouse_guard", -4.2, 0.12, -1.8, "room3"},
		-- room2
		{"coa3_warehouse_guard", 3.9, 0.12, -3.4, "room2"},
		-- room1
		{"coa3_warehouse_guard", 3.6, 0.12, 1.3, "room1"},
		{"coa3_warehouse_thug", 3.7, 0.12, 3.6, "room1"},
		-- Outside
		{"coa3_warehouse_thug", -4.8, 0, 10.0, ""},
		{"coa3_warehouse_thug", 4.8, 0, 10.0, ""},
	},

	staticMobiles = {
		{"corellia", "coa3_information_rebel", 60,14.1936,1.13306,-8.97227,335.228,1855516, "calm"},
		{"corellia", "coa3_information_rebel", 60,14.1936,1.13306,-8.97227,335.228,1855526, "calm"},
		{"corellia", "coa3_information_rebel", 60,14.1936,1.13306,-8.97227,335.228,1935453, "calm"},
		{"talus", "coa3_information_rebel", 60,14.1936,1.13306,-8.97227,335.228,4265395, "calm"},
		{"tatooine", "coa3_information_rebel", 60,14.1936,1.13306,-8.97227,335.228,1279963, "calm"},
		{"tatooine", "coa3_information_rebel",60,14.2091,1.13306,-10.1408,205.638,1256010, ""},
		{"naboo", "coa3_information_imperial",60,14.0299,1.13306,-8.82756,97.6176,1741509, "npc_imperial"},
		{"naboo", "coa3_information_imperial",60,14.0299,1.13306,-8.82756,97.6176,1692083, "npc_imperial"},
		{"rori", "coa3_information_imperial",60,14.0299,1.13306,-8.82756,97.6176,2615383, "npc_imperial"},
		{"tatooine", "coa3_information_imperial",60,14.0299,1.13306,-8.82756,97.6176,1028561, "npc_imperial"},

		{"corellia", "coa3_tactical_rebel", 60,9.53575,1.13306,0.330446,310.824,1935441, "calm"},
		{"tatooine", "coa3_tactical_imperial",60,9.74537,1.13306,0.300803,93.0077,1028549, "npc_imperial"},

		{"veers", "dantooine", 2505.7, 14, -2053.4, -139},
		{"veers", "dathomir", -6303.1, 123.2, -529.8, -42},
		{"veers", "endor", -1954.1, 146.6, 1051.9, -32},
		{"veers", "lok", -2568.4, 21.7, -861.4, 159},
		{"veers", "yavin4", 1586.4, 50.5, -3533.3, 46},
		{"leia_organa", "dantooine", 6874.4, 60, -2253, -126},
		{"leia_organa", "dathomir", -48.2, 142.3, 85.9, -60},
		{"leia_organa", "endor", 4021.1, 7.4, 2970.2, -82},
		{"leia_organa", "lok", -4753, 4, 3516.4, 111},
		{"leia_organa", "yavin4", -4237.2, 183.5, 2276, -23},
	}
}

registerScreenPlay("Coa3Screenplay", true)

function Coa3Screenplay:start()
	self:spawnStaticMobiles()
end

function Coa3Screenplay:spawnStaticMobiles()
	local mobiles = self.staticMobiles

	for i = 1, #mobiles, 1 do
		local mobile = mobiles[i]

		if (isZoneEnabled(mobile[1])) then
			local pMobile = spawnMobile(mobile[1], mobile[2], mobile[3], mobile[4], mobile[5], mobile[6], mobile[7], mobile[8], mobile[9])

			if (pMobile ~= nil and string.find(mobile[2], "coa3_tactical")) then
				SceneObject(pMobile):setContainerComponent("Coa3ContainerComponent")
			end
		end
	end
end

function Coa3Screenplay:setupMission(pPlayer, pNpc, faction, missionNum)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local randPlanet = self:getMissionPlanet()
	local minDistance, maxDistance, spawnName

	-- Lookout
	if (missionNum == self.LOOKOUT_MISSION) then
		minDistance = 1000
		maxDistance = 1500
		spawnName = "coa3_lookout"
	elseif (missionNum == self.FLORA_MISSION) then
		minDistance = 1000
		maxDistance = 1500
		spawnName = "object/building/poi/coa3_flora_warehouse.iff"
	elseif (missionNum == self.COMMANDER_MISSION) then
		minDistance = 1000
		maxDistance = 1500
		spawnName = "object/building/poi/coa3_flora_warehouse.iff"

		--self:setupCommanderMission(pPlayer, pNpc, faction, missionNum)
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	writeVector3Data(playerID .. ":CoA3:returnLoc:", SceneObject(pNpc):getWorldPositionX(), 0, SceneObject(pNpc):getWorldPositionY())
	writeStringData(playerID .. ":CoA3:returnPlanet:", SceneObject(pNpc):getZoneName())
	writeStringData(playerID .. ":CoA3:Faction:", faction)
	writeStringData(playerID .. ":CoA3:redirectPlanet:", randPlanet)
	writeStringData(playerID .. ":CoA3:spawnName:", spawnName)

	writeData(playerID .. ":CoA3:redirectMinDistance:", minDistance)
	writeData(playerID .. ":CoA3:redirectMaxDistance:", maxDistance)
	writeData(playerID .. ":CoA3:missionNum:", missionNum)

	CreatureObject(pPlayer):sendSystemMessage("@mission/mission_generic:target_located_" .. randPlanet)
	createObserver(ZONESWITCHED, "Coa3Screenplay", "updateMissionLocation", pPlayer)

	local x = getRandomNumber(8190) + (-1 * getRandomNumber(8190))
	local y = getRandomNumber(8190) + (-1 * getRandomNumber(8190))

	self:createMissionWaypoint(pPlayer, x, y, randPlanet, missionNum, faction)
	writeVector3Data(playerID .. ":CoA3:missionLocation:", x, 0, y)

	-- 20 minutes to complete the mission
	SceneObject(pPlayer):addPendingTask((20 * 60 * 1000), "Coa3Screenplay", "timeoutMission")
end

function Coa3Screenplay:updateMissionLocation(pPlayer, nill, zoneNameHash)
	if (pPlayer == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local planet = readStringData(playerID .. ":CoA3:redirectPlanet:")

	if (planet == "") then
		return 1
	end

	if (zoneNameHash ~= getHashCode(planet)) then
		return 0
	end

	-- Remove Waypoint and update with new one at chosen location
	self:removeMissionWaypoint(pPlayer)

	local faction = readStringData(playerID .. ":CoA3:Faction:")
	local missionNum = readData(playerID .. ":CoA3:missionNum:")
	local minDistance = readData(playerID .. ":CoA3:redirectMinDistance:")
	local maxDistance = readData(playerID .. ":CoA3:redirectMaxDistance:")
	local location = readVector3Data(playerID .. ":CoA3:missionLocation:")

	print("updateMissionLocation called - planet = " .. planet .. " zoneNameHash = " .. zoneNameHash .. " X = " .. location[1] .. " Y = " .. location[3] .. " Min Dist = " ..  minDistance .. " maxDistance = " .. maxDistance)

	local missionLoc = getSpawnArea(planet, location[1], location[3], minDistance, maxDistance, 20, 10, true)

	writeVector3Data(playerID .. ":CoA3:missionLocation:", missionLoc[1], missionLoc[2], missionLoc[3])

	print("updateMissionLocation -- spawn area -- X = " .. missionLoc[1] .. " Y = " .. missionLoc[3])

	local pActiveArea = spawnActiveArea(planet, "object/active_area.iff", missionLoc[1], missionLoc[2], missionLoc[3], 200, 0)

	if (pActiveArea == nil) then
		return 0
	end

	ActiveArea(pActiveArea):setNoSpawnArea(true)
	areaID = SceneObject(pActiveArea):getObjectID()
	writeData(areaID .. ":CoA3:ownerID:", playerID)

	createObserver(ENTEREDAREA, "Coa3Screenplay", "enteredMissionArea", pActiveArea)

	self:createMissionWaypoint(pPlayer, missionLoc[1], missionLoc[3], planet, missionNum, faction)

	deleteVector3Data(playerID .. ":CoA3:missionLocation:")
	deleteStringData(playerID .. ":CoA3:redirectPlanet:")
	deleteData(playerID .. ":CoA3:redirectMinDistance:")
	deleteData(playerID .. ":CoA3:redirectMaxDistance:")

	return 1
end

function Coa3Screenplay:enteredMissionArea(pArea, pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() or pArea == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local ownerID = readData(SceneObject(pArea):getObjectID() ..  ":CoA3:ownerID:")

	print("enteredMissionArea called -- ownerID = " .. ownerID .. " playerID = " .. playerID)

	if (ownerID ~= playerID) then
		return 0
	end

	local zoneName = SceneObject(pPlayer):getZoneName()
	local areaRadius = ActiveArea(pArea):getRadius()
	local missionNum = readData(playerID .. ":CoA3:missionNum:")
	local spawnName = readStringData(playerID .. ":CoA3:spawnName:")
	local spawnedObjects = {}

	local x = SceneObject(pArea):getWorldPositionX()
	local z = SceneObject(pArea):getWorldPositionZ()
	local y = SceneObject(pArea):getWorldPositionY()

	print("eneteredMissionArea -- areaRadiu = " .. areaRadius .. " zoneName = ".. zoneName ..  " missionNum = " .. missionNum .. " spawnName = " .. spawnName)

	if (missionNum == 1) then
		local pActiveArea = spawnActiveArea(zoneName, "object/active_area.iff", x, z, y, 75, 0)

		if (pActiveArea ~= nil) then
			ActiveArea(pActiveArea):setNoSpawnArea(true)

			local areaID = SceneObject(pActiveArea):getObjectID()
			writeData(areaID .. ":CoA3:ownerID:", playerID)
			spawnObjects[#spawnedObjects + 1] = tostring(areaID)

			createObserver(ENTEREDAREA, "Coa3Screenplay", "enteredLookoutArea", pActiveArea)
		end

		-- Handle Spawning a mobile for lookout area
		local pMobile = spawnMobile(zoneName, spawnName, 0, x, z, y, 0, 0)

		if (pMobile ~= nil) then
			AiAgent(pMobile):addCreatureFlag(AI_STATIONARY)

			local mobileID = SceneObject(pMobile):getObjectID()
			writeData(ownerID .. ":CoA3:NpcID:", mobileID)
			writeData(mobileID .. ":CoA3:ownerID:", ownerID)
		end
	elseif (missionNum == 3) then
		local pActiveArea = spawnActiveArea(zoneName, "object/active_area.iff", x, z, y, 75, 0)

		if (pActiveArea ~= nil) then
			ActiveArea(pActiveArea):setNoSpawnArea(true)

			local areaID = SceneObject(pActiveArea):getObjectID()
			writeData(areaID .. ":CoA3:ownerID:", playerID)
			spawnedObjects[#spawnedObjects + 1] = tostring(areaID)
		end

		-- spawn flora warehouse
		local pBuilding = spawnBuilding(pPlayer, spawnName, x, y, 0)

		if pBuilding == nil then
			self:abortMission(pPlayer, missionNum, true)
			return
		end

		spawnedObjects[#spawnedObjects + 1] = tostring(SceneObject(pBuilding):getObjectID())

		createObserver(ENTEREDBUILDING, "Coa3Screenplay", "onEnteredWarehouse", pBuilding)
		createObserver(OBJECTDESTRUCTION, "Coa3Screenplay", "notifyDestroyedWarehouse", pBuilding)

		createEvent(1000, "Coa3Screenplay", "spawnFlora", pBuilding, "")
		createEvent(2000, "Coa3Screenplay", "spawnWarehouseMobiles", pBuilding, "")
	end

	deleteData(SceneObject(pArea):getObjectID() .. ":CoA3:ownerID:")
	SceneObject(pArea):destroyObjectFromWorld()

	writeStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:", spawnedObjects)

	--deleteData(playerID .. ":CoA3:MissionArea:")

	return 1
end

-- ========= Mission Functions =========

function Coa3Screenplay:setupCommanderMission(pPlayer, pNpc, faction, missionNum)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	print("setupCommanderMission called -- faction = " .. faction)

	local playerID = SceneObject(pPlayer):getObjectID()
	local commanderID = Coa2Screenplay:getRandomCommander(faction)
	local pCommander = getSceneObject(commanderID)

	if (pCommander == nil) then
		Logger:log("Commander is nil in CoA3:setupCommanderMission - Player: " .. CreatureObject(pPlayer):getFirstName() .. "; ID: " .. playerID, LT_ERROR)
	end

	local planet = SceneObject(pCommander):getZoneName()
	local x = SceneObject(pCommander):getWorldPositionX()
	local y = SceneObject(pCommander):getWorldPositionY()

	writeData(playerID .. ":CoA3:missionNum:", missionNum)
	self:createMissionWaypoint(pPlayer, x, y, planet, 4, faction)
end

function Coa3Screenplay:spawnFlora(pBuilding)
	if (pBuilding == nil) then
		return
	end

	local planet = SceneObject(pBuilding):getZoneName()
	local playerID = BuildingObject(pBuilding):getOwnerID()
	local pCell = BuildingObject(pBuilding):getNamedCell("room3")

	if (pCell == nil) then
		return
	end

	local pDrum = spawnSceneObject(planet, "object/tangible/container/drum/poi_prize_box_off.iff", -4.5, 0.13, -3.23, SceneObject(pCell):getObjectID(), math.rad(90))

	if (pDrum ~= nil) then
		SceneObject(pDrum):setContainerInheritPermissionsFromParent(false)
		SceneObject(pDrum):setContainerDefaultDenyPermission(MOVEIN)
		SceneObject(pDrum):setContainerDefaultAllowPermission(MOVEOUT)
		SceneObject(pDrum):setContainerLockedStatus(true)

		local drumID = SceneObject(pDrum):getObjectID()
		writeData(playerID .. ":CoA3:floraDrum:", drumID)

		local totalFlora = getRandomNumber(1, 3)

		for i = 1, totalFlora, 1 do
			createLoot(pDrum, "coa3_alderaan_flora", -1, true)
		end

		createObserver(CONTAINERCONTENTSCHANGED, "Coa3Screenplay", "notifyContainerLooted", pDrum)
	end
end

function Coa3Screenplay:spawnWarehouseMobiles(pBuilding)
	if (pBuilding == nil) then
		return
	end

	local playerID = BuildingObject(pBuilding):getOwnerID()
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil) then
		self:abortMission(pPlayer, Coa3Screenplay.FLORA_MISSION, true)
		return
	end

	local spawnedObjects = readStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:")

	local planet = SceneObject(pBuilding):getZoneName()
	local x = SceneObject(pBuilding):getWorldPositionX()
	local y = SceneObject(pBuilding):getWorldPositionY()

	local mobiles = self.warehouseMobiles
	local totalMobiles = 0

	for i = 1, #mobiles, 1 do
		local mobile = mobiles[i]
		local cellID = 0

		if (mobile[5] ~= "") then
			local pCell = BuildingObject(pBuilding):getNamedCell(mobile[5])
			if (pCell ~= nil) then
				cellID = SceneObject(pCell):getObjectID()
			end
		end

		local spawnX = mobile[2]
		local spawnZ = mobile[3]
		local spawnY = mobile[4]

		if (cellID == 0) then
			spawnX = spawnX + x
			spawnY = spawnY + y
			spawnZ = getWorldFloor(spawnX, spawnY, planet)
		end

		-- {template, x, z, y, cellName}
		local pMobile = spawnMobile(planet, mobile[1], -1, spawnX, spawnZ, spawnY, 0, cellID)

		if (pMobile ~= nil) then
			local mobileID = SceneObject(pMobile):getObjectID()
			spawnedObjects[#spawnedObjects + 1] = mobileID

			totalMobiles = totalMobiles + 1

			createObserver(OBJECTDESTRUCTION, "Coa3Screenplay", "notifyGuardKilled", pMobile)
		end
	end

	writeData(playerID .. ":CoA3:totalWarehouseMobiles:", totalMobiles)
	writeStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:", spawnedObjects)
end

-- ========= Mission Specific Observers =========


function Coa3Screenplay:enteredLookoutArea(pArea, pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() or pArea == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local ownerID = readData(SceneObject(pArea):getObjectID() ..  ":CoA3:ownerID:")

	print("enteredLookoutArea called -- ownerID = " .. ownerID .. " playerID = " .. playerID)

	if (ownerID ~= playerID) then
		return 0
	end

	local missionNum = readData(playerID .. ":CoA3:missionNum:")
	local faction = readStringData(playerID .. ":CoA3:Faction:")
	local npcID = readData(playerID .. ":CoA3:NpcID:")
	local pNpc = getSceneObject(npcID)

	if (pNpc == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_" .. faction .. "_missions:m" .. missionNum .. "_init_failure")
		self:abortMission(pPlayer, missionNum, true)
	end

	 return 1
end

function Coa3Screenplay:onEnteredWarehouse(pBuilding, pPlayer)
	if (pBuilding == nil or pPlayer == nil) then
		return 1
	end

	local ownerID = BuildingObject(pBuilding):getOwnerID()
	local playerID = SceneObject(pPlayer):getObjectID()

	if (ownerID ~= playerID) then
		return 0
	end

	local totalCells = BuildingObject(pBuilding):getTotalCellNumber()

	for i = 1, totalCells, 1 do
		local pCell = BuildingObject(pBuilding):getCell(i)

		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j)

				if pObject ~= nil and SceneObject(pObject):isAiAgent() then
					AiAgent(pObject):setDefender(pPlayer)
				end
			end
		end
	end

	return 1
end

function Coa3Screenplay:notifyDestroyedWarehouse(pBuilding, pBuilding2)
	if (pBuilding == nil) then
		return 1
	end

	local planet = SceneObject(pBuilding):getZoneName()
	local ownerID = BuildingObject(pBuilding):getOwnerID()
	local pPlayer = getCreatureObject(ownerID)

	if (pPlayer == nil) then
		return 1
	end

	for i = 1, 5, 1 do
		playClientEffectLoc(pPlayer, "clienteffect/dth_watch_water_pressure.cef", planet, SceneObject(pBuilding):getPositionX(), SceneObject(pBuilding):getPositionZ(), SceneObject(pBuilding):getPositionY(), 0)
	end

	local faction = readStringData(ownerID .. ":CoA3:Faction:")
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)

	print("notifyDestroyedWarehouse called -- with player state = " .. state)

	if (state >= self.M3_LOOTED_FLORA and state < self.M3_WAREHOUSE_DESTROYED) then
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M3_WAREHOUSE_DESTROYED)
	else
		writeData(ownerID .. "CoA3:extraFloraMission:", Coa3Screenplay.FLORA_WAREHOUSE_DESTROYED)
	end

	self:removeWaypoint(pPlayer)
	self:abortMission(pPlayer, Coa3Screenplay.FLORA_MISSION, 1)

	return 1
end

function Coa3Screenplay:setupCaravan(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local planet = SceneObject(pPlayer):getZoneName()
	local faction = readStringData(playerID .. ":CoA3:Faction:")

	print("setupCaravanCalled - faction = " .. faction .. " planet = " .. planet)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local missionLoc = getSpawnArea(planet, SceneObject(pPlayer):getWorldPositionX(), SceneObject(pPlayer):getWorldPositionY(), 1000, 1500, 20, 10, true)

	local wayName = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_name_2"
	local wayDesc = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_desc_2"

	local wayID = PlayerObject(pGhost):addWaypoint(planet, wayName, wayDesc, missionLoc[1], missionLoc[3], WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)
	local spawnIDs = {}

	local x = missionLoc[1]
	local y = missionLoc[3]

	-- Active Area to track player leaving
	local pActiveArea = spawnActiveArea(planet, "object/active_area.iff", x, getWorldFloor(x, y, planet), y, 75, 0)

	if (pActiveArea ~= nil) then
		createObserver(EXITEDAREA, "Coa3Screenplay", "exitedCaravanArea", pActiveArea)

		local areaID = SceneObject(pActiveArea):getObjectID()
		spawnIDs[#spawnIDs + 1] = tostring(areaID)
	end

	-- Spawn Theater for terrain
	local pTheater = spawnTheaterObject(planet, x, getWorldFloor(x, y, planet), y, true)

	if (pTheater ~= nil) then
		local theaterID = SceneObject(pTheater):getObjectID()

		spawnIDs[#spawnIDs + 1] = tostring(theaterID)
	end

	-- Spawn Mobiles
	local spawns = {"coa3_caravan_leader", "coa3_caravan_thug", "coa3_caravan_thug", "coa3_caravan_thug", "coa3_caravan_thug", "coa3_caravan_thug"}

	for i = 1, #spawns, 1 do
		local pMobile = spawnMobile(planet, spawns[i], -1, x, getWorldFloor(x, y, planet), y, 0, 0)

		if (pMobile ~= nil) then
			if (i == 1) then
				AiAgent(pMobile):addCreatureFlag(AI_STATIONARY)
			end

			local mobileID = SceneObject(pMobile):getObjectID()
			spawnIDs[#spawnIDs + 1] = tostring(mobileID)
		end
	end

	-- spawn decoration
	local deco = {
		"object/static/vehicle/e3/landspeeder.iff",
		"object/static/vehicle/e3/landspeeder.iff",
	}

	for j = 1, #deco, 1 do
		--{planet, template, x, z, y, cell, direction}
		if (j == 1) then
			x = x - 8
		else
			x = x + 9
		end

		y = y + 5

		local pScno = spawnSceneObject(planet, deco[j], x, getWorldFloor(x, y, planet), y, 0, math.rad(getRandomNumber(180)))

		if pScno ~= nil then
			local scnoID = SceneObject(pScno):getObjectID()

			spawnIDs[#spawnIDs + 1] = tostring(scnoID)
		end
	end

	-- Store Data for cleanup
	writeData(playerID .. ":CoA3:CaravanWaypoint:", wayID)
	writeStringVectorSharedMemory(playerID .. ":CoA3:caravanSpawns:", spawnIDs)
end

function Coa3Screenplay:cleanUpCaravan(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local wayID = readData(playerID .. ":CoA3:CaravanWaypoint:")

	PlayerObject(pGhost):removeWaypoint(wayID, true)
	deleteData(playerID .. ":CoA3:CaravanWaypoint:")

	local objects = readStringVectorSharedMemory(playerID .. ":CoA3:caravanSpawns:")

	for i = 1, #objects, 1 do
		local pTarget = getSceneObject(tonumber(objects[i]))

		if pTarget ~= nil then
			SceneObject(pTarget):destroyObjectFromWorld()
		end
	end

	deleteStringVectorSharedMemory(playerID .. ":CoA3:caravanSpawns:")
	deleteData(playerID .. ":CoA3:partStatus:")
end

function Coa3Screenplay:exitedCaravanArea(pArea, pPlayer)
	if (pPlayer == nil or not self:hasDisk(pPlayer)) then
		return 0
	end

	self:cleanUpCaravan(pPlayer)

	return 1
end

function Coa3Screenplay:notifyGuardKilled(pMobile, pKiller)
	if (pMobile == nil or pKiller == nil) then
		print("something is nil")
		return 1
	end

	local playerID = SceneObject(pKiller):getObjectID()
	local totalMobiles = readData(playerID .. ":CoA3:totalWarehouseMobiles:")

	totalMobiles = totalMobiles -1

	if (totalMobiles <= 0) then
		local drumID = readData(playerID .. ":CoA3:floraDrum:")
		local pDrum = getSceneObject(drumID)

		if (pDrum ~= nil) then
			SceneObject(pDrum):setContainerLockedStatus(false)

			deleteData(playerID .. ":CoA3:floraDrum:")
		end
		return 1
	end

	writeData(playerID .. ":CoA3:totalWarehouseMobiles:", totalMobiles)

	return 0
end

function Coa3Screenplay:notifyContainerLooted(pContainer, pLooter)
	if (pContainer == nil or pLooter == nil or not SceneObject(pLooter):isCreatureObject()) then
		return 1
	end

	local totalContents = SceneObject(pContainer):getContainerObjectsSize()

	if (totalContents > 0) then
		return 0
	end

	local playerID = SceneObject(pLooter):getObjectID()
	local faction = readStringData(playerID .. ":CoA3:Faction:")
	local stateKey = self:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pLooter, stateKey)

	print("notifyContainerLooted -- stateKey = " .. stateKey)

	if (state == self.M3_SENT_TO_WAREHOUSE) then
		CriesOfAlderaan:setState(pLooter, stateKey, Coa3Screenplay.M3_LOOTED_FLORA)
		return 1
	end

	return 0
end

function Coa3Screenplay:removeWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local wayID = readData(playerID .. ":CoA3:Waypoint:")

	PlayerObject(pGhost):removeWaypoint(wayID, true)
	deleteData(playerID .. ":CoA3:Waypoint:")
end

function Coa3Screenplay:giveWaypoint(pPlayer, pTarget, name, desc)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return 0
	end

	local x = SceneObject(pTarget):getWorldPositionX()
	local y = SceneObject(pTarget):getWorldPositionY()
	local planet = SceneObject(pTarget):getZoneName()

	local wayID = PlayerObject(pGhost):addWaypoint(planet, name, desc, x, y, WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)

	writeData(playerID .. ":CoA3:Waypoint", wayID)
end

function Coa3Screenplay:abortMission(pPlayer, missionNum, returnToNpc)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	self:cleanupMission(pPlayer)

	if (returnToNpc >= 1) then
		local returnLocation = readVector3Data(playerID .. ":CoA3:returnLoc:")
		local returnPlanet = readStringData(playerID .. ":CoA3:returnPlanet:")

		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			local faction = readStringData(playerID .. ":CoA3:Faction:")
			local wayName = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_return_name_" .. missionNum
			local wayDesc = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_return_desc_" .. missionNum

			PlayerObject(pGhost):addWaypoint(returnPlanet, wayName, wayDesc, returnLocation[1], returnLocation[3], WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)
		end
	end
end

function Coa3Screenplay:cleanupMission(pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	SceneObject(pPlayer):cancelPendingTask("Coa3Screenplay", "timeoutMission")

	self:removeWaypoint(pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()
	local targetID = readData(playerID .. ":CoA3:NpcID:")
	local pTarget = getSceneObject(targetID)

	if pTarget ~= nil then
		SceneObject(pTarget):destroyObjectFromWorld()
	end

	local spawnedObjects = readStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:")

	for i = 1, #spawnedObjects, 1 do
		local pObject = getSceneObject(spawnedObjects[i])

		if pObject ~= nil then
			if (SceneObject(pObject):isBuildingObject()) then
				destroyBuilding(spawnedObjects[i])
			else
				SceneObject(pObject):destroyObjectFromWorld()
			end
		end
	end

	deleteData(targetID .. ":CoA3:ownerID:")
	deleteData(playerID .. ":CoA3:NpcID:")
	deleteData(playerID .. ":CoA3:totalWarehouseMobiles:")
	deleteData(playerID .. ":CoA3:floraDrum:")

	deleteStringData(playerID .. ":CoA3:Faction:")
	deleteStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:")

	print("CoA3 CleanUp Complete")
end


-- ======== General Functions =========

function Coa3Screenplay:createMissionWaypoint(pPlayer, x, y, planet, missionNum, faction)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	local wayName = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_name_" .. missionNum
	local wayDesc = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_desc_" .. missionNum

	local wayID = PlayerObject(pGhost):addWaypoint(planet, wayName, wayDesc, x, y, WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)

	writeData(playerID .. ":CoA3:Waypoint:", wayID)
end

function Coa3Screenplay:removeMissionWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local wayID = readData(playerID .. ":CoA3:Waypoint:")

	PlayerObject(pGhost):removeWaypoint(wayID, true)
end

function Coa3Screenplay:getMissionPlanet()
	local planets = {"dathomir", "endor", "yavin4", "lok"}
	return planets[getRandomNumber(1, #planets)]
end

function Coa3Screenplay:getStateKey(faction)
	if (faction == FACTIONIMPERIAL or faction == "imperial") then
		return "coa3_imperial"
	elseif (faction == FACTIONREBEL or faction == "rebel") then
		return "coa3_rebel"
	else
		return ""
	end
end

function Coa3Screenplay:timeoutMission(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local faction = readStringData(playerID .. ":CoA3:Faction:")
	local stateKey = self:getStateKey(faction)
	local missionNum = readData(playerID .. ":CoA3:missionNum:")

	if (missionNum == 1) then
		Coa3Screenplay:cleanUpCaravan(pPlayer)

		deleteData(playerID .. ":CoA3:lookoutConvoFlow:")
		deleteData(playerID .. ":CoA3:lookoutTracker:")
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M1_FIND_LOOKOUT)

		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_" .. faction .. "_missions:m" .. missionNum .. "_init_failure")
	end

	CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_" .. faction .. "_missions:m" .. missionNum .. "_init_failure")
	self:abortMission(pPlayer, missionNum, true)
end

function Coa3Screenplay:getFactionString(pCreature)
	if (pCreature == nil) then
		return ""
	end

	local factionString = ""

	if (SceneObject(pCreature):isPlayerCreature()) then
		local playerID = SceneObject(pPlayer):getObjectID()
		factionString = readStringData(playerID .. ":CoA3:Faction:")
	else
		local faction = CreatureObject(pCreature):getFaction()

		if (faction == FACTIONIMPERIAL) then
			factionString = "imperial"
		elseif (faction == FACTIONREBEL) then
			factionString = "rebel"
		end
	end

	return factionString
end

function Coa3Screenplay:hasDisk(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return false
	end

	local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/theme_park/alderaan/act3/encoded_data_disk.iff", false)

	if pItem == nil then
		return false
	end

	return true
end

function Coa3Screenplay:giveRepairKit(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	if (SceneObject(pInventory):isContainerFullRecursive()) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_imperial_missions:m2_repair_kit_denied")
		return
	end

	local repairKit = giveItem(pInventory, "object/tangible/theme_park/alderaan/act3/grav_unit_repair_kit.iff", -1)

	if (repairKit ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_imperial_missions:m2_repair_kit_received")
	end
end

function Coa3Screenplay:giveBrokenUnit(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	if (SceneObject(pInventory):isContainerFullRecursive()) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_imperial_missions:m3_broken_grav_unit_denied")
		return
	end

	local pBrokenUnit = giveItem(pInventory, "object/tangible/theme_park/alderaan/act3/broken_grav_unit.iff", -1)

	if (pBrokenUnit ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_imperial_missions:m3_broken_grav_unit_received")
	end
end

function Coa3Screenplay:repairGravUnit(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_rebel_missions:repair_failed")
		return
	end

	local pBrokenUnit = getContainerObjectByTemplate(pInventory, "object/tangible/theme_park/alderaan/act3/broken_grav_unit.iff", false)

	if (pBrokenUnit == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_rebel_missions:repair_failed")
		return
	end

	SceneObject(pBrokenUnit):destroyObjectFromDatabase()
	SceneObject(pBrokenUnit):destroyObjectFromWorld()

	if (SceneObject(pInventory):isContainerFullRecursive()) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_rebel_missions:repair_failed")
		return
	end

	local pRepairedUnit = giveItem(pInventory, "object/tangible/theme_park/alderaan/act3/repaired_grav_unit.iff", -1)

	if (pRepairedUnit ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_rebel_missions:repair_grav_unit")
	end
end

function Coa3Screenplay:hasRepairedGravUnit(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return false
	end

	local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/theme_park/alderaan/act3/repaired_grav_unit.iff", false)

	if pItem == nil then
		return false
	end

	return true
end

function Coa3Screenplay:giveDisk(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	if (SceneObject(pInventory):isContainerFullRecursive()) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_imperial_missions:m3_data_disk_denied")
		return
	end

	local templates = {
		"object/tangible/theme_park/alderaan/act3/repaired_grav_unit.iff",
		"object/tangible/theme_park/alderaan/act3/grav_unit_repair_kit.iff"
	}

	for i = 1, #templates, 1 do
		local pItem = getContainerObjectByTemplate(pInventory, templates[i], false)

		if pItem ~= nil then
			SceneObject(pItem):destroyObjectFromDatabase()
			SceneObject(pItem):destroyObjectFromWorld()
		end
	end

	local pDisk = giveItem(pInventory, "object/tangible/theme_park/alderaan/act3/encoded_data_disk.iff", -1)

	if (pDisk ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_imperial_missions:m3_data_disk_received")
	end
end

function Coa3Screenplay:getObjOwner(pObj)
	local pPlayerInv = SceneObject(pObj):getParent()

	if (pPlayerInv == nil) then
		return nil
	end

	local parent = SceneObject(pPlayerInv):getParent()

	if (parent == nil) then
		return nil
	end

	if (SceneObject(parent):isCreatureObject()) then
		return parent
	end

	return nil
end
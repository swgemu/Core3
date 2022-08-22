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
	FACILITY = 5,

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
		{"corellia", "coa3_information_rebel", 60,14.1936,1.13306,-8.97227,335.228,1935453, "calm"},
		{"talus", "coa3_information_rebel", 60,14.1936,1.13306,-8.97227,335.228,4265395, "calm"},
		{"tatooine", "coa3_information_rebel", 60,14.1936,1.13306,-8.97227,335.228,1279963, "calm"},
		{"tatooine", "coa3_information_rebel",60,14.2091,1.13306,-10.1408,205.638,1256010, ""},

		{"naboo", "coa3_information_imperial",60,14.0299,1.13306,-8.82756,97.6176,1741509, "npc_imperial"},
		{"naboo", "coa3_information_imperial",60,14.0299,1.13306,-8.82756,97.6176,1692083, "npc_imperial"},
		{"rori", "coa3_information_imperial",60,14.0299,1.13306,-8.82756,97.6176,4615383, "npc_imperial"},
		{"rori", "coa3_information_imperial",60,14.0299,1.13306,-8.82756,97.6176,4635663, "npc_imperial"},
		{"tatooine", "coa3_information_imperial",60,14.0299,1.13306,-8.82756,97.6176,1028561, "npc_imperial"},

		{"corellia", "coa3_tactical_rebel", 60,9.53575,1.13306,0.330446,310.824,1935441, "calm"},
		{"corellia", "coa3_tactical_rebel", 60,9.53575,1.13306,0.330446,310.824,1855504, "calm"},
		{"talus", "coa3_tactical_rebel", 60,9.53575,1.13306,0.330446,310.824,4265403, "calm"},
		{"tatooine", "coa3_tactical_rebel", 60,9.53575,1.13306,0.330446,310.824,1189635, "calm"},
		{"tatooine", "coa3_tactical_rebel", 60,9.53575,1.13306,0.330446,310.824,1255990, "calm"},

		{"tatooine", "coa3_tactical_imperial", 60,9.74537,1.13306,0.300803,93.0077,1028549, "npc_imperial"},
		{"naboo", "coa3_tactical_imperial", 60, 9.8, 1.1, 0.9, 143, 1692071, "npc_imperial"},
		{"naboo", "coa3_tactical_imperial", 60, 9.8, 1.1, 0.9, 143, 1741458, "npc_imperial"},
		{"rori", "coa3_tactical_imperial", 60,9.74537,1.13306,0.300803,93.0077,4615371, "npc_imperial"},
		{"rori", "coa3_tactical_imperial", 60,9.74537,1.13306,0.300803,93.0077,4635687, "npc_imperial"},
	},

	coa3commanders = {
		{"dantooine", "coa3_veers", 2506.0, 14, -2049.7, -139},
		{"dathomir", "coa3_veers", -6299.51, 123.2, -527.7, -42},
		{"endor", "coa3_veers", -1956.3, 146.6, 1051.6, -32},
		{"lok", "coa3_veers", -2571.1, 21.7, -860.2, 159},
		{"yavin4", "coa3_veers", 1577.9, 50.5, -3531.3, 46},
		{"dantooine", "coa3_leia_organa", 6883.2, 60, -2253.1, -126},
		{"dathomir", "coa3_leia_organa", -49.0, 142.2, 85.3, -60},
		{"endor", "coa3_leia_organa", 4021.8, 7.4, 2972.8, -82},
		{"lok", "coa3_leia_organa", -4751.0, 4, 3517.8, 157},
		{"yavin4", "coa3_leia_organa", -4236.6, 183.5, 2274.9, 57},
	},

	finalRebelMobiles = {"coa3_rebel_research_captain",	"coa3_rebel_research_captain", "coa3_rebel_research_guard",
		"coa3_rebel_research_guard", "coa3_rebel_research_guard", "coa3_rebel_research_guard",
		"coa3_rebel_research_guard", "coa3_rebel_research_guard"
	},

	finalImperialMobiles = {"coa3_imperial_research_captain", "coa3_imperial_research_captain", "coa3_imperial_research_guard",
		"coa3_imperial_research_guard", "coa3_imperial_research_guard", "coa3_imperial_research_guard", "coa3_imperial_research_guard",
		"coa3_imperial_research_guard"
	},
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

	local coa3commanders = self.coa3commanders

	for j = 1, #coa3commanders, 1 do
		local commander = coa3commanders[j]

		if (isZoneEnabled(commander[1])) then
			local pCommander = spawnMobile(commander[1], commander[2], -1, commander[3], commander[4], commander[5], commander[6], 0)

			if (pCommander ~= nil) then
				local commanderID = SceneObject(pCommander):getObjectID()

				writeData(j .. ":CoA3:commanderID:", commanderID)
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

	if (missionNum == self.LOOKOUT_MISSION) then
		minDistance = 1000
		maxDistance = 1500
		spawnName = "coa3_lookout"
	elseif (missionNum == self.FLORA_MISSION) then
		minDistance = 1000
		maxDistance = 1500
		spawnName = "object/tangible/theme_park/alderaan/act3/coa3_flora_warehouse.iff"
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

	local missionLoc = getSpawnArea(planet, location[1], location[3], minDistance, maxDistance, 20, 10, true)

	writeVector3Data(playerID .. ":CoA3:missionLocation:", missionLoc[1], missionLoc[2], missionLoc[3])

	local pActiveArea = spawnActiveArea(planet, "object/active_area.iff", missionLoc[1], missionLoc[2], missionLoc[3], 200, 0)

	if (pActiveArea == nil) then
		return 0
	end

	ActiveArea(pActiveArea):setNoSpawnArea(true)

	local areaID = SceneObject(pActiveArea):getObjectID()
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

	if (missionNum == 1) then
		local pActiveArea = spawnActiveArea(zoneName, "object/active_area.iff", x, z, y, 75, 0)

		if (pActiveArea ~= nil) then
			ActiveArea(pActiveArea):setNoSpawnArea(true)

			local areaID = SceneObject(pActiveArea):getObjectID()
			writeData(areaID .. ":CoA3:ownerID:", playerID)
			spawnedObjects[#spawnedObjects + 1] = tostring(areaID)

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
			self:abortMission(pPlayer, missionNum, 1)
			return
		end

		spawnedObjects[#spawnedObjects + 1] = tostring(SceneObject(pBuilding):getObjectID())

		createObserver(ENTEREDBUILDING, "Coa3Screenplay", "onEnteredWarehouse", pBuilding)
		createObserver(OBJECTDESTRUCTION, "Coa3Screenplay", "notifyDestroyedWarehouse", pBuilding)

		-- createNavMesh for area
		local pNavMesh = createNavMesh(zoneName, x, y, 50, true, "CoA3:warehouseMission:" .. playerID)

		if (pNavMesh ~= nil) then
			local meshID = SceneObject(pNavMesh):getObjectID()

			writeData(playerID .. ":CoA3:navMesh:", meshID)
		end

		createEvent(1000, "Coa3Screenplay", "spawnFlora", pBuilding, "")
		createEvent(2000, "Coa3Screenplay", "spawnWarehouseMobiles", pBuilding, "")
	end

	deleteData(SceneObject(pArea):getObjectID() .. ":CoA3:ownerID:")
	SceneObject(pArea):destroyObjectFromWorld()

	writeStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:", spawnedObjects)

	return 1
end

-- ========= Mission Functions =========

function Coa3Screenplay:setupCommanderMission(pPlayer, faction)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local commanderID = self:getRandomCommander(faction)
	local pCommander = getSceneObject(commanderID)

	if (pCommander == nil) then
		Logger:log("Commander is nil in CoA3:setupCommanderMission - Player: " .. CreatureObject(pPlayer):getFirstName() .. "; ID: " .. playerID, LT_ERROR)
	end

	local planet = SceneObject(pCommander):getZoneName()
	local x = SceneObject(pCommander):getWorldPositionX()
	local y = SceneObject(pCommander):getWorldPositionY()

	writeData(playerID .. ":CoA3:missionNum:", self.COMMANDER_MISSION)
	writeVector3Data(playerID .. ":CoA3:returnLoc:", x, 0, y)
	writeStringData(playerID .. ":CoA3:returnPlanet:", planet)

	self:createMissionWaypoint(pPlayer, x, y, planet, self.COMMANDER_MISSION, faction)
end

function Coa3Screenplay:spawnCommanderObjective(pPlayer, pCommander, faction)
	if (pPlayer == nil or pCommander == nil) then
		return
	end

	self:removeWaypoint(pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()
	local planet = SceneObject(pCommander):getZoneName()
	local commanderX = SceneObject(pCommander):getWorldPositionX()
	local commanderY = SceneObject(pCommander):getWorldPositionY()

	local missionLoc = getSpawnArea(planet, commanderX, commanderY, 1500, 2500, 20, 10, true)
	local x = missionLoc[1]
	local y = missionLoc[3]
	local z = getWorldFloor(x, y, planet)
	local spawnedObjects = {}

	local spawnName = "object/tangible/theme_park/alderaan/act3/research_facility.iff"

	local pObject = spawnSceneObject(planet, spawnName, x, z, y, 0, 0)

	if (pObject == nil) then
		self:abortMission(pPlayer, self.FACILITY, 1)
		return
	end

	spawnedObjects[#spawnedObjects + 1] = tostring(SceneObject(pObject):getObjectID())

	local pTheater = spawnTheaterObject(planet, x, z, y, true)

	if (pTheater ~= nil) then
		spawnedObjects[#spawnedObjects + 1] = tostring(SceneObject(pTheater):getObjectID())
	end

	local pActiveArea = spawnActiveArea(planet, "object/active_area.iff", x, z, y, 125, 0)

	if (pActiveArea ~= nil) then
		createObserver(ENTEREDAREA, "Coa3Screenplay", "enteredFinalMission", pActiveArea)

		ActiveArea(pActiveArea):setNoSpawnArea(true)
		ActiveArea(pActiveArea):setNoBuildArea(true)

		local areaID = SceneObject(pActiveArea):getObjectID()
		spawnedObjects[#spawnedObjects + 1] = tostring(areaID)
		writeData(areaID .. ":CoA3:ownerID:", playerID)
	end

	-- spawn terminal for imperial only
	if (faction == "imperial") then
		local termX = x + -8.0
		local termY = y + 3.4

		local pTerminal = spawnSceneObject(planet, "object/tangible/furniture/imperial/data_terminal_s1.iff", termX, z, termY, SceneObject(pObject):getObjectID(), math.rad(-90))

		if (pTerminal ~= nil) then
			local terminalID = SceneObject(pTerminal):getObjectID()
			writeData(playerID .. ":CoA3:finalTerminal:", terminalID)
			writeData(playerID .. ":CoA3:facilityID:", SceneObject(pObject):getObjectID())

			spawnedObjects[#spawnedObjects + 1] = tostring(terminalID)
		end
	end

	-- createNavMesh for area
	local pNavMesh = createNavMesh(planet, x, y, 125, true, "CoA3:finalMission:" .. playerID)

	if (pNavMesh ~= nil) then
		local meshID = SceneObject(pNavMesh):getObjectID()

		writeData(playerID .. ":CoA3:navMesh:", meshID)
	end

	writeStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:", spawnedObjects)
	writeStringData(playerID .. ":CoA3:Faction:", faction)

	self:createMissionWaypoint(pPlayer, x, y, planet, self.FACILITY, faction)

	-- 20 minutes to complete the mission
	SceneObject(pPlayer):addPendingTask((20 * 60 * 1000), "Coa3Screenplay", "timeoutMission")
end

function Coa3Screenplay:spawnFinalMobiles(pPlayer, pArea)
	if (pPlayer == nil or pArea == nil) then
		self:abortMission(pPlayer, self.FACILITY, 1)
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local faction = readStringData(playerID .. ":CoA3:Faction:")
	local spawnedObjects = readStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:")

	local planet = SceneObject(pArea):getZoneName()
	local x = SceneObject(pArea):getWorldPositionX()
	local y = SceneObject(pArea):getWorldPositionY()

	local mobiles = self.finalRebelMobiles
	local totalMobiles = 0

	for i = 1, #mobiles, 1 do
		local mobileTemplate = mobiles[i]

		local spawnX = x
		local spawnY = y + 20
		local spawnZ = getWorldFloor(spawnX, spawnY, planet)

		-- {template, x, z, y, cellName}
		local pMobile = spawnMobile(planet, mobileTemplate, -1, spawnX, spawnZ, spawnY, 0, 0)

		if (pMobile ~= nil) then
			local mobileID = SceneObject(pMobile):getObjectID()
			spawnedObjects[#spawnedObjects + 1] = mobileID
			writeData(mobileID .. ":CoA3:ownerID:", playerID)

			totalMobiles = totalMobiles + 1

			createObserver(OBJECTDESTRUCTION, "Coa3Screenplay", "rebelDefendMobileKilled", pMobile)
		end
	end

	writeData(playerID .. ":CoA3:totalGuards:", totalMobiles)
	writeStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:", spawnedObjects)
end

function Coa3Screenplay:spawnAssaultWave(pArea)
	if (pArea == nil) then
		self:abortMission(pPlayer, self.FACILITY, 1)
		return
	end

	local areaID = SceneObject(pArea):getObjectID()
	local playerID = readData(areaID .. ":CoA3:ownerID:")
	local planet = SceneObject(pArea):getZoneName()

	local totalMobiles = readData(playerID .. ":CoA3:totalGuards:")

	-- All of the guards have been killed, mission failed.
	if (totalMobiles <= 0) then
		return
	end

	local waveNum = readData(playerID .. ":CoA3:assaultNumber:") + 1
	local spawnedObjects = readStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:")

	local attacker1 = "coa3_rebel_research_attacker_1"
	local attacker2 = "coa3_rebel_research_attacker_2"

	local x = SceneObject(pArea):getWorldPositionX()
	local y = SceneObject(pArea):getWorldPositionY()

	local totalAttackers = readData(playerID .. ":CoA3:totalAttackers:")

	for i = 1, waveNum + 2, 1 do
		local spawnX = x + getRandomNumber(2, 10)
		local spawnY = y + 125

		local pMobile1 = spawnMobile(planet, attacker1, -1, spawnX, getWorldFloor(spawnX, spawnY, planet), spawnY, 0, 0)

		if (pMobile1 ~= nil) then
			local mobileID = SceneObject(pMobile1):getObjectID()

			spawnedObjects[#spawnedObjects + 1] = mobileID
			writeData(mobileID .. ":CoA3:ownerID:", playerID)

			AiAgent(pMobile1):clearPatrolPoints()
			AiAgent(pMobile1):setNextPosition(x + getRandomNumber(2, 14), getWorldFloor(x, y, planet), y + 30, 0)

			if (waveNum == 3) then
				createObserver(OBJECTDESTRUCTION, "Coa3Screenplay", "rebelDefendMobileKilled", pMobile1)
				totalAttackers = totalAttackers + 1
			end
		end
	end

	for j = 1, waveNum, 1 do
		local spawnX = x + getRandomNumber(5, 15)
		local spawnY = y + 125

		local pMobile2 = spawnMobile(planet, attacker2, -1, spawnX, getWorldFloor(spawnX, spawnY, planet), spawnY, 0, 0)

		if (pMobile2 ~= nil) then
			local mobileID = SceneObject(pMobile2):getObjectID()

			spawnedObjects[#spawnedObjects + 1] = mobileID
			writeData(mobileID .. ":CoA3:ownerID:", playerID)

			AiAgent(pMobile2):clearPatrolPoints()
			AiAgent(pMobile2):setNextPosition(x + getRandomNumber(2, 14), getWorldFloor(x, y, planet), y + 30, 0)

			if (waveNum == 3) then
				createObserver(OBJECTDESTRUCTION, "Coa3Screenplay", "rebelDefendMobileKilled", pMobile2)
				totalAttackers = totalAttackers + 1
			end
		end
	end

	writeStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:", spawnedObjects)
	writeData(playerID .. ":CoA3:assaultNumber:", waveNum)

	if (waveNum < 3) then
		local time = getRandomNumber(60, 90)

		createEvent(time * 1000, "Coa3Screenplay", "spawnAssaultWave", pArea, "")
	else
		writeData(playerID .. ":CoA3:totalAttackers:", totalAttackers)
	end
end

function Coa3Screenplay:setupCaravan(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local planet = SceneObject(pPlayer):getZoneName()
	local faction = readStringData(playerID .. ":CoA3:Faction:")

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

				createObserver(LOOTCREATURE, "Coa3Screenplay", "onLootCaravanLeader", pMobile)
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
		SceneObject(pDrum):setContainerDefaultDenyPermission(MOVEIN + MOVECONTAINER)
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
		self:abortMission(pPlayer, Coa3Screenplay.FLORA_MISSION, 1)
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

	if (ownerID ~= playerID) then
		return 0
	end

	local missionNum = readData(playerID .. ":CoA3:missionNum:")
	local faction = readStringData(playerID .. ":CoA3:Faction:")
	local npcID = readData(playerID .. ":CoA3:NpcID:")
	local pNpc = getSceneObject(npcID)

	if (pNpc == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_" .. faction .. "_missions:m" .. missionNum .. "_init_failure")
		self:abortMission(pPlayer, missionNum, 1)
	end

	 return 1
end

function Coa3Screenplay:onLootCaravanLeader(pLootedCreature, pLooter, nothing)
	if (pLootedCreature == nil or pLooter == nil) then
		return 1
	end

	local playerID = SceneObject(pLooter):getObjectID()
	local faction = readStringData(playerID .. ":CoA3:Faction:")
	local stateKey = self:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pLooter, stateKey)

	if (state == self.M2_FIND_CARAVAN_LEADER) then
		CriesOfAlderaan:setState(pLooter, "coa3_" .. faction, Coa3Screenplay.M2_RETURNED_UNIT)

		CreatureObject(pLooter):sendSystemMessage("@theme_park/alderaan/act3/shared_imperial_missions:m3_data_disk_received")

		local pGhost = CreatureObject(pLooter):getPlayerObject()

		if (pGhost ~= nil) then
			local returnLocation = readVector3Data(playerID .. ":CoA3:returnLoc:")
			local returnPlanet = readStringData(playerID .. ":CoA3:returnPlanet:")

			if (returnPlanet ~= "") then
				local wayName = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_return_name_2"
				local wayDesc = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_return_desc_2"

				local wayID = PlayerObject(pGhost):addWaypoint(returnPlanet, wayName, wayDesc, returnLocation[1], returnLocation[3], WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)
			end
		end
		return 1
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
		local x = SceneObject(pBuilding):getPositionX()
		local y = SceneObject(pBuilding):getPositionY()
		local z = SceneObject(pBuilding):getPositionZ()

		if (i == 1) then
			x = x + 5
		elseif (i == 2) then
			x = x + 5
			y = y + 5
		elseif (i == 3) then
			x = x + 5
			y = y + 5
			z = z + 5
		elseif (i == 4) then
			x = x -5
		elseif (i == 5) then
			x = x - 5
			y = y - 5
		end

		playClientEffectLoc(pPlayer, "clienteffect/lair_damage_heavy.cef", planet, x, z, y, 0)
	end

	local faction = readStringData(ownerID .. ":CoA3:Faction:")
	local stateKey = Coa3Screenplay:getStateKey(faction)
	local state = CriesOfAlderaan:getState(pPlayer, stateKey)

	if (state >= self.M3_LOOTED_FLORA and state < self.M3_WAREHOUSE_DESTROYED) then
		CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M3_WAREHOUSE_DESTROYED)
	else
		writeData(ownerID .. "CoA3:extraFloraMission:", Coa3Screenplay.FLORA_WAREHOUSE_DESTROYED)
	end

	self:removeWaypoint(pPlayer)
	self:abortMission(pPlayer, Coa3Screenplay.FLORA_MISSION, 1)

	return 1
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
		return 1
	end

	local playerID = SceneObject(pKiller):getObjectID()
	local totalMobiles = readData(playerID .. ":CoA3:totalWarehouseMobiles:")

	totalMobiles = totalMobiles - 1

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

	if (state == self.M3_SENT_TO_WAREHOUSE) then
		CriesOfAlderaan:setState(pLooter, stateKey, Coa3Screenplay.M3_LOOTED_FLORA)
		return 1
	end

	return 0
end

function Coa3Screenplay:enteredFinalMission(pArea, pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() or pArea == nil) then
		return 0
	end

	local areaID = SceneObject(pArea):getObjectID()
	local areaOwnerID = readData(areaID .. ":CoA3:ownerID:")
	local playerID = SceneObject(pPlayer):getObjectID()
	local faction = readStringData(playerID .. ":CoA3:Faction:")

	if (areaOwnerID == playerID) then
		self:spawnFinalMobiles(pPlayer, pArea)

		if (faction == "rebel") then
			local time = getRandomNumber(60, 90)

			createEvent(time * 1000, "Coa3Screenplay", "spawnAssaultWave", pArea, "")

			local stateKey = self:getStateKey(faction)
			CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M5_DEFENDING)
		end

		return 1
	end

	return 0
end

function Coa3Screenplay:rebelDefendMobileKilled(pMobile, pKiller)
	if (pMobile == nil or pKiller == nil) then
		return 1
	end

	local mobileID = SceneObject(pMobile):getObjectID()
	local ownerID = readData(mobileID .. ":CoA3:ownerID:")

	local mobFaction = CreatureObject(pMobile):getFaction()

	if (mobFaction == FACTIONREBEL) then
		local totalGuards = readData(ownerID .. ":CoA3:totalGuards:")
		totalGuards = totalGuards - 1

		if (totalGuards <= 0) then
			local pOwner = getSceneObject(ownerID)

			if (pOwner == nil) then
				return 1
			end

			local ownerFaction = CreatureObject(pOwner):getFaction()

			if (ownerFaction == FACTIONIMPERIAL) then
				-- Trigger destructible
				local terminalID = readData(ownerID .. ":CoA3:finalTerminal:")
				local pTerminal = getSceneObject(terminalID)

				if (pTerminal == nil) then
					deleteData(ownerID .. ":CoA3:totalGuards:")
					self:abortMission(pOwner, Coa3Screenplay.FACILITY, 1)

					local stateKey = self:getStateKey(ownerFaction)
					CriesOfAlderaan:setState(pOwner, stateKey, Coa3Screenplay.M5_GO_TO_FACILITY)

					return 1
				end

				SceneObject(pTerminal):setObjectMenuComponent("CoA3DestroyFacilityTerminal")
				return 1
			elseif (ownerFaction == FACTIONREBEL) then
				-- Mission failed
				if (SceneObject(pOwner):isCreatureObject()) then
					CreatureObject(pOwner):sendSystemMessage("@theme_park/alderaan/act3/shared_rebel_missions:mission_failed")
				end

				deleteData(ownerID .. ":CoA3:totalGuards:")
				self:abortMission(pOwner, Coa3Screenplay.FACILITY, 1)

				local stateKey = self:getStateKey(ownerFactionFaction)
				CriesOfAlderaan:setState(pOwner, stateKey, Coa3Screenplay.M4_COMMANDER)
			end

			return 1
		end

		writeData(ownerID .. ":CoA3:totalGuards:", totalGuards)
	elseif (mobFaction == FACTIONIMPERIAL) then
		local totalAttackers = readData(ownerID .. ":CoA3:totalAttackers:")
		local waveNum = readData(ownerID .. ":CoA3:assaultNumber:")

		totalAttackers = totalAttackers - 1

		if (totalAttackers <= 0 and waveNum >= 3) then
			-- Mission Success
			local pOwner = getSceneObject(ownerID)

			if (pOwner ~= nil) then
				self:grantCoA3Badge(pOwner)
			end

			deleteData(ownerID .. ":CoA3:totalAttackers:")
			deleteData(ownerID .. ":CoA3:assaultNumber:")
			return 1
		end

		writeData(ownerID .. ":CoA3:totalAttackers:", totalAttackers)
	end

	return 0
end

-- =========== End Observers ===========


-- ======== General Functions =========

function Coa3Screenplay:destroyFacility(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local facilityID = readData(playerID .. ":CoA3:facilityID:")
	local pFacility = getSceneObject(facilityID)

	if (pFacility == nil) then
		return
	end

	local planet = SceneObject(pFacility):getZoneName()

	for i = 1, 5, 1 do
		local x = SceneObject(pFacility):getPositionX()
		local y = SceneObject(pFacility):getPositionY()
		local z = SceneObject(pFacility):getPositionZ()

		if (i == 1) then
			x = x + 5
		elseif (i == 2) then
			x = x + 5
			y = y + 5
		elseif (i == 3) then
			x = x + 5
			y = y + 5
			z = z + 5
		elseif (i == 4) then
			x = x - 5
		elseif (i == 5) then
			x = x - 5
			y = y - 5
		end

		playClientEffectLoc(pPlayer, "clienteffect/lair_damage_heavy.cef", planet, x, z, y, 0)
	end

	self:grantCoA3Badge(pPlayer)
	self:cleanupMission(pPlayer)
end

function Coa3Screenplay:grantCoA3Badge(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local faction = CreatureObject(pPlayer):getFaction()
	local factionString = self:getFactionString(pPlayer)
	local badgeNum

	CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_" .. factionString .. "_missions:mission_complete")

	if (faction == FACTIONREBEL) then
		badgeNum = EVENT_COA3_REBEL -- 'event_coa3_rebel', 'Event: Cries of Alderaan: Final Chapter'
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_rebel_missions:mission_complete")
	else
		badgeNum = EVENT_COA3_IMPERIAL -- 'event_coa3_imperial', 'Event: Cries of Alderaan: Final Chapter'
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):awardBadge(badgeNum)

		if (faction == FACTIONREBEL) then
			local rebelScore = getQuestStatus("CriesOfAlderaan:rebelScore:")

			if (rebelScore == nil) then
				rebelScore = 0
			end

			rebelScore = rebelScore + 1
			setQuestStatus("CriesOfAlderaan:rebelScore:", rebelScore)

			ThemeParkLogic:giveFaction(pPlayer, "rebel", 750)
			CreatureObject(pPlayer):playMusicMessage("sound/music_lando_theme.snd")
		else
			local imperialScore = getQuestStatus("CriesOfAlderaan:imperialScore:")

			if (imperialScore == nil) then
				imperialScore = 0
			end

			imperialScore = imperialScore + 1
			setQuestStatus("CriesOfAlderaan:imperialScore:", imperialScore)

			ThemeParkLogic:giveFaction(pPlayer, "imperial", 750)
			CreatureObject(pPlayer):playMusicMessage("sound/music_darth_vader_theme.snd")
		end
	end

	local stateKey = self:getStateKey(faction)
	CriesOfAlderaan:setState(pPlayer, stateKey, Coa3Screenplay.M5_COMPLETE)

	self:cleanupMission(pPlayer)
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

function Coa3Screenplay:abortMission(pPlayer, missionNum, returnToNpc)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	if (returnToNpc >= 1) then
		local returnLocation = readVector3Data(playerID .. ":CoA3:returnLoc:")
		local returnPlanet = readStringData(playerID .. ":CoA3:returnPlanet:")

		if (returnPlanet ~= "") then
			local pGhost = CreatureObject(pPlayer):getPlayerObject()

			if (pGhost ~= nil) then
				local faction = readStringData(playerID .. ":CoA3:Faction:")
				local wayName = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_return_name_" .. missionNum
				local wayDesc = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_return_desc_" .. missionNum

				local wayID = PlayerObject(pGhost):addWaypoint(returnPlanet, wayName, wayDesc, returnLocation[1], returnLocation[3], WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)

				writeData(playerID .. ":CoA3:ReturnWaypoint:", wayID)
			end
		end
	end

	self:cleanupMission(pPlayer)
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
				local objectID = SceneObject(pObject):getObjectID()
				deleteData(objectID .. ":CoA3:ownerID:")

				SceneObject(pObject):destroyObjectFromWorld()
			end
		end
	end

	local meshID = readData(playerID .. ":CoA3:navMesh:")

	if (meshID > 0) then
		destroyNavMesh(meshID)
	end

	deleteVector3Data(playerID .. ":CoA3:returnLoc:")
	deleteData(playerID .. ":CoA3:NpcID:")
	deleteData(playerID .. ":CoA3:totalWarehouseMobiles:")
	deleteData(playerID .. ":CoA3:floraDrum:")

	deleteData(playerID .. ":CoA3:totalGuards:")
	deleteData(playerID .. ":CoA3:totalAttackers:")
	deleteData(playerID .. ":CoA3:assaultNumber:")
	deleteData(playerID .. ":CoA3:facilityID:")
	deleteData(playerID .. ":CoA3:finalTerminal:")
	deleteData(playerID .. ":CoA3:redirectMinDistance:")
	deleteData(playerID .. ":CoA3:redirectMaxDistance:")
	deleteData(playerID .. ":CoA3:missionNum:")

	deleteStringData(playerID .. ":CoA3:returnPlanet:")
	deleteStringData(playerID .. ":CoA3:redirectPlanet:")
	deleteStringData(playerID .. ":CoA3:spawnName:")
	deleteStringData(playerID .. ":CoA3:Faction:")

	deleteStringVectorSharedMemory(playerID .. ":CoA3:missionObjects:")
end

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
	deleteData(playerID .. ":CoA3:Waypoint:")
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
	end

	CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_" .. faction .. "_missions:m" .. missionNum .. "_init_failure")
	self:abortMission(pPlayer, missionNum, 1)
end

function Coa3Screenplay:getFactionString(pCreature)
	if (pCreature == nil) then
		return ""
	end

	local factionString = ""

	if (SceneObject(pCreature):isPlayerCreature()) then
		local playerID = SceneObject(pCreature):getObjectID()
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

function Coa3Screenplay:getRandomCommander(faction)
	local options = {}
	local coa3commanders = self.coa3commanders

	for i = 1, #coa3commanders, 1 do
		local commanderID = readData(i .. ":CoA3:commanderID:")

		local commander = coa3commanders[i]
		local commanderString = "veers"

		if (faction == "rebel") then
			commanderString = "leia"
		end

		if (string.find(commander[2], commanderString) and isZoneEnabled(commander[1])) then
			table.insert(options, commanderID)
		end
	end

	if #options > 0 then
		local option = options[getRandomNumber(1, #options)]
		return option
	else
		return 0
	end
end
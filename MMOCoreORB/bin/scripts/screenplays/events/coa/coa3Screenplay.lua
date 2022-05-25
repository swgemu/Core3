Coa3Screenplay = ScreenPlay:new {
	PRE_INFO_OFFICER = 1, -- Sent to info officer
	PRE_RETURN = 2, -- Return to coordinator
	M1_FIND_LOOKOUT = 3, -- Sent to lookout
	M1_TRIAL_COMPLETED = 4, -- Passed convo trial
	M1_REFUSED = 5, -- Refused to do repairs
	M2_FIND_CARAVAN_LEADER = 6, -- Sent to caravan leader
	M2_RETURNED_UNIT = 9,	-- Returned repaired grav unit
	M3_TACTICAL_OFFICER = 10, -- Sent to tactical officer
	M3_SENT_TO_WAREHOUSE = 11, -- Tactical officer sent player to flora warehouse
	M3_LOOTED_FLORA = 11, -- Flora looted
	M3_WAREHOUSE_DESTROYED = 12, -- Warehouse destroyed, return to tactical officer
	M3_COMPLETE = 13, -- Flora turned in
	M4_CELEBRITY = 14, -- Sent to princess/veers
	M5_GO_TO_FACILITY = 15, -- Sent to defend facility
	M5_DEFENDING = 16, -- Defense in progress
	M5_COMPLETE = 17, -- Defense complete
}

registerScreenPlay("Coa3Screenplay", true)

function Coa3Screenplay:start()
--self:spawnStaticNpcs()
end

function Coa3Screenplay:setupMission(pPlayer, pNpc, faction, missionNum)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	local randPlanet = self:getMissionPlanet()
	local minDistance, maxDistance, spawnName

	if (missionNum == 1) then
		minDistance = 1500
		maxDistance = 2000
		spawnName = "coa3_lookout"
	elseif (missionNum == 3) then
		minDistance = 1500
		maxDistance = 2000
		spawnName = "object/building/theme_park/alderaan/act3/flora_warehouse.iff"
	elseif (missionNum == 4) then
	-- TODO commander
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	writeVector3Data(playerID .. ":coa3returnLoc", SceneObject(pNpc):getWorldPositionX(), 0, SceneObject(pNpc):getWorldPositionY())
	writeStringData(playerID .. ":coa3returnPlanet", SceneObject(pNpc):getZoneName())
	writeStringData(playerID .. ":coa3Faction", faction)
	writeStringData(playerID .. ":coa3redirectPlanet", randPlanet)
	writeData(playerID .. ":coa3redirectMinDistance", minDistance)
	writeData(playerID .. ":coa3redirectMaxDistance", maxDistance)
	writeData(playerID .. ":coa3missionNum", missionNum)
	writeStringData(playerID .. ":coa3spawnName", spawnName)

	self:createMissionWaypoint(pPlayer, 8190, 8190, randPlanet, missionNum, faction)
	CreatureObject(pPlayer):sendSystemMessage("@mission/mission_generic:target_located_" .. randPlanet)

	dropObserver(ZONESWITCHED, "Coa3Screenplay", "updateMissionLocation", pPlayer)
	createObserver(ZONESWITCHED, "Coa3Screenplay", "updateMissionLocation", pPlayer)
end

function Coa3Screenplay:createMissionWaypoint(pPlayer, x, y, planet, missionNum, faction)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	local wayName = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_name_" .. missionNum
	local wayDesc = "@theme_park/alderaan/act3/shared_" .. faction .. "_missions:waypoint_desc_" .. missionNum

	local wayID = PlayerObject(pGhost):addWaypoint(planet, wayName, wayDesc, x, y, WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)

	writeData(playerID .. ":coa3Waypoint", wayID)
end

function Coa3Screenplay:removeMissionWaypoint(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local wayID = readData(playerID .. ":coa3Waypoint")
	PlayerObject(pGhost):removeWaypoint(wayID, true)
end

function Coa3Screenplay:updateMissionLocation(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local planet = readStringData(playerID .. ":coa3redirectPlanet")

	if (planet == "") then
		return 1
	end

	local zoneName = SceneObject(pPlayer):getZoneName()

	if (zoneName ~= planet) then
		return 0
	end

	self:removeMissionWaypoint(pPlayer)

	local areaID = readData(playerID .. ":coa3ActiveArea")

	if (areaID ~= 0) then
		local pArea = getSceneObject(areaID)

		if (pArea ~= nil) then
			SceneObject(pArea):destroyObjectFromWorld()
		end

		deleteData(playerID .. ":coa3ActiveArea")
		deleteData(areaID .. ":ownerID")
	end


	local faction = readStringData(playerID .. ":coa3Faction")
	local missionNum = readData(playerID .. ":coa3missionNum")
	local missionLoc = getSpawnArea(zoneName, SceneObject(pPlayer):getWorldPositionX(), SceneObject(pPlayer):getWorldPositionY(), 1500, 2000, 20, 10, true)
	writeVector3Data(playerID .. ":coa3missionLoc", missionLoc[1], missionLoc[2], missionLoc[3])

	local pActiveArea = spawnActiveArea(spawnPlanet, "object/active_area.iff", missionLoc[1], missionLoc[2], missionLoc[3], 100, 0)

	if (pActiveArea == nil) then
		return 0
	end

	areaID = SceneObject(pActiveArea):getObjectID()
	writeData(playerID .. ":coa3MissionArea", areaID)
	writeData(areaID .. ":ownerID", playerID)
	createObserver(ENTEREDAREA, "Coa3Screenplay", "enteredMissionArea", pActiveArea)

	self:createMissionWaypoint(pPlayer, missionLoc[1], missionLoc[3], planet, missionNum, faction)

	deleteStringData(playerID .. ":coa3redirectPlanet")
	deleteData(playerID .. ":coa3redirectMinDistance")
	deleteData(playerID .. ":coa3redirectMaxDistance")

	return 1
end

function Coa3Screenplay:enteredMissionArea(pArea, pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local ownerID = readData(SceneObject(pArea):getObjectID() .. ":ownerID")

	if (ownerID ~= SceneObject(pPlayer):getObjectID()) then
		return 0
	end

	local areaRadius = ActiveArea(pArea):getRadius()
	local faction = readStringData(playerID .. ":coa3Faction")
	local missionNum = readData(playerID .. ":coa3missionNum")

	if (radius == 100) then
		local spawnName = readStringData(playerID .. ":coa3spawnName")

		if (string.find(spawnName, "iff") == nil) then
			local pMobile = spawnMobile(SceneObject(pArea):getZoneName(), spawnName, 0, SceneObject(pArea):getWorldPositionX(), SceneObject(pArea):getWorldPositionZ(), SceneObject(pArea):getWorldPositionY(), 0, 0)

			if (pMobile ~= nil) then
				local mobileID = SceneObject(pMobile):getObjectID()
				writeData(ownerID .. ":coa3NpcID", mobileID)
				writeData(mobileID .. ":ownerID", ownerID)
			end
		end

		local pActiveArea = spawnActiveArea(spawnPlanet, "object/active_area.iff", SceneObject(pArea):getWorldPositionX(), SceneObject(pArea):getWorldPositionZ(), SceneObject(pArea):getWorldPositionY(), 20, 0)

		if (pActiveArea ~= nil) then
			local areaID = SceneObject(pActiveArea):getObjectID()
			writeData(playerID .. ":coa3ActiveArea", areaID)
			writeData(areaID .. ":ownerID", playerID)
			createObserver(ENTEREDAREA, "Coa3Screenplay", "enteredLookoutArea", pActiveArea)
		end
	else
		local mobileID = readData(ownerID .. ":coa3NpcID")

		if (mobileID ~= 0) then
			local pMobile = getSceneObject(mobileID)

			if (pMobile == nil) then
				CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_" .. faction .. "_missions:m" .. missioNum .. "_init_failure")
				self:abortMission(pPlayer, missionNum, true)
			else
				self:removeWaypoint(pPlayer)
			end
		else
			self:removeWaypoint(pPlayer)
		end
	end

	deleteData(SceneObject(pArea):getObjectID() .. ":ownerID")
	SceneObject(pArea):destroyObjectFromWorld()

	deleteData(playerID .. ":coa3MissionArea")

	return 1
end

function Coa3Screenplay:abortMission(pPlayer, missionNum, returnToNpc)
	if (pPlayer == nil) then
		return
	end

	local state = CriesOfAlderaan:getState(pPlayer, "coa3_rebel")

	self:cleanupMission(pPlayer)

	if (returnToNpc) then
	end
end

function Coa3Screenplay:getMissionPlanet()
	local planets = { "dathomir", "endor", "yavin4" }
	return planets[getRandomNumber(1, #planets)]
end

function Coa3Screenplay:removeWaypoint(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local wayID = readData(playerID .. ":coa3Waypoint")

	PlayerObject(pGhost):removeWaypoint(wayID, true)
	deleteData(playerID .. ":coa3Waypoint")
end

function Coa2Screenplay:giveWaypoint(pPlayer, pTarget, name, desc)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return 0
	end

	local x = SceneObject(pTarget):getWorldPositionX()
	local y = SceneObject(pTarget):getWorldPositionY()
	local planet = SceneObject(pTarget):getZoneName()

	local wayID = PlayerObject(pGhost):addWaypoint(planet, name, desc, x, y, WAYPOINTYELLOW, true, true, WAYPOINTQUESTTASK)

	writeData(playerID .. ":coa3Waypoint", wayID)
end

function Coa3Screenplay:cleanupMission(pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	SceneObject(pPlayer):cancelPendingTask("Coa3Screenplay", "timeoutMission")

	self:removeWaypoint(pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()
	local targetID = readData(playerID .. ":coa3NpcID")
	local pTarget = getSceneObject(targetID)

	if pTarget ~= nil then
		SceneObject(pTarget):destroyObjectFromWorld()
	end

	deleteData(targetID .. ":ownerID")
	deleteData(playerID .. ":coa3NpcID")

	local areaID = readData(playerID .. ":coa3ActiveArea")
	local pArea = getSceneObject(areaID)

	if pArea ~= nil then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	deleteData(playerID .. ":coa3ActiveArea")
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

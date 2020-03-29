Coa3Screenplay = ScreenPlay:new {
	M1_INFO_OFFICER = 1, -- Sent to info officer
	M1_RETURN = 2, -- Return to coordinator
	M2_FIND_LOOKOUT = 3, -- Sent to lookout
	M2_TRIAL_COMPLETED = 4, -- Passed convo trial
	M3_REFUSED = 5, -- Refused to do repairs
	M3_FIND_CARAVAN_LEADER = 6, -- Sent to caravan leader
	M3_GIVEN_UNIT = 7, -- Received grav unit to repair
	M3_REPAIRED_UNIT = 8, -- Grav unit repaired
	M3_RETURNED_UNIT = 9,	-- Returned grav unit
	M4_TACTICAL_OFFICER = 10, -- Sent to tactical officer
	M4_LOOTED_FLORA = 11, -- Flora looted
	M4_WAREHOUSE_DESTROYED = 12, -- Warehouse destroyed, return to tactical officer
	M4_COMPLETE = 13, -- Flora turned in
	M5_CELEBRITY = 14, -- Sent to princess/veers
	M5_GO_TO_FACILITY = 15, -- Sent to defend facility
	M5_DEFENDING = 16, -- Defense in progress
	M5_COMPLETE = 17, -- Defense complete
}

registerScreenPlay("Coa3Screenplay", true)

function Coa3Screenplay:start()
	self:spawnStaticNpcs()
end

function Coa3Screenplay:spawnStaticNpcs()
	for i = 1, #self.npcs do
		local npc = self.npcs[i]

		if isZoneEnabled(npc[2]) then
			local pNpc = spawnMobile(npc[2], npc[1], 0, npc[3], npc[4], npc[5], npc[6], 0)

			if pNpc ~= nil then
				writeData("coa3NpcID_" .. i, SceneObject(pNpc):getObjectID())
			end
		end
	end
end

function Coa3Screenplay:startLookoutMission(pPlayer, faction)
	CriesOfAlderaan:setState(pPlayer, "rebel_coa3", self.M2_FIND_LOOKOUT)
	local randPlanet = getMissionPlanet()

	if (randPlanet == nil or randPlanet == "") then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	writeStringData(playerID .. ":coa3Planet", randPlanet)
	writeStringData(playerID .. ":coa3Faction", faction)

	dropObserver(ZONESWITCHED, "Coa3Screenplay", "updateLookoutLocation", pPlayer)
	createObserver(ZONESWITCHED, "Coa3Screenplay", "updateLookoutLocation", pPlayer)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		if (faction == "rebel") then
			self:giveWaypoint(pPlayer, pActiveArea, "@theme_park/alderaan/act3/shared_rebel_missions:waypoint_name_1", "@theme_park/alderaan/act3/shared_rebel_missions:waypoint_desc_1")
		else
			self:giveWaypoint(pPlayer, pActiveArea, "@theme_park/alderaan/act3/shared_imperial_missions:waypoint_name_1", "@theme_park/alderaan/act3/shared_rebel_missions:waypoint_desc_1")
		end
	end
end

function Coa3Screenplay:updateLookoutLocation(pPlayer)
	if (CriesOfAlderaan:getState(pPlayer, stateName) ~= self.M2_FIND_LOOKOUT) then
		deleteStringData(SceneObject(pPlayer):getObjectID() .. ":coa3Planet")
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local planet = readStringData(playerID .. ":coa3Planet")

	if (planet == "") then
		return 1
	end

	local zoneName = SceneObject(pPlayer):getZoneName()

	if (zoneName ~= planet) then
		return 0
	end

	local areaID = readData(playerID .. ":coa3ActiveArea")

	if (areaID ~= 0) then
		local pArea = getSceneObject(areaID)

		if (pArea ~= nil) then
			SceneObject(pArea):destroyObjectFromWorld()
		end

		deleteData(playerID .. ":coa3ActiveArea")
	end

	local missionLoc = getSpawnArea(zoneName, SceneObject(pPlayer):getWorldPositionX(), SceneObject(pPlayer):getWorldPositionY(), 1500, 2000, 20, 10, true)
	local pActiveArea = spawnActiveArea(spawnPlanet, "object/active_area.iff", missionLoc[1], missionLoc[2], missionLoc[3], 100, 0)

	if (pActiveArea == nil) then
		return 0
	end

	areaID = SceneObject(pActiveArea):getObjectID()
	writeData(playerID .. ":coa3ActiveArea", areaID)
	writeData(areaID .. ":ownerID", playerID)
	createObserver(ENTEREDAREA, "Coa3Screenplay", "enteredLookoutArea", pActiveArea)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		local faction = readStringData(playerID .. ":coa3Faction")

		if (faction == "rebel") then
			self:giveWaypoint(pPlayer, pActiveArea, "@theme_park/alderaan/act3/shared_rebel_missions:waypoint_name_1", "@theme_park/alderaan/act3/shared_rebel_missions:waypoint_desc_1")
		else
			self:giveWaypoint(pPlayer, pActiveArea, "@theme_park/alderaan/act3/shared_imperial_missions:waypoint_name_1", "@theme_park/alderaan/act3/shared_rebel_missions:waypoint_desc_1")
		end
	end

	deleteStringData(playerID .. ":coa3Planet")

	return 1
end

function Coa2Screenplay:enteredLookoutArea(pArea, pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local ownerID = readData(SceneObject(pArea):getObjectID() .. ":ownerID")

	if (ownerID ~= SceneObject(pPlayer):getObjectID()) then
		return 0
	end

	local areaRadius = ActiveArea(pArea):getRadius()

	if (radius == 100) then
		local pMobile = spawnMobile(SceneObject(pArea):getZoneName(), "coa3_lookout", 0, SceneObject(pArea):getWorldPositionX(), SceneObject(pArea):getWorldPositionZ(), SceneObject(pArea):getWorldPositionY(), 0, 0)

		if (pMobile ~= nil) then
			local mobileID = SceneObject(pMobile):getObjectID()
			writeData(ownerID .. ":coa3NpcID", mobileID)
			writeData(mobileID .. ":ownerID", ownerID)
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
		local pMobile = getSceneObject(mobileID)

		if (pMobile == nil) then
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act3/shared_rebel_missions:m1_init_failure") -- It appears the lookout is no longer at this location.
			self:abortMission(pPlayer, true)
		else
			self:removeWaypoint(pPlayer)
		end
	end

	deleteData(SceneObject(pArea):getObjectID() .. ":ownerID")
	return 1
end

function Coa3Screenplay:abortMission(pPlayer, returnToNpc)
	local state = CriesOfAlderaan:getState(pPlayer, "rebel_coa3")
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		local waypointID = readData(ownerID .. ":coa3Waypoint")
		PlayerObject(pGhost):removeWaypoint(waypointID, true)
	end

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

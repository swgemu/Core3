
--[[
Quest states:
1 - m1 refused/aborted
2 - m1 active
3 - m1 return
4 - m1 complete
5 - m2 refused/aborted
6 - m2 active
7 - m2 return
8 - m2 complete
9 - m3/4 active
10 - m3/4 complete
11 - m5 refused/aborted
12 - m5 active
13 - m5 complete
]]

Coa2Screenplay = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "Coa2Screenplay",

	staticNpcs = {
		{"coa2_imperial_coordinator", "naboo", 5144, -192, 6674, 50},
		{"coa2_imperial_coordinator", "naboo", -5431.7, 6, 4168.5, 173},
		{"coa2_imperial_coordinator", "rori", -5255.8, 80, -2254.5, -99},
		{"coa2_imperial_coordinator", "rori", 5347.5, 80, 5617.5, -8},
		{"coa2_imperial_coordinator", "tatooine", -1131.2, 12, -3661.2, -36},
		{"coa2_rebel_coordinator", "corellia", -5218.1, 21, -2602.6, -11},
		{"coa2_rebel_coordinator", "corellia", 95.3, 28, -4519.1, -91},
		{"coa2_rebel_coordinator", "talus", 4065.1, 2, 5289.5, 130},
		{"coa2_rebel_coordinator", "tatooine", 3286.3, 5, -4524.8, -48},
		{"coa2_rebel_coordinator", "tatooine", -2927.5, 5, 2574.3, 131},
		{"imperial_recruiter", "dantooine", 2503.7, 14, -2049, 179},
		{"imperial_recruiter", "dathomir", -6306, 122.9, -532.5, -34},
		{"imperial_recruiter", "endor", -1950.7, 146.6, 1051.8, -54},
		{"imperial_recruiter", "lok", -2572.2, 21.7, -862.5, 101},
		{"imperial_recruiter", "yavin4", 1588.7, 50.5, -3538.5, 38},
		{"rebel_recruiter", "dantooine", 6876.7, 60, -2258.4, -78},
		{"rebel_recruiter", "dathomir", -48.3, 142.1, 88.1, -139},
		{"rebel_recruiter", "endor", 4018.8, 7.4, 2966.2, -53},
		{"rebel_recruiter", "lok", -4749, 4, 3525.5, 113},
		{"rebel_recruiter", "yavin4", -4237, 183, 2284.1, -165},
	},

	commanders = {
		{"coa2_imperial_commander", "dantooine", 2505.7, 14, -2053.4, -139},
		{"coa2_imperial_commander", "dathomir", -6303.1, 123.2, -529.8, -42},
		{"coa2_imperial_commander", "endor", -1954.1, 146.6, 1051.9, -32},
		{"coa2_imperial_commander", "lok", -2568.4, 21.7, -861.4, 159},
		{"coa2_imperial_commander", "yavin4", 1586.4, 50.5, -3533.3, 46},
		{"coa2_rebel_commander", "dantooine", 6874.4, 60, -2253, -126},
		{"coa2_rebel_commander", "dathomir", -48.2, 142.3, 85.9, -60},
		{"coa2_rebel_commander", "endor", 4021.1, 7.4, 2970.2, -82},
		{"coa2_rebel_commander", "lok", -4753, 4, 3516.4, 111},
		{"coa2_rebel_commander", "yavin4", -4237.2, 183.5, 2276, -23},
	}
}

registerScreenPlay("Coa2Screenplay", true)

function Coa2Screenplay:start()
	self:spawnStaticNpcs()
end

function Coa2Screenplay:spawnStaticNpcs()
	for i = 1, # self.staticNpcs do
		local npc = self.staticNpcs[i]
		if isZoneEnabled(npc[2]) then
			spawnMobile(npc[2], npc[1], 0, npc[3], npc[4], npc[5], npc[6], 0)
		end
	end

	for i = 1, # self.commanders do
		local npc = self.commanders[i]
		if isZoneEnabled(npc[2]) then
			local pNpc = spawnMobile(npc[2], npc[1], 0, npc[3], npc[4], npc[5], npc[6], 0)

			if pNpc ~= nil then
				writeData("coaCommanderID_" .. i, SceneObject(pNpc):getObjectID())
			else
				deleteData("coaCommanderID_" .. i)
			end
		end
	end
end

function Coa2Screenplay:hasDisk(pPlayer, diskType)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return false
	end

	local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/encoded_disk/encoded_disk_base.iff", false)

	if pItem == nil then
		return false
	end

	local name = SceneObject(pItem):getObjectName()

	if string.find(name, diskType) ~= nil then
		return true
	end

	return false
end

function Coa2Screenplay:giveWaypoint(pPlayer, pTarget, name, desc, commander)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return 0
	end

	local x = SceneObject(pTarget):getWorldPositionX()
	local y = SceneObject(pTarget):getWorldPositionY()
	local planet = SceneObject(pTarget):getZoneName()

	local wayID = PlayerObject(pGhost):addWaypoint(planet, name, desc, x, y, 2, true, true, 0, commander)

	return wayID
end

function Coa2Screenplay:removeWaypoint(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local wayID = readData(playerID .. ":coaWayID")

	PlayerObject(pGhost):removeWaypoint(wayID, true)
	deleteData(playerID .. ":coaWayID")
end

function Coa2Screenplay:spawnNpc(pSource, template, minDist, maxDist, force)
	local sourceX = SceneObject(pSource):getWorldPositionX()
	local sourceY = SceneObject(pSource):getWorldPositionY()
	local planet = SceneObject(pSource):getZoneName()

	local spawnPoint = getSpawnPoint(planet, sourceX, sourceY, minDist, maxDist, force)

	if spawnPoint == nil then
		return nil
	end

	local pNpc = spawnMobile(planet, template, 0, spawnPoint[1], spawnPoint[2], spawnPoint[3], getRandomNumber(360) - 180, 0)

	return pNpc
end

function Coa2Screenplay:spawnObject(pSource, template, minDist, maxDist)
	local sourceX = SceneObject(pSource):getWorldPositionX()
	local sourceY = SceneObject(pSource):getWorldPositionY()
	local planet = SceneObject(pSource):getZoneName()

	local spawnPoint = getSpawnPoint(planet, sourceX, sourceY, minDist, maxDist)

	if spawnPoint == nil then
		return nil
	end

	local pObject = spawnSceneObject(planet, template, spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, getRandomNumber(360) - 180)

	return pObject
end

function Coa2Screenplay:getRandomCommander(faction)
	local options = {}

	for i = 1, # self.commanders do
		local commanderID = readData("coaCommanderID_" .. i)

		if commanderID ~= nil and commanderID ~= 0 then
			local npc = self.commanders[i]
			if string.find(npc[1], faction) ~= nil and isZoneEnabled(npc[2]) then
				table.insert(options, commanderID)
			end
		end
	end

	if # options > 0 then
		local option = options[getRandomNumber(1, # options)]
		return option
	else
		return 0
	end
end

function Coa2Screenplay:startMissionOne(pPlayer, conversingNPC, faction)
	if pPlayer == nil or conversingNPC == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local file = "@theme_park/alderaan/act2/shared_" .. faction .. "_missions"
	local playerID = SceneObject(pPlayer):getObjectID()

	local pNpc

	if faction == "imperial" then
		pNpc = self:spawnNpc(pPlayer, "coa2_imperial_informant", 1000, 1500, false)
	elseif faction == "rebel" then
		pNpc = self:spawnNpc(pPlayer, "coa2_rebel_sympathizer", 1000, 1500, false)
	end

	if pNpc == nil then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":m1_init_failure")
		return
	end

	writeData(playerID .. ":coaTargetID", SceneObject(pNpc):getObjectID())

	local wayName = file .. ":waypoint_name_1"
	local wayDesc = file .. ":waypoint_desc_1"
	local wayID = self:giveWaypoint(pPlayer, pNpc, wayName, wayDesc, 0)

	if wayID == 0 then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":waypoint_failure")
		self:cleanupMission(pPlayer)
		return
	end

	writeData(playerID .. ":coaCoordinatorID", SceneObject(conversingNPC):getObjectID())
	writeData(playerID .. ":coaWayID", wayID)
	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 2)

	SceneObject(pPlayer):addPendingTask(1800000, "Coa2Screenplay", "timeoutMission")
end

function Coa2Screenplay:progressMissionOne(pPlayer, faction)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local file = "@theme_park/alderaan/act2/shared_" .. faction .. "_missions"

	if faction == "rebel" and SceneObject(pInventory):isContainerFullRecursive() then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":m1_data_disk_denied")
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local coordinatorID = readData(playerID .. ":coaCoordinatorID")
	local pNpc = getSceneObject(coordinatorID)

	if pNpc == nil then
		return
	end

	if faction == "rebel" then
		local pItem = giveItem(pInventory, "object/tangible/encoded_disk/encoded_disk_base.iff", -1)

		if pItem == nil then
			return
		end

		SceneObject(pItem):setObjectName("theme_park/alderaan/act2/shared_rebel_missions", "disk_name_encoded", true)
		CreatureObject(pPlayer):sendSystemMessage(file .. ":m1_data_disk_received")
	end

	self:removeWaypoint(pPlayer)

	local wayName = file .. ":waypoint_return_name_1"
	local wayDesc = file .. ":waypoint_return_desc_1"
	local wayID = self:giveWaypoint(pPlayer, pNpc, wayName, wayDesc, 0)

	if wayID == 0 then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":waypoint_failure")
		return
	end

	writeData(playerID .. ":coaWayID", wayID)
	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 3)
end

function Coa2Screenplay:finishMissionOne(pPlayer, faction)
	self:cleanupMission(pPlayer)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	PlayerObject(pGhost):addRewardedSchematic("object/draft_schematic/item/theme_park/alderaan/act2/dead_eye_decoder.iff", 2, 1, true)

	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 4)
end

function Coa2Screenplay:startMissionTwo(pPlayer, conversingNPC, faction)
	if pPlayer == nil or conversingNPC == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local file = "@theme_park/alderaan/act2/shared_" .. faction .. "_missions"
	local playerID = SceneObject(pPlayer):getObjectID()

	local pNpc

	if faction == "imperial" then
		pNpc = self:spawnNpc(pPlayer, "coa2_imperial_slicer", 1000, 1500, false)
	elseif faction == "rebel" then
		pNpc = self:spawnNpc(pPlayer, "coa2_lyda_skims", 1000, 1500, false)
	end

	if pNpc == nil then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":m3_init_failure")
		return
	end

	writeData(playerID .. ":coaTargetID", SceneObject(pNpc):getObjectID())

	if faction == "imperial" then
		createObserver(OBJECTDESTRUCTION, "Coa2Screenplay", "notifyImperialTargetDefeated", pNpc)
		writeData(SceneObject(pNpc):getObjectID() .. ":coaNpcOwnerID", playerID)
	end

	local wayName = file .. ":waypoint_name_3"
	local wayDesc = file .. ":waypoint_desc_3"
	local wayID = self:giveWaypoint(pPlayer, pNpc, wayName, wayDesc, 0)

	if wayID == 0 then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":waypoint_failure")
		self:cleanupMission(pPlayer)
		return
	end

	writeData(playerID .. ":coaWayID", wayID)

	local pSecondaryNpc

	for i = 1, 5 do
		if faction == "imperial" then
			pSecondaryNpc = self:spawnNpc(pNpc, "coa2_imperial_slicer_gang", 10, 15, true)
		elseif faction == "rebel" then
			pSecondaryNpc = self:spawnNpc(pNpc, "coa2_lyda_thug", 10, 15, true)
		end

		if pSecondaryNpc ~= nil then
			writeData(playerID .. ":coaSecondaryTargetID" .. i, SceneObject(pSecondaryNpc):getObjectID())
		end
	end

	writeData(playerID .. ":coaCoordinatorID", SceneObject(conversingNPC):getObjectID())
	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 6)

	SceneObject(pPlayer):addPendingTask(1800000, "Coa2Screenplay", "timeoutMission")
end

function Coa2Screenplay:notifyImperialTargetDefeated(pNpc, pAttacker)
	if pNpc == nil or pAttacker == nil or not SceneObject(pNpc):isCreatureObject() or not SceneObject(pAttacker):isCreatureObject() then
		return 0
	end

	local npcID = CreatureObject(pNpc):getObjectID()
	local attackerID = CreatureObject(pAttacker):getObjectID()

	local ownerID = readData(npcID .. ":coaNpcOwnerID")
	local pOwner = getCreatureObject(ownerID)

	if (pOwner == nil) then
		return 1
	end

	if ownerID ~= attackerID and (CreatureObject(pAttacker):isGroupedWith(pOwner) == false or CreatureObject(pOwner):isInRangeWithObject(pNpc, 128) == false) then
		CreatureObject(pNpc):setLootRights(nil)
		return 1
	end

	local state = tonumber(readScreenPlayData(pOwner, "imperial_coa2", "state"))

	if state == 6 then
		CreatureObject(pNpc):setLootRights(pOwner)

		local pInventory = CreatureObject(pNpc):getSlottedObject("inventory")
		if pInventory == nil then
			return 1
		end

		local inventory = LuaSceneObject(pInventory)

		local numberOfItems = inventory:getContainerObjectsSize()
		local diskTemplate = "object/tangible/encoded_disk/encoded_disk_base.iff"

		for i = 0, numberOfItems - 1, 1 do
			local pItem = inventory:getContainerObject(i)

			if pItem ~= nil then
				if diskTemplate == SceneObject(pItem):getTemplateObjectPath() then
					createObserver(ITEMLOOTED, "Coa2Screenplay", "notifyItemLooted", pItem)
					SceneObject(pItem):setObjectName("theme_park/alderaan/act2/shared_imperial_missions", "disk_name_slicer", true)
					break
				end
			end
		end

	elseif state == 12 then
		local count = tonumber(readData(ownerID .. ":coaDrallKilled"))

		if count == nil then
			count = 0
		end

		if count < 9 then
			writeData(ownerID .. ":coaDrallKilled", count + 1)
		else
			deleteData(ownerID .. ":coaDrallKilled")
			self:completeMissionFive(pOwner, "imperial")
		end
	end

	deleteData(npcID .. ":coaNpcOwnerID")

	return 1
end

function Coa2Screenplay:notifyRebelTargetDefeated(pNpc, pAttacker)
	if pNpc == nil or pAttacker == nil or not SceneObject(pNpc):isCreatureObject() or not SceneObject(pAttacker):isCreatureObject() then
		return 0
	end

	local npcID = CreatureObject(pNpc):getObjectID()
	local attackerID = CreatureObject(pAttacker):getObjectID()

	local ownerID = readData(npcID .. ":coaNpcOwnerID")
	local pOwner = getCreatureObject(ownerID)

	if (pOwner == nil) then
		return 1
	end

	if ownerID ~= attackerID and (CreatureObject(pAttacker):isGroupedWith(pOwner) == false or CreatureObject(pOwner):isInRangeWithObject(pNpc, 128) == false) then
		CreatureObject(pNpc):setLootRights(nil)
		return 1
	end

	local state = tonumber(readScreenPlayData(pOwner, "rebel_coa2", "state"))

	if state == 12 then
		CreatureObject(pOwner):sendSystemMessage("@theme_park/alderaan/act2/shared_rebel_missions:access_key_received")
		writeData(ownerID .. ":coaHasPassKey", 1)
	end

	deleteData(npcID .. ":coaNpcOwnerID")

	return 1
end

function Coa2Screenplay:notifyItemLooted(pItem, pLooter)
	if pItem == nil or pLooter == nil or not SceneObject(pLooter):isCreatureObject() then
		return 1
	end

	self:progressMissionTwo(pLooter, "imperial")

	return 1
end

function Coa2Screenplay:progressMissionTwo(pPlayer, faction)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local file = "@theme_park/alderaan/act2/shared_" .. faction .. "_missions"

	local playerID = SceneObject(pPlayer):getObjectID()
	local coordinatorID = readData(playerID .. ":coaCoordinatorID")
	local pNpc = getSceneObject(coordinatorID)

	if pNpc == nil then
		return
	end

	self:removeWaypoint(pPlayer)

	local wayName = file .. ":waypoint_return_name_3"
	local wayDesc = file .. ":waypoint_return_desc_3"
	local wayID = self:giveWaypoint(pPlayer, pNpc, wayName, wayDesc, 0)

	if wayID == 0 then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":waypoint_failure")
		return
	end

	writeData(playerID .. ":coaWayID", wayID)
	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 7)
end

function Coa2Screenplay:startMissionThree(pPlayer, conversingNPC, faction)
	if pPlayer == nil or conversingNPC == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local commanderID = self:getRandomCommander(faction)
	local pNpc = getSceneObject(commanderID)

	if pNpc == nil then
		CreatureObject(pPlayer):sendSystemMessage("Error: cannot find a commander")
		return
	end

	local file = "@theme_park/alderaan/act2/shared_" .. faction .. "_missions"
	local wayName = file .. ":waypoint_name_4"
	local wayDesc = file .. ":waypoint_desc_4"
	local wayID = self:giveWaypoint(pPlayer, pNpc, wayName, wayDesc, 1)

	if wayID == 0 then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":waypoint_failure")
		return
	end

	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 9)
end

function Coa2Screenplay:finishMissionFour(pPlayer, faction)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	PlayerObject(pGhost):increaseFactionStanding(faction, 250)

	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 10)
end

function Coa2Screenplay:startMissionFive(pPlayer, conversingNPC, faction)
	if pPlayer == nil or conversingNPC == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local file = "@theme_park/alderaan/act2/shared_" .. faction .. "_missions"
	local playerID = SceneObject(pPlayer):getObjectID()

	local pTarget

	if faction == "imperial" then
		pTarget = self:spawnObject(pPlayer, "object/building/poi/coa2_rebel_drall_camp.iff", 2000, 3000)
	elseif faction == "rebel" then
		pTarget = self:spawnObject(pPlayer, "object/building/poi/coa2_imperial_relay_station.iff", 2000, 3000)
	end

	if pTarget == nil then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":m5_init_failure")
		return
	end

	writeData(playerID .. ":coaTargetID", SceneObject(pTarget):getObjectID())

	local wayName = file .. ":waypoint_name_5"
	local wayDesc = file .. ":waypoint_desc_5"
	local wayID = self:giveWaypoint(pPlayer, pTarget, wayName, wayDesc, 0)

	if wayID == 0 then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":waypoint_failure")
		self:cleanupMission(pPlayer)
		return
	end

	writeData(playerID .. ":coaWayID", wayID)

	if faction == "imperial" then
		for i = 1, 9, 2 do
			local pNpc = self:spawnNpc(pTarget, "coa2_drall_scientist", 5, 12, true)

			if pNpc ~= nil then
				createObserver(OBJECTDESTRUCTION, "Coa2Screenplay", "notifyImperialTargetDefeated", pNpc)
				writeData(SceneObject(pNpc):getObjectID() .. ":coaNpcOwnerID", playerID)
				writeData(playerID .. ":coaSecondaryTargetID" .. i, SceneObject(pNpc):getObjectID())
			end

			pNpc = self:spawnNpc(pTarget, "coa2_drall_guard", 8, 20, true)

			if pNpc ~= nil then
				createObserver(OBJECTDESTRUCTION, "Coa2Screenplay", "notifyImperialTargetDefeated", pNpc)
				writeData(SceneObject(pNpc):getObjectID() .. ":coaNpcOwnerID", playerID)
				writeData(playerID .. ":coaSecondaryTargetID" .. (i + 1), SceneObject(pNpc):getObjectID())
			end
		end

	elseif faction == "rebel" then
		local pTower = SceneObject(pTarget):getChildObject(0)

		if pTower == nil or not SceneObject(pTower):isBuildingObject() then
			CreatureObject(pPlayer):sendSystemMessage(file .. ":m5_init_failure")
			self:cleanupMission(pPlayer)
			return
		end

		local pCell = BuildingObject(pTower):getNamedCell("spawn")

		if pCell == nil then
			CreatureObject(pPlayer):sendSystemMessage(file .. ":m5_init_failure")
			self:cleanupMission(pPlayer)
			return
		end

		SceneObject(pCell):setContainerInheritPermissionsFromParent(false)
		SceneObject(pCell):clearContainerDefaultAllowPermission(WALKIN)
		SceneObject(pCell):setContainerDefaultDenyPermission(WALKIN)
		cellID = SceneObject(pCell):getObjectID()
		writeData(playerID .. ":coaTowerCellID", cellID)

		local pTerminal = spawnSceneObject(SceneObject(pTower):getZoneName(), "object/tangible/theme_park/alderaan/act2/relay_station_terminal.iff", 0, 3.6, 0.2, cellID, 0, 1, 0, 0)

		if pTerminal == nil then
			CreatureObject(pPlayer):sendSystemMessage(file .. ":m5_init_failure")
			self:cleanupMission(pPlayer)
			return
		end

		SceneObject(pTerminal):setObjectMenuComponent("CoaRelayStationTerminalMenuComponent")
		SceneObject(pTerminal):setCustomObjectName("Imperial Relay Terminal")

		local pTowerArea = spawnActiveArea(SceneObject(pTower):getZoneName(), "object/active_area.iff", SceneObject(pTower):getWorldPositionX(), SceneObject(pTower):getWorldPositionZ(), SceneObject(pTower):getWorldPositionY(), 5, 0)

		if pTowerArea ~= nil then
			createObserver(ENTEREDAREA, "Coa2Screenplay", "notifyEnteredTowerArea", pTowerArea)
			writeData(SceneObject(pTowerArea):getObjectID() .. ":coaTowerOwnerID", playerID)
			writeData(playerID .. ":coaAreaID", SceneObject(pTowerArea):getObjectID())
		end

		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
		local pObject

		if pInventory ~= nil then
			pObject = giveItem(pInventory, "object/tangible/theme_park/alderaan/act2/interface_override_device.iff", -1, true)
		end

		if pObject == nil then
			CreatureObject(pPlayer):sendSystemMessage(file .. ":m5_init_failure")
			self:cleanupMission(pPlayer)
			return
		end

		local pNpc = self:spawnNpc(pTarget, "coa2_relay_captain", 10, 15, true)

		if pNpc ~= nil then
			createObserver(OBJECTDESTRUCTION, "Coa2Screenplay", "notifyRebelTargetDefeated", pNpc)
			writeData(SceneObject(pNpc):getObjectID() .. ":coaNpcOwnerID", playerID)
			writeData(playerID .. ":coaSecondaryTargetID" .. 1, SceneObject(pNpc):getObjectID())
		end

		for i = 2, 7 do
			pNpc = self:spawnNpc(pTarget, "coa2_relay_guard", 10, 20, true)

			if pNpc ~= nil then
				writeData(playerID .. ":coaSecondaryTargetID" .. i, SceneObject(pNpc):getObjectID())
			end
		end
	end

	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 12)

	SceneObject(pPlayer):addPendingTask(3600000, "Coa2Screenplay", "timeoutMission")
end

function Coa2Screenplay:notifyEnteredTowerArea(pArea, pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local ownerID = readData(SceneObject(pArea):getObjectID() .. ":coaTowerOwnerID")
	local hasPasskey = readData(ownerID .. ":coaHasPassKey")
	local cellID = readData(ownerID .. ":coaTowerCellID")
	local pCell = getSceneObject(cellID)

	if hasPasskey == 1 and playerID == ownerID and pCell ~= nil then
		SceneObject(pCell):clearContainerDefaultDenyPermission(WALKIN)
		SceneObject(pCell):setContainerDefaultAllowPermission(WALKIN)

		local pTower = SceneObject(pCell):getParent()

		if pTower ~= nil and SceneObject(pTower):isBuildingObject() then
			BuildingObject(pTower):broadcastSpecificCellPermissions(cellID)
		end

		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act2/shared_rebel_missions:imperial_station_unlocked")
		return 1
	else
		CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act2/shared_rebel_missions:imperial_station_locked")
		return 0
	end
end

function Coa2Screenplay:completeMissionFive(pPlayer, faction)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return
	end

	local file = "@theme_park/alderaan/act2/shared_" .. faction .. "_missions"

	CreatureObject(pPlayer):sendSystemMessage(file .. ":mission_complete")
	PlayerObject(pGhost):increaseFactionStanding(faction, 500)

	if faction == "imperial" then
		PlayerObject(pGhost):awardBadge(EVENT_COA2_IMPERIAL)
	elseif faction == "rebel" then
		PlayerObject(pGhost):awardBadge(EVENT_COA2_REBEL)
	end

	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 13)

	SceneObject(pPlayer):cancelPendingTask("Coa2Screenplay", "timeoutMission")

	createEvent(600000, "Coa2Screenplay", "cleanupMission", pPlayer, "")
end

function Coa2Screenplay:timeoutMission(pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local faction

	if CreatureObject(pPlayer):isImperial() then
		faction = "imperial"
	elseif CreatureObject(pPlayer):isRebel() then
		faction = "rebel"
	end

	local state = tonumber(readScreenPlayData(pPlayer, faction .. "_coa2", "state"))

	if state ~= nil then
		local mission = 0

		if state == 2 then
			mission = 1
		elseif state == 6 then
			mission = 3
		elseif state == 12 then
			mission = 5
		end

		if mission > 0 then
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act2/shared_" .. faction .. "_missions:m" .. mission .. "_init_failure")
		end

	end

	self:cleanupMission(pPlayer)
end

function Coa2Screenplay:cleanupMission(pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	SceneObject(pPlayer):cancelPendingTask("Coa2Screenplay", "timeoutMission")

	self:removeWaypoint(pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()
	local targetID = readData(playerID .. ":coaTargetID")
	local pTarget = getSceneObject(targetID)

	if pTarget ~= nil then
		SceneObject(pTarget):destroyObjectFromWorld()
	end

	deleteData(targetID .. ":coaNpcOwnerID")
	deleteData(playerID .. ":coaTargetID")
	deleteData(playerID .. ":coaCoordinatorID")
	deleteData(playerID .. ":coaDrallKilled")
	deleteData(playerID .. ":coaHasPassKey")
	deleteData(playerID .. ":coaTowerCellID")

	local areaID = readData(playerID .. ":coaAreaID")
	local pArea = getSceneObject(areaID)

	if pArea ~= nil then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	deleteData(areaID .. ":coaTowerOwnerID")
	deleteData(playerID .. ":coaAreaID")

	for i = 1, 10 do
		npcID = readData(playerID .. ":coaSecondaryTargetID" .. i)
		pNpc = getSceneObject(npcID)

		if pNpc ~= nil then
			SceneObject(pNpc):destroyObjectFromWorld()
		end

		deleteData(playerID .. ":coaSecondaryTargetID" .. i)
		deleteData(npcID .. ":coaNpcOwnerID")
	end
end

CoaRelayStationTerminalMenuComponent = {  }

function CoaRelayStationTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)
	response:addRadialMenuItem(20, 3, "@theme_park/alderaan/act2/shared_rebel_missions:use_terminal")
end

function CoaRelayStationTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	if selectedID == 20 then
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if pInventory == nil then
			return 0
		end

		local pTerminalParent = SceneObject(pSceneObject):getParent()
		local pPlayerParent = SceneObject(pPlayer):getParent()
		local pInterfaceDevice = getContainerObjectByTemplate(pInventory, "object/tangible/theme_park/alderaan/act2/interface_override_device.iff", false)

		local state = tonumber(readScreenPlayData(pPlayer, "rebel_coa2", "state"))

		if pTerminalParent ~= nil and pTerminalParent == pPlayerParent and pInterfaceDevice ~= nil and state == 12 then
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act2/shared_rebel_missions:message_sent")
			Coa2Screenplay:completeMissionFive(pPlayer, "rebel")
			SceneObject(pInterfaceDevice):destroyObjectFromWorld()
			SceneObject(pInterfaceDevice):destroyObjectFromDatabase()
		else
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/alderaan/act2/shared_rebel_missions:terminal_locked")
		end
	end
	return 0
end

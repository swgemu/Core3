
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
13 - m5 return
14 - m5 complete
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
			spawnMobile(npc[2], npc[1], 0, npc[3], npc[4], npc[5], npc[6], 0)
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

function Coa2Screenplay:giveWaypoint(pPlayer, pNpc, name, desc, commander)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		return 0
	end

	local x = SceneObject(pNpc):getWorldPositionX()
	local y = SceneObject(pNpc):getWorldPositionY()
	local planet = SceneObject(pNpc):getZoneName()

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

function Coa2Screenplay:spawnNpc(pSource, template, minDist, maxDist)
	local sourceX = SceneObject(pSource):getWorldPositionX()
	local sourceY = SceneObject(pSource):getWorldPositionY()
	local planet = SceneObject(pSource):getZoneName()

	local spawnPoint = getSpawnPoint(pSource, sourceX, sourceY, minDist, maxDist)

	local pNpc = spawnMobile(planet, template, 0, spawnPoint[1], spawnPoint[2], spawnPoint[3], getRandomNumber(360) - 180, spawnPoint[4])

	return pNpc
end

function Coa2Screenplay:startMissionOne(pPlayer, conversingNPC, faction)
	if pPlayer == nil or conversingNPC == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	local file = "@theme_park/alderaan/act2/shared_" .. faction .. "_missions"
	local playerID = SceneObject(pPlayer):getObjectID()

	local pNpc

	if faction == "imperial" then
		pNpc = self:spawnNpc(pPlayer, "coa2_imperial_informant", 1000, 1500)
	elseif faction == "rebel" then
		pNpc = self:spawnNpc(pPlayer, "coa2_rebel_sympathizer", 1000, 1500)
	end

	if pNpc == nil then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":m1_init_failure")
		return
	end

	writeData(playerID .. ":coaNpcID", SceneObject(pNpc):getObjectID())

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
		pNpc = self:spawnNpc(pPlayer, "coa2_imperial_slicer", 1000, 1500)
	elseif faction == "rebel" then
		pNpc = self:spawnNpc(pPlayer, "coa2_lyda_skims", 1000, 1500)
	end

	if pNpc == nil then
		CreatureObject(pPlayer):sendSystemMessage(file .. ":m3_init_failure")
		return
	end

	writeData(playerID .. ":coaNpcID", SceneObject(pNpc):getObjectID())

	if faction == "imperial" then
		createObserver(OBJECTDESTRUCTION, "Coa2Screenplay", "notifyTargetDefeated", pNpc)
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
			pSecondaryNpc = self:spawnNpc(pNpc, "coa2_imperial_slicer_gang", 10, 15)
		elseif faction == "rebel" then
			pSecondaryNpc = self:spawnNpc(pNpc, "coa2_lyda_thug", 10, 15)
		end

		if pSecondaryNpc ~= nil then
			writeData(playerID .. ":coaSecondaryNpcID" .. i, SceneObject(pSecondaryNpc):getObjectID())
		end
	end

	writeData(playerID .. ":coaCoordinatorID", SceneObject(conversingNPC):getObjectID())
	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 6)
end

function Coa2Screenplay:notifyTargetDefeated(pNpc, pAttacker)
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
	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 9)
end

function Coa2Screenplay:finishMissionFour(pPlayer, faction)
	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 10)
end

function Coa2Screenplay:startMissionFive(pPlayer, conversingNPC, faction)
	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 12)
end

function Coa2Screenplay:finishMissionFive(pPlayer, faction)
	writeScreenPlayData(pPlayer, faction .. "_coa2", "state", 14)
end

function Coa2Screenplay:cleanupMission(pPlayer)
	if pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() then
		return
	end

	self:removeWaypoint(pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = readData(playerID .. ":coaNpcID")
	local pNpc = getSceneObject(npcID)

	if pNpc ~= nil then
		SceneObject(pNpc):destroyObjectFromWorld()
	end

	deleteData(playerID .. ":coaNpcID")
	deleteData(playerID .. ":coaCoordinatorID")

	for i = 1, 5 do
		npcID = readData(playerID .. ":coaSecondaryNpcID" .. i)
		pNpc = getSceneObject(npcID)

		if pNpc ~= nil then
			SceneObject(pNpc):destroyObjectFromWorld()
		end

		deleteData(playerID .. ":coaSecondaryNpcID" .. i)
	end
end

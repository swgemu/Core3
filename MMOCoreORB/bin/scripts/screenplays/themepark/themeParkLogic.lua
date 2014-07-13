require("screenplays.screenplay")
local ObjectManager = require("managers.object.object_manager")

WAYPOINT_COLOR_PURPLE = 5
SIT = 1
STAND = 0
FACTIONIMPERIAL = 0xDB4ACC54
FACTIONREBEL = 0x16148850

ThemeParkLogic = ScreenPlay:new {
	numberOfActs = 1,
	npcMap = {},
	waypointMap = {},
	permissionMap = {},
	sceneObjectMap = {},
	className = "ThemeParkLogic",
	screenPlayState = "theme_park_general",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = "",
	faction = 0
}

function ThemeParkLogic:start()
	self:spawnNpcs()
	self:spawnSceneObjects()
	self:permissionObservers()
end

function ThemeParkLogic:spawnNpcs()
	for i = 1, # self.npcMap do
		local npcSpawnData = self.npcMap[i].spawnData
		if isZoneEnabled(npcSpawnData.planetName) then
			local pNpc = spawnMobile(npcSpawnData.planetName, npcSpawnData.npcTemplate, 1, npcSpawnData.x, npcSpawnData.z, npcSpawnData.y, npcSpawnData.direction, npcSpawnData.cellID)
			if pNpc ~= nil and npcSpawnData.position == SIT then
				local npc = LuaCreatureObject(pNpc)
				npc:setState(STATESITTINGONCHAIR)
			end
		end
	end
end

function ThemeParkLogic:spawnSceneObjects()
	if self.sceneObjectMap ~= nil then
		for i = 1, # self.sceneObjectMap do
			local objectSpawnData = self.sceneObjectMap[i].spawnData
			if isZoneEnabled(objectSpawnData.planetName) then
				local pObject = spawnSceneObject(objectSpawnData.planetName, objectSpawnData.objectTemplate, objectSpawnData.x, objectSpawnData.z, objectSpawnData.y, objectSpawnData.cellID, objectSpawnData.dw, objectSpawnData.dx, objectSpawnData.dy, objectSpawnData.dz)
				ObjectManager.withSceneObject(pObject, function(luaObject)
					if self.sceneObjectMap[i].customObjectName ~= nil and self.sceneObjectMap[i].customObjectName ~= "" then
						luaObject:setCustomObjectName(self.sceneObjectMap[i].customObjectName)
					end
					if self.sceneObjectMap[i].objectIdLabel ~= nil and self.sceneObjectMap[i].objectIdLabel ~= "" then
						objectId = luaObject:getObjectID()
						writeData(self.sceneObjectMap[i].objectIdLabel, objectId)
					end
				end)
			end
		end
	end
end

function ThemeParkLogic:permissionObservers()
	for i = 1, # self.permissionMap, 1 do
		local permission = self.permissionMap[i]
		self:setupPermissionGroups(permission)
		local pRegion = getRegion(permission.planetName, permission.regionName)
		if pRegion ~= nil then
			createObserver(ENTEREDAREA, self.className, "cellPermissionsObserver", pRegion)
		end
	end
end

function ThemeParkLogic:setupPermissionGroups(permission)
	for i = 1, #permission.permissions, 1 do
		local thisPermission = permission.permissions[i]
		for j = 1, #thisPermission.cells, 1 do
			local pCell = getSceneObject(thisPermission.cells[j])
			if pCell ~= nil then
				local cell = LuaSceneObject(pCell)
				cell:setContainerInheritPermissionsFromParent(false)
				cell:clearContainerDefaultDenyPermission(WALKIN)
				cell:clearContainerDefaultAllowPermission(WALKIN)
				cell:setContainerAllowPermission(permission.regionName .. i, WALKIN)
				cell:setContainerDenyPermission(permission.regionName .. i, MOVEIN)
			end
		end
	end
end

function ThemeParkLogic:cellPermissionsObserver(pRegion, pCreature)
	if pRegion == nil or pCreature == nil then
		return 0
	end

	local creatureSceneObject = LuaSceneObject(pCreature)

	if creatureSceneObject:isCreatureObject() then
		local region = LuaSceneObject(pRegion)
		for i = 1, # self.permissionMap, 1 do
			if self.permissionMap[i].regionName == region:getObjectName() then
				self:setCellPermissions(self.permissionMap[i], pCreature)
			end
		end
	end

	return 0
end

function ThemeParkLogic:setCellPermissions(permissions, pCreature)
	if pCreature ~= nil then
		local creature = LuaCreatureObject(pCreature)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			for i = 1, # permissions.permissions, 1 do
				if self:hasPermission(permissions.permissions[i].conditions, pCreature) == true then
					ghost:addPermissionGroup(permissions.regionName .. i, true)
				else
					ghost:removePermissionGroup(permissions.regionName .. i, true)
				end
			end
		end
	end
end

function ThemeParkLogic:hasFullInventory(pPlayer)
	return ObjectManager.withSceneObject(pPlayer, function(player)
		local pInventory = player:getSlottedObject("inventory")
		return ObjectManager.withSceneObject(pInventory, function(inventory)
			return inventory:hasFullContainerObjects()
		end)
	end)
end

function ThemeParkLogic:hasPermission(conditions, pCreature)
	local hasPermission = true
	for i = 1, # conditions, 1 do
		if conditions[i].permissionType == "faction" then
			if conditions[i].faction ~= nil then
				if self:isInFaction(conditions[i].faction, pCreature) == false then
					hasPermission = false
				end
			else
				if self:isInFaction(self.faction, pCreature) == false then
					hasPermission = false
				end
			end
		elseif conditions[i].permissionType == "missionState" then
			if self:hasMissionState(conditions[i].mission, conditions[i].missionState, pCreature) == false then
				hasPermission = false
			end
		elseif conditions[i].permissionType == "npcState" then
			if self:hasNpcMissionState(conditions[i].npcState, conditions[i].state, pCreature) == false then
				hasPermission = false
			end
		end
	end
	return hasPermission
end

function ThemeParkLogic:isInFaction(faction, pCreature)
	if pCreature == nil then
		return false
	end

	local creature = LuaCreatureObject(pCreature)

	if creature:getFaction() == faction then
		return true
	else
		return false
	end
end

function ThemeParkLogic:isOnLeave(pPlayer)
	return ObjectManager.withCreaturePlayerObject(pPlayer, function(player)
		return player:isOnLeave()
	end)
end

function ThemeParkLogic:isValidConvoString(stfFile, stringid)
	if (getStringId(stfFile .. stringid) ~= "") then
		return true
	else
		return false
	end
end

function ThemeParkLogic:getGlobalFaction()
	if self.faction == nil then
		return 0
	end

	return self.faction
end

function ThemeParkLogic:getMissionFaction(npcNumber, missionNumber)
	local mission = self:getMission(npcNumber, missionNumber)

	if mission.faction == nil then
		return 0
	end

	return mission.faction
end

function ThemeParkLogic:hasMissionState(mission, missionState, pCreature)
	if pCreature == nil then
		return false
	end

	local npcNumber = self:getActiveNpcNumber(pCreature)

	if npcNumber > missionState then
		return true
	else
		return false
	end
end

function ThemeParkLogic:hasNpcMissionState(npcState, state, pCreature)
	return ObjectManager.withCreatureObject(pCreature, function(creature)
		if creature:hasScreenPlayState(state, npcState) == 1 then
			return true
		else
			return false
		end
	end)
end

function ThemeParkLogic:getNpcNumber(pNpc)
	if pNpc == nil then
		return 0
	end
	local npc = LuaCreatureObject(pNpc)

	local x = npc:getPositionX()
	local y = npc:getPositionY()
	local z = npc:getPositionZ()

	for i = 1, # self.npcMap do
		local npcData = self.npcMap[i].spawnData
		if (math.abs(x - npcData.x) < 0.1) and (math.abs(z - npcData.z) < 0.1) and (math.abs(y - npcData.y) < 0.1) then
			return self.npcMap[i].npcNumber
		end
	end

	return 1
end

function ThemeParkLogic:getNpcData(npcNumber)
	for i = 1, # self.npcMap do
		if npcNumber == self.npcMap[i].npcNumber then
			return self.npcMap[i]
		end
	end

	return nil
end

function ThemeParkLogic:getActiveNpcNumber(pConversingPlayer)
	if pConversingPlayer == nil then
		return -1
	end

	local creature = LuaCreatureObject(pConversingPlayer)

	local npcNumber = 1
	local activeNpcNumber = 1
	for i = 1, 10, 1 do
		if creature:hasScreenPlayState(npcNumber, self.screenPlayState) == 1 then
			activeNpcNumber = npcNumber * 2
		end
		npcNumber = npcNumber * 2
	end

	return activeNpcNumber
end

function ThemeParkLogic:activeNpc(pConversingPlayer, pConversingNpc)
	if pConversingPlayer == nil then
		return -1
	end

	local npcNumber = self:getNpcNumber(pConversingNpc)
	local activeNpcNumber = self:getActiveNpcNumber(pConversingPlayer)
	return npcNumber - activeNpcNumber
end

function ThemeParkLogic:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	if pConversingPlayer == nil then
		return 0
	end
	local creature = LuaCreatureObject(pConversingPlayer)

	local npcData = self:getNpcData(npcNumber)
	if npcData ~= nil then
		local npcName = npcData.spawnData.npcTemplate
		local numberOfMissionsTotal = table.getn(npcData.missions)

		local missionsCompleted = 0
		local stateToCheck = 1
		for i = 1, numberOfMissionsTotal, 1 do
			if creature:hasScreenPlayState(stateToCheck, self.screenPlayState .. "_mission_" .. npcName) == 1 then
				stateToCheck = stateToCheck * 2
				missionsCompleted = missionsCompleted + 1
			end
		end

		return missionsCompleted + 1
	else
		return 0
	end
end

function ThemeParkLogic:missionStatus(pConversingPlayer)
	if pConversingPlayer == nil then
		return 0
	end
	local creature = LuaCreatureObject(pConversingPlayer)

	return readData(creature:getObjectID() .. ":activeMission")
end

function ThemeParkLogic:getStfFile(npcNumber)
	local npcData = self:getNpcData(npcNumber)

	return npcData.stfFile
end

function ThemeParkLogic:handleMissionAccept(npcNumber, missionNumber, pConversingPlayer)
	local mission = self:getMission(npcNumber, missionNumber)
	local creature = LuaCreatureObject(pConversingPlayer)

	writeStringData(creature:getObjectID() .. ":activeScreenPlay", self.className)

	if mission.missionType == "deliver" then
		return self:handleDeliverMissionAccept(mission, pConversingPlayer, missionNumber)
	elseif mission.missionType == "escort" then
		return self:handleEscortMissionAccept(mission, pConversingPlayer, missionNumber)
	elseif mission.missionType == "retrieve" then
		return self:handleRetrieveMissionAccept(mission, pConversingPlayer, missionNumber)
	elseif mission.missionType == "assassinate" then
		return self:handleAssassinateMissionAccept(mission, pConversingPlayer, missionNumber)
	elseif mission.missionType == "confiscate" then
		return self:handleConfiscateMissionAccept(mission, pConversingPlayer, missionNumber)
	elseif mission.missionType == "destroy" then
		return self:handleDestroyMissionAccept(mission, pConversingPlayer, missionNumber)
	end
end

function ThemeParkLogic:writeData(pConversingPlayer, dataName, value)
	if pConversingPlayer == nil then
		return
	end

	local creature = LuaCreatureObject(pConversingPlayer)
	writeData(creature:getObjectID() .. dataName, value)
end

function ThemeParkLogic:getMission(npcNumber, missionNumber)
	local npcData = self:getNpcData(npcNumber)

	if (npcData == nil) then
		printf("null npcData in ThemeParkLogic:getMission for %s", self.className);
	end

	local missions = npcData.missions

	return missions[missionNumber]
end

function ThemeParkLogic:handleDeliverMissionAccept(mission, pConversingPlayer, missionNumber)
	if self:spawnMissionNpcs(mission, pConversingPlayer) == true then
		self:giveMissionItems(mission, pConversingPlayer)
		return true
	else
		return false
	end
end

function ThemeParkLogic:handleRetrieveMissionAccept(mission, pConversingPlayer, missionNumber)
	if self:spawnMissionNpcs(mission, pConversingPlayer) == true then
		self:writeData(pConversingPlayer, ":activeMission", 1)
		return true
	else
		return false
	end
end

function ThemeParkLogic:handleEscortMissionAccept(mission, pConversingPlayer, missionNumber)
	if self:spawnMissionNpcs(mission, pConversingPlayer) == true then
		self:writeData(pConversingPlayer, ":activeMission", 1)
		return true
	else
		return false
	end
end

function ThemeParkLogic:handleDestroyMissionAccept(mission, pConversingPlayer, missionNumber)
	if self:spawnDestroyBuilding(mission, pConversingPlayer) == true then
		self:spawnMissionNpcs(mission, pConversingPlayer)
		self:writeData(pConversingPlayer, ":activeMission", 1)
		return true
	else
		return false
	end
end

function ThemeParkLogic:handleAssassinateMissionAccept(mission, pConversingPlayer, missionNumber)
	if self:spawnMissionNpcs(mission, pConversingPlayer) == true then
		self:writeData(pConversingPlayer, ":activeMission", 1)
		self:writeData(pConversingPlayer, ":killedMissionNpcs", 0)
		return true
	else
		return false
	end
end

function ThemeParkLogic:handleConfiscateMissionAccept(mission, pConversingPlayer, missionNumber)
	if self:spawnMissionNpcs(mission, pConversingPlayer) == true then
		self:writeData(pConversingPlayer, ":activeMission", 1)
		self:writeData(pConversingPlayer, ":requiredItemsLooted", 0)
		return true
	else
		return false
	end
end

function ThemeParkLogic:spawnDestroyBuilding(mission, pConversingPlayer)
	if pConversingPlayer == nil then
		return false
	end

	local npcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self:getStfFile(npcNumber)

	local buildingData = mission.buildingSpawn

	if buildingData == nil then
		printf("null building data in ThemeParkLogic:spawnDestroyBuilding for %s", self.className);
		return false
	end

	local spawnDistance = self.distance
	return ObjectManager.withCreatureObject(pConversingPlayer, function(creature)
		local spawnPoint = getSpawnArea(pConversingPlayer, creature:getWorldPositionX(), creature:getWorldPositionY(), spawnDistance, (spawnDistance/2)*3, 20, 5)
		local pBuilding = spawnBuilding(pConversingPlayer, buildingData.building.template, spawnPoint[1], spawnPoint[3], 0)

		if (pBuilding == nil) then
			return false
		end

		createObserver(OBJECTDESTRUCTION, self.className, "notifyDestroyedBuilding", pBuilding)

		return ObjectManager.withBuildingObject(pBuilding, function(buildingObject)
			return ObjectManager.withSceneObject(pBuilding, function(buildingSceo)
				return ObjectManager.withSceneObject(buildingObject:getCell(buildingData.terminal.vectorCellID), function(targetCellObject)
					local pTerminal = spawnSceneObject(buildingData.building.planet, buildingData.terminal.template, buildingData.terminal.x, buildingData.terminal.z, buildingData.terminal.y, targetCellObject:getObjectID(), 1, 0, 0, 0)
					writeData(creature:getObjectID() .. ":destroyableBuildingID", buildingSceo:getObjectID())
					self:updateWaypoint(pConversingPlayer, buildingData.building.planet, spawnPoint[1], spawnPoint[3], "target")
					self:spawnDestroyMissionNpcs(mission, pConversingPlayer)
					return true
				end)
			end)
		end)
	end)
end

function ThemeParkLogic:spawnMissionStaticObjects(mission, pConversingPlayer, x, y)
	if pConversingPlayer == nil then
		return false
	end

	local player = LuaCreatureObject(pConversingPlayer)
	local playerID = player:getObjectID()
	local npcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pConversingPlayer)

	local numberOfSpawns = table.getn(mission.staticObjects)

	ObjectManager.withCreatureObject(pConversingPlayer, function(creature)
		writeData(creature:getObjectID() .. ":missionStaticObjects", numberOfSpawns)
		for i = 1, numberOfSpawns, 1 do
			local spawnPoint = getSpawnPoint(pConversingPlayer, x, y, 5, 10)
			if spawnPoint ~= nil then
				local pObject = spawnSceneObject(mission.staticObjects[i].planetName, mission.staticObjects[i].objectTemplate, spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0, 0, 0, 0)
				ObjectManager.withSceneObject(pObject, function(object)
					writeData(creature:getObjectID() .. ":missionStaticObject:no" .. i, object:getObjectID())
				end)
			end
		end
	end)
end

function ThemeParkLogic:spawnMissionNpcs(mission, pConversingPlayer)
	if pConversingPlayer == nil then
		return false
	end

	local player = LuaCreatureObject(pConversingPlayer)
	local playerID = player:getObjectID()

	local npcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self:getStfFile(npcNumber)
	local currentMissionType = self:getMissionType(npcNumber, pConversingPlayer)
	local spawnPoints

	local numberOfSpawns = table.getn(mission.primarySpawns) + table.getn(mission.secondarySpawns)

	if (currentMissionType == "destroy") then
		local buildingID = readData(playerID .. ":destroyableBuildingID")
		local pBuilding = getSceneObject(buildingID)
		ObjectManager.withSceneObject(pBuilding, function(buildingSceo)
			spawnPoints = self:getSpawnPoints(numberOfSpawns, buildingSceo:getWorldPositionX(), buildingSceo:getWorldPositionY(), pConversingPlayer)
		end)
	else
		ObjectManager.withCreatureObject(pConversingPlayer, function(creature)
			spawnPoints = self:getSpawnPoints(numberOfSpawns, creature:getWorldPositionX(), creature:getWorldPositionY(), pConversingPlayer)
		end)
	end

	if table.getn(spawnPoints) ~= numberOfSpawns then
		return false
	end

	local creature = LuaCreatureObject(pConversingPlayer)
	writeData(creature:getObjectID() .. ":missionSpawns", numberOfSpawns)

	local mainNpcs = mission.primarySpawns
	for i = 1, table.getn(mission.primarySpawns), 1 do
		local pNpc = self:spawnNpc(mainNpcs[i], spawnPoints[i], pConversingPlayer, i)
		if pNpc ~= nil then
			if i == 1 then
				if (self:isValidConvoString(stfFile, ":npc_breech_" .. missionNumber)) then
					local pBreechArea = spawnSceneObject(mainNpcs[i].planetName, "object/active_area.iff", spawnPoints[i][1], spawnPoints[i][2], spawnPoints[i][3], 0, 0, 0, 0, 0)
					ObjectManager.withActiveArea(pBreechArea, function(activeArea)
						activeArea:setRadius(65)
						createObserver(ENTEREDAREA, self.className, "notifyEnteredBreechArea", pBreechArea)
						ObjectManager.withCreatureObject(pNpc, function(breechNpc)
							writeData(creature:getObjectID() .. ":breechNpcID", breechNpc:getObjectID())
							writeData(creature:getObjectID() .. ":breechAreaID", activeArea:getObjectID())
						end)
					end)
				end
				self:updateWaypoint(pConversingPlayer, mainNpcs[i].planetName, spawnPoints[i][1], spawnPoints[i][3], "target")
				if (mission.staticObjects ~= nil and table.getn(mission.staticObjects) > 0) then
					self:spawnMissionStaticObjects(mission, pConversingPlayer, spawnPoints[i][1], spawnPoints[i][3])
				end
			end
			if mission.missionType == "assassinate" then
				createObserver(OBJECTDESTRUCTION, self.className, "notifyDefeatedTarget", pNpc)
				ObjectManager.withCreatureObject(pNpc, function(npc)
					ObjectManager.withCreatureObject(pConversingPlayer, function(creature)
						writeData(npc:getObjectID() .. ":missionOwnerID", creature:getObjectID())
					end)
				end)
			elseif mission.missionType == "confiscate" then
				createObserver(OBJECTDESTRUCTION, self.className, "notifyDefeatedTargetWithLoot", pNpc)
				ObjectManager.withCreatureObject(pNpc, function(npc)
					ObjectManager.withCreatureObject(pConversingPlayer, function(creature)
						writeData(npc:getObjectID() .. ":missionOwnerID", creature:getObjectID())
					end)
				end)
			elseif mission.missionType == "escort" then
				ObjectManager.withCreatureObject(pNpc, function(npc)
					ObjectManager.withCreatureObject(pConversingPlayer, function(creature)
						writeData(npc:getObjectID() .. ":missionOwnerID", creature:getObjectID())
					end)
				end)
			end
		end
	end

	local secondaryNpcs = mission.secondarySpawns
	for i = 1 + table.getn(mission.primarySpawns), numberOfSpawns, 1 do
		local secondaryNpc = secondaryNpcs[i - table.getn(mission.primarySpawns)]
		local pNpc = self:spawnNpc(secondaryNpc, spawnPoints[i], pConversingPlayer, i)
		ObjectManager.withCreatureObject(pNpc, function(npc)
			ObjectManager.withCreatureObject(pConversingPlayer, function(creature)
				writeData(npc:getObjectID() .. ":missionOwnerID", creature:getObjectID())
				if (secondaryNpc.dead ~= nil and secondaryNpc.dead == "true") then
					npc:setPosture(14)
				end
			end)
		end)
	end

	return true
end

function ThemeParkLogic:spawnDestroyMissionNpcs(mission, pConversingPlayer)
	if pConversingPlayer == nil then
		return false
	end
	ObjectManager.withCreatureObject(pConversingPlayer, function(player)
		local playerID = player:getObjectID()

		local npcNumber = self:getActiveNpcNumber(pConversingPlayer)
		local missionNumber = self:getCurrentMissionNumber(npcNumber, pConversingPlayer)
		local stfFile = self:getStfFile(npcNumber)
		local currentMissionType = self:getMissionType(npcNumber, pConversingPlayer)

		local buildingData = mission.buildingSpawn
		local childNpcs = buildingData.childNpcs
		local numberOfChildNpcs = table.getn(childNpcs)

		local buildingID = readData(playerID .. ":destroyableBuildingID")
		local pBuilding = getSceneObject(buildingID)

		ObjectManager.withBuildingObject(pBuilding, function(buildingObject)
			for i = 1, numberOfChildNpcs, 1 do
				local targetCellObject = LuaSceneObject(buildingObject:getCell(childNpcs[i].vectorCellID))
				local pNpc = spawnMobile(buildingData.building.planet, childNpcs[i].npcTemplate, 0, childNpcs[i].x, childNpcs[i].z, childNpcs[i].y, math.random(-180, 180), targetCellObject:getObjectID())

				ObjectManager.withCreatureObject(pNpc, function(npc)
					local npcName = self:getNpcName(childNpcs[i].npcName)
					npc:setCustomObjectName(npcName)
					if i == 1 then
						if (self:isValidConvoString(stfFile, ":npc_breech_" .. missionNumber)) then
							local pBreechArea = spawnSceneObject(buildingData.building.planet, "object/active_area.iff", childNpcs[i].x, childNpcs[i].z, childNpcs[i].y, childNpcs[i].vectorCellID, 0, 0, 0, 0)
							ObjectManager.withActiveArea(pBreechArea, function(activeArea)
								activeArea:setRadius(20)
								createObserver(ENTEREDAREA, self.className, "notifyEnteredBreechArea", pBreechArea)
								ObjectManager.withCreatureObject(pNpc, function(breechNpc)
									writeData(player:getObjectID() .. ":breechNpcID", breechNpc:getObjectID())
									writeData(player:getObjectID() .. ":breechAreaID", activeArea:getObjectID())
								end)
							end)
						end
					end
				end)
			end
		end)
	end)
end

function ThemeParkLogic:notifyDefeatedTargetWithLoot(pVictim, pAttacker)
	if pVictim == nil or pAttacker == nil then
		return 0
	end

	local victim = LuaCreatureObject(pVictim)
	local attacker = LuaCreatureObject(pAttacker)

	local victimID = victim:getObjectID()
	local attackerID = attacker:getObjectID()

	if self:killedByCorrectPlayer(victimID, attackerID) == false then
		return 0
	end

	local pInventory = victim:getSlottedObject("inventory")
	if pInventory == nil then
		return 0
	end

	local inventory = LuaSceneObject(pInventory)

	local numberOfItems = inventory:getContainerObjectsSize()
	local activeNpcNumber = self:getActiveNpcNumber(pAttacker)
	local requiredItems = self:getRequiredItem(activeNpcNumber, pAttacker)

	for j = 1, # requiredItems, 1 do
		for i = 0, numberOfItems - 1, 1 do
			local pItem = inventory:getContainerObject(i)

			if pItem ~= nil then
				local item = LuaSceneObject(pItem)
				if requiredItems[j].itemTemplate == item:getTemplateObjectPath() and (requiredItems[j].itemName == item:getCustomObjectName() or requiredItems[j].itemName == item:getDisplayedName()) then
					createObserver(ITEMLOOTED, self.className, "notifyItemLooted", pItem)
					writeData(item:getObjectID() .. ":missionOwnerID", attacker:getObjectID())
					break
				end
			end
		end
	end

	return 1
end

function ThemeParkLogic:notifyItemLooted(pItem, pLooter)
	if pItem == nil or pLooter == nil then
		return 0
	end

	local item = LuaCreatureObject(pItem)
	local looter = LuaCreatureObject(pLooter)

	local itemID = item:getObjectID()
	local looterID = looter:getObjectID()

	if self:lootedByCorrectPlayer(itemID, looterID) == true then
		local currentLootCount = readData(looterID .. ":requiredItemsLooted") + 1
		writeData(looterID, ":requiredItemsLooted", currentLootCount)

		if currentLootCount == self:getMissionLootCount(pLooter) then
			self:completeMission(pLooter)
			return 1
		end
	end

	return 0
end

function ThemeParkLogic:lootedByCorrectPlayer(itemID, looterID)
	if readData(itemID .. ":missionOwnerID") == looterID then
		return true
	else
		return false
	end
end

function ThemeParkLogic:getMissionLootCount(pLooter)
	local npcNumber = self:getActiveNpcNumber(pLooter)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pLooter)
	local mission = self:getMission(npcNumber, missionNumber)

	if mission.missionType == "confiscate" then
		return table.getn(mission.itemSpawns)
	else
		return 0
	end
end

function ThemeParkLogic:getMissionPreReq(pPlayer)
	local npcNumber = self:getActiveNpcNumber(pPlayer)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pPlayer)
	local mission = self:getMission(npcNumber, missionNumber)
	local preReq = mission.preReq

	if preReq == nil or preReq == "" then
		return 0
	else
		return preReq
	end
end

function ThemeParkLogic:notifyEnteredBreechArea(pActiveArea, pPlayer)
	ObjectManager.withActiveArea(pActiveArea, function(activeArea)
		ObjectManager.withCreatureObject(pPlayer, function(player)
			local playerID = player:getObjectID()
			local breechNpcID = readData(playerID .. ":breechNpcID")
			local breechAreaID = readData(playerID .. ":breechAreaID")
			if (activeArea:getObjectID() == breechAreaID) then
				self:setNpcDefender(pPlayer)
				if (breechNpcID ~= nil and breechNpcID ~= 0) then
					local pNpc = getSceneObject(breechNpcID)
					local npcNumber = self:getActiveNpcNumber(pPlayer)
					local missionNumber = self:getCurrentMissionNumber(npcNumber, pPlayer)
					local stfFile = self:getStfFile(npcNumber)
					spatialChat(pNpc, stfFile .. ":npc_breech_" .. missionNumber)
					writeData(playerID .. ":breechNpcID", 0)
					ObjectManager.withSceneObject(pActiveArea, function(activeArea)
						activeArea:destroyObjectFromWorld()
					end)
				end
			end
		end)
	end)
	return 0
end

function ThemeParkLogic:setNpcDefender(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local playerID = player:getObjectID()
		local npcNumber = self:getActiveNpcNumber(pPlayer)
		local missionNumber = self:getCurrentMissionNumber(npcNumber, pPlayer)
		local mission = self:getMission(npcNumber, missionNumber)
		local currentMissionType = self:getMissionType(npcNumber, pPlayer)

		local numberOfSpawns = readData(player:getObjectID() .. ":missionSpawns")
		for i = 1, numberOfSpawns, 1 do
			local objectID = readData(playerID .. ":missionSpawn:no" .. i)
			if readData(objectID .. ":missionOwnerID") == playerID then
				local pNpc = getSceneObject(objectID)
				if (i <= table.getn(mission.primarySpawns)) then
					if currentMissionType == "assassinate" or currentMissionType == "confiscate" or currentMissionType == "destroy" then
						ObjectManager.withCreatureAiAgent(pNpc, function(mobile)
							mobile:setDefender(pPlayer)
						end)
					end
				elseif i > table.getn(mission.primarySpawns) then
					ObjectManager.withCreatureAiAgent(pNpc, function(mobile)
						if (mission.secondarySpawns[i - table.getn(mission.primarySpawns)].dead == nil or mission.secondarySpawns[i - table.getn(mission.primarySpawns)].dead ~= "true") then
							mobile:setDefender(pPlayer)
						end
					end)
				end
			end
		end
	end)
end

function ThemeParkLogic:notifyDefeatedTarget(pVictim, pAttacker)
	if pVictim == nil or pAttacker == nil then
		return 0
	end

	local victim = LuaCreatureObject(pVictim)
	local attacker = LuaCreatureObject(pAttacker)

	local victimID = victim:getObjectID()
	local attackerID = attacker:getObjectID()

	if self:killedByCorrectPlayer(victimID, attackerID) == true then
		local currentKillCount = readData(attackerID .. ":killedMissionNpcs") + 1
		writeData(attackerID .. ":killedMissionNpcs", currentKillCount)

		if currentKillCount == self:getMissionKillCount(pAttacker) then
			self:completeMission(pAttacker)
		end
	end

	return 1
end

function ThemeParkLogic:notifyDestroyedBuilding(pBuilding, pBuilding2)
	if pBuilding == nil then
		return 0
	end

	return ObjectManager.withBuildingObject(pBuilding, function(buildingObject)
		local ownerID = buildingObject:getOwnerID()
		local pPlayer = getCreatureObject(ownerID)
		self:completeMission(pPlayer)
		return 1
	end)
end

function ThemeParkLogic:getMissionKillCount(pAttacker)
	local npcNumber = self:getActiveNpcNumber(pAttacker)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pAttacker)
	local mission = self:getMission(npcNumber, missionNumber)

	if mission.missionType == "assassinate" then
		return table.getn(mission.primarySpawns)
	else
		return 0
	end
end

function ThemeParkLogic:killedByCorrectPlayer(victimID, attackerID)
	if readData(victimID .. ":missionOwnerID") == attackerID then
		return true
	else
		return false
	end
end

function ThemeParkLogic:spawnNpc(npcTemplate, position, pConversingPlayer, spawnNumber)
	if pConversingPlayer == nil then
		return nil
	end

	local pNpc = spawnMobile(npcTemplate.planetName, npcTemplate.npcTemplate, 0, position[1], position[2], position[3], math.random(-180, 180), position[4])

	if pNpc ~= nil then
		local npc = LuaCreatureObject(pNpc)
		local npcName = self:getNpcName(npcTemplate.npcName)
		npc:setCustomObjectName(npcName)

		local creature = LuaCreatureObject(pConversingPlayer)

		writeData(creature:getObjectID() .. ":missionSpawn:no" .. spawnNumber, npc:getObjectID())
	end
	return pNpc
end

function ThemeParkLogic:getNpcName(name)
	if name ~= "random" then
		return name
	end
	return makeCreatureName(true)
end

function ThemeParkLogic:giveMissionItems(mission, pConversingPlayer)
	if pConversingPlayer == nil then
		return
	end

	local creature = LuaCreatureObject(pConversingPlayer)

	local activeNpcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local currentMissionType = self:getMissionType(activeNpcNumber, pConversingPlayer)

	if (currentMissionType == "retrieve") then
		writeData(creature:getObjectID() .. ":activeMission", 2)
	else
		writeData(creature:getObjectID() .. ":activeMission", 1)
	end

	local itemsToGive = mission.itemSpawns

	local pInventory = creature:getSlottedObject("inventory")
	if pInventory == nil then
		return
	end

	writeData(creature:getObjectID() .. ":missionItems", table.getn(itemsToGive))

	for i = 1, table.getn(itemsToGive), 1 do
		local pInvItem = getContainerObjectByTemplate(pInventory, itemsToGive[i].itemTemplate, true)
		if (pInvItem == nil) then
			local pItem = giveItem(pInventory, itemsToGive[i].itemTemplate, -1)
			ObjectManager.withSceneObject(pItem, function(item)
				item:setCustomObjectName(itemsToGive[i].itemName)
				writeData(creature:getObjectID() .. ":missionItem:no" .. i, item:getObjectID())
			end)
		else
			ObjectManager.withSceneObject(pInvItem, function(item)
				writeData(creature:getObjectID() .. ":missionItem:no" .. i, item:getObjectID())
			end)
		end
	end
end

function ThemeParkLogic:getMissionDescription(pConversingPlayer, direction)
	local activeNpcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self:getCurrentMissionNumber(activeNpcNumber, pConversingPlayer)
	local creature = LuaCreatureObject(pConversingPlayer)

	local npcNumber = 1
	while (npcNumber < activeNpcNumber) do
		missionNumber = missionNumber + table.getn(self:getNpcData(npcNumber).missions)
		npcNumber = npcNumber * 2
	end

	if self.missionDescriptionStf == "" then
		local currentMissionNumber = self:getCurrentMissionNumber(activeNpcNumber, pConversingPlayer)
		local curMission = self:getMission(activeNpcNumber, currentMissionNumber)
		local stfFile = self:getStfFile(activeNpcNumber)
		if not self:isValidConvoString(stfFile, ":waypoint_description_" .. missionNumber) or not self:isValidConvoString(stfFile, ":waypoint_name_" .. missionNumber) or not self:isValidConvoString(stfFile, ":return_waypoint_name_" .. missionNumber) then
			return self:getDefaultWaypointName(pConversingPlayer, direction)
		else
			if direction == "target" then
				creature:sendSystemMessage(stfFile .. ":waypoint_description_" .. currentMissionNumber)
				return stfFile .. ":waypoint_name_" .. currentMissionNumber
			else
				return stfFile .. ":return_waypoint_name_" .. currentMissionNumber
			end
		end
	else
		if direction == "target" then
			local message = self.missionDescriptionStf .. missionNumber
			creature:sendSystemMessage(message)
			return message
		else
			return self.missionDescriptionStf .. "return"
		end
	end
end

function ThemeParkLogic:getDefaultWaypointName(pConversingPlayer, direction)
	if direction == "target" then
		local activeNpcNumber = self:getActiveNpcNumber(pConversingPlayer)
		local currentMissionType = self:getMissionType(activeNpcNumber, pConversingPlayer)
		local currentMissionNumber = self:getCurrentMissionNumber(activeNpcNumber, pConversingPlayer)
		local mission = self:getMission(activeNpcNumber, currentMissionNumber)
		local mainNpc = mission.primarySpawns
		local mainNpcName = self:getNpcName(mainNpc[1].npcName)
		local missionItem = mission.itemSpawns

		if currentMissionType == "deliver" then
			local missionItemName = missionItem[1].itemName
			return "Deliver " .. missionItemName
		elseif currentMissionType == "escort" then
			return "Escort " .. mainNpcName
		elseif currentMissionType == "retrieve" then
			local missionItemName = missionItem[1].itemName
			return "Retrieve " .. missionItemName
		elseif currentMissionType == "assassinate" then
			return "Kill " .. mainNpcName
		elseif currentMissionType == "confiscate" then
			local missionItemName = missionItem[1].itemName
			return "Confiscate " .. missionItemName
		end
	else
		return "Return to the mission giver."
	end
end

function ThemeParkLogic:createEscortReturnArea(pNpc, pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local playerID = player:getObjectID()
		local npcNumber = self:getActiveNpcNumber(pPlayer)
		local missionNumber = self:getCurrentMissionNumber(npcNumber, pPlayer)
		local stfFile = self:getStfFile(npcNumber)

		local npcData = self.npcMap[npcNumber]
		if (self:isValidConvoString(stfFile, ":npc_dropoff_" .. missionNumber)) then
			local pEscortArea = spawnSceneObject(npcData.spawnData.planetName, "object/active_area.iff", npcData.spawnData.x, npcData.spawnData.z, npcData.spawnData.y, 0, 0, 0, 0, 0)
			ObjectManager.withActiveArea(pEscortArea, function(activeArea)
				activeArea:setRadius(10)
				createObserver(ENTEREDAREA, self.className, "notifyEnteredEscortArea", pEscortArea)
				ObjectManager.withCreatureObject(pNpc, function(escortNpc)
					writeData(activeArea:getObjectID() .. ":escortNpcID", escortNpc:getObjectID())
				end)
			end)
		end
	end)
end

function ThemeParkLogic:notifyEnteredEscortArea(pActiveArea, pCreature)
	ObjectManager.withActiveArea(pActiveArea, function(activeArea)
		ObjectManager.withCreatureObject(pCreature, function(creature)
			local objectID = creature:getObjectID()
			local escortNpcID = readData(activeArea:getObjectID() .. ":escortNpcID")
			if (objectID == escortNpcID) then
				local ownerID = readData(escortNpcID .. ":missionOwnerID")
				local pPlayer = getCreatureObject(ownerID)
				
				if (pPlayer == nil) then
					return 0
				end
				
				local npcNumber = self:getActiveNpcNumber(pPlayer)
				local missionNumber = self:getCurrentMissionNumber(npcNumber, pPlayer)
				local stfFile = self:getStfFile(npcNumber)
				spatialChat(pCreature, stfFile .. ":npc_dropoff_" .. missionNumber)
				deleteData(activeArea:getObjectID() .. ":escortNpcID")
				ObjectManager.withSceneObject(pActiveArea, function(activeArea)
					activeArea:destroyObjectFromWorld()
				end)
			end
		end)
	end)
	return 0
end

function ThemeParkLogic:updateWaypoint(pConversingPlayer, planetName, x, y, direction)
	if pConversingPlayer ~= nil then
		local creature = LuaCreatureObject(pConversingPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)

			waypointID = ghost:addWaypoint(planetName, self:getMissionDescription(pConversingPlayer, direction), "", x, y, WAYPOINT_COLOR_PURPLE, true, true, WAYPOINTTHEMEPARK)
		end
	end
end

function ThemeParkLogic:getSpawnPoints(numberOfSpawns, x, y, pConversingPlayer)
	local spawnPoints = {}

	if (numberOfSpawns == 0) then
		return spawnPoints
	end

	local firstSpawnPoint

	local activeNpcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local currentMissionType = self:getMissionType(activeNpcNumber, pConversingPlayer)
	local currentMissionNumber = self:getCurrentMissionNumber(activeNpcNumber, pConversingPlayer)
	local mission = self:getMission(activeNpcNumber, currentMissionNumber)

	local spawnDistance = self.distance

	if currentMissionType == "destroy" then
		firstSpawnPoint = getSpawnPoint(pConversingPlayer, x, y, 10, 20)
	else
		firstSpawnPoint = getSpawnPoint(pConversingPlayer, x, y, spawnDistance, (spawnDistance/2)*3)
	end

	if firstSpawnPoint ~= nil then
		table.insert(spawnPoints, firstSpawnPoint)
		for i = 2, numberOfSpawns, 1 do
			local nextSpawnPoint
			if currentMissionType == "destroy" then
				nextSpawnPoint = getSpawnPoint(pConversingPlayer, firstSpawnPoint[1], firstSpawnPoint[3], 10, 20)
			else
				nextSpawnPoint = getSpawnPoint(pConversingPlayer, firstSpawnPoint[1], firstSpawnPoint[3], 5, 15)
			end
			if nextSpawnPoint ~= nil then
				table.insert(spawnPoints, nextSpawnPoint)
			end
		end
	end

	return spawnPoints
end

function ThemeParkLogic:hasEliteCombatProfession(pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		if player:hasSkill("combat_1hsword_novice") or player:hasSkill("combat_2hsword_novice") or player:hasSkill("combat_bountyhunter_novice") or player:hasSkill("combat_carbine_novice")
			or player:hasSkill("combat_commando_novice") or player:hasSkill("combat_pistol_novice") or player:hasSkill("combat_polearm_novice") or player:hasSkill("combat_rifleman_novice")
			or player:hasSkill("combat_smuggler_novice") or player:hasSkill("combat_unarmed_novice") or player:hasSkill("science_combatmedic_novice") then
			return true
		else
			return false
		end
	end)
end

function ThemeParkLogic:requiresEliteCombatProfession()
	if self.requiresEliteCombat ~= nil and self.requiresEliteCombat == true then
		return true
	else
		return false
	end
end

function ThemeParkLogic:hasRequiredItem(pConversingPlayer)
	if pConversingPlayer == nil then
		return false
	end

	local creature = LuaCreatureObject(pConversingPlayer)

	local pInventory = creature:getSlottedObject("inventory")
	if pInventory == nil then
		return false
	end

	local inventory = LuaSceneObject(pInventory)

	local itemID = readData(creature:getObjectID() .. ":missionItem:no1")

	local pItem = inventory:getContainerObjectById(itemID)

	if pItem == nil then
		return false
	end

	return true
end

function ThemeParkLogic:doPreReqItemCheck(pPlayer, preReq)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local itemIff = preReq.itemTemplate
		local pInventory = player:getSlottedObject("inventory")
		if pInventory == nil then
			return false
		end
		local pItem = getContainerObjectByTemplate(pInventory, itemIff, true)
		if pItem ~= nil then
			return ObjectManager.withSceneObject(pItem, function(item)
				if preReq.destroy ~= nil and preReq.destroy == true then
					item:destroyObjectFromWorld()
					item:destroyObjectFromDatabase()
				end
				writeData(player:getObjectID() .. ":hasPreReqItem", 1)
				return true
			end)
		else
			return false
		end
	end)
end

function ThemeParkLogic:hasLootedRequiredItem(activeNpcNumber, pConversingPlayer)
	if pConversingPlayer == nil then
		return false
	end

	local creature = LuaCreatureObject(pConversingPlayer)

	local pInventory = creature:getSlottedObject("inventory")
	if pInventory == nil then
		return false
	end

	local inventory = LuaSceneObject(pInventory)

	local numberOfItems = inventory:getContainerObjectsSize()
	local requiredItems = self:getRequiredItem(activeNpcNumber, pConversingPlayer)

	local unmatchedItems = 0
	local itemsToDestroy = {}
	for j = 1, # requiredItems, 1 do
		unmatchedItems = unmatchedItems + 1
		for i = 0, numberOfItems - 1, 1 do
			local pItem = inventory:getContainerObject(i)

			if pItem ~= nil then
				local item = LuaSceneObject(pItem)
				if requiredItems[j].itemTemplate == item:getTemplateObjectPath() and (requiredItems[j].itemName == item:getCustomObjectName() or requiredItems[j].itemName == item:getDisplayedName()) then
					table.insert(itemsToDestroy, item)
					unmatchedItems = unmatchedItems - 1
					break
				end
			end
		end
	end

	if unmatchedItems == 0 then
		for i = 1, # itemsToDestroy, 1 do
			itemsToDestroy[i]:destroyObjectFromWorld()
			itemsToDestroy[i]:destroyObjectFromDatabase()
		end
		return true
	else
		return false
	end
end

function ThemeParkLogic:getRequiredItem(activeNpcNumber, pConversingPlayer)
	local missionNumber = self:getCurrentMissionNumber(activeNpcNumber, pConversingPlayer)
	local mission = self:getMission(activeNpcNumber, missionNumber)

	return mission.itemSpawns
end

function ThemeParkLogic:getNpcWorldPosition(npcNumber)
	local worldPosition = { x = 0, y = 0 }

	for i = 1, # self.npcMap do
		local npcSpawnNumber = self.npcMap[i].npcNumber
		if npcNumber == npcSpawnNumber then
			if self.npcMap[i].spawnData.cellID == 0 then
				worldPosition.x = self.npcMap[i].spawnData.x
				worldPosition.y = self.npcMap[i].spawnData.y
			else
				worldPosition.x = self.npcMap[i].worldPosition.x
				worldPosition.y = self.npcMap[i].worldPosition.y
			end
		end
	end

	return worldPosition
end

function ThemeParkLogic:completeMission(pConversingPlayer)
	if pConversingPlayer == nil then
		return
	end

	local creature = LuaCreatureObject(pConversingPlayer)

	local npcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local stfFile = self:getStfFile(npcNumber)

	if self.missionCompletionMessageStf ~= "" then
		creature:sendSystemMessage(self.missionCompletionMessageStf)
	elseif self:isValidConvoString(stfFile, ":return_waypoint_description_" .. missionNumber) then
		creature:sendSystemMessage(stfFile .. ":return_waypoint_description_" .. missionNumber)
	else
		creature:sendSystemMessage("@theme_park/messages:static_completion_message")
	end

	local worldPosition = self:getNpcWorldPosition(npcNumber)

	local npcData = self:getNpcData(npcNumber)

	self:updateWaypoint(pConversingPlayer, npcData.spawnData.planetName, worldPosition.x, worldPosition.y, "return")

	writeData(creature:getObjectID() .. ":activeMission", 2)
	writeData(creature:getObjectID() .. ":destroyableBuildingID", 0)
end

function ThemeParkLogic:handleMissionReward(pConversingPlayer)
	local npcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local mission = self:getMission(npcNumber, missionNumber)
	local rewards = mission.rewards

	for i = 1, # rewards, 1 do
		local reward = rewards[i]
		if reward.rewardType == "credits" then
			self:giveCredits(pConversingPlayer, reward.amount)
		elseif reward.rewardType == "faction" then
			self:giveFaction(pConversingPlayer, reward.faction, reward.amount)
		elseif reward.rewardType == "loot" then
			self:giveLoot(pConversingPlayer, reward.lootGroup)
		elseif reward.rewardType == "badge" then
			self:giveBadge(pConversingPlayer, reward.badge)
		elseif reward.rewardType == "permission" then
			self:givePermission(pConversingPlayer, reward.permissionGroup)
		end
	end
end

function ThemeParkLogic:givePermission(pConversingPlayer, permissionGroup)
	if pConversingPlayer == nil then
		return
	end

	local creature = LuaCreatureObject(pConversingPlayer)
	local pGhost = creature:getPlayerObject()

	if pGhost ~= nil then
		local ghost = LuaPlayerObject(pGhost)
		ghost:addPermissionGroup(permissionGroup, true)
	end
end

function ThemeParkLogic:giveBadge(pConversingPlayer, badge)
	if pConversingPlayer == nil then
		return
	end

	local creature = LuaCreatureObject(pConversingPlayer)
	local pGhost = creature:getPlayerObject()

	if pGhost ~= nil then
		local ghost = LuaPlayerObject(pGhost)
		ghost:awardBadge(badge)
	end
end

function ThemeParkLogic:giveLoot(pConversingPlayer, lootGroup)
	if pConversingPlayer == nil then
		return
	end
	local creature = LuaCreatureObject(pConversingPlayer)

	local pInventory = creature:getSlottedObject("inventory")
	if pInventory == nil then
		return
	end

	createLoot(pInventory, lootGroup, 0, true)
	creature:sendSystemMessage("@theme_park/messages:theme_park_reward")
end

function ThemeParkLogic:giveCredits(pConversingPlayer, amount)
	if pConversingPlayer == nil then
		return
	end
	local creature = LuaCreatureObject(pConversingPlayer)

	creature:addCashCredits(amount, true)
	creature:sendSystemMessageWithDI("@theme_park/messages:theme_park_credits_pp", amount)
end

function ThemeParkLogic:giveFaction(pConversingPlayer, faction, points)
	if pConversingPlayer == nil then
		return
	end
	local creature = LuaCreatureObject(pConversingPlayer)
	local pPlayerObject = creature:getSlottedObject("ghost")
	local playerObject = LuaPlayerObject(pPlayerObject)

	playerObject:increaseFactionStanding(faction, points)
end

function ThemeParkLogic:giveItem(pConversingPlayer, itemList)
	if pConversingPlayer == nil then
		return
	end
	local creature = LuaCreatureObject(pConversingPlayer)

	local pInventory = creature:getSlottedObject("inventory")
	if pInventory == nil then
		return
	end

	for currentItem = 1, # itemList, 1 do
		local thisItem = itemList[currentItem]
		local itemTemplate = thisItem.itemTemplate
		local numberOfItemsOfThisType = math.random(thisItem.minimum, thisItem.maximum)

		for i = 1, numberOfItemsOfThisType, 1 do
			local pItem = giveItem(pInventory, itemTemplate, -1)
		end
	end
end

function ThemeParkLogic:cleanUpMission(pConversingPlayer)
	if pConversingPlayer == nil then
		return false
	end

	ObjectManager.withCreaturePlayerObject(pConversingPlayer, function(playerObject)
		playerObject:removeWaypointBySpecialType(WAYPOINTTHEMEPARK)
	end)

	local creature = LuaCreatureObject(pConversingPlayer)
	local npcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local currentMissionType = self:getMissionType(npcNumber, pConversingPlayer)

	if (currentMissionType == "destroy") then
		local buildingID = readData(creature:getObjectID() .. ":destroyableBuildingID")
		if (buildingID ~= 0) then
			removeObservers(getSceneObject(buildingID), OBJECTDESTRUCTION)
			destroyBuilding(buildingID)
		end
		writeData(creature:getObjectID() .. ":destroyableBuildingID", 0)
	end

	local numberOfObjects = readData(creature:getObjectID() .. ":missionStaticObjects")
	for i = 1, numberOfObjects, 1 do
		local objectID = readData(creature:getObjectID() .. ":missionStaticObject:no" .. i)
		local pObj = getSceneObject(objectID)

		ObjectManager.withSceneObject(pObj, function(obj)
			obj:destroyObjectFromWorld()
		end)
	end

	local numberOfSpawns = readData(creature:getObjectID() .. ":missionSpawns")
	for i = 1, numberOfSpawns, 1 do
		local objectID = readData(creature:getObjectID() .. ":missionSpawn:no" .. i)
		local pNpc = getSceneObject(objectID)

		if pNpc ~= nil then
			local npc = LuaSceneObject(pNpc)
			npc:destroyObjectFromWorld()
		end
	end
end

function ThemeParkLogic:removeDeliverItem(pConversingPlayer)
	if pConversingPlayer == nil then
		return false
	end

	local creature = LuaCreatureObject(pConversingPlayer)

	local pInventory = creature:getSlottedObject("inventory")
	if pInventory == nil then
		return false
	end

	local inventory = LuaSceneObject(pInventory)

	local numberOfItems = readData(creature:getObjectID() .. ":missionItems")
	for i = 1, numberOfItems, 1 do
		local itemID = readData(creature:getObjectID() .. ":missionItem:no" .. i)

		local pItem = inventory:getContainerObjectById(itemID)
		if pItem ~= nil then
			local item = LuaSceneObject(pItem)
			item:destroyObjectFromWorld()
			item:destroyObjectFromDatabase()
		end
	end
end

function ThemeParkLogic:goToNextMission(pConversingPlayer)
	if pConversingPlayer == nil then
		return
	end

	local npcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local npcData = self:getNpcData(npcNumber)
	local npcName = npcData.spawnData.npcTemplate

	local creature = LuaCreatureObject(pConversingPlayer)
	writeData(creature:getObjectID() .. ":activeMission", 0)
	writeData(creature:getObjectID() .. ":hasPreReqItem", 0)
	writeStringData(creature:getObjectID() .. ":activeScreenPlay", "")
	creature:setScreenPlayState(math.pow(2, missionNumber - 1), self.screenPlayState .. "_mission_" .. npcName)

	if missionNumber == table.getn(npcData.missions) then
		creature:setScreenPlayState(npcNumber, self.screenPlayState)
	end
end

function ThemeParkLogic:followPlayer(pConversingNpc, pConversingPlayer)
	if pConversingNpc ~= nil and pConversingPlayer ~= nil then
		local npc = LuaAiAgent(pConversingNpc)
		npc:setFollowObject(pConversingPlayer)
		npc:setAiTemplate("follow")
	end
end

function ThemeParkLogic:getMissionType(activeNpcNumber, pConversingPlayer)
	if pConversingPlayer == nil then
		return
	end

	local npcNumber = self:getActiveNpcNumber(pConversingPlayer)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pConversingPlayer)
	local mission = self:getMission(npcNumber, missionNumber)

	return mission.missionType
end

function ThemeParkLogic:escortedNpcCloseEnough(pConversingPlayer)
	if pConversingPlayer == nil then
		return false
	end

	local creature = LuaCreatureObject(pConversingPlayer)
	local playerSceneObject = LuaSceneObject(pConversingPlayer)

	local objectID = readData(creature:getObjectID() .. ":missionSpawn:no1")
	local pNpc = getSceneObject(objectID)

	if pNpc ~= nil then
		if playerSceneObject:getDistanceTo(pNpc) < 64 then
			return true
		end
	end

	return false
end

function ThemeParkLogic:resetCurrentMission(pConversingPlayer)
	if pConversingPlayer == nil then
		return
	end

	local creature = LuaCreatureObject(pConversingPlayer)
	writeData(creature:getObjectID() .. ":activeMission", 0)
	writeData(creature:getObjectID() .. ":breechNpcID", 0)
	writeData(creature:getObjectID() .. ":breechAreaID", 0)
	writeData(creature:getObjectID() .. ":hasPreReqItem", 0)
	writeStringData(creature:getObjectID() .. ":activeScreenPlay", "")

	self:cleanUpMission(pConversingPlayer)
end

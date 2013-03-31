WAYPOINT_COLOR_PURPLE = 5
SIT = 1
STAND = 0
FACTIONIMPERIAL = 0xDB4ACC54
FACTIONREBEL = 0x16148850

ThemeParkLogic = ScreenPlay:new {
	numberOfActs = 1,
	npcMap = {},
	permissionMap = {},
	className = "ThemeParkLogic",
	screenPlayState = "theme_park_general",
	distance = 1000,
	missionDescriptionStf = "",
	missionCompletionMessageStf = ""
}

function ThemeParkLogic:start()
	self:spawnNpcs()
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

function ThemeParkLogic:hasPermission(conditions, pCreature)
	local hasPermission = true
	for i = 1, # conditions, 1 do
		if conditions[i].permissionType == "faction" then
			if self:isInFaction(conditions[i].faction, pCreature) == false then
				hasPermission = false
			end
		elseif conditions[i].permissionType == "missionState" then
			if self:hasMissionState(conditions[i].mission, conditions[i].missionState, pCreature) == false then
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

function ThemeParkLogic:getHasWaypointNames(npcNumber)	
	local npcData = self:getNpcData(npcNumber)

	return npcData.hasWaypointNames
end

function ThemeParkLogic:handleMissionAccept(npcNumber, missionNumber, pConversingPlayer)
	local mission = self:getMission(npcNumber, missionNumber)
	
	if mission.missionType == "deliver" then
		return self:handleDeliverMissionAccept(mission, pConversingPlayer, missionNumber)
	elseif mission.missionType == "escort" then
		return self:handleEscortMissionAccept(mission, pConversingPlayer, missionNumber)
	elseif mission.missionType == "retrieve" then
		return self:handleRetrieveMissionAccept(mission, pConversingPlayer, missionNumber)
	elseif mission.missionType == "assassinate" then
		return self:handleAssassinateMissionAccept(mission, pConversingPlayer, missionNumber)
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
		self:writeData(pConversingPlayer, ":activeMission", 0)
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

function ThemeParkLogic:handleAssassinateMissionAccept(mission, pConversingPlayer, missionNumber)
	if self:spawnMissionNpcs(mission, pConversingPlayer) == true then
		self:writeData(pConversingPlayer, ":activeMission", 1)
		self:writeData(pConversingPlayer, ":killedMissionNpcs", 0)
		return true
	else
		return false
	end
end

function ThemeParkLogic:spawnMissionNpcs(mission, pConversingPlayer)
	if pConversingPlayer == nil then
		return false
	end
	local creature = LuaCreatureObject(pConversingPlayer)
	local numberOfSpawns = table.getn(mission.primarySpawns) + table.getn(mission.secondarySpawns)

	local spawnPoints = self:getSpawnPoints(numberOfSpawns, creature:getWorldPositionX(), creature:getWorldPositionY(), pConversingPlayer)
	if table.getn(spawnPoints) ~= numberOfSpawns then
		return false
	end
	
	writeData(creature:getObjectID() .. ":missionSpawns", numberOfSpawns)
	
	local mainNpcs = mission.primarySpawns
	for i = 1, table.getn(mission.primarySpawns), 1 do
		local pNpc = self:spawnNpc(mainNpcs[i], spawnPoints[i], pConversingPlayer, i)
		if pNpc ~= nil then
			if i == 1 then
				self:updateWaypoint(pConversingPlayer, mainNpcs[i].planetName, spawnPoints[i][1], spawnPoints[i][3], "target")
			end
			if mission.missionType == "assassinate" then
				createObserver(OBJECTDESTRUCTION, self.className, "notifyDefeatedTarget", pNpc)
				if mission.silentTarget ~= "yes" then
					createObserver(DAMAGERECEIVED, self.className, "notifyDamagedTarget", pNpc)
				end
				local npc = LuaCreatureObject(pNpc)
				local creature = LuaCreatureObject(pConversingPlayer)
				writeData(npc:getObjectID() .. ":missionOwnerID", creature:getObjectID())
			end
		end
	end
	
	local secondaryNpcs = mission.secondarySpawns
	for i = 1 + table.getn(mission.primarySpawns), numberOfSpawns, 1 do
		self:spawnNpc(secondaryNpcs[i - table.getn(mission.primarySpawns)], spawnPoints[i], pConversingPlayer, i)
	end
	
	return true
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

function ThemeParkLogic:notifyDamagedTarget(pTarget, pAttacker, damage)
	if pTarget == nil or pAttacker == nil then
		return 1
	end
	local npcNumber = self:getActiveNpcNumber(pAttacker)
	local missionNumber = self:getCurrentMissionNumber(npcNumber, pAttacker)
	local stfFile = self:getStfFile(npcNumber)
	
	local attacker = LuaCreatureObject(pAttacker)
	local target = LuaCreatureObject(pTarget)
	
	local targetID = target:getObjectID()
	local attackerID = attacker:getObjectID()
	
	if self:killedByCorrectPlayer(targetID, attackerID) == true then
		spatialChat(pTarget, stfFile .. ":npc_breech_" .. missionNumber)
		return 1
	end
	
	return 0
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
	writeData(creature:getObjectID() .. ":activeMission", 1)
	
	local itemsToGive = mission.itemSpawns
	
	local pInventory = creature:getSlottedObject("inventory")
	if pInventory == nil then
		return
	end
	
	writeData(creature:getObjectID() .. ":missionItems", table.getn(itemsToGive))
	
	for i = 1, table.getn(itemsToGive), 1 do
		local pItem = giveItem(pInventory, itemsToGive[i].itemTemplate, -1)
		
		if (pItem ~= nil) then
			local item = LuaSceneObject(pItem)
			item:setCustomObjectName(itemsToGive[i].itemName)
			item:sendTo(pConversingPlayer)
			writeData(creature:getObjectID() .. ":missionItem:no" .. i, item:getObjectID())
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
		local wpNames = self:getHasWaypointNames(activeNpcNumber)
		local currentMissionNumber = self:getCurrentMissionNumber(activeNpcNumber, pConversingPlayer)

		if wpNames == "no" then
			return self:getDefaultWaypointName(pConversingPlayer, direction)
		else
			local stfFile = self:getStfFile(activeNpcNumber)
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
		end
	else
		return "Return to the mission giver."
	end
end

function ThemeParkLogic:removeWaypoint(pConversingPlayer)
	if pConversingPlayer ~= nil then
		local creature = LuaCreatureObject(pConversingPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			local waypointID = readData(creature:getObjectID() .. "themePark:waypointID")
			ghost:removeWaypoint(waypointID, true)
		end
	end
end

function ThemeParkLogic:updateWaypoint(pConversingPlayer, planetName, x, y, direction)
	self:removeWaypoint(pConversingPlayer)
	if pConversingPlayer ~= nil then
		local creature = LuaCreatureObject(pConversingPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)

			waypointID = ghost:addWaypoint(planetName, self:getMissionDescription(pConversingPlayer, direction), "", x, y, WAYPOINT_COLOR_PURPLE, true, true)
			writeData(creature:getObjectID() .. "themePark:waypointID", waypointID)
		end
	end
end

function ThemeParkLogic:getSpawnPoints(numberOfSpawns, x, y, pConversingPlayer)
	local spawnPoints = {}
	
	local spawnDistance = self.distance

	local firstSpawnPoint = getSpawnPoint(pConversingPlayer, x, y, spawnDistance, (spawnDistance/2)*3)
	if firstSpawnPoint ~= nil then
		table.insert(spawnPoints, firstSpawnPoint)
		for i = 2, numberOfSpawns, 1 do
			local nextSpawnPoint = getSpawnPoint(pConversingPlayer, firstSpawnPoint[1], firstSpawnPoint[3], 5, 15)
			if nextSpawnPoint ~= nil then
				table.insert(spawnPoints, nextSpawnPoint)
			end
		end
	end
	
	return spawnPoints
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
				if requiredItems[j].itemTemplate == item:getTemplateObjectPath() and requiredItems[j].itemName == item:getCustomObjectName() then
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

	if self.missionCompletionMessageStf == "" then
		local stfFile = self:getStfFile(npcNumber)
		creature:sendSystemMessage(stfFile .. ":return_waypoint_description_" .. missionNumber)
	else
		creature:sendSystemMessage(self.missionCompletionMessageStf)
	end

	local worldPosition = self:getNpcWorldPosition(npcNumber)

	local npcData = self:getNpcData(npcNumber)

	self:updateWaypoint(pConversingPlayer, npcData.spawnData.planetName, worldPosition.x, worldPosition.y, "return")

	writeData(creature:getObjectID() .. ":activeMission", 2)
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
	
	createLoot(pInventory, lootGroup, 0)
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
			
			if (pItem ~= nil) then
				local item = LuaSceneObject(pItem)
				item:sendTo(pConversingPlayer)
			end
		end
	end
end

function ThemeParkLogic:cleanUpMission(pConversingPlayer)
	if pConversingPlayer == nil then
		return false
	end

	self:removeWaypoint(pConversingPlayer)

	local creature = LuaCreatureObject(pConversingPlayer)
	
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
	creature:setScreenPlayState(math.pow(2, missionNumber - 1), self.screenPlayState .. "_mission_" .. npcName)
	
	if missionNumber == table.getn(npcData.missions) then
		creature:setScreenPlayState(npcNumber, self.screenPlayState)
	end
end

function ThemeParkLogic:followPlayer(pConversingNpc, pConversingPlayer)
	if pConversingNpc ~= nil and pConversingPlayer ~= nil then
		local npc = LuaAiAgent(pConversingNpc)
		npc:setFollowObject(pConversingPlayer)
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
	
	self:cleanUpMission(pConversingPlayer)
end

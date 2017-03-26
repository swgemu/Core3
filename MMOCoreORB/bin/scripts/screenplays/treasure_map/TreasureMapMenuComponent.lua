local ObjectManager = require("managers.object.object_manager")

local mapStringName = { "pirate1", "pirate2", "bountyhunter1", "hedon1" }

local treasureMapData = {
	{ planet = "corellia", x = 3400, y = -1400 }, -- Pirate 1
	{ planet = "naboo", x = -1900, y = -4000 }, -- Pirate 2
	{ planet = "talus", x = 3800, y = -1000 }, -- Bounty Hunter
	{ planet = "tatooine", x = 6700, y = 4240 } -- Scythe Schematic
}

local TREASURE_CHEST_LIFESPAN = 600000 --10 minutes

TreasureMapMenuComponent = { }

function TreasureMapMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(120, 3, "@treasure_map/treasure_map:use") -- Read
	menuResponse:addRadialMenuItem(121, 3, "@treasure_map/treasure_map:search_area") -- Search Area
	menuResponse:addRadialMenuItem(122, 3, "@treasure_map/treasure_map:extract_treasure") -- Extract Treasure
end

function TreasureMapMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	if (SceneObject(pObject):isASubChildOf(pPlayer) == false) then
		CreatureObject(pPlayer):sendSystemMessage("@treasure_map/treasure_map:sys_not_in_inv") -- The treasure map must be in your inventory for you to use it!
		return 0
	end

	if (TreasureMapMenuComponent:getMapType(pObject) == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@treasure_map/treasure_map:map_fail") -- This map is obviously a fake.
		return 0
	end

	if (selectedID == 120) then
		TreasureMapMenuComponent:doReadMap(pObject, pPlayer)
	elseif (selectedID == 121) then
		TreasureMapMenuComponent:doSearchArea(pObject, pPlayer)
	elseif (selectedID == 122) then
		TreasureMapMenuComponent:doExtractTreasure(pObject, pPlayer)
	end
	return 0
end

function TreasureMapMenuComponent:doSearchArea(pObject, pPlayer)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	local mapType = TreasureMapMenuComponent:getMapType(pObject)

	local mapData = treasureMapData[mapType]
	local playerID = CreatureObject(pPlayer):getObjectID()
	local waypointID = readData(playerID .. ":treasureMapSearchAreaWaypointID")
	local searchAreaID = readData(playerID .. ":treasureMapSearchAreaActiveAreaID")

	if (waypointID == 0 or searchAreaID == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@treasure_map/treasure_map:sys_no_waypoint") -- You must store the treasure's waypoint in your datapad before you can search for it!
		return 0
	end

	if (TangibleObject(pPlayer):hasActiveArea(searchAreaID) == false) then
		CreatureObject(pPlayer):sendSystemMessage("@treasure_map/treasure_map:sys_cant_pinpoint") -- You are not close enough to pinpoint the treasure's location.
		return 0
	end

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@treasure_map/treasure_map:sys_no_waypoint") -- You must store the treasure's waypoint in your datapad before you can search for it!
		return 0
	end

	local pActiveArea = getSceneObject(searchAreaID)
	SceneObject(pActiveArea):destroyObjectFromWorld()
	local zoneName = SceneObject(pPlayer):getZoneName()

	local spawnPoint

	if (mapType == 4) then
		spawnPoint = getSpawnPoint(zoneName, SceneObject(pWaypoint):getWorldPositionX(), SceneObject(pWaypoint):getWorldPositionY(), 15, 30, true)
	else
		spawnPoint = getSpawnPoint(zoneName, SceneObject(pWaypoint):getWorldPositionX(), SceneObject(pWaypoint):getWorldPositionY(), 30, 60)
	end

	CreatureObject(pPlayer):sendSystemMessage("@treasure_map/treasure_map:sys_pinpoint") -- You have successfully pinpointed the exact location of the treasure!
	local waypointID = PlayerObject(pGhost):addWaypoint(mapData.planet, "@treasure_map/treasure_map:waypoint_name", "", spawnPoint[1], spawnPoint[3], WAYPOINTGREEN, true, true, WAYPOINTTREASUREMAP, 0)
	writeData(playerID .. ":treasureMapExactWaypointID", waypointID)
	deleteData(playerID .. ":treasureMapSearchAreaWaypointID")
	deleteData(playerID .. ":treasureMapSearchAreaActiveAreaID")
end

function TreasureMapMenuComponent:doExtractTreasure(pObject, pPlayer)
	if (pObject == nil or pPlayer == nil) then
		return 0
	end

	local mapType = TreasureMapMenuComponent:getMapType(pObject)
	local playerID = SceneObject(pPlayer):getObjectID()

	local mapData = treasureMapData[mapType]
	local waypointID = readData(playerID .. ":treasureMapExactWaypointID")

	local pWaypoint = getSceneObject(waypointID)

	if (pWaypoint == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@treasure_map/treasure_map:sys_no_waypoint") -- You must store the treasure's waypoint in your datapad before you can search for it!
		return 0
	end

	local x = SceneObject(pWaypoint):getWorldPositionX()
	local y = SceneObject(pWaypoint):getWorldPositionY()
	local z = getTerrainHeight(pPlayer, x, y)

	if (SceneObject(pPlayer):getDistanceToPosition(x, z, y) > 5) then
		CreatureObject(pPlayer):sendSystemMessage("@treasure_map/treasure_map:sys_dist_far") -- You aren't close enough to extract the treasure.
		return 0
	end

	local treasureChestID = readData(playerID .. ":treasureChestID")

	if (treasureChestID ~= nil) then
		local pExistingChest = getSceneObject(treasureChestID)
		if (pExistingChest ~= nil) then
			self:removeTreasureChest(pExistingChest)
		end
	end

	CreatureObject(pPlayer):sendSystemMessage("@treasure_map/treasure_map:sys_found") -- You successfully extract the treasure!

	local pChest = spawnSceneObject(mapData.planet, "object/tangible/container/drum/treasure_drum.iff", x, z, y, 0, 0, 0, 0, 0)

	if (pChest ~= nil) then
		local chestID = SceneObject(pChest):getObjectID()
		writeData(playerID .. ":treasureChestID", chestID)
		writeData(chestID .. ":ownerID", playerID)
		SceneObject(pChest):setContainerOwnerID(playerID)
		createObserver(OPENCONTAINER, "TreasureMapMenuComponent", "openChestEvent", pChest)
		createObserver(CONTAINERCONTENTSCHANGED, "TreasureMapMenuComponent", "chestLootedEvent", pChest)
		TreasureMapMenuComponent:spawnTreasureLoot(pChest, pPlayer, mapType)
		createEvent(TREASURE_CHEST_LIFESPAN, "TreasureMapMenuComponent", "removeTreasureChest", pChest, "")
	end

	TreasureMapMenuComponent:spawnTreasureDefenders(pObject, pPlayer, x, z, y, mapType)
	SceneObject(pObject):destroyObjectFromWorld()
	SceneObject(pObject):destroyObjectFromDatabase(true)
end

function TreasureMapMenuComponent:chestLootedEvent(pChest, pCreature)
	if (pChest == nil) then
		return 0
	end

	if (SceneObject(pChest):getContainerObjectsSize() == 0) then
		TreasureMapMenuComponent:removeTreasureChest(pChest)
	end

	return 0
end

function TreasureMapMenuComponent:openChestEvent(pChest, pCreature)
	if pCreature == nil or pChest == nil or not SceneObject(pCreature):isCreatureObject() then
		return 0
	end

	local chestOwnerID = readData(SceneObject(pChest):getObjectID() .. ":ownerID")
	local playerID = CreatureObject(pCreature):getObjectID()

	if (chestOwnerID ~= playerID) then
		CreatureObject(pCreature):sendSystemMessage("@treasure_map/treasure_map:sys_not_yours") -- That treasure chest doesn't belong to you.
		return 0
	end

	local hasOpenedChest = readData(playerID .. ":hasOpenedChest")

	if (hasOpenedChest ~= 1) then
		local credits = getRandomNumber(500, 5000)
		CreatureObject(pCreature):addCashCredits(credits, true)
		CreatureObject(pCreature):sendSystemMessage("You find " .. credits .. " credits in the chest.")
		writeData(playerID .. ":hasOpenedChest", 1)
	end

	return 0
end

function TreasureMapMenuComponent:spawnTreasureLoot(pChest, pPlayer, mapType)
	if (pPlayer == nil or pChest == nil) then
		return
	end

	if (mapType == 1 or mapType == 2 or mapType == 3) then
		local playerLevelRange = getRandomNumber(CreatureObject(pPlayer):getLevel() - 5, CreatureObject(pPlayer):getLevel() + 5)

		for i = 1, 5 do
			createLoot(pChest, "treasure_map_group", playerLevelRange, false)
		end
	else
		createLoot(pChest, "hedon_istee_treasure", 10, false)
	end
end

function TreasureMapMenuComponent:spawnTreasureDefenders(pObject, pPlayer, x, z, y, mapType)
	if (pObject == nil or pPlayer == nil) then
		return
	end

	local zoneName = SceneObject(pPlayer):getZoneName()
	local mapType = TreasureMapMenuComponent:getMapType(pObject)
	local mapData = treasureMapData[mapType]
	local firstSpawnPoint, secondSpawnPoint, thirdSpawnPoint
	if (mapType ~= 4) then
		firstSpawnPoint = getSpawnPoint(zoneName, x, y, 10, 20)
	end

	if (mapType == 1 or mapType == 2) then
		secondSpawnPoint = getSpawnPoint(zoneName, x, y, 10, 20)
		thirdSpawnPoint = getSpawnPoint(zoneName, x, y, 10, 20)
		local pMobile = spawnMobile(mapData.planet, "pirate_leader", 0, firstSpawnPoint[1], firstSpawnPoint[2], firstSpawnPoint[3], 0, 0)
		TreasureMapMenuComponent:setDefenderAggro(pMobile, pPlayer)
		spatialChat(pMobile, "@treasure_map/treasure_map:bark_" .. mapStringName[mapType])
		local pMobile2 = spawnMobile(mapData.planet, "pirate_armsman", 0, secondSpawnPoint[1], secondSpawnPoint[2], secondSpawnPoint[3], 0, 0)
		TreasureMapMenuComponent:setDefenderAggro(pMobile2, pPlayer)
		local pMobile3 = spawnMobile(mapData.planet, "pirate_armsman", 0, thirdSpawnPoint[1], thirdSpawnPoint[2], thirdSpawnPoint[3], 0, 0)
		TreasureMapMenuComponent:setDefenderAggro(pMobile3, pPlayer)
	elseif (mapType == 3) then
		local pMobile = spawnMobile(mapData.planet, "bounty_hunter_thug", 0, firstSpawnPoint[1], firstSpawnPoint[2], firstSpawnPoint[3], 0, 0)
		spatialChat(pMobile, "@treasure_map/treasure_map:bark_" .. mapStringName[mapType])
		TreasureMapMenuComponent:setDefenderAggro(pMobile, pPlayer)
	else
		spawnMobile(mapData.planet, "canyon_krayt_dragon", 0, x, z, y, 0, 0)
	end
end

function TreasureMapMenuComponent:setDefenderAggro(pCreature, pPlayer)
	if (pCreature == nil) then
		return
	end

	AiAgent(pCreature):setDefender(pPlayer)
end

function TreasureMapMenuComponent:removeTreasureChest(pChest)
	if (pChest == nil) then
		return
	end

	local chestID = SceneObject(pChest):getObjectID()
	local chestOwnerID = readData(chestID .. ":ownerID")
	local pOwner = getSceneObject(chestOwnerID)

	if (pOwner ~= nil) then
		local pGhost = CreatureObject(pOwner):getPlayerObject()

		if (pGhost ~= nil) then
			PlayerObject(pGhost):removeWaypointBySpecialType(WAYPOINTTREASUREMAP)
		end
	end

	deleteData(chestOwnerID .. ":treasureChestID")
	deleteData(chestID .. ":ownerID")
	SceneObject(pChest):destroyObjectFromWorld()

	deleteData(chestOwnerID .. ":hasOpenedChest")
	deleteData(chestOwnerID .. ":treasureMapExactWaypointID")
end

function TreasureMapMenuComponent:doReadMap(pObject, pPlayer)
	if (pObject == nil or pPlayer == nil) then
		return
	end

	local mapType = TreasureMapMenuComponent:getMapType(pObject)
	local suiManager = LuaSuiManager()
	suiManager:sendMessageBox(pObject, pPlayer, "@treasure_map/treasure_map:title_" .. mapStringName[mapType], "@treasure_map/treasure_map:text_" .. mapStringName[mapType], "@treasure_map/treasure_map:store_waypoint", "TreasureMapMenuComponent", "handleTreasureMapSuiCallback")
end

function TreasureMapMenuComponent:handleTreasureMapSuiCallback(pCreature, pSui, eventIndex)
	local pGhost = CreatureObject(pCreature):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed or pCreature == nil) then
		return 0
	end

	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()

	if (pUsingObject == nil) then
		return 0
	end

	local mapType = TreasureMapMenuComponent:getMapType(pUsingObject)

	local mapData = treasureMapData[mapType]
	if (CreatureObject(pCreature):getZoneName() ~= mapData.planet) then
		CreatureObject(pCreature):sendSystemMessage("@treasure_map/treasure_map:wrong_planet") -- The coordinates stored in the map data do not appear to be for this planet.
		return 0
	end
	local playerID = CreatureObject(pCreature):getObjectID()

	local currentWaypointID = readData(playerID .. ":treasureMapSearchAreaWaypointID")
	local exactWaypointID = readData(playerID .. ":treasureMapExactWaypointID")
	local pExactWaypoint = getSceneObject(currentWaypointID)
	local pWaypoint = getSceneObject(currentWaypointID)

	if (pWaypoint ~= nil or pExactWaypoint ~= nil) then
		CreatureObject(pCreature):sendSystemMessage("@treasure_map/treasure_map:sys_waypoint_exists") -- A waypoint to this location already exists in your datapad.
		return 0
	end

	local spawnPoint
	local zoneName = SceneObject(pCreature):getZoneName()

	if (mapType == 4) then
		spawnPoint = getSpawnPoint(zoneName, mapData.x, mapData.y, 1, 50, true)
	else
		spawnPoint = getSpawnPoint(zoneName, mapData.x, mapData.y, 1, 2000)
	end

	local waypointID = PlayerObject(pGhost):addWaypoint(mapData.planet, "@treasure_map/treasure_map:waypoint_name", "", spawnPoint[1], spawnPoint[3], WAYPOINTGREEN, true, true, WAYPOINTTREASUREMAP, 0)
	local activeAreaID = self:spawnSearchArea(mapType, pCreature, spawnPoint[1], spawnPoint[3])
	writeData(playerID .. ":treasureMapSearchAreaWaypointID", waypointID)
	writeData(playerID .. ":treasureMapSearchAreaActiveAreaID", activeAreaID)
end

function TreasureMapMenuComponent:spawnSearchArea(mapType, pCreature, x, y)
	if (pCreature == nil) then
		return 0
	end

	local mapData = treasureMapData[mapType]
	local z = getTerrainHeight(pCreature, x, y)
	local pActiveArea = spawnActiveArea(mapData.planet, "object/active_area.iff", x, z, y, 64, 0)

	if pActiveArea ~= nil then
		return SceneObject(pActiveArea):getObjectID()
	else
		return 0
	end
end

function TreasureMapMenuComponent:getMapType(pObject)
	if (pObject == nil) then
		return 0
	end

	local objectTemplate = SceneObject(pObject):getTemplateObjectPath()

	if (objectTemplate == "object/tangible/treasure_map/treasure_map_pirate1.iff") then
		return 1
	elseif (objectTemplate == "object/tangible/treasure_map/treasure_map_pirate2.iff") then
		return 2
	elseif (objectTemplate == "object/tangible/treasure_map/treasure_map_bh.iff") then
		return 3
	elseif (objectTemplate == "object/tangible/loot/quest/treasure_map_hedon.iff") then
		return 4
	else
		return 0
	end
end

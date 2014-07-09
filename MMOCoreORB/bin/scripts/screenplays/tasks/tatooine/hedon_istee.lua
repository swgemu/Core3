hedon_istee_missions =
{
	{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "drognuz", planetName = "tatooine", npcName = "Drognuz" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 3000 } 
		}
	},
	{
		missionType = "assassinate",
		primarySpawns = 
		{ 
			{ npcTemplate = "rath_kanaz", planetName = "tatooine", npcName = "Rath Kanaz" } 
		}, 
		secondarySpawns = {},
		itemSpawns = {}, 
		rewards = 
		{ 
			{ rewardType = "credits", amount = 6000 } 
		}
	},
	{
		missionType = "deliver", 
		primarySpawns = 
		{ 
			{ npcTemplate = "serene_floater", planetName = "tatooine", npcName = "Serene Floater" } 
		}, 
		secondarySpawns = {}, 
		itemSpawns = 
		{
			{ itemTemplate = "object/tangible/mission/quest_item/hedon_istee_q3_needed.iff", itemName = "B'omarr Sacred Scroll" }
		}, 
		rewards = 
		{ 
			{ rewardType = "loot",  lootGroup = "task_reward_hedon_istee" },
		}
	}
}

npcMapHedonIstee = 
{ 
	{ 
		spawnData = { planetName = "tatooine", npcTemplate = "hedon_istee", x = 1390, z = 7, y = 3197, direction = 0, cellID = 0, position = STAND },
		npcNumber = 1,
		stfFile = "@static_npc/tatooine/hedon_istee",
		missions = hedon_istee_missions
	},
}

HedonIstee = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapHedonIstee,
	permissionMap = {},
	className = "HedonIstee",
	screenPlayState = "hedon_istee_task",
	distance = 800,
	mapX = 6700,
	mapY = 4240,
	mapZ = 20,
	treasure_life = 600000 --10 minutes
}

registerScreenPlay("HedonIstee", true)

hedon_istee_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = HedonIstee
}
hedon_istee_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = HedonIstee
}

function HedonIstee:spawnActiveArea()
	local pActiveArea = spawnSceneObject("tatooine", "object/active_area.iff", HedonIstee.mapX, HedonIstee.mapZ, HedonIstee.mapY, 0, 0, 0, 0, 0)
	local scno = LuaSceneObject(pActiveArea)
	local area = LuaActiveArea(pActiveArea)
	area:setRadius(32)

	return scno:getObjectID()

end

function HedonIstee:handleTreasureMapCallback(pCreature, pSui, cancelPressed)
	if (not cancelPressed) then
		if (pCreature ~= nil) then
			local creature = LuaCreatureObject(pCreature)
			local pPlayerObject = creature:getPlayerObject()
			
			if (pPlayerObject ~= nil) then
				local playerObject = LuaPlayerObject(pPlayerObject)
				local waypointID = playerObject:addWaypoint("tatooine", "Ancient Treasure Location", "", HedonIstee.mapX, HedonIstee.mapY, WAYPOINTGREEN, true, true, 0)
				local activeAreaID = self:spawnActiveArea()
				writeData(creature:getObjectID() .. ":scytheTreasureWaypointID", waypointID)
				writeData(creature:getObjectID() .. ":treasureActiveAreaID", activeAreaID)
			end
		end
	end
end

function HedonIstee:spawnTreasure(pTreasureMap, pPlayer)
	local creature = LuaCreatureObject(pPlayer)
	creature:sendSystemMessage("@treasure_map/treasure_map:sys_found") --You successfully extract the treasure!

	local pPlayerObject = creature:getPlayerObject()

	if (pPlayerObject ~= nil) then
		local playerObject = LuaPlayerObject(pPlayerObject)
		local oldWaypoint = readData(creature:getObjectID() .. ":scytheTreasureWaypointID")
		playerObject:removeWaypoint(oldWaypoint, true)

		local objectID = readData(creature:getObjectID() .. ":treasureActiveAreaID")
		local pActiveArea = getSceneObject(objectID)
		if (pActiveArea ~= nil) then
			local area = LuaSceneObject(pActiveArea)
			area:destroyObjectFromWorld()
			area:destroyObjectFromDatabase()
		end

		local x = HedonIstee.mapX - math.random(200)
		local y = HedonIstee.mapY - math.random(200)
		local z = getTerrainHeight(pPlayer, x, y)

		playerObject:addWaypoint("tatooine", "Ancient Treasure Location", "", x, y, WAYPOINTGREEN, true, true, 0)

		local pChest = spawnSceneObject("tatooine", "object/tangible/container/drum/treasure_drum.iff", x, z, y, 0, 0, 0, 0, 0)
		local pKrayt = spawnMobile("tatooine", "canyon_krayt_dragon", 0, x, z, y, 0, 0)

		if (pChest ~= nil) then
			local chest = LuaSceneObject(pChest)
			chest:setContainerOwnerID(creature:getObjectID())
			createLoot(pChest, "hedon_istee_treasure", 10, false)
			createEvent(HedonIstee.treasure_life, "HedonIstee", "removeTreasureChest", pChest)
		end

		if (pTreasureMap ~= nil) then
			local map = LuaSceneObject(pTreasureMap)
			map:destroyObjectFromWorld()
			map:destroyObjectFromDatabase()
		end
	end
end

function HedonIstee:removeTreasureChest(pChest)
	if (pChest ~= nil) then
		local chest = LuaSceneObject(pChest)
		chest:destroyObjectFromWorld()
		chest:destroyObjectFromDatabase(true)
	end
end


hedon_istee_holo_map_menucomponent = { }


function hedon_istee_holo_map_menucomponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	
	local player = LuaSceneObject(pPlayer)
	
	if (player:hasActiveArea(readData(player:getObjectID() .. ":treasureActiveAreaID"))) then
		menuResponse:addRadialMenuItem(121, 3, "@treasure_map/treasure_map:extract_treasure") --Extract Treasure
	else
		menuResponse:addRadialMenuItem(120, 3, "@treasure_map/treasure_map:use") --Read
	end
end

function hedon_istee_holo_map_menucomponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end
	
	local luaSceneObject = LuaSceneObject(pSceneObject)
	
	if (luaSceneObject:isASubChildOf(pPlayer) == false) then
		return 0
	end
	
	if (selectedID == 120) then
		local suiManager = LuaSuiManager()
		suiManager:sendMessageBox(pSceneObject, pPlayer, "@treasure_map/treasure_map:title_hedon1", "@treasure_map/treasure_map:text_hedon1", "@treasure_map/treasure_map:store_waypoint", "HedonIstee", "handleTreasureMapCallback")
	elseif (selectedID == 121) then
		HedonIstee:spawnTreasure(pSceneObject, pPlayer)
	end
			
	return 0
end


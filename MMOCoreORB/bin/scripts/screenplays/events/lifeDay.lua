local ObjectManager = require("managers.object.object_manager")

lifeDayScreenplay = ScreenPlay:new {
	numberOfActs = 1,

	greeterLocs = {
		{ planet = "naboo", x = -5586.6, z = -150, y = -33.5, angle = 87, cell = 0 }, -- Lake Retreat
		{ planet = "tatooine", x = 119.4, z = 52.0, y = -5353.7, angle = -99, cell = 0 }, -- Anchorhead
		{ planet = "corellia", x = -5544.5, z = 23.4, y = -6176.6, angle = -96, cell = 0 }, -- Vreni Island
	},

	waypointPlanets = {"endor","dathomir","lok","yavin4"},

	camp = "object/building/poi/custom/life_day_hut.iff",

	campMobs = {
		{ mobile = "oraalarri", x = -2.8, y = -1.5, heading = 12},
		{ mobile = "anarra", x = 3.4, y = -1.7, heading = -36},
		{ mobile = "radrrl", x = -1.7, y = 9.3, heading = 67},
		{ mobile = "tebeurra", x = 3.3, y = 8.7, heading = 0},
	},

	randomGifts = {"object/tangible/loot/quest/lifeday_orb.iff",
			"object/tangible/painting/painting_wookiee_m.iff",
			"object/tangible/painting/painting_wookiee_f.iff",
			"object/tangible/painting/painting_trees_s01.iff"},

	robe = "object/tangible/wearables/wookiee/wke_lifeday_robe.iff"
}

registerScreenPlay("lifeDayScreenplay", true)

function lifeDayScreenplay:start()
	self:spawnMobiles()
end

function lifeDayScreenplay:spawnMobiles()
	local mobiles = self.greeterLocs
	for i = 1, table.getn(mobiles), 1 do
		if isZoneEnabled(mobiles[i].planet) then
			spawnMobile(mobiles[i].planet, "kkatamk", 1, mobiles[i].x, mobiles[i].z, mobiles[i].y, mobiles[i].angle, mobiles[i].cell)
		end
	end
end

function lifeDayScreenplay:getRandomEnabledPlanet()
	local enabledPlanets = {}
	for i = 1, table.getn(self.waypointPlanets), 1 do
		if isZoneEnabled(self.waypointPlanets[i]) then
			enabledPlanets[table.getn(enabledPlanets) + 1] = self.waypointPlanets[i]
		end
	end

	local rand = getRandomNumber(1, table.getn(enabledPlanets))
	return enabledPlanets[rand]
end

function lifeDayScreenplay:removeWaypoint(pPlayer)
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, ghost)
		local oldWaypointID = readData(player:getObjectID() .. "lifeDayWaypointID")

		if oldWaypointID ~= "" and oldWaypointID ~= nil and oldWaypointID ~= 0 then
			ghost:removeWaypoint(oldWaypointID, true)
			writeData(player:getObjectID() .. "lifeDayWaypointID", 0)
		end
	end)
end

function lifeDayScreenplay:removeArea(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local areaID = readData(player:getObjectID() .. ":lifeDayAreaID")

		if areaID ~= "" and areaID ~= nil and areaID ~= 0 then
			local pArea = getSceneObject(areaID)
			if pArea ~= nil then
				SceneObject(pArea):destroyObjectFromWorld(true)
			end
			writeData(player:getObjectID() .. "lifeDayAreaID", 0)
		end
	end)
end

function lifeDayScreenplay:giveWaypoint(pPlayer)
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, ghost)
		self:cleanupCamp(pPlayer)

		local planet = self:getRandomEnabledPlanet()

		if planet == "" then
			player:sendSystemMessage("Error finding a planet.")
			return
		end

		local spawnPoint = getSpawnArea(pPlayer, 0, 0, 0, 8000, 20, 5, planet)
		if spawnPoint ~= nil then
			local pArea = spawnSceneObject(planet, "object/active_area.iff", spawnPoint[1], spawnPoint[2], spawnPoint[3], 0, 0, 0, 0, 0)
			if (pArea ~= nil) then
				local activeArea = ActiveArea(pArea)
				activeArea:setRadius(128)
				activeArea:setNoSpawnArea(true)
				createObserver(ENTEREDAREA, "lifeDayScreenplay", "notifyEnteredLifeDayArea", pArea)

				local newWaypointID = ghost:addWaypoint(planet, "@quest/lifeday/lifeday:waypoint_name", "", spawnPoint[1], spawnPoint[3], 2, true, true, 0, 0) -- Life Day Celebration
				writeData(player:getObjectID() .. "lifeDayWaypointID", newWaypointID)
				writeData(player:getObjectID() .. ":lifeDayState", 1)
				writeData(player:getObjectID() .. ":lifeDayAreaID", SceneObject(pArea):getObjectID())

				player:sendSystemMessage("@quest/lifeday/lifeday:waypoint_updated") -- A waypoint to a planet holding a Life Day celebration was added to your datapad.

				createEvent(3600000, "lifeDayScreenplay", "cleanupCamp", pPlayer)
			end
		end
	end)
end

function lifeDayScreenplay:notifyEnteredLifeDayArea(pActiveArea, pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local areaID = readData(playerID .. ":lifeDayAreaID")

	if (readData(playerID .. ":lifeDayAreaTriggered") == 1) then
		return 0
	end

	if (SceneObject(pActiveArea):getObjectID() == areaID) then
		writeData(playerID .. ":lifeDayAreaTriggered", 1)
		self:spawnCamp(pActiveArea, pPlayer)
		return 1
	end
	return 0
end

function lifeDayScreenplay:spawnCamp(pActiveArea, pPlayer)
	ObjectManager.withSceneObject(pActiveArea, function(area)
		local playerID = CreatureObject(pPlayer):getObjectID()
		local x = area:getPositionX()
		local y = area:getPositionY()
		local z = getTerrainHeight(pPlayer, x, y)
		local zoneName = area:getZoneName()
		local pCamp = spawnSceneObject(zoneName, self.camp, x, z, y, 0, 0, 0, 0, 0)

		if pCamp ~= nil then
			writeData(playerID .. ":lifeDayCampID", SceneObject(pCamp):getObjectID())
		end

		for i = 1, table.getn(self.campMobs), 1 do
			local pMob = spawnMobile(zoneName, self.campMobs[i].mobile, 0, x + self.campMobs[i].x, z, y + self.campMobs[i].y, self.campMobs[i].heading, 0)
			if pMob ~= nil then
				writeData(playerID .. ":lifeDayMobID" .. i, SceneObject(pMob):getObjectID())
			end
		end
	end)
end

function lifeDayScreenplay:cleanupCamp(pPlayer)
	self:removeWaypoint(pPlayer)
	self:removeArea(pPlayer)

	local playerID = CreatureObject(pPlayer):getObjectID()
	local campID = readData(playerID .. ":lifeDayCampID")

	if campID ~= "" and campID ~= nil and campID ~= 0 then
		local pCamp = getSceneObject(campID)

		if pCamp ~= nil then
			SceneObject(pCamp):destroyObjectFromWorld(true)
		end
		writeData(playerID .. ":lifeDayCampID", 0)
	end

	for i = 1, table.getn(self.campMobs), 1 do
		local mobID = readData(playerID .. ":lifeDayMobID" .. i)

		if mobID ~= "" and mobID ~= nil and mobID ~= 0 then
			local pMob = getSceneObject(mobID)

			if pMob ~= nil then
				SceneObject(pMob):destroyObjectFromWorld(true)
			end
			writeData(playerID .. ":lifeDayMobID" .. i, 0)
		end
	end
end

function lifeDayScreenplay:giveRandomGift(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local pInventory = player:getSlottedObject("inventory")

		ObjectManager.withSceneObject(pInventory, function(inventory)
			local slotsRemaining = inventory:getContainerVolumeLimit() - inventory:getContainerObjectsSize()
			if slotsRemaining <= 0 then
				player:sendSystemMessage("@quest/lifeday/lifeday:full_inv") -- Your inventory is full. Please make some room and speak to the NPC again to receive your gift.
				return
			end

			local rand = getRandomNumber(1, table.getn(self.randomGifts))
			local itemTemplate = self.randomGifts[rand]
			local pItem = giveItem(pInventory, itemTemplate, -1)

			writeScreenPlayData(pPlayer, "lifeDay", "complete", 1)
		end)
	end)
end

function lifeDayScreenplay:giveRobe(pPlayer)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local pInventory = player:getSlottedObject("inventory")

		ObjectManager.withSceneObject(pInventory, function(inventory)
			local slotsRemaining = inventory:getContainerVolumeLimit() - inventory:getContainerObjectsSize()
			if slotsRemaining <= 0 then
				player:sendSystemMessage("@quest/lifeday/lifeday:full_inv") -- Your inventory is full. Please make some room and speak to the NPC again to receive your gift.
				return
			end

			local pItem = giveItem(pInventory, self.robe, -1)

			writeScreenPlayData(pPlayer, "lifeDay", "complete", 1)
		end)
	end)
end


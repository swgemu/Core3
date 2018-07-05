local ObjectManager = require("managers.object.object_manager")

lifeDayScreenplay = ScreenPlay:new {
	numberOfActs = 1,

	mobiles = {
		{ mobile = "kkatamk", planet = "naboo", x = -5586.6, z = -150, y = -33.5, angle = 87 }, -- Lake Retreat
		{ mobile = "kkatamk", planet = "tatooine", x = 130.3, z = 52.0, y = -5383.7, angle = -88 }, -- Anchorhead
		{ mobile = "kkatamk", planet = "corellia", x = -5544.5, z = 23.4, y = -6176.6, angle = -96 }, -- Vreni Island

		{ mobile = "oraalarri", planet = "dathomir", x = -2580.2, z = 77.0, y = -5521.4, angle = 7 },
		{ mobile = "anarra", planet = "dathomir", x = -2574.9, z = 77.0, y = -5510.8, angle = -24 },
		{ mobile = "radrrl", planet = "dathomir", x = -2581.5, z = 77.0, y = -5510.3, angle = 28 },
		{ mobile = "tebeurra", planet = "dathomir", x = -2574.5, z = 77.0, y = -5518.8, angle = -50 },

		{ mobile = "oraalarri", planet = "endor", x = -1087.8, z = 6.2, y = -998.1, angle = -83 },
		{ mobile = "anarra", planet = "endor", x = -1098.9, z = 6.0, y = -993.8, angle = -160 },
		{ mobile = "radrrl", planet = "endor", x = -1098.6, z = 5.9, y = -999.3, angle = -35 },
		{ mobile = "tebeurra", planet = "endor", x = -1090.0, z = 6.2, y = -992.4, angle = -155 },

		{ mobile = "oraalarri", planet = "yavin4", x = -14.5, z = 163.5, y = -3917.0, angle = 123 },
		{ mobile = "anarra", planet = "yavin4", x = -5.9, z = 163.5, y = -3924.9, angle = 73 },
		{ mobile = "radrrl", planet = "yavin4", x = -3.6, z = 163.4, y = -3919.0, angle = 163 },
		{ mobile = "tebeurra", planet = "yavin4", x = -14.8, z = 163.5, y = -3922.5, angle = 65 },
	},

	waypoints = {
		{ planet = "dathomir", x = -2578.3, y = -5519.6, },
		{ planet = "endor", x = -1088.4, y = -996.0, },
		{ planet = "yavin4", x = -14.4, y = -3919.7, },
	},

	randomGifts = {"object/tangible/loot/quest/lifeday_orb.iff",
		"object/tangible/painting/painting_wookiee_m.iff",
		"object/tangible/painting/painting_wookiee_f.iff",
		"object/tangible/painting/painting_trees_s01.iff"},

	robe = "object/tangible/wearables/wookiee/wke_lifeday_robe.iff"
}

registerScreenPlay("lifeDayScreenplay", true)

function lifeDayScreenplay:start()
	if getFormattedTime():find("Dec") ~= nil then
		writeStringSharedMemory("lifeDayScreenplayName", "lifeDay" .. tostring(os.date('%Y')))
		self:spawnMobiles()
	end
end

function lifeDayScreenplay:spawnMobiles()
	local mobs = self.mobiles
	for i = 1, #mobs, 1 do
		if isZoneEnabled(mobs[i].planet) then
			spawnMobile(mobs[i].planet, mobs[i].mobile, 1, mobs[i].x, mobs[i].z, mobs[i].y, mobs[i].angle, 0)
		end
	end
end

function lifeDayScreenplay:getRandomEnabledPlanet()
	local enabledPlanets = {}
	for i = 1, #self.waypoints, 1 do
		if isZoneEnabled(self.waypoints[i].planet) then
			enabledPlanets[#enabledPlanets + 1] = i
		end
	end

	local rand = getRandomNumber(1, #enabledPlanets)
	return enabledPlanets[rand]
end

function lifeDayScreenplay:removeWaypoint(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local oldWaypointID = readData(playerID .. "lifeDayWaypointID")

	if oldWaypointID ~= "" and oldWaypointID ~= nil and oldWaypointID ~= 0 then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		end

		deleteData(playerID .. "lifeDayWaypointID")
	end
end

function lifeDayScreenplay:giveWaypoint(pPlayer)
	self:removeWaypoint(pPlayer)

	local num = self:getRandomEnabledPlanet()

	if num == "" or num == 0 or num == nil then
		CreatureObject(pPlayer):sendSystemMessage("Error finding a planet.")
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		local newWaypointID = PlayerObject(pGhost):addWaypoint(self.waypoints[num].planet, "@quest/lifeday/lifeday:waypoint_name", "", self.waypoints[num].x, self.waypoints[num].y, 2, true, true, 0, 0) -- Life Day Celebration
		writeData(playerID .. "lifeDayWaypointID", newWaypointID)
		writeData(playerID .. ":lifeDayState", 1)

		CreatureObject(pPlayer):sendSystemMessage("@quest/lifeday/lifeday:waypoint_updated") -- A waypoint to a planet holding a Life Day celebration was added to your datapad.

		createEvent(3600000, "lifeDayScreenplay", "removeWaypoint", pPlayer, "")
	end
end

function lifeDayScreenplay:giveRandomGift(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	if SceneObject(pInventory):isContainerFullRecursive() then
		CreatureObject(pPlayer):sendSystemMessage("@quest/lifeday/lifeday:full_inv") -- Your inventory is full. Please make some room and speak to the NPC again to receive your gift.
		return
	end

	local rand = getRandomNumber(1, #self.randomGifts)
	local itemTemplate = self.randomGifts[rand]
	local pItem = giveItem(pInventory, itemTemplate, -1)

	writeScreenPlayData(pPlayer, readStringSharedMemory("lifeDayScreenplayName"), "complete", 1)

	self:removeWaypoint(pPlayer)
end

function lifeDayScreenplay:giveRobe(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	if SceneObject(pInventory):isContainerFullRecursive() then
		CreatureObject(pPlayer):sendSystemMessage("@quest/lifeday/lifeday:full_inv") -- Your inventory is full. Please make some room and speak to the NPC again to receive your gift.
		return
	end

	local pItem = giveItem(pInventory, self.robe, -1)

	writeScreenPlayData(pPlayer, readStringSharedMemory("lifeDayScreenplayName"), "complete", 1)

	self:removeWaypoint(pPlayer)
end

function lifeDayScreenplay:noGift(pPlayer)
	if (pPlayer == nil) then
		return
	end

	writeScreenPlayData(pPlayer, readStringSharedMemory("lifeDayScreenplayName"), "complete", 1)
	self:removeWaypoint(pPlayer)
end

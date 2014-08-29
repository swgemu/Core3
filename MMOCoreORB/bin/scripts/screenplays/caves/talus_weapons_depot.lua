local ObjectManager = require("managers.object.object_manager")

TalusWeaponsDepotScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TalusWeaponsDepotScreenPlay",

	buildingID = 9686134,

--9686134 bunker rebel weapon depot
--9686309 security terminal
--9686329 power regulator
--9645673 uplink terminal
--9645698 terminal hq
--9645714 override terminal
}

registerScreenPlay("TalusWeaponsDepotScreenPlay", true)

function TalusWeaponsDepotScreenPlay:start()
	if (isZoneEnabled("talus")) then
		self:spawnSceneObjects()

		local pBuilding = getSceneObject(self.buildingID)
		createObserver(FACTIONBASEFLIPPED, "TalusWeaponsDepotScreenPlay", "flipBase", pBuilding)

		if getRandomNumber(100) >= 50 then
			self:spawnRebels(pBuilding)
		else
			self:spawnImperials(pBuilding)
		end
	end
end

function TalusWeaponsDepotScreenPlay:spawnSceneObjects()
	spawnSceneObject("naboo", "object/tangible/terminal/terminal_elevator_up.iff", -8.45, -20, 59, 9686145, .7, 0, .7, 0)
	spawnSceneObject("naboo", "object/tangible/terminal/terminal_elevator_down.iff", -8.45, -12, 59, 9686145, .7, 0, .7, 0)
	spawnSceneObject("naboo", "object/tangible/terminal/terminal_elevator_up.iff", 75.45, -50, 59, 9686170, .7, 0, -.7, 0)
	spawnSceneObject("naboo", "object/tangible/terminal/terminal_elevator_down.iff", 75.45, -20, 59, 9686170, .7, 0, -.7, 0)
end

function TalusWeaponsDepotScreenPlay:flipBase(pBuilding)

	ObjectManager.withBuildingObject(pBuilding, function(building)
		building:destroyChildObjects()

		if building:getFaction() == FACTIONIMPERIAL then
			self:spawnRebels(pBuilding)
		elseif building:getFaction() == FACTIONREBEL then
			self:spawnImperials(pBuilding)
		end
	end)

	return 0
end

function TalusWeaponsDepotScreenPlay:spawnImperials(pBuilding)

	ObjectManager.withBuildingObject(pBuilding, function(building)
		building:initializeStaticGCWBase(FACTIONIMPERIAL)

		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", 25.3, -12.0, 29.0, 9686140, .7, 0, .7, 0)

	   	building:spawnChildCreature("talus", "stormtrooper", 300, 15.5, -12.0, 28.3, -92, 9686140)
		building:spawnChildCreature("talus", "imperial_major", 300, 57.1, -12.0, 59.1, -97, 9686143)
		building:spawnChildCreature("talus", "imperial_staff_sergeant", 300, 55.7, -12.0, 64.7, 12, 9686143)
		building:spawnChildCreature("talus", "stormtrooper", 300, 35.0, -12.0, 55.7, -78, 9686143)
		building:spawnChildCreature("talus", "imperial_warrant_officer_i", 300, -10.4, -12.0, 105.4, -2, 9686150)
		building:spawnChildCreature("talus", "imperial_second_lieutenant", 300, -15.2, -12.0, 96.9, 90, 9686150)
		building:spawnChildCreature("talus", "stormtrooper", 300, -4.0, -12.0, 96.6, -68, 9686150)
		building:spawnChildCreature("talus", "imperial_corporal", 300, -1.3, -12.0, 117.5, -50, 9686149)
		building:spawnChildCreature("talus", "imperial_corporal", 300, 0.6, -12.0, 111.2, 0, 9686149)
		building:spawnChildCreature("talus", "imperial_second_lieutenant", 300, 16.4, -12.0, 92.7, 152, 9686148)
		building:spawnChildCreature("talus", "stormtrooper", 300, 97.4, -20.0, 135.9, 109, 9686159)
		building:spawnChildCreature("talus", "stormtrooper", 300, 105.5, -20.0, 130.8, 109, 9686159)
		building:spawnChildCreature("talus", "stormtrooper", 300, 96.7, -20.0, 125.5, -39, 9686159)
		building:spawnChildCreature("talus", "stormtrooper", 300, 44.8, -20.0, 151.3, 136, 9686155)
		building:spawnChildCreature("talus", "stormtrooper", 300, 49.8, -20.0, 150.0, 139, 9686155)
		building:spawnChildCreature("talus", "stormtrooper", 300, 50.1, -20.0, 139.0, 134, 9686155)
		building:spawnChildCreature("talus", "stormtrooper", 300, 52.6, -20.0, 139.1, -142, 9686155)
		building:spawnChildCreature("talus", "imperial_colonel", 300, 43.9, -20.0, 142.0, -14, 9686155)
		building:spawnChildCreature("talus", "imperial_medic", 300, 9.6, -12.0, 62.9, 85, 9686144)
		building:spawnChildCreature("talus", "imperial_corporal", 300, -2.4, -12.0, 62.0, -90, 9686144)
		building:spawnChildCreature("talus", "imperial_warrant_officer_i", 300, -3.5, -12.0, 73.6, 90, 9686144)
	end)
end

function TalusWeaponsDepotScreenPlay:spawnRebels(pBuilding)

	ObjectManager.withBuildingObject(pBuilding, function(building)
		building:initializeStaticGCWBase(FACTIONREBEL)

		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", 25.3, -12.0, 29.0, 9686140, .7, 0, .7, 0)

	   	building:spawnChildCreature("talus", "rebel_trooper", 300, 13.9, -12.0, 27.5, -68, 9686140)
		building:spawnChildCreature("talus", "rebel_major", 300, 55.0, -12.0, 55.9, -7, 9686143)
		building:spawnChildCreature("talus", "rebel_staff_sergeant", 300, 54.9, -12.0, 62.5, -179, 9686143)
		building:spawnChildCreature("talus", "rebel_trooper", 300, 39.2, -12.0, 60.6, -96, 9686143)
		building:spawnChildCreature("talus", "rebel_warrant_officer_i", 300, -12.2, -12.0, 94.6, 0, 9686150)
		building:spawnChildCreature("talus", "rebel_second_lieutenant", 300, -15.5, -12.0, 103.8, -40, 9686150)
		building:spawnChildCreature("talus", "rebel_trooper", 300, -4.0, -12.0, 101.3, -90, 9686150)
		building:spawnChildCreature("talus", "rebel_corporal", 300, 8.5, -12.0, 118.0, 45, 9686149)
		building:spawnChildCreature("talus", "rebel_corporal", 300, 0.3, -12.0, 115.5, -179, 9686149)
		building:spawnChildCreature("talus", "rebel_second_lieutenant", 300, 17.6, -12.0, 97.1, -2, 9686148)
		building:spawnChildCreature("talus", "rebel_trooper", 300, 97.4, -20.0, 115.9, 109, 9686160)
		building:spawnChildCreature("talus", "rebel_trooper", 300, 105.5, -20.0, 110.8, 109, 9686160)
		building:spawnChildCreature("talus", "rebel_trooper", 300, 96.7, -20.0, 105.5, -39, 9686160)
		building:spawnChildCreature("talus", "rebel_trooper", 300, 43.2, -20.0, 156.2, -8, 9686155)
		building:spawnChildCreature("talus", "rebel_trooper", 300, 52.7, -20.0, 156.4, 0, 9686155)
		building:spawnChildCreature("talus", "rebel_trooper", 300, 42.2, -20.0, 139.1, 84, 9686155)
		building:spawnChildCreature("talus", "rebel_trooper", 300, 45.0, -20.0, 139.0, -85, 9686155)
		building:spawnChildCreature("talus", "rebel_colonel", 300, 47.9, -20.0, 144.4, 2, 9686155)
		building:spawnChildCreature("talus", "rebel_medic", 300, 10.1, -12.0, 53.6, -29, 9686144)
		building:spawnChildCreature("talus", "rebel_corporal", 300, 9.7, -12.0, 71.0, 90, 9686144)
		building:spawnChildCreature("talus", "rebel_warrant_officer_i", 300, -3.3, -12.0, 72.1, 73, 9686144)
	end)
end

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
	if (pBuilding == nil) then
		return 1
	end

	BuildingObject(pBuilding):destroyChildObjects()

	if BuildingObject(pBuilding):getFaction() == FACTIONIMPERIAL then
		self:spawnRebels(pBuilding)
	elseif BuildingObject(pBuilding):getFaction() == FACTIONREBEL then
		self:spawnImperials(pBuilding)
	end

	return 0
end

function TalusWeaponsDepotScreenPlay:spawnImperials(pBuilding)
	BuildingObject(pBuilding):initializeStaticGCWBase(FACTIONIMPERIAL)

	BuildingObject(pBuilding):spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", 25.3, -12.0, 29.0, 9686140, .7, 0, .7, 0)

	BuildingObject(pBuilding):spawnChildCreature("talus", "stormtrooper", 300, 15.5, -12.0, 28.3, -92, 9686140)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_major", 300, 57.1, -12.0, 59.1, -97, 9686143)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_staff_sergeant", 300, 55.7, -12.0, 64.7, 12, 9686143)
	BuildingObject(pBuilding):spawnChildCreature("talus", "stormtrooper", 300, 35.0, -12.0, 55.7, -78, 9686143)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_warrant_officer_i", 300, -10.4, -12.0, 105.4, -2, 9686150)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_second_lieutenant", 300, -15.2, -12.0, 96.9, 90, 9686150)
	BuildingObject(pBuilding):spawnChildCreature("talus", "stormtrooper", 300, -4.0, -12.0, 96.6, -68, 9686150)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_corporal", 300, -1.3, -12.0, 117.5, -50, 9686149)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_corporal", 300, 0.6, -12.0, 111.2, 0, 9686149)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_second_lieutenant", 300, 16.4, -12.0, 92.7, 152, 9686148)
	BuildingObject(pBuilding):spawnChildCreature("talus", "stormtrooper", 300, 97.4, -20.0, 135.9, 109, 9686159)
	BuildingObject(pBuilding):spawnChildCreature("talus", "stormtrooper", 300, 105.5, -20.0, 130.8, 109, 9686159)
	BuildingObject(pBuilding):spawnChildCreature("talus", "stormtrooper", 300, 96.7, -20.0, 125.5, -39, 9686159)
	BuildingObject(pBuilding):spawnChildCreature("talus", "stormtrooper", 300, 44.8, -20.0, 151.3, 136, 9686155)
	BuildingObject(pBuilding):spawnChildCreature("talus", "stormtrooper", 300, 49.8, -20.0, 150.0, 139, 9686155)
	BuildingObject(pBuilding):spawnChildCreature("talus", "stormtrooper", 300, 50.1, -20.0, 139.0, 134, 9686155)
	BuildingObject(pBuilding):spawnChildCreature("talus", "stormtrooper", 300, 52.6, -20.0, 139.1, -142, 9686155)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_colonel", 300, 43.9, -20.0, 142.0, -14, 9686155)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_medic", 300, 9.6, -12.0, 62.9, 85, 9686144)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_corporal", 300, -2.4, -12.0, 62.0, -90, 9686144)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_warrant_officer_i", 300, -3.5, -12.0, 73.6, 90, 9686144)
	--2nd floor down
	BuildingObject(pBuilding):spawnChildCreature("talus", "detention_security_guard", 300, 23.9, -20.0, 115.3, -99, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_probe_drone", 300, 19.5, -20.0, 96.0, 175, 9686164)
	BuildingObject(pBuilding):spawnChildCreature("talus", "command_security_guard", 300, 18.4, -20.0, 88.2, -90, 9686164)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_obscureops_agent", 300, 6.8, -20.0, 110.0, -45, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_obscureops_agent", 300, -15.0, -20.0, 115.5, 90, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "r3", 300, 1.2, -20.0, 121.0, 1, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "twilek_slave", 300, 14.5, -20.0, 126.9, 89, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "assault_trooper", 300, 19.2, -20.0, 129.1, 178, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "assault_trooper", 300, 12.6, -20.0, 114.7, 88, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "comm_operator", 300, 18.1, -20.0, 45.2, 170, 9686163)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_stealth_operative", 300, 53.0, -20.0, 59.4, -89, 9686166)
	--3rd floor down
	BuildingObject(pBuilding):spawnChildCreature("talus", "signalman", 300, 39.7, -50.0, 25.2, 88, 9686175)
	BuildingObject(pBuilding):spawnChildCreature("talus", "assault_trooper", 300, 25.3, -50.0, 31.4, -178, 9686175)
	BuildingObject(pBuilding):spawnChildCreature("talus", "special_missions_engineer", 300, 30.5, -50.0, 72.9, -91, 9686177)
	BuildingObject(pBuilding):spawnChildCreature("talus", "droid_corps_junior_technician", 300, -0.5, -50.0, 74.1, -7, 9686178)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_high_general", 300, -133.6, -50.0, 56.2, 88, 9686179)
	BuildingObject(pBuilding):spawnChildCreature("talus", "storm_commando", 300, -136.5, -50.0, 49.6, 89, 9686179)
	BuildingObject(pBuilding):spawnChildCreature("talus", "storm_commando", 300, -136.4, -50.0, 58.8, 89, 9686179)
end

function TalusWeaponsDepotScreenPlay:spawnRebels(pBuilding)
	BuildingObject(pBuilding):initializeStaticGCWBase(FACTIONREBEL)

	BuildingObject(pBuilding):spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", 25.3, -12.0, 29.0, 9686140, .7, 0, .7, 0)

	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_trooper", 300, 13.9, -12.0, 27.5, -68, 9686140)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_major", 300, 55.0, -12.0, 55.9, -7, 9686143)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_staff_sergeant", 300, 54.9, -12.0, 62.5, -179, 9686143)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_trooper", 300, 39.2, -12.0, 60.6, -96, 9686143)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_warrant_officer_i", 300, -12.2, -12.0, 94.6, 0, 9686150)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_second_lieutenant", 300, -15.5, -12.0, 103.8, -40, 9686150)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_trooper", 300, -4.0, -12.0, 101.3, -90, 9686150)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_corporal", 300, 8.5, -12.0, 118.0, 45, 9686149)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_corporal", 300, 0.3, -12.0, 115.5, -179, 9686149)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_second_lieutenant", 300, 17.6, -12.0, 97.1, -2, 9686148)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_trooper", 300, 97.4, -20.0, 115.9, 109, 9686160)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_trooper", 300, 105.5, -20.0, 110.8, 109, 9686160)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_trooper", 300, 96.7, -20.0, 105.5, -39, 9686160)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_trooper", 300, 43.2, -20.0, 156.2, -8, 9686155)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_trooper", 300, 52.7, -20.0, 156.4, 0, 9686155)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_trooper", 300, 42.2, -20.0, 139.1, 84, 9686155)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_trooper", 300, 45.0, -20.0, 139.0, -85, 9686155)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_colonel", 300, 47.9, -20.0, 144.4, 2, 9686155)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_medic", 300, 10.1, -12.0, 53.6, -29, 9686144)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_corporal", 300, 9.7, -12.0, 71.0, 90, 9686144)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_warrant_officer_i", 300, -3.3, -12.0, 72.1, 73, 9686144)
	--2nd floor down
	BuildingObject(pBuilding):spawnChildCreature("talus", "area_coordinator", 300, 23.4, -20.0, 115.0, -95, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "tamed_razor_cat", 300, 19.5, -20.0, 95.5, 175, 9686164)
	BuildingObject(pBuilding):spawnChildCreature("talus", "network_leader", 300, 18.2, -20.0, 88.3, -90, 9686164)
	BuildingObject(pBuilding):spawnChildCreature("talus", "royal_imperial_guard", 300, 7.0, -20.0, 109.5, -45, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "royal_imperial_guard", 300, -14.5, -20.0, 115.1, 90, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "bounty_hunter", 300, 1.4, -20.0, 120.0, -1, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "imperial_stealth_operative", 300, 14.2, -20.0, 126.4, 85, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_commando", 300, 18.8, -20.0, 130.2, 179, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_commando", 300, 12.1, -20.0, 114.9, 85, 9686165)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_network_leader", 300, 18.3, -20.0, 45.3, 177, 9686163)
	BuildingObject(pBuilding):spawnChildCreature("talus", "specops_agent", 300, 55.0, -20.0, 59.0, -89, 9686166)
	--3rd floor down
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_master_sergeant", 300, 39.0, -50.0, 25.1, 89, 9686175)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_commando", 300, 25.5, -50.0, 32.0, -179, 9686175)
	BuildingObject(pBuilding):spawnChildCreature("talus", "specforce_procurement_specialist", 300, 31.5, -50.0, 73.0, -92, 9686177)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_crewman", 300, -1.5, -50.0, 73.5, -6, 9686178)
	BuildingObject(pBuilding):spawnChildCreature("talus", "rebel_high_general", 300, -136.6, -50.0, 54.2, 89, 9686179)
	BuildingObject(pBuilding):spawnChildCreature("talus", "senior_specforce_heavy_weapons_specialist", 300, -139.5, -50.0, 48.6, 89, 9686179)
	BuildingObject(pBuilding):spawnChildCreature("talus", "senior_specforce_heavy_weapons_specialist", 300, -139.4, -50.0, 59.8, 89, 9686179)
end


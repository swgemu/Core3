local ObjectManager = require("managers.object.object_manager")

WeaponFacilityScreenPlay = ScreenPlay:new {
        numberOfActs = 1,

	buildingID = 6335638
}

registerScreenPlay("WeaponFacilityScreenPlay", true)

function WeaponFacilityScreenPlay:start()
	if isZoneEnabled("naboo") then
		local pBuilding = getSceneObject(self.buildingID)
		createObserver(FACTIONBASEFLIPPED, "WeaponFacilityScreenPlay", "flipBase", pBuilding)

		if getRandomNumber(100) >= 50 then
			self:spawnRebels(pBuilding)
		else
			self:spawnImperials(pBuilding)
		end
	end
end

function WeaponFacilityScreenPlay:flipBase(pBuilding)

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

function WeaponFacilityScreenPlay:spawnImperials(pBuilding)

	ObjectManager.withBuildingObject(pBuilding, function(building)
		building:initializeStaticGCWBase(FACTIONIMPERIAL)

		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", 6.7, -12.0, 41.4, 6335643, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", 0.2, -12.0, 41.4, 6335643, 1, 0, 0, 0)

    	--Cell [0]
        	building:spawnChildCreature("dark_trooper", 300, -6502.1, 40.0, -3312.7, -1, 0)
        	building:spawnChildCreature("stormtrooper", 300, -6509.6, 40.0, -3312.9, -1, 0)
        	building:spawnChildCreature("imperial_officer", 300, -6512.7, 40.0, -3302.5, 71, 0)
        	building:spawnChildCreature("stormtrooper", 300, -6496.0, -40.0, -3303.5, -104, 0)
        	building:spawnChildCreature("dark_trooper", 300, -6482.0, 40.0, -3283.3, -133, 0)
        	building:spawnChildCreature("stormtrooper", 300, -6482.3, -40.0, -3288.5, -19, 0)
        	building:spawnChildCreature("dark_trooper", 300, -6486.6, 40.0, -3286.3, 76, 0)
        	building:spawnChildCreature("stormtrooper", 300, -6495.7, 40.0, -3279.5, -165, 0)
        	building:spawnChildCreature("imperial_colonel", 300, -6496.3, 40.0, -3290.1, -3, 0)
        	building:spawnChildCreature("stormtrooper", 300, -6511.0, 40.0, -3281.4, 57, 0)
        	building:spawnChildCreature("imperial_officer", 300, -6511.9, 40.0, -3274.4, 138, 0)
        	building:spawnChildCreature("stormtrooper", 300, -6495.8, 40.0, -3272.4, 25, 0)
        	building:spawnChildCreature("dark_trooper", 300, -6504.4, 40.0, -3262.2, 44, 0)

    	--Cell [6335640]
        	building:spawnChildCreature("stormtrooper", 300, -4.2, 0.3, 3.8, 131, 6335640)
        	building:spawnChildCreature("dark_trooper", 300, 0.5, 0.3, 2.0, -41, 6335640)
        	building:spawnChildCreature("stormtrooper", 300, -4.6, 0.3, -4.7, 39, 6335640)

    	--Cell [6335641]
        	building:spawnChildCreature("stormtrooper", 300, 4.0, 0.3, -4.0, -90, 6335641)

    	--Cell [6335642]
        	building:spawnChildCreature("dark_trooper", 300, 2.7, -12.0, 20.6, -179, 6335642)
        	building:spawnChildCreature("dark_trooper", 300, 4.6, -12.0, 20.8, -171, 6335642)

    	--Cell [6335643]
        	building:spawnChildCreature("stormtrooper", 300, 9.7, -12.0, 31.0, 90, 6335643)
        	building:spawnChildCreature("stormtrooper", 300, 3.3, -12.0, 30.4, 178, 6335643)
        	building:spawnChildCreature("imperial_officer", 300, -2.6, -12.0, 31.0, -91, 6335643)
        	building:spawnChildCreature("imperial_colonel", 300, 1.2, -12.0, 38.8, -177, 6335643)
        	building:spawnChildCreature("stormtrooper", 300, 19.5, -12.0, 40.8, -179, 6335643)
        	building:spawnChildCreature("imperial_officer", 300, 19.5, -12.0, 51.1, 179, 6335643)
        	building:spawnChildCreature("dark_trooper", 300, 25.5, -12.0, 43.6, 0, 6335643)
        	building:spawnChildCreature("imperial_first_lieutenant", 300, 9.6, -12.0, 47.0, -90, 6335643)
        	building:spawnChildCreature("stormtrooper", 300, 27.8, -12.0, 48.3, -105, 6335643)
        	building:spawnChildCreature("dark_trooper", 300, -2.9, -12.0, 63.2, -90, 6335643)
        	building:spawnChildCreature("stormtrooper", 300, 3.6, -12.0, 65.5, 179, 6335643)
        	building:spawnChildCreature("imperial_officer", 300, 5.9, -12.0, 63.1, -91, 6335643)
        	building:spawnChildCreature("stormtrooper", 300, 3.7, -12.0, 60.7, 0, 6335643)
        	building:spawnChildCreature("imperial_second_lieutenant", 300, 10.0, -12.0, 62.9, 90, 6335643)
        	building:spawnChildCreature("dark_trooper", 300, 3.5, -12.0, 68.2, -1, 6335643)
        	building:spawnChildCreature("dark_trooper", 300, -3.1, -12.0, 67.9, 114, 6335643)
        	building:spawnChildCreature("stormtrooper", 300, 3.5, -12.0, 52.4, 179, 6335643)
        	building:spawnChildCreature("imperial_colonel", 300, -12.4, -12.0, 51.4, -177, 6335643)
        	building:spawnChildCreature("dark_trooper", 300, -19.9, -12.0, 39.7, 43, 6335643)
        	building:spawnChildCreature("dark_trooper", 300, -19.8, -12.0, 54.4, 128, 6335643)
        	building:spawnChildCreature("imperial_officer", 300, -12.4, -12.0, 40.8, -178, 6335643)
        	building:spawnChildCreature("stormtrooper", 300, -2.2, -12.0, 47.0, 90, 6335643)
        	building:spawnChildCreature("imperial_first_lieutenant", 300, -13.7, -12.0, 47.1, 90, 6335643)

    	--Cell [6335644]
        	building:spawnChildCreature("dark_trooper", 300, -44.8, -20.0, 45.7, 80, 6335644)
        	building:spawnChildCreature("dark_trooper", 300, -44.8, -20.0, 48.3, 96, 6335644)


    	--Cell [6335645]
        	--WeaponTestingRoom--
        	building:spawnChildCreature("stormtrooper", 300, -50.6, -20.0, 28.0, -45, 6335645)
        	building:spawnChildCreature("dark_trooper", 300, -54.5, -20.0, 28.6, 57, 6335645)
        	building:spawnChildCreature("dark_trooper", 300, -52.7, -20.0, 32.7, 152, 6335645)
        	building:spawnChildCreature("imperial_first_lieutenant", 300, -59.4, -20.0, 32.6, -8, 6335645)
        	building:spawnChildCreature("dark_trooper", 300, -56.3, -20.0, 38.2, -92, 6335645)
        	building:spawnChildCreature("stormtrooper", 300, -58.3, -20.0, 42.5, -164, 6335645)
        	building:spawnChildCreature("dark_trooper", 300, -76.5, -20.0, 47.0, 89, 6335645)
        	building:spawnChildCreature("imperial_officer", 300, -71.3, -20.0, 52.0, 47, 6335645)
        	building:spawnChildCreature("stormtrooper", 300, -66.6, -20.0, 53.7, -66, 6335645)
        	building:spawnChildCreature("stormtrooper", 300, -68.5, -20.0, 57.7, -162, 6335645)
        	building:spawnChildCreature("dark_trooper", 300, -58.9, -20.0, 66.3, -2, 6335645)
        	building:spawnChildCreature("imperial_officer", 300, -62.0, -20.0, 66.6, 1, 6335645)
        	building:spawnChildCreature("dark_trooper", 300, -74.7, -20.0, 64.7, -41, 6335645)
        	building:spawnChildCreature("stormtrooper", 300, -72.6, -20.0, 66.7, -79, 6335645)
        	building:spawnChildCreature("imperial_officer", 300, -55.4, -20.0, 62.2, -75, 6335645)
        	building:spawnChildCreature("imperial_colonel", 300, -67.9, -20.0, 23.6, -179, 6335645)
        	building:spawnChildCreature("dark_trooper", 300, -74.3, -20.0, 26.1, 61, 6335645)
        	building:spawnChildCreature("dark_trooper", 300, -75.7, -20.0, 29.5, 61, 6335645)

    	--Cell [6335646]
        	building:spawnChildCreature("imperial_inquisitor", 600, -46.7, -20.0, 12.9, -84, 6335646)
        	building:spawnChildCreature("imperial_second_lieutenant", 300, -68.2, -20.0, 18.0, 178, 6335646)
        	building:spawnChildCreature("stormtrooper", 300, -68.2, -20.0, 11.5, -176, 6335646)
        	building:spawnChildCreature("dark_trooper", 300, -74.5, -20.0, 7.2, -149, 6335646)
        	building:spawnChildCreature("imperial_officer", 300, -76.0, -20.0, 17.8, -44, 6335646)
        	building:spawnChildCreature("dark_trooper", 300, -63.6, -20.0, 13.0, 89, 6335646)
        	building:spawnChildCreature("imperial_colonel", 300, -60.2, -20.0, 18.6, 1, 6335646)
        	building:spawnChildCreature("dark_trooper", 300, -62.1, -20.0, 6.9, 177, 6335646)
        	building:spawnChildCreature("imperial_officer", 300, -54.5, -20.0, 9.6, -89, 6335646)
        	building:spawnChildCreature("stormtrooper", 300, -49.4, -20.0, 7.7, 131, 6335646)

    	--Cell [6335647]
        	building:spawnChildCreature("dark_trooper", 300, -47.9, -20.0, 81.0, -89, 6335647)
        	building:spawnChildCreature("imperial_first_lieutenant", 300, -50.5, -20.0, 78.4, -118, 6335647)
        	building:spawnChildCreature("imperial_colonel", 300, -51.6, -20.0, 86.4, -83, 6335647)
        	building:spawnChildCreature("imperial_officer", 300, -77.1, -20.0, 78.3, -89, 6335647)
        	building:spawnChildCreature("dark_trooper", 300, -75.5, -20.0, 86.0, 137, 6335647)
        	building:spawnChildCreature("dark_trooper", 300, -73.4, -20.0, 73.7, -179, 6335647)
        	building:spawnChildCreature("imperial_officer", 300, -70.4, -20.0, 88.3, -2, 6335647)
        	building:spawnChildCreature("dark_trooper", 300, -71.4, -20.0, 82.1, -97, 6335647)
        	building:spawnChildCreature("dark_trooper", 300, -71.7, -20.0, 79.3, -75, 6335647)
        	building:spawnChildCreature("stormtrooper", 300, -54.5, -20.0, 88.1, 0, 6335647)

    	--Cell [6335652]
        	building:spawnChildCreature("dark_trooper", 300, 37.5, -12.0, 11.1, -91, 6335652)
        	building:spawnChildCreature("dark_trooper", 300, 26.2, -12.0, 26.0, 0, 6335652)
        	building:spawnChildCreature("dark_trooper", 300, 16.1, -12.0, -0.0, -88, 6335652)
        	building:spawnChildCreature("stormtrooper", 300, 22.1, -12.0, 4.2, 171, 6335652)
        	building:spawnChildCreature("imperial_warrant_officer_ii", 300, 25.5, -12.0, 0.3, -41, 6335652)
        	building:spawnChildCreature("dark_trooper", 300, 20.6, -12.0, 0.2, 39, 6335652)
        	building:spawnChildCreature("stormtrooper_major", 300, 61.7, -12.0, 1.8, -86, 6335652)
        	building:spawnChildCreature("dark_trooper", 300, 61.6, -12.0, -0.5, -83, 6335652)
        	building:spawnChildCreature("dark_trooper", 300, 37.8, -12.0, -3.6, 0, 6335652)
        	building:spawnChildCreature("dark_trooper", 300, 37.9, -12.0, 1.5, -179, 6335652)
        	building:spawnChildCreature("stormtrooper", 300, 51.2, -12.0, 12.8, -145, 6335652)
        	building:spawnChildCreature("imperial_officer", 300, 49.8, -12.0, 9.7, 19, 6335652)
        	building:spawnChildCreature("stormtrooper", 300, 41.3, -12.0, 22.8, 112, 6335652)
        	building:spawnChildCreature("dark_trooper", 300, 45.0, -12.0, 19.5, -15, 6335652)

    	--Cell [6335654]
        	building:spawnChildCreature("dark_trooper", 300, -22.5, -20.0, -1.8, 5, 6335654)
        	building:spawnChildCreature("imperial_second_lieutenant", 300, -20.4, -20.0, -1.8, 0, 6335654)
        	building:spawnChildCreature("imperial_colonel", 300, -12.6, -20.0, -1.6, 0, 6335654)
        	building:spawnChildCreature("dark_trooper", 300, -10.7, -20.0, -1.5, 0, 6335654)
        	building:spawnChildCreature("imperial_warrant_officer_i", 300, -10.7, -20.0, 7.6, -179, 6335654)
        	building:spawnChildCreature("dark_trooper", 300, -12.9, -20.0, 7.6, 178, 6335654)
        	building:spawnChildCreature("imperial_officer", 300, -20.3, -20.0, 7.4, 179, 6335654)
        	building:spawnChildCreature("stormtrooper", 300, -22.4, -20.0, 7.5, 177, 6335654)
        	building:spawnChildCreature("dark_trooper", 300, -23.5, -20.0, 1.0, 81, 6335654)
        	building:spawnChildCreature("dark_trooper", 300, -23.7, -20.0, 5.1, 118, 6335654)

    	--Cell [6335657]
        	building:spawnChildCreature("dark_trooper", 300, -29.2, -20.0, 99.2, -173, 6335657)
        	building:spawnChildCreature("dark_trooper", 300, -32.3, -20.0, 99.0, 167, 6335657)
        	building:spawnChildCreature("dark_trooper", 300, -37.8, -20.0, 101.2, -87, 6335657)
        	building:spawnChildCreature("imperial_officer", 300, -32.5, -20.0, 104.5, 1, 6335657)
        	building:spawnChildCreature("dark_trooper", 300, -26.8, -20.0, 114.9, -155, 6335657)
        	building:spawnChildCreature("dark_trooper", 300, -22.4, -20.0, 104.5, -2, 6335657)
        	building:spawnChildCreature("imperial_first_lieutenant", 300, -7.2, -20.0, 100.8, 88, 6335657)
        	building:spawnChildCreature("dark_trooper", 300, -12.5, -20.0, 104.7, 0, 6335657)
        	building:spawnChildCreature("imperial_warrant_officer_ii", 300, -17.5, -20.0, 116.6, -176, 6335657)
        	building:spawnChildCreature("imperial_officer", 300, -36.4, -20.0, 117.9, -177, 6335657)
        	building:spawnChildCreature("dark_trooper", 300, -36.6, -20.0, 112.4, -4, 6335657)
        	building:spawnChildCreature("imperial_officer", 300, -8.9, -20.0, 95.1, -54, 6335657)
        	building:spawnChildCreature("stormtrooper", 300, -13.2, -20.0, 101.1, 138, 6335657)
        	building:spawnChildCreature("stormtrooper", 300, -13.2, -20.0, 96.5, 48, 6335657)

    	--Cell [6335659]
        	building:spawnChildCreature("imperial_warrant_officer_i", 300, -7.4, -20.0, 67.0, 19, 6335659)
        	building:spawnChildCreature("dark_trooper", 300, -7.0, -20.0, 76.0, 124, 6335659)
        	building:spawnChildCreature("imperial_colonel", 300, 2.3, -20.0, 74.5, -136, 6335659)
        	building:spawnChildCreature("dark_trooper", 300, 2.2, -20.0, 67.2, -56, 6335659)

    	--Cell [6335650]
        	building:spawnChildCreature("dark_trooper", 300, 73.7, -12.0, 58.6, 89, 6335650)
        	building:spawnChildCreature("dark_trooper", 300, 64.1, -12.0, 57.4, 2, 6335650)
        	building:spawnChildCreature("dark_trooper", 300, 63.8, -12.0, 60.4, -178, 6335650)
        	building:spawnChildCreature("imperial_colonel", 300, 53.0, -12.0, 60.0, -3, 6335650)
        	building:spawnChildCreature("dark_trooper", 300, 47.0, -12.0, 57.7, -168, 6335650)
        	building:spawnChildCreature("imperial_second_lieutenant", 300, 44.8, -12.0, 65.1, -176, 6335650)

    	--Cell [6335649]
        	building:spawnChildCreature("dark_trooper", 300, 45.0, -12.0, 77.3, -1, 6335649)
        	building:spawnChildCreature("imperial_officer", 300, 45.0, -12.0, 89.6, -179, 6335649)
        	building:spawnChildCreature("imperial_warrant_officer_i", 300, 61.0, -12.0, 82.1, -179, 6335649)
        	building:spawnChildCreature("imperial_first_lieutenant", 300, 65.5, -12.0, 84.6, 6, 6335649)
        	building:spawnChildCreature("dark_trooper", 300, 73.6, -12.0, 83.0, 89, 6335649)
        	building:spawnChildCreature("dark_trooper", 300, 71.2, -12.0, 81.4, 179, 6335649)

    	--Cell [6335651]
        	building:spawnChildCreature("stormtrooper", 300, 19.5, -20.0, 115.7, 179, 6335651)
        	building:spawnChildCreature("imperial_officer", 300, 12.4, -20.0, 122.9, -90, 6335651)
        	building:spawnChildCreature("imperial_first_lieutenant", 300, 12.2, -20.0, 138.9, -91, 6335651)
        	building:spawnChildCreature("imperial_colonel", 300, 36.9, -20.0, 124.2, 0, 6335651)
        	building:spawnChildCreature("imperial_officer", 300, 37.1, -20.0, 128.5, 179, 6335651)
        	building:spawnChildCreature("dark_trooper", 300, 33.5, -20.0, 139.7, 89, 6335651)
        	building:spawnChildCreature("imperial_warrant_officer_ii", 300, 39.1, -20.0, 139.4, -89, 6335651)
        	building:spawnChildCreature("dark_trooper", 300, 20.8, -20.0, 131.3, 88, 6335651)
        	building:spawnChildCreature("dark_trooper", 300, 17.6, -20.0, 125.0, 90, 6335651)
        	building:spawnChildCreature("stormtrooper", 300, 23.5, -20.0, 125.1, -89, 6335651)
	end)
end

function WeaponFacilityScreenPlay:spawnRebels(pBuilding)

	ObjectManager.withBuildingObject(pBuilding, function(building)
		building:initializeStaticGCWBase(FACTIONREBEL)

		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", 6.7, -12.0, 41.4, 6335643, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", 0.2, -12.0, 41.4, 6335643, 1, 0, 0, 0)

    	--Cell [0]
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -6496.0, 40.0, -3324.7, -133, 0)
        	building:spawnChildCreature("specforce_marine", 300, -6515.3, 40.0, -3325.9, 131, 0)
        	building:spawnChildCreature("rebel_trooper", 300, -6516.8, 40.0, -3313.5, -101, 0)
        	building:spawnChildCreature("specforce_marine", 300, -6494.9, -40.0, -3313.6, 98, 0)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -6482.7, 40.0, -3279.1, -61, 0)
        	building:spawnChildCreature("specforce_marine", 300, -6483.2, -40.0, -3291.2, -128, 0)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -6489.1, 40.0, -3284.2, -4, 0)
        	building:spawnChildCreature("specforce_marine", 300, -6500.1, 40.0, -3283.7, -91, 0)
        	building:spawnChildCreature("rebel_colonel", 300, -6493.1, 40.0, -3289.4, 156, 0)
        	building:spawnChildCreature("specforce_marine", 300, -6511.9, 40.0, -3279.4, -87, 0)
        	building:spawnChildCreature("rebel_major", 300, -6511.8, 40.0, -3277.2, -95, 0)
        	building:spawnChildCreature("specforce_marine", 300, -6494.0, 40.0, -3271.8, 49, 0)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -6502.8, 40.0, -3260.9, -20, 0)

    	--Cell [6335640]
        	building:spawnChildCreature("specforce_marine", 300, -4.1, 0.3, 0.7, 169, 6335640)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -2.0, 0.3, 2.5, 172, 6335640)
        	building:spawnChildCreature("specforce_marine", 300, -3.3, 0.3, -5.0, 0, 6335640)

    	--Cell [6335641]
        	building:spawnChildCreature("specforce_marine", 300, 3.9, 0.3, -3.2, 88, 6335641)

    	--Cell [6335642]
        	building:spawnChildCreature("specforce_marine", 300, 2.6, 0.0, 1.0, -94, 6335642)
        	building:spawnChildCreature("specforce_marine", 300, 4.2, -12.0, 21.9, 82, 6335642)

    	--Cell [6335643]
        	building:spawnChildCreature("specforce_marine", 300, 10.7, -12.0, 29.1, 0, 6335643)
        	building:spawnChildCreature("specforce_marine", 300, 4.5, -12.0, 30.7, -157, 6335643)
        	building:spawnChildCreature("senior_specforce_lieutenant", 300, -3.4, -12.0, 32.8, -164, 6335643)
        	building:spawnChildCreature("rebel_colonel", 300, 3.1, -12.0, 40.1, -39, 6335643)
        	building:spawnChildCreature("specforce_marine", 300, 18.1, -12.0, 40.3, -109, 6335643)
        	building:spawnChildCreature("rebel_medic", 300, 19.5, -12.0, 49.4, 0, 6335643)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 26.5, -12.0, 43.2, -38, 6335643)
        	building:spawnChildCreature("rebel_first_lieutenant", 300, 11.5, -12.0, 49.1, -30, 6335643)
        	building:spawnChildCreature("specforce_marine", 300, 26.6, -12.0, 49.5, 89, 6335643)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -2.6, -12.0, 62.2, -83, 6335643)
        	building:spawnChildCreature("specforce_marine", 300, 5.1, -12.0, 64.6, -145, 6335643)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 1.4, -12.0, 63.0, 85, 6335643)
        	building:spawnChildCreature("specforce_marine", 300, 5.3, -12.0, 61.4, -49, 6335643)
        	building:spawnChildCreature("rebel_second_lieutenant", 300, 9.6, -12.0, 63.8, 103, 6335643)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 6.1, -12.0, 67.3, 3, 6335643)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -1.7, -12.0, 68.8, -35, 6335643)
        	building:spawnChildCreature("specforce_marine", 300, 0.2, -12.0, 53.3, -179, 6335643)
        	building:spawnChildCreature("rebel_colonel", 300, -10.9, -12.0, 50.2, -52, 6335643)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -19.2, -12.0, 43.7, 6, 6335643)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -19.4, -12.0, 49.6, -98, 6335643)
        	building:spawnChildCreature("rebel_medic", 300, -13.1, -12.0, 40.9, 159, 6335643)
        	building:spawnChildCreature("specforce_marine", 300, -1.3, -12.0, 48.2, 170, 6335643)
        	building:spawnChildCreature("rebel_first_lieutenant", 300, -9.8, -12.0, 47.0, -97, 6335643)

    	--Cell [6335644]
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -42.7, -20.0, 46.0, -174, 6335644)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -43.2, -20.0, 47.9, -9, 6335644)


    	--Cell [6335645]
        	--WeaponTestingRoom--
        	building:spawnChildCreature("specforce_marine", 300, -50.4, -20.0, 26.4, 145, 6335645)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -55.0, -20.0, 27.2, -166, 6335645)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -50.1, -20.0, 32.7, 98, 6335645)
        	building:spawnChildCreature("rebel_first_lieutenant", 300, -61.8, -20.0, 34.4, 20, 6335645)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -57.0, -20.0, 36.6, -92, 6335645)
        	building:spawnChildCreature("specforce_marine", 300, -61.6, -20.0, 41.9, 149, 6335645)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -77.5, -20.0, 48.0, -93, 6335645)
        	building:spawnChildCreature("rebel_major", 300, -73.8, -20.0, 51.9, -61, 6335645)
        	building:spawnChildCreature("specforce_marine", 300, -61.6, -20.0, 54.8, 83, 6335645)
        	building:spawnChildCreature("specforce_marine", 300, -69.5, -20.0, 56.4, -127, 6335645)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -60.3, -20.0, 65.9, -14, 6335645)
        	building:spawnChildCreature("rebel_master_sergeant", 300, -67.9, -20.0, 69.9, 4, 6335645)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -74.0, -20.0, 65.3, 10, 6335645)
        	building:spawnChildCreature("specforce_marine", 300, -72.8, -20.0, 68.4, -98, 6335645)
        	building:spawnChildCreature("rebel_major_general", 300, -51.2, -20.0, 60.5, 102, 6335645)
        	building:spawnChildCreature("rebel_colonel", 300, -63.6, -20.0, 26.3, 139, 6335645)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -74.8, -20.0, 27.8, -113, 6335645)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -73.0, -20.0, 36.9, -41, 6335645)

    	--Cell [6335646]
        	building:spawnChildCreature("rebel_army_captain", 300, -48.7, -20.0, 14.5, -68, 6335646)
        	building:spawnChildCreature("rebel_second_lieutenant", 300, -70.0, -20.0, 16.4, 93, 6335646)
        	building:spawnChildCreature("specforce_marine", 300, -70.0, -20.0, 9.8, 86, 6335646)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -76.2, -20.0, 8.8, -119, 6335646)
        	building:spawnChildCreature("rebel_medic", 300, -74.7, -20.0, 13.0, 88, 6335646)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -61.1, -20.0, 13.0, -90, 6335646)
        	building:spawnChildCreature("rebel_colonel", 300, -62.9, -20.0, 19.1, 1, 6335646)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -59.1, -20.0, 6.9, 172, 6335646)
        	building:spawnChildCreature("rebel_trooper", 300, -56.3, -20.0, 11.8, 165, 6335646)
        	building:spawnChildCreature("specforce_marine", 300, -49.3, -20.0, 18.2, 44, 6335646)

    	--Cell [6335647]
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -48.7, -20.0, 75.0, -50, 6335647)
        	building:spawnChildCreature("rebel_first_lieutenant", 300, -50.5, -20.0, 82.0, -119, 6335647)
        	building:spawnChildCreature("rebel_colonel", 300, -49.1, -20.0, 86.5, 22, 6335647)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -77.4, -20.0, 79.5, -149, 6335647)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -76.7, -20.0, 87.1, -79, 6335647)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -77.8, -20.0, 73.6, 33, 6335647)
        	building:spawnChildCreature("rebel_corporal", 300, -72.8, -20.0, 87.5, -29, 6335647)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -77.5, -20.0, 82.9, -34, 6335647)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -70.9, -20.0, 80.0, 75, 6335647)
        	building:spawnChildCreature("specforce_marine", 300, -55.7, -20.0, 86.4, -148, 6335647)

    	--Cell [6335652]
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 40.3, -12.0, 9.4, -176, 6335652)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 22.2, -12.0, 24.9, 13, 6335652)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 18.0, -12.0, 3.5, -98, 6335652)
        	building:spawnChildCreature("specforce_marine", 300, 23.3, -12.0, 11.8, 43, 6335652)
        	building:spawnChildCreature("rebel_warrant_officer_ii", 300, 28.2, -12.0, 2.6, 64, 6335652)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 21.4, -12.0, -4.3, 9, 6335652)
        	building:spawnChildCreature("rebel_major", 300, 58.6, -12.0, 2.4, -14, 6335652)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 54.0, -12.0, -0.9, 174, 6335652)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 44.1, -12.0, -0.9, 170, 6335652)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 37.9, -12.0, 4.3, -14, 6335652)
        	building:spawnChildCreature("specforce_marine", 300, 61.8, -12.0, 12.5, 10, 6335652)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 48.3, -12.0, 12.4, -8, 6335652)
        	building:spawnChildCreature("specforce_marine", 300, 42.2, -12.0, 20.0, -169, 6335652)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 52.1, -12.0, 22.8, 4, 6335652)

    	--Cell [6335654]
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -22.7, -20.0, -3.0, 169, 6335654)
        	building:spawnChildCreature("rebel_second_lieutenant", 300, -21.3, -20.0, -1.7, -2, 6335654)
        	building:spawnChildCreature("rebel_colonel", 300, -13.0, -20.0, -2.9, 172, 6335654)
        	building:spawnChildCreature("rebel_trooper", 300, -10.0, -20.0, -2.7, 89, 6335654)
        	building:spawnChildCreature("rebel_warrant_officer_i", 300, -9.9, -20.0, 8.5, -110, 6335654)
        	building:spawnChildCreature("rebel_trooper", 300, -13.9, -20.0, 7.8, 171, 6335654)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -19.7, -20.0, 9.1, 2, 6335654)
        	building:spawnChildCreature("specforce_marine", 300, -23.2, -20.0, 8.9, -98, 6335654)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -19.6, -20.0, -3.3, 176, 6335654)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -15.7, -20.0, 2.6, -79, 6335654)

    	--Cell [6335657]
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -29.0, -20.0, 95.9, 78, 6335657)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -36.2, -20.0, 96.5, -102, 6335657)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -37.1, -20.0, 99.9, -68, 6335657)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -25.3, -20.0, 119.5, 62, 6335657)
        	building:spawnChildCreature("rebel_trooper", 300, -27.4, -20.0, 106.7, -1, 6335657)
        	building:spawnChildCreature("rebel_trooper", 300, -23.3, -20.0, 100.2, -170, 6335657)
        	building:spawnChildCreature("rebel_first_lieutenant", 300, -7.8, -20.0, 99.8, 76, 6335657)
        	building:spawnChildCreature("rebel_trooper", 300, -13.9, -20.0, 105.4, 66, 6335657)
        	building:spawnChildCreature("rebel_warrant_officer_ii", 300, -19.1, -20.0, 113.8, -179, 6335657)
        	building:spawnChildCreature("rebel_army_captain", 300, -35.9, -20.0, 120.7, 82, 6335657)
        	building:spawnChildCreature("rebel_trooper", 300, -35.9, -20.0, 105.5, -87, 6335657)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -9.1, -20.0, 96.4, 91, 6335657)
        	building:spawnChildCreature("specforce_marine", 300, -15.9, -20.0, 102.2, -65, 6335657)
        	building:spawnChildCreature("specforce_marine", 300, -16.4, -20.0, 95.2, -66, 6335657)

    	--Cell [6335659]
        	building:spawnChildCreature("rebel_warrant_officer_i", 300, -3.7, -20.0, 64.8, 163, 6335659)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, -4.0, -20.0, 72.8, -158, 6335659)
        	building:spawnChildCreature("rebel_colonel", 300, 1.1, -20.0, 76.4, 31, 6335659)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 3.4, -20.0, 64.8, 166, 6335659)

    	--Cell [6335650]
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 69.4, -12.0, 59.7, -15, 6335650)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 69.0, -12.0, 57.9, 174, 6335650)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 60.7, -12.0, 59.6, 32, 6335650)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 53.1, -12.0, 57.7, -170, 6335650)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 46.8, -12.0, 59.7, -5, 6335650)
        	building:spawnChildCreature("rebel_second_lieutenant", 300, 44.6, -12.0, 53.1, 1, 6335650)

    	--Cell [6335649]
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 50.1, -12.0, 84.7, -9, 6335649)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 50.9, -12.0, 81.2, 178, 6335649)
        	building:spawnChildCreature("rebel_warrant_officer_i", 300, 57.7, -12.0, 81.2, 175, 6335649)
        	building:spawnChildCreature("rebel_first_lieutenant", 300, 67.3, -12.0, 84.7, -17, 6335649)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 73.7, -12.0, 81.2, -176, 6335649)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 71.6, -12.0, 84.7, 8, 6335649)

    	--Cell [6335651]
        	building:spawnChildCreature("specforce_marine", 300, 21.9, -20.0, 120.0, -30, 6335651)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 13.5, -20.0, 127.3, 56, 6335651)
        	building:spawnChildCreature("rebel_first_lieutenant", 300, 18.3, -20.0, 145.9, 42, 6335651)
        	building:spawnChildCreature("rebel_colonel", 300, 38.7, -20.0, 121.8, 92, 6335651)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 38.2, -20.0, 127.6, 122, 6335651)
        	building:spawnChildCreature("rebel_trooper", 300, 41.7, -20.0, 133.4, 73, 6335651)
        	building:spawnChildCreature("rebel_warrant_officer_ii", 300, 36.4, -20.0, 145.9, -10, 6335651)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 32.8, -20.0, 125.4, 38, 6335651)
        	building:spawnChildCreature("senior_specforce_infiltrator", 300, 26.7, -20.0, 131.9, -40, 6335651)
        	building:spawnChildCreature("specforce_marine", 300, 19.6, -20.0, 136.9, 156, 6335651)
	end)
end

local ObjectManager = require("managers.object.object_manager")

HyperdriveResearchFacilityScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "HyperdriveResearchFacilityScreenPlay",

	buildingID =  479815
}

registerScreenPlay("HyperdriveResearchFacilityScreenPlay", true)

function HyperdriveResearchFacilityScreenPlay:start()
	if isZoneEnabled("rori") then
		local pBuilding = getSceneObject(self.buildingID)
		createObserver(FACTIONBASEFLIPPED, "HyperdriveResearchFacilityScreenPlay", "flipBase", pBuilding)

		if getRandomNumber(100) >= 50 then
			self:spawnRebels(pBuilding)
		else
			self:spawnImperials(pBuilding)
		end
	end
end

function HyperdriveResearchFacilityScreenPlay:flipBase(pBuilding)

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

function HyperdriveResearchFacilityScreenPlay:spawnImperials(pBuilding)

	ObjectManager.withBuildingObject(pBuilding, function(building)
		building:initializeStaticGCWBase(FACTIONIMPERIAL)

		--imperial decorations
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", -1130.5, 77.2, 4532.2, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", -1137.0, 77.2, 4532.2, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", -1153.8, 77.2, 4510.9, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", -1117.3, 77.2, 4510.9, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", -1133.9, 77.2, 4511.4, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", -1145.8, 89.0, 4552.4, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", -1136.4, 78.1, 4584.3, 0, 1, 0, 0, 0)

		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", 6.7, -12.0, 41.4, 479820, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_imperial.iff", 0.2, -12.0, 41.4, 479820, 1, 0, 0, 0)

		building:spawnChildSceneObject("object/tangible/furniture/imperial/warren_warning_sign.iff", 35.5, -20.0, 112.6, 479828, 1, 0, 0, 0)

		--imperials outside
		building:spawnChildCreature("imperial_trooper", 300, -1100, 76.0, 4520, 0, 0)
		building:spawnChildCreature("imperial_trooper", 300, -1100, 76.0, 4524, 0, 0)
		building:spawnChildCreature("imperial_trooper", 300, -1100, 76.0, 4528, 0, 0)
		building:spawnChildCreature("imperial_trooper", 300, -1130.5, 77.2, 4511.5, 180, 0)
		building:spawnChildCreature("imperial_trooper", 300, -1136.9, 77.2, 4511.5, 180, 0)

		building:spawnChildCreature("at_st", 300, getRandomNumber(12) + -1142.5, 77.7, getRandomNumber(12) + 4586.5, getRandomNumber(180) + -90, 0)

		building:spawnChildCreature("stormtrooper", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("stormtrooper", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("stormtrooper", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("stormtrooper", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("stormtrooper_commando", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("stormtrooper_commando", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("stormtrooper_commando", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)

		building:spawnChildCreature("imperial_trooper", 300, -1185, 75.9, 4510, 45, 0)
		building:spawnChildCreature("imperial_trooper", 300, -1182, 75.9, 4513, 45, 0)
		building:spawnChildCreature("imperial_trooper", 300, -1179, 75.9, 4516, 45, 0)
		building:spawnChildCreature("imperial_trooper", 300, -1176, 75.9, 4519, 45, 0)

		--imperials inside
		building:spawnChildCreature("imperial_trooper", 300, 0.0, 0.3, 8.9, 0,  479816)
		building:spawnChildCreature("imperial_trooper", 300, 0.0, 0.3, 6.4, 0,  479816)

		building:spawnChildCreature("imperial_major", 300, -3.2, 0.3, -1.1, -90,  479817)

		building:spawnChildCreature("dark_trooper", 300, 3.7, 0.3, -4.3, -90,  479818)

		building:spawnChildCreature("imperial_trooper", 300, 2.2, -12.0, 21.2, 90,  479819)
		building:spawnChildCreature("imperial_trooper", 300, 4.8, -12.0, 21.2, -90,  479819)

		building:spawnChildCreature("imperial_colonel", 300, 2.4, -12.0, 40.3, 0,  479820)
		building:spawnChildCreature("imperial_private", 300, 4.4, -12.0, 40.3, 0,  479820)
		building:spawnChildCreature("stormtrooper", 300, -2.4, -12.0, 37.1, 90,  479820)
		building:spawnChildCreature("stormtrooper", 300, -2.4, -12.0, 34.1, 90,  479820)
		building:spawnChildCreature("stormtrooper", 300, -2.4, -12.0, 31.1, 90,  479820)
		building:spawnChildCreature("stormtrooper", 300, -2.4, -12.0, 28.1, 90,  479820)
		building:spawnChildCreature("stormtrooper", 300, 10.2, -12.0, 33.1, -90,  479820)
		building:spawnChildCreature("stormtrooper", 300, 10.2, -12.0, 36.1, -90,  479820)
		building:spawnChildCreature("stormtrooper_sniper", 300, 25.8, -12.0, 50.7, -155,  479820)
		building:spawnChildCreature("stormtrooper_sniper", 300, 22.3, -12.0, 40.7, -55,  479820)
		building:spawnChildCreature("stormtrooper_sniper", 300, 14.8, -12.0, 44.3, 55,  479820)
		building:spawnChildCreature("stormtrooper_sniper", 300, 14.3, -12.0, 52.8, 180,  479820)
		building:spawnChildCreature("imperial_major", 300, 10.1, -12.0, 47.2, -90,  479820)
		building:spawnChildCreature("imperial_warrant_officer_ii", 300, -1.5, -12.0, 62.7, 90,  479820)
		building:spawnChildCreature("imperial_warrant_officer_ii", 300, 1.9, -12.0, 61.2, 35,  479820)
		building:spawnChildCreature("imperial_warrant_officer_ii", 300, 3.6, -12.0, 53.6, 180,  479820)
		building:spawnChildCreature("dark_trooper", 300, -18.4, -12.0, 53.6, 180,  479820)
		building:spawnChildCreature("dark_trooper", 300, -15.4, -12.0, 53.6, 180,  479820)
		building:spawnChildCreature("dark_trooper", 300, -12.4, -12.0, 53.6, 180,  479820)
		building:spawnChildCreature("dark_trooper", 300, -9.4, -12.0, 53.6, 180,  479820)
		building:spawnChildCreature("imperial_sergeant", 300, -17.5, -12.0, 43.2, 40,  479820)

		building:spawnChildCreature("imperial_trooper", 300, -41.8, -20.0, 48.3, 180, 479821)
		building:spawnChildCreature("imperial_trooper", 300, -41.8, -20.0, 45.7, 0, 479821)

		building:spawnChildCreature("imperial_major", 300, -49.0, -20.0, 28.0, 90, 479822)
		building:spawnChildCreature("imperial_second_lieutenant", 300, -67.9, -20.0, 24.4, 175, 479822)
		building:spawnChildCreature("imperial_second_lieutenant", 300, -67.2, -20.0, 69.9, -24, 479822)

		building:spawnChildCreature("imperial_lance_corporal", 300, -50.5, -20.0, 18.7, 24, 479823)
		building:spawnChildCreature("imperial_lance_corporal", 300, -49.0, -20.0, 17.5, 64, 479823)
		building:spawnChildCreature("imperial_lance_corporal", 300, -48.7, -20.0, 9.2, 120, 479823)
		building:spawnChildCreature("imperial_lance_corporal", 300, -50.5, -20.0, 7.2, 160, 479823)
		building:spawnChildCreature("imperial_major", 300, -60.7, -20.0, 11.7, -90, 479823)
		building:spawnChildCreature("imperial_inquisitor", 900, -60.7, -20.0, 14.0, -90, 479823)
		building:spawnChildCreature("imperial_surface_marshall", 300, -59.1, -20.0, 6.9, 180, 479823)
		building:spawnChildCreature("imperial_second_lieutenant", 300, -62.6, -20.0, 6.9, 180, 479823)
		building:spawnChildCreature("imperial_surface_marshall", 300, -66.1, -20.0, 6.9, 180, 479823)
		building:spawnChildCreature("imperial_master_sergeant", 300, -74.6, -20.0, 7.3, -145, 479823)
		building:spawnChildCreature("imperial_master_sergeant", 300, -76.2, -20.0, 8.8, -125, 479823)
		building:spawnChildCreature("stormtrooper_bombardier", 300, -78.2, -20.0, 12.0, 90, 479823)
		building:spawnChildCreature("stormtrooper_bombardier", 300, -78.2, -20.0, 14.4, 90, 479823)
		building:spawnChildCreature("imperial_private", 300, -75.6, -20.0, 17.9, -45, 479823)
		building:spawnChildCreature("imperial_surface_marshall", 300, -59.1, -20.0, 19.0, 0, 479823)
		building:spawnChildCreature("imperial_second_lieutenant", 300, -62.6, -20.0, 19.0, 0, 479823)
		building:spawnChildCreature("imperial_surface_marshall", 300, -66.1, -20.0, 19.0, 0, 479823)

		building:spawnChildCreature("imperial_medic", 300, -77.1, -20.0, 74.4, 45, 479824)
		building:spawnChildCreature("imperial_medic", 300, -53.8, -20.0, 86.4, 90, 479824)
		building:spawnChildCreature("imperial_medic", 300, -50.2, -20.0, 79.8, 135, 479824)
		building:spawnChildCreature("imperial_medic", 300, -69.2, -20.0, 77.3, -90, 479824)

		building:spawnChildCreature("stormtrooper_medic", 300, 36.5, -12.0, 52.2, 0, 479825)
		building:spawnChildCreature("stormtrooper_captain", 300, 34.9, -12.0, 52.2, 0, 479825)
		building:spawnChildCreature("stormtrooper_rifleman", 300, 36.5, -12.0, 57.2, 0, 479825)
		building:spawnChildCreature("stormtrooper_rifleman", 300, 34.9, -12.0, 57.2, 0, 479825)
		building:spawnChildCreature("stormtrooper_squad_leader", 300, 36.5, -12.0, 62.2, 0, 479825)
		building:spawnChildCreature("stormtrooper_medic", 300, 34.9, -12.0, 62.2, 0, 479825)

		building:spawnChildCreature("droid_corps_junior_technician", 300, 49.3, -12.0, 87.8, 180, 479826)
		building:spawnChildCreature("droid_corps_junior_technician", 300, 56.7, -12.0, 87.8, 180, 479826)
		building:spawnChildCreature("droid_corps_junior_technician", 300, 63.3, -12.0, 87.8, 180, 479826)
		building:spawnChildCreature("droid_corps_junior_technician", 300, 70.0, -12.0, 87.8, 180, 479826)
		building:spawnChildCreature("droid_corps_junior_technician", 300, 49.3, -12.0, 78.4, 0, 479826)
		building:spawnChildCreature("droid_corps_junior_technician", 300, 56.7, -12.0, 78.4, 0, 479826)
		building:spawnChildCreature("droid_corps_junior_technician", 300, 63.3, -12.0, 78.4, 0, 479826)
		building:spawnChildCreature("droid_corps_junior_technician", 300, 70.0, -12.0, 78.4, 0, 479826)

		building:spawnChildCreature("imperial_warrant_officer_ii", 300, 50.4, -12.0, 62.6, 82, 479827)
		building:spawnChildCreature("imperial_warrant_officer_ii", 300, 50.4, -12.0, 55.8, 122, 479827)

		building:spawnChildCreature("dark_trooper", 300, 36.4, -20.0, 111.8, 180, 479828)
		building:spawnChildCreature("dark_trooper", 300, 34.6, -20.0, 111.8, 180, 479828)

		building:spawnChildCreature("imperial_trooper", 300, 52.2, -12.0, -4.2, 0, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 49.2, -12.0, -4.2, 0, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 46.2, -12.0, -4.2, 0, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 43.2, -12.0, -4.2, 0, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 36.2, -12.0, -4.2, 0, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 33.2, -12.0, -4.2, 0, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 30.2, -12.0, -4.2, 0, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 27.2, -12.0, -4.2, 0, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 20.2, -12.0, -4.2, 0, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 17.2, -12.0, -4.2, 0, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 52.2, -12.0, 26.0, 180, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 49.2, -12.0, 26.0, 180, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 46.2, -12.0, 26.0, 180, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 43.2, -12.0, 26.0, 180, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 36.2, -12.0, 26.0, 180, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 33.2, -12.0, 26.0, 180, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 30.2, -12.0, 26.0, 180, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 27.2, -12.0, 26.0, 180, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 20.2, -12.0, 26.0, 180, 479829)
		building:spawnChildCreature("imperial_trooper", 300, 17.2, -12.0, 26.0, 180, 479829)
		building:spawnChildCreature("imperial_warrant_officer_i", 300, 61.6, -12.0, 16.3, 90, 479829)
		building:spawnChildCreature("imperial_warrant_officer_i", 300, 61.6, -12.0, 5.5, 90, 479829)
		building:spawnChildCreature("imperial_moff", 300, 52.0, -12.0, 10.0, -90, 479829)
		building:spawnChildCreature("imperial_high_general", 300, 52.0, -12.0, 11.5, -90, 479829)
		building:spawnChildCreature("imperial_high_general", 300, 52.0, -12.0, 8.6, -90, 479829)
		building:spawnChildCreature("imperial_general", 300, 48.6, -12.0, 15.5, 180, 479829)
		building:spawnChildCreature("imperial_major_general", 300, 46.0, -12.0, 15.5, 180, 479829)
		building:spawnChildCreature("imperial_colonel", 300, 41.7, -12.0, 15.5, 180, 479829)
		building:spawnChildCreature("imperial_major", 300, 39.2, -12.0, 15.5, 180, 479829)
		building:spawnChildCreature("imperial_general", 300, 47.6, -12.0, 4.7, 0, 479829)
		building:spawnChildCreature("imperial_lieutenant_general", 300, 44.1, -12.0, 4.7, 0, 479829)
		building:spawnChildCreature("imperial_lieutenant_general", 300, 41.4, -12.0, 4.7, 0, 479829)
		building:spawnChildCreature("imperial_major", 300, 38.9, -12.0, 4.7, 0, 479829)
		building:spawnChildCreature("imperial_colonel", 300, 33.0, -12.0, 10.0, 90, 479829)

		building:spawnChildCreature("imperial_trooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("imperial_trooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("imperial_trooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("imperial_trooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("stormtrooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("stormtrooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("stormtrooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("stormtrooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)

		building:spawnChildCreature("stormtrooper", 300, -31.2, -20.0, 40.0, 180, 479833)
		building:spawnChildCreature("stormtrooper", 300, -31.2, -20.0, 45.0, 180, 479833)
		building:spawnChildCreature("stormtrooper", 300, -31.2, -20.0, 50.0, 180, 479833)
		building:spawnChildCreature("stormtrooper", 300, -31.2, -20.0, 55.0, 180, 479833)
		building:spawnChildCreature("stormtrooper", 300, -29.8, -20.0, 40.0, 180, 479833)
		building:spawnChildCreature("stormtrooper", 300, -29.8, -20.0, 45.0, 180, 479833)
		building:spawnChildCreature("stormtrooper", 300, -29.8, -20.0, 50.0, 180, 479833)
		building:spawnChildCreature("stormtrooper", 300, -29.8, -20.0, 55.0, 180, 479833)

		building:spawnChildCreature("droid_corps_junior_technician", 300, -8.0, -20.0, 102.1, 110, 479834)
		building:spawnChildCreature("droid_corps_junior_technician", 300, -37.4, -20.0, 99.9, -55, 479834)

		building:spawnChildCreature("stormtrooper_medic", 300, getRandomNumber(12) + -9.5, -20.0, getRandomNumber(12) + 65.3, getRandomNumber(360), 479836)
		building:spawnChildCreature("stormtrooper_medic", 300, getRandomNumber(12) + -9.5, -20.0, getRandomNumber(12) + 65.3, getRandomNumber(360), 479836)
		building:spawnChildCreature("stormtrooper_medic", 300, getRandomNumber(12) + -9.5, -20.0, getRandomNumber(12) + 65.3, getRandomNumber(360), 479836)
		building:spawnChildCreature("stormtrooper_medic", 300, getRandomNumber(12) + -9.5, -20.0, getRandomNumber(12) + 65.3, getRandomNumber(360), 479836)
		building:spawnChildCreature("stormtrooper_medic", 300, getRandomNumber(12) + -9.5, -20.0, getRandomNumber(12) + 65.3, getRandomNumber(360), 479836)
	end)
end

function HyperdriveResearchFacilityScreenPlay:spawnRebels(pBuilding)

	ObjectManager.withBuildingObject(pBuilding, function(building)
		building:initializeStaticGCWBase(FACTIONREBEL)

		--rebel decorations
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", -1130.5, 77.2, 4532.2, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", -1137.0, 77.2, 4532.2, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", -1153.8, 77.2, 4510.9, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", -1117.3, 77.2, 4510.9, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", -1133.9, 77.2, 4511.4, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", -1145.8, 89.0, 4552.4, 0, 1, 0, 0, 0)

		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", -1136.4, 78.1, 4584.3, 0, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", -1231.9, 75.9, 4500.3, 0, 1, 0, 0, 0)

		building:spawnChildSceneObject("object/tangible/camp/camp_pavilion_s1.iff", -1231.9, 75.9, 4480.3, 0, 1, 0, 0, 0)

		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", 6.7, -12.0, 41.4, 479820, 1, 0, 0, 0)
		building:spawnChildSceneObject("object/tangible/gcw/flip_banner_onpole_rebel.iff", 0.2, -12.0, 41.4, 479820, 1, 0, 0, 0)

		building:spawnChildSceneObject("object/tangible/furniture/imperial/warren_warning_sign.iff", 35.5, -20.0, 112.6, 479828, 1, 0, 0, 0)

		--rebels outside
		building:spawnChildCreature("rebel_trooper", 300, -1130.5, 77.2, 4511.5, 180, 0)
		building:spawnChildCreature("rebel_trooper", 300, -1136.9, 77.2, 4511.5, 180, 0)

		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(12) + -1142.5, 77.7, getRandomNumber(12) + 4586.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(12) + -1142.5, 77.7, getRandomNumber(12) + 4586.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(12) + -1142.5, 77.7, getRandomNumber(12) + 4586.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(12) + -1142.5, 77.7, getRandomNumber(12) + 4586.5, getRandomNumber(180) + -90, 0)

		building:spawnChildCreature("specforce_marine", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("specforce_marine", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("specforce_marine", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("specforce_marine", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("specforce_marine", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("specforce_heavy_weapons_specialist", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("specforce_heavy_weapons_specialist", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("specforce_heavy_weapons_specialist", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("specforce_heavy_weapons_specialist", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("specforce_heavy_weapons_specialist", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)
		building:spawnChildCreature("specforce_heavy_weapons_specialist", 300, getRandomNumber(32) + -1150.0, 77.2, getRandomNumber(12) + 4533.5, getRandomNumber(180) + -90, 0)

		building:spawnChildCreature("rebel_major", 300, -1232.0, 76.0, 4483.3, 180, 0)
		building:spawnChildCreature("rebel_medic", 300, -1218.5, 76.0, 4486.9, 45, 0)
		building:spawnChildCreature("rebel_first_lieutenant", 300, -1228.4, 76.0, 4478.4, -75, 0)
		building:spawnChildCreature("rebel_major", 300, -1234.5, 76.0, 4478.3, 75, 0)

		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(24) + -1244.0, 76.0, getRandomNumber(40) + 4465.5, getRandomNumber(360), 0)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(24) + -1244.0, 76.0, getRandomNumber(40) + 4465.5, getRandomNumber(360), 0)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(24) + -1244.0, 76.0, getRandomNumber(40) + 4465.5, getRandomNumber(360), 0)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(24) + -1244.0, 76.0, getRandomNumber(40) + 4465.5, getRandomNumber(360), 0)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(24) + -1244.0, 76.0, getRandomNumber(40) + 4465.5, getRandomNumber(360), 0)
		building:spawnChildCreature("rebel_warrant_officer_ii", 300, getRandomNumber(24) + -1244.0, 76.0, getRandomNumber(40) + 4465.5, getRandomNumber(360), 0)
		building:spawnChildCreature("rebel_staff_sergeant", 300, getRandomNumber(24) + -1244.0, 76.0, getRandomNumber(40) + 4465.5, getRandomNumber(360), 0)
		building:spawnChildCreature("rebel_warrant_officer_i", 300, getRandomNumber(24) + -1244.0, 76.0, getRandomNumber(40) + 4465.5, getRandomNumber(360), 0)
		building:spawnChildCreature("rebel_trooper", 300, -1185, 75.9, 4510, -135, 0)
		building:spawnChildCreature("rebel_trooper", 300, -1182, 75.9, 4513, -135, 0)
		building:spawnChildCreature("rebel_trooper", 300, -1179, 75.9, 4516, -135, 0)

		--rebels inside
		building:spawnChildCreature("rebel_trooper", 300, 0.0, 0.3, 8.9, 0, 479816)
		building:spawnChildCreature("rebel_trooper", 300, 0.0, 0.3, 6.4, 0,  479816)

		building:spawnChildCreature("rebel_major", 300, -3.2, 0.3, -1.1, -90, 479817)

		building:spawnChildCreature("specforce_heavy_weapons_specialist", 300, 3.7, 0.3, -4.3, -90, 479818)

		building:spawnChildCreature("rebel_trooper", 300, 2.2, -12.0, 21.2, 90, 479819)
		building:spawnChildCreature("rebel_trooper", 300, 4.8, -12.0, 21.2, -90, 479819)

		building:spawnChildCreature("rebel_colonel", 300, 2.4, -12.0, 40.3, 0, 479820)
		building:spawnChildCreature("rebel_corporal", 300, 4.4, -12.0, 40.3, 0, 479820)
		building:spawnChildCreature("senior_specforce_marine", 300, -2.4, -12.0, 37.1, 90, 479820)
		building:spawnChildCreature("senior_specforce_marine", 300, -2.4, -12.0, 34.1, 90, 479820)
		building:spawnChildCreature("senior_specforce_marine", 300, -2.4, -12.0, 31.1, 90, 479820)
		building:spawnChildCreature("senior_specforce_marine", 300, -2.4, -12.0, 28.1, 90, 479820)
		building:spawnChildCreature("senior_specforce_marine", 300, 10.2, -12.0, 33.1, -90, 479820)
		building:spawnChildCreature("senior_specforce_marine", 300, 10.2, -12.0, 36.1, -90, 479820)
		building:spawnChildCreature("senior_specforce_heavy_weapons_specialist", 300, 25.8, -12.0, 50.7, -155, 479820)
		building:spawnChildCreature("senior_specforce_heavy_weapons_specialist", 300, 22.3, -12.0, 40.7, -55, 479820)
		building:spawnChildCreature("senior_specforce_heavy_weapons_specialist", 300, 14.8, -12.0, 44.3, 55, 479820)
		building:spawnChildCreature("senior_specforce_heavy_weapons_specialist", 300, 14.3, -12.0, 52.8, 180, 479820)
		building:spawnChildCreature("rebel_major", 300, 10.1, -12.0, 47.2, -90, 479820)
		building:spawnChildCreature("rebel_warrant_officer_ii", 300, -1.5, -12.0, 62.7, 90, 479820)
		building:spawnChildCreature("rebel_warrant_officer_ii", 300, 1.9, -12.0, 61.2, 35, 479820)
		building:spawnChildCreature("rebel_warrant_officer_ii", 300, 3.6, -12.0, 53.6, 180, 479820)
		building:spawnChildCreature("senior_specforce_marine", 300, -18.4, -12.0, 53.6, 180, 479820)
		building:spawnChildCreature("senior_specforce_marine", 300, -15.4, -12.0, 53.6, 180, 479820)
		building:spawnChildCreature("senior_specforce_marine", 300, -12.4, -12.0, 53.6, 180, 479820)
		building:spawnChildCreature("senior_specforce_marine", 300, -9.4, -12.0, 53.6, 180, 479820)
		building:spawnChildCreature("rebel_sergeant", 300, -17.5, -12.0, 43.2, 40, 479820)

		building:spawnChildCreature("rebel_trooper", 300, -41.8, -20.0, 48.3, 180, 479821)
		building:spawnChildCreature("rebel_trooper", 300, -41.8, -20.0, 45.7, 0, 479821)

		building:spawnChildCreature("rebel_colonel", 300, -49.0, -20.0, 28.0, 90, 479822)
		building:spawnChildCreature("rebel_staff_sergeant", 300, -67.9, -20.0, 24.4, 175, 479822)
		building:spawnChildCreature("rebel_staff_sergeant", 300, -67.2, -20.0, 69.9, -24, 479822)

		building:spawnChildCreature("rebel_staff_sergeant", 300, -50.5, -20.0, 18.7, 24, 479823)
		building:spawnChildCreature("rebel_staff_sergeant", 300, -49.0, -20.0, 17.5, 64, 479823)
		building:spawnChildCreature("rebel_staff_sergeant", 300, -48.7, -20.0, 9.2, 120, 479823)
		building:spawnChildCreature("rebel_staff_sergeant", 300, -50.5, -20.0, 7.2, 160, 479823)
		building:spawnChildCreature("rebel_major", 300, -60.7, -20.0, 11.7, -90, 479823)
		building:spawnChildCreature("rebel_commandant", 1200, -60.7, -20.0, 14.0, -90, 479823)
		building:spawnChildCreature("rebel_surface_marshall", 300, -59.1, -20.0, 6.9, 180, 479823)
		building:spawnChildCreature("rebel_second_lieutenant", 300, -62.6, -20.0, 6.9, 180, 479823)
		building:spawnChildCreature("rebel_surface_marshall", 300, -66.1, -20.0, 6.9, 180, 479823)
		building:spawnChildCreature("rebel_master_sergeant", 300, -74.6, -20.0, 7.3, -145, 479823)
		building:spawnChildCreature("rebel_master_sergeant", 300, -76.2, -20.0, 8.8, -125, 479823)
		building:spawnChildCreature("senior_specforce_marine", 300, -78.2, -20.0, 12.0, 90, 479823)
		building:spawnChildCreature("senior_specforce_marine", 300, -78.2, -20.0, 14.4, 90, 479823)
		building:spawnChildCreature("senior_specforce_technician", 300, -75.6, -20.0, 17.9, -45, 479823)
		building:spawnChildCreature("rebel_surface_marshall", 300, -59.1, -20.0, 19.0, 0, 479823)
		building:spawnChildCreature("rebel_second_lieutenant", 300, -62.6, -20.0, 19.0, 0, 479823)
		building:spawnChildCreature("rebel_surface_marshall", 300, -66.1, -20.0, 19.0, 0, 479823)

		building:spawnChildCreature("rebel_medic", 300, -77.2, -20.0, 74.3, 45, 479824)
		building:spawnChildCreature("specforce_technician", 300, -74.4, -20.0, 86.7, 135, 479824)
		building:spawnChildCreature("specforce_technician", 300, -56.7, -20.0, 75.2, 180, 479824)
		building:spawnChildCreature("rebel_second_lieutenant", 300, -69.2, -20.0, 77.3, -90, 479824)

		building:spawnChildCreature("senior_specforce_lieutenant", 300, 35.7, -12.0, 40.6, 0, 479825)
		building:spawnChildCreature("senior_specforce_heavy_weapons_specialist", 300, 35.7, -12.0, 66.2, 180, 479825)
		building:spawnChildCreature("senior_specforce_lieutenant", 300, 35.7, -12.0, 78.2, 180, 479825)
		building:spawnChildCreature("senior_specforce_pathfinder", 300, 35.7, -12.0, 87.9, 180, 479825)

		building:spawnChildCreature("senior_specforce_technician", 300, 49.3, -12.0, 87.8, 180, 479826)
		building:spawnChildCreature("senior_specforce_technician", 300, 56.7, -12.0, 87.8, 180, 479826)
		building:spawnChildCreature("senior_specforce_technician", 300, 63.3, -12.0, 87.8, 180, 479826)
		building:spawnChildCreature("senior_specforce_technician", 300, 70.0, -12.0, 87.8, 180, 479826)
		building:spawnChildCreature("senior_specforce_technician", 300, 49.3, -12.0, 78.4, 0, 479826)
		building:spawnChildCreature("senior_specforce_technician", 300, 56.7, -12.0, 78.4, 0, 479826)
		building:spawnChildCreature("senior_specforce_technician", 300, 63.3, -12.0, 78.4, 0, 479826)
		building:spawnChildCreature("senior_specforce_technician", 300, 70.0, -12.0, 78.4, 0, 479826)

		building:spawnChildCreature("rebel_warrant_officer_ii", 300, 50.4, -12.0, 62.6, 82, 479827)
		building:spawnChildCreature("rebel_warrant_officer_ii", 300, 50.4, -12.0, 55.8, 122, 479827)

		building:spawnChildCreature("rebel_trooper", 300, 36.4, -20.0, 111.8, 180, 479828)
		building:spawnChildCreature("rebel_trooper", 300, 34.6, -20.0, 111.8, 180, 479828)

		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_sergeant", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_corporal", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_warrant_officer_i", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_sergeant", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_sergeant", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_warrant_officer_i", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_warrant_officer_ii", 300, getRandomNumber(15) + 16.5, -12.0, getRandomNumber(29) + -4.2, getRandomNumber(360), 479829)
		building:spawnChildCreature("rebel_surface_marshall", 300, 61.6, -12.0, 16.3, 90, 479829)
		building:spawnChildCreature("rebel_surface_marshall", 300, 61.6, -12.0, 5.5, 90, 479829)

		building:spawnChildCreature("senior_specforce_technician", 300, -5.1, -20.0, 3.3, 90, 479830)

		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("rebel_trooper", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("senior_specforce_lieutenant", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("senior_specforce_lieutenant", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("senior_specforce_lieutenant", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)
		building:spawnChildCreature("senior_specforce_lieutenant", 300, getRandomNumber(14) + -23.7, -20.0, getRandomNumber(13) + -4.2, getRandomNumber(360), 479831)

		building:spawnChildCreature("senior_specforce_marine", 300, -29.8, -20.0, 21.0, 0, 479833)
		building:spawnChildCreature("senior_specforce_marine", 300, -29.8, -20.0, 36.0, 0, 479833)
		building:spawnChildCreature("senior_specforce_marine", 300, -31.3, -20.0, 37.0, 180, 479833)
		building:spawnChildCreature("senior_specforce_marine", 300, -31.3, -20.0, 44.0, 180, 479833)
		building:spawnChildCreature("senior_specforce_marine", 300, -29.8, -20.0, 57.0, 0, 479833)
		building:spawnChildCreature("senior_specforce_marine", 300, -31.3, -20.0, 59.0, 180, 479833)
		building:spawnChildCreature("senior_specforce_marine", 300, -31.3, -20.0, 71.0, 180, 479833)
		building:spawnChildCreature("senior_specforce_marine", 300, -29.8, -20.0, 81.0, 0, 479833)
		building:spawnChildCreature("senior_specforce_marine", 300, -31.3, -20.0, 82.0, 180, 479833)

		building:spawnChildCreature("senior_specforce_technician", 300, -8.0, -20.0, 102.1, 110, 479834)
		building:spawnChildCreature("senior_specforce_technician", 300, -37.4, -20.0, 99.9, -55, 479834)

		building:spawnChildCreature("specforce_procurement_specialist", 300, getRandomNumber(12) + -9.5, -20.0, getRandomNumber(12) + 65.3, getRandomNumber(360), 479836)
		building:spawnChildCreature("specforce_procurement_specialist", 300, getRandomNumber(12) + -9.5, -20.0, getRandomNumber(12) + 65.3, getRandomNumber(360), 479836)
		building:spawnChildCreature("specforce_procurement_specialist", 300, getRandomNumber(12) + -9.5, -20.0, getRandomNumber(12) + 65.3, getRandomNumber(360), 479836)
		building:spawnChildCreature("specforce_procurement_specialist", 300, getRandomNumber(12) + -9.5, -20.0, getRandomNumber(12) + 65.3, getRandomNumber(360), 479836)
	end)
end

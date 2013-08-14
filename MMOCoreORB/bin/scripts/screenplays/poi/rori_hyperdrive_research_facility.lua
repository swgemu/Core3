HyperdriveResearchFacilityScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "HyperdriveResearchFacilityScreenPlay",

	lootContainers = {

        },

        lootLevel = 22,

        lootGroups = {
                {
                        groups = {
                                {group = "color_crystals", chance = 100000},
                                {group = "junk", chance = 6300000},
                                {group = "melee_weapons", chance = 1500000},
				{group = "pistols", chance = 500000},
				{group = "carbines", chance = 500000},
				{group = "rifles", chance = 500000},
                                {group = "clothing_attachments", chance = 300000},
                                {group = "armor_attachments", chance = 300000}
                        },
                        lootChance = 8000000
                }
        },

        lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("HyperdriveResearchFacilityScreenPlay", true)

function HyperdriveResearchFacilityScreenPlay:start()
	if isZoneEnabled("rori") then
		self:initializeLootContainers()

		if math.random(100) >= 50 then
			self:spawnRebels()
		else
			self:spawnImperials()
		end
	end
end



function HyperdriveResearchFacilityScreenPlay:spawnImperials()

	--imperial decorations
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_imperial.iff", -1130.5, 77.2, 4532.2, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_imperial.iff", -1137.0, 77.2, 4532.2, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_imperial.iff", -1153.8, 77.2, 4510.9, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_imperial.iff", -1117.3, 77.2, 4510.9, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_imperial.iff", -1133.9, 77.2, 4511.4, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_imperial.iff", -1145.8, 89.0, 4552.4, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_imperial.iff", -1136.4, 78.1, 4584.3, 0, 1, 0, 0, 0)

	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_imperial.iff", 6.7, -12.0, 41.4, 479820, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_imperial.iff", 0.2, -12.0, 41.4, 479820, 1, 0, 0, 0)

	spawnSceneObject("rori", "object/tangible/furniture/imperial/warren_warning_sign.iff", 35.5, -20.0, 112.6, 479828, 1, 0, 0, 0)

	--imperials outside

	spawnMobile("rori", "imperial_trooper", 300, -1100, 76.0, 4520, 0, 0)
	spawnMobile("rori", "imperial_trooper", 300, -1100, 76.0, 4524, 0, 0)
	spawnMobile("rori", "imperial_trooper", 300, -1100, 76.0, 4528, 0, 0)
	spawnMobile("rori", "imperial_trooper", 300, -1130.5, 77.2, 4511.5, 180, 0)
	spawnMobile("rori", "imperial_trooper", 300, -1136.9, 77.2, 4511.5, 180, 0)

	spawnMobile("rori", "at_st", 300, math.random(12) + -1142.5, 77.7, math.random(12) + 4586.5, math.random(180) + -90, 0)

	spawnMobile("rori", "stormtrooper", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "stormtrooper", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "stormtrooper", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "stormtrooper", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "stormtrooper_commando", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "stormtrooper_commando", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "stormtrooper_commando", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)

	spawnMobile("rori", "imperial_trooper", 300, -1185, 75.9, 4510, 45, 0)
	spawnMobile("rori", "imperial_trooper", 300, -1182, 75.9, 4513, 45, 0)
	spawnMobile("rori", "imperial_trooper", 300, -1179, 75.9, 4516, 45, 0)
	spawnMobile("rori", "imperial_trooper", 300, -1176, 75.9, 4519, 45, 0)

	--imperials inside
	spawnMobile("rori", "imperial_trooper", 300, 0.0, 0.3, 8.9, 0, 479816)
	spawnMobile("rori", "imperial_trooper", 300, 0.0, 0.3, 6.4, 0, 479816)

	spawnMobile("rori", "imperial_commander", 300, -3.2, 0.3, -1.1, -90, 479817)

	spawnMobile("rori", "dark_trooper", 300, 3.7, 0.3, -4.3, -90, 479818)

	spawnMobile("rori", "imperial_trooper", 300, 2.2, -12.0, 21.2, 90, 479819)
	spawnMobile("rori", "imperial_trooper", 300, 4.8, -12.0, 21.2, -90, 479819)

	spawnMobile("rori", "imperial_colonel", 300, 2.4, -12.0, 40.3, 0, 479820)
	spawnMobile("rori", "imperial_private", 300, 4.4, -12.0, 40.3, 0, 479820)
	spawnMobile("rori", "stormtrooper", 300, -2.4, -12.0, 37.1, 90, 479820)
	spawnMobile("rori", "stormtrooper", 300, -2.4, -12.0, 34.1, 90, 479820)
	spawnMobile("rori", "stormtrooper", 300, -2.4, -12.0, 31.1, 90, 479820)
	spawnMobile("rori", "stormtrooper", 300, -2.4, -12.0, 28.1, 90, 479820)
	spawnMobile("rori", "stormtrooper", 300, 10.2, -12.0, 33.1, -90, 479820)
	spawnMobile("rori", "stormtrooper", 300, 10.2, -12.0, 36.1, -90, 479820)
	spawnMobile("rori", "stormtrooper_sniper", 300, 25.8, -12.0, 50.7, -155, 479820)
	spawnMobile("rori", "stormtrooper_sniper", 300, 22.3, -12.0, 40.7, -55, 479820)
	spawnMobile("rori", "stormtrooper_sniper", 300, 14.8, -12.0, 44.3, 55, 479820)
	spawnMobile("rori", "stormtrooper_sniper", 300, 14.3, -12.0, 52.8, 180, 479820)
	spawnMobile("rori", "imperial_commander", 300, 10.1, -12.0, 47.2, -90, 479820)
	spawnMobile("rori", "imperial_warrant_officer_ii", 300, -1.5, -12.0, 62.7, 90, 479820)
	spawnMobile("rori", "imperial_warrant_officer_ii", 300, 1.9, -12.0, 61.2, 35, 479820)
	spawnMobile("rori", "imperial_warrant_officer_ii", 300, 3.6, -12.0, 53.6, 180, 479820)
	spawnMobile("rori", "dark_trooper", 300, -18.4, -12.0, 53.6, 180, 479820)
	spawnMobile("rori", "dark_trooper", 300, -15.4, -12.0, 53.6, 180, 479820)
	spawnMobile("rori", "dark_trooper", 300, -12.4, -12.0, 53.6, 180, 479820)
	spawnMobile("rori", "dark_trooper", 300, -9.4, -12.0, 53.6, 180, 479820)
	spawnMobile("rori", "imperial_sergeant", 300, -17.5, -12.0, 43.2, 40, 479820)

	spawnMobile("rori", "imperial_trooper", 300, -41.8, -20.0, 48.3, 180, 479821)
	spawnMobile("rori", "imperial_trooper", 300, -41.8, -20.0, 45.7, 0, 479821)

	spawnMobile("rori", "imperial_commander", 300, -49.0, -20.0, 28.0, 90, 479822)
	spawnMobile("rori", "imperial_second_lieutenant", 300, -67.9, -20.0, 24.4, 175, 479822)
	spawnMobile("rori", "imperial_second_lieutenant", 300, -67.2, -20.0, 69.9, -24, 479822)

	spawnMobile("rori", "imperial_lance_corporal", 300, -50.5, -20.0, 18.7, 24, 479823)
	spawnMobile("rori", "imperial_lance_corporal", 300, -49.0, -20.0, 17.5, 64, 479823)
	spawnMobile("rori", "imperial_lance_corporal", 300, -48.7, -20.0, 9.2, 120, 479823)
	spawnMobile("rori", "imperial_lance_corporal", 300, -50.5, -20.0, 7.2, 160, 479823)
	spawnMobile("rori", "imperial_commander", 300, -60.7, -20.0, 11.7, -90, 479823)
	spawnMobile("rori", "imperial_inquisitor", 900, -60.7, -20.0, 14.0, -90, 479823)
	spawnMobile("rori", "imperial_surface_marshall", 300, -59.1, -20.0, 6.9, 180, 479823)
	spawnMobile("rori", "imperial_second_lieutenant", 300, -62.6, -20.0, 6.9, 180, 479823)
	spawnMobile("rori", "imperial_surface_marshall", 300, -66.1, -20.0, 6.9, 180, 479823)
	spawnMobile("rori", "imperial_master_sergeant", 300, -74.6, -20.0, 7.3, -145, 479823)
	spawnMobile("rori", "imperial_master_sergeant", 300, -76.2, -20.0, 8.8, -125, 479823)
	spawnMobile("rori", "stormtrooper_bombardier", 300, -78.2, -20.0, 12.0, 90, 479823)
	spawnMobile("rori", "stormtrooper_bombardier", 300, -78.2, -20.0, 14.4, 90, 479823)
	spawnMobile("rori", "imperial_private", 300, -75.6, -20.0, 17.9, -45, 479823)
	spawnMobile("rori", "imperial_surface_marshall", 300, -59.1, -20.0, 19.0, 0, 479823)
	spawnMobile("rori", "imperial_second_lieutenant", 300, -62.6, -20.0, 19.0, 160, 479823)
	spawnMobile("rori", "imperial_surface_marshall", 300, -66.1, -20.0, 19.0, 0, 479823)

	spawnMobile("rori", "imperial_medic", 300, -77.1, -20.0, 74.4, 45, 479824)
	spawnMobile("rori", "imperial_medic", 300, -53.8, -20.0, 86.4, 90, 479824)
	spawnMobile("rori", "imperial_medic", 300, -50.2, -20.0, 79.8, 135, 479824)
	spawnMobile("rori", "imperial_medic", 300, -69.2, -20.0, 77.3, -90, 479824)

	spawnMobile("rori", "stormtrooper_medic", 300, 36.5, -12.0, 52.2, 0, 479825)
	spawnMobile("rori", "stormtrooper_captain", 300, 34.9, -12.0, 52.2, 0, 479825)
	spawnMobile("rori", "stormtrooper_rifleman", 300, 36.5, -12.0, 57.2, 0, 479825)
	spawnMobile("rori", "stormtrooper_rifleman", 300, 34.9, -12.0, 57.2, 0, 479825)
	spawnMobile("rori", "stormtrooper_squad_leader", 300, 36.5, -12.0, 62.2, 0, 479825)
	spawnMobile("rori", "stormtrooper_medic", 300, 34.9, -12.0, 62.2, 0, 479825)

	spawnMobile("rori", "droid_corps_junior_technician", 240, 49.3, -12.0, 87.8, 180, 479826)
	spawnMobile("rori", "droid_corps_junior_technician", 240, 56.7, -12.0, 87.8, 180, 479826)
	spawnMobile("rori", "droid_corps_junior_technician", 240, 63.3, -12.0, 87.8, 180, 479826)
	spawnMobile("rori", "droid_corps_junior_technician", 240, 70.0, -12.0, 87.8, 180, 479826)
	spawnMobile("rori", "droid_corps_junior_technician", 240, 49.3, -12.0, 78.4, 0, 479826)
	spawnMobile("rori", "droid_corps_junior_technician", 240, 56.7, -12.0, 78.4, 0, 479826)
	spawnMobile("rori", "droid_corps_junior_technician", 240, 63.3, -12.0, 78.4, 0, 479826)
	spawnMobile("rori", "droid_corps_junior_technician", 240, 70.0, -12.0, 78.4, 0, 479826)

	spawnMobile("rori", "imperial_warrant_officer_ii", 300, 50.4, -12.0, 62.6, 82, 479827)
	spawnMobile("rori", "imperial_warrant_officer_ii", 300, 50.4, -12.0, 55.8, 122, 479827)

	spawnMobile("rori", "dark_trooper", 300, 36.4, -20.0, 111.8, 180, 479828)
	spawnMobile("rori", "dark_trooper", 300, 34.6, -20.0, 111.8, 180, 479828)

	spawnMobile("rori", "imperial_trooper", 300, 52.2, -12.0, -4.2, 0, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 49.2, -12.0, -4.2, 0, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 46.2, -12.0, -4.2, 0, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 43.2, -12.0, -4.2, 0, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 36.2, -12.0, -4.2, 0, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 33.2, -12.0, -4.2, 0, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 30.2, -12.0, -4.2, 0, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 27.2, -12.0, -4.2, 0, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 20.2, -12.0, -4.2, 0, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 17.2, -12.0, -4.2, 0, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 52.2, -12.0, 26.0, 180, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 49.2, -12.0, 26.0, 180, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 46.2, -12.0, 26.0, 180, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 43.2, -12.0, 26.0, 180, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 36.2, -12.0, 26.0, 180, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 33.2, -12.0, 26.0, 180, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 30.2, -12.0, 26.0, 180, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 27.2, -12.0, 26.0, 180, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 20.2, -12.0, 26.0, 180, 479829)
	spawnMobile("rori", "imperial_trooper", 300, 17.2, -12.0, 26.0, 180, 479829)
	spawnMobile("rori", "imperial_warrant_officer_i", 300, 61.6, -12.0, 16.3, 90, 479829)
	spawnMobile("rori", "imperial_warrant_officer_i", 300, 61.6, -12.0, 5.5, 90, 479829)
	spawnMobile("rori", "imperial_moff", 300, 52.0, -12.0, 10.0, -90, 479829)
	spawnMobile("rori", "imperial_high_general", 300, 52.0, -12.0, 11.5, -90, 479829)
	spawnMobile("rori", "imperial_high_general", 300, 52.0, -12.0, 8.6, -90, 479829)
	spawnMobile("rori", "imperial_general", 300, 48.6, -12.0, 15.5, 180, 479829)
	spawnMobile("rori", "imperial_major_general", 300, 46.0, -12.0, 15.5, 180, 479829)
	spawnMobile("rori", "imperial_colonel", 300, 41.7, -12.0, 15.5, 180, 479829)
	spawnMobile("rori", "imperial_major", 300, 39.2, -12.0, 15.5, 180, 479829)
	spawnMobile("rori", "imperial_general", 300, 47.6, -12.0, 4.7, 0, 479829)
	spawnMobile("rori", "imperial_lieutenant_general", 300, 44.1, -12.0, 4.7, 0, 479829)
	spawnMobile("rori", "imperial_lieutenant_general", 300, 41.4, -12.0, 4.7, 0, 479829)
	spawnMobile("rori", "imperial_major", 300, 38.9, -12.0, 4.7, 0, 479829)
	spawnMobile("rori", "imperial_commander", 300, 33.0, -12.0, 10.0, 90, 479829)

	spawnMobile("rori", "imperial_trooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "imperial_trooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "imperial_trooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "imperial_trooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "stormtrooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "stormtrooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "stormtrooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "stormtrooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)

	spawnMobile("rori", "stormtrooper", 300, -31.2, -20.0, 40.0, 180, 479833)
	spawnMobile("rori", "stormtrooper", 300, -31.2, -20.0, 45.0, 180, 479833)
	spawnMobile("rori", "stormtrooper", 300, -31.2, -20.0, 50.0, 180, 479833)
	spawnMobile("rori", "stormtrooper", 300, -31.2, -20.0, 55.0, 180, 479833)
	spawnMobile("rori", "stormtrooper", 300, -29.8, -20.0, 40.0, 180, 479833)
	spawnMobile("rori", "stormtrooper", 300, -29.8, -20.0, 45.0, 180, 479833)
	spawnMobile("rori", "stormtrooper", 300, -29.8, -20.0, 50.0, 180, 479833)
	spawnMobile("rori", "stormtrooper", 300, -29.8, -20.0, 55.0, 180, 479833)

	spawnMobile("rori", "droid_corps_junior_technician", 300, -8.0, -20.0, 102.1, 110, 479834)
	spawnMobile("rori", "droid_corps_junior_technician", 300, -37.4, -20.0, 99.9, -55, 479834)

	spawnMobile("rori", "stormtrooper_medic", 300, math.random(12) + -9.5, -20.0, math.random(12) + 65.3, math.random(360), 479836)
	spawnMobile("rori", "stormtrooper_medic", 300, math.random(12) + -9.5, -20.0, math.random(12) + 65.3, math.random(360), 479836)
	spawnMobile("rori", "stormtrooper_medic", 300, math.random(12) + -9.5, -20.0, math.random(12) + 65.3, math.random(360), 479836)
	spawnMobile("rori", "stormtrooper_medic", 300, math.random(12) + -9.5, -20.0, math.random(12) + 65.3, math.random(360), 479836)
	spawnMobile("rori", "stormtrooper_medic", 300, math.random(12) + -9.5, -20.0, math.random(12) + 65.3, math.random(360), 479836)

end

function HyperdriveResearchFacilityScreenPlay:spawnRebels()

	--rebel decorations
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_rebel.iff", -1130.5, 77.2, 4532.2, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_rebel.iff", -1137.0, 77.2, 4532.2, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_rebel.iff", -1153.8, 77.2, 4510.9, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_rebel.iff", -1117.3, 77.2, 4510.9, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_rebel.iff", -1133.9, 77.2, 4511.4, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_rebel.iff", -1145.8, 89.0, 4552.4, 0, 1, 0, 0, 0)

	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_rebel.iff", -1136.4, 78.1, 4584.3, 0, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_rebel.iff", -1231.9, 75.9, 4500.3, 0, 1, 0, 0, 0)

	spawnSceneObject("rori", "object/tangible/camp/camp_pavilion_s1.iff", -1231.9, 75.9, 4480.3, 0, 1, 0, 0, 0)

	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_rebel.iff", 6.7, -12.0, 41.4, 479820, 1, 0, 0, 0)
	spawnSceneObject("rori", "object/tangible/gcw/flip_banner_onpole_rebel.iff", 0.2, -12.0, 41.4, 479820, 1, 0, 0, 0)

	spawnSceneObject("rori", "object/tangible/furniture/imperial/warren_warning_sign.iff", 35.5, -20.0, 112.6, 479828, 1, 0, 0, 0)

	--rebels outside

	spawnMobile("rori", "rebel_trooper", 300, -1130.5, 77.2, 4511.5, 180, 0)
	spawnMobile("rori", "rebel_trooper", 300, -1136.9, 77.2, 4511.5, 180, 0)

	spawnMobile("rori", "rebel_trooper", 300, math.random(12) + -1142.5, 77.7, math.random(12) + 4586.5, math.random(180) + -90, 0)
	spawnMobile("rori", "rebel_trooper", 300, math.random(12) + -1142.5, 77.7, math.random(12) + 4586.5, math.random(180) + -90, 0)
	spawnMobile("rori", "rebel_trooper", 300, math.random(12) + -1142.5, 77.7, math.random(12) + 4586.5, math.random(180) + -90, 0)
	spawnMobile("rori", "rebel_trooper", 300, math.random(12) + -1142.5, 77.7, math.random(12) + 4586.5, math.random(180) + -90, 0)

	spawnMobile("rori", "specforce_marine", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "specforce_marine", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "specforce_marine", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "specforce_marine", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "specforce_marine", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "specforce_heavy_weapons_specialist", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "specforce_heavy_weapons_specialist", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "specforce_heavy_weapons_specialist", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "specforce_heavy_weapons_specialist", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "specforce_heavy_weapons_specialist", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)
	spawnMobile("rori", "specforce_heavy_weapons_specialist", 300, math.random(32) + -1150.0, 77.2, math.random(12) + 4533.5, math.random(180) + -90, 0)

	spawnMobile("rori", "rebel_major", 300, -1232.0, 76.0, 4483.3, 180, 0)
	spawnMobile("rori", "rebel_medic", 300, -1218.5, 76.0, 4486.9, 45, 0)
	spawnMobile("rori", "rebel_first_lieutenant", 300, -1228.4, 76.0, 4478.4, -75, 0)
	spawnMobile("rori", "rebel_major", 300, -1234.5, 76.0, 4478.3, 75, 0)

	spawnMobile("rori", "rebel_trooper", 300, math.random(24) + -1244.0, 76.0, math.random(40) + 4465.5, math.random(360), 0)
	spawnMobile("rori", "rebel_trooper", 300, math.random(24) + -1244.0, 76.0, math.random(40) + 4465.5, math.random(360), 0)
	spawnMobile("rori", "rebel_trooper", 300, math.random(24) + -1244.0, 76.0, math.random(40) + 4465.5, math.random(360), 0)
	spawnMobile("rori", "rebel_trooper", 300, math.random(24) + -1244.0, 76.0, math.random(40) + 4465.5, math.random(360), 0)
	spawnMobile("rori", "rebel_trooper", 300, math.random(24) + -1244.0, 76.0, math.random(40) + 4465.5, math.random(360), 0)
	spawnMobile("rori", "rebel_warrant_officer_ii", 300, math.random(24) + -1244.0, 76.0, math.random(40) + 4465.5, math.random(360), 0)
	spawnMobile("rori", "rebel_staff_sergeant", 300, math.random(24) + -1244.0, 76.0, math.random(40) + 4465.5, math.random(360), 0)
	spawnMobile("rori", "rebel_warrant_officer_i", 300, math.random(24) + -1244.0, 76.0, math.random(40) + 4465.5, math.random(360), 0)
	spawnMobile("rori", "rebel_trooper", 300, -1185, 75.9, 4510, -135, 0)
	spawnMobile("rori", "rebel_trooper", 300, -1182, 75.9, 4513, -135, 0)
	spawnMobile("rori", "rebel_trooper", 300, -1179, 75.9, 4516, -135, 0)

	--rebels inside
	spawnMobile("rori", "rebel_trooper", 300, 0.0, 0.3, 8.9, 0, 479816)
	spawnMobile("rori", "rebel_trooper", 300, 0.0, 0.3, 6.4, 0, 479816)

	spawnMobile("rori", "rebel_commander", 300, -3.2, 0.3, -1.1, -90, 479817)

	spawnMobile("rori", "specforce_heavy_weapons_specialist", 300, 3.7, 0.3, -4.3, -90, 479818)

	spawnMobile("rori", "rebel_trooper", 300, 2.2, -12.0, 21.2, 90, 479819)
	spawnMobile("rori", "rebel_trooper", 300, 4.8, -12.0, 21.2, -90, 479819)

	spawnMobile("rori", "rebel_colonel", 300, 2.4, -12.0, 40.3, 0, 479820)
	spawnMobile("rori", "rebel_corporal", 300, 4.4, -12.0, 40.3, 0, 479820)
	spawnMobile("rori", "senior_specforce_marine", 300, -2.4, -12.0, 37.1, 90, 479820)
	spawnMobile("rori", "senior_specforce_marine", 300, -2.4, -12.0, 34.1, 90, 479820)
	spawnMobile("rori", "senior_specforce_marine", 300, -2.4, -12.0, 31.1, 90, 479820)
	spawnMobile("rori", "senior_specforce_marine", 300, -2.4, -12.0, 28.1, 90, 479820)
	spawnMobile("rori", "senior_specforce_marine", 300, 10.2, -12.0, 33.1, -90, 479820)
	spawnMobile("rori", "senior_specforce_marine", 300, 10.2, -12.0, 36.1, -90, 479820)
	spawnMobile("rori", "senior_specforce_heavy_weapons_specialist", 300, 25.8, -12.0, 50.7, -155, 479820)
	spawnMobile("rori", "senior_specforce_heavy_weapons_specialist", 300, 22.3, -12.0, 40.7, -55, 479820)
	spawnMobile("rori", "senior_specforce_heavy_weapons_specialist", 300, 14.8, -12.0, 44.3, 55, 479820)
	spawnMobile("rori", "senior_specforce_heavy_weapons_specialist", 300, 14.3, -12.0, 52.8, 180, 479820)
	spawnMobile("rori", "rebel_commander", 300, 10.1, -12.0, 47.2, -90, 479820)
	spawnMobile("rori", "rebel_warrant_officer_ii", 300, -1.5, -12.0, 62.7, 90, 479820)
	spawnMobile("rori", "rebel_warrant_officer_ii", 300, 1.9, -12.0, 61.2, 35, 479820)
	spawnMobile("rori", "rebel_warrant_officer_ii", 300, 3.6, -12.0, 53.6, 180, 479820)
	spawnMobile("rori", "senior_specforce_marine", 300, -18.4, -12.0, 53.6, 180, 479820)
	spawnMobile("rori", "senior_specforce_marine", 300, -15.4, -12.0, 53.6, 180, 479820)
	spawnMobile("rori", "senior_specforce_marine", 300, -12.4, -12.0, 53.6, 180, 479820)
	spawnMobile("rori", "senior_specforce_marine", 300, -9.4, -12.0, 53.6, 180, 479820)
	spawnMobile("rori", "rebel_sergeant", 300, -17.5, -12.0, 43.2, 40, 479820)

	spawnMobile("rori", "rebel_trooper", 300, -41.8, -20.0, 48.3, 180, 479821)
	spawnMobile("rori", "rebel_trooper", 300, -41.8, -20.0, 45.7, 0, 479821)

	spawnMobile("rori", "rebel_commander", 300, -49.0, -20.0, 28.0, 90, 479822)
	spawnMobile("rori", "rebel_staff_sergeant", 300, -67.9, -20.0, 24.4, 175, 479822)
	spawnMobile("rori", "rebel_staff_sergeant", 300, -67.2, -20.0, 69.9, -24, 479822)

	spawnMobile("rori", "rebel_staff_sergeant", 300, -50.5, -20.0, 18.7, 24, 479823)
	spawnMobile("rori", "rebel_staff_sergeant", 300, -49.0, -20.0, 17.5, 64, 479823)
	spawnMobile("rori", "rebel_staff_sergeant", 300, -48.7, -20.0, 9.2, 120, 479823)
	spawnMobile("rori", "rebel_staff_sergeant", 300, -50.5, -20.0, 7.2, 160, 479823)
	spawnMobile("rori", "rebel_commander", 300, -60.7, -20.0, 11.7, -90, 479823)
	spawnMobile("rori", "rebel_commandant", 1200, -60.7, -20.0, 14.0, -90, 479823)
	spawnMobile("rori", "rebel_surface_marshall", 300, -59.1, -20.0, 6.9, 180, 479823)
	spawnMobile("rori", "rebel_second_lieutenant", 300, -62.6, -20.0, 6.9, 180, 479823)
	spawnMobile("rori", "rebel_surface_marshall", 300, -66.1, -20.0, 6.9, 180, 479823)
	spawnMobile("rori", "rebel_master_sergeant", 300, -74.6, -20.0, 7.3, -145, 479823)
	spawnMobile("rori", "rebel_master_sergeant", 300, -76.2, -20.0, 8.8, -125, 479823)
	spawnMobile("rori", "senior_specforce_marine", 300, -78.2, -20.0, 12.0, 90, 479823)
	spawnMobile("rori", "senior_specforce_marine", 300, -78.2, -20.0, 14.4, 90, 479823)
	spawnMobile("rori", "senior_specforce_technician", 300, -75.6, -20.0, 17.9, -45, 479823)
	spawnMobile("rori", "rebel_surface_marshall", 300, -59.1, -20.0, 19.0, 0, 479823)
	spawnMobile("rori", "rebel_second_lieutenant", 300, -62.6, -20.0, 19.0, 160, 479823)
	spawnMobile("rori", "rebel_surface_marshall", 300, -66.1, -20.0, 19.0, 0, 479823)

	spawnMobile("rori", "rebel_medic", 300, -77.2, -20.0, 74.3, 45, 479824)
	spawnMobile("rori", "specforce_technician", 300, -74.4, -20.0, 86.7, 135, 479824)
	spawnMobile("rori", "specforce_technician", 300, -56.7, -20.0, 75.2, 180, 479824)
	spawnMobile("rori", "rebel_second_lieutenant", 300, -69.2, -20.0, 77.3, -90, 479824)

	spawnMobile("rori", "senior_specforce_lieutenant", 300, 35.7, -12.0, 40.6, 0, 479825)
	spawnMobile("rori", "senior_specforce_heavy_weapons_specialist", 300, 35.7, -12.0, 66.2, 180, 479825)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, 35.7, -12.0, 78.2, 180, 479825)
	spawnMobile("rori", "senior_specforce_pathfinder", 300, 35.7, -12.0, 87.9, 180, 479825)

	spawnMobile("rori", "senior_specforce_technician", 300, 49.3, -12.0, 87.8, 180, 479826)
	spawnMobile("rori", "senior_specforce_technician", 300, 56.7, -12.0, 87.8, 180, 479826)
	spawnMobile("rori", "senior_specforce_technician", 300, 63.3, -12.0, 87.8, 180, 479826)
	spawnMobile("rori", "senior_specforce_technician", 300, 70.0, -12.0, 87.8, 180, 479826)
	spawnMobile("rori", "senior_specforce_technician", 300, 49.3, -12.0, 78.4, 0, 479826)
	spawnMobile("rori", "senior_specforce_technician", 300, 56.7, -12.0, 78.4, 0, 479826)
	spawnMobile("rori", "senior_specforce_technician", 300, 63.3, -12.0, 78.4, 0, 479826)
	spawnMobile("rori", "senior_specforce_technician", 300, 70.0, -12.0, 78.4, 0, 479826)

	spawnMobile("rori", "rebel_warrant_officer_ii", 300, 50.4, -12.0, 62.6, 82, 479827)
	spawnMobile("rori", "rebel_warrant_officer_ii", 300, 50.4, -12.0, 55.8, 122, 479827)

	spawnMobile("rori", "rebel_trooper", 300, 36.4, -20.0, 111.8, 180, 479828)
	spawnMobile("rori", "rebel_trooper", 300, 34.6, -20.0, 111.8, 180, 479828)

	spawnMobile("rori", "rebel_trooper", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_trooper", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_trooper", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_trooper", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_trooper", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_sergeant", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_corporal", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_warrant_officer_i", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_sergeant", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_sergeant", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_warrant_officer_i", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_warrant_officer_ii", 300, math.random(15) + 16.5, -12.0, math.random(29) + -4.2, math.random(360), 479829)
	spawnMobile("rori", "rebel_surface_marshall", 300, 61.6, -12.0, 16.3, 90, 479829)
	spawnMobile("rori", "rebel_surface_marshall", 300, 61.6, -12.0, 5.5, 90, 479829)

	spawnMobile("rori", "senior_specforce_technician", 300, -5.1, -20.0, 3.3, 90, 479830)

	spawnMobile("rori", "rebel_trooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "rebel_trooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "rebel_trooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "rebel_trooper", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, math.random(14) + -23.7, -20.0, math.random(13) + -4.2, math.random(360), 479831)

	spawnMobile("rori", "senior_specforce_marine", 300, -29.8, -20.0, 21.0, 0, 479833)
	spawnMobile("rori", "senior_specforce_marine", 300, -29.8, -20.0, 36.0, 0, 479833)
	spawnMobile("rori", "senior_specforce_marine", 300, -31.3, -20.0, 37.0, 180, 479833)
	spawnMobile("rori", "senior_specforce_marine", 300, -31.3, -20.0, 44.0, 180, 479833)
	spawnMobile("rori", "senior_specforce_marine", 300, -29.8, -20.0, 57.0, 0, 479833)
	spawnMobile("rori", "senior_specforce_marine", 300, -31.3, -20.0, 59.0, 180, 479833)
	spawnMobile("rori", "senior_specforce_marine", 300, -31.3, -20.0, 71.0, 180, 479833)
	spawnMobile("rori", "senior_specforce_marine", 300, -29.8, -20.0, 81.0, 0, 479833)
	spawnMobile("rori", "senior_specforce_marine", 300, -31.3, -20.0, 82.0, 180, 479833)

	spawnMobile("rori", "senior_specforce_technician", 300, -8.0, -20.0, 102.1, 110, 479834)
	spawnMobile("rori", "senior_specforce_technician", 300, -37.4, -20.0, 99.9, -55, 479834)

	spawnMobile("rori", "specforce_procurement_specialist", 300, math.random(12) + -9.5, -20.0, math.random(12) + 65.3, math.random(360), 479836)
	spawnMobile("rori", "specforce_procurement_specialist", 300, math.random(12) + -9.5, -20.0, math.random(12) + 65.3, math.random(360), 479836)
	spawnMobile("rori", "specforce_procurement_specialist", 300, math.random(12) + -9.5, -20.0, math.random(12) + 65.3, math.random(360), 479836)
	spawnMobile("rori", "specforce_procurement_specialist", 300, math.random(12) + -9.5, -20.0, math.random(12) + 65.3, math.random(360), 479836)

end

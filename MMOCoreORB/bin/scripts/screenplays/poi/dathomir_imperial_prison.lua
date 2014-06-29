ImperialPrisonScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "ImperialPrisonScreenPlay",

	lootContainers = {
		3295526,
		3295522,
		3295524,
		3295525
        },
        
        lootLevel = 43,

        lootGroups = {
                {
                        groups = {
				{group = "junk", chance = 5500000},
                                {group = "color_crystals", chance = 1000000},
                                {group = "melee_weapons", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "carbines", chance = 500000},
				{group = "rifles", chance = 500000},
                                {group = "clothing_attachments", chance = 750000},
                                {group = "armor_attachments", chance = 750000}
                        },
                        lootChance = 8000000
                }
        },

        lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("ImperialPrisonScreenPlay", true)

function ImperialPrisonScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

function ImperialPrisonScreenPlay:spawnMobiles()

	--outside the walls

	spawnMobile("dathomir", "imperial_probe_drone", 300, -5936.1, 131.5, 986.2, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -5932.6, 134.6, 916.6, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -5942.9, 121.7, 831.3, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6001.3, 127.5, 698.4, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6086.3, 132.6, 600.2, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6173.1, 130.3, 546.8, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6292.1, 127.1, 509.3, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6436.6, 195.6, 511.6, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6577.3, 211.6, 565.3, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6781.0, 467.9, 886.7, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6728.0, 432.7, 720.9, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6769.6, 525.8, 1036.8, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6683.9, 469.5, 1204.1, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6582.0, 400.0, 1291.0, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6367.3, 212.6, 1355.1, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6265.7, 150.0, 1344.9, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6107.0, 112.3, 1273.3, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6002.5, 155.3, 1162.9, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -6067.7, 133.7, 752.1, 45, 0)
	spawnMobile("dathomir", "imperial_probe_drone", 300, -5961.9, 124.7, 1084.6, 45, 0)

	spawnMobile("dathomir", "at_st", 720, -6108.5, 127.0, 1050.2, -33, 0)
	spawnMobile("dathomir", "at_st", 720, -6080.7, 129.3, 914.7, 162, 0)
	spawnMobile("dathomir", "at_st", 720, -6255.7, 130.6, 789.3, 162, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6147.3, 129.4, 953.2, 45, 0)
	spawnMobile("dathomir", "stormtrooper_sniper", 300, -6143.0, 129.4, 953.5, 45, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6147.6, 129.4, 949.2, 45, 0)

	spawnMobile("dathomir", "stormtrooper", 300, -6272.2, 130.0, 794.7, 37, 0)
	spawnMobile("dathomir", "stormtrooper_sniper", 300, -6275.7, 130.0, 796.2, 37, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6269.7, 130.0, 790.2, 37, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6218.7, 129.9, 866.0, 52, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6221.2, 129.9, 868.5, 52, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6215.2, 129.9, 864.5, 45, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6151.9, 126.6, 994.2, -42, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6153.4, 126.6, 990.7, -42, 0)
	spawnMobile("dathomir", "stormtrooper_squad_leader", 300, -6149.4, 126.6, 996.7, -42, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6211.3, 129.8, 1052.7, -65, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6214.8, 129.8, 1050.2, -65, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6208.8, 129.8, 1054.2, -65, 0)

	spawnMobile("dathomir", "stormtrooper", 300, -6288.1, 129.9, 1092.5, -76, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6285.6, 129.9, 1095.0, -76, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6290.6, 129.9, 1090.0, -76, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6386.2, 129.9, 1099.9, -100, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6388.7, 129.9, 1097.4, -100, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6388.7, 129.9, 1102.4, -100, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6484.5, 129.9, 1105.8, -132, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6482.0, 129.9, 1103.3, -132, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6487.0, 129.9, 1103.3, -132, 0)

	spawnMobile("dathomir", "stormtrooper", 300, -6534.3, 129.9, 1034.3, -125, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6536.8, 129.9, 1036.8, -125, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6531.8, 129.9, 1036.8, -125, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6571.7, 129.9, 958.6, 167, 0)
	spawnMobile("dathomir", "stormtrooper_sniper", 300, -6574.2, 129.9, 956.1, 167, 0)
	spawnMobile("dathomir", "stormtrooper_sniper", 300, -6569.2, 129.9, 961.1, 167, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6530.5, 129.9, 906.2, 152, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6528.0, 129.9, 908.7, 152, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6533.0, 129.9, 903.7, 152, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6530.5, 129.9, 833.2, 174, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6528.0, 129.9, 835.7, 174, 0)
	spawnMobile("dathomir", "stormtrooper_squad_leader", 300, -6533.0, 129.9, 830.2, 174, 0)

	spawnMobile("dathomir", "stormtrooper_sniper", 300, -6504.3, 136.1, 756.3, 108, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6506.8, 138.1, 753.8, 108, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6501.8, 134.4, 758.8, 108, 0)

	spawnMobile("dathomir", "stormtrooper", 300, -6405.2, 129.9, 765.2, 101, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6402.7, 129.9, 767.7, 101, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6407.7, 129.9, 762.7, 101, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6345.8, 133.9, 703.4, 90, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6342.3, 133.9, 705.9, 90, 0)
	spawnMobile("dathomir", "stormtrooper_squad_leader", 300, -6342.3, 134.3, 700.9, 90, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6146.2, 127.9, 976.7, 105, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6145.5, 127.9, 969.9, 105, 0)

	--between the inner and outer walls

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6164.3, 127.9, 964.9, -172, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6161.8, 127.9, 962.4, -172, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6161.8, 127.9, 967.4, -172, 0)

	spawnMobile("dathomir", "stormtrooper", 300, -6271.7, 127.9, 843.1, 180, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6271.7, 127.9, 847.1, 180, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6271.7, 127.9, 851.1, 180, 0)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6321.0, 127.9, 799.8, -90, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6325.0, 127.9, 800.0, -90, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6329.0, 127.9, 800.2, -90, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6345.5, 127.9, 792.9, 0, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6351.5, 127.9, 793.5, 0, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6352.8, 127.9, 803.1, 180, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6347.2, 127.9, 804.6, 180, 0)

	spawnMobile("dathomir", "stormtrooper", 300, -6455.5, 127.9, 774.3, -90, 0)
	spawnMobile("dathomir", "stormtrooper_captain", 300, -6459.5, 127.9, 774.5, -90, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6463.5, 127.9, 774.7, -90, 0)

	spawnMobile("dathomir", "stormtrooper_medic", 300, -6487.0, 127.9, 862.6, -40, 0)
	spawnMobile("dathomir", "stormtrooper_sniper", 300, -6489.9, 127.9, 866.6, -40, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6492.8, 127.9, 870.6, -40, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6506.5, 127.9, 926.9, -128, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6503.1, 127.9, 921.9, -128, 0)

	spawnMobile("dathomir", "stormtrooper_medic", 300, -6545.3, 127.9, 956.7, 0, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6545.8, 127.9, 960.7, 0, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6546.3, 127.9, 964.7, 0, 0)

	spawnMobile("dathomir", "stormtrooper_medic", 300, -6459.5, 127.9, 1084.4, 99, 0)
	spawnMobile("dathomir", "stormtrooper_sniper", 300, -6455.5, 127.9, 1084.0, 99, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6451.5, 127.9, 1083.6, 99, 0)

	spawnMobile("dathomir", "stormtrooper", 300, -6334.1, 127.9, 1059.9, 90, 0)
	spawnMobile("dathomir", "stormtrooper_sniper", 300, -6330.1, 127.9, 1059.9, 90, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6326.1, 127.9, 1059.9, 90, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6203.2, 127.9, 1021.9, 20, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6196.8, 127.9, 1018.6, 20, 0)

	--inside the walls (not in buildings)

	spawnMobile("dathomir", "stormtrooper_rifleman", 300, -6455.0, 119.9, 961.9, -128, 0)
	spawnMobile("dathomir", "stormtrooper_medic", 300, -6452.1, 119.9, 964.0, -128, 0)
	spawnMobile("dathomir", "stormtrooper_squad_leader", 300, -6457.7, 119.9, 960.1, -128, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6304.5, 119.9, 885.6, 0, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6311.2, 119.9, 885.8, 0, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6339.9, 119.9, 924.6, 90, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6339.9, 119.9, 931.1, 90, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6239.6, 119.9, 940.0, -100, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6241.7, 119.9, 949.8, -100, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6359.2, 119.9, 832.9, -15, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6352.7, 119.9, 834.4, -15, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6389.2, 119.9, 879.3, 0, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6396.1, 119.9, 879.2, 0, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6320.2, 119.9, 978.3, -170, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6327.2, 119.9, 979.6, -170, 0)

	spawnMobile("dathomir", "stormtrooper_commando", 300, -6384.2, 119.9, 988.3, -170, 0)
	spawnMobile("dathomir", "stormtrooper_commando", 300, -6377.7, 119.9, 987.0, -170, 0)

	spawnMobile("dathomir", "stormtrooper", 300, -6257.7, 119.9, 940.4, -100, 0)
	spawnMobile("dathomir", "stormtrooper_sniper", 300, -6262.7, 119.9, 939.6, -100, 0)
	spawnMobile("dathomir", "stormtrooper", 300, -6267.7, 119.9, 938.8, -100, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6272.7, 119.9, 938.0, -100, 0)
	spawnMobile("dathomir", "force_sensitive_renegade", 600, -6277.7, 119.9, 937.2, -100, 0)
	spawnMobile("dathomir", "imprisoned_rebel_soldier", 300, -6282.7, 119.9, 936.4, -100, 0)
	spawnMobile("dathomir", "dark_trooper", 300, -6287.7, 119.9, 935.6, -100, 0)
	spawnMobile("dathomir", "dark_trooper", 300, -6292.7, 119.9, 934.8, -100, 0)

	spawnMobile("dathomir", "tough_dathomir_prisoner", 300, -6276.5, 119.9, 897.4, -140, 0)
	spawnMobile("dathomir", "tough_dathomir_prisoner", 300, -6306.5, 119.9, 905.4, 140, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6297.6, 119.9, 874.6, -100, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6302.5, 119.9, 872.4, 60, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6299.5, 119.9, 877.7, 160, 0)
	spawnMobile("dathomir", "tough_dathomir_prisoner", 300, -6319.5, 119.9, 873.4, -140, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6339.5, 119.9, 877.4, 40, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6357.5, 119.9, 853.4, -21, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6419.8, 129.5, 883.9, -62, 0)

	spawnMobile("dathomir", "dathomir_prisoner", 300, -6190.2, 119.9, 992.6, -126, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6201.2, 119.9, 993.6, 176, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6186.2, 119.9, 954.2, 166, 0)
	spawnMobile("dathomir", "tough_dathomir_prisoner", 300, -6258.5, 119.9, 1006.6, -126, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6325.2, 119.9, 958.6, -16, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6463.7, 119.9, 992.6, 136, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6429.2, 119.9, 1001.6, 86, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6414.3, 119.9, 1042.4, -156, 0)
	spawnMobile("dathomir", "tough_dathomir_prisoner", 300, -6415.7, 119.9, 1039.3, 24, 0)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -6427.9, 119.9, 920.6, 100, 0)

	spawnMobile("dathomir", "commoner_old", 300, -6334.5, 119.9, 921.4, -40, 0)
	spawnMobile("dathomir", "commoner_old", 300, -6371.2, 119.9, 860.3, -140, 0)
	spawnMobile("dathomir", "informant_npc_lvl_3", 10, -6237.5, 119.9, 937.9, 180, 0)

	--buildings (stormtrooper barracks)

	spawnMobile("dathomir", "stormtrooper", 300, 3.6, 0.1, 1.8, -90, 2665665)
	spawnMobile("dathomir", "stormtrooper", 300, -3.9, 0.1, -3.5, 90, 2665667)
	spawnMobile("dathomir", "dark_trooper", 300, 0.0, 0.1, -3.5, 0, 2665678)

	spawnMobile("dathomir", "stormtrooper", 300, 3.6, 0.1, 1.8, -90, 3295422)
	spawnMobile("dathomir", "stormtrooper_squad_leader", 300, -3.9, 0.1, -3.5, 90, 3295424)
	spawnMobile("dathomir", "stormtrooper_medic", 300, 3.6, 0.1, 1.8, -90, 3295429)
	spawnMobile("dathomir", "stormtrooper", 300, 3.6, 0.1, -3.8, -90, 3295430)

	--buildings (prison cells)

	spawnMobile("dathomir", "singing_mountain_clan_outcast", 600, 4.5, 0.1, -3.6, 90, 5335769)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -4.5, 0.1, -1.2, 166, 5335770)

	spawnMobile("dathomir", "commoner_old", 300, -4.5, 0.1, -1.2, 166, 5335791)
	spawnMobile("dathomir", "tough_dathomir_prisoner", 300, -4.9, 0.1, -2.4, 16, 5335791)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -4.2, 0.1, -3.6, -66, 5335791)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -4.5, 0.1, -4.8, 96, 5335791)

	spawnMobile("dathomir", "imprisoned_rebel_soldier", 300, 4.5, 0.1, -2.2, 0, 5335783)
	spawnMobile("dathomir", "imprisoned_rebel_soldier", 300, 4.5, 0.1, -3.6, 90, 5335783)
	spawnMobile("dathomir", "imprisoned_rebel_soldier", 300, 3.0, 0.1, -5.6, -60, 5335783)

	spawnMobile("dathomir", "imprisoned_jabba_employee", 300, 4.5, 0.1, -2.2, 40, 5335804)
	spawnMobile("dathomir", "tough_dathomir_prisoner", 300, 4.5, 0.1, -3.6, 180, 5335804)
	spawnMobile("dathomir", "commoner_old", 30, 3.0, 0.1, -5.6, -60, 5335804)

	spawnMobile("dathomir", "dathomir_prisoner", 300, -4.5, 0.1, -1.2, 166, 5335819)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -4.9, 0.1, -2.4, 16, 5335819)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -4.2, 0.1, -3.6, -66, 5335819)
	spawnMobile("dathomir", "dathomir_prisoner", 300, -4.5, 0.1, -4.8, 96, 5335819)
	spawnMobile("dathomir", "tough_dathomir_prisoner", 300, 4.5, 0.1, -2.2, 0, 5335818)
	spawnMobile("dathomir", "tough_dathomir_prisoner", 300, 4.5, 0.1, -3.6, 90, 5335818)
	spawnMobile("dathomir", "tough_dathomir_prisoner", 300, 3.0, 0.1, -5.6, -60, 5335818)
	spawnMobile("dathomir", "dathomir_prisoner", 300, 3.8, 0.1, 1.5, 0, 5335817)

	--main building

		--cellid 2665365 to 2665375

	spawnMobile("dathomir", "dark_trooper", 300, 20.8, 1.0, 10.5, 180, 2665365)
	spawnMobile("dathomir", "dark_trooper", 300, 16.0, 1.0, 10.5, 180, 2665365)
	spawnMobile("dathomir", "dark_trooper", 300, 18.1, 1.0, 5.5, 0, 2665365)
	spawnMobile("dathomir", "dark_trooper", 300, -15.9, 1.0, 8.2, 90, 2665365)
	spawnMobile("dathomir", "dark_trooper", 300, 2.5, 1.0, -15.5, 0, 2665365)
	spawnMobile("dathomir", "dark_trooper", 300, -2.5, 1.0, -15.5, 0, 2665365)
	spawnMobile("dathomir", "imperial_warrant_officer_ii", 300, -2.1, 2.0, 3.7, -45, 2665365)
	spawnMobile("dathomir", "dark_trooper", 300, -7.5, 1.0, -0.3, 90, 2665365)

	spawnMobile("dathomir", "nightsister_outcast", 600, 18.0, 1.0, 15.8, 0, 2665366)
	spawnMobile("dathomir", "dark_trooper", 300, 21.5, 1.0, 18.7, -90, 2665366)
	spawnMobile("dathomir", "dark_trooper", 300, 14.5, 1.0, 18.7, 90, 2665366)
	spawnMobile("dathomir", "dark_trooper", 300, 16.5, 1.0, 12.6, 0, 2665366)
	spawnMobile("dathomir", "dark_trooper", 300, 19.4, 1.0, 15.1, 0, 2665366)
	spawnMobile("dathomir", "warden_vinzel_heylon", 600, 16.8, 1.0, 21.0, -90, 2665366)

	spawnMobile("dathomir", "stormtrooper_colonel", 300, -18.0, 1.0, 19.9, 90, 2665367)

	spawnMobile("dathomir", "imprisoned_rebel_soldier", 600, 11.2, 1.0, -19.5, -147, 2665369)
	spawnMobile("dathomir", "dark_trooper", 300, 14.1, 1.0, -18.0, -90, 2665369)

	spawnMobile("dathomir", "imprisoned_jabba_employee", 300, 0, 1.0, -18.4, 0, 2665370)

	spawnMobile("dathomir", "dark_trooper", 300, -15.3, 1.0, -4.5, 90, 2665372)

	spawnMobile("dathomir", "dark_trooper", 300, -13.3, 7.0, -9.5, 180, 2665373)
	spawnMobile("dathomir", "dark_trooper", 300, -8.3, 7.0, -9.5, 180, 2665373)
	spawnMobile("dathomir", "imperial_warrant_officer_ii", 300, 3.4, 7.0, 0.0, 0, 2665373)
	spawnMobile("dathomir", "dark_trooper", 300, 8.9, 7.0, 1.0, 180, 2665373)
	spawnMobile("dathomir", "dark_trooper", 300, 12.0, 7.0, 1.0, 180, 2665373)

	spawnMobile("dathomir", "imperial_warrant_officer_i", 300, -11.1, 7.0, 6.1, 180, 2665374)

	spawnMobile("dathomir", "imperial_medic", 300, 14.0, 7.0, 11.7, 55, 2665375)

	--cave

	spawnMobile("dathomir", "cavern_spider", 300, -4.4, -9.8, -11.3, -43, 2635354)
	spawnMobile("dathomir", "cavern_spider_hunter", 300, 5.0, -11.5, -17.6, -60, 2635354)
	spawnMobile("dathomir", "cavern_spider", 300, -1.7, -10.6, -18.0, -35, 2635354)
	spawnMobile("dathomir", "cavern_spider_hunter", 300, 14.3, -18.8, -33.6, 4, 2635354)
	spawnMobile("dathomir", "cavern_spider_hunter", 300, 8.9, -21.9, -37.6, 103, 2635354)

	spawnMobile("dathomir", "cavern_spider_hunter", 300, -34.5, -45.6, -80.2, 50, 2635355)
	spawnMobile("dathomir", "cavern_spider_hunter", 300, -40.6, -48.2, -84.2, 57, 2635355)

	spawnMobile("dathomir", "cavern_spider_queen", 300, -5.3, -48.5, -170.6, -33, 2635357)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, -6.8, -48.5, -182.7, -33, 2635357)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, -4.3, -48.3, -181.5, -43, 2635357)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, -1.3, -48.4, -180.6, 133, 2635357)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, -1.3, -48.9, -177.2, 73, 2635357)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, -4.6, -48.6, -174.8, -13, 2635357)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, 9.6, -50.6, -158.3, -167, 2635357)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, 12.0, -51.0, -163.3, -133, 2635357)

	spawnMobile("dathomir", "giant_cavern_spider_recluse", 300, -74.3, -70.2, -194.3, 90, 2635361)

	spawnMobile("dathomir", "cavern_spider_queen", 300, 38.4, -81.6, -238.5, -45, 2635363)
	spawnMobile("dathomir", "cavern_spider_hunter", 300, 39.5, -79.1, -226.6, -33, 2635363)
	spawnMobile("dathomir", "cavern_spider_hunter", 300, 26.3, -79.0, -233.0, 0, 2635363)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, 62.3, -80.9, -229.7, -83, 2635363)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, 63.5, -81.9, -234.1, -83, 2635363)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, 59.8, -81.9, -238.3, -23, 2635363)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, 51.9, -79.5, -249.4, -43, 2635363)
	spawnMobile("dathomir", "cavern_spider_broodling", 300, 42.5, -79.3, -250.8, -23, 2635363)

	spawnMobile("dathomir", "reclusive_cavern_spider", 300, 29.6, -79.9, -267.1, -60, 2635365)
	spawnMobile("dathomir", "reclusive_cavern_spider_queen", 300, 21.6, -79.9, -265.0, -20, 2635365)
	spawnMobile("dathomir", "reclusive_cavern_spider", 300, 11.6, -79.9, -266.7, 60, 2635365)
	spawnMobile("dathomir", "giant_cavern_spider_recluse", 300, 28.2, -80.6, -282.6, -25, 2635365)

	spawnMobile("dathomir", "mutant_rancor", 300, -155.0, -113.0, -338.4, 75, 2635369)

end

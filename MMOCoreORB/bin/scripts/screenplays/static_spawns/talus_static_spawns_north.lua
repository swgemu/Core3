--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
TalusStaticSpawnsNorthScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TalusStaticSpawnsNorthScreenPlay",

	lootContainers = {
		1094899
		--9645503 = bugged container, enabling this container caused the entire screenplay to not work.

	},

	lootLevel = 14,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 700000},
				{group = "junk", chance = 7500000},
				{group = "rifles", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000}
			},
			lootChance = 8000000
		}
	},

	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("TalusStaticSpawnsNorthScreenPlay", true)

function TalusStaticSpawnsNorthScreenPlay:start()
	if (isZoneEnabled("talus")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function TalusStaticSpawnsNorthScreenPlay:spawnMobiles()

	--Crashed Transport (-2400,2033)
	local pNpc = spawnMobile("talus", "stormtrooper_squad_leader", 360, -2416.3, 28.3, 2034.3, 180, 0)
	self:setMoodString(pNpc, "npc_imperial")
	spawnMobile("talus", "stormtrooper_medic", 360, -2404.1, 27.2, 2036.8, 81, 0)
	spawnMobile("talus", "stormtrooper", 360, -2404.2, 27.3, 2031.2, 125, 0)
	spawnMobile("talus", "stormtrooper_commando", 360, -2403.9, 26.7, 2021.6, -90, 0)
	spawnMobile("talus", "stormtrooper_captain", 360, -2418.3, 28.4, 2034.8, 180, 0)
	spawnMobile("talus", "stormtrooper", 360, -2421.2, 28.3, 2028.2, 90, 0)
	spawnMobile("talus", "stormtrooper", 360, -2417.8, 27.6, 2022.3, 150, 0)
	spawnMobile("talus", "stormtrooper", 360, -2410.8, 27.2, 2014.5, 109, 0)
	spawnMobile("talus", "stormtrooper_medic", 360, -2411.6, 28.0, 2030.1, -165, 0)
	spawnMobile("talus", "stormtrooper_rifleman", 360, -2412.4, 27.1, 2021.7, -30, 0)
	spawnMobile("talus", "stormtrooper_rifleman", 360, -2419.8, 27.4, 2014.8, -125, 0)
	spawnMobile("talus", "stormtrooper", 360, -2398.3, 26.9, 2014.4, -15, 0)
	spawnMobile("talus", "stormtrooper", 360, -2392.4, 26.1, 2020.0, 45, 0)
	spawnMobile("talus", "stormtrooper", 360, -2389.6, 25.4, 2025.9, -22, 0)
	spawnMobile("talus", "stormtrooper_bombardier", 360, -2388.5, 24.7, 2032.9, 0, 0)
	spawnMobile("talus", "stormtrooper_bombardier", 360, -2379.8, 23.4, 2032.8, 0, 0)
	spawnMobile("talus", "stormtrooper", 360, -2364.2, 11.0, 2105.0, 40, 0)
	spawnMobile("talus", "stormtrooper", 360, -2369.2, 11.5, 2109.0, 40, 0)

	--Four Stones & Fire (-1832,1438)
	spawnMobile("talus", "aakuan_warder", 300, -1838.7, 7.5, 1437.7, 115, 0)
	spawnMobile("talus", "aakuan_keeper", 300, -1825.0, 8.9, 1425.7, 122, 0)
	spawnMobile("talus", "aakuan_keeper", 300, -1824.4, 7.9, 1442.6, 0, 0)
	--Bridge (-150,323)
	--Dath Tree (-695,156)
	spawnMobile("talus", "foaming_vynock", 300, -687.8, 44.3, 170.1, 45, 0)
	spawnMobile("talus", "foaming_vynock", 300, -699.9, 43.6, 174.7, -70, 0)
	spawnMobile("talus", "foaming_vynock", 300, -712.1, 42.7, 169.4, -60, 0)
	spawnMobile("talus", "foaming_vynock", 300, -714.6, 42.5, 152.3, 140, 0)
	spawnMobile("talus", "foaming_vynock", 300, -705.1, 43.2, 142.1, 60, 0)
	spawnMobile("talus", "foaming_vynock", 300, -690.8, 44.2, 141.7, 70, 0)
	spawnMobile("talus", "foaming_vynock", 300, -678.8, 44.8, 150.9, 30, 0)
	spawnMobile("talus", "foaming_vynock", 300, -680.9, 44.7, 160.6, 180, 0)
	spawnMobile("talus", "foaming_vynock", 300, -694.2, 43.9, 153.6, -130, 0)
	spawnMobile("talus", "foaming_vynock", 300, -705.8, 43.2, 155.6, -177, 0)
	spawnMobile("talus", "foaming_vynock", 300, -697.8, 43.7, 166.6, 108, 0)

	--Probe Droid (-2599,101)
	spawnMobile("talus", "rebel_commando", 300, -2601.8, 47.9, 101.0, 88, 0)
	spawnMobile("talus", "rebel_commando", 300, -2605.7, 45.1, 88.6, -48, 0)
	spawnMobile("talus", "rebel_commando", 300, -2609.7, 45.9, 97.7, 70, 0)
	spawnMobile("talus", "rebel_commando", 300, -2618.8, 42.7, 91.7, 68, 0)
	spawnMobile("talus", "rebel_commando", 300, -2613.2, 46.4, 114.5, 126, 0)

	--Ribcage (-4472,65)
	spawnMobile("talus", "decay_mite", 300, -4464.8, 17.6, 63.4, -123, 0)
	spawnMobile("talus", "decay_mite", 300, -4465.5, 19.2, 60.8, -123, 0)
	spawnMobile("talus", "decay_mite", 300, -4469.1, 20.5, 61.9, -63, 0)
	spawnMobile("talus", "decay_mite", 300, -4470.9, 22.1, 60.3, -43, 0)
	spawnMobile("talus", "decay_mite", 300, -4472.5, 23.6, 57.9, -163, 0)
	spawnMobile("talus", "decay_mite", 300, -4476.6, 22.9, 62.5, 63, 0)
	spawnMobile("talus", "decay_mite", 300, -4478.0, 21.3, 66.0, 53, 0)
	spawnMobile("talus", "decay_mite", 300, -4474.8, 17.4, 70.4, 135, 0)
	spawnMobile("talus", "decay_mite", 300, -4473.5, 14.0, 74.8, 13, 0)
	spawnMobile("talus", "decay_mite", 300, -4468.5, 12.3, 75.8, 113, 0)
	spawnMobile("talus", "decay_mite", 300, -4467.1, 12.2, 79.4, -163, 0)
	spawnMobile("talus", "decay_mite", 300, -4466.7, 17.2, 65.5, -98, 0)
	spawnMobile("talus", "decay_mite", 300, -4465.1, 14.7, 68.2, -63, 0)
	spawnMobile("talus", "decay_mite", 300, -4469.1, 14.5, 71.3, -143, 0)
	spawnMobile("talus", "decay_mite", 300, -4460.4, 13.5, 72.2, -133, 0)

	--statue head (-5040,116)
	spawnMobile("talus", "fed_dub_investigator", 300, -5040.2, 4.9, 113.2, -17, 0)

	--Debris (-6316,1253)
	spawnMobile("talus", "tortur_bull", 360, -6259.0, 7.8, 1272.6, 90, 0)
	spawnMobile("talus", "tortur_bull", 360, -6279.9, 7.8, 1256.0, 90, 0)
	spawnMobile("talus", "tortur", 360, -6283.3, 6.9, 1288.8, 90, 0)
	--Bones (-5855.3,1442)
	--Large Broken Tower (-5517,1064)
	spawnMobile("talus", "lost_aqualish_outrider", 360, -5512.1, 21.5, 1063.7, 87, 0)

	--Small Pillar + Red Haze (-5100,1271)
	spawnMobile("talus", "aakuan_anarchist", 360, -5096.5, 9.2, 1268.1, -55, 0)
	spawnMobile("talus", "aakuan_anarchist", 360, -5095.9, 9.1, 1272.2, -108, 0)
	--Bones (-4716,1131)
	--Broken Flora Harvester (-4350,1542)
	spawnMobile("talus", "vicious_huf_dun", 360, -4347.5, 59.5, 1546.1, -160, 0)

	--Bridge Struts & Skeletons (-3996,977)
	spawnMobile("talus", "foaming_vynock", 360, -4000.8, 1.4, 973.6, -58, 0)
	spawnMobile("talus", "foaming_vynock", 360, -4006.7, 0.2, 971.5, 18, 0)

	--Flag (-3460,1550)
	spawnMobile("talus", "aakuan_keeper", 360, -3456.1, 10.9, 1546.6, -45, 0)
	spawnMobile("talus", "aakuan_keeper", 360, -3463.7, 10.7, 1545.6, 28, 0)

	--Fishing (-3009,1941)
	spawnMobile("talus", "fed_dub_supporter", 360, -3009.7, 0.2, 1941.7, 84, 0)

	--AT-ST cabin (-2771,1568)
	spawnMobile("talus", "comm_operator", 360, -2774.0, 0.5, 1567.0, 55, 0)
	spawnMobile("talus", "comm_operator", 360, -2770.0, 0.9, 1563.0, 0, 0)

	--Red Fire (-1833,1437)
	spawnMobile("talus", "aakuan_keeper", 360, -1837.7, 7.8, 1433.8, 60, 0)
	spawnMobile("talus", "aakuan_keeper", 360, -1837.7, 7.4, 1441.0, 110, 0)
	spawnMobile("talus", "aakuan_keeper", 360, -1826.5, 8.1, 1438.1, -90, 0)

	--Gas Harvester (-1470,1231)
	spawnMobile("talus", "commoner_technician", 360, -1470.9, 29.1, 1230.9, 90, 0)
	spawnMobile("talus", "clipped_fynock", 300, -1454.1, 28.8, 1225.1, -60, 0)
	spawnMobile("talus", "clipped_fynock", 300, -1456.6, 28.8, 1228.1, -50, 0)
	spawnMobile("talus", "clipped_fynock", 300, -1453.1, 28.5, 1230.1, -90, 0)
	--Three Stones with campfire out (-1362,1060)
	--Bones (-1243,1496)
	spawnMobile("talus", "decay_mite", 300, -1243.0, 6.8, 1500.2, -148, 0)
	spawnMobile("talus", "decay_mite", 300, -1240.9, 7.7, 1595.0, -51, 0)

	--worship Stone (-861,1020)
	spawnMobile("talus", "aakuan_steward", 360, -858.2, 18.3, 1019.6, -98, 0)
	spawnMobile("talus", "aakuan_steward", 360, -865.0, 16.9, 1019.6, 82, 0)

	--Engine Debris (-563,1270)
	spawnMobile("talus", "imperial_probe_drone", 360, -564.8, 54.7, 1266.4, 5, 0)

	--Dath Tree (-55,980)
	spawnMobile("talus", "sludge_panther", 360, -71.0, 11.9, 982.6, 2, 0)

	--Tent and Skeletons (86,1581)
	spawnMobile("talus", "rotting_decay_mite_guard", 360, 82.6, 11.6, 1584.5, 80, 0)

	--Pillar (618,1100)
	spawnMobile("talus", "aakuan_sentinel", 360, 621.4, 41.2, 1098.0, -3, 0)
	--Broken Walls (1115,1489)
	--Imperial House and lookout (1712,1629)
	spawnMobile("talus", "imperial_private", 360, 1712.7, 30.1, 1629.8, -50, 0)
	spawnMobile("talus", "imperial_private", 360, 1740.1, 20.1, 1638.1, 70, 0)
	spawnMobile("talus", "imperial_trooper", 360, 1695.4, 53.6, 1639.0, -22, 0)
	spawnMobile("talus", "imperial_trooper", 360, 1673.7, 70.7, 1630.3, 48, 0)
	spawnMobile("talus", "imperial_trooper", 360, 1672.6, 67.5, 1647.2, 102, 0)
	spawnMobile("talus", "imperial_trooper", 360, 1710.6, 52.9, 1666.6, 142, 0)
	spawnMobile("talus", "imperial_trooper", 360, 1770.3, 7.1, 1649.6, 101, 0)
	spawnMobile("talus", "imperial_trooper", 360, 1779.9, 7.0, 1681.8, 126, 0)
	spawnMobile("talus", "imperial_trooper", 360, 1702.6, 21.1, 1601.0, -112, 0)
	spawnMobile("talus", "imperial_trooper", 360, -6.0, 0.7, -1.7, 0, 9505497)
	spawnMobile("talus", "imperial_pilot", 360, -1.0, 0.7, -6.9, -90, 9505498)
	spawnMobile("talus", "imperial_medic", 360, -2.2, 0.7, -2.0, 90, 9505499)
	spawnMobile("talus", "imperial_army_captain", 360, -2.2, 0.7, 4.3, 90, 9505500)

	--Debris (1711,783)
	spawnMobile("talus", "repugnant_dung_mite_crawler", 360, 1711.9, 6.5, 780.6, -78, 0)
	--Skull (2120,1272)
	--Small Shrine with Skulls (2470,787)
	spawnMobile("talus", "aakuan_keeper", 360, 2466.3, 34.2, 787.7, 106, 0)
	spawnMobile("talus", "aakuan_keeper", 360, 2472.9, 33.1, 791.7, -150, 0)
	spawnMobile("talus", "aakuan_champion", 360, 2469.4, 30.3, 810.6, 177, 0)

	--Imperial Watch Tower (3209,1262)
	spawnMobile("talus", "imperial_medic", 360, 3200.5, 6.3, 1261.9, -40, 0)
	spawnMobile("talus", "stormtrooper_sniper", 360, 3191.5, 5.1, 1269.0, -40, 0)
	spawnMobile("talus", "stormtrooper_sniper", 360, 3198.6, 5.3, 1274.0, -40, 0)
	spawnMobile("talus", "at_st", 720, 3202.0, 9.3, 1243.9, -40, 0)

	--Tall Odd Tree (3474,481)
	spawnMobile("talus", "ravenous_rasp", 360, 3480.1, 35.2, 481.4, -77, 0)

	--Bridge and Debris (5480,1085)
	spawnMobile("talus", "talus_liberation_party_loyalist", 360, 5486.8, 45.4, 1112.8, -36, 0)
	spawnMobile("talus", "talus_liberation_party_loyalist", 360, 5499.0, 44.4, 1081.8, 92, 0)
	spawnMobile("talus", "talus_liberation_party_fanatic", 360, 5477.0, 40.0, 1077.3, -32, 0)
	spawnMobile("talus", "talus_liberation_party_fanatic", 360, 5466.7, 40.0, 1076.4, -109, 0)
	spawnMobile("talus", "talus_liberation_party_activist", 360, 5484.3, 40.0, 1077.4, 66, 0)
	--Table (5413,2655)
	--Pillars Ruins (4974,3849)
	--Burning Rocks (4310,2563)
	spawnMobile("talus", "sleemo_vandal", 360, 4314.9, 48.0, 2565.8, -113, 0)
	--Monument in Lake (2445,2485)
	--Gateway (2338,2936)
	spawnMobile("talus", "talus_liberation_party_activist", 360, 2335.8, 38.7, 2933.4, 144, 0)
	spawnMobile("talus", "talus_liberation_party_activist", 360, 2341.2, 39.2, 2937.0, 144, 0)
	spawnMobile("talus", "talus_liberation_party_loyalist", 360, 2333.7, 39.7, 2943.7, 177, 0)

	--Stones (169,3409)
	spawnMobile("talus", "rot_mite", 300, 164.3, 73.2, 3408.4, 71, 0)
	spawnMobile("talus", "rot_mite", 300, 163.1, 73.5, 3402.7, 171, 0)
	spawnMobile("talus", "rot_mite", 300, 169.1, 73.5, 3400.2, -31, 0)
	spawnMobile("talus", "rot_mite", 300, 175.7, 72.3, 3412.2, 7, 0)

	--Aqualish Camp (-97,2610)
	spawnMobile("talus", "lost_aqualish_marshall", 360, -99.5, 72.4, 2616.3, 140, 0)
	spawnMobile("talus", "lost_aqualish_commando", 360, -92.2, 71.1, 2611.9, -118, 0)
	spawnMobile("talus", "lost_aqualish_warrior", 360, -95.5, 72.0, 2603.8, -20, 0)
	--Stone Pillars (-735,2033)
	--Broken Tree (-525,3790)
	spawnMobile("talus", "rot_mite", 300, -522.5, 51.9, 3795.8, 81, 0)
	spawnMobile("talus", "rot_mite", 300, -516.9, 51.7, 3796.0, 31, 0)
	spawnMobile("talus", "rot_mite", 300, -508.4, 50.9, 3790.2, 124, 0)
	spawnMobile("talus", "rot_mite", 300, -513.1, 50.3, 3780.8, -131, 0)
	spawnMobile("talus", "rot_mite", 300, -522.8, 50.4, 3780.3, -50, 0)
	spawnMobile("talus", "rot_mite", 300, -528.1, 50.1, 3778.3, 1, 0)
	spawnMobile("talus", "rot_mite", 300, -534.2, 51.0, 3783.8, 131, 0)
	spawnMobile("talus", "rot_mite", 300, -520.8, 51.5, 3789.1, 45, 0)
	spawnMobile("talus", "rot_mite", 300, -531.4, 51.8, 3793.4, -31, 0)
	--Creature Skull (-1117,3753)
	--Ruins (-1394,2117)
	--Old Communications Tower (-1652,3382)
	spawnMobile("talus", "imperial_probe_drone", 300, -1653.7, 115.1, 3383.9, 154, 0)
	--Rock Formation (-2042,2810)
	spawnMobile("talus", "imperial_sharpshooter", 300, -2033.9, 141.7, 2807.1, 75, 0)
	spawnMobile("talus", "imperial_sharpshooter", 300, -2040.6, 141.0, 2816.8, 0, 0)
	spawnMobile("talus", "imperial_sharpshooter", 300, -2050.3, 141.2, 2819.5, -55, 0)
	spawnMobile("talus", "imperial_sharpshooter", 300, -2050.5, 140.6, 2811.7, -125, 0)
	spawnMobile("talus", "imperial_sharpshooter", 300, -2044.1, 141.6, 2806.9, 180, 0)
	spawnMobile("talus", "imperial_sergeant_major", 300, -2041.2, 140.7, 2811.6, -175, 0)

	--Road/Trail north of Imperial Outpost (-2255,2467) to (-2059,2444)
	spawnMobile("talus", "imperial_first_lieutenant", 300, -2251.1, 66.7, 2487.0, -5, 0)
	spawnMobile("talus", "imperial_trooper", 300, -2251.3, 67.4, 2491.0, -5, 0)
	spawnMobile("talus", "imperial_trooper", 300, -2251.5, 68.0, 2495.0, -5, 0)
	spawnMobile("talus", "imperial_trooper", 300, -2251.7, 68.6, 2499.0, -5, 0)
	spawnMobile("talus", "imperial_trooper", 300, -2251.9, 69.1, 2503.0, -5, 0)
	spawnMobile("talus", "imperial_trooper", 300, -2252.1, 69.6, 2507.0, -5, 0)
	spawnMobile("talus", "imperial_trooper", 300, -2252.3, 70.0, 2511.0, -5, 0)
	--Broken Arch (-2988,3820)
	--Statue (-3246,3425)
	spawnMobile("talus", "sleemo_vandal", 300, -3248.9, 50.0, 3432.9, 175, 0)
	spawnMobile("talus", "sleemo_vandal", 300, -3242.6, 49.5, 3432.4, 75, 0)
	spawnMobile("talus", "sleemo_vandal", 300, -3241.8, 48.9, 3425.6, -95, 0)
	spawnMobile("talus", "sleemo_vandal", 300, -3245.5, 49.7, 3428.3, -145, 0)

	--Skeleton and Debris (-3394,2497)
	spawnMobile("talus", "scavenger", 300, -3394.8, 8.4, 2497.4, 105, 0)
	spawnMobile("talus", "scavenger", 300, -3391.3, 8.4, 2500.2, 180, 0)
	spawnMobile("talus", "scavenger", 300, -3397.8, 8.6, 2499.6, 55, 0)

	--Ruins (-3492,3697)
	spawnMobile("talus", "scavenger", 300, -3491.7, 40.5, 3697.5, 180, 0)
	spawnMobile("talus", "scavenger", 300, -3483.6, 39.9, 3700.0, 180, 0)

	--Creature Skeleton (-3482,3965)
	--Stones and Skull (-3710,2891)
	--Broken Bridge (-4025,3664)

	--Ruined Lookout Tower (-4381,2669)
	spawnMobile("talus", "scavenger", 300, -4384.1, 16.7, 2663.6, 12, 0)
	spawnMobile("talus", "scavenger", 300, -4379.1, 16.8, 2663.1, -33, 0)

	--Diseased Ruins & Mite Nest (-5117,3213)
	spawnMobile("talus", "giant_decay_mite_queen", 360, -5107.7, 19.6, 3215.1, -108, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5110.2, 19.2, 3214.0, -158, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5109.2, 18.8, 3210.4, 165, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5113.5, 19.9, 3220.9, -33, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5104.6, 20.7, 3221.9, 145, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5108.5, 20.8, 3225.0, -50, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5116.6, 20.1, 3224.8, -90, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5119.5, 18.8, 3216.5, -165, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5116.1, 18.4, 3211.4, 65, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5114.9, 17.7, 3204.9, 170, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5121.8, 17.2, 3205.7, -88, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5130.4, 16.1, 3202.6, -111, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5127.3, 16.0, 3199.7, 115, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5126.2, 19.7, 3228.4, -45, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5101.7, 19.6, 3211.4, -65, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5102.2, 18.6, 3204.6, -145, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5106.4, 17.8, 3201.0, -65, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5117.3, 16.5, 3197.5, -35, 0)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5119.3, 20.7, 3231.2, 175, 0)

	spawnMobile("talus", "giant_decay_mite_guardian", 300, -5117.8, 19.4, 3220.0, 135, 0)
	spawnMobile("talus", "giant_decay_mite_protector", 300, -5112.8, 18.4, 3209.4, 22, 0)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -5141.9, 18.9, 3233.1, -45, 0)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -5151.3, 16.6, 3222.0, -45, 0)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -5151.1, 14.6, 3205.4, -115, 0)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -5152.3, 15.5, 3213.9, 85, 0)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -5147.4, 20.8, 3253.3, -25, 0)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -5161.4, 18.4, 3238.1, 165, 0)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -5171.8, 14.1, 3215.8, 90, 0)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -5136.1, 12.7, 3180.4, 180, 0)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -5101.3, 15.9, 3184.2, 88, 0)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -5088.1, 19.2, 3201.6, 165, 0)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -5100.3, 22.8, 3235.4, 5, 0)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -5116.9, 22.5, 3244.1, -15, 0)

	spawnMobile("talus", "giant_decay_mite_harvester", 300, -5105.9, 25.3, 3258.8, -9, 0)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -5118.5, 25.5, 3269.7, 49, 0)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -5147.5, 21.4, 3259.0, -114, 0)

	--Diseased Debris (-5139,3706)
	spawnMobile("talus", "giant_decay_mite_harvester", 360, -5143.0, 35.4, 3699.2, -49, 0)
	spawnMobile("talus", "giant_decay_mite_harvester", 360, -5148.5, 37.6, 3708.2, 82, 0)
	spawnMobile("talus", "giant_decay_mite_harvester", 360, -5132.1, 37.3, 3710.6, -89, 0)

	--Skulls + Red Fire (-5098,2355)
	spawnMobile("talus", "aakuan_keeper", 360, -5098.9, 47.3, 2355.5, 75, 0)
	spawnMobile("talus", "aakuan_keeper", 360, -5098.3, 47.5, 2362.4, 75, 0)

	--Backbone (-5730,2856)
	--3 Stone Pillars w/ Stone on Top (-5694,4012)
	--3 stone Collumns w/ Force Stone on Top (-5400,4302)
	spawnMobile("talus", "aakuan_guardian", 360, -5399.7, 72.5, 4302.5, -46, 0)
	--Arch w/ Teeth (-5221,4597)
	--Small Stone Circle (-5100,4722)
	pNpc = spawnMobile("talus", "aakuan_follower", 360, -5099.2, 39.9, 4725.7, -173, 0)
	self:setMoodString(pNpc, "entertained")

	--Tie Bomber Debris (-5277,5055)
	spawnMobile("talus", "clipped_fynock", 300, -5284.4, 52.2, 5049.1, -4, 0)
	spawnMobile("talus", "clipped_fynock", 300, -5286.0, 53.5, 5063.4, 145, 0)
	spawnMobile("talus", "clipped_fynock", 300, -5265.7, 11.2, 5062.1, 174, 0)
	spawnMobile("talus", "clipped_fynock", 300, -5263.5, 10.4, 5046.0, -24, 0)

	--Rock Circle (-5672,5290)
	pNpc = spawnMobile("talus", "aakuan_sentinel", 300, -5673.5, 7.0, 5289.8, -73, 0)
	self:setMoodString(pNpc, "angry")

	--Smoldering Fire in a Skull (-5928,5652)
	pNpc = spawnMobile("talus", "aakuan_spice_guard", 300, -5926.9, 26.6, 5655.3, 169, 0)
	self:setMoodString(pNpc, "worried")
	--Rocks (-5997,5951)
	--Large Dead Tree & Skulls (-5476,5811)
	spawnMobile("talus", "female_roba", 300, -5466.8, 43.4, 5813.3, 180, 0)
	spawnMobile("talus", "female_roba", 300, -5459.9, 44.2, 5816.9, 180, 0)
	spawnMobile("talus", "male_roba", 300, -5458.6, 44.8, 5806.0, -90, 0)

	--Escape Pod & Skeletons (-4984,5753)
	spawnMobile("talus", "rot_mite", 300, -4988.6, 41.9, 5757.4, 81, 0)
	spawnMobile("talus", "rot_mite", 300, -4993.8, 41.2, 5749.9, 116, 0)
	spawnMobile("talus", "rot_mite", 300, -4990.1, 42.5, 5744.7, 41, 0)
	spawnMobile("talus", "rot_mite", 300, -4981.1, 44.5, 5744.7, -31, 0)

	--Broken Probe Droid (-4803,5165)
	spawnMobile("talus", "scavenger", 300, -4804.6, 14.8, 5165.8, 102, 0)

	--Geyser (-4596,5703)
	spawnMobile("talus", "guf_drolg", 300, -4578.9, 29.5, 5694.6, -105, 0)
	spawnMobile("talus", "guf_drolg_female", 300, -4590.0, 29.3, 5687.1, 45, 0)
	--Sunken Ruins (-4575,4356)
	--Bushes & Tree (-4452,4059)
	spawnMobile("talus", "percussive_rasp", 300, -4451.8, 5.4, 4054.8, -9, 0)
	--Rock Pillar + Green Flame & Smoke (-4150,5952)
	--Stone Pillar + Fire (-4085,5566)
	--Broken Gas Harvester + Debris (-4020,4623)
	spawnMobile("talus", "scavenger", 300, -4020.9, 30.2, 4619.2, 10, 0)
	spawnMobile("talus", "scavenger", 300, -4030.9, 30.6, 4628.1, 152, 0)
	--3 Spikes (-3920,4127)
	--Broken Stone Pillar (-3698,4394)
	--Statue Head (-3594,5675)
	--Scientist Camp + Old Jedi Monument (-3640,6332) loot container = 1094899
	spawnMobile("talus", "scientist", 1, -3630.9, 56.5, 6328.2, -52, 0)
	spawnMobile("talus", "scientist", 1, -3631.8, 56.8, 6335.7, -135, 0)
	spawnMobile("talus", "scientist", 1, -3642.4, 56.7, 6337.1, 180, 0)

	--Shipping containers (-3445,6184)
	spawnMobile("talus", "smuggler", 300, -3448.2, 43.3, 6186.0, 10, 0)
	spawnMobile("talus", "scavenger", 300, -3440.6, 42.5, 6182.3, 96, 0)
	spawnMobile("talus", "scavenger", 300, -3444.8, 43.8, 6174.0, 28, 0)
	spawnMobile("talus", "scavenger", 300, -3451.5, 44.1, 6181.7, 64, 0)
	--Skeleton on Rocks (-3171,5735)
	--Spaceship Debris (-3333,5170)
	spawnMobile("talus", "foaming_vynock", 300, -3330.5, 75.5, 5167.9, -28, 0)
	spawnMobile("talus", "foaming_vynock", 300, -3325.8, 75.0, 5171.1, -91, 0)
	spawnMobile("talus", "foaming_vynock", 300, -3336.1, 75.9, 5164.7, 48, 0)

	--AT-ST Wreckage + Skeleton (-3197,4757)
	spawnMobile("talus", "imperial_probe_drone", 300, -3194.3, 49.7, 4761.1, -120, 0)
	--Small Tree (-3090,4608)
	spawnMobile("talus", "song_rasp", 300, -3088.2, 28.4, 4605.9, -60, 0)
	--Giant Broken Tree Stump (-3244,4323)
	--Spring (-3230,4201) nothing there?? not 14.1 ??
	--Spaceship Wreckage in River (-2986,5040)
	--Small camp & skeleton (-1229,4344) loot container = 9645503 (enabling this container causes the entire screenplay to not work)
	spawnMobile("talus", "mire_marauder", 300, -1222.1, 40.9, 4345.6, -112, 0)

	--Statue (910,4640)
	spawnMobile("talus", "aakuan_warder", 300, 910.1, 80.5, 4640.1, 85, 0)
	--Tree & Skeletons (1638,5431)
	--Broken Wall (2811,5583)
	--Aqualish Fishing Spot (5348,4545)
	spawnMobile("talus", "lost_aqualish_scout", 300, 5348.2, 1.2, 4545.4, 32, 0)
	spawnMobile("talus", "lost_aqualish_scout", 300, 5342.9, 1.2, 4550.6, 32, 0)
	spawnMobile("talus", "lost_aqualish_captain", 300, 5353.8, 1.2, 4542.6, 32, 0)

	--2 Trees + Green Myst (5440,5584)
	spawnMobile("talus", "puss_covered_decay_mite_soldier", 300, 5443.8, 139.2, 5596.4, -153, 0)
	spawnMobile("talus", "sickly_decay_mite_queen", 600, 5436.2, 142.2, 5570.2, 0, 0)

end

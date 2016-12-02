NabooKerenScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NabooKerenScreenPlay",

	planet = "naboo",

	gcwMobs = {
		{"stormtrooper_black_hole", "rebel_gungan_grand_army_soldier", 1981.7,11.0,2184.7,162,0, "", ""},
		{"stormtrooper_black_hole", "rebel_gungan_grand_army_soldier", 1984.8,11.0,2185.6,165,0, "", ""},
		{"stormtrooper_black_hole_squad_leader", "rebel_gungan_war_chief", 1942.9,11.7,2329.8,-14,0, "", ""},
		{"stormtrooper_black_hole", "rebel_gungan_grand_army_soldier", 1935.8,12.0,2328.8,-17,0, "", ""},
		{"stormtrooper_black_hole", "rebel_gungan_grand_army_soldier", 1950.3,11.8,2333.0,-17,0, "", ""},
		{"dark_trooper", "rebel_trooper", 1958.2,12.0,2403.6,-102,0, "", ""},
		{"dark_trooper", "rebel_trooper", 1964.1,12.0,2375.3,-100,0, "", ""},
		{"naboo_police", "naboo_police", 1961.5,12.0,2454.2,35,0, "", ""},
		{"naboo_police", "naboo_police", 1968.4,12.0,2448.3,35,0, "", ""},
		{"stormtrooper", "rebel_gungan_guard", 2009.9,19.0,2536.1,120,0, "", ""},
		{"stormtrooper", "rebel_gungan_guard", 2012.9,19.0,2540.9,120,0, "", ""},
		{"stormtrooper_bombardier", "rebel_gungan_kaadu_rider", 2049.8,19.0,2561.6,-120,0, "", ""},
		{"scout_trooper", "rebel_scout", 2105.3,30.0,2597.9,-150,0, "", ""},
		{"scout_trooper", "rebel_scout", 2098.0,30.0,2601.6,-155,0, "", ""},
		{"scout_trooper", "rebel_scout", 1901.2,12.0,2611.8,-90,0, "", ""},
		{"scout_trooper", "rebel_scout", 1901.6,12.0,2618.6,-90,0, "", ""},
		{"naboo_police_chief", "naboo_police_chief", 1862.4,12.0,2543.0,-45,0, "", ""},
		{"naboo_police_officer", "naboo_police_officer", 1856.7,12.0,2538.1,-45,0, "", ""},
		{"stormtrooper", "rebel_gungan_guard", 1803.1,12.0,2516.6,0,0, "", ""},
		{"stormtrooper", "rebel_gungan_guard", 1810.2,12.0,2516.7,0,0, "", ""},
		{"stormtrooper_rifleman", "rebel_gungan_scout", 1685.7,12.0,2609.5,175,0, "", ""},
		{"stormtrooper_rifleman", "rebel_gungan_scout", 1686.0,12.0,2618.9,0,0, "", ""},
		{"dark_trooper", "rebel_trooper", 1802.0,12.5,2629.2,50,0, "", ""},
		{"dark_trooper", "rebel_trooper", 1772.1,12.5,2598.7,-132,0, "", ""},
		{"stormtrooper_sniper", "rebel_gungan_bomber", 1602.3,25.0,2697.0,-87,0, "", ""},
		{"stormtrooper_sniper", "rebel_gungan_bomber", 1607.5,25.0,2695.9,-168,0, "", ""},
		{"stormtrooper", "rebel_gungan_guard", 1528.0,25.0,2739.8,5,0, "", ""},
		{"stormtrooper", "rebel_gungan_guard", 1523.1,25.0,2741.6,0,0, "", ""},
		{"scout_trooper", "rebel_scout", 1572.7,25.0,2830.7,-90,0, "", ""},
		{"scout_trooper", "rebel_scout", 1572.5,25.0,2836.3,-90,0, "", ""},
		{"stormtrooper_sniper", "rebel_gungan_bomber", 1598.4,40.0,2830.5,90,0, "", ""},
		{"stormtrooper_black_hole_squad_leader", "rebel_gungan_war_chief", 1213.8,13.0,2768.2,90,0, "", ""},
		{"stormtrooper_black_hole", "rebel_gungan_grand_army_soldier", 1209.4,13.0,2785.8,-90,0, "", ""},
		{"stormtrooper_black_hole", "rebel_gungan_grand_army_soldier", 1209.5,13.0,2751.3,-90,0, "", ""},
		{"special_missions_engineer", "rebel_general", 1210.2,13.0,2768.3,-90,0, "", ""},
	},
}

registerScreenPlay("NabooKerenScreenPlay", true)

function NabooKerenScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnSceneObjects()
		self:spawnGcwMobiles()
	end
end

function NabooKerenScreenPlay:spawnSceneObjects()

	--outside starport
	spawnSceneObject(self.planet, "object/tangible/crafting/station/public_space_station.iff", 1437.02, 13, 2763.06, 0, math.rad(90) )
	spawnSceneObject(self.planet, "object/tangible/crafting/station/public_space_station.iff", 1436.71, 13, 2778.92, 0, math.rad(90) )
end

function NabooKerenScreenPlay:spawnMobiles()
	spawnMobile(self.planet, "gadget_specialist", 60, 1215.5, 13, 2741.1, 11, 0)

	--starport interior
	local pNpc = spawnMobile(self.planet, "chiss_female",60,55.2,-0.5,31.6,0,2125385)
	self:setMoodString(pNpc, "npc_sitting_table_eating")
	pNpc = spawnMobile(self.planet, "chiss_male",60,57.4,-0.5,33.4,-135,2125385)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile(self.planet, "chassis_dealer",60,5.5,0.6,67.4,-2,2125382)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile(self.planet, "trainer_shipwright",60,-0.5,0.6,67.2,180,2125382)
	self:setMoodString(pNpc, "neutral")

	--cantina
	pNpc = spawnMobile(self.planet, "bartender",60,3.6,-0.9,-2.5,163,5)
	self:setMoodString(pNpc, "conversation")

	--Guild Hall 1720 2613
	spawnMobile(self.planet, "trainer_artisan",0,0.0976721,1.13306,-13.6995,0,1396874)

	--Guild Hall/Theater
	spawnMobile(self.planet, "trainer_dancer",0,18.188,2.12871,53.8705,2,4045383)
	spawnMobile(self.planet, "trainer_entertainer",0,29.6396,2.12878,74.0291,270,4045383)
	spawnMobile(self.planet, "trainer_musician",0,21.7,2.1,76.2,180,4045383)
	spawnMobile(self.planet, "theater_manager",0,21.7887,2.12809,63.5017,3,4045383)
	spawnMobile(self.planet, "trainer_imagedesigner",0,-20.97,2.1287,74.23,180,4045384)

	--Guild Hall 1786 2547
	spawnMobile(self.planet, "trainer_architect",0,11,1.133,-14.5,0,1650543)
	spawnMobile(self.planet, "trainer_armorsmith",0,-15,1.133,0,88,1650542)
	spawnMobile(self.planet, "trainer_droidengineer",0,-11,1.13306,-13,0,1650545)
	spawnMobile(self.planet, "trainer_merchant",0,12,1.13306,6,180,1650541)
	spawnMobile(self.planet, "trainer_weaponsmith",0,-2.5,1.13306,-8.4,91,1650544)

	--Guild Hall 1851 2613
	spawnMobile(self.planet, "trainer_brawler",0,-11,1.13306,-12.5,0,1650535)
	spawnMobile(self.planet, "trainer_marksman",0,0,0,-13,0,1650534)
	spawnMobile(self.planet, "trainer_scout",0,-12.0327,1.13306,4.62955,179,1650532)
	spawnMobile(self.planet, "junk_dealer", 0, -14.5, 1.1, 2.9, 119, 1650532)

	--Med Center
	spawnMobile(self.planet, "trainer_combatmedic",0,27.2188,0.26,5.37779,76,1661366)
	spawnMobile(self.planet, "trainer_combatmedic",0,-17,0.26,9,180,1661370)
	spawnMobile(self.planet, "trainer_doctor",0,17.4,0.3,1,9,1661366)
	spawnMobile(self.planet, "trainer_doctor",0,-25.9,0.3,-3.2,173,1661370)
	spawnMobile(self.planet, "trainer_medic",0,14.1386,0.26,3.567,128,1661366)
	spawnMobile(self.planet, "trainer_medic",0,-16.956,0.26,1.559,24,1661370)

	--Outside
	spawnMobile(self.planet, "informant_npc_lvl_1",0,2030,12,2591,0,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,1959,12,2577,0,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,1818,12,2496,0,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,1890,12,2527,0,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,1926,12,2527,0,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,1835,12,2633,0,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,1847,12,2573,0,0)
	spawnMobile(self.planet, "informant_npc_lvl_1",0,1347,13,2671,0,0)
	spawnMobile(self.planet, "informant_npc_lvl_2",0,1279,13,2858,330,0)
	spawnMobile(self.planet, "trainer_architect",0,1533,25,2744,-93,0)
	spawnMobile(self.planet, "trainer_armorsmith",0,1890,12,2767,180,0)
	spawnMobile(self.planet, "trainer_artisan",0,1522,25,2781,180,0)
	spawnMobile(self.planet, "trainer_artisan",0,2003.71,12,2484.06,243,0)
	spawnMobile(self.planet, "trainer_brawler",0,1890,12,2725,0,0)
	spawnMobile(self.planet, "trainer_brawler",0,1537,25,2757,0,0)
	spawnMobile(self.planet, "trainer_carbine",0,1265.08,13,2677.88,9,0)
	spawnMobile(self.planet, "trainer_chef",0,1840,12,2672,180,0)
	spawnMobile(self.planet, "trainer_combatmedic",0,1927,12,2729.93,264,0)
	spawnMobile(self.planet, "trainer_dancer",0,1630.59,12,2574.54,99,0)
	spawnMobile(self.planet, "trainer_droidengineer",0,1966,12,2419,-64,0)
	spawnMobile(self.planet, "trainer_droidengineer",0,1627,12,2439,0,0)
	spawnMobile(self.planet, "trainer_entertainer",0,1246,13,2723,12,0)
	spawnMobile(self.planet, "trainer_entertainer",0,1520,25,2744,0,0)
	spawnMobile(self.planet, "trainer_entertainer",0,1727,12,2479,0,0)
	spawnMobile(self.planet, "trainer_entertainer",0,1772.77,12,2744.98,179,0)
	spawnMobile(self.planet, "trainer_imagedesigner",0,1253,13,2711,0,0)
	spawnMobile(self.planet, "trainer_marksman",0,1538,25,2751,180,0)
	spawnMobile(self.planet, "trainer_marksman",0,1992,12,2515,180,0)
	spawnMobile(self.planet, "trainer_medic",0,1982,12,2598,0,0)
	spawnMobile(self.planet, "trainer_medic",0,1541,25,2789,0,0)
	spawnMobile(self.planet, "trainer_medic",0,1784,12,2714,0,0)
	spawnMobile(self.planet, "trainer_merchant",0,1524,25,2782,37,0)
	spawnMobile(self.planet, "trainer_merchant",0,2005,12,2483,243,0)
	spawnMobile(self.planet, "trainer_pistol",0,1253,13,2686,180,0)
	spawnMobile(self.planet, "trainer_rifleman",0,1276,13,2685,73,0)
	spawnMobile(self.planet, "trainer_scout",0,1512.27,25,2754.94,111,0)
	spawnMobile(self.planet, "trainer_scout",0,1842.37,12,2709.61,134,0)
	spawnMobile(self.planet, "trainer_smuggler",0,1362.94,13,2833.96,82,0)
	spawnMobile(self.planet, "trainer_smuggler",0,1846,12,2772,31,0)
	spawnMobile(self.planet, "trainer_weaponsmith",0,1905,12,2767,180,0)
	spawnMobile(self.planet, "trainer_bountyhunter",0,2087,30,2575,180,0)
	spawnMobile(self.planet, "junk_dealer", 0, 1274.18, 13, 2787.07, -96, 0)
	pNpc = spawnMobile(self.planet, "junk_dealer", 0, 1242.11, 13, 2732.43, 48, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerFineryConvoTemplate")
	end
	pNpc = spawnMobile(self.planet, "junk_dealer", 0, 1286.34, 13, 2676.88, -166, 0)
	if pNpc ~= nil then
		AiAgent(pNpc):setConvoTemplate("junkDealerArmsConvoTemplate")
	end
	spawnMobile(self.planet, "junk_dealer", 0, 1372.26, 13, 2705.58, -173, 0)

	--newb grind starter spawns
	spawnMobile(self.planet, "gungan_hermit", 300, getRandomNumber(10) + 1360, 13.3, getRandomNumber(10) + 2941, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gungan_hermit", 300, getRandomNumber(10) + 1360, 13.3, getRandomNumber(10) + 2941, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gungan_hermit", 300, getRandomNumber(10) + 1360, 13.3, getRandomNumber(10) + 2941, getRandomNumber(360), 0)
	spawnMobile(self.planet, "gungan_hermit", 300, getRandomNumber(10) + 1360, 13.3, getRandomNumber(10) + 2941, getRandomNumber(360), 0)
	spawnMobile(self.planet, "flewt", 300, getRandomNumber(10) + 1216, 6.1, getRandomNumber(10) + 2878, getRandomNumber(360), 0)
	spawnMobile(self.planet, "flewt", 300, getRandomNumber(10) + 1216, 6.1, getRandomNumber(10) + 2878, getRandomNumber(360), 0)
	spawnMobile(self.planet, "flewt", 300, getRandomNumber(10) + 1216, 6.1, getRandomNumber(10) + 2878, getRandomNumber(360), 0)
	spawnMobile(self.planet, "flewt", 300, getRandomNumber(10) + 1216, 6.1, getRandomNumber(10) + 2878, getRandomNumber(360), 0)
	spawnMobile(self.planet, "flewt", 300, getRandomNumber(10) + 1216, 6.1, getRandomNumber(10) + 2878, getRandomNumber(360), 0)
	spawnMobile(self.planet, "chuba", 300, getRandomNumber(10) + 1328, 11.9, getRandomNumber(10) + 2604, getRandomNumber(360), 0)
	spawnMobile(self.planet, "chuba", 300, getRandomNumber(10) + 1328, 11.9, getRandomNumber(10) + 2604, getRandomNumber(360), 0)
	spawnMobile(self.planet, "chuba", 300, getRandomNumber(10) + 1328, 11.9, getRandomNumber(10) + 2604, getRandomNumber(360), 0)
	spawnMobile(self.planet, "chuba", 300, getRandomNumber(10) + 1328, 11.9, getRandomNumber(10) + 2604, getRandomNumber(360), 0)
	spawnMobile(self.planet, "chuba", 300, getRandomNumber(10) + 1328, 11.9, getRandomNumber(10) + 2604, getRandomNumber(360), 0)
end

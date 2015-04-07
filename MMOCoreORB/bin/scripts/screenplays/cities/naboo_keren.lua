NabooKerenScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NabooKerenScreenPlay"
}

registerScreenPlay("NabooKerenScreenPlay", true)

function NabooKerenScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function NabooKerenScreenPlay:spawnSceneObjects()
 
	-- Shuttleport A
    spawnSceneObject("naboo", "object/static/particle/particle_distant_ships.iff", 2047, 50, 2522, 0, 1, 0, 0, 0)
	-- Shuttleport B
    spawnSceneObject("naboo", "object/static/particle/particle_distant_ships.iff", 1567, 50, 2857, 0, 1, 0, 0, 0)   
	-- Starport
    spawnSceneObject("naboo", "object/static/particle/particle_distant_ships.iff", 1429, 50, 2770, 0, 1, 0, 0, 0)

end

function NabooKerenScreenPlay:spawnMobiles()

	--Anything dashed out will need to be added here and removed from spawn manager once the spawnMobiles command is extended.

	--Guild Hall 1720 2613
	spawnMobile("naboo", "trainer_artisan",0,0.0976721,1.13306,-13.6995,0,1396874)

	--Guild Hall/Theater
	spawnMobile("naboo", "trainer_dancer",0,18.188,2.12871,53.8705,2,4045383)
	spawnMobile("naboo", "trainer_entertainer",0,29.6396,2.12878,74.0291,270,4045383)
	spawnMobile("naboo", "trainer_musician",0,21.7887,2.12809,63.5017,3,4045383)
	spawnMobile("naboo", "trainer_imagedesigner",0,-20.97,2.1287,74.23,180,4045384)

	--Guild Hall 1786 2547
	spawnMobile("naboo", "trainer_architect",0,11,1.133,-14.5,0,1650543)
	spawnMobile("naboo", "trainer_armorsmith",0,-15,1.133,0,88,1650542)
	spawnMobile("naboo", "trainer_droidengineer",0,-11,1.13306,-13,0,1650545)
	spawnMobile("naboo", "trainer_merchant",0,12,1.13306,6,180,1650541)
	spawnMobile("naboo", "trainer_weaponsmith",0,-2.5,1.13306,-8.4,91,1650544)

	--Guild Hall 1851 2613
	spawnMobile("naboo", "trainer_brawler",0,-11,1.13306,-12.5,0,1650535)
	spawnMobile("naboo", "trainer_marksman",0,0,0,-13,0,1650534)
	spawnMobile("naboo", "trainer_scout",0,-12.0327,1.13306,4.62955,179,1650532)

	--Med Center
	spawnMobile("naboo", "trainer_combatmedic",0,27.2188,0.26,5.37779,76,1661366)
	spawnMobile("naboo", "trainer_combatmedic",0,-17,0.26,9,180,1661370)
	spawnMobile("naboo", "trainer_doctor",0,17.4,0.3,1,9,1661366)
	spawnMobile("naboo", "trainer_doctor",0,-25.9,0.3,-3.2,173,1661370)
	spawnMobile("naboo", "trainer_medic",0,14.1386,0.26,3.567,128,1661366)
	spawnMobile("naboo", "trainer_medic",0,-16.956,0.26,1.559,24,1661370)

	--Outside
	spawnMobile("naboo", "informant_npc_lvl_1",0,2030,12,2591,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,1959,12,2577,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,1818,12,2496,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,1890,12,2527,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,1926,12,2527,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,1835,12,2633,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,1847,12,2573,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,1347,13,2671,0,0)
	spawnMobile("naboo", "informant_npc_lvl_2",0,1279,13,2858,330,0)
	--{"junk_dealer",0,1371.6,13,2705.3,177,0, "", "",JUNKGENERIC,JUNKCONVGENERIC},
	spawnMobile("naboo", "trainer_architect",0,1533,25,2744,-93,0)
	spawnMobile("naboo", "trainer_armorsmith",0,1890,12,2767,180,0)
	spawnMobile("naboo", "trainer_artisan",0,1522,25,2781,180,0)
	spawnMobile("naboo", "trainer_artisan",0,2003.71,12,2484.06,243,0)
	spawnMobile("naboo", "trainer_brawler",0,1890,12,2725,0,0)
	spawnMobile("naboo", "trainer_brawler",0,1537,25,2757,0,0)
	spawnMobile("naboo", "trainer_carbine",0,1265.08,13,2677.88,9,0)
	spawnMobile("naboo", "trainer_chef",0,1840,12,2672,180,0)
	spawnMobile("naboo", "trainer_combatmedic",0,1927,12,2729.93,264,0)
	spawnMobile("naboo", "trainer_dancer",0,1630.59,12,2574.54,99,0)
	spawnMobile("naboo", "trainer_droidengineer",0,1966,12,2419,-64,0)
	spawnMobile("naboo", "trainer_droidengineer",0,1627,12,2439,0,0)
	spawnMobile("naboo", "trainer_entertainer",0,1246,13,2723,12,0)
	spawnMobile("naboo", "trainer_entertainer",0,1520,25,2744,0,0)
	spawnMobile("naboo", "trainer_entertainer",0,1727,12,2479,0,0)
	spawnMobile("naboo", "trainer_entertainer",0,1772.77,12,2744.98,179,0)
	spawnMobile("naboo", "trainer_imagedesigner",0,1253,13,2711,0,0)
	spawnMobile("naboo", "trainer_marksman",0,1538,25,2751,180,0)
	spawnMobile("naboo", "trainer_marksman",0,1992,12,2515,180,0)
	spawnMobile("naboo", "trainer_medic",0,1982,12,2598,0,0)
	spawnMobile("naboo", "trainer_medic",0,1541,25,2789,0,0)
	spawnMobile("naboo", "trainer_medic",0,1784,12,2714,0,0)
	spawnMobile("naboo", "trainer_merchant",0,1524,25,2782,37,0)
	spawnMobile("naboo", "trainer_merchant",0,2005,12,2483,243,0)
	spawnMobile("naboo", "trainer_pistol",0,1253,13,2686,180,0)
	spawnMobile("naboo", "trainer_rifleman",0,1276,13,2685,73,0)
	spawnMobile("naboo", "trainer_scout",0,1512.27,25,2754.94,111,0)
	spawnMobile("naboo", "trainer_scout",0,1842.37,12,2709.61,134,0)
	--{"trainer_shipwright",0,1352,13,2768,141,0, "", "a shipwright trainer"},
	spawnMobile("naboo", "trainer_smuggler",0,1362.94,13,2833.96,82,0)
	spawnMobile("naboo", "trainer_smuggler",0,1846,12,2772,31,0)
	spawnMobile("naboo", "trainer_weaponsmith",0,1905,12,2767,180,0)
	spawnMobile("naboo", "trainer_bountyhunter",0,2087,30,2575,180,0)
end

DWB = ScreenPlay:new {
	numberOfActs = 1
}

--   Set to 1 for debug messages  -
TEST = 0

--------------------------------------------------------------
--   TODO List                                               -
--------------------------------------------------------------
--[[
* Set customization vars for armor so it's colored
* Fix Jetpack Z, spawn timer and auto-mount
* Make Voice Recognition Terminal work
* Make debris spawn again once the blastromech functionality works
* Make rebel sidequest's target npc send proper parameter message:
	code is there, but not sending for some reason
* Make Haldo auto-attack first and only conversible after some damage done:
	code is there, but neither forcePeace() nor updating the optionsBitmask to allow conversaton works
* Make DE10, Executioner's Hack and Mandalorian Wine Schematics work
* Add working lootable Data Storage Units:
	Using crafter name once it is changed to Origin Object (anyone else hat EA's Origin?)
* Add Ventilation Quest
* Make Advanced Rebreather, Industrial Battery (cleaned and uncleaned) and Alum Sickness Medicine No-Trade
* Make mobs in crafting rooms despawn after the crafting timer runs out
]]

-- Unused messages:
--[[
ventilation_repair	Alum Mine ventilation system is now operational.
repair_failed	Mission Failure: The droid was destroyed and the ventilation system is still off.
protect_tools	Protect the droid while it picks up tools needed to repair the ventilation system.
protect_fix	Protect the droid while it conducts repairs on the ventilation system.
entrance_denied	This door is locked. Perhaps you should seek the advice of someone knowledgeable about the Mandalorians on how to enter this base.
allum_warning	Environmental protection is required beyond this point due to high levels of alum gas.
]]

--------------------------------------------------------------
--   Spawn Map for conditionally spawned Creatures           -
--------------------------------------------------------------
specialSpawnMapDWB = {
	--[[according to a bug report these spawned at the other door pre-cu
	rageon_vart = {"rageon_vart", 0, -84.8, -20, -25.7, -114, 5996323},
	rageon_vart_assist1 = {"death_watch_bloodguard", 0, -84.8, -20, -25.7, -114, 5996323},
	rageon_vart_assist2 = {"death_watch_bloodguard", 0, -84.8, -20, -25.7, -114, 5996323},]]
	rageon_vart = {"rageon_vart", 0, -114.3, -20, -25.7, 108, 5996323},
	rageon_vart_assist1 = {"death_watch_bloodguard", 0, -114.3, -20, -25.7, 108, 5996323},
	rageon_vart_assist2 = {"death_watch_bloodguard", 0, -114.3, -20, -25.7, 108, 5996323},
	--[[according to a bug report these spawned at the other door pre-cu
	klin_nif = {"klin_nif", 0, -44.9, -32, -99.4, 56, 5996331},
	klin_nif_assist1 = {"death_watch_bloodguard", 0, -44.9, -32, -99.4, 56, 5996331},
	klin_nif_assist2 = {"death_watch_bloodguard", 0, -44.9, -32, -99.4, 56, 5996331},]]
	klin_nif = {"klin_nif", 0, -9.9, -32, -100.5, -47, 5996331},
	klin_nif_assist1 = {"death_watch_bloodguard", 0, -9.9, -32, -100.5, -47, 5996331},
	klin_nif_assist2 = {"death_watch_bloodguard", 0, -9.9, -32, -100.5, -47, 5996331},
	fenri_dalso = {"fenri_dalso", 0, 25.8, -60, -172.1, -9, 5996346},
	fenri_dalso_add1 = {"death_watch_wraith", 0, 26.0, -60, -171.1, 0, 5996346},
	fenri_dalso_add2 = {"death_watch_s_battle_droid", 0, 24.9, -60, -174.0, -5, 5996346},
	fenri_dalso_add3 = {"death_watch_s_battle_droid", 0, 27.3, -60, -173.7, -9, 5996346},
	fenri_dalso_add4 = {"death_watch_wraith", 0, 25.8, -60, -173.7, 0, 5996346},
	fenri_dalso_assist1 = {"death_watch_wraith", 0, 25.8, -60, -172.1, -9, 5996346},
	fenri_dalso_assist2 = {"death_watch_wraith", 0, 25.8, -60, -172.1, -9, 5996346},
	haldo1 = {"mand_bunker_crazed_miner", 0, -47.6,-59.8,-123.2,-26,5996362},
	haldo2 = {"mand_bunker_crazed_miner", 0, -178.7,-60.1,-147.9,12,5996369},
	haldo3 = {"mand_bunker_crazed_miner", 0, -185,-60.4,-250.5,-138,5996376},
	lootbox1mob1 = {"death_watch_s_battle_droid", 0, 2.8, -12, 31.8, -120, 5996318},
	lootbox2mob1 = {"death_watch_s_battle_droid", 0, 7.2, -31.9, -94.5, -8, 5996337},
	lootbox3mob1 = 	{"death_watch_ghost", 0, -0.6, -32, -39.9, 54, 5996335},
	lootbox3mob2 = {"death_watch_ghost", 0, 5.2, -32, -40.6, -29, 5996335},
	jetpackdroid = {"r3", 1, -266.7, -50.0, -85.0, 101, 5996370},
	tailordroid = {"r3", 1, -143.1, -60.0, -74.3, 33, 5996368},
	armorsmithdroid = {"r3", 1, -245.2, -60.0, -244.4, -42, 5996374},
	droidengineerdroid = {"r3", 1, -235.4, -40.0, -84.7, 21, 5996370},
	entrance1 = {"death_watch_battle_droid", 0, -31.9, -12.0, -3.7, 121, 5996315},
	entrance2 = {"death_watch_battle_droid", 0, -32.5, -12.0, -8.1, 76, 5996315}, 
	tailorattack1 = {"death_watch_s_battle_droid", 0,-151.8, -60.0, -83.9, 30, 5996368},
	tailorattack2 = {"death_watch_wraith", 0, -142.5, -60.0, -93.7, -12, 5996368},
	tailorattack3 = {"death_watch_ghost", 0,-159.3, -60.0, -92.5, 23, 5996368},
	tailorattack4 = {"death_watch_bloodguard", 0,-159.5, -60.0, -81.1, 101, 5996368},
	armorattack1 = {"death_watch_s_battle_droid", 0,-245.2, -59.9, -233.6, 176, 5996374},
	armorattack2 = {"death_watch_wraith", 0, -238.9, -60.0, -236.4, -127, 5996374},
	armorattack3 = {"death_watch_ghost", 0,-255.8, -60.0, -239.4, 81, 5996374},
	armorattack4 = {"death_watch_bloodguard", 0,-242.5, -59.9, -227.9, -150, 5996374},
	jetpackattack1 = {"death_watch_s_battle_droid", 0,-252.0, -50.0, -88.5, -116, 5996370},
	jetpackattack2 = {"death_watch_wraith", 0, -255.8, -50.0, -89.4, -34, 5996370},
	jetpackattack3 = {"death_watch_ghost", 0,-252.1, -50.0, -95.6, -13, 5996370},
	jetpackattack4 = {"death_watch_bloodguard", 0,-242.4, -50.0, -88.4, -116, 5996370},
	droidengineerattack1 = {"death_watch_s_battle_droid", 0,-248.6, -40.0, -90.0, 84, 5996370},
	droidengineerattack2 = {"death_watch_wraith", 0, -241.9, -40.0, -95.8, 23, 5996370},
	droidengineerattack3 = {"death_watch_ghost", 0,-249.1, -40.0, -85.1, 114, 5996370},
	droidengineerattack4 = {"death_watch_bloodguard", 0,-254.9, -40.0, -92.7, -130, 5996370},
}

--------------------------------------------------------------
--   Spawn Map for respawning static Creatures               -
--------------------------------------------------------------
spawnMapDWB = 	{
	{"death_watch_overlord", 0, 118, -64, -94, -135, 5996349},
	{"death_watch_s_battle_droid", 240, 110, -64, -92, 150, 5996349},
	{"death_watch_ghost", 240, 116, -64, -101, -156, 5996349},
	{"death_watch_wraith", 240, 113, -64, -100.7, -36, 5996349},
	{"blastromech", 240, 98, -64, -132, -90, 5996348},
	{"death_watch_s_battle_droid", 240, 22.1, -64, -97, 110, 5996347},
	{"death_watch_wraith", 240, 22.6, -64, -111.1, 128, 5996347},
	{"death_watch_battle_droid", 240, 40.2, -64, -154.6, -71, 5996347},
	{"death_watch_battle_droid", 240, 39.5, -64, -147.9, -116, 5996347},
	{"death_watch_s_battle_droid", 240, 57, -64, -138.4, 50, 5996347},
	{"death_watch_black_sun_assassin", 240, 50.2, -64, -123.7, -73, 5996347},
	{"death_watch_s_battle_droid", 240, 13.7, -54.8, -158.5, 169, 5996345},
	{"death_watch_s_battle_droid", 240, 51.7, -52.0, -130.2, -42, 5996338},
	{"death_watch_bloodguard", 240, 30.2, -52.0, -116.9, 171, 5996338},
	{"death_watch_wraith", 240, 30.1, -42, -103.1, -77, 5996338},
	{"death_watch_bloodguard", 240, 32.5, -42.0, -111.6, 65, 5996338},
	{"death_watch_bloodguard", 240, 36.3, -32.0, -107.3, -56, 5996338},
	{"death_watch_battle_droid", 240, 40.2, -32, -112.6, 2, 5996338},
	{"death_watch_battle_droid", 240, 46.6, -32, -111.8, 74, 5996338},
	{"death_watch_wraith", 240, 54.2, -32, -103.9, -82, 5996338},
	{"death_watch_battle_droid", 240, 71.4, -32, -101.3, -86, 5996339},
	{"death_watch_s_battle_droid", 240, 70.3, -32.0, -87.5, -116, 5996340},
	{"death_watch_wraith", 240, 45.5, -32, -89.5, -100, 5996340},
	{"death_watch_s_battle_droid", 240, 46.1, -32.0, -65.0, 53, 5996340},
	{"death_watch_wraith", 240, 71.3, -32, -64.5, -126, 5996340},
	{"death_watch_battle_droid", 240, 46.2, -32, -52.1, -107, 5996341},
	{"death_watch_battle_droid", 240, 42.0, -32, -51.0, 114, 5996341},
	{"death_watch_bloodguard", 240, 92.9, -32.0, -96, -127, 5996342},
	{"death_watch_battle_droid", 240, 95.5, -32, -88.9, 13, 5996342},
	{"death_watch_wraith", 240, 88.2, -32, -85.2, -55, 5996342},
	{"death_watch_bloodguard", 240, 89.4, -32.0, -60.1, 71, 5996343},
	{"death_watch_black_sun_henchman", 240, 89.6, -32, -64.7, 43, 5996343},
	{"death_watch_black_sun_guard", 240, 93.5, -32, -59, -119, 5996343},
	{"death_watch_s_battle_droid", 240, 112, -32.0, -70.2, 178, 5996344},
	{"death_watch_ghost", 240, 109.9, -32, -83.3, 134, 5996344},
	{"death_watch_wraith", 240, 113.5, -32, -83.9, -146, 5996344},
	{"death_watch_s_battle_droid", 240, 6.4, -31.9, -89, -9, 5996337},
	{"death_watch_s_battle_droid", 240, 5.9, -29.8, -66.6, -1, 5996336},
	{"death_watch_wraith", 240, 36.5, -28, -56.7, -154, 5996336},
	{"death_watch_wraith", 240, 36.0, -20, -92.2, -121, 5996336},
	{"death_watch_battle_droid", 240, 24.6, -20, -91.5, -39, 5996336},
	{"death_watch_battle_droid", 240, 20.7, -20, -80.4, -65, 5996332},
	{"death_watch_s_battle_droid", 240, 24.2, -20, -32.3, -175, 5996333},
	{"death_watch_ghost", 240, 25.9, -20, -37.7, -158, 5996333},
	{"death_watch_wraith", 240, 21.5, -20, -38.3, 95, 5996333},
	{"death_watch_battle_droid", 240, -2.5, -20, -58.9, 178, 5996332},
	{"death_watch_bloodguard", 240, -4.0, -20.0, -46.5, -7, 5996330},
	{"death_watch_battle_droid", 240, -26.5, -20, -41.2, -90, 5996330},
	{"death_watch_battle_droid", 240, -57.4, -20, -40.8, -89, 5996330},
	{"death_watch_s_battle_droid", 240, -77.8, -20, -41.1, 103, 5996330},
	{"death_watch_wraith", 240, -4.3, -24, -113.5, -15, 5996334},
	{"death_watch_wraith", 240, -38.3, -32, -113, -92, 5996334},
	{"death_watch_s_battle_droid", 240, -58.5, -32, -118.7, 10, 5996334},
	{"death_watch_s_battle_droid", 240, -44.7, -32, -99.6, 41, 5996331},
	{"death_watch_s_battle_droid", 240, -11.4, -32, -99.0, -23, 5996331},
	{"death_watch_s_battle_droid", 240, -12.7, -32, -56.7, -166, 5996331},
	{"death_watch_wraith", 240, 4.3, -32, -32.1, -31, 5996335},
	{"death_watch_bloodguard", 240, -1.4, -32.0, -34.5, 83, 5996335},
	{"death_watch_black_sun_henchman", 240, -16.1, -12.0, 8.8, -37, 5996316},
	{"death_watch_black_sun_thug", 240, -15.1, -12.0, 13.5, -163, 5996316},
	{"death_watch_black_sun_guard", 240, -1.3, -12, 28.4, 22, 5996318},
	{"death_watch_black_sun_assassin", 240, 0.6, -12, 34.0, -80, 5996318},
	{"death_watch_s_battle_droid", 240, -57.1, -20, 27.8, -121, 5996319},
	{"death_watch_black_sun_henchman", 240, -62.1, -20, 25.1, -63, 5996319},
	{"death_watch_black_sun_assassin", 240, -67.3, -20, 35.6, 131, 5996319},
	{"death_watch_s_battle_droid", 240, -76.9, -20, 51.6, 82, 5996320},
	{"death_watch_battle_droid", 240, -72.4, -20.0, 55.5, -69, 5996320},
	{"death_watch_bloodguard", 240, -75, -20, 58.6, -165, 5996320},
	{"death_watch_battle_droid", 240, -70.2, -20.0, 11.0, -123, 5996321},
	{"death_watch_battle_droid", 240, -77.0, -20.0, 10.0, 127, 5996321},
	{"death_watch_battle_droid", 240, -77.6, -20.0, -8.2, 61, 5996321},
	{"death_watch_battle_droid", 240, -70.8, -20.0, -6.6, -20, 5996321},
	{"death_watch_black_sun_guard", 240, -79, -20, -24.8, -102, 5996322},
	{"death_watch_black_sun_thug", 240, -92.5, -20, -28.3, -37, 5996323},
	{"death_watch_black_sun_assassin", 240, -98.2, -20, -25.8, 114, 5996323},
	{"death_watch_black_sun_henchman", 240, -112.6, -20, -53.3, -57, 5996323},
	{"death_watch_wraith", 240, -126, -20, -49.2, -164, 5996325},
	{"death_watch_bloodguard", 240, -126, -20, -55.2, 55, 5996325},
	{"death_watch_battle_droid", 240, -129.6, -20, -53.0, 37, 5996325},
	{"death_watch_black_sun_guard", 240, -125.9, -20, -28.1, 52, 5996324},
	{"death_watch_bloodguard", 240, -127.9, -20, -22.5, 66, 5996324},
	{"death_watch_battle_droid", 240, -124.8, -20, -21.8, 136, 5996324},
	{"death_watch_s_battle_droid", 240, -59.5, -20, -52.4, -97, 5996326},
	{"death_watch_black_sun_thug", 240, -59.8, -20, -69.5, -155, 5996327},
	{"death_watch_black_sun_assassin", 240, -65.5, -20, -78.7, 58, 5996327},
	{"death_watch_black_sun_henchman", 240, -56.9, -20, -74.4, 48, 5996327},
	{"death_watch_battle_droid", 240, -72.2, -20, -98.8, -59, 5996326},
	{"death_watch_battle_droid", 240, -73.9, -20, -90.8, -162, 5996326},
	{"death_watch_battle_droid", 240, -91.8, -20, -81.7, 31, 5996326},
	{"death_watch_battle_droid", 240, -85.8, -20, -81.9, 118, 5996326},
	{"death_watch_black_sun_guard", 240, -92.6, -20, -94.8, 54, 5996326},
	{"death_watch_bloodguard", 240, -103, -20, -100.4, -154, 5996328},
	{"death_watch_s_battle_droid", 240, -114.3, -20, -95.3, -77, 5996328},
	{"death_watch_black_sun_henchman", 240, -110.2, -20, -91.9, 56, 5996328},
	
	{"death_watch_black_sun_thug", 240, -93.5, -20, -114.7, 21, 5996329},
	{"death_watch_bloodguard", 240, -82.3, -20, -112.1, -50, 5996329},
	{"death_watch_black_sun_guard", 240, -38, -20, -46.3, 12, 5996330},
	{"death_watch_scientist", 240, 20.9, -20, -55.8, 121, 5996332},
	{"death_watch_scientist", 240, 5, -22, -74.2, 65, 5996332},
	{"death_watch_scientist", 240, -1.3, -32, -79.8, 90, 5996337},
	{"death_watch_scientist", 240, 15.8, -32, -94.5, -109, 5996337},
	{"death_watch_s_battle_droid", 240, -7.8, -52, -143.3, 159, 5996345},
	{"death_watch_s_battle_droid", 240, -21.2, -52, -156.9, 19, 5996378},
	{"death_watch_s_battle_droid", 240, -26.3, -52, -149.1, 129, 5996378},
	{"death_watch_battle_droid", 240, -28.9, -52, -161.1, 111, 5996378},
	{"death_watch_battle_droid", 240, -16.7, -52, -168.4, -5, 5996378},
	{"death_watch_battle_droid", 240, -9.6, -52, -153.4, -25, 5996378},
	
	{"death_watch_wraith", 240, -11.5, -60.3, -293.4, -6, 5996354},
	{"death_watch_s_battle_droid", 240, -8.2, -60, -229.9, -42, 5996354},
	{"death_watch_s_battle_droid", 240, -43.8, -59.8, -296.8, 86, 5996356},
	{"death_watch_ghost", 240, -90.4, -59.8, -376.2, -31, 5996357},
	{"death_watch_bloodguard", 240, -97.2, -59.8, -374.0, 10, 5996357},
	{"death_watch_overlord_mines", 240, -127.1, -59.7, -379.2, 22, 5996357},
	{"death_watch_s_battle_droid", 240, -122.3, -60.1, -376.4, 40, 5996357},
	{"death_watch_s_battle_droid", 240, -128.3, -60.0, -370.1, 133, 5996357},
	{"death_watch_s_battle_droid", 240, -121.8, -59.8, -362.7, -162, 5996357}, 
	
	{"death_watch_battle_droid", 240, -223.6, -60.1, -217.0, -160, 5996373},
	{"death_watch_wraith", 240, -185.1, -59.8, -217.1, -93, 5996375},
	{"death_watch_s_battle_droid", 240, -178.1, -59.8, -217.0, 86, 5996375},
	
	{"death_watch_mine_rat", 240, -181.0, -60.3, -231.9, 108, 5996376},
	{"death_watch_mine_rat", 240, -172.7, -60.0, -237.9, -16, 5996376},
	{"death_watch_wraith", 240, -159.7, -59.7, -229.1, -141, 5996376},
	{"death_watch_mine_rat", 240, -159.9, -59.9, -243.6, -82, 5996376},
	{"death_watch_mine_rat", 240, -170.9, -60.0, -246.8, -19, 5996376},
	{"death_watch_mine_rat", 240, -183.0, -60.5, -237.7, 50, 5996376},
	{"death_watch_s_battle_droid", 240, -185.6, -60.0, -244.1, 110, 5996376},
	{"miner", 240, -183.4, -60.2, -257.1, -72, 5996376},
	{"death_watch_mine_rat", 240, -167.1, -60.5, -256.3, -70, 5996376},
	{"death_watch_mine_rat", 240, -168.5, -59.8, -264.2, -152, 5996376},
	{"death_watch_mine_rat", 240, -177.8, -60.2, -259.9, 19, 5996376},
	
	{"death_watch_ghost", 240, -174.0, -59.8, -276.2, 0, 5996377},
	{"death_watch_s_battle_droid", 240, -173.9, -59.8, -296.8, 178, 5996377},
	{"death_watch_ghost", 240, -174.2, -59.8, -316.7, 87, 5996377},
	
	{"death_watch_mine_rat", 240, -156.6, -60.2, -312.6, -110, 5996357},
	{"death_watch_mine_rat", 240, -147.3, -60.2, -319.7, -74, 5996357},
	{"death_watch_mine_rat", 240, -129.5, -60.1, -318.3, 19, 5996357},
	{"death_watch_mine_rat", 240, -130.7, -60.0, -339.8, -22, 5996357},
	{"miner", 240, -124.9, -59.8, -305.2, -156, 5996357},
	{"miner", 240, -125.7, -60.0, -350.2, 1, 5996357},
	
	{"death_watch_mine_rat", 240, -109.3, -59.5, -375.7, 103, 5996357},
	{"death_watch_battle_droid", 240, -98.6, -59.7, -360.2, 17, 5996357},
	{"death_watch_battle_droid", 240, -99.1, -59.9, -339.2, 30, 5996357},
	{"death_watch_battle_droid", 240, -87.5, -59.4, -331.1, -10, 5996357},
	
	{"death_watch_s_battle_droid", 240, -94.2, -59.8, -216.5, 175, 5996359},
	{"death_watch_s_battle_droid", 240, -80, -59.8, -203.5, 179, 5996358},
	{"miner", 240, -60.2, -60.1, -178.6, -112, 5996352},
	{"miner", 240, -42.2, -60.0, -172.8, 10, 5996352},
	{"miner", 240, -22.5, -60.0, -183.7, -165, 5996352},
	{"death_watch_battle_droid", 240, -41.7, -59.8, -204.9, 0, 5996353},
	
	{"death_watch_s_battle_droid", 240, -155.3, -60.0, -106.8, 88, 5996365},
	{"death_watch_s_battle_droid", 240, -222.2, -60.0, -129.0, -4, 5996367},
	{"death_watch_s_battle_droid", 240, -288.3, -60.0, -124.8, 88, 5996371},
	{"death_watch_battle_droid", 240, -281.9, -60.0, -120.7, 177, 5996371},
	{"death_watch_battle_droid", 240, -281.9, -60.0, -129.6, -3, 5996371},
	
	{"death_watch_wraith", 240, -2, -60.0, -172.6, 176, 5996352},
	{"miner", 240, -12.5, -59.9, -203.6, 127, 5996354},
	{"miner", 240, -10.8, -60.1, -207.2, -24, 5996354},
	
	{"death_watch_mine_rat", 240, -6.6, -60.1, -222.5, -35, 5996354},
	{"death_watch_mine_rat", 240, -13.1, -60.0, -216.9, 3, 5996354},
	{"death_watch_mine_rat", 240, -16.9, -60.4, -247.1, 9, 5996354},
	{"death_watch_mine_rat", 240, -8.1, -59.7, -279.9, -33, 5996354},
	{"miner", 240, -13.7, -60.4, -252.0, -162, 5996354},
	{"miner", 240, 27.4, -61.8, -303.6, 19, 5996355},
	{"miner", 240, 27.4, -61.2, -305.8, -123, 5996355},
	{"miner", 240, 21.2, -60.2, -304.7, 63, 5996355},
	{"miner", 240, -45.8, -59.8, -317.0, -4, 5996356},--should be a technician with ENEMEY bitmask
	{"death_watch_mine_rat", 240, -71.1, -60.1, -315.1, 95, 5996357},
	{"death_watch_mine_rat", 240, -113.1, -59.9, -321.3, -96, 5996357},
	{"death_watch_battle_droid", 240, -100.7, -60.1, -314.8, 16, 5996357},
	{"death_watch_mine_rat", 240, -97.9, -59.8, -307.0, 29, 5996357},
	{"miner", 240, -89.8, -59.9, -300.6, -142, 5996357},
	{"death_watch_mine_rat", 240, -90.0, -60.5, -287.3, -3, 5996357},
	{"miner", 240, -98.5, -60.1, -279.1, 115, 5996357},
	{"death_watch_mine_rat", 240, -91.7, -60.0, -258.1, -153, 5996357},
	
	{"death_watch_battle_droid", 240, -123.1, -59.8, -199.8, -142, 5996360},
	{"death_watch_battle_droid", 240, -118.8, -59.8, -153.4, -73, 5996361},
	{"death_watch_mine_rat", 240, -129.2, -60.1, -163.1, 155, 5996361},
	{"death_watch_mine_rat", 240, -124.3, -60.1, -150.7, 175, 5996361},
	{"death_watch_mine_rat", 240, -120.4, -60.0, -136.9, 111, 5996361},
	{"death_watch_mine_rat", 240, -127.8, -60.0, -137.8, 111, 5996361},
	{"death_watch_battle_droid", 240, -135.4, -59.9, -143.6, 111, 5996361},
	
	{"death_watch_battle_droid", 240, -95.9, -60.1, -139.1, 156, 5996362},
	{"death_watch_mine_rat", 240, -93.7, -59.7, -150.1, -65, 5996362},
	{"death_watch_mine_rat", 240, -75.9, -60.2, -152, -50, 5996362},
	{"death_watch_mine_rat", 240, -63.6, -60.1, -148.2, -81, 5996362},
	{"death_watch_s_battle_droid", 240, -70.7, -59.8, -160.8, -43, 5996362},
	{"death_watch_mine_rat", 240, -58.3, -59.9, -136.6, -142, 5996362},
	{"death_watch_mine_rat", 240, -78.9, -59.9, -129.1, 72, 5996362},
	{"death_watch_mine_rat", 240, -71.6, -59.5, -124.7, -140, 5996362},
	{"death_watch_mine_rat", 240, -50.1, -59.5, -123.4, 128, 5996362},
	{"death_watch_mine_rat", 240, -39.1, -60.1, -136.6, -116, 5996362},
	{"death_watch_battle_droid", 240, -39.2, -59.7, -147.8, -80, 5996362},
	
	
	{"death_watch_battle_droid", 240, -151.2, -59.5, -162.2, 21, 5996364},
	{"death_watch_mine_rat", 240, -142.1, -60.1, -164.2, -86, 5996364},
	{"death_watch_mine_rat", 240, -143.7, -59.9, -175.8, -96, 5996364},
	{"death_watch_s_battle_droid", 240, -147.1, -60.2, -190.2, -1, 5996364},
	{"death_watch_mine_rat", 240, -153, -60.2, -184.8, 131, 5996364},
	{"death_watch_mine_rat", 240, -142.8, -60.7, -198.2, -89, 5996364},
	{"death_watch_mine_rat", 240, -152.9, -60.1, -210.9, 24, 5996364},
	
	{"death_watch_s_battle_droid", 240, -148.4, -59.8, -125.4, 147, 5996365},
	{"death_watch_s_battle_droid", 240, -178, -59.8, -121.0, 84, 5996366},
	{"death_watch_battle_droid", 240, -176.2, -60, -133.1, -108, 5996369},
	{"death_watch_mine_rat", 240, -171.9, -60.1, -140.7, -49, 5996369},
	{"death_watch_mine_rat", 240, -179.6, -60.2, -142.6, -3, 5996369},
	{"death_watch_mine_rat", 240, -177.0, -60.0, -150.3, -14, 5996369},
	{"death_watch_battle_droid", 240, -180.4, -60.2, -150.8, 39, 5996369},
	
	{"death_watch_s_battle_droid", 240, -205.8, -59.8, -121.3, -90, 5996367},
	{"death_watch_s_battle_droid", 240, -207.8, -60, -138.8, -7, 5996372},
	{"death_watch_mine_rat", 240, -202.7, -60.1, -141.4, -149, 5996372},
	{"death_watch_mine_rat", 240, -212.6, -59.9, -157.8, 22, 5996372},
	{"death_watch_battle_droid", 240, -204.1, -60.6, -173.9, -4, 5996372},
	{"death_watch_battle_droid", 240, -206.5, -60.4, -177.8, -175, 5996372},
	{"death_watch_mine_rat", 240, -210.7, -60.1, -194.4, 164, 5996372},
	{"miner", 240, -210.3, -60.1, -203.2, 169, 5996372},
	{"miner", 240, -207.2, -60.1, -203, 5, 5996372},
	
	-- Quest NPCs:
	{"mand_bunker_foreman", 1, 27.6, -61.5, -297.6, -112, 5996355},
	{"workshop_droid", 1, -113.3, -20, -101.3, 35, 5996328},
	{"mand_bunker_technician", 1, -23.9, -52, -163.8, 45, 5996378},
	--{"ventilation_quest_droid", 1, -6.2, -52.0, -119.6, 62, 5996379},
	{"g12-4j", 1, -80.3, -20, -121, -34, 5996329},
	{"death_watch_rescue_scientist", 1, 113.9,-68,-187,1,5996351},
}

--------------------------------------------------------------------------------
--   Constants used to reference items, cells, rooms and skills                -
--------------------------------------------------------------------------------

PASSKEYHALL = "object/tangible/dungeon/death_watch_bunker/passkey_hall.iff"
PASSKEYSTORAGE = "object/tangible/dungeon/death_watch_bunker/passkey_storage.iff"
PASSKEYMINE = "object/tangible/dungeon/death_watch_bunker/passkey_mine.iff"

OUTSIDE = 5996315
ENTRANCE = 5996316
AREAA = 5996326
AREAB = 5996338
MINES = 5996352

ARMOR = 5996374
DROIDENGINEER = 5996370
TAILOR = 5996368

ALUMMINERAL = "object/tangible/loot/dungeon/death_watch_bunker/mining_drill_reward.iff"

ADVANCEDREBREATHER = "Advanced Rebreather"
MANDOHELMET = "object/tangible/wearables/armor/mandalorian/armor_mandalorian_helmet.iff"
MANDOREBREATHER = "object/tangible/wearables/goggles/rebreather.iff"
FILTER = "object/tangible/dungeon/death_watch_bunker/filter.iff"
ENHANCEDFILTER = "object/tangible/dungeon/death_watch_bunker/enhanced_filter.iff"
ALUMGEL = "object/tangible/dungeon/death_watch_bunker/gel_packet.iff"
MEDICINE = "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff"
DRILLBATTERY = "object/tangible/dungeon/death_watch_bunker/drill_battery.iff"
DRILLBATTERYCLEAN = "object/tangible/dungeon/death_watch_bunker/drill_battery_clean.iff"
JETPACKBASE = "object/tangible/loot/dungeon/death_watch_bunker/jetpack_base.iff"
JETPACKSTABILIZER = "object/tangible/loot/dungeon/death_watch_bunker/jetpack_stabilizer.iff"
DUCTEDFAN = "object/tangible/loot/dungeon/death_watch_bunker/ducted_fan.iff"
INJECTORTANK = "object/tangible/loot/dungeon/death_watch_bunker/fuel_injector_tank.iff"
DISPERSIONUNIT = "object/tangible/loot/dungeon/death_watch_bunker/fuel_dispersion_unit.iff"
BINARYLIQUID = "object/tangible/loot/dungeon/death_watch_bunker/binary_liquid.iff"
PROTECTIVELIQUID = "object/tangible/loot/dungeon/death_watch_bunker/emulsion_protection.iff"

TARGETITEMS = {
		--Armorsmith Crafting Terminal
		{ "object/tangible/wearables/armor/mandalorian/armor_mandalorian_chest_plate.iff",
		  "object/tangible/wearables/armor/mandalorian/armor_mandalorian_boots.iff",
		  "object/tangible/wearables/armor/mandalorian/armor_mandalorian_bicep_l.iff",
		  "object/tangible/wearables/armor/mandalorian/armor_mandalorian_bicep_r.iff" },
		
		--Droid Engineer Crafting Terminal
		{ "object/tangible/wearables/armor/mandalorian/armor_mandalorian_helmet.iff",
		  "object/tangible/wearables/armor/mandalorian/armor_mandalorian_bracer_l.iff",
		  "object/tangible/wearables/armor/mandalorian/armor_mandalorian_bracer_r.iff" },
		 
		--Tailor Crafting Terminal
		{ "object/tangible/wearables/armor/mandalorian/armor_mandalorian_leggings.iff",
		  "object/tangible/wearables/armor/mandalorian/armor_mandalorian_gloves.iff",
		  "object/tangible/wearables/armor/mandalorian/armor_mandalorian_belt.iff" },
		
		-- Jetpack Crafting Terminal
		{ "object/tangible/deed/vehicle_deed/jetpack_deed.iff" },
	}

SPAWNGROUP = {
	"",
	"terminalAnextSpawn",
	"terminalBnextSpawn",
	"terminalCnextSpawn" }

SPAWNEVENT = {
	"",
	"spawnNextA",
	"spawnNextB",
	"spawnNextC" }

STATES = {
	2,--entrance unlocked
	4,--terminal a unlocked
	8,--terminal b unlocked
	16,--terminal mines unlocked
	32,--armorsmith door unlocked
	64,--droidengineer door unlocked
	128,--tailor door unlocked
}

ACCESSCELL = {
	ENTRANCE,
	AREAA,
	AREAB,
	MINES,
	ARMOR,
	DROIDENGINEER,
	TAILOR	}

UNLOCKMESSAGE = {
	"@dungeon/death_watch:access_granted",
	"@dungeon/death_watch:access_granted",
	"@dungeon/death_watch:access_granted",
	"@dungeon/death_watch:access_granted",
	"@dungeon/death_watch:unlock_door",
	"@dungeon/death_watch:unlock_door",
	"@dungeon/death_watch:unlock_door" }
	
LOCKMESSAGE = {
	"@dungeon/death_watch:terminal_locked",
	"@dungeon/death_watch:terminal_locked",
	"@dungeon/death_watch:terminal_locked",
	"@dungeon/death_watch:terminal_locked",
	"@dungeon/death_watch:room_in_use",
	"@dungeon/death_watch:room_in_use",
	"@dungeon/death_watch:room_in_use"}

TERMINALSKILLS = {
	"",
	"",
	"",
	"",
	"crafting_armorsmith_master",
	"crafting_droidengineer_master",
	"crafting_tailor_master",
	"crafting_artisan_master"}

TERMINALSKILLMESSAGE = {
	"@dungeon/death_watch:master_armorsmith_required",
	"@dungeon/death_watch:master_droidengineer_required",
	"@dungeon/death_watch:master_tailor_required",
	"@dungeon/death_watch:master_artisan_required"}

PARTSTRINGS = {
	"@dungeon/death_watch:armorsmith_items",
	"@dungeon/death_watch:droid_engineer_items",
	"@dungeon/death_watch:tailored_items"
	}

LOCKTIME = {10,10,10,10,6,6,6}

MISSINGSKILL = {
	"",
	"",
	"",
	"",
	"@dungeon/death_watch:not_enough_armorsmith_skill",
	"@dungeon/death_watch:not_enough_droidengineer_skill",
	"@dungeon/death_watch:not_enough_tailor_skill"}

DOORTYPE = {1,2,2,2,3,3,3}

DOORS = {
	{ },
	{ PASSKEYHALL },
	{ PASSKEYSTORAGE },
	{ PASSKEYMINE },

	--ARMORSMITHDOOR
	{	"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_chest_plate.iff",
		"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_boots.iff",
		"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bicep_l.iff",
		"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bicep_r.iff"
	},

	--DROIDENGINEERDOOR
	{	"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_helmet.iff",
		"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bracer_l.iff",
		"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bracer_r.iff"
	},

	--TAILORDOOR
	{	"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_leggings.iff",
		"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_gloves.iff",
		"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_belt.iff"} }

MINECELLS = {
	5996352,
	5996353,
	5996354,
	5996356,
	5996357,
	5996358,
	5996359,
	5996360,
	5996361,
	5996362,
	5996363,
	5996364,
	5996365,
	5996366,
	5996369,
	5996372,
	5996375,
	5996376,
	5996377,	
}
		
registerScreenPlay("DWB", true);

--------------------------------------------------------------
--   *** START SCREENPLAY ***                                -
--------------------------------------------------------------
function DWB:start(creatureObject)
	if (not isZoneEnabled("endor")) then	
		if TEST == 1 then
			printf("[Death Watch Bunker] Zone not loaded.\n")
		end
		return 0
	end
		
	if TEST == 1 then
		printf("[Death Watch Bunker] Initiating spawns and observers\n")
	end
	math.randomseed( os.time() )
	local bunker = getSceneObject(5996314)
	
	if bunker == nil then
		if TEST == 1 then
			printf("[Death Watch Bunker] Could not initialize. Zone not loaded?\n")
		end
		return 0
	end

	zero = self:spawnObjects(bunker)
	zero = self:test(bunker)
	zero = self:spawnMobiles(bunker)

	local bunkerObject = LuaBuildingObject(bunker)

	createEvent(1000 * 30, "DWB", "poison", bunker) 	
	createObserver(ENTEREDBUILDING, "DWB", "onEnterDWB", bunker)
	createObserver(EXITEDBUILDING, "DWB", "onExitDWB", bunker)
	return 0
end

--------------------------------------------------------------
--   Spawning Logic                                          -
--------------------------------------------------------------

--   Spawns all static respawning mobiles  -
function DWB:spawnMobiles(sceneObject)
	for i,v in ipairs(spawnMapDWB) do
		spawnedPoint = spawnMobile("endor", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
	end

	return 0
end

-- Spawns all static objects and assigns Observers -
function DWB:spawnObjects(creatureObject)
	local spawnedSceneObject = LuaSceneObject(nil)

	-- Door Acces Terminal Outside
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -18.016,-12,-8.55806, 5996315, 1, 0, 0, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:access1", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 1)

	-- Door Access Terminal A
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -84.4526,-20,-50.504,5996323,-0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:access2", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 2)
	
	-- Door Access Terminal B
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -8.3714,-32,-95.3985,5996331,-0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:access3", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 3)
	
	-- Door Access Terminal Mines
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", 26.1493,-64,-95.4288,5996347,0,0,1,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:access4", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 4)
	
	-- Voice Recognition Terminal
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/terminal_free_s1.iff",74.7941,-54,-143.444,5996348,-0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Voice Control Terminal")
	
	-- Armorsmith Access Terminal
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -232.11,-60,-219.996,5996373,0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Armorsmith Crafting Room Entry Terminal")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 5)
	
	-- Droid Engineer Crafting Room Entry Terminal
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -230.09,-60,-124.003,5996367,0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Droid Engineer Crafting Room Entry Terminal")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 6)
	
	-- Master Armorsmith Crafting Droid
	spawn = specialSpawnMapDWB["armorsmithdroid"]
	if spawn ~= nil then
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spawnedSceneObject:_setObject(spawnPointer)
		spawnedSceneObject:setCustomObjectName("Crafting Droid")
		spawnedSceneObject:setContainerComponent("death_watch_bunker_crafting_droid")
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 1)
		
		--not necessary, but kept for reference
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:user", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:targetitemindex", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:currentlycrafting", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:alummineral", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:binary", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:protective", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:bharmorpart", 0)
		
		droid = spawnedSceneObject:getObjectID()
		
		-- Armorsmith Crafting Terminal (Biceps, Chest, Boots)
		spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/terminal_free_s1.iff",-246.097,-60,-245.163,5996374,1,0,0,0)
		spawnedSceneObject:_setObject(spawnedPointer)
		spawnedSceneObject:setCustomObjectName("Mandalorian Engineering Unit")
		spawnedSceneObject:setObjectMenuComponent("death_watch_bunker_mandalorian_crafting_terminal")
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 1)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:droid", droid)
	end
	
	
	-- Master Droid Engineer Crafting Droid
	spawn = specialSpawnMapDWB["droidengineerdroid"]
	if spawn ~= nil then
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spawnedSceneObject:_setObject(spawnPointer)
		spawnedSceneObject:setCustomObjectName("Crafting Droid")
		spawnedSceneObject:setContainerComponent("death_watch_bunker_crafting_droid")
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 2)
		
		--not necessary, but kept for reference
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:user", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:targetitemindex", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:currentlycrafting", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:alummineral", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:binary", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:protective", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:bharmorpart", 0)
		
		droid = spawnedSceneObject:getObjectID()
		
		-- Master Droid Engineer Crafting Terminal (Bracer, Helmet)
		spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/terminal_free_s1.iff",-234.536,-40,-84.8062,5996370,1,0,0,0)
		spawnedSceneObject:_setObject(spawnedPointer)
		spawnedSceneObject:setCustomObjectName("Mandalorian Engineering Unit")
		spawnedSceneObject:setObjectMenuComponent("death_watch_bunker_mandalorian_crafting_terminal")
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 2)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:droid", droid)
	end
	
	
	-- Master Tailor Crafting Droid
	spawn = specialSpawnMapDWB["tailordroid"]
	if spawn ~= nil then
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spawnedSceneObject:_setObject(spawnPointer)
		spawnedSceneObject:setCustomObjectName("Crafting Droid")
		spawnedSceneObject:setContainerComponent("death_watch_bunker_crafting_droid")
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 3)
		
		--not necessary, but kept for reference
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:user", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:targetitemindex", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:currentlycrafting", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:alummineral", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:binary", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:protective", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:bharmorpart", 0)
		
		droid = spawnedSceneObject:getObjectID()
		
		-- Tailor Crafting Terminal (Pants, Gloves, Belt)
		spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/terminal_free_s1.iff",-141.981,-60,-74.3199,5996368,1,0,0,0)
		spawnedSceneObject:_setObject(spawnedPointer)
		spawnedSceneObject:setCustomObjectName("Mandalorian Engineering Unit")
		spawnedSceneObject:setObjectMenuComponent("death_watch_bunker_mandalorian_crafting_terminal")
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 3)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:droid", droid)
	end
	
	-- Jetpack Crafting Droid
	spawn = specialSpawnMapDWB["jetpackdroid"]
	if spawn ~= nil then
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spawnedSceneObject:_setObject(spawnPointer)
		spawnedSceneObject:setCustomObjectName("Jetpack Crafting Droid")
		spawnedSceneObject:setContainerComponent("death_watch_bunker_crafting_droid_jetpack")
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 4)
	
		--This is not necessary, just for reference
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:user", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:targetitemindex", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:currentlycrafting", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:alummineral", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:jetpackbase", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:jetpackstabilizer", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:ductedfan", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:injectortank", 0)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:dispersionunit", 0)
	
		droid = spawnedSceneObject:getObjectID()
		
		-- Master Artisan Crafting Terminal (Jetpack)
		spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/terminal_free_s1.iff",-265.425,-50.0002,-84.957,5996370,1,0,0,0)
		spawnedSceneObject:_setObject(spawnedPointer)
		spawnedSceneObject:setCustomObjectName("Mandalorian Engineering Unit")
		spawnedSceneObject:setObjectMenuComponent("death_watch_bunker_mandalorian_crafting_terminal")
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 4)
		writeData(spawnedSceneObject:getObjectID() .. ":dwb:droid", droid)	
	end
	
	-- Tailor Access Terminal
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -151.045,-60,-98.8703,5996365,0,0,1,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Tailor Crafting Room Entry Terminal")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 7)
	
	-- Debris
	--[[spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/invulnerable_debris.iff",66.8122,-64,-113.893,5996348,1,0,0,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:debrisEntrance", spawnedSceneObject:getObjectID())
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/invulnerable_debris.iff",112.524,-64,-113.886,5996348,1,0,0,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:debrisOverlord", spawnedSceneObject:getObjectID())
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/invulnerable_debris.iff",113.21,-64,-151.844,5996348,1,0,0,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:debrisRescue", spawnedSceneObject:getObjectID())]]
	
	--Write Data for Foreman
	writeData(5996314 .. ":dwb:haldo_busy", 0)
	--writeData(5996314 .. ":dwb:battery_busy", 0)
	--writeData(5996314 .. ":dwb:pumps_busy", 0)
	
	-- Spawn Haldo
	halnum = math.random(1,3)
	spawn = specialSpawnMapDWB["haldo" .. halnum]
	if spawn ~= nil then
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spawnedSceneObject:_setObject(spawnPointer)
		writeData(5996314 .. ":dwb:haldo", spawnedSceneObject:getObjectID())
		createObserver(OBJECTDESTRUCTION, "DWB", "haldo_killed", spawnPointer)
		--createObserver(DAMAGERECEIVED, "DWB", "haldo_damage", spawnPointer)
	end
	
	-- Water Pressure Valve Control A
	spawnedPointer = spawnSceneObject("endor","object/tangible/terminal/terminal_water_pressure.iff",55.5855,-32,-92.8,5996340,1,0,0,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setObjectMenuComponent("death_watch_bunker_water_valve")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 1)
	writeData(5996314 .. ":dwb:valve1", 0)
	
	-- Water Pressure Valve Control B
	spawnedPointer = spawnSceneObject("endor","object/tangible/terminal/terminal_water_pressure.iff",42.2316,-32,-72.5555,5996340,-0.707107,0,-0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setObjectMenuComponent("death_watch_bunker_water_valve")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 2)
	writeData(5996314 .. ":dwb:valve2", 0)
	
	-- Water Pressure Valve Control C
	spawnedPointer = spawnSceneObject("endor","object/tangible/terminal/terminal_water_pressure.iff",73.7982,-32,-76.4291,5996340,0.707107,0,-0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setObjectMenuComponent("death_watch_bunker_water_valve")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 3)
	writeData(5996314 .. ":dwb:valve3", 0)
	
	-- Water Pressure Valve Control D
	spawnedPointer = spawnSceneObject("endor","object/tangible/terminal/terminal_water_pressure.iff",56.0941,-32,-61.251,5996340,0,0,-1,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setObjectMenuComponent("death_watch_bunker_water_valve")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 4)
	writeData(5996314 .. ":dwb:valve4", 0)
	
	-- Rebreather Filter Dispenser
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/filter_dispenser.iff",-12.8382,-52,-147.565,5996378,0,0,1,0)
	--createObserver(OBJECTRADIALUSED, "DWB", "dispenser", spawnedPointer)
	
	-- Rebreather Workbench
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/workbench.iff",-16.2596,-52,-147.091,5996378,0,0,1,0)
	--createObserver(OBJECTRADIALUSED, "DWB", "workbench", spawnedPointer)
	
	-- Loot Boxes
	spawnedPointer = spawnSceneObject("endor", "object/tangible/container/general/tech_chest.iff", -3.10801,-12,36.7064,5996318,0,0,-1,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Chest")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:lootbox", 1)
	createEvent(1000, "DWB", "refill", spawnedPointer)
	
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/coal_bin_container.iff",6.01353,-32,-102.05,5996337,0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:lootbox", 2)
	createEvent(1000, "DWB", "refill", spawnedPointer)
	
	spawnedPointer = spawnSceneObject("endor", "object/tangible/container/loot/placable_loot_crate_tech_armoire.iff", -2.78947,-32,-27.1899,5996335,0,0,1,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:lootbox", 3)
	createEvent(1000, "DWB", "refill", spawnedPointer)

	return 1
end


--------------------------------------------------------------
--   Observer Callbacks                                      -
--------------------------------------------------------------
function DWB:onEnterDWB(sceneObject, creatureObject)
	local creature = LuaCreatureObject(creatureObject)
	
	if (creature:isAiAgent() == true) then
		return 0
	end
	
	state = creature:hasScreenPlayState(2, "death_watch_bunker")
	
	if state == 0 then
		local targetCellObject = LuaSceneObject(creature:getParent())
		local buildingObject = LuaSceneObject(targetCellObject:getParent())
		if TEST == 1 then
			printf("locking from " .. targetCellObject:getObjectID() .. " in " .. buildingObject:getObjectID() .. "\n")
		end
		self:lockAll(creatureObject)
	else
		if TEST == 1 then
			printf("already has access\n")
		end
		
		createEvent(10 * 1000, "DWB", "lockCellsOnly", creatureObject)
	end
	
	return 0
end

function DWB:onExitDWB(sceneObject, creatureObject, long)
	local creature = LuaCreatureObject(creatureObject)
	
	if (creature:isAiAgent() == true) then
		return 0
	end	
	
	if long == OUTSIDE or long == 0 then
		creature:sendSystemMessage("@dungeon/death_watch:relock")
	
		if TEST == 1 then
			printf("removing permissions\n")
		end
	
		creature:removeScreenPlayState(2, "death_watch_bunker")
		creature:removeScreenPlayState(4, "death_watch_bunker")
		creature:removeScreenPlayState(8, "death_watch_bunker")
		creature:removeScreenPlayState(16, "death_watch_bunker")
		creature:removeScreenPlayState(32, "death_watch_bunker")
		creature:removeScreenPlayState(64, "death_watch_bunker")
		creature:removeScreenPlayState(128, "death_watch_bunker")
	
		self:lockAll(creatureObject)
	end
	
	return 0
end

function DWB:lootBox(sceneObject, creatureObject, selectedID)
	if selectedID ~= 16 then
		return 0
	end
	
	if TEST == 1 then
		printf("opening box\n")
	end
	
	local creature = LuaCreatureObject(creatureObject)
	local container = LuaSceneObject(sceneObject)

   	state = readData(container:getObjectID() .. ":dwb:spawned")
   	
   	if state == 1 then
    	return 0
	else
		box = readData(container:getObjectID() .. ":dwb:lootbox")
    	writeData(container:getObjectID() .. ":dwb:spawned", 1)
     	
     	--spawn enemies
		if box == 1 then
			local spawn = specialSpawnMapDWB["lootbox1mob1"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7]) 
		elseif box == 2 then
			local spawn = specialSpawnMapDWB["lootbox2mob1"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7]) 
		elseif box == 3 then
			local spawn = specialSpawnMapDWB["lootbox3mob1"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = specialSpawnMapDWB["lootbox3mob2"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])  					
		end
		
     	createEvent(240 * 1000, "DWB", "refill", sceneObject)
     	return 1
   	end
end

function DWB:haldo_killed(creatureObject, playerObject)
	createEvent(1000 * 240, "DWB", "respawn_haldo", playerObject)
	num = math.random(1, 100)
	if num < 30 then
		creoid = readData(5996314 .. ":dwb:haldo_player")
		local creo = getSceneObject(creoid)
		if creo ~= nil then
			local creature = LuaCreatureObject(creo)
			creature:sendSystemMessage("@dungeon/death_watch:recovered_battery")
			
			creature:setScreenPlayState(2, "death_watch_foreman_stage_failed")
			
			local scno = LuaSceneObject(creo)
			inventory = scno:getSlottedObject("inventory")
			
			local pbattery = giveItem(inventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", -1)
			
			if (pbattery ~= nil) then
				local battery = LuaSceneObject(pbattery)
				battery:sendTo(creo)
			end
		end
	end
end

function DWB:haldo_damage(creatureObject, playerObject, damage)
	if creatureObject == nil or playerObject == nil then
		return 0
	end
	
	local player = LuaCreatureObject(playerObject)
	local creature = LuaCreatureObject(creatureObject)
	
	health = creature:getHAM(0)
	action = creature:getHAM(3)
	mind = creature:getHAM(6)
	
	maxHealth = creature:getMaxHAM(0)
	maxAction = creature:getMaxHAM(3)
	maxMind = creature:getMaxHAM(6)
	
	--printf("Health: " .. health .. " Action: " .. action .. " Mind: " .. mind .. "\n")
	
	
	if ((health <= (maxHealth * 0.9)) or (action <= (maxAction * 0.9)) or (mind <= (maxMind * 0.9))) then		
		spatialChat(creatureObject, "@dungeon/death_watch:help_me")
		
		
		creature:setPvpStatusBitmask(0)
		forcePeace(creatureObject)
		creature:setOptionsBitmask(264)
		local creo = LuaSceneObject(creatureObject)
		creo:sendTo(playerObject)
		
		
							
		return 1		
	end
	
	return 0
end


function DWB:diedWhileCrafting(creatureObject, attacker, long)
	if creatureObject == nil then
		return 1
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	iscrafting = readData(creature:getObjectID() .. ":dwb:currentlycrafting")
	
	if iscrafting == 0 then
		return 1
	else
		id = readData(creature:getObjectID() .. ":dwb:terminal")
		if id ~= 0 then
			term = getSceneObject(id)
			if term ~= nil then
				creature:sendSystemMessage("@dungeon/death_watch:died_during_crafting")
				DWB:stopCraftingProcess(creatureObject, term, false, false)
			end
		end
	end
	
	return 1
end
--------------------------------------------------------------
--   General Events                                          -
--------------------------------------------------------------
function DWB:enableAccess(sceneObject)
	local terminal = LuaSceneObject(sceneObject)
	writeData(terminal:getObjectID() .. ":dwb:accessEnabled", 1)
end

function DWB:respawn_haldo(creatureObject)
	halnum = math.random(1,3)
	spawn = specialSpawnMapDWB["haldo" .. halnum]
	if spawn ~= nil then
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		local spawnedSceneObject = LuaSceneObject(spawnPointer)
		writeData(5996314 .. ":dwb:haldo", spawnedSceneObject:getObjectID())
		createObserver(OBJECTDESTRUCTION, "DWB", "haldo_killed", spawnPointer)
		--createObserver(DAMAGERECEIVED, "DWB", "haldo_damage", spawnPointer)
	end
end

function DWB:lockCellsOnly(creatureObject)
	if creatureObject == nil then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	if TEST == 1 then
		printf("lock on reentry\n")
	end
	
	state = creature:hasScreenPlayState(2, "death_watch_bunker")
	
	if state == 0 then
		updateCellPermission(getSceneObject(ENTRANCE), 0, creatureObject)
	end
	
	state = creature:hasScreenPlayState(4, "death_watch_bunker")
	
	if state == 0 then
		updateCellPermission(getSceneObject(AREAA), 0, creatureObject)
	end

	
	state = creature:hasScreenPlayState(8, "death_watch_bunker")
	
	if state == 0 then
		updateCellPermission(getSceneObject(AREAB), 0, creatureObject)
	end		
	
	state = creature:hasScreenPlayState(16, "death_watch_bunker")
	
	if state == 0 then
		updateCellPermission(getSceneObject(MINES), 0, creatureObject)
	end
	
	state = creature:hasScreenPlayState(32, "death_watch_bunker")
	
	if state == 0 then
		updateCellPermission(getSceneObject(ARMOR), 0, creatureObject)
	end
	
	state = creature:hasScreenPlayState(64, "death_watch_bunker")
	
	if state == 0 then
		updateCellPermission(getSceneObject(DROIDENGINEER), 0, creatureObject)
	end
	
	state = creature:hasScreenPlayState(128, "death_watch_bunker")
	
	if state == 0 then
		updateCellPermission(getSceneObject(TAILOR), 0, creatureObject)
	end
end

function DWB:refill(sceneObject)
	if (sceneObject == nil) then
		return
	end
	
	createObserver(OBJECTRADIALUSED, "DWB", "lootBox", sceneObject)
	
	local container = LuaSceneObject(sceneObject)
		
	writeData(container:getObjectID() .. ":dwb:spawned", 0)
	
	if (container:getContainerObjectsSize() == 0) then
		
		if TEST == 1 then
			printf("refilling\n")
		end
		
		-- add items
		chance = math.random(100)
		createLoot(sceneObject, "death_watch_bunker_lootbox", 1) 
	
		-- second item
		if chance > 95 then
   			createLoot(sceneObject, "death_watch_bunker_lootbox", 1)
 		end
	else
		if TEST == 1 then
			printf("refilling\n")
		end
	end
end

function DWB:poison(sceneObject)
	if TEST == 1 then
		printf("Poison Trigger\n")
	end

	for i,v in ipairs(MINECELLS) do
		local pCell = getSceneObject(v)
		if pCell ~= nil then
			local cell = LuaSceneObject(pCell)
			size = cell:getContainerObjectsSize()
			
			for j=0, size - 1, 1 do
				local pointer = cell:getContainerObject(j)
				
				if pointer ~= nil then
									
					local sco = LuaSceneObject(pointer)
						
					if (sco:isCreatureObject()) then
						local creo = LuaCreatureObject(pointer)
						
						if (not creo:isAiAgent()) then
									
							if (self:hasRebreather(pointer) == 1) then
								if TEST == 1 then
									printf("Poison averted\n")
								end
							else
								self:doPoison(pointer)
							end 

						end
					end
				end
			end
		end		
	end
	createEvent(1000 * (50 + math.random(0,20)) , "DWB", "poison", sceneObject)
end

function DWB:timeWarning(creatureObject)
	if creatureObject ~= nil then
		local creature = LuaCreatureObject(creatureObject)
		creature:sendGroupMessage("@dungeon/death_watch:thirty_seconds")
	end
end

function DWB:removeFromDWB(creatureObject)
	if (creatureObject == nil) then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	if (creature:isGrouped()) then
		size = creature:getGroupSize()
		
		for i = 0, size - 1, 1 do
			pMember = creature:getGroupMember(i)
			if pMember ~= nil then
				local groupMember = LuaCreatureObject(pMember)
				if groupMember:getParentID() > 5996313 and groupMember:getParentID() < 5996380 then
					createEvent(500, "DWB", "teleportPlayer", pMember)
				end
			end
		end 
	else
		createEvent(500, "DWB", "teleportPlayer", creatureObject)
	end
	
end

function DWB:teleportPlayer(creatureObject)
	if (creatureObject == nil) then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	creature:teleport(-4657, 14.4, 4322.3, 0)
	
	self:lockAll(creatureObject)
end

function DWB:haldo_timer(creatureObject)
	if (creatureObject == nil) then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	finished_time = creature:hasScreenPlayState(4, "death_watch_foreman_stage")
	
	if finished_time == 0 then
		creature:removeScreenPlayState(1, "death_watch_foreman_stage")
		creature:removeScreenPlayState(2, "death_watch_foreman_stage")
		creature:removeScreenPlayState(4, "death_watch_foreman_stage")
		creature:sendSystemMessage("@dungeon/death_watch:haldo_failed")
		creature:setScreenPlayState(1, "death_watch_foreman_stage_failed")
		createEvent(1000 * 60 * 20, "DWB", "unlock_haldo", creatureObject)
	end
end

function DWB:pump_timer(creatureObject)
	if (creatureObject == nil) then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	finished_time = creature:hasScreenPlayState(64, "death_watch_foreman_stage")
	
	if finished_time == 0 then
		creature:removeScreenPlayState(32, "death_watch_foreman_stage")
		creature:setScreenPlayState(3, "death_watch_foreman_stage_failed")
		creature:sendSystemMessage("@dungeon/death_watch:water_pressure_failed")
	end
end

function DWB:unlock_haldo(creatureObject)
	if (creatureObject == nil) then
		return
	end
	
	local creature = LuaCreatureObject(creatureObjcet)
	creature:removeScreenPlayState(1, "death_watch_foreman_stage_failed")
end

function DWB:destroyIngredient(ingredient)
	if ingredient ~= nil then
		local object = LuaSceneObject(ingredient)
		object:destroyObjectFromWorld()
	end
end

--------------------------------------------------------------
--   Key Spawn Events                                        -
--------------------------------------------------------------
function DWB:spawnNextA(creatureObject)
	nextSpawn = readData(5996314 .. ":dwb:terminalAnextSpawn")
	
	if nextSpawn == 0 then
		return
	elseif nextSpawn == 1 then
		writeData(5996314 .. ":dwb:terminalAnextSpawn", 2)
		local spawn = specialSpawnMapDWB["rageon_vart_assist1"] 
		createEvent((math.random(0, 10) + 30) * 1000, "DWB", "spawnNextA", creatureObject)
		
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 102)
	elseif nextSpawn == 2 then
		writeData(5996314 .. ":dwb:terminalAnextSpawn", 3)
		local spawn = specialSpawnMapDWB["rageon_vart_assist2"]
		createEvent((math.random(0, 10) + 30) * 1000, "DWB", "spawnNextA", creatureObject)
		
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 40)
	else
		writeData(5996314 .. ":dwb:terminalAnextSpawn", 0)
		local spawn = specialSpawnMapDWB["rageon_vart"]
		
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	end
	
end

function DWB:spawnNextB(creatureObject)
	nextSpawn = readData(5996314 .. ":dwb:terminalBnextSpawn")
	
	if nextSpawn == 0 then
		return
	elseif nextSpawn == 1 then
		writeData(5996314 .. ":dwb:terminalBnextSpawn", 2)
		local spawn = specialSpawnMapDWB["klin_nif_assist1"] 
		createEvent((math.random(0, 10) + 30) * 1000, "DWB", "spawnNextB", creatureObject)
		
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 31)
	elseif nextSpawn == 2 then
		writeData(5996314 .. ":dwb:terminalBnextSpawn", 3)
		local spawn = specialSpawnMapDWB["klin_nif_assist2"]
		createEvent((math.random(0, 10) + 30) * 1000, "DWB", "spawnNextB", creatureObject)
		
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 67)
	else
		writeData(5996314 .. ":dwb:terminalBnextSpawn", 0)
		local spawn = specialSpawnMapDWB["klin_nif"]
		
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	end
	
end

function DWB:spawnNextC(creatureObject)
	nextSpawn = readData(5996314 .. ":dwb:terminalCnextSpawn")
	
	if nextSpawn == 0 then
		return
	elseif nextSpawn == 1 then
		writeData(5996314 .. ":dwb:terminalCnextSpawn", 2)
		local spawn = specialSpawnMapDWB["fenri_dalso_assist1"] 
		createEvent((math.random(0, 10) + 30) * 1000, "DWB", "spawnNextC", creatureObject)
		
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 37)
	elseif nextSpawn == 2 then
		writeData(5996314 .. ":dwb:terminalCnextSpawn", 3)
		local spawn = specialSpawnMapDWB["fenri_dalso_assist2"]
		createEvent((math.random(0, 10) + 30) * 1000, "DWB", "spawnNextC", creatureObject)
		
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 21)
	else
		writeData(5996314 .. ":dwb:terminalCnextSpawn", 0)
		local spawn = specialSpawnMapDWB["fenri_dalso_add1"]
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		local spawn = specialSpawnMapDWB["fenri_dalso_add2"]
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		local spawn = specialSpawnMapDWB["fenri_dalso_add3"]
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		local spawn = specialSpawnMapDWB["fenri_dalso_add4"]
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		local spawn = specialSpawnMapDWB["fenri_dalso"]
		spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	end
	
end

--------------------------------------------------------------
--   Helper Functions                                        -
--------------------------------------------------------------

--   Checks whether a creature has sufficient skill to access a particular crafting room  -
function DWB:hasRequiredSkill(room, creatureObject)
	if (creatureObject == nil) then
		if TEST == 1 then
			printf("creature nil\n")
		end
		return false
	end
	
	if (room < 1 or room > 8) then
		if TEST == 1 then
			printf("room invalid\n")
		end
		return false
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	if creature:hasSkill(TERMINALSKILLS[room]) then
		return true
	end
	
	return false
end

--   Checks whether a creature has an Alum Mineral  -
function DWB:hasAlumMineral(creatureObject)
	if creatureObject == nil then
		return false
	end
	
	local creature = LuaSceneObject(creatureObject)
	inventory = creature:getSlottedObject("inventory")
	
	if (getContainerObjectByTemplate(inventory, ALUMMINERAL, true) == nil) then
		if TEST == 1 then
			printf("no alum\n")
		end
		return false
	end

	return true
end

--   Checks whether a creature has all necessary items to access a particular crafting room  -
function DWB:findRequiredItem(room, creatureObject)
	if (creatureObject == nil) then
		if TEST == 1 then
			printf("creature nil\n")
		end
		return nil
	end
	
	if (room < 1 or room > 7) then
		if TEST == 1 then
			printf("room invalid\n")
		end
		return nil
	end
	
	local creature = LuaSceneObject(creatureObject)
	inventory = creature:getSlottedObject("inventory")
	
	local table = DOORS[room]
	
	for i,v in ipairs(table) do
		obj = getContainerObjectByTemplate(inventory, v, true) 
		if (obj ~= nil) then
			return obj
		end
	end
	if TEST == 1 then
		printf("required item not found\n")
	end
	return nil
end

--   Checks whether a creature has sufficient protection against alum mine poison  -
function DWB:hasRebreather(sceneObject)
	--TODO: Change this to be a skill mod check for private_poison_rebreather
	local scno = LuaSceneObject(sceneObject)
	local pRebreather = scno:getSlottedObject("eyes")
	
	if (pRebreather ~= nil) then
		local rebreather = LuaSceneObject(pRebreather)
		headSlot = rebreather:getTemplateObjectPath()
		
		if TEST == 1 then
			printf("hat: " .. headSlot .. "\n")
		end
		
		if (headSlot == MANDOREBREATHER) then
			if (rebreather:getCustomObjectName() == ADVANCEDREBREATHER) then
				return 1
			else
				return 0
			end
		elseif (headSlot == MANDOHELMET) then
			return 1
		end
	end
	
	return 0
end

--   Inflict poison damage on a creature  -
function DWB:doPoison(creatureObject)
	if creatureObject == nil then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	if TEST == 1 then
		printf("poisoned\n")
	end
	
	creature:inflictDamage(creatureObject, 0, 100, 0)
	creature:sendSystemMessage("@dungeon/death_watch:bad_air")
end

--   Lock all restricted cells to a creature  -
-- NOTE: Once proper permissions are in, might have to revisit and set all cells of a restricted area 
-- rather than just the first accessible one
function DWB:lockAll(creatureObject)
	if creatureObject == nil then
		if TEST == 1 then
			printf("creature is nil\n")
		end
		return
	end
	
	--first terminal
	updateCellPermission(getSceneObject(ENTRANCE), 0, creatureObject)
	
	--terminal a
	updateCellPermission(getSceneObject(AREAA), 0, creatureObject)
	
	--terminal b
	updateCellPermission(getSceneObject(AREAB), 0, creatureObject)

	--mines
	updateCellPermission(getSceneObject(MINES), 0, creatureObject)
	
	--Armorsmith Crafting Room
	updateCellPermission(getSceneObject(ARMOR), 0, creatureObject)
	
	--Tailor Crafting Room
	updateCellPermission(getSceneObject(TAILOR), 0, creatureObject)
	
	--Droid Engineer Crafting Room
	updateCellPermission(getSceneObject(DROIDENGINEER), 0, creatureObject)
end

function DWB:spawnDefenders(number, creatureObject)
	if number < 1 or number > 4 then
		return
	end
	
	if number == 1 then
		local spawn = specialSpawnMapDWB["entrance1"]
		spawnPointer1 = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		local spawn = specialSpawnMapDWB["entrance2"]
		spawnPointer2 = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		
		if creatureObject ~= nil then
			local spawnedCreature = LuaCreatureObject(spawnPointer1)
			spawnedCreature:engageCombat(creatureObject)
			spawnedCreature:_setObject(spawnPointer2)
			spawnedCreature:engageCombat(creatureObject)
		end
	else
		writeData(5996314 .. ":dwb:" .. SPAWNGROUP[number], 1)
		createEvent(2 * 1000, "DWB", SPAWNEVENT[number], creatureObject)
	end
end

function DWB:unlockForGroup(number, creatureObject, cells)
	if creatureObject == nil then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	-- screenplaystates for login/logout
	if (creature:isGrouped()) then
		size = creature:getGroupSize()
		
		for i = 0, size - 1, 1 do
			pMember = creature:getGroupMember(i)
			if pMember ~= nil then
				local groupMember = LuaCreatureObject(pMember)
				
				local parentID = groupMember:getParentID()
				
				if (cells and parentID > 5996313 and parentID < 5996380) then
					groupMember:setScreenPlayState(STATES[number], "death_watch_bunker")
					updateCellPermission(getSceneObject(ACCESSCELL[number]), 1, pMember)
					groupMember:sendSystemMessage(UNLOCKMESSAGE[number])
				elseif ((not cells) and groupMember:getZoneName() == "endor") then
					groupMember:setScreenPlayState(STATES[number], "death_watch_bunker")
					updateCellPermission(getSceneObject(ACCESSCELL[number]), 1, pMember)
					groupMember:sendSystemMessage(UNLOCKMESSAGE[number])
				end
			end
		end 
	else
		creature:setScreenPlayState(STATES[number], "death_watch_bunker")
		updateCellPermission(getSceneObject(ACCESSCELL[number]), 1, creatureObject)
		creature:sendSystemMessage(UNLOCKMESSAGE[number])
	end
end

function DWB:checkDoor(sceneObject, creatureObject)
	if creatureObject == nil or sceneObject == nil then
		return 
	end
	
	local creature = LuaCreatureObject(creatureObject)
	local terminal = LuaSceneObject(sceneObject)
	enabled = readData(terminal:getObjectID() .. ":dwb:accessEnabled")
	number = readData(terminal:getObjectID() .. ":dwb:terminal")
	
	if TEST == 1 then
		printf(creature:getName() .. " trying to open door number " .. number .. "\n")
	end
	
	type = DOORTYPE[number]
	
	if type == 1 then
		local state = creature:hasScreenPlayState(1, "death_watch_bunker")
		if state == 0 then
			if (enabled == 0) then
				creature:sendSystemMessage(LOCKMESSAGE[number])
				return
			end
			
			creature:sendGroupMessage("@dungeon/death_watch:airlock_backup")
			self:spawnDefenders(number, creatureObject)
		else
			self:unlockForGroup(number, creatureObject, false)
			return
		end
	elseif type == 2 then
		if (self:findRequiredItem(number, creatureObject) == nil) then
			if (enabled == 0) then
				creature:sendSystemMessage(LOCKMESSAGE[number])
				return
			end
			
			creature:sendGroupMessage("@dungeon/death_watch:denied_access")
			self:spawnDefenders(number, creatureObject)
		else
			requiredItem = self:findRequiredItem(number, creatureObject)
			local item = LuaSceneObject(requiredItem)
			self:unlockForGroup(number, creatureObject, true)
			item:destroyObjectFromWorld()
			return
		end
	elseif type == 3 then
		if (enabled == 0) then
			creature:sendSystemMessage(LOCKMESSAGE[number])
			return
		end
		
		if (self:findRequiredItem(number, creatureObject) == nil or self:hasAlumMineral(creatureObject) == false) then
			creature:sendSystemMessage("@dungeon/death_watch:not_enough_ingredients")
			return
		end
		
		if (self:hasRequiredSkill(number, creatureObject) == false) then
			creature:sendSystemMessage(MISSINGSKILL[number])
			return
		end
		
		self:unlockForGroup(number, creatureObject, true)
		
		cell = getSceneObject(ACCESSCELL[number])
		if cell == nil then
			printf("cell nil\n")
			return
		end		
		
		createEvent(1000 * 60 * 5, "DWB", "removeFromDWB", creatureObject)
		createEvent(1000 * 60 * 4.5, "DWB", "timeWarning", creatureObject)
		createEvent(1000 * 60 * 5.5, "DWB", "despawnCell", cell)
	end
	
	writeData(terminal:getObjectID() .. ":dwb:accessEnabled", 0)
	createEvent(1000 * 60 * LOCKTIME[number], "DWB", "enableAccess", sceneObject)
end

function DWB:despawnCell(pcell)
	if pcell == nil then
		return
	end
	
	local cell = LuaSceneObject(pcell)
	size = cell:getContainerObjectsSize()
	for i = 0, size - 1, 1 do
		pointer = cell:getContainerObject(i)
		if pointer ~= nil then
			local object = LuaSceneObject(pointer)
			if object:isCreatureObject() then
				template = object:getTemplateObjectPath()
				
				if string.find(template, "death_watch") ~= nil or string.find(template, "battle_droid") ~= nil then
					createEvent(1000, "DWB", "despawnCreature", pointer)
				end
			end
		end
	end
end

function DWB:despawnCreature(pointer)
	if pointer ~= nil then
		local object = LuaSceneObject(pointer)
		object:destroyObjectFromWorld()
	end
end

function DWB:startForemanQuestStage(number, creatureObject)
	if creatureObject == nil then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	
	if number == 1 then
		writeData(5996314 .. ":dwb:haldo_busy", 1)
		writeData(5996314 .. ":dwb:haldo_player", creature:getObjectID())
		createEvent(1000 * 60 * 60, "DWB", "haldo_timer", creatureObject)
	elseif number == 2 then
		createEvent(1000 * 60 * 60, "DWB", "pump_timer", creatureObject)
	end
end

function DWB:storeTime(creatureObject)
	if creatureObject ~= nil then
		time = os.time()
		writeScreenPlayData(creatureObject, "DWB", "time", time)
	end
end

function DWB:checkTime(creatureObject)
	if creatureObject == nil then
		return false
	end
	
	currenttime = os.time()
	receivedtime = readScreenPlayData(creatureObject, "DWB", "time")
	
	if receivedtime == "" then
		return false
	end
	
	seconds = os.difftime(currenttime, receivedtime)
	
	if (seconds > 216000) then--more then 60 hours passed
		return true
	end
	
	return false
end

function DWB:cancelCrafting(term)
	if term == nil then
		return
	end
	
	local terminal = LuaSceneObject(term)
	isCrafting = readData(terminal:getObjectID() .. ":dwb:currentlycrafting")
	
	if isCrafting > 0 and isCrafting < 4 then
		id = readData(terminal:getObjectID() .. ":dwb:user")
		if id ~= 0 then
			creatureObject = getSceneObject(id)
			if creatureObject ~= nil then
				local creature = LuaCreatureObject(creatureObject)
				creature:sendSystemMessage("@dungeon/death_watch:took_too_long")
				DWB:stopCraftingProcess(creatureObject, term, false, true)
			end
		end
	end
end

function DWB:stopCraftingProcess(creatureObject, droid, successful, teleport)
	if creatureObject == nil or droid == nil then
		return
	end
	
	local creature = LuaCreatureObject(creatureObject)
	local terminal = LuaSceneObject(droid)
	number = readData(terminal:getObjectID() .. ":dwb:craftingterminal")  
	target = readData(terminal:getObjectID() .. ":dwb:targetitemindex")
	
	writeData(creature:getObjectID() .. ":dwb:currentlycrafting", 0)
	writeData(terminal:getObjectID() .. ":dwb:currentlycrafting", 0)
	
	if successful == true then
		local creo = LuaSceneObject(creatureObject)
		inventory = creo:getSlottedObject("inventory")
		local targetitems = TARGETITEMS[number]
		local reward = giveItem(inventory, targetitems[target], -1)
		
		if (reward == nil) then
			return 0
		end
		--local rewardObject = LuaTangibleObject(pcure)
		--tcure:setCustomizationVariable("index_color_1", 51)
		local rewardObject = LuaSceneObject(reward)
		rewardObject:sendTo(creatureObject)
	end
	
	writeData(creature:getObjectID() .. ":dwb:terminal", 0)
	writeData(terminal:getObjectID() .. ":dwb:user", 0)
	writeData(terminal:getObjectID() .. ":dwb:targetitemindex", 0)
	
	
	if number == 4 then
		writeData(terminal:getObjectID() .. ":dwb:alummineral", 0)
		writeData(terminal:getObjectID() .. ":dwb:jetpackbase", 0)
		writeData(terminal:getObjectID() .. ":dwb:jetpackstabilizer", 0)
		writeData(terminal:getObjectID() .. ":dwb:ductedfan", 0)
		writeData(terminal:getObjectID() .. ":dwb:injectortank", 0)
		writeData(terminal:getObjectID() .. ":dwb:dispersionunit", 0)
	else
		writeData(terminal:getObjectID() .. ":dwb:alummineral", 0)
		writeData(terminal:getObjectID() .. ":dwb:binary", 0)
		writeData(terminal:getObjectID() .. ":dwb:protective", 0)
		writeData(terminal:getObjectID() .. ":dwb:bharmorpart", 0)
	end
	
	if teleport == true then
		createEvent(5000, "DWB", "teleportPlayer", creatureObject)
	end
end

function DWB:sendUseTerminalMessage(creatureObject)
	if creatureObject ~= nil then
		local creature = LuaCreatureObject(creatureObject)
		creature:sendSystemMessage("@dungeon/death_watch:use_terminal")
	end
end

function DWB:startCraftingProcess(creatureObject, terminal)
	if creatureObject == nil or terminal == nil then
		return
	end

	local creature = LuaCreatureObject(creatureObject)
	createEvent(1000 * 30, "DWB", "cancelCrafting", terminal)
	createEvent(1000, "DWB", "sendUseTerminalMessage", creatureObject)
	writeData(creature:getObjectID() .. ":dwb:currentlycrafting", 1)
	createObserver(OBJECTDESTRUCTION, "DWB", "diedWhileCrafting", creatureObject)  
end

function DWB:nextCraftingStep(droid)
	if droid == nil then
		return
	end
	
	local terminal = LuaSceneObject(droid)
	writeData(terminal:getObjectID() .. ":dwb:currentlycrafting", 3)
	creoid = readData(terminal:getObjectID() .. ":dwb:user")
	if creoid ~= 0 then
		creo = getSceneObject(creoid)
		if creo ~= nil then
			local creature = LuaCreatureObject(creo)
			creature:sendSystemMessage("@dungeon/death_watch:use_terminal")
		end
	end
end

function DWB:finishCraftingStep(droid)
	if droid == nil then
		return
	end
	
	local terminal = LuaSceneObject(droid)
	creoid = readData(terminal:getObjectID() .. ":dwb:user")
	if creoid ~= 0 then
		creo = getSceneObject(creoid)
		if creo ~= nil then
			local creature = LuaCreatureObject(creo)
			creature:sendSystemMessage("@dungeon/death_watch:crafting_finished")
			DWB:stopCraftingProcess(creo, droid, true, true)
		end
	end
end

--------------------------------------------------------------
--   Lua Components                                       -
--------------------------------------------------------------

door_control_terminal = {  }

function door_control_terminal:fillObjectMenuResponse(sceneObject, menuResponse, player)
	local response = LuaObjectMenuResponse(menuResponse)
	response:addRadialMenuItem(20, 3, "@dungeon/death_watch:mnu_open_door") 
end

function door_control_terminal:handleObjectMenuSelect(sceneObject, player, selectedID)
	if (selectedID == 20) then
		DWB:checkDoor(sceneObject, player)
	end
		
	return 0
end

death_watch_bunker_filter_dispenser = { }

function death_watch_bunker_filter_dispenser:fillObjectMenuResponse(sceneObject, menuResponse, player)
	local response = LuaObjectMenuResponse(menuResponse)
	response:addRadialMenuItem(117, 3, "@dungeon/death_watch:mnu_issue_filter")
end

function death_watch_bunker_filter_dispenser:handleObjectMenuSelect(sceneObject, player, selectedID)
	if (player == nil) then
		return 0
	end
	
	if (selectedID == 117) then
		local creature = LuaCreatureObject(player)
		local owner = LuaSceneObject(player)
		inventory = owner:getSlottedObject("inventory")
		oldfilter = getContainerObjectByTemplate(inventory, FILTER, true)
		if oldfilter ~= nil then
			creature:sendSystemMessage("@dungeon/death_watch:already_has_filter")
		else
			local pfilter = giveItem(inventory,FILTER, -1)
			creature:sendSystemMessage("@dungeon/death_watch:issue_filter")
			
			if (pfilter == nil) then
				return 0
			end
			
			local ofilter = LuaSceneObject(pfilter)
			ofilter:sendTo(player)
		end
		
		return 0
	end
	
	return 0
end
	
death_watch_bunker_workbench = { }

function death_watch_bunker_workbench:fillObjectMenuResponse(sceneObject, menuResponse, player)
	local response = LuaObjectMenuResponse(menuResponse)
	response:addRadialMenuItem(117, 3, "@dungeon/death_watch:mnu_workbench")
end

function death_watch_bunker_workbench:handleObjectMenuSelect(sceneObject, player, selectedID)
	if (player == nil) then
		return 0
	end
	
	if (selectedID ~= 117) then
		if TEST == 1 then
			printf("Wrong selectedID " .. selectedID .. "\n")
		end
		return 0
	end
	
	local creature = LuaCreatureObject(player)
	local owner = LuaSceneObject(player)
	inventory = owner:getSlottedObject("inventory")
	pRebreather = getContainerObjectByTemplate(inventory, MANDOREBREATHER, true)
	pEnhancedfilter = getContainerObjectByTemplate(inventory, ENHANCEDFILTER, true)
	
	
	if (pRebreather == nil or pEnhancedfilter == nil) then
		creature:sendSystemMessage("@dungeon/death_watch:missing_component")
		return 0
	else
		local rebreather = LuaSceneObject(pRebreather)
		local enhancedfilter = LuaSceneObject(pEnhancedfilter)
		rebreather:destroyObjectFromWorld()
		enhancedfilter:destroyObjectFromWorld()
		local pAdvrebreather = giveItem(inventory, MANDOREBREATHER, -1)
		creature:sendSystemMessage("@dungeon/death_watch:agumented_rebreather")
		
		if (pAdvrebreather == nil) then
			return 0
		end
	
		local advrebreather = LuaSceneObject(pAdvrebreather)
		advrebreather:setCustomObjectName("Advanced Rebreather")
		advrebreather:sendTo(player)
		
		
				
	end

	return 0
end

death_watch_bunker_filter = { }

function death_watch_bunker_filter:fillObjectMenuResponse(sceneObject, menuResponse, player)
	local response = LuaObjectMenuResponse(menuResponse)
	response:addRadialMenuItem(117, 3, "@dungeon/death_watch:mnu_filter")
end

function death_watch_bunker_filter:handleObjectMenuSelect(sceneObject, player, selectedID)
	if (player == nil) then
		return 0
	end
	
	if (selectedID ~= 117) then
		if TEST == 1 then
			printf("Wrong selectedID " .. selectedID .. "\n")
		end
		return 0
	end
	
	local creature = LuaCreatureObject(player)
	local owner = LuaSceneObject(player)
	inventory = owner:getSlottedObject("inventory")
	palumgel = getContainerObjectByTemplate(inventory, ALUMGEL, true)
	
	
	if (palumgel == nil or sceneObject == nil) then
		creature:sendSystemMessage("@dungeon/death_watch:missing_component2")
		return 0
	elseif (not creature:hasSkill("crafting_artisan_engineering_02")) then
		creature:sendSystemMessage("@dungeon/death_watch:not_skilled")
		return 0
	else
		local alumgel = LuaSceneObject(palumgel)
		local oldfilter = LuaSceneObject(sceneObject)
		alumgel:destroyObjectFromWorld()
		oldfilter:destroyObjectFromWorld()
		local penhfilter = giveItem(inventory, ENHANCEDFILTER, -1)
		creature:sendSystemMessage("@dungeon/death_watch:agumented_filter")
		
		if (penhfilter == nil) then
			return 0
		end
	
		local enhfilter = LuaSceneObject(penhfilter)
		enhfilter:sendTo(player)
				
	end

	return 0
end

death_watch_bunker_water_valve = { }

function death_watch_bunker_water_valve:fillObjectMenuResponse(sceneObject, menuResponse, player)
	local response = LuaObjectMenuResponse(menuResponse)
	response:addRadialMenuItem(20, 3, "@dungeon/death_watch:mnu_water_valve")
end

function death_watch_bunker_water_valve:handleObjectMenuSelect(sceneObject, player, selectedID)
	if (player == nil or sceneObject == nil) then
		return 0
	end
	
	if (selectedID ~= 20) then
		if TEST == 1 then
			printf("Wrong selectedID " .. selectedID .. "\n")
		end
		return 0
	end
	
	local creature = LuaCreatureObject(player)
	
	started = creature:hasScreenPlayState(32, "death_watch_foreman_stage")
	finished = creature:hasScreenPlayState(64, "death_watch_foreman_stage")
	if started == 0 or finished == 1 then
		creature:sendSystemMessage("@dungeon/death_watch:access_denied")
		return 0
	end	
	
	local terminal = LuaSceneObject(sceneObject)
	
	termnum = readData(terminal:getObjectID() .. ":dwb:terminal")
	
	if termnum == 1 then
		state = readData(5996314 .. ":dwb:valve1")
		if state % 2 == 0 then
			creature:sendSystemMessage("@dungeon/death_watch:valve_on")
		else
			creature:sendSystemMessage("@dungeon/death_watch:valve_off")
		end
		
		writeData(5996314 .. ":dwb:valve1", state + 1)		
	
		state = readData(5996314 .. ":dwb:valve3")
		writeData(5996314 .. ":dwb:valve3", state + 1)
		
	elseif termnum == 2 then
		state = readData(5996314 .. ":dwb:valve2")
		if state % 2 == 0 then
			creature:sendSystemMessage("@dungeon/death_watch:valve_on")
		else
			creature:sendSystemMessage("@dungeon/death_watch:valve_off")
		end
		
		writeData(5996314 .. ":dwb:valve2", state + 1)		
	
		state = readData(5996314 .. ":dwb:valve1")
		writeData(5996314 .. ":dwb:valve1", state + 1)
	elseif termnum == 3 then
		state = readData(5996314 .. ":dwb:valve3")
		if state % 2 == 0 then
			creature:sendSystemMessage("@dungeon/death_watch:valve_on")
		else
			creature:sendSystemMessage("@dungeon/death_watch:valve_off")
		end
		
		writeData(5996314 .. ":dwb:valve3", state + 1)		
	
		state = readData(5996314 .. ":dwb:valve4")
		writeData(5996314 .. ":dwb:valve4", state + 1)
		
	elseif termnum == 4 then
		state = readData(5996314 .. ":dwb:valve4")
		if state % 2 == 0 then
			creature:sendSystemMessage("@dungeon/death_watch:valve_on")
		else
			creature:sendSystemMessage("@dungeon/death_watch:valve_off")
		end
		
		writeData(5996314 .. ":dwb:valve4", state + 1)		
	end
	
	state1 = readData(5996314 .. ":dwb:valve1")
	state2 = readData(5996314 .. ":dwb:valve2")
	state3 = readData(5996314 .. ":dwb:valve3")
	state4 = readData(5996314 .. ":dwb:valve4")
	
	if (state1 % 2 == 1 and state2 % 2 == 1 and state3 % 2 == 1 and state4 % 2 == 1) then
		creature:setScreenPlayState(64, "death_watch_foreman_stage")
		creature:sendSystemMessage("@dungeon/death_watch:restored_pressure")
		writeData(5996314 .. ":dwb:valve1", 0)
		writeData(5996314 .. ":dwb:valve2", 0)
		writeData(5996314 .. ":dwb:valve3", 0)
		writeData(5996314 .. ":dwb:valve4", 0)	
	end
	
	return 0
end

death_watch_bunker_mandalorian_crafting_terminal = { }

function death_watch_bunker_mandalorian_crafting_terminal:fillObjectMenuResponse(sceneObject, menuResponse, player)
	
end

function death_watch_bunker_mandalorian_crafting_terminal:handleObjectMenuSelect(sceneObject, player, selectedID)
	if (player == nil or sceneObject == nil) then
		return 0
	end
	
	if (selectedID ~= 20) then
		if TEST == 1 then
			printf("Wrong selectedID " .. selectedID .. "\n")
		end
		return 0
	end
	
	local creature = LuaCreatureObject(player)
	local factory = LuaSceneObject(sceneObject)
	term = getSceneObject(readData(factory:getObjectID() .. ":dwb:droid"))
	
	if term == nil then
		return 0
	end
	
	local terminal = LuaSceneObject(term)
	isCrafting = readData(terminal:getObjectID() .. ":dwb:currentlycrafting")
	userid = readData(terminal:getObjectID() .. ":dwb:user")
	
	if isCrafting < 1 then
		return 0
	end
	
	if creature:getObjectID() ~= userid then
		creature:sendSystemMessage("@dungeon/death_watch:same_user_only")
		return 0
	end
	
	if isCrafting == 2 or isCrafting == 4 then
		creature:sendSystemMessage("@dungeon/death_watch:crafting_not_yet")
		return 0
	end
	
	if isCrafting == 1 then
		local suiManager = LuaSuiManager()
		suiManager:sendConfirmSui(term, player, "DWB", "craftingConfirmCallback", "@dungeon/death_watch:continue_manufacturing", "@dungeon/death_watch:continue_button")
	elseif isCrafting == 3 then
		local suiManager = LuaSuiManager()
		suiManager:sendConfirmSui(term, player, "DWB", "craftingConfirmCallback", "@dungeon/death_watch:finish_manufacturing", "@dungeon/death_watch:finish_button")
	end
			
	return 0
end

death_watch_bunker_crafting_droid_jetpack = { }

function death_watch_bunker_crafting_droid_jetpack:canAddObject(droid, ingredient, slot)
	if ingredient == nil then
		return false
	end
	
	if slot ~= -1 then
		return false
	end
	
	local object = LuaSceneObject(ingredient)
	pParent = object:getParent()
	
	if pParent == nil then
		return false
	end
	
	local parent = LuaSceneObject(pParent)
	pParent = parent:getParent()
	
	if pParent == nil then
		return false
	end
	
	local parent = LuaSceneObject(pParent)
	if parent:isCreatureObject() == false then
		return false
	end
	
	local creature = LuaCreatureObject(pParent) 
	
	local terminal = LuaSceneObject(droid)
	template = object:getTemplateObjectPath()
	
	userid = readData(terminal:getObjectID() .. ":dwb:user")
	
	if userid ~= 0 and userid ~= creature:getObjectID() then
		creature:sendSystemMessage("@dungeon/death_watch:same_user_only")
		return false
	end	
	
	if creature:hasSkill(TERMINALSKILLS[8]) == false then
		creature:sendSystemMessage(TERMINALSKILLMESSAGE[4])
		return false
	end
	
	hasMineral = readData(terminal:getObjectID() .. ":dwb:alummineral")
	hasJetpackBase = readData(terminal:getObjectID() .. ":dwb:jetpackbase")
	hasJetpackStabilizer = readData(terminal:getObjectID() .. ":dwb:jetpackstabilizer")
	hasDuctedFan = readData(terminal:getObjectID() .. ":dwb:ductedfan")
	hasInjectorTank = readData(terminal:getObjectID() .. ":dwb:injectortank")
	hasDispersionUnit = readData(terminal:getObjectID() .. ":dwb:dispersionunit")
	
	if template == JETPACKBASE then
		if hasJetpackBase == 0 then
			return true
		else
			creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	elseif template == JETPACKSTABILIZER then
		if hasJetpackStabilizer == 0 then
			return true
		else
			creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	elseif template == DUCTEDFAN then
		if hasDuctedFan == 0 then
			return true
		else
			creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	elseif template == INJECTORTANK then
		if hasInjectorTank == 0 then
			return true
		else
			creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	elseif template == DISPERSIONUNIT then
		if hasDispersionUnit == 0 then
			return true
		else
			creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
		end 
	elseif template == ALUMMINERAL then
		if hasMineral == 0 then
			return true
		else
			creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	end
		
	return false
end

function death_watch_bunker_crafting_droid_jetpack:transferObject(droid, ingredient, slot)
	if (ingredient == nil) then
		return 0
	end

	if slot == -1 then
		local object = LuaSceneObject(ingredient)
		
		pParent = object:getParent()
	
		if pParent == nil then
			return 0
		end
		
		local parent = LuaSceneObject(pParent)
		pParent = parent:getParent()
		
		if pParent == nil then
			return 0
		end
		
		local parent = LuaSceneObject(pParent)
		if parent:isCreatureObject() == false then
			return 0
		end
		
		local creature = LuaCreatureObject(pParent)
		
		local terminal = LuaSceneObject(droid)
		template = object:getTemplateObjectPath()
		
		if template == JETPACKBASE then
			writeData(terminal:getObjectID() .. ":dwb:jetpackbase", 1)
		elseif template == JETPACKSTABILIZER then
			writeData(terminal:getObjectID() .. ":dwb:jetpackstabilizer", 1)
		elseif template == DUCTEDFAN then
			writeData(terminal:getObjectID() .. ":dwb:ductedfan", 1)
		elseif template == INJECTORTANK then
			writeData(terminal:getObjectID() .. ":dwb:injectortank", 1)
		elseif template == DISPERSIONUNIT then
			writeData(terminal:getObjectID() .. ":dwb:dispersionunit", 1)
		elseif template == ALUMMINERAL then
			writeData(terminal:getObjectID() .. ":dwb:alummineral", 1)
		end
		
		-- avoid Locker issues
		createEvent(500, "DWB", "destroyIngredient", ingredient)
		
		hasMineral = readData(terminal:getObjectID() .. ":dwb:alummineral")
		hasJetpackBase = readData(terminal:getObjectID() .. ":dwb:jetpackbase")
		hasJetpackStabilizer = readData(terminal:getObjectID() .. ":dwb:jetpackstabilizer")
		hasDuctedFan = readData(terminal:getObjectID() .. ":dwb:ductedfan")
		hasInjectorTank = readData(terminal:getObjectID() .. ":dwb:injectortank")
		hasDispersionUnit = readData(terminal:getObjectID() .. ":dwb:dispersionunit")
		
		userid = readData(terminal:getObjectID() .. ":dwb:user")
		if userid == 0 then
			writeData(terminal:getObjectID() .. ":dwb:user", creature:getObjectID())
			writeData(creature:getObjectID() .. ":dwb:terminal", terminal:getObjectID())
		end
		
		if (hasMineral == 1 and hasJetpackBase == 1 and hasJetpackStabilizer == 1 and hasDuctedFan == 1 and hasInjectorTank == 1 and hasDispersionUnit == 1) then
			creature:sendSystemMessage("@dungeon/death_watch:starting_to_craft")
			writeData(terminal:getObjectID() .. ":dwb:currentlycrafting", 1)
			writeData(terminal:getObjectID() .. ":dwb:targetitemindex", 1)
			
			local spawn = specialSpawnMapDWB["jetpackattack1"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = specialSpawnMapDWB["jetpackattack2"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = specialSpawnMapDWB["jetpackattack3"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = specialSpawnMapDWB["jetpackattack4"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			
			local spawn = specialSpawnMapDWB["droidengineerattack1"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = specialSpawnMapDWB["droidengineerattack2"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = specialSpawnMapDWB["droidengineerattack3"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = specialSpawnMapDWB["droidengineerattack4"]
			spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			
			DWB:startCraftingProcess(pParent, droid)
		else
			creature:sendSystemMessage("@dungeon/death_watch:items_still_needed")
			if hasJetpackBase == 0 then
				creature:sendSystemMessage("@dungeon/death_watch:jetpack_base")	
			end
			
			if hasJetpackStabilizer == 0 then
				creature:sendSystemMessage("@dungeon/death_watch:stabilizer")
			end
			
			if hasDuctedFan == 0 then
				creature:sendSystemMessage("@dungeon/death_watch:ducted_fan")
			end
			
			if hasInjectorTank == 0 then
				creature:sendSystemMessage("@dungeon/death_watch:fuel_injector")
			end
			
			if hasDispersionUnit == 0 then
				creature:sendSystemMessage("@dungeon/death_watch:dispersion")
			end 
			
			if hasMineral == 0 then
				creature:sendSystemMessage("@dungeon/death_watch:alum_mineral")
			end
		end
	end

	return 0
end

function death_watch_bunker_crafting_droid_jetpack:removeObject(droid, ingredient, slot)
	return false
end

death_watch_bunker_crafting_droid = { }

function death_watch_bunker_crafting_droid:canAddObject(droid, ingredient, slot)
	if ingredient == nil then
		return false
	end
	
	if slot ~= -1 then
		return false
	end
	
	local object = LuaSceneObject(ingredient)
	pParent = object:getParent()
	
	if pParent == nil then
		return false
	end
	
	local parent = LuaSceneObject(pParent)
	pParent = parent:getParent()
	
	if pParent == nil then
		return false
	end
	
	local parent = LuaSceneObject(pParent)
	if parent:isCreatureObject() == false then
		return false
	end
	
	local creature = LuaCreatureObject(pParent) 
	
	local terminal = LuaSceneObject(droid)
	number = readData(terminal:getObjectID() .. ":dwb:craftingterminal")
	template = object:getTemplateObjectPath()
	
	userid = readData(terminal:getObjectID() .. ":dwb:user")
	
	if userid ~= 0 and userid ~= creature:getObjectID() then
		creature:sendSystemMessage("@dungeon/death_watch:same_user_only")
		return false
	end	
	
	if creature:hasSkill(TERMINALSKILLS[number + 4]) == false then
		creature:sendSystemMessage(TERMINALSKILLMESSAGE[number])
		return false
	end
	
	hasMineral = readData(terminal:getObjectID() .. ":dwb:alummineral")
	hasBL = readData(terminal:getObjectID() .. ":dwb:binary")
	hasPLC = readData(terminal:getObjectID() .. ":dwb:protective")
	hasArmorPart = readData(terminal:getObjectID() .. ":dwb:bharmorpart")
	
	if template == BINARYLIQUID then
		if hasBL == 0 then
			return true
		else
			creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	elseif template == PROTECTIVELIQUID then
		if hasPLC == 0 then
			return true
		else
			creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	elseif template == ALUMMINERAL then
		if hasMineral == 0 then
			return true
		else
			creature:sendSystemMessage("@dungeon/death_watch:already_has_component")
		end
	else
		local table = DOORS[number + 4]
		for i,v in ipairs(table) do
			if template == v then
				if hasArmorPart == 0 then
					return true
				else
					creature:sendSystemMessage("@dungeon/death_watch:making_something_else")
				end
			end
		end
	end
		
	return false
end

function death_watch_bunker_crafting_droid:transferObject(droid, ingredient, slot)
	if (ingredient == nil) then
		return 0
	end

	if slot == -1 then
		local object = LuaSceneObject(ingredient)
		
		pParent = object:getParent()
	
		if pParent == nil then
			return 0
		end
		
		local parent = LuaSceneObject(pParent)
		pParent = parent:getParent()
		
		if pParent == nil then
			return 0
		end
		
		local parent = LuaSceneObject(pParent)
		if parent:isCreatureObject() == false then
			return 0
		end
		
		local creature = LuaCreatureObject(pParent)
		
		local terminal = LuaSceneObject(droid)
		number = readData(terminal:getObjectID() .. ":dwb:craftingterminal")
		template = object:getTemplateObjectPath()
		
		if template == BINARYLIQUID then
			writeData(terminal:getObjectID() .. ":dwb:binary", 1)
			-- avoid Locker issues
			createEvent(500, "DWB", "destroyIngredient", ingredient)
		elseif template == PROTECTIVELIQUID then
			writeData(terminal:getObjectID() .. ":dwb:protective", 1)
			-- avoid Locker issues
			createEvent(500, "DWB", "destroyIngredient", ingredient)
		elseif template == ALUMMINERAL then
			writeData(terminal:getObjectID() .. ":dwb:alummineral", 1)
			-- avoid Locker issues
			createEvent(500, "DWB", "destroyIngredient", ingredient)
		else
			local table = DOORS[number + 4]
			for i,v in ipairs(table) do
				if template == v then
					writeData(terminal:getObjectID() .. ":dwb:bharmorpart", 1)
					writeData(terminal:getObjectID() .. ":dwb:targetitemindex", i)
				end
			end
			if (readData(terminal:getObjectID() .. ":dwb:bharmorpart") == 1) then
				-- avoid Locker issues
				createEvent(500, "DWB", "destroyIngredient", ingredient)
			else
				return 0
			end
		end
		
		hasMineral = readData(terminal:getObjectID() .. ":dwb:alummineral")
		hasBL = readData(terminal:getObjectID() .. ":dwb:binary")
		hasPLC = readData(terminal:getObjectID() .. ":dwb:protective")
		hasArmorPart = readData(terminal:getObjectID() .. ":dwb:bharmorpart")
		
		userid = readData(terminal:getObjectID() .. ":dwb:user")
		if userid == 0 then
			writeData(terminal:getObjectID() .. ":dwb:user", creature:getObjectID())
			writeData(creature:getObjectID() .. ":dwb:terminal", terminal:getObjectID())
		end
		
		if (hasMineral == 1 and hasBL == 1 and hasPLC == 1 and hasArmorPart == 1) then
			creature:sendSystemMessage("@dungeon/death_watch:starting_to_craft")
			writeData(terminal:getObjectID() .. ":dwb:currentlycrafting", 1)
			if number == 1 then
				local spawn = specialSpawnMapDWB["armorattack1"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["armorattack2"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["armorattack3"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["armorattack4"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				
			elseif number == 2 then
				local spawn = specialSpawnMapDWB["jetpackattack1"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["jetpackattack2"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["jetpackattack3"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["jetpackattack4"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				
				local spawn = specialSpawnMapDWB["droidengineerattack1"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["droidengineerattack2"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["droidengineerattack3"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["droidengineerattack4"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			elseif number == 3 then
				local spawn = specialSpawnMapDWB["tailorattack1"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["tailorattack2"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["tailorattack3"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
				local spawn = specialSpawnMapDWB["tailorattack4"]
				spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			end
			
			DWB:startCraftingProcess(pParent, droid)
		else
			creature:sendSystemMessage("@dungeon/death_watch:items_still_needed")
			if hasBL == 0 then
				creature:sendSystemMessage("@dungeon/death_watch:binary_liquid")	
			end
			
			if hasPLC == 0 then
				creature:sendSystemMessage("@dungeon/death_watch:emulsifier")
			end
			
			if hasArmorPart == 0 then
				creature:sendSystemMessage(PARTSTRINGS[number])
			end 
			
			if hasMineral == 0 then
				creature:sendSystemMessage("@dungeon/death_watch:alum_mineral")
			end
		end
	end

	return 0
end

function death_watch_bunker_crafting_droid:removeObject(droid, ingredient, slot)
	return false
end

--------------------------------------------------------------
--   Sui Callbacks                                           -
--------------------------------------------------------------

function DWB:craftingConfirmCallback(pCreature, pSui, cancelPressed)
	local creature = LuaCreatureObject(pCreature)
	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()
	
	if (pUsingObject == nil) then
		return 0
	end
	
	local terminal = LuaSceneObject(pUsingObject)
	
	step = readData(terminal:getObjectID() .. ":dwb:currentlycrafting")
	
	if step == 1 then
		writeData(terminal:getObjectID() .. ":dwb:currentlycrafting", 2)
		creature:sendSystemMessage("@dungeon/death_watch:alum_process_begun")
		createEvent(5 * 1000, "DWB", "nextCraftingStep", pUsingObject)
	elseif step == 3 then
		writeData(terminal:getObjectID() .. ":dwb:currentlycrafting", 4)
		creature:sendSystemMessage("@dungeon/death_watch:aeration_process_begun")
		createEvent(5 * 1000, "DWB", "finishCraftingStep", pUsingObject)
	end
	
	return 0
end

--------------------------------------------------------------
--   Provide Testing Assistance to Players                   -
--------------------------------------------------------------
function DWB:testSpatial(pDroid, pPlayer)
	local droid = LuaSceneObject(pDroid)
	local player = LuaCreatureObject(pPlayer)
	distance = droid:getDistanceTo(pPlayer)
	
	if distance == 0 then
		return 0
	elseif distance < 20 then
		spatialChat(pDroid, "Welcome to the Death Watch Bunker! To ease with testing, these guys behind me can give you Quests.")
		createEvent(15 * 1000, "DWB", "testSecond", pDroid)
		createEvent(200 * 1000, "DWB", "testRepeat", pDroid) 
		return 1
	else
		return 0
	end
end

function DWB:testSecond(pDroid)
	spatialChat(pDroid, "Missing Features: Foreman Quest, Rebreather Quest, Ventilation Quest and Blastromech Control. Known Bugs: Wrong animations for Battle Droids. Looted Schematics not working.")
	createEvent(15 * 1000, "DWB", "testThird", pDroid)
end

function DWB:testThird(pDroid)
	spatialChat(pDroid, "DWB Info: Finish Boba Fett's conversation to gain entry. Use the passkeys dropped from named NPCs to get past the three doors. They are spawned by using the Door Control Terminals.")
end 

function DWB:testRepeat(pDroid)
	createObserver(OBJECTINRANGEMOVED, "DWB", "testSpatial", pDroid)
end

function DWB:testSpatial2(pDroid, pPlayer)
	local droid = LuaSceneObject(pDroid)
	local player = LuaCreatureObject(pPlayer)
	distance = droid:getDistanceTo(pPlayer)
	
	if distance == 0 then
		return 0
	elseif distance < 20 then
		spatialChat(pDroid, "Welcome to the Death Watch Bunker! Feel free to gather around these flags if you are looking for a group.")
		createEvent(120 * 1000, "DWB", "testRepeat2", pDroid) 
		return 1
	else
		return 0
	end
end

function DWB:testRepeat2(pDroid)
	createObserver(OBJECTINRANGEMOVED, "DWB", "testSpatial2", pDroid)
end

function DWB:test(sceneObject)
	spawnedPointer = spawnMobile("endor", "death_watch_herald_rebel", 1, -4659, 14.4, 4326.3, 80, 0)
	spawnedPointer = spawnMobile("endor", "boba_fett", 1, -4659, 14.4, 4324.3, 80, 0)
	spawnedPointer = spawnMobile("endor", "death_watch_herald_imperial", 1, -4659, 14.4, 4322.3, 80, 0)
	spawnedPointer = spawnMobile("endor", "r3", 1, -4656.7, 14.4, 4324.2, 93, 0)
	
	createObserver(OBJECTINRANGEMOVED, "DWB", "testSpatial", spawnedPointer)
	
	spawnedPointer = spawnSceneObject("endor", "object/tangible/event_perk/lambda_shuttle.iff", -4668,12.9,4291.4,0,0,0,1,0)
	
	spawnedPointer = spawnSceneObject("endor", "object/tangible/terminal/terminal_character_builder.iff", -4655,12.5,4293.1,0,0,0,1,0)
	--doesnt work spawnedPointer = spawnSceneObject("endor", "object/tangible/terminal/terminal_cloning.iff", -4663,14.4,4324.3,0,0,0,1,0)
	
	spawnedPointer = spawnSceneObject("endor", "object/tangible/terminal/terminal_character_builder.iff", 27.1,-61.3,-295.5,5996355,0,0,1,0)
	
	spawnedPointer = spawnMobile("endor", "imperial_recruiter", 1, -4655.8, 14.4, 4328.3, 179, 0)
	spawnedPointer = spawnMobile("endor", "rebel_recruiter", 1, -4653.8, 14.4, 4328.3, 179, 0)
	
	--Plattform:
	spawnedPointer = spawnSceneObject("endor", "object/static/structure/tatooine/palette_tatooine_style_01.iff", -4651,12.4,4294.0,0,0,0,1,0)
	--spawnedPointer = spawnSceneObject("endor", "object/tangible/event_perk/camp_pavilion_s2.iff", -4651,12.4,4294.0,0,0,0,1,0)

	spawnedPointer = spawnMobile("endor", "r3", 1, -4650.3, 12.5, 4293.1, 127, 0)
	createObserver(OBJECTINRANGEMOVED, "DWB", "testSpatial2", spawnedPointer)

	
	--Looking for DWB Group: Healer
	spawnedPointer = spawnSceneObject("endor", "object/tangible/event_perk/banner_generic_s01.iff", -4642.0,12.0,4294.1,0,0,0,1,0)
	local scene = LuaSceneObject(spawnedPointer)
	scene:setCustomObjectName("LFG: Healer")
	
	--Looking for DWB Group: Combat Profession
	spawnedPointer = spawnSceneObject("endor", "object/tangible/event_perk/banner_rebel_style_01.iff", -4649.6,12.1,4302.7,0,0,0,1,0)
	local scene = LuaSceneObject(spawnedPointer)
	scene:setCustomObjectName("LFG: Melee Combat")
	
	--Looking for DWB Group: Combat Profession
	spawnedPointer = spawnSceneObject("endor", "object/tangible/event_perk/banner_imperial_style_01.iff", -4649.5,12.6,4285.6,0,0,0,1,0)
	local scene = LuaSceneObject(spawnedPointer)
	scene:setCustomObjectName("LFG: Ranged Combat")
	

	--Looking for DWB Group: Crafter
	spawnedPointer = spawnSceneObject("endor", "object/tangible/event_perk/banner_generic_s02.iff", -4656.0,12.6,4294.0,0,0,0,1,0)
	local scene = LuaSceneObject(spawnedPointer)
	scene:setCustomObjectName("LFG: Crafter")
	
	--spawnedPointer = spawnSceneObject("endor", "object/tangible/event_perk/lambda_shuttle.iff", -4668,12.9,4291.4,0,0,0,1,0)
	--spawnedPointer = spawnSceneObject("endor", "object/tangible/event_perk/lambda_shuttle.iff", -4668,12.9,4291.4,0,0,0,1,0)
	--spawnedPointer = spawnSceneObject("endor", "object/tangible/event_perk/lambda_shuttle.iff", -4668,12.9,4291.4,0,0,0,1,0)
	--spawnedPointer = spawnSceneObject("endor", "object/tangible/event_perk/lambda_shuttle.iff", -4668,12.9,4291.4,0,0,0,1,0)
	
	if TEST == 1 then
		printf("Testing Environment Set Up - Players can now take DWB Quests directly on Endor\n")
	end
	
	return 1
end
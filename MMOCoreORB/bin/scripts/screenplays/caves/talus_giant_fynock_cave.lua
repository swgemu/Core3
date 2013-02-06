TalusGiantFynockCaveScreenPlay = ScreenPlay:new {
       numberOfActs = 1, screenplayName = "TalusGiantFynockCaveScreenPlay",

        lootContainers = {
           7955671,
	   7955670,
	   7955663,
           7955708,
           7955728,
	   7955686
        },
        
        lootLevel = 25, 
 
        lootGroups = {
                {
                        groups = {
                                {group = "color_crystals", chance = 160000},
                                {group = "junk", chance = 8240000},
                                {group = "melee_weapons", chance = 1000000},
                                {group = "clothing_attachments", chance = 300000},
                                {group = "armor_attachments", chance = 300000}
                        },
                        lootChance = 8000000
                }                                       
        },
        
        lootContainerRespawn = 1800
}
 
registerScreenPlay("TalusGiantFynockCaveScreenPlay", true)
 
function TalusGiantFynockCaveScreenPlay:start()
	if (isZoneEnabled("talus")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

 
function TalusGiantFynockCaveScreenPlay:spawnMobiles()    
        spawnMobile("talus", "fearful_fynock_youth", 300, 1550.4, 43.9, -912.0, -55, 0)
        spawnMobile("talus", "fearful_fynock_youth", 300, 1551.5, 43.2, -904.0, -150, 0)
        spawnMobile("talus", "fearful_fynock_youth", 300, 1543.8, 43.6, -907.4, 98, 0)

       	spawnMobile("talus", "fearful_fynock_youth", 300, 1536.4, 40.4, -841.2, -32, 0)
        spawnMobile("talus", "fearful_fynock_youth", 300, 1527.7, 40.3, -839.5, 66, 0)
        spawnMobile("talus", "fearful_fynock_youth", 300, 1531.4, 40.0, -828.7, 152, 0)

	spawnMobile("talus", "clipped_fynock", 300, 1538.9, 42.5, -870.0, 24, 0)
        spawnMobile("talus", "clipped_fynock", 300, 1536.4, 42.3, -859.0, 124, 0)
        spawnMobile("talus", "fynock", 300, 1548.6, 42.7, -867.7, -55, 0)

	spawnMobile("talus", "frenzied_fynock_guardian", 300, 1570.4, 44.6, -868.4, -87, 0)

	spawnMobile("talus", "frenzied_fynock_guardian", 300, 9.1, -7.9, -9.4, -51, 5625516)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, 11.7, -15.5, -27.6, -55, 5625517)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -10.3, -22.8, -27.5, -4, 5625517)

	spawnMobile("talus", "frenzied_fynock_guardian", 300, -8.2, -32.3, -59.3, -2, 5625518)
	spawnMobile("talus", "clipped_fynock", 300, 13.2, -32.2, -78.2, -117, 5625518)
	spawnMobile("talus", "clipped_fynock", 300, 9.9, -32.5, -76.1, -3, 5625518)
	spawnMobile("talus", "clipped_fynock", 300, 13.2, -32.2, -78.2, -117, 5625518)
	spawnMobile("talus", "fynock", 300, 9.0, -32.7, -72.0, 9, 5625518)
	spawnMobile("talus", "fynock", 300, 17.9, -32.9, -72.3, -125, 5625518)

	spawnMobile("talus", "fynock", 300, 46.6, -38.8, -51.1, -166, 5625519)
	spawnMobile("talus", "fynock", 300, 49.9, -38.9, -57.2, -145, 5625519)

	spawnMobile("talus", "feared_fynock_youth", 300, 51.8, -37.9, -91.5, -135, 5625519)
	spawnMobile("talus", "feared_fynock_youth", 300, 52.5, -37.8, -97.3, 175, 5625519)
	spawnMobile("talus", "feared_fynock_youth", 300, 50.8, -37.2, -102.4, -55, 5625519)
	spawnMobile("talus", "feared_fynock_youth", 300, 40.2, -38.0, -99.7, 60, 5625519)	
	spawnMobile("talus", "feared_fynock_youth", 300, 45.1, -38.6, -89.9, 134, 5625519)

	spawnMobile("talus", "glutted_fynock_queen", 300, -9.1, -37.7, -147.4, 31, 5625520)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -4.0, -38.1, -148.4, -58, 5625520)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, 2.0, -37.0, -144.1, -63, 5625520)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, 1.7, -36.8, -137.5, -57, 5625520)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -12.7, -36.1, -136.2, 79, 5625520)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, 1.3, -36.7, -130.6, 59, 5625520)

	spawnMobile("talus", "fynock", 300, 70.2, -37.0, -122.8, -128, 5625520)
	spawnMobile("talus", "fynock", 300, 66.3, -37.2, -120.2, -172, 5625520)
	spawnMobile("talus", "fynock", 300, 63.2, -38.3, -123.4, 95, 5625520)
	spawnMobile("talus", "fynock", 300, 65.8, -39.1, -128.0, 17, 5625520)
	spawnMobile("talus", "fynock", 300, 72.0, -37.7, -126.5, -47, 5625520)

	spawnMobile("talus", "frenzied_fynock_guardian", 300, 58.7, -48.8, -176.6, 71, 5625520)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, 60.7, -49.2, -181.3, 33, 5625520)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, 63.5, -49.1, -181.4, -29, 5625520)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, 65.5, -49.1, -178.6, -85, 5625520)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, 64.8, -49.2, -174.7, -139, 5625520)
	spawnMobile("talus", "glutted_fynock_queen", 300, 62.0, -48.8, -178.1, -28, 5625520)

	spawnMobile("talus", "glutted_fynock_queen", 300, -10.8, -55.1, -261.8, -38, 5625522)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -23.9, -55.4, -257.1, 14, 5625522)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -20.7, -57.7, -241.6, 38, 5625522)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -4.5, -56.9, -241.1, -23, 5625522)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -1.3, -55.8, -231.3, -48, 5625522)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -18.7, -56.7, -220.1, 42, 5625522)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -6.0, -57.6, -209.5, -39, 5625522)

	spawnMobile("talus", "fynock", 300, -61.1, -62.0, -195.6, 30, 5625523)
	spawnMobile("talus", "fynock", 300, -55.6, -62.0, -195.3, -15, 5625523)
	spawnMobile("talus", "fynock", 300, -55.7, -63.0, -182.7, -143, 5625523)
	spawnMobile("talus", "fynock", 300, -61.0, -61.3, -161.9, -118, 5625523)
	spawnMobile("talus", "fynock", 300, -66.7, -62.2, -160.5, 134, 5625523)
	spawnMobile("talus", "fynock", 300, -66.0, -61.6, -168.2, 24, 5625523)
	spawnMobile("talus", "fynock", 300, -86.6, -64.3, -171.5, -89, 5625523)
	spawnMobile("talus", "fynock", 300, -87.9, -65.1, -176.5, -75, 5625523)
	spawnMobile("talus", "fynock", 300, -95.1, -64.4, -180.6, -25, 5625523)
	spawnMobile("talus", "fynock", 300, -101.4, -63.8, -178.1, 38, 5625523)
	spawnMobile("talus", "fynock", 300, -105.7, -62.8, -172.3, 63, 5625523)
	spawnMobile("talus", "fynock", 300, -101.6, -64.8, -162.5, 125, 5625523)
	spawnMobile("talus", "fynock", 300, -90.4, -65.4, -163.2, -143, 5625523)
	spawnMobile("talus", "clipped_fynock", 300, -93.7, -66.0, -167.7, -143, 5625523)
	spawnMobile("talus", "clipped_fynock", 300, -91.6, -65.3, -172.6, -85, 5625523)
	spawnMobile("talus", "clipped_fynock", 300, -96.5, -64.7, -177.8, -21, 5625523)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -103.5, -61.2, -131.7, -161, 5625523)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -108.3, -61.6, -126.7, -93, 5625523)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -102.2, -62.3, -122.4, 0, 5625523)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -95.0, -62.4, -125.7, 76, 5625523)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -98.5, -61.4, -132.3, 143, 5625523)
	spawnMobile("talus", "fearful_fynock_youth", 300, -103.9, -62.5, -124.7, 140, 5625523)
	spawnMobile("talus", "fearful_fynock_youth", 300, -99.8, -62.4, -124.2, -151, 5625523)
	spawnMobile("talus", "fearful_fynock_youth", 300, -100.7, -62.0, -129.7, -20, 5625523)

	spawnMobile("talus", "fynock", 300, -65.9, -62.8, -85.6, -114, 5625524)
	spawnMobile("talus", "fynock", 300, -62.8, -60.7, -97.4, -115, 5625524)
	spawnMobile("talus", "fynock", 300, -61.7, -60.5, -107.9, -131, 5625524)
	spawnMobile("talus", "fynock", 300, -51.7, -60.8, -112.7, -142, 5625524)
	spawnMobile("talus", "fynock", 300, -53.8, -60.6, -102.5, -42, 5625524)
	spawnMobile("talus", "fynock", 300, -57.4, -61.3, -91.8, -3, 5625524)
	spawnMobile("talus", "fynock", 300, -53.1, -61.3, -79.0, 37, 5625524)
	spawnMobile("talus", "fynock", 300, -43.8, -61.9, -86.9, -16, 5625524)
	spawnMobile("talus", "fynock", 300, -40.8, -62.0, -98.4, 69, 5625524)
	spawnMobile("talus", "fynock", 300, -39.3, -61.9, -112.7, -52, 5625524)
	spawnMobile("talus", "fynock", 300, -28.3, -61.9, -111.6, 41, 5625524)
	spawnMobile("talus", "fynock", 300, -25.4, -61.1, -103.0, -49, 5625524)
	spawnMobile("talus", "fynock", 300, -30.8, -62.6, -83.8, -94, 5625524)

	spawnMobile("talus", "frenzied_fynock_guardian", 300, -24.1, -71.8, -145.7, -25, 5625525)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -18.9, -71.0, -139.9, -57, 5625525)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -18.9, -69.4, -132.0, -75, 5625525)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -28.2, -69.7, -131.3, -6, 5625525)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -32.4, -72.3, -143.2, -103, 5625525)

	spawnMobile("talus", "glutted_fynock_queen", 300, -73.3, -91.3, -160.7, 30, 5625523)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -68.1, -88.5, -155.7, 26, 5625523)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -74.1, -90.8, -151.7, -33, 5625523)
	spawnMobile("talus", "frenzied_fynock_guardian", 300, -83.3, -91.0, -154.4, 156, 5625523)

	spawnMobile("talus", "giant_fynock", 300, -91.9, -92.9, -97.5, 175, 5625526)
end


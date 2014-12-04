TalusGiantDecayMiteCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1, 

	screenplayName = "TalusGiantDecayMiteCaveScreenPlay",

	lootContainers = {
		5625575,
		5625569,
		5625579,
		5625591,
		5995655,
		5995666,
		5995665,
		5995664
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
 
registerScreenPlay("TalusGiantDecayMiteCaveScreenPlay", true)
 
function TalusGiantDecayMiteCaveScreenPlay:start()
	if (isZoneEnabled("talus")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

function TalusGiantDecayMiteCaveScreenPlay:spawnMobiles()
	spawnMobile("talus", "giant_decay_mite_queen", 300, -95.4, -92.4, -108.9, -170, 5625547)
	spawnMobile("talus", "giant_decay_mite_guardian", 300, -99.0, -93.2, -121.0, 161, 5625547)
	spawnMobile("talus", "giant_decay_mite_guardian", 300, -86.3, -94.9, -127.3, -174, 5625547)
	spawnMobile("talus", "giant_decay_mite_guardian", 300, -28.7, -71.6, -139.3, 34, 5625546)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -23.0, -71.4, -141.8, -10, 5625546)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -25.6, -70.9, -135.8, -158, 5625546)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -22.1, -61.7, -111.3, -77, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -20.3, -60.8, -102.0, -4, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -22.7, -61.8, -89.0, -91, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -33.4, -63.1, -84.6, -44, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -43.3, -62.2, -81.8, -15, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -43.9, -61.7, -97.4, 103, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -42.9, -61.6, -110.1, -141, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -55.0, -60.5, -108.5, 92, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -53.4, -60.6, -98.7, 17, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -56.5, -62.1, -84.1, -25, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -68.0, -62.3, -88.1, -136, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -68.3, -61.1, -96.2, 83, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -69.5, -60.6, -101.5, -122, 5625545)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -72.4, -62.1, -84.8, 51, 5625545)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -97.4, -62.3, -108.3, -173, 5625544)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -104.0, -60.7, -108.7, -130, 5625544)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -90.1, -62.1, -126.8, 141, 5625544)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -99.6, -61.3, -140.4, 174, 5625544)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -122.3, -61.7, -152.6, -58, 5625544)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -117.8, -62.0, -197.4, 107, 5625544)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -68.4, -61.8, -196.9, 30, 5625544)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, -68.6, -62.4, -160.2, -26, 5625544)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -89.7, -65.1, -178.1, -51, 5625544)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -96.3, -63.9, -183.0, -21, 5625544)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -103.3, -63.4, -175.5, 62, 5625544)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -91.8, -65.6, -167.7, -151, 5625544)
	spawnMobile("talus", "giant_decay_mite_guardian", 300, -43.2, -60.6, -181.3, 90, 5625544)
	spawnMobile("talus", "giant_decay_mite_guardian", 300, -17.5, -55.7, -259.1, -41, 5625543)
	spawnMobile("talus", "giant_decay_mite_guardian", 300, -25.4, -55.2, -257.1, 26, 5625543)
	spawnMobile("talus", "giant_decay_mite_guardian", 300, -6.5, -56.3, -235.5, -32, 5625543)
	spawnMobile("talus", "giant_decay_mite_guardian", 300, -19.9, -56.5, -220.6, 26, 5625543)
	spawnMobile("talus", "giant_decay_mite_guardian", 300, -6.2, -57.6, -209.8, -34, 5625543)
	spawnMobile("talus", "giant_decay_mite_protector", 300, 34.7, -51.2, -177.9, 16, 5625541)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, 33.4, -50.9, -174.4, 40, 5625541)
	spawnMobile("talus", "giant_decay_mite_protector", 300, 56.7, -48.6, -171.9, 39, 5625541)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, 61.8, -49.0, -174.7, 113, 5625541)
	spawnMobile("talus", "giant_decay_mite_protector", 300, 70.4, -46.4, -149.7, -15, 5625541)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, 69.5, -45.3, -143.9, -35, 5625541)
	spawnMobile("talus", "giant_decay_mite_protector", 300, 53.0, -36.9, -121.2, -102, 5625541)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, 58.5, -38.6, -122.6, 97, 5625541)
	spawnMobile("talus", "giant_decay_mite_protector", 300, 35.3, -43.3, -139.5, -49, 5625541)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, 40.3, -44.7, -143.7, -136, 5625541)
	spawnMobile("talus", "giant_decay_mite_guardian", 300, -4.0, -37.1, -139.4, 38, 5625541)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, 2.3, -36.7, -136.3, 43, 5625541)
	spawnMobile("talus", "giant_decay_mite_sentry", 300, 2.2, -36.5,-126.6, 78, 5625541)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -12.2, -36.1, -137.9, 137, 5625541)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -11.0, -36.6, -142.1, 112, 5625541)
	spawnMobile("talus", "giant_decay_mite_hatchling", 300, -5.6, -38.6, -150.7, -132, 5625541)
	spawnMobile("talus", "giant_decay_mite_protector", 300, 47.3, -38.2, -95.8, -29, 5625540)
	spawnMobile("talus", "giant_decay_mite_protector", 300, 43.4, -38.1, -97.3, -48, 5625540)
	spawnMobile("talus", "giant_decay_mite_protector", 300, 41.1, -37.9, -68.1, -16, 5625540)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, 16.0, -33.2, -70.4, -154, 5625539)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, 18.2, -31.6, -79.6, -110, 5625539)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, 5.6, -32.9, -77.5, -79, 5625539)
	spawnMobile("talus", "giant_decay_mite_harvester", 300, -9.3, -32.4, -72.3, -7, 5625539)
	spawnMobile("talus", "giant_decay_mite_soldier", 300, -5.8, -31.7, -56.9, -21, 5625539)
end

GarynRaidersBunkerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "GarynRaidersBunkerScreenPlay",

	lootContainers = {
		5555918,
		5555917,
		5555916,
		5555915,
		5555912,
		5555914
        },
        
        lootLevel = 15, 
 
        lootGroups = {
                {
                        groups = {
                                {group = "color_crystals", chance = 100000},
                                {group = "junk", chance = 6100000},
                                {group = "melee_weapons", chance = 1500000},
				{group = "pistols", chance = 500000},
				{group = "carbines", chance = 500000},
				{group = "rifles", chance = 500000},
                                {group = "clothing_attachments", chance = 400000},
                                {group = "armor_attachments", chance = 400000}
                        },
                        lootChance = 8000000
                }                                       
        },
        
        lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("GarynRaidersBunkerScreenPlay", true)

function GarynRaidersBunkerScreenPlay:start()
	if (isZoneEnabled("rori")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

function GarynRaidersBunkerScreenPlay:spawnMobiles()
	spawnMobile("rori", "garyns_prowler", 360, -6008.7, 116.3, -1848.6, 100, 0)
	spawnMobile("rori", "garyns_prowler", 360, -6006.9, 115.4, -1845.1, 84, 0)
	spawnMobile("rori", "garyns_prowler", 360, -5983.9, 120.5, -1771.6, 114, 0)
	spawnMobile("rori", "garyns_prowler", 360, -5984.8, 120.4, -1773.8, 117, 0)
	spawnMobile("rori", "garyns_prowler", 360, -5953.4, 84.7, -1835.2, 73, 0)
	spawnMobile("rori", "garyns_prowler", 360, -5950.0, 83.0, -1840.0, 66, 0)
	spawnMobile("rori", "garyns_prowler", 360, -5930.5, 85.0, -1879.1, 88, 0)
	spawnMobile("rori", "garyns_prowler", 360, -5930.7, 85.0, -1882.3, 91, 0)
	spawnMobile("rori", "garyns_thief", 360, -6025.7, 117.5, -1825.8, 77, 0)
	spawnMobile("rori", "garyns_thief", 360, -6024.4, 117.9, -1818.0, 123, 0)
	spawnMobile("rori", "garyns_prowler", 360, -3.8, 0.3, 2.8, 83, 5555842)
	spawnMobile("rori", "garyns_prowler", 360, -3.6, 0.3, 4.3, 79, 5555842)
	spawnMobile("rori", "garyns_pirate", 360, 4.3, 0.3, -4.5, -78, 5555843)
	spawnMobile("rori", "garyns_mugger", 360, -6.9, -6.8, -6.2, 19, 5555845)
	spawnMobile("rori", "garyns_prowler", 360, -0.9, -6.8, -5.7, -22, 5555845)
	spawnMobile("rori", "garyns_prowler", 360, -2.8, -6.8, -5.3, -15, 5555845)
	spawnMobile("rori", "garyns_prowler", 360, -8.1, -6.8, -16.0, 36, 5555846)
	spawnMobile("rori", "garyns_prowler", 360, -7.5, -6.8, -13.1, 78, 5555846)
	spawnMobile("rori", "garyns_pirate", 360, 2.3, -6.8, -15.8, -50, 5555846)
	spawnMobile("rori", "garyns_pirate", 360, 6.4, -6.8, -14.4, -88, 5555846)
	spawnMobile("rori", "garyns_mugger", 360, 8.2, -6.8, -12.5, -96, 5555846)
	spawnMobile("rori", "garyns_pirate", 360, 7.1, -6.8, -3.2, -168, 5555847)
	spawnMobile("rori", "garyns_mugger", 360, 3.2, -6.8, -3.5, 147, 5555847)
	spawnMobile("rori", "garyns_mugger", 360, 5.1, -6.8, -2.4, 165, 5555847)
	spawnMobile("rori", "garyns_pirate", 360, -5.9, -13.8, -0.5, 32, 5555849)
	spawnMobile("rori", "garyns_pirate", 360, -3.8, -13.8, -0.9, 17, 5555849)
	spawnMobile("rori", "garyns_mugger", 360, -6.9, -13.8, -8.0, 15, 5555849)
	spawnMobile("rori", "garyns_mugger", 360, -4.6, -13.8, -7.3, 10, 5555849)
	spawnMobile("rori", "garyns_marauder", 360, -4.0, -13.8, -15.3, 3, 5555849)
end

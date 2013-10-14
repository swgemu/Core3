KobolaBunkerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "KobolaBunkerScreenPlay",

	lootContainers = {
		479811,
		479878,
		479898,
		479908,
		479910,
		479918,
		479943,
		479945,
		479956

        },
        
        lootLevel = 18, 
 
        lootGroups = {
                {
                        groups = {
                                {group = "color_crystals", chance = 100000},
                                {group = "junk", chance = 6400000},
				{group = "heavy_weapons_consumable", chance = 500000},
                                {group = "melee_weapons", chance = 900000},
				{group = "pistols", chance = 300000},
				{group = "carbines", chance = 300000},
				{group = "rifles", chance = 300000},
                                {group = "clothing_attachments", chance = 600000},
                                {group = "armor_attachments", chance = 600000}
                        },
                        lootChance = 8000000
                }                                       
        },
        
        lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("KobolaBunkerScreenPlay", true)

function KobolaBunkerScreenPlay:start()
	if (isZoneEnabled("rori")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

function KobolaBunkerScreenPlay:spawnMobiles()
	spawnMobile("rori", "kobola_assassin", 360,  7346.7, 76.0, 97.9, -85, 0)
	spawnMobile("rori", "kobola_assassin", 360,  7347.0, 75.1, 94.9, -83, 0)

	spawnMobile("rori", "kobola_guard", 360,  -15.0, -0.6, 2.6, -16, 479723)
	spawnMobile("rori", "kobola_guard", 360,  -19.7, -0.7, 2.8, -8, 479723)
	spawnMobile("rori", "kobola_miner", 360,  14.2, -22.3, -5.4, -40, 479723)
	spawnMobile("rori", "kobola_miner", 360,  12.3, -22.2, -5.3, 14, 479723)
	spawnMobile("rori", "kobola_guard", 360,  25.7, -28.6, -11.3, -50, 479723)
	spawnMobile("rori", "kobola_guard", 360,  26.4, -27.7, -8.5, -96, 479723)

	spawnMobile("rori", "kobola_miner", 360,  22.7, -41.6, -71.1, -143, 479724)
	spawnMobile("rori", "kobola_miner", 360,  22.6, -42.1, -67.9, -129, 479724)
	spawnMobile("rori", "kobola_guard", 360,  23.9, -42.3, -68.8, -121, 479724)
	spawnMobile("rori", "kobola_guard", 360,  52.9, -48.9, -55.3, -137, 479724)
	spawnMobile("rori", "kobola_guard", 360,  55.2, -48.5, -57.5, -111, 479724)
	spawnMobile("rori", "kobola_assassin", 360,  49.0, -47.4, -12.2, -179, 479724)
	spawnMobile("rori", "kobola_guard", 360,  46.1, -47.0, -15.1, -174, 479724)
	spawnMobile("rori", "kobola_foreman", 360,  56.9, -68.5, -41.7, -104, 479724)
	spawnMobile("rori", "kobola_miner", 360,  55.2, -68.4, -40.4, -97, 479724)
	spawnMobile("rori", "kobola_miner", 360,  54.8, -68.2, -43.5, -112, 479724)

	spawnMobile("rori", "kobola_foreman", 360,  47.3, -49.0, -99.8, -115, 479732)

	spawnMobile("rori", "kobola_miner", 360,  92.1, -46.4, -96.2, 3, 479727)
	spawnMobile("rori", "kobola_miner", 360,  95.7, -45.6, -98.1, 68, 479727)
	spawnMobile("rori", "kobola_miner", 360,  94.9, -45.7, -101.2, 161, 479727)

	spawnMobile("rori", "kobola_pitboss", 360,  79.3, -46.5, -142.0, 73, 479733)
	spawnMobile("rori", "kobola_miner", 360,  77.8, -46.2, -136.0, -42, 479733)
	spawnMobile("rori", "kobola_miner", 360,  77.3, -45.8, -147.3, -160, 479733)

	spawnMobile("rori", "kobola_guard", 360,  95.4, -62.0, -13.2, -89, 479725)
	spawnMobile("rori", "kobola_assassin", 360,  95.3, -62.2, -16.0, -81, 479725)
	spawnMobile("rori", "kobola_guard", 360,  94.9, -62.6, -19.4, -77, 479725)

	spawnMobile("rori", "kobola_miner", 360,  94.2, -74.2, -56.8, 35, 479726)
	spawnMobile("rori", "kobola_miner", 360,  96.5, -74.0, -57.4, 65, 479726)
	spawnMobile("rori", "kobola_miner", 360,  96.8, -74.9, -60.9, 86, 479726)
	spawnMobile("rori", "kobola_foreman", 360,  93.6, -75.4, -60.2, 40, 479726)
	spawnMobile("rori", "kobola_miner", 360,  92.8, -76.4, -88.7, 113, 479726)
	spawnMobile("rori", "kobola_miner", 360,  95.4, -76.2, -85.3, 115, 479726)
	spawnMobile("rori", "kobola_foreman", 360,  91.6, -76.3, -84.4, 139, 479726)
	spawnMobile("rori", "kobola_assassin", 360,  65.6, -76.8, -88.3, -3, 479726)
	spawnMobile("rori", "kobola_assassin", 360,  60.8, -76.1, -81.0, 4, 479726)

	spawnMobile("rori", "kobola_miner", 360,  54.6, -70.1, -121.2, -137, 479728)
	spawnMobile("rori", "kobola_miner", 360,  54.1, -70.5, -118.3, -134, 479728)
	spawnMobile("rori", "kobola_foreman", 360,  57.4, -70.6, -119.0, -128, 479728)

	spawnMobile("rori", "kobola_foreman", 360,  86.5, -66.8, -142.2, -81, 479729)
	spawnMobile("rori", "kobola_assassin", 360,  89.2, -66.8, -141.7, -24, 479729)
	spawnMobile("rori", "kobola_assassin", 360,  86.9, -66.9, -140.4, -42, 479729)

	spawnMobile("rori", "kobola_miner", 360,  112.7, -67.2, -89.7, -53, 479730)
	spawnMobile("rori", "kobola_miner", 360,  114.4, -67.0, -86.5, -35, 479730)
	spawnMobile("rori", "kobola_miner", 360,  142.7, -66.4, -85.5, 34, 479730)
	spawnMobile("rori", "kobola_miner", 360,  144.7, -66.3, -87.6, 65, 479730)
	spawnMobile("rori", "kobola_pitboss", 360,  133.5, -66.5, -105.6, -103, 479730)
	spawnMobile("rori", "kobola_assassin", 360,  136.0, -66.2, -102.9, -95, 479730)
	spawnMobile("rori", "kobola_assassin", 360,  135.9, -66.2, -107.7, -88, 479730)
	spawnMobile("rori", "kobola_miner", 360,  155.1, -65.6, -126.1, 114, 479730)
	spawnMobile("rori", "kobola_miner", 360,  155.6, -65.6, -130.6, 128, 479730)
	spawnMobile("rori", "kobola_miner", 360,  151.4, -66.1, -130.5, 165, 479730)
	spawnMobile("rori", "kobola_foreman", 360,  150.9, -66.6, -125.2, 133, 479730)

	spawnMobile("rori", "kobola_pitboss", 360,  189.8, -66.2, -106.1, -71, 479731)
	spawnMobile("rori", "kobola_pitboss", 360,  190.1, -66.4, -99.2, -83, 479731)
	spawnMobile("rori", "kobola_underboss", 360,  187.1, -66.1, -101.6, -84, 479731)
end

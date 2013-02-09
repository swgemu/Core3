SpiderClanCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "SpiderClanCaveScreenPlay",

	lootContainers = {
		5165581,
		5165583,
		5165584,
		5165585,
		5165586,
		5165587,
		5165588,
		5165591,
		5165592,
		5165593
	},
	
	lootLevel = 36,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 1000000},
				{group = "junk", chance = 5000000},
				{group = "rifles", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 1500000},
				{group = "armor_attachments", chance = 1500000}
			},
			lootChance = 10000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("SpiderClanCaveScreenPlay", true)

function SpiderClanCaveScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function SpiderClanCaveScreenPlay:spawnMobiles()
        --Cell[3695702]
        spawnMobile("dathomir", "spiderclan_sentry", 900, 2.1, -5.8, 6.9, -46, 3695702)
        spawnMobile("dathomir", "spiderclan_sentry", 900, -1.4, -13.2, -6.8, 11, 3695702)
        spawnMobile("dathomir", "spiderclan_sentry", 900, 12.0, -15.0, -7.0, -93, 3695702)

        --Cell[3695703]
        spawnMobile("dathomir", "spiderclan_acolyte", 900, -8.8, -30.6, -26.5, 75, 3695703)

        --Cell[3695704]
        spawnMobile("dathomir", "spiderclan_sentry", 900, -12.5, -41.1, -65.6, 164, 3695704)
        spawnMobile("dathomir", "spiderclan_sentinel", 900, -9.4, -40.5, -84.4, -163, 3695704)
        spawnMobile("dathomir", "spiderclan_sentry", 900, 0.7, -40.9, -77.8, 55, 3695704)
        spawnMobile("dathomir", "spiderclan_sentry", 900, 6.4, -40.9, -75.1, -85, 3695704)
        spawnMobile("dathomir", "spiderclan_acolyte", 900, -0.2, -40.9, -73.9, 124, 3695704)

        --Cell[3695705]
        spawnMobile("dathomir", "spiderclan_sentinel", 900, 38.9, -46.0, -52.8, 151, 3695705)
        spawnMobile("dathomir", "spiderclan_acolyte", 900, 46.0, -47.1, -55.1, -86, 3695705)
        spawnMobile("dathomir", "spiderclan_sentry", 900, 47.3, -46.2, -93.7, -73, 3695705)
        spawnMobile("dathomir", "spiderclan_sentry", 900, 43.0, -46.1, -94.3, 67, 3695705)

        --Cell[3695706]
        spawnMobile("dathomir", "spiderclan_sentinel", 900, 28.9, -46.0, -52.8, 151, 3695706)
        spawnMobile("dathomir", "spiderclan_sentinel", 900, 19.3, -47.7, -133.4, 11, 3695706)
        spawnMobile("dathomir", "spiderclan_sentry", 900, -1.5, -45.1, -135.2, -145, 3695706)
        spawnMobile("dathomir", "spiderclan_auspex", 900, -7.7, -45.0, -136.9, 121, 3695706)
        spawnMobile("dathomir", "spiderclan_sentinel", 900, -6.8, -45.1, -142.4, 39, 3695706)
        spawnMobile("dathomir", "spiderclan_sentry", 900, 54.7, -48.8, -129.1, 148, 3695706)
        spawnMobile("dathomir", "spiderclan_sentry", 900, 57.6, -49.1, -131.4, -54, 3695706)
        spawnMobile("dathomir", "spiderclan_sentinel", 900, 59.2, -55.3, -151.1, -138, 3695706)
        spawnMobile("dathomir", "spiderclan_sentry", 900, 63.0, -57.6, -165.1, -66, 3695706)
        spawnMobile("dathomir", "spiderclan_sentinel", 900, 56.1, -56.6, -170.0, -32, 3695706)
        spawnMobile("dathomir", "spiderclan_sentry", 900, 45.7, -56.6, -165.7, 68, 3695706)
        spawnMobile("dathomir", "spiderclan_protector", 900, 51.2, -56.2, -158.7, 134, 3695706)
        spawnMobile("dathomir", "spiderclan_elder", 3600, -6.4, -46.6, -150.8, 9, 3695706)
        
        --Cell[3695707]
        spawnMobile("dathomir", "spiderclan_sentry", 900, -9.0, -64.3, -188.5, 1, 3695707)
        spawnMobile("dathomir", "spiderclan_sentry", 900, -13.6, -64.1, -188.2, 1, 3695707)
        spawnMobile("dathomir", "spiderclan_sentry", 900, -28.1, -65.6, -177.6, 86, 3695707)
        spawnMobile("dathomir", "spiderclan_sentry", 900, -27.8, -64.4, -183.0, 85, 3695707)

        --Cell[3695708]
        spawnMobile("dathomir", "spiderclan_elder", 3600, -20.7, -62.8, -261.2, 18, 3695708)
        spawnMobile("dathomir", "spiderclan_web_dancer", 900, -12.0, -63.7, -260.5, -74, 3695708)
        spawnMobile("dathomir", "spiderclan_web_dancer", 900, 2.7, -63.4, -229.7, -99, 3695708)
          --v Spiders Here v--
        spawnMobile("dathomir", "cavern_spider", 900, -23.0, -65.6, -241.3, 67, 3695708)
        spawnMobile("dathomir", "cavern_spider", 900, -3.1, -65.2, -242.3, 7, 3695708)
        spawnMobile("dathomir", "cavern_spider", 900, 0.4, -63.6, -235.9, -161, 3695708)
        spawnMobile("dathomir", "cavern_spider", 900, -13.3, -63.6, -226.1, 5, 3695708)
        spawnMobile("dathomir", "cavern_spider", 900, -20.8, -65.2, -213.6, 57, 3695708)
        spawnMobile("dathomir", "cavern_spider", 900, -0.6, -65.0, -209.6, -81, 3695708)
          --^ Spiders Here ^--
          
        --Cell[3695709]
        spawnMobile("dathomir", "cavern_spider", 900, -64.8, -70.3, -197.4, 26, 3695709) 
        spawnMobile("dathomir", "spiderclan_web_dancer", 900, -64.5, -69.3, -187.8, 164, 3695709)
        spawnMobile("dathomir", "cavern_spider", 900, -56.4, -70.5, -192.1, -123, 3695709)  
        spawnMobile("dathomir", "spiderclan_web_dancer", 900, -117.9, -69.6, -200.4, 118, 3695709)
        spawnMobile("dathomir", "cavern_spider", 900, -111.1, -69.0, -205.1, -58, 3695709)  
        spawnMobile("dathomir", "cavern_spider", 900, -120.3, -69.0, -167.5, -174, 3695709)
        spawnMobile("dathomir", "spiderclan_web_dancer", 900, -120.4, -69.4, -172.0, 0, 3695709) 
        spawnMobile("dathomir", "cavern_spider", 900, -97.0, -73.7, -167.3, 163, 3695709)
        spawnMobile("dathomir", "spiderclan_web_dancer", 900, -93.5, -73.4, -174.1, -35, 3695709)
        spawnMobile("dathomir", "cavern_spider", 900, -101.1, -71.7, -175.6, 26, 3695709)
        
        spawnMobile("dathomir", "spiderclan_sentinel", 900, -98.1, -70.1, -109.7, -178, 3695709)
        spawnMobile("dathomir", "spiderclan_sentinel", 900, -92.5, -70.8, -111.2, -151, 3695709) 
        
        --Cell[3695710]
        spawnMobile("dathomir", "reclusive_cavern_spider", 900, -68.1, -68.8, -99.1, -14, 3695710)
        spawnMobile("dathomir", "reclusive_cavern_spider", 900, -65.3, -69.6, -91.5, -135, 3695710)
        spawnMobile("dathomir", "reclusive_cavern_spider", 900, -73.6, -70.2, -92.3, 127, 3695710)       
        spawnMobile("dathomir", "giant_cavern_spider_recluse", 900, -43.3, -69.8, -88.0, -140, 3695710)
        spawnMobile("dathomir", "reclusive_cavern_spider", 900, -55.9, -68.5, -115.9, -33, 3695710)
        spawnMobile("dathomir", "reclusive_cavern_spider", 900, -21.5, -69.4, -96.7, -91, 3695710)   
        spawnMobile("dathomir", "giant_cavern_spider_recluse", 900, -19.9, -68.7, -107.0, -34, 3695710)
        
        --Cell[3695711]
        local pQueen = spawnMobile("dathomir", "reclusive_cavern_spider_queen", 7200, -26.6, -80.0, -149.5, 0, 3695711)
        createObserver(OBJECTDESTRUCTION, "SpiderClanCaveScreenPlay", "notifyQueenDead", pQueen)
        
        spawnMobile("dathomir", "reclusive_cavern_spider", 900, -35.5, -80.4, -139.8, 129, 3695711)
        spawnMobile("dathomir", "reclusive_cavern_spider", 900, -27.3, -77.9, -132.0, 172, 3695711)
        spawnMobile("dathomir", "reclusive_cavern_spider", 900, -17.3, -77.4, -132.3, -144, 3695711)            
end

function SpiderClanCaveScreenPlay:notifyQueenDead(pQueen, pKiller)
     if (readData("spiderclancave:kiindray") == 0) then
          local pKiinDray = spawnMobile("dathomir", "kiin_dray", 0, -87.7, -100.8, -103.4, 174, 3695712)
          createObserver(OBJECTDESTRUCTION, "SpiderClanCaveScreenPlay", "notifyKiinDrayDead", pKiinDray)
          writeData("spiderclancave:kiindray",1)
     end
     
     return 0
end

function SpiderClanCaveScreenPlay:notifyKiinDrayDead(pKiinDray, pKiller)
     writeData("spiderclancave:kiindray", 0)
     
     return 1
end

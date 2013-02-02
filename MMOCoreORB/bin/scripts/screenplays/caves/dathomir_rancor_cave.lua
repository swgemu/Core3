RancorCaveScreenPlay = ScreenPlay:new { 
    numberOfActs = 1, 
    
    screenplayName = "RancorCaveScreenPlay",
    
    lootContainers = {
		9815402,
        9815403,
        9815404,
        9815405,
        9815406,
        9815412
	},
	
	lootLevel = 26,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 160000},
				{group = "junk", chance = 8240000},
				{group = "rifles", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
} 
 
registerScreenPlay("RancorCaveScreenPlay", true) 
 
function RancorCaveScreenPlay:start() 
        self:spawnMobiles() 
	self:initializeLootContainers()
end 
 
function RancorCaveScreenPlay:spawnMobiles() 
        --Cell[4335463]
        spawnMobile("dathomir", "enraged_bull_rancor", 600, -23.6, -27.5, -8.1, 87, 4335463)
        
        --Cell[4335464]
        spawnMobile("dathomir", "enraged_bull_rancor", 600, -23.8, -42.4, -64.0, 0, 4335464)
        spawnMobile("dathomir", "enraged_bull_rancor", 600, -50.6, -48.9, -61.7, 127, 4335464)
        spawnMobile("dathomir", "gnarled_rancor", 600, -49.1, -47.4, -12.0, 177, 4335464)
        spawnMobile("dathomir", "enraged_bull_rancor", 600, -54.4, -68.3, -40.0, -82, 4335464)
        
        --Cell[4335473]
        spawnMobile("dathomir", "enraged_bull_rancor", 600, -93.4, -46.6, -128.6, 3, 4335473)
          --Youths
        spawnMobile("dathomir", "rancor_youth", 600, -81.3, -46.2, -137.8, 152, 4335473)
        spawnMobile("dathomir", "rancor_youth", 600, -72.7, -45.6, -139.7, -123, 4335473)
        spawnMobile("dathomir", "rancor_youth", 600, -77.6, -45.8, -148.0, -19, 4335473)
        
        --Cell[4335465]
        spawnMobile("dathomir", "mutant_rancor", 600, -87.1, -62.2, -14.9, -178, 4335465)
        
        --Cell[4335466]
        spawnMobile("dathomir", "gnarled_rancor", 600, -79.0, -76.7, -89.2, 4, 4335466)
        
        --Cell[4335467]
        spawnMobile("dathomir", "mutant_rancor", 600, -95.4, -66.3, -109.3, 172, 4335467)
        
        --Cell[4335470]
          --Mutant/Enraged
        spawnMobile("dathomir", "enraged_bull_rancor", 600, -130.4, -66.8, -107.7, 91, 4335470)
          --Youths
        spawnMobile("dathomir", "rancor_youth", 600, -151.6, -66.5, -125.0, 69, 4335470)
        spawnMobile("dathomir", "rancor_youth", 600, -132.8, -66.6, -121.8, -82, 4335470)
        
          --Ancient
        --Cell[4335471]
        spawnMobile("dathomir", "ancient_bull_rancor", 720, -189.9, -66.5, -102.1, 87, 4335471)
                          
 
end

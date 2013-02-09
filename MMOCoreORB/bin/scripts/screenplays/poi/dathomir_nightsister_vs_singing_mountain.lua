NightSisterVsSingingMountainClanScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "NightSisterVsSingingMountainClanScreenPlay",
	
	lootContainers = {
		164427,
		164428,		
		164429,	
		164430			
	},
	
	lootLevel = 38,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 3500000},
				{group = "junk", chance = 3500000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("NightSisterVsSingingMountainClanScreenPlay", true)

function NightSisterVsSingingMountainClanScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function NightSisterVsSingingMountainClanScreenPlay:spawnMobiles()
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch",900,-2541,130.5,1581,179,0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch",900,-2500.6,123.6,1581,179,0)
	spawnMobile("dathomir", "singing_mountain_clan_councilwoman",3600,-2520.4,130,1598.8,179,0)
	spawnMobile("dathomir", "singing_mountain_clan_dragoon",900,-2520.4,124.2,1566.9,179,0)
	spawnMobile("dathomir", "singing_mountain_clan_guardian",1800,-2520.4,127.9,1586.9,179,0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate",900,-2539.3,125.6,1548.7,179,0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate",900,-2503.1,120.6,1548.7,179,0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor",900,-2550.2,129.6,1566.9,179,0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor",900,-2491.9,120.2,1566.9,179,0)	
	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer",900,-2538.1,127.6,1566.9,179,0)	
	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer",900,-2504.4,121.6,1566.9,179,0)	
	spawnMobile("dathomir", "singing_mountain_clan_scout",900,-2551,127.1,1548.7,179,0)	
	spawnMobile("dathomir", "singing_mountain_clan_scout",900,-2490.6,119.4,1548.7,179,0)	
	spawnMobile("dathomir", "singing_mountain_clan_sentry",900,-2520.4,122.9,1548.7,179,0)	
	

	spawnMobile("dathomir", "nightsister_spell_weaver",900,-2538.0,128.8,1488.5,0,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-2500.6,128.8,1488.6,0,0)
	spawnMobile("dathomir", "nightsister_elder",3600,-2519.9,130.6,1470,0,0)	
	spawnMobile("dathomir", "nightsister_protector",1800,-2521.2,130.2,1482.2,0,0)		
	spawnMobile("dathomir", "nightsister_stalker",900,-2519.9,128.4,1502.1,0,0)	
	spawnMobile("dathomir", "nightsister_sentinel",900,-2539.1,125.1,1527.8,0,0)	
	spawnMobile("dathomir", "nightsister_initiate",900,-2538.2,125.6,1518,0,0)	
	spawnMobile("dathomir", "nightsister_initiate",900,-2502.5,123.8,1520.9,0,0)	
	spawnMobile("dathomir", "nightsister_rancor",900,-2550.4,126.0,1502.7,0,0)
	spawnMobile("dathomir", "nightsister_rancor",900,-2489.1,125.2,1501.8,0,0)	
	spawnMobile("dathomir", "nightsister_rancor_tamer",900,-2499.2,127.1,1502,0,0)
	spawnMobile("dathomir", "nightsister_rancor_tamer",900,-2535.1,127.0,1502.3,0,0)	
	spawnMobile("dathomir", "nightsister_outcast",900,-2551.4,125.3,1518.1,0,0)	
	spawnMobile("dathomir", "nightsister_outcast",900,-2488.6,121.6,1521.7,0,0)	
	spawnMobile("dathomir", "nightsister_sentry",900,-2517.1,125.2,1519.9,0,0)		
end

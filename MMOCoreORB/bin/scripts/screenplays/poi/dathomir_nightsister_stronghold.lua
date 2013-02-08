NightSisterStrongholdScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "NightSisterStrongholdScreenPlay",
	
	lootContainers = {
		5035775
	},
	
	lootLevel = 26,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 160000},
				{group = "junk", chance = 8600000},
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

registerScreenPlay("NightSisterStrongholdScreenPlay", true)

function NightSisterStrongholdScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function NightSisterStrongholdScreenPlay:spawnMobiles()
	spawnMobile("dathomir", "nightsister_elder",3600,-3976.1,131.5,-171.3,-169,0)
	spawnMobile("dathomir", "nightsister_elder",3600,-4003.5,121,-270.1,-54,0)
	spawnMobile("dathomir", "nightsister_elder",3600,-4155.3,121.0,-99.8,51,0)
	spawnMobile("dathomir", "nightsister_rancor_tamer",900,-4107.2,126.3,-100,-24,0)
	spawnMobile("dathomir", "nightsister_protector",900,-4105.6,126.8,-94.5,178,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-4100.6,126.7,-95.5,-110,0)
	spawnMobile("dathomir", "nightsister_rancor_tamer",900,-4016.0,130.3,-139.0,6,0)
	spawnMobile("dathomir", "nightsister_protector",900,-4014.0,130.4,-136.8,-100,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-4019.4,129.8,-137.7,80,0)
	spawnMobile("dathomir", "nightsister_rancor_tamer",900,-3984.0,123.4,-231.0,0,0)
	spawnMobile("dathomir", "nightsister_protector",900,-3983.0,124.4,-226.9,-166,0)
	spawnMobile("dathomir", "nightsister_protector",900,-4017.5,121.0,-249.5,-64,0)	
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-3986.7,124.2,-225.4,178,0)
	spawnMobile("dathomir", "nightsister_sentinel",900,-4059.9,128.0,-157.0,0,0)
	spawnMobile("dathomir", "nightsister_sentry",900,-4058.3,127.8,-150.9,-175,0)
	spawnMobile("dathomir", "nightsister_stalker",900,-4062.8,128.3,-152.9,116,0)
	spawnMobile("dathomir", "nightsister_initiate",900,-4046.1,120.8,-188.7,37,0)
	spawnMobile("dathomir", "nightsister_rancor_tamer",900,-4039.4,120.7,-194.8,19,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-4035.4,121.2,-194.1,-4,0)
	spawnMobile("dathomir", "nightsister_protector",900,-4042.3,118.8,-230.7,-134,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-4047.7,119.1,-232.2,101,0)
	spawnMobile("dathomir", "nightsister_ranger",900,-4045.0,120.2,-261.8,-54,0)
	spawnMobile("dathomir", "nightsister_outcast",900,-3965.2,125.1,-237.1,-65,0)
	spawnMobile("dathomir", "nightsister_protector",900,-4150.9,134.6,-176.0,-62,0)	
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-4157.6,134.0,-173.4,111,0)
	spawnMobile("dathomir", "nightsister_sentinel",900,-4152.9,133.5,-168.5,178,0)	
	spawnMobile("dathomir", "nightsister_protector",900,-4142.0,126.9,-136.8,-52,0)	
	spawnMobile("dathomir", "nightsister_ranger",900,-4192.0,125.2,-132.9,110,0)
	spawnMobile("dathomir", "nightsister_ranger",900,-4190.3,124.7,-124.8,98,0)	
	spawnMobile("dathomir", "nightsister_protector",900,-4139.9,121.0,-82.8,84,0)		
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-4117.0,126.7,-116.6,-125,0)	
	spawnMobile("dathomir", "nightsister_stalker",900,-4122.8,126.2,-120.6,54,0)	
	spawnMobile("dathomir", "nightsister_protector",900,-4066.6,130.5,-105.8,38,0)	
	spawnMobile("dathomir", "nightsister_protector",900,-4060.1,130.5,-111.9,46,0)	
	spawnMobile("dathomir", "nightsister_sentry",900,-4067.4,126.3,-83.5,167,0)	
	spawnMobile("dathomir", "nightsister_protector",900,-3993.8,131.2,-194.4,-138,0)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-4028.1,126.3,-109.2,52,0)	
	spawnMobile("dathomir", "nightsister_ranger",900,-3992.4,129.6,-108.1,-64,0)		
	spawnMobile("dathomir", "nightsister_sentry",900,-3955.8,131.9,-204.4,-158,0)	
	spawnMobile("dathomir", "nightsister_sentry",900,-4084.6,133.6,-210.4,26,0)	
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-4080.4,132.9,-207.0,-105,0)	
	spawnMobile("dathomir", "nightsister_sentry",900,-4113.8,122.5,-57.2,-156,0)
	spawnMobile("dathomir", "nightsister_protector",900,-4024.4,126.7,-111.9,2,0)		
	
	

	spawnMobile("dathomir", "axkva_min",6400,-90.5,-101,-102.2,172,4115629)	
	spawnMobile("dathomir", "nightsister_protector",900,-98.1117,-102.689,-131.572,7,4115626)
	spawnMobile("dathomir", "nightsister_sentinel",900,-89.6414,-100.547,-149.769,2,4115626)	
	spawnMobile("dathomir", "nightsister_protector",900,-28.3439,-80.1922,-151.496,7,4115628)
	spawnMobile("dathomir", "nightsister_sentinel",900,-22.2057,-80.5683,-151.813,2,4115628)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-12.9025,-68.921,-96.3403,7,4115627)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-85.9,-100.8,-105.4,-118,4115629)
	spawnMobile("dathomir", "nightsister_sentinel",900,-99.1,-99.8,-105.1,168,4115629)	
	spawnMobile("dathomir", "nightsister_sentinel",900,-19.9525,-69.7168,-92.0932,2,4115627)
	spawnMobile("dathomir", "nightsister_protector",900,-52.8,-68.7,-103.5,20,4115627)
	spawnMobile("dathomir", "nightsister_sentinel",900,-77.9595,-70.2354,-89.9193,2,4115627)
	spawnMobile("dathomir", "nightsister_protector",900,-107.147,-68.531,-113.11,7,4115626)
	spawnMobile("dathomir", "nightsister_sentinel",900,-118.707,-69.6862,-123.213,2,4115626)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-122.558,-69.332,-138.946,7,4115626)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-104.958,-71.5983,-176.399,2,4115626)
	spawnMobile("dathomir", "nightsister_sentinel",900,-115.398,-69.2239,-172.659,7,4115626)
	spawnMobile("dathomir", "nightsister_protector",900,-121.94,-69.8514,-182.011,2,4115626)	
	spawnMobile("dathomir", "nightsister_protector",900,-115.618,-69.9586,-198.215,7,4115626)
	spawnMobile("dathomir", "nightsister_protector",900,-78.9,-101.0,-125.6,-139,4115629)	
	spawnMobile("dathomir", "nightsister_sentinel",900,-101.324,-68.9513,-203.529,2,4115626)
	spawnMobile("dathomir", "nightsister_protector",900,-68.4386,-69.8099,-196.707,7,4115626)
	spawnMobile("dathomir", "nightsister_sentinel",900,-20.5611,-64.3706,-179.909,2,4115624)
	spawnMobile("dathomir", "nightsister_sentinel",900,-11.0538,-64.4992,-199.182,7,4115624)
	spawnMobile("dathomir", "nightsister_protector",900,-13.1121,-64.7617,-221.124,2,4115625)
	spawnMobile("dathomir", "nightsister_protector",900,-10.2736,-65.1708,-240.442,7,4115625)
	spawnMobile("dathomir", "nightsister_protector",900,-93.1,-73.3,-174.5,-6,4115626)	
	spawnMobile("dathomir", "nightsister_sentinel",900,-994.4,-73.2,-166.3,88,4115626)	
	spawnMobile("dathomir", "nightsister_sentinel",900,-22.5375,-65.6053,-242.708,2,4115625)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-21.7987,-63.2164,-259.727,7,4115625)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,-14.8913,-63.0358,-261.214,2,4115625)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,64.9,-48.3,-131.0,-105,4115623)
	spawnMobile("dathomir", "nightsister_spell_weaver",900,60.9,-52.4,-142.4,-92,4115623)	
	spawnMobile("dathomir", "nightsister_protector",900,-12.1496,-64.6121,-259.169,7,4115625)
	spawnMobile("dathomir", "nightsister_protector",900,-5.85405,-66.7536,-214.372,2,4115625)	
	spawnMobile("dathomir", "nightsister_sentinel",900,14.0655,-63.2116,-184.377,2,4115624)
	spawnMobile("dathomir", "nightsister_sentinel",900,57.2187,-56.7709,-178.97,2,4115623)
	spawnMobile("dathomir", "nightsister_protector",900,61.2023,-57.0517,-174.241,-134,4115623)
	spawnMobile("dathomir", "nightsister_protector",900,65.0699,-55.58,-159.308,2,4115623)
	spawnMobile("dathomir", "nightsister_sentinel",900,65.4328,-55.1946,-157.441,-167,4115623)
	spawnMobile("dathomir", "nightsister_sentinel",900,37.6787,-52.6718,-143.421,2,4115623)
	spawnMobile("dathomir", "nightsister_protector",900,37.6899,-52.6698,-143.418,7,4115623)
	spawnMobile("dathomir", "nightsister_sentinel",900,17.99,-47.6612,-133.802,2,4115623)	
	spawnMobile("dathomir", "nightsister_protector",900,1.69093,-44.6251,-129.463,2,4115623)		
	spawnMobile("dathomir", "nightsister_spell_weaver",900,0.0473984,-45.1734,-143.086,7,4115623)
	spawnMobile("dathomir", "nightsister_sentinel",900,38.3645,-45.6514,-94.5238,2,4115622)
	spawnMobile("dathomir", "nightsister_sentinel",900,40.565,-46.6515,-76.2628,7,4115622)
	spawnMobile("dathomir", "nightsister_sentinel",900,48.2317,-47.0278,-54.4734,2,4115622)
	spawnMobile("dathomir", "nightsister_sentinel",900,44.0373,-46.6601,-51.444,7,4115622)
	spawnMobile("dathomir", "nightsister_sentinel",900,31.0654,-45.1049,-56.1405,-100,4115622)
	spawnMobile("dathomir", "nightsister_sentinel",900,15.027,-40.2011,-76.6327,7,4115621)
	spawnMobile("dathomir", "nightsister_protector",900,-5.96411,-40.5602,-65.8697,2,4115621)		
	spawnMobile("dathomir", "nightsister_sentinel",900,-10.1746,-39.3909,-54.6325,2,4115621)
	spawnMobile("dathomir", "nightsister_sentinel",900,-9.30522,-31.6686,-33.0453,7,4115620)
	spawnMobile("dathomir", "nightsister_sentinel",900,5.27219,-24.4314,-26.0931,2,4115620)
	spawnMobile("dathomir", "nightsister_sentinel",900,2.20982,-11.8595,-2.93477,7,4115619)
end

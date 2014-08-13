--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
DathomirStaticSpawnsNwScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DathomirStaticSpawnsNwScreenPlay",

	lootContainers = {
		

	},

	lootLevel = 39,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 700000},
				{group = "junk", chance = 7500000},
				{group = "rifles", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000}
			},
			lootChance = 8000000
		}
	},

	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("DathomirStaticSpawnsNwScreenPlay", true)

function DathomirStaticSpawnsNwScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function DathomirStaticSpawnsNwScreenPlay:spawnMobiles()

	--rebel camp (-50,86)

	-- nightsister outcast camp (-2597,4954)
	spawnMobile("dathomir", "nightsister_outcast", 420, -2602.2, 131.2, 4958.5, 105, 0)
	spawnMobile("dathomir", "nightsister_outcast", 420, -2596.6, 131.2, 4951.8, -165, 0)
	spawnMobile("dathomir", "nightsister_outcast", 420, -2569.4, 125.9, 4986.5, -135, 0)

	--imperial camp (-4630,5393)
	spawnMobile("dathomir", "assault_trooper", 300, -4631.2, 121.1, 5392.8, -115, 0)
	spawnMobile("dathomir", "assault_trooper", 300, -4626.9, 122.1, 5386.7, 175, 0)

	--singing mountain clan village (-7081,5888)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 360, -7097.5, 379.7, 5897.5, 75, 0)
	spawnMobile("dathomir", "singing_mountain_clan_dragoon", 360, -7075.1, 383.0, 5906.1, -70, 0)
	spawnMobile("dathomir", "singing_mountain_clan_guardian", 360, -7089.9, 389.3, 5925.9, 170, 0)
	spawnMobile("dathomir", "singing_mountain_clan_huntress", 360, -7064.9, 388.6, 5926.8, -128, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 360, -7088.3, 382.4, 5887.0, 18, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 360, -7081.9, 382.1, 5891.7, 180, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 360, -7062.5, 388.7, 5886.7, -112, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -7080.3, 386.8, 5851.6, 180, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -7090.9, 389.0, 5851.6, 180, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 360, -7081.5, 387.8, 5817.2, 144, 0)
	spawnMobile("dathomir", "singing_mountain_clan_slave", 360, -7094.4, 381.9, 5909.0, 164, 0)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 360, -7079.1, 388.3, 5923.3, -164, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer", 360, -7072.5, 409.6, 5962.6, -170, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 360, -7060.7, 405.1, 5959.0, 170, 0)

	--Large Mast (-6427,7206)
	spawnMobile("dathomir", "gaping_spider_hunter", 300, -6415.2, 503.2, 7216.2, -170, 0)
	spawnMobile("dathomir", "gaping_spider_hunter", 300, -6411.7, 503.6, 7217.3, -170, 0)
	spawnMobile("dathomir", "gaping_spider_hunter", 300, -6421.3, 506.5, 7217.7, -170, 0)

	--singing mountain clan tree (-2650,7366)
	spawnMobile("dathomir", "singing_mountain_clan_councilwoman", 4200, -2657.9, 545.7, 7368.5, 110, 0)

	--singing mountain clan totem (-1206,5312)
	spawnMobile("dathomir", "singing_mountain_clan_huntress", 360, -1203.7, 127.5, 5303.4, -21, 0)
	spawnMobile("dathomir", "singing_mountain_clan_dragoon", 360, -1204.4, 128.3, 5319.4, 171, 0)

	--singing mountain clan bridge (-830,4175) - (-430,4175)
	spawnMobile("dathomir", "singing_mountain_clan_scout", 360, -264.0, 129.8, 4117.6, 120, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -411.9, 126.4, 4168.1, 90, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -456.2, 121.1, 4181.9, -90, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -456.2, 121.0, 4170.4, -90, 0)
	spawnMobile("dathomir", "singing_mountain_clan_huntress", 360, -441.7, 121.0, 4165.7, 40, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 720, -444.8, 121.0, 4185.2, 115, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -503.9, 121.2, 4175.9, 90, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -631.7, 121.2, 4175.9, 180, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -756.4, 121.2, 4175.9, -90, 0)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 720, -822.4, 121.0, 4167.1, -65, 0)
	spawnMobile("dathomir", "singing_mountain_clan_guardian", 1220, -826.1, 121.0, 4186.0, -145, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -854.8, 121.9, 4159.3, -90, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -854.8, 121.0, 4178.2, -90, 0)

	--spell weavers trees (-850,2195)
	spawnMobile("dathomir", "nightsister_spell_weaver", 720, -860.8, 146.4, 2792.5, -170, 0)
	spawnMobile("dathomir", "nightsister_spell_weaver", 720, -840.5, 146.6, 2788.0, 17, 0)

	--decorative rock (-999,856)

	--crashed escape pod (-4442,575)

	--burial site (-5259,1295)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -5231.4, 128.1, 1311.2, 40, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, -5289.7, 125.8, 1297.1, -140, 0)

	--burial site (-7122,1175)
	spawnMobile("dathomir", "nightsister_elder", 4200, -7120.29, 460.67, 1179.38, 35, 0)

	--spiderclan floating rocks (-7121,2933)
	spawnMobile("dathomir", "spiderclan_protector", 1220, -7121.9, 368.1, 2919.5, 0, 0)
	spawnMobile("dathomir", "spiderclan_auspex", 600, -7111.2, 369.2, 2929.6, -75, 0)
	spawnMobile("dathomir", "spiderclan_sentinel", 420, -7115.3, 368.2, 2939.7, -135, 0)
	spawnMobile("dathomir", "spiderclan_sentinel", 420, -7126.9, 366.6, 2940.5, 135, 0)
	spawnMobile("dathomir", "spiderclan_stalker", 420, -7131.1, 367.3, 2929.5, 75, 0)

	--stone tower



end

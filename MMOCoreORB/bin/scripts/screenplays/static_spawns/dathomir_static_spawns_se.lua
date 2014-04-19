--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
DathomirStaticSpawnsSeScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DathomirStaticSpawnsSeScreenPlay",

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

registerScreenPlay("DathomirStaticSpawnsSeScreenPlay", true)

function DathomirStaticSpawnsSeScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function DathomirStaticSpawnsSeScreenPlay:spawnMobiles()


	-- fenced building (50,-168)
	spawnMobile("dathomir", "thug", 300, 76.6, 127.1, -164.5, -90, 0)
	spawnMobile("dathomir", "thug", 300, 74.3, 126.3, -175.8, -10, 0)
	spawnMobile("dathomir", "thug", 300, 83.3, 127.1, -173.8, 90, 0)
	spawnMobile("dathomir", "thug", 300, 90.9, 128.7, -167.8, 15, 0)
	spawnMobile("dathomir", "thug", 300, 80.1, 128.0, -152.9, -90, 0)
	spawnMobile("dathomir", "thug", 300, 72.7, 126.9, -156.3, -110, 0)
	spawnMobile("dathomir", "thug", 300, 79.0, 127.9, -150.3, 90, 0)
	spawnMobile("dathomir", "thug", 300, 80.2, 127.0, -171.3, 180, 0)

	spawnMobile("dathomir", "injured_verne", 300, 28.5, 127.3, -184.8, -150, 0)
	spawnMobile("dathomir", "injured_verne", 300, 33.2, 127.9, -190.7, 140, 0)
	spawnMobile("dathomir", "injured_verne", 300, 27.4, 128.2, -191.2, -90, 0)
	spawnMobile("dathomir", "injured_verne", 300, 21.6, 129.0, -196.9, 40, 0)

	--singing mountain clan arch (1125,-1022)
	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer", 360, 1128.4, 140.3, -1045.7, 0, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 360, 1136.8, 138.3, -1040.9, 0, 0)
	spawnMobile("dathomir", "singing_mountain_clan_dragoon", 360, 1136.2, 134.0, -1016.5, -30, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 360, 1116.0, 132.0, -1010.2, 160, 0)

	--ancient stone hut (3490,-395)
	spawnMobile("dathomir", "nightsister_protector", 1220, 3489.1, 128.5, -394.4, 115, 0)
	spawnMobile("dathomir", "nightsister_sentinel", 360, 3502.4, 129.1, -391.7, -15, 0)
	spawnMobile("dathomir", "nightsister_sentinel", 360, 3474.0, 125.3, -405.2, 180, 0)

	--sentry tower (1555,-6473)
	spawnMobile("dathomir", "nightsister_sentry", 360, 1551.1, 303.8, -6477.0, -33, 0)

	--singing mountain clan floating rocks (5202,6905)
	spawnMobile("dathomir", "singing_mountain_clan_dragoon", 360, 5204.7, 447.1, -6881.7, 180, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer", 360, 5221.7, 446.1, -6918.0, -66, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor_tamer", 360, 5185.1, 443.0, -6907.4, 90, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 360, 5179.3, 438.7, -6922.3, 44, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 360, 5196.2, 437.4, -6929.5, 14, 0)
	spawnMobile("dathomir", "singing_mountain_clan_rancor", 360, 5214.4, 437.9, -6931.9, -24, 0)
	
	--spiderclan stone arch (7070,-6440)

	--broken ship engine (6885,-4925)

	--large rock formation (5355,-4705)

	--floating rocks (3000,-5145)

	--ceremonial site (1072,-4485)
	spawnMobile("dathomir", "nightsister_sentinel", 360, 1083.9, 101.7, -4495.8, -95, 0)
	spawnMobile("dathomir", "nightsister_sentinel", 360, 1078.2, 103.2, -4476.4, -130, 0)
	spawnMobile("dathomir", "nightsister_sentry", 360, 1052.8, 96.1, -4496.3, -90, 0)
	spawnMobile("dathomir", "nightsister_sentry", 360, 1050.5, 97.9, -4483.8, -90, 0)
	spawnMobile("dathomir", "nightsister_slave", 360, 1064.5, 100.9, -4483.3, 95, 0)
	spawnMobile("dathomir", "nightsister_slave", 360, 1068.0, 99.1, -4497.1, 35, 0)
	spawnMobile("dathomir", "nightsister_slave", 360, 1075.5, 100.8, -4493.8, -5, 0)
	spawnMobile("dathomir", "nightsister_elder", 3600, 1085.0, 103.0, -4485.2, -95, 0)

	--giant bolma skeleton (1377,-3192)
	spawnMobile("dathomir", "bull_rancor", 480, 1379.9, 98.3, -3193.3, -75, 0)

	--singing mountain clan rock (5205,-3084)
	spawnMobile("dathomir", "singing_mountain_clan_arch_witch", 600, 5205.5, 41.2, -3084.2, -30, 0)

	--wall (7442,-3024)
	spawnMobile("dathomir", "singing_mountain_clan_dragoon", 360, 7442.4, 551.0, -3023.4, 35, 0)
	spawnMobile("dathomir", "singing_mountain_clan_sentry", 360, 7440.5, 549.1, -3044.4, -138, 0)
	spawnMobile("dathomir", "singing_mountain_clan_initiate", 360, 7435.0, 552.0, -3009.8, -109, 0)

	--singing mountain clan outcasts hut (7480,-912)
	spawnMobile("dathomir", "singing_mountain_clan_outcast", 360, 7480.1, 362.9, -912.8, -160, 0)

	--sining mountain clan hut (5556,-688)
	spawnMobile("dathomir", "singing_mountain_clan_guardian", 360, 5556.5, 128.8, -688.6, -85, 0)


end

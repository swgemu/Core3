--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
DathomirStaticSpawnsNeScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DathomirStaticSpawnsNeScreenPlay",

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

registerScreenPlay("DathomirStaticSpawnsNeScreenPlay", true)

function DathomirStaticSpawnsNeScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function DathomirStaticSpawnsNeScreenPlay:spawnMobiles()


	-- rancors + hut (7185,3228)
	spawnMobile("dathomir", "rancor", 540, 7199.1, 490.0, 3222.9, -55, 0)
	spawnMobile("dathomir", "rancor", 540, 7192.7, 492.0, 3237.2, 155, 0)
	spawnMobile("dathomir", "mutant_rancor", 540, 7183.8, 499.6, 3203.7, 5, 0)
	spawnMobile("dathomir", "bull_rancor", 540, 7169.5, 499.8, 3225.6, 75, 0)

	-- free slaves + huts (7205,5560)
	spawnMobile("dathomir", "escaped_nightsister_slave", 300, 7204.2, 533.0, 5552.5, 65, 0)
	spawnMobile("dathomir", "escaped_nightsister_slave", 300, 7207.9, 533.1, 5552.3, -65, 0)
	spawnMobile("dathomir", "escaped_nightsister_slave", 300, 7205.5, 532.8, 5545.0, -155, 0)
	spawnMobile("dathomir", "escaped_singing_mountain_clan_slave", 300, 7200.2, 536.0, 5565.8, 25, 0)
	spawnMobile("dathomir", "escaped_singing_mountain_clan_slave", 300, 7202.0, 536.5, 5568.9, -145, 0)
	spawnMobile("dathomir", "escaped_singing_mountain_clan_slave", 300, 7196.1, 536.3, 5569.7, 115, 0)

	-- nightsister outcast's hut (4886,3278)
	spawnMobile("dathomir", "nightsister_outcast", 420, 4886.3, 113.7, 3278.1, -85, 0)
	spawnMobile("dathomir", "nightsister_outcast", 420, 4879.8, 113.5, 3267.2, -155, 0)
	spawnMobile("dathomir", "nightsister_outcast", 420, 4875.0, 112.4, 3288.1, 55, 0)

	-- nightsister beach tower (915,6858)
	spawnMobile("dathomir", "nightsister_stalker", 360, 915.1, 15.7, 6869.1, -35, 0)
	spawnMobile("dathomir", "nightsister_stalker", 360, 946.6, 12.0, 6861.3, 75, 0)
	spawnMobile("dathomir", "nightsister_stalker", 360, 916.3, 19.2, 6835.4, -145, 0)
	spawnMobile("dathomir", "nightsister_protector", 720, 928.7, 15.4, 6849.9, -19, 0)
	spawnMobile("dathomir", "nightsister_spell_weaver", 420, 901.1, 18.7, 6859.5, -45, 0)

	-- nightsister outcast's hut (866,1096)
	spawnMobile("dathomir", "nightsister_outcast", 420, 865.9, 132.0, 1094.5, 180, 0)

	-- creature skeleton (5297,1430)
	spawnMobile("dathomir", "rancor", 360, 5313.9, 27.2, 1408.0, -15, 0)
	spawnMobile("dathomir", "rancor", 360, 5274.9, 24.0, 1422.2, 70, 0)
	spawnMobile("dathomir", "rancor", 360, 5295.0, 25.1, 1416.9, 15, 0)


end

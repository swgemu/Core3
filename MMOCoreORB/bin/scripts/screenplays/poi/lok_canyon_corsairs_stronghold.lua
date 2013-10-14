CanyonCorsairsStrongholdScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CanyonCorsairsStrongholdScreenPlay",

	lootContainers = {
		568630,
		568615,		
		568637,
		568665
	},
	
	lootLevel = 32,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 2500000},
				{group = "junk", chance = 2500000},
				{group = "melee_two_handed", chance = 800000},
				{group = "heavy_weapons_consumable", chance = 800000},
				{group = "rifles", chance = 800000},
				{group = "carbines", chance = 800000},
				{group = "pistols", chance = 800000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1200 -- 20 minutes
}

registerScreenPlay("CanyonCorsairsStrongholdScreenPlay", true)

function CanyonCorsairsStrongholdScreenPlay:start()
	if (isZoneEnabled("lok")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function CanyonCorsairsStrongholdScreenPlay:spawnMobiles()

	spawnMobile("lok", "canyon_corsair_weak_pirate", 300, -3714.5, 11.9, -3890.7, 90, 0)
	spawnMobile("lok", "canyon_corsair_scout", 300, -3720.5, 11.9, -3902.7, 90, 0)
	spawnMobile("lok", "canyon_corsair_weak_pirate", 300, -3723.5, 11.9, -3907.9, 90, 0)
	spawnMobile("lok", "canyon_corsair_guard", 300, -3728.0, 12.0, -3900.1, 90, 0)

	spawnMobile("lok", "canyon_corsair_weak_pirate", 300, -3804.9, 11.9, -3979.7, 155, 0)
	spawnMobile("lok", "canyon_corsair_scout", 300, -3812.8, 11.9, -3975.5, 170, 0)
	spawnMobile("lok", "canyon_corsair_weak_pirate", 300, -3812.9, 11.9, -3965.9, 170, 0)
	spawnMobile("lok", "canyon_corsair_guard", 300, -3818.7, 12.0, -3969.7, 155, 0)

	spawnMobile("lok", "canyon_corsair_scout", 300, -3851.0, 11.9, -3974.0, 175, 0)
	spawnMobile("lok", "canyon_corsair_scout", 300, -3916.0, 11.7, -3913.3, 75, 0)
	spawnMobile("lok", "canyon_corsair_scout", 300, -3872.0, 11.9, -3879.3, -95, 0)
	spawnMobile("lok", "canyon_corsair_scout", 300, -3813.5, 11.9, -3828.3, -120, 0)

	spawnMobile("lok", "canyon_corsair_elite_pirate", 480, -3787.9, 11.9, -3873.4, -175, 0)
	spawnMobile("lok", "canyon_corsair_guard", 480, -3791.2, 11.9, -3874.7, -175, 0)
	spawnMobile("lok", "canyon_corsair_captain", 480, -3789.5, 11.9, -3868.4, -175, 0)
	spawnMobile("lok", "canyon_corsair_elite_pirate", 480, -3793.6, 11.9, -3871.2, -175, 0)
	spawnMobile("lok", "canyon_corsair_guard", 480, -3787.8, 11.9, -3864.5, -175, 0)

	spawnMobile("lok", "canyon_corsair_cutthroat", 300, -3875.8, 11.9, -3972.2, 180, 0)
	spawnMobile("lok", "canyon_corsair_scout", 300, -3879.0, 12.0, -3967.8, -170, 0)
	spawnMobile("lok", "canyon_corsair_weak_pirate", 300, -3883.8, 11.9, -3972.1, -170, 0)
	spawnMobile("lok", "canyon_corsair_guard", 300, -3884.7, 12.0, -3964.4, 155, 0)

	spawnMobile("lok", "canyon_corsair_cutthroat", 300, -3843.3, 12.9, -3740.3, 145, 0)
	spawnMobile("lok", "canyon_corsair_strong_pirate", 300, -3832.2, 13.0, -3747.8, 150, 0)
	spawnMobile("lok", "canyon_corsair_strong_pirate", 300, -3838.7, 12.9, -3754.7, 145, 0)
	spawnMobile("lok", "canyon_corsair_guard", 300, -3834.8, 13.0, -3772.3, 145, 0)

	spawnMobile("lok", "canyon_corsair_elite_pirate", 300, -3922.8, 11.9, -3802.2, 104, 0)
	spawnMobile("lok", "canyon_corsair_elite_pirate", 300, -3904.0, 12.0, -3793.5, 170, 0)
	spawnMobile("lok", "canyon_corsair_weak_pirate", 300, -3899.4, 11.9, -3801.7, 145, 0)
	spawnMobile("lok", "canyon_corsair_guard", 300, -3902.7, 12.0, -3802.4, 145, 0)
	spawnMobile("lok", "canyon_corsair_destroyer", 300, -3915.3, 11.9, -3810.8, -94, 0)
	spawnMobile("lok", "canyon_corsair_elite_pirate", 300, -3895.1, 12.0, -3832.1, 135, 0)
	spawnMobile("lok", "canyon_corsair_captain", 420, -3882.0, 12.3, -3827.0, 125, 0)
	spawnMobile("lok", "canyon_corsair_guard", 300, -3875.5, 12.0, -3817.4, 105, 0)

end

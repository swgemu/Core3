LostVillageofDurbinScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "LostVillageofDurbinScreenPlay",

	lootContainers = {
		178447,
		178448,
		178449
	},

	lootLevel = 26,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 3100000},
				{group = "junk", chance = 3500000},
				{group = "heavy_weapons_consumable", chance = 600000},
				{group = "rifles", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}
	},

	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("LostVillageofDurbinScreenPlay", true)

function LostVillageofDurbinScreenPlay:start()
	if (isZoneEnabled("talus")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function LostVillageofDurbinScreenPlay:spawnMobiles()
	spawnMobile("talus", "famished_sludge_panther", 300, 4355.3, 6.0, 990.9, -54, 0)
	spawnMobile("talus", "greater_sludge_panther", 300, 4328.3, 6.0, 1009.1, -76, 0)
	spawnMobile("talus", "sludge_panther", 300, 4307.9, 6.0, 1037.9, -48, 0)
	spawnMobile("talus", "greater_sludge_panther", 300, 4291.8, 6.0, 1079.7, 11, 0)
	spawnMobile("talus", "famished_sludge_panther", 300, 4256.1, 6.0, 1062.0, 175, 0)
	spawnMobile("talus", "greater_sludge_panther", 300, 4275.5, 6.0, 1023.7, 2, 0)
	spawnMobile("talus", "sludge_panther", 300, 4250.4, 6.0, 992.7, -107, 0)
	spawnMobile("talus", "minor_sludge_panther", 300, 4237.3, 9.3, 955.5, -133, 0)
	spawnMobile("talus", "famished_sludge_panther", 300, 4214.5, 6.0, 977.5, -26, 0)
	spawnMobile("talus", "greater_sludge_panther", 300, 4215.6, 6.0, 1027.3, -3, 0)
	spawnMobile("talus", "minor_sludge_panther", 300, 4198.4, 6.0, 1074.9, -27, 0)
	spawnMobile("talus", "greater_sludge_panther", 300, 4154.6, 6.0, 1164.3, -8, 0)
	spawnMobile("talus", "famished_sludge_panther", 300, 4154.3, 6.0, 1015.2, 155, 0)
	spawnMobile("talus", "greater_sludge_panther", 300, 4131.1, 6.0, 982.2, -144, 0)
	spawnMobile("talus", "greater_sludge_panther", 300, 4102.0, 6.0, 956.1, -88, 0)
	spawnMobile("talus", "minor_sludge_panther", 300, 4132.6, 6.0, 953.7, 76, 0)
	spawnMobile("talus", "famished_sludge_panther", 300, 4140, 6.0, 943.0, 104, 0)
	spawnMobile("talus", "greater_sludge_panther", 300, 4186.6, 6.0, 948.3, 123, 0)
	spawnMobile("talus", "minor_sludge_panther", 300, 4195.2, 18.2, 876.9, -176, 0)
	spawnMobile("talus", "greater_sludge_panther", 300, 4229.6, 45.7, 881.6, -60, 0)
end

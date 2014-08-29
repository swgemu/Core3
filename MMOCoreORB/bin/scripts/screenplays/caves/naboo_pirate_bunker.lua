NabooPirateBunkerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	--location -1482 -1729
	screenplayName = "NabooPirateBunkerScreenPlay",

 	lootContainers = {
		5535582,
		5535589,
		5535590,
		5535591,
		5535606,
		5535607,
		5535608,
		5535609,
		5535610,
		5535611
	},

	lootLevel = 16,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 160000},
				{group = "junk", chance = 7240000},
				{group = "heavy_weapons_consumable", chance = 500000},
				{group = "rifles", chance = 500000},
				{group = "carbines", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000}
			},
			lootChance = 8000000
		}
	},

	lootContainerRespawn = 1800
}

registerScreenPlay("NabooPirateBunkerScreenPlay", true)

function NabooPirateBunkerScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function NabooPirateBunkerScreenPlay:spawnMobiles()
	--add mobiles here

	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(25) + -1540.0, 278, getRandomNumber(30) + -1759.7, getRandomNumber(360) + 0, 0)
	spawnMobile("naboo", "naboo_gunrunner", 300, getRandomNumber(25) + -1540.0, 278, getRandomNumber(30) + -1759.7, getRandomNumber(360) + 0, 0)
	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(25) + -1540.0, 278, getRandomNumber(30) + -1759.7, getRandomNumber(360) + 0, 0)
	spawnMobile("naboo", "naboo_gunrunner", 300, getRandomNumber(25) + -1540.0, 278, getRandomNumber(30) + -1759.7, getRandomNumber(360) + 0, 0)
	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(25) + -1540.0, 278, getRandomNumber(30) + -1759.7, getRandomNumber(360) + 0, 0)
	spawnMobile("naboo", "naboo_gunrunner", 300, getRandomNumber(25) + -1540.0, 278, getRandomNumber(30) + -1759.7, getRandomNumber(360) + 0, 0)
	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(25) + -1540.0, 278, getRandomNumber(30) + -1759.7, getRandomNumber(360) + 0, 0)
	spawnMobile("naboo", "naboo_gunrunner", 300, getRandomNumber(25) + -1540.0, 278, getRandomNumber(30) + -1759.7, getRandomNumber(360) + 0, 0)

	spawnMobile("naboo", "naboo_pirate_cutthroat", 300, -1540.0, 278, -1759.7, 90, 0)
	spawnMobile("naboo", "naboo_pirate_cutthroat", 300, -1512.0, 278, -1726.8, -90, 0)
	spawnMobile("naboo", "naboo_pirate_crewman", 300, -1501.0, 278, -1713.2, 180, 0)
	spawnMobile("naboo", "naboo_pirate_crewman", 300, -1484.1, 278, -1712.3, 140, 0)
	spawnMobile("naboo", "naboo_pirate_crewman", 300, -1485.0, 278, -1740.4, 0, 0)
	spawnMobile("naboo", "naboo_pirate_crewman", 300, -1501.8, 278, -1743.8, 10, 0)

	spawnMobile("naboo", "naboo_pirate_cutthroat", 300, 0.0, 0.3, 3.5, 0, 5535565)
	spawnMobile("naboo", "naboo_pirate_cutthroat", 300, -3.7, 0.3, -0.8, 0, 5535565)
	spawnMobile("naboo", "naboo_pirate_cutthroat", 300, 3.5, 0.0, 1.0, 180, 5535573)

	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(8) + -1.3, -12.0, getRandomNumber(8) + 26.1, getRandomNumber(360) + 0, 5535567)
	spawnMobile("naboo", "naboo_pirate_crewman", 300, getRandomNumber(8) + -1.3, -12.0, getRandomNumber(8) + 26.1, getRandomNumber(360) + 0, 5535567)
	spawnMobile("naboo", "naboo_pirate_crewman", 300, getRandomNumber(8) + -1.3, -12.0, getRandomNumber(8) + 26.1, getRandomNumber(360) + 0, 5535567)
	spawnMobile("naboo", "naboo_pirate_cutthroat", 300, getRandomNumber(8) + -1.3, -12.0, getRandomNumber(8) + 26.1, getRandomNumber(360) + 0, 5535567)

	spawnMobile("naboo", "naboo_pirate_lieutenant", 300, 32.1, -12.0, 30.3, -90, 5535568)

	spawnMobile("naboo", "naboo_pirate_lieutenant", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate_armsman", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate_armsman", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate_armsman", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate_crewman", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate_crewman", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate_crewman", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate_cutthroat", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate_cutthroat", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate_cutthroat", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_gunrunner", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_gunrunner", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)
	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(44) + 39.5, -16.0, getRandomNumber(24) + 58.4, getRandomNumber(360) + 0, 5535571)

	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(37) + -15.5, -16.0, getRandomNumber(10) + 72.5, getRandomNumber(360) + 0, 5535570)
	spawnMobile("naboo", "naboo_gunrunner", 300, getRandomNumber(37) + -15.5, -16.0, getRandomNumber(10) + 72.5, getRandomNumber(360) + 0, 5535570)
	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(37) + -15.5, -16.0, getRandomNumber(10) + 72.5, getRandomNumber(360) + 0, 5535570)
	spawnMobile("naboo", "naboo_gunrunner", 300, getRandomNumber(37) + -15.5, -16.0, getRandomNumber(10) + 72.5, getRandomNumber(360) + 0, 5535570)
	spawnMobile("naboo", "naboo_pirate", 300, getRandomNumber(37) + -15.5, -16.0, getRandomNumber(10) + 72.5, getRandomNumber(360) + 0, 5535570)

	spawnMobile("naboo", "naboo_dread_pirate", 300, -37.2, -14, 78.8, 88, 5535572)
end

--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
NabooStaticSpawnsNorthScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NabooStaticSpawnsNorthScreenPlay",

	lootContainers = {
		
	},

	lootLevel = 19,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 700000},
				{group = "junk", chance = 6900000},
				{group = "rifles", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000}
			},
			lootChance = 8000000
		}
	},

	lootContainerRespawn = 1800 -- 30 minutes

}
registerScreenPlay("NabooStaticSpawnsNorthScreenPlay", true)

function NabooStaticSpawnsNorthScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:initializeLootContainers()
		self:spawnMobiles()
	end
end

function NabooStaticSpawnsNorthScreenPlay:spawnMobiles()

	--Beach Location (400, 6900)
	spawnMobile("naboo", "veermok_pygmy", 900, getRandomNumber(5) + 421, -209.8, getRandomNumber(5) + 6969, getRandomNumber(360), 0)
	spawnMobile("naboo", "veermok_pygmy", 900, getRandomNumber(5) + 421, -209.8, getRandomNumber(5) + 6969, getRandomNumber(360), 0)

	--Beach Gungan Ruins by Hill (7600, 7000) - researched wp is wrong
	spawnMobile("naboo", "veermok_pygmy", 900, getRandomNumber(5) + 7584, -210.1, getRandomNumber(5) + 6952, getRandomNumber(360), 0)
	spawnMobile("naboo", "veermok_pygmy", 900, getRandomNumber(5) + 7584, -210.1, getRandomNumber(5) + 6952, getRandomNumber(360), 0)

	--Statue Head near Hills (3400, 5000) - researched wp is wrong
	spawnMobile("naboo", "giant_fanned_rawl", 900, getRandomNumber(5) + 3431, -198.1, getRandomNumber(5) + 5086, getRandomNumber(360), 0)
	spawnMobile("naboo", "giant_fanned_rawl", 900, getRandomNumber(5) + 3431, -198.1, getRandomNumber(5) + 5086, getRandomNumber(360), 0)

end

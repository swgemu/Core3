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
	end
end

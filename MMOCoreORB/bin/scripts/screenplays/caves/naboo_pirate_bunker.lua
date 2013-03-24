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
				{group = "junk", chance = 8240000},
				{group = "rifles", chance = 500000},
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

end

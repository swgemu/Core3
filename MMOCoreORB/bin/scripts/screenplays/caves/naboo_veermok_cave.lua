VeermokCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	--location 5703 -1557
	screenplayName = "VeermokCaveScreenPlay",

 	lootContainers = {
		261338,
		7955559,
		7955560,
		7955561,
		7955562,
		7955563
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

registerScreenPlay("VeermokCaveScreenPlay", true)

function VeermokCaveScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function VeermokCaveScreenPlay:spawnMobiles()
	--add mobiles here

end

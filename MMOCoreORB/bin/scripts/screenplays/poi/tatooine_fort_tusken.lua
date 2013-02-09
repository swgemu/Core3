FortTuskenScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "FortTuskenScreenPlay",

	lootContainers = {
		7875788,
		7875790,		
		7875789
	},
	
	lootLevel = 26,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 3500000},
				{group = "junk", chance = 3500000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("FortTuskenScreenPlay", true)

function FortTuskenScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function FortTuskenScreenPlay:spawnMobiles()
   --On top of Tusken Pool
	spawnMobile("tatooine", "tusken_commoner",300,-3996.8,60,6285.7,74,0)
	spawnMobile("tatooine", "tusken_commoner",300,-3969.1,60,6282.8,-73,0)
	spawnMobile("tatooine", "tusken_commoner",300,-3978.6,60,6266.4,-10,0)
	spawnMobile("tatooine", "tusken_commoner",300,-3979.6,60,6261.4,-2,0)
	spawnMobile("tatooine", "tusken_commoner",300,-3.8,37.9,-34.1,43,1189186)
	spawnMobile("tatooine", "tusken_commoner",300,-2.8,37.9,-20.7,71,1189187)
	spawnMobile("tatooine", "tusken_commoner",300,31,37.9,-30.6,-124,1189189)
	spawnMobile("tatooine", "tusken_commoner",300,27,44,-22.4,47,1189192)
	spawnMobile("tatooine", "tusken_commoner",300,29.6,44,-16.3,175,1189192)
	
	spawnMobile("tatooine", "tusken_raider",300,-3997.1,60,6288.4,112,0)
	spawnMobile("tatooine", "tusken_raider",300,-3969,60,6288.3,-101,0)
	spawnMobile("tatooine", "tusken_raider",300,-3983.4,60,6266.1,6,0)
	spawnMobile("tatooine", "tusken_raider",300,-1.9,37.9,-29.2,100,1189186)
	spawnMobile("tatooine", "tusken_raider",300,2.9,37.9,-15.5,-126,1189187)
	spawnMobile("tatooine", "tusken_raider",300,24.2,37.9,-31.6,71,1189189)
	spawnMobile("tatooine", "tusken_raider",300,27.6,37.9,-26,177,1189189)
	
	spawnMobile("tatooine", "tusken_warlord",300,-4.6,37.9,-30.1,118,1189186)
	spawnMobile("tatooine", "tusken_warlord",300,-3.2,37.9,-16.2,109,1189187)
	spawnMobile("tatooine", "tusken_warlord",300,28.9,44,-29.2,0,1189193)
end

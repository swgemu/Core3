TuskenBunkerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "TuskenBunkerScreenPlay",

 	lootContainers = {
			5995601,
        	5995605,
        	5995608,
			5995609
	},

	lootLevel = 26,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 160000},
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

registerScreenPlay("TuskenBunkerScreenPlay", true)

function TuskenBunkerScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function TuskenBunkerScreenPlay:spawnMobiles()
	spawnMobile("tatooine", "tusken_elite_guard",300,-2.92495,-20.75,29.469,166.951,4235606)
	spawnMobile("tatooine", "tusken_elite_guard",300,-0.204799,-20.75,17.7372,0,4235606)
	spawnMobile("tatooine", "tusken_elite_guard",300,-1.60381,-20.75,17.5898,72.7847,4235606)
	spawnMobile("tatooine", "tusken_elite_guard",300,-0.719627,-20.75,17.8638,0,4235606)
	spawnMobile("tatooine", "tusken_elite_guard",300,6.07437,-20.75,29.8174,295.947,4235606)

	spawnMobile("tatooine", "tusken_guard",300,-5.50469,-6.75,3.83646,78.615,4235600)
	spawnMobile("tatooine", "tusken_guard",300,-4.72547,-6.75,2.91168,331.956,4235600)
	spawnMobile("tatooine", "tusken_guard",300,4.11507,-20.7332,17.43,344.353,4235606)
	spawnMobile("tatooine", "tusken_guard",300,1.92794,-20.7332,4.5864,0,4235605)
	spawnMobile("tatooine", "tusken_guard",300,1.22038,-20.7332,4.1939,290.603,4235605)
	spawnMobile("tatooine", "tusken_guard",300,-0.26899,-20.7332,4.75359,0,4235605)

	spawnMobile("tatooine", "tusken_king",300,1.5864,-20.75,32.0004,0,4235606)

	spawnMobile("tatooine", "tusken_savage",300,3.74075,0.25,-4.07544,318.495,4235599)
	spawnMobile("tatooine", "tusken_savage",300,-8,0.25,7,7.99216,4235603)
	spawnMobile("tatooine", "tusken_savage",300,-8,0.25,8,304.313,4235603)
	spawnMobile("tatooine", "tusken_savage",300,4.35912,-13.75,7.04643,0,4235603)
	spawnMobile("tatooine", "tusken_savage",300,3.61216,-13.75,6.31851,68.5105,4235603)
	spawnMobile("tatooine", "tusken_savage",300,4.47368,-20.75,17.4,0,4235606)

	spawnMobile("tatooine", "tusken_sniper",300,-1488.54,41,-193.359,1.44349,0)
	spawnMobile("tatooine", "tusken_sniper",300,-1482.7,41.0005,-198.492,135.409,0)
	spawnMobile("tatooine", "tusken_sniper",300,3.2,41,8.263,135.004,4235603)

	spawnMobile("tatooine", "tusken_warrior",300,-5.2,-20.7,17.23,184.378,4235606)
	spawnMobile("tatooine", "tusken_warrior",300,-1482.53,41,-193.195,148.977,0)
	spawnMobile("tatooine", "tusken_warrior",300,-1478.25,41,-199.32,315.009,0)
end

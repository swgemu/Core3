Yavin4MiningOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "Yavin4MiningOutpostScreenPlay",

	planet = "yavin4",

	patrolMobiles = {
		--{patrolPoints, template, x, z, y, direction, cell, mood, combatPatrol},
		{"surgical_1", "surgical_droid_21b", -1.9, 0.7, 2.5, 175, 7925478, "neutral", false},
	},

	patrolPoints = {
		--table_name = {{x, z, y, cell, delayAtNextPoint}}
		surgical_1 = {{-1.9, 0.7, 2.5, 7925478, false}, {-1.8, 0.7, 4.4, 7925478, false}, {3.1, 0.7, 4.5, 7925478, true}, {3.2, 0.7, 3.6, 7925478, false}, {3.1, 0.7, 4.5, 7925478, false}, {-1.8, 0.7, 4.4, 7925478, false}},
	},

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_old"},
	stationaryNpcs = {"bodyguard", "bounty_hunter", "businessman", "chiss_female", "chiss_male", "commoner_technician", "explorer", "fringer", "gambler", "medic", "mercenary", "miner",  "pilot", "scientist", "shadowy_figure", "slicer", "sullustan_male"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		--tavern a
		{1, 3.1, 0.7, 2.4, 0, 7925478, "npc_sitting_chair"}, {1, 2.3, 0.7, 6.5, -5, 7925478, "sad"},
		--tavern b
		{1, 0.4, 0.6, -0.7, -179, 7925451, "npc_sitting_chair"}, {1, 3.5, 0.6, 4.2, -5, 7925449, "npc_standing_drinking"},
		--building empty
		{1, 3.6, 0.1, -0.5, 0, 1713372, "npc_sitting_chair"}
	},
}

registerScreenPlay("Yavin4MiningOutpostScreenPlay", true)

function Yavin4MiningOutpostScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
	end
end

function Yavin4MiningOutpostScreenPlay:spawnMobiles()
	--tavern b
	local pNpc = spawnMobile("yavin4", "bartender",60,3.4,0.6,5.6,173,7925449)

	if pNpc ~= nil then
		self:setMoodString(pNpc, "conversation")
	end

	--outside tavern area
	spawnMobile("yavin4", "rebel_commando", 460, -255.5, 35.0, 4859.2, 81, 0)
	spawnMobile("yavin4", "rebel_commando", 460, -250.5, 35.0, 4854.2, 86, 0)
	spawnMobile("yavin4", "rebel_commando", 460, -260.5, 35.0, 4864.2, 76, 0)
end

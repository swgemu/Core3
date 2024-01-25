--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
Yavin4StaticSpawnsScreenPlay = ScreenPlay:new {
	screenplayName = "Yavin4StaticSpawnsScreenPlay",

	planet = "yavin4",

	mobiles = {
		-- Light Jedi Enclave (-5575, 4910)
		{"light_jedi_sentinel", 10, -5579.0, 87.7, 4908.5, -179, 0},
		{"light_jedi_sentinel", 10, -5572.6, 87.7, 4908.2, -179, 0},

		-- Dark Jedi Enclave (5068, 310)
		{"dark_jedi_sentinel", 10, 5074.2, 78.8, 313.9, 90, 0},
		{"dark_jedi_sentinel", 10, 5074.3, 79.2, 306.4, 90, 0},

		-- Yavin4 Ruins (-6299, -1502)
		{"crazed_geonosian_guard",300,-6299.1,24.7,-1502,0,0},
		{"crazed_geonosian_guard",300,-6299.1,25.6,-1506.4,179,0},
		{"crazed_geonosian_guard",300,-6302.1,24.9,-1504.2,-90,0},
		{"crazed_geonosian_guard",300,-6296.0,25.3,-1504.2,90,0},

		-- Captain Eso & Yith Seenath's base of operations (1591, 1536)
		{"rebel_commando", 360, 1595.0, 102.5, 1531.9, -40, 0},
		{"rebel_commando", 360, 1595.0, 102.5, 1530.4, -30, 0},
		{"rebel_commando", 360, 1597.8, 102.9, 1530.3, -37, 0},
		{"rebel_commando", 360, 1595.3, 102.7, 1527.8, -26, 0},

		-- Imp base camp outside Massassi Temple POI
		{"stormtrooper", 360, -3196.7, 69.6, -3139.5, -100, 0},
		{"stormtrooper", 360, -3195.8, 69.8, -3130.7, -104, 0}
	}
}

registerScreenPlay("Yavin4StaticSpawnsScreenPlay", true)

function Yavin4StaticSpawnsScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
	end
end

function Yavin4StaticSpawnsScreenPlay:spawnMobiles()
	local mobiles = self.mobiles

	for i = 1, #mobiles do
		local mobile = mobiles[i]

		local pMobile = spawnMobile(self.planet, mobile[1], mobile[2], mobile[3], mobile[4], mobile[5], mobile[6], mobile[7])

		if pMobile ~= nil then
			AiAgent(pMobile):addObjectFlag(AI_STATIC)
		end
	end
end

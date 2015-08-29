
--[[
Rebel Quest states:
1 - m1 refused
2 - m1 active
3 - m1 return
4 - m1 complete
5 - m2 refused
6 - m2 active
7 - m2 return
8 - m2 complete
9 - m3/4 active
10 - m3/4 complete
11 - m5 refused
12 - m5 active
13 - m5 return
14 - m5 complete

Imperial Quest states:
1 - m1 active
2 - m1 complete
3 - m2 active
4 - m2 complete
5 - m3/4 active
6 - m3/4 complete
7 - m5 active
8 - m5 return
9 - m5 complete
]]

Coa2Screenplay = ScreenPlay:new {
	numberOfActs = 1,
	screenplayName = "Coa2Screenplay",

	staticNpcs = {
		{"coa2_imperial_coordinator", "naboo", 5144, -192, 6674, 50},
		{"coa2_imperial_coordinator", "naboo", -5431.7, 6, 4168.5, 173},
		{"coa2_imperial_coordinator", "rori", -5255.8, 80, -2254.5, -99},
		{"coa2_imperial_coordinator", "rori", 5347.5, 80, 5617.5, -8},
		{"coa2_imperial_coordinator", "tatooine", -1131.2, 12, -3661.2, -36},
		{"coa2_rebel_coordinator", "corellia", -5218.1, 21, -2602.6, -11},
		{"coa2_rebel_coordinator", "corellia", 95.3, 28, -4519.1, -91},
		{"coa2_rebel_coordinator", "talus", 4065.1, 2, 5289.5, 130},
		{"coa2_rebel_coordinator", "tatooine", 3286.3, 5, -4524.8, -48},
		{"coa2_rebel_coordinator", "tatooine", -2927.5, 5, 2574.3, 131},
		{"imperial_recruiter", "dantooine", 2503.7, 14, -2049, 179},
		{"imperial_recruiter", "dathomir", -6306, 122.9, -532.5, -34},
		{"imperial_recruiter", "endor", -1950.7, 146.6, 1051.8, -54},
		{"imperial_recruiter", "lok", -2572.2, 21.7, -862.5, 101},
		{"imperial_recruiter", "yavin4", 1588.7, 50.5, -3538.5, 38},
		{"rebel_recruiter", "dantooine", 6876.7, 60, -2258.4, -78},
		{"rebel_recruiter", "dathomir", -48.3, 142.1, 88.1, -139},
		{"rebel_recruiter", "endor", 4018.8, 7.4, 2966.2, -53},
		{"rebel_recruiter", "lok", -4749, 4, 3525.5, 113},
		{"rebel_recruiter", "yavin4", -4237, 183, 2284.1, -165},
	},

	commanders = {
		{"coa2_imperial_commander", "dantooine", 2505.7, 14, -2053.4, -139},
		{"coa2_imperial_commander", "dathomir", -6303.1, 123.2, -529.8, -42},
		{"coa2_imperial_commander", "endor", -1954.1, 146.6, 1051.9, -32},
		{"coa2_imperial_commander", "lok", -2568.4, 21.7, -861.4, 159},
		{"coa2_imperial_commander", "yavin4", 1586.4, 50.5, -3533.3, 46},
		{"coa2_rebel_commander", "dantooine", 6874.4, 60, -2253, -126},
		{"coa2_rebel_commander", "dathomir", -48.2, 142.3, 85.9, -60},
		{"coa2_rebel_commander", "endor", 4021.1, 7.4, 2970.2, -82},
		{"coa2_rebel_commander", "lok", -4753, 4, 3516.4, 111},
		{"coa2_rebel_commander", "yavin4", -4237.2, 183.5, 2276, -23},
	}
}

registerScreenPlay("Coa2Screenplay", true)

function Coa2Screenplay:start()
	self:spawnStaticNpcs()
end

function Coa2Screenplay:spawnStaticNpcs()
	for i = 1, # self.staticNpcs do
		local npc = self.staticNpcs[i]
		if isZoneEnabled(npc[2]) then
			spawnMobile(npc[2], npc[1], 0, npc[3], npc[4], npc[5], npc[6], 0)
		end

	end

	for i = 1, # self.commanders do
		local npc = self.commanders[i]
		if isZoneEnabled(npc[2]) then
			spawnMobile(npc[2], npc[1], 0, npc[3], npc[4], npc[5], npc[6], 0)
		end

	end
end

function Coa2Screenplay:hasDecodedDisk(pPlayer)
	return false
end

function Coa2Screenplay:hasEncodedDisk(pPlayer)
	return false
end

function Coa2Screenplay:startMission(pPlayer, faction, number)

end

function Coa2Screenplay:progressMission(pPlayer, faction, number)

end

function Coa2Screenplay:cleanupMission(pPlayer, faction, number)

end

function Coa2Screenplay:finishMission(pPlayer, faction, number)

end

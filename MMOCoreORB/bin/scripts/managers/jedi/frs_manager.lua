frsEnabled = 0

-- Object ID of Enclave buildings
lightEnclaveID = 8525417
darkEnclaveID = 3435626

petitionInterval = 86400000 -- 1 day
votingInterval = 86400000 -- 1 day
acceptanceInterval = 86400000 -- 1 day
maintenanceInterval = 86400000 -- 1 day

requestDemotionDuration = 604800000 -- 7 days
voteChallengeDuration = 604800000 -- 7 days

-- Costs are in FRS experience
baseMaintCost = 100
requestDemotionCost = 2500
voteChallengeCost = 2000

maxPetitioners = 11
missedVotePenalty = 100 -- FRS XP

darkFrsSkills = {}
lightFrsSkills = {}

-- { rank, skillName, requiredExperience, playerCap }
lightRankingData = {
	{ 0, "force_rank_light_novice", 0, -1 },
	{ 1, "force_rank_light_rank_01", 10000, 10 },
	{ 2, "force_rank_light_rank_02", 20000, 10 },
	{ 3, "force_rank_light_rank_03", 30000, 10 },
	{ 4, "force_rank_light_rank_04", 40000, 10 },
	{ 5, "force_rank_light_rank_05", 60000, 9 },
	{ 6, "force_rank_light_rank_06", 80000, 9 },
	{ 7, "force_rank_light_rank_07", 100000, 9 },
	{ 8, "force_rank_light_rank_08", 150000, 8 },
	{ 9, "force_rank_light_rank_09", 200000, 8 },
	{ 10, "force_rank_light_rank_10", 300000, 11 },
	{ 11, "force_rank_light_master", 500000, 1 },
}

darkRankingData = {
	{ 0, "force_rank_dark_novice", 0, -1 },
	{ 1, "force_rank_dark_rank_01", 10000, 10 },
	{ 2, "force_rank_dark_rank_02", 20000, 10 },
	{ 3, "force_rank_dark_rank_03", 30000, 10 },
	{ 4, "force_rank_dark_rank_04", 40000, 10 },
	{ 5, "force_rank_dark_rank_05", 60000, 9 },
	{ 6, "force_rank_dark_rank_06", 80000, 9 },
	{ 7, "force_rank_dark_rank_07", 100000, 9 },
	{ 8, "force_rank_dark_rank_08", 150000, 8 },
	{ 9, "force_rank_dark_rank_09", 200000, 8 },
	{ 10, "force_rank_dark_rank_10", 300000, 11 },
	{ 11, "force_rank_dark_master", 500000, 1 },
}

enclaveRoomRequirements = {
	-- Light enclave
	{ 8525444, -1 }, -- entrancehall1
	{ 8525421, 1 }, -- tier1hall1
	{ 8525420, 1 }, -- tier1room
	{ 8525419, 1 }, -- tier1hall2
	{ 8525424, 5 }, -- tier2hall1
	{ 8525423, 5 }, -- tier2room
	{ 8525422, 5 }, -- tier2hall2
	{ 8525433, 8 }, -- tier3hall1
	{ 8525432, 8 }, -- tier3room
	{ 8525431, 8 }, -- tier3hall2
	{ 8525430, 10 }, -- tier4hall1
	{ 8525429, 10 }, -- tier4room
	{ 8525428, 10 }, -- tier4hall2
	{ 8525427, 11 }, -- tier5hall1
	{ 8525426, 11 }, -- tier5room
	{ 8525425, 11 }, -- tier5hall2
	-- Dark enclave
	{ 3435626, -1 }, -- ramp1
	{ 3435644, 1 }, -- hallwayb1
	{ 3435650, 1 }, -- council1
	{ 3435637, 5 }, -- hallwaya1
	{ 3435652, 5 }, -- council3
	{ 3435638, 8 }, -- hallwaya2
	{ 3435653, 8 }, -- council4
	{ 3435645, 8 }, -- hallwayb2
	{ 3435639, 10 }, -- hallwaya3
	{ 3435646, 10 }, -- hallwayb3
	{ 3435651, 10 }, -- council2
	{ 3435640, 11 }, -- hallwaya4
	{ 3435647, 11 }, -- hallwayb4
	{ 3435641, 11 }, -- chamberramp
	{ 3435642, 11 }, -- chamber
}

	-- Key followed by values for player rank 0 through 11
	-- Key references the player's target
	-- Ex: Rank 5 loses to BH, see "bh_lose" key and 6th integer value in same row
frsExperienceValues = {
	{ "nonjedi_win", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ "nonjedi_lose", 1000, 1250, 1759, 2250, 3000, 3750, 4750, 5500, 6750, 7750, 8750, 10000 },
	{ "bh_win", 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500 },
	{ "bh_lose", 1000, 1250, 1759, 2250, 3000, 3750, 4750, 5500, 6750, 7750, 8750, 10000 },
	{ "padawan_win", 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 },
	{ "padawan_lose", 500, 650, 1000, 1250, 1750, 2250, 2750, 2350, 4000, 4500, 5000, 6000 },
	{ "rank0_win", 750, 750, 750, 750, 750, 750, 750, 750, 750, 750, 750, 750 },
	{ "rank0_lose", 250, 500, 750, 1000, 1500, 2000, 2500, 3000, 3750, 4250, 5000, 5750 },
	{ "rank1_win", 900, 900, 900, 900, 900, 900, 900, 900, 900, 900, 900, 900 },
	{ "rank1_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
	{ "rank2_win", 1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250 },
	{ "rank2_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
	{ "rank3_win", 2250, 2250, 2250, 2250, 2250, 2250, 2250, 2250, 2250, 2250, 2250, 2250 },
	{ "rank3_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
	{ "rank4_win", 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000 },
	{ "rank4_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
	{ "rank5_win", 3750, 3750, 3750, 3750, 3750, 3750, 3750, 3750, 3750, 3750, 3750, 3750 },
	{ "rank5_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
	{ "rank6_win", 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500, 4500 },
	{ "rank6_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
	{ "rank7_win", 5500, 5500, 5500, 5500, 5500, 5500, 5500, 5500, 5500, 5500, 5500, 5500 },
	{ "rank7_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
	{ "rank8_win", 6500, 6500, 6500, 6500, 6500, 6500, 6500, 6500, 6500, 6500, 6500, 6500 },
	{ "rank8_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
	{ "rank9_win", 7500, 7500, 7500, 7500, 7500, 7500, 7500, 7500, 7500, 7500, 7500, 7500 },
	{ "rank9_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
	{ "rank10_win", 8750, 8750, 8750, 8750, 8750, 8750, 8750, 8750, 8750, 8750, 8750, 8750 },
	{ "rank10_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
	{ "rank11_win", 9750, 9750, 9750, 9750, 9750, 9750, 9750, 9750, 9750, 9750, 9750, 9750 },
	{ "rank11_lose", 100, 250, 500, 900, 1300, 1750, 2250, 2750, 3500, 4150, 4750, 5500 },
}

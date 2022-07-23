CriesOfAlderaan = ScreenPlay:new {
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

	episodeOneEnabled = true,
	episodeTwoEnabled = true,
	episodeThreeEnabled = true,
	skipToThree = false
}

registerScreenPlay("CriesOfAlderaan", true)

function CriesOfAlderaan:start()
	self:spawnStaticNpcs()
	self:determineWinningFaction()
end

function CriesOfAlderaan:spawnStaticNpcs()
	for i = 1, # self.staticNpcs do
		local npc = self.staticNpcs[i]
		if isZoneEnabled(npc[2]) then
			spawnMobile(npc[2], npc[1], 0, npc[3], npc[4], npc[5], npc[6], 0)
		end
	end
end

function CriesOfAlderaan:getState(pPlayer, stateName)
	local state = readScreenPlayData(pPlayer, stateName, "state")

	if (state == nil or state == "") then
		return 0
	end

	return tonumber(state)
end

function CriesOfAlderaan:setState(pPlayer, stateName, val)
	writeScreenPlayData(pPlayer, stateName, "state", val)
end

function CriesOfAlderaan:determineWinningFaction()
	local time = os.time(os.date("*t"))
	local checkTime = getQuestStatus("CriesOfAlderaan:winningFactionUpdate:")
	local winningFaction = getQuestStatus("CriesOfAlderaan:winningFaction:")

	if (checkTime == nil) then
		checkTime = 0
	else
		checkTime = tonumber(checkTime)
	end

	local checkDelay = 604800 -- 1 week in seconds

	if ((checkTime + checkDelay) > time) then
		local timeDiff = (checkTime + checkDelay) - time + 10

		Logger:logEvent("CriesofAlderaan:determinewinningFfaction -- rescheduled in " .. timeDiff .. " seconds", LT_INFO)

		createEvent(timeDiff * 1000, "CriesOfAlderaan", "determineWinningFaction", nullptr, "")
		return
	end

	if (winningFaction ~= nil) then
		winningFaction = tonumber(winningFaction)
	end

	-- compare scores
	local rebelScore = getQuestStatus("CriesOfAlderaan:rebelScore:")
	local imperialScore = getQuestStatus("CriesOfAlderaan:imperialScore:")

	if (rebelScore == nil) then
		rebelScore = 0
	else
		rebelScore = tonumber(rebelScore)
	end

	if (imperialScore == nil) then
		imperialScore = 0
	else
		imperialScore = tonumber(imperialScore)
	end

	if (imperialScore > rebelScore) then
		winningFaction = FACTIONIMPERIAL
	elseif (rebelScore > imperialScore) then
		winningFaction = FACTIONREBEL
	else
		local randScore = getRandomNumber(100)

		if (randScore > 50) then
			winningFaction = FACTIONREBEL
		else
			winningFaction = FACTIONIMPERIAL
		end
	end

	Logger:logEvent("CriesofAlderaan:determineWinningFaction -- Set Winning Faction " .. winningFaction, LT_INFO)

	setQuestStatus("CriesOfAlderaan:winningFaction:", winningFaction)
	setCoaWinningFaction(winningFaction)

	setQuestStatus("CriesOfAlderaan:winningFactionUpdate:", time)
	createEvent(checkDelay * 1000, "CriesOfAlderaan", "determineWinningFaction", nullptr, "")
end

function CriesOfAlderaan:getWinningFaction()
	local winningFaction = getQuestStatus("CriesOfAlderaan:winningFaction:")

	if (winningFaction == nil or winningFaction == 0) then
		return 0
	end

	return winningFaction
end

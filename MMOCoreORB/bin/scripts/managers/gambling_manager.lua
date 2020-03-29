SLOTS = 1
ROULETTE = 2
SABAAC = 3

gamblingEnabled = 1
betTimeout = 60 * 1000 -- 60 secs

-- Game type data
-- { game, minPlayers, maxPlayers, minBet, maxBet }
gameData = {
	{ SLOTS, 1, 1, 1, 3 },
	{ ROULETTE, 1, 10, 1, 10000 },
	{ SABAAC, 1, 4, 1, 100000 }
}

-- { reelPattern, basePayout, maxPayout }
slotData = {
	{ "*1|2|3", 2, 6 },
	{ "000", 4, 12 },
	{ "111", 50, 150 },
	{ "222", 75, 225 },
	{ "333", 4, 300 },
	{ "444", 4, 750 },
	{ "555", 500, 1500 },
	{ "666", 1000, 3000 },
	{ "777", 1500, 5000 }
}

-- { reelNumber, weight }
slotWeights = {
 { 1, 20 },
 { 2, 18 },
 { 3, 15 },
 { 4, 10 },
 { 5, 5 },
 { 6, 3 },
 { 7, 1 }
}
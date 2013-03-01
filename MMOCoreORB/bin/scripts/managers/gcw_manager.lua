--frequency of sanity check in seconds
gcwCheckTimer = 7200

--Amount of time in seconds that a base will be vulnerable
vulnerabilityDuration = 10800  

-- Amount of time in seconds between base vulnerabilities.  
vulnerabilityFrequency = 259200

-- amount of time before waiting to reset vulnerability
resetTimer = 604800	

-- amount of time in seconds to wait when a slice fails
sliceCooldown = 120

totalDNASamples = 44

DNAMatchesRequired = 22

-- Amount of time in seconds that a base destructino takes after the countdown is initiated
destructionTimer = 600

-- maximum bases per planet
maxBases = 25

-- time in seconds that a player must be overt before aborting a facility shutdown
overtCooldown = 300

-- time in seconds to wait before reactivating the overload after the shutdown is aborted
reactvationTimer = 300

-- time that a player can maintain control of a turret before another player can take it
--(removed)turretInactivityTimer = 15

-- amount of time in seconds that a turret must wait after the last manual turret activity
-- X seconds after the last manual activity the turret will be able to auto fire
turretAutoFireTimeout = 20

maxBasesPerPlayer = 25

-- xp bonus for faction controlling a planet
bonusXP = 15

-- discount percentage for side losing the gcw.  negative value of increase in price.  positive for a decrease
bonusDiscount = -30

racialPenaltyEnabled = 1

-- assign points to each type of base
-- s01=Forward Outpost, s02 = Field Hospital , s03 = Tactical Center, s04 = Detach HQ
HQValues = {
	{"object/building/faction_perk/hq/hq_s01_imp_pvp.iff", 2}, 
	{"object/building/faction_perk/hq/hq_s01_imp.iff", 1},
	{"object/building/faction_perk/hq/hq_s02_imp_pvp.iff", 6},
	{"object/building/faction_perk/hq/hq_s02_imp.iff" , 3},
	{"object/building/faction_perk/hq/hq_s03_imp_pvp.iff" , 8},
	{"object/building/faction_perk/hq/hq_s03_imp.iff", 4},
	{"object/building/faction_perk/hq/hq_s04_imp_pvp.iff", 20}, 
	{"object/building/faction_perk/hq/hq_s04_imp.iff", 10},
	{"object/building/faction_perk/hq/hq_s01_rebel_pvp.iff", 2},
	{"object/building/faction_perk/hq/hq_s01_rebel.iff", 1},
	{"object/building/faction_perk/hq/hq_s02_rebel_pvp.iff", 6},
	{"object/building/faction_perk/hq/hq_s02_rebel.iff" , 3},
	{"object/building/faction_perk/hq/hq_s03_rebel_pvp.iff" , 8},
	{"object/building/faction_perk/hq/hq_s03_rebel.iff", 4},
	{"object/building/faction_perk/hq/hq_s04_rebel_pvp.iff", 20},
	{"object/building/faction_perk/hq/hq_s04_rebel.iff", 10},

}

-- race (raceid, penalty_multiplier)
-- raceid found in creatureobject
--HUMAN = 0; RODIAN = 1; TRANDOSHAN = 2; MONCAL = 3; WOOKIE = 4; BOTHAN = 5; TWILEK = 6; ZABRAK = 7; ITHORIAN = 0x21; SULLUSTAN = 0x31; 
imperial_racial_penalty = {
		{0, 1},
		{1, 3}, --rodian
		{2, 2}, -- trando
		{3, 3}, -- moncal
		{4, 3},
		{5, 2},
		{6, 1.5},
		{7, 2},
		{33, 2},
		{49, 2},
	
}

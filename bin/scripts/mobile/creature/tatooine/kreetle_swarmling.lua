kreetle_swarmling = Creature:new {
	objectName = "@mob/creature_names:kreetle_swarming",
	socialGroup = "Uber Kreetle",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 125,
	baseHAMmax = 125,
	armor = 0,
	resists = {5,5,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 1,
	hideType = "hide_scaley",
	hideAmount = 2,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/kreetle.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kreetle_swarmling, "kreetle_swarmling")
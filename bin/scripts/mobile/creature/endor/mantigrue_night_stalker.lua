mantigrue_night_stalker = Creature:new {
	objectName = "@mob/creature_names:mantigrue_night_stalker",
	socialGroup = "Mantigrue",
	pvpFaction = "",
	faction = "",
	level = 28,
	chanceHit = 0.360000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {30,40,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mantigrue_night_stalker, "mantigrue_night_stalker")
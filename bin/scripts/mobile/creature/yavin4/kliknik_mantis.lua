kliknik_mantis = Creature:new {
	objectName = "@mob/creature_names:kliknik_mantis",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.350000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 2006,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {20,0,0,-1,0,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_mantis, "kliknik_mantis")
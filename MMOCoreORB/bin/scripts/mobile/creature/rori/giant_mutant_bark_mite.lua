giant_mutant_bark_mite = Creature:new {
	objectName = "@mob/creature_names:mutant_bark_mite_giant",
	socialGroup = "Mutant Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {0,0,0,10,10,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 20,
	hideType = "hide_bristley",
	hideAmount = 18,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareaattack",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_mutant_bark_mite, "giant_mutant_bark_mite")
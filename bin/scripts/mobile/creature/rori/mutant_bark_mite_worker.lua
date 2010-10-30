mutant_bark_mite_worker = Creature:new {
	objectName = "@mob/creature_names:mutant_bark_mite_worker",
	socialGroup = "Mut. Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.280000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 609,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {5,5,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 10,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_bark_mite_worker, "mutant_bark_mite_worker")
mutant_bark_mite_hatchiing = Creature:new {
	objectName = "@mob/creature_names:mutant_bark_mite_hatchiing",
	socialGroup = "Mut. Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 430,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_bristley",
	hideAmount = 8,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 1,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite_hatchling.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_bark_mite_hatchiing, "mutant_bark_mite_hatchiing")
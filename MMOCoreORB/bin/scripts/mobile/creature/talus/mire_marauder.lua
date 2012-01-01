mire_marauder = Creature:new {
	objectName = "@mob/creature_names:mire_marauder",
	socialGroup = "Sludge Panth.",
	pvpFaction = "",
	faction = "",
	level = 56,
	chanceHit = 0.55,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5464,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 1,
	resists = {55,55,10,80,-1,-1,10,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 150,
	hideType = "hide_leathery",
	hideAmount = 140,
	boneType = "bone_mammal",
	boneAmount = 140,
	milk = 0,
	tamingChance = 0,
	ferocity = 12,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/minor_sludge_panther.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mire_marauder, "mire_marauder")
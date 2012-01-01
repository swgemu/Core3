deranged_ravisher = Creature:new {
	objectName = "@mob/creature_names:deranged_ravisher",
	socialGroup = "Endor Squill",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.39,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3460,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {40,40,15,-1,15,15,15,15,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/squill.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(deranged_ravisher, "deranged_ravisher")
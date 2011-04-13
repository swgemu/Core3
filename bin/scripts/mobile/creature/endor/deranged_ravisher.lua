deranged_ravisher = Creature:new {
	objectName = "deranged ravisher",
	socialGroup = "Endor Squill",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.390000,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3460,
	baseHAM = 9000,
	baseHAMmax = 9000,
	armor = 0,
	resists = {40,40,0,-1,0,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/squill.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(deranged_ravisher, "deranged_ravisher")
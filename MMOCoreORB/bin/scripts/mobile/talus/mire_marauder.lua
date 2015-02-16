mire_marauder = Creature:new {
	objectName = "@mob/creature_names:mire_marauder",
	socialGroup = "panther",
	faction = "",
	level = 56,
	chanceHit = 0.55,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5464,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 1,
	resists = {155,155,10,180,-1,-1,10,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 150,
	hideType = "hide_leathery",
	hideAmount = 140,
	boneType = "bone_mammal",
	boneAmount = 140,
	milk = 0,
	tamingChance = 0,
	ferocity = 12,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/minor_sludge_panther.iff"},
	scale = 1.4,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mire_marauder, "mire_marauder")

stintaril_ravager = Creature:new {
	objectName = "@mob/creature_names:stintaril_ravager",
	socialGroup = "stinaril",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 7,
	hideType = "hide_bristley",
	hideAmount = 5,
	boneType = "bone_mammal",
	boneAmount = 4,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/stintaril_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"mediumdisease",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stintaril_ravager, "stintaril_ravager")
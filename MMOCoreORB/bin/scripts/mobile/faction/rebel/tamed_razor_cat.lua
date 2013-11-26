tamed_razor_cat = Creature:new {
	objectName = "@mob/creature_names:rebel_tamed_razor_cat",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 12,
	chanceHit = 0.29,
	damageMin = 140,
	damageMax = 150,
	baseXp = 514,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/tusk_cat.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tamed_razor_cat, "tamed_razor_cat")
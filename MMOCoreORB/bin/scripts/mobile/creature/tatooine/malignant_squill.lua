malignant_squill = Creature:new {
	objectName = "@mob/creature_names:malignant_squill",
	socialGroup = "Squill",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.5,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4916,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 1,
	resists = {5,5,5,5,100,5,5,5,-1},
	meatType = "meat_carnivore",
	meatAmount = 25,
	hideType = "hide_leathery",
	hideAmount = 25,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0.1,
	ferocity = 12,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/squill.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongdisease",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(malignant_squill, "malignant_squill")
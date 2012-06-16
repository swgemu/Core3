veermok_scout = Creature:new {
	objectName = "@mob/creature_names:veermok_scout",
	socialGroup = "veermok",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 719,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {10,5,0,0,0,0,0,0,0},
	meatType = "meat_carnivore",
	meatAmount = 150,
	hideType = "hide_bristley",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 60,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 0,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/alpha_veermok.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(veermok_scout, "veermok_scout")
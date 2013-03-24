vrelt_mother = Creature:new {
	objectName = "@mob/creature_names:startled_vrelt_mother",
	socialGroup = "vrelt",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_carnivore",
	meatAmount = 13,
	hideType = "hide_bristley",
	hideAmount = 13,
	boneType = "bone_mammal",
	boneAmount = 13,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/startled_vrelt_mother.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(vrelt_mother, "vrelt_mother")

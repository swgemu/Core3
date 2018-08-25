infant_brackaset = Creature:new {
	objectName = "@mob/creature_names:infant_brackaset",
	socialGroup = "brackaset",
	faction = "",
	level = 6,
	chanceHit = 0.25,
	damageMin = 55,
	damageMax = 65,
	baseXp = 113,
	baseHAM = 135,
	baseHAMmax = 165,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 75,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_mammal",
	boneAmount = 60,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/infant_brackaset.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 0.6,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(infant_brackaset, "infant_brackaset")

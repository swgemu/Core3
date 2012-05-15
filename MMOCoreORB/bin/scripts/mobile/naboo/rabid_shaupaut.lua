rabid_shaupaut = Creature:new {
	objectName = "@mob/creature_names:rabid_shaupaut",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 4,
	hideType = "hide_bristley",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 3,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/shaupaut.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(rabid_shaupaut, "rabid_shaupaut")
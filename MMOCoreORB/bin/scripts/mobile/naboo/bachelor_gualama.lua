bachelor_gualama = Creature:new {
	objectName = "@mob/creature_names:bachelor_gualama",
	socialGroup = "gualama",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 514,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 200,
	hideType = "hide_wooly",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 90,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/gualama.iff"},
	controlDeviceTemplate = "object/intangible/pet/gualama_hue.iff",
	scale = 0.95,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bachelor_gualama, "bachelor_gualama")

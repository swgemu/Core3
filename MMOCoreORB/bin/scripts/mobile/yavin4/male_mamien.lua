male_mamien = Creature:new {
	objectName = "@mob/creature_names:mamien_male",
	socialGroup = "mamien",
	faction = "",
	level = 19,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1426,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {120,115,5,5,-1,-1,5,-1,-1},
	meatType = "meat_wild",
	meatAmount = 45,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mamien.iff"},
	controlDeviceTemplate = "object/intangible/pet/mamien_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(male_mamien, "male_mamien")

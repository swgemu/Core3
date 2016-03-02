wormed_vrobal = Creature:new {
	objectName = "@mob/creature_names:wormed_vrobal",
	socialGroup = "vrobal",
	faction = "",
	level = 11,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 356,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {0,0,0,110,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 13,
	hideType = "hide_leathery",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 15,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/vrobal.iff"},
	controlDeviceTemplate = "object/intangible/pet/roba_hue.iff",
	scale = 0.95,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(wormed_vrobal, "wormed_vrobal")

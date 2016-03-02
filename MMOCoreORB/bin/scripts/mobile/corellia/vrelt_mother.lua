vrelt_mother = Creature:new {
	objectName = "@mob/creature_names:startled_vrelt_mother",
	socialGroup = "vrelt",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {110,110,0,0,0,0,0,-1,-1},
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
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/startled_vrelt_mother.iff"},
	controlDeviceTemplate = "object/intangible/pet/stintaril_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(vrelt_mother, "vrelt_mother")

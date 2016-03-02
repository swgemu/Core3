pugoriss = Creature:new {
	objectName = "@mob/creature_names:pugoriss",
	socialGroup = "pugoriss",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {110,110,0,0,115,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 375,
	hideType = "hide_leathery",
	hideAmount = 425,
	boneType = "bone_mammal",
	boneAmount = 375,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/pugoriss.iff"},
	controlDeviceTemplate = "object/intangible/pet/pugoriss_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(pugoriss, "pugoriss")

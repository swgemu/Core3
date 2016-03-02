kwi = Creature:new {
	objectName = "@mob/creature_names:kwi",
	socialGroup = "kwi",
	faction = "",
	level = 10,
	chanceHit = 0.27,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {110,110,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_mammal",
	boneAmount = 75,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi.iff"},
	controlDeviceTemplate = "object/intangible/pet/kwi_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(kwi, "kwi")

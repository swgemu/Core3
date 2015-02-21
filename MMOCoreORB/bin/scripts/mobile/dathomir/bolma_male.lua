bolma_male = Creature:new {
	objectName = "@mob/creature_names:bolma_male",
	socialGroup = "bolma",
	faction = "",
	level = 27,
	chanceHit = 0.37,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2730,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {135,120,15,-1,-1,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 320,
	hideType = "hide_leathery",
	hideAmount = 340,
	boneType = "bone_mammal",
	boneAmount = 320,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bolma_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/bolma_hue.iff",
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bolma_male, "bolma_male")

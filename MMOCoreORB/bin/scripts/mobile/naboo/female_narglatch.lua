female_narglatch = Creature:new {
	objectName = "@mob/creature_names:narglatch_female",
	socialGroup = "narglatch",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2443,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {125,10,10,10,-1,-1,10,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/narglatch_female.iff"},
	controlDeviceTemplate = "object/intangible/pet/narglatch_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_narglatch, "female_narglatch")

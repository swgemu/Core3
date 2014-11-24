festering_squill = Creature:new {
	objectName = "@mob/creature_names:festering_squill",
	socialGroup = "squill",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.38,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3097,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {140,140,15,-1,15,15,150,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 3,
	hideType = "hide_leathery",
	hideAmount = 4,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/squill_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/squill_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(festering_squill, "festering_squill")

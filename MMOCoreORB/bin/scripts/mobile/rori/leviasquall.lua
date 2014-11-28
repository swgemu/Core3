leviasquall = Creature:new {
	objectName = "@mob/creature_names:leviasquall",
	socialGroup = "squall",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1426,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {115,5,-1,-1,130,130,-1,5,-1},
	meatType = "meat_herbivore",
	meatAmount = 50,
	hideType = "hide_bristley",
	hideAmount = 61,
	boneType = "bone_mammal",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/leviasquall.iff"},
	controlDeviceTemplate = "object/intangible/pet/squall_hue.iff",
	scale = 1.5,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(leviasquall, "leviasquall")

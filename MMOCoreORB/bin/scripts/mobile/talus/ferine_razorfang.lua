ferine_razorfang = Creature:new {
	objectName = "@mob/creature_names:kima_ferine_razorfang",
	socialGroup = "kima",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {120,120,10,10,10,10,10,10,-1},
	meatType = "meat_herbivore",
	meatAmount = 7,
	hideType = "hide_bristley",
	hideAmount = 8,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 8,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kima_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/kima_hue.iff",
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ferine_razorfang, "ferine_razorfang")

bull_bantha = Creature:new {
	objectName = "@mob/creature_names:bull_bantha",
	socialGroup = "bantha",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {5,125,5,140,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 475,
	hideType = "hide_wooly",
	hideAmount = 345,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/bantha_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	controlDeviceTemplate = "object/intangible/pet/bantha_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(bull_bantha, "bull_bantha")

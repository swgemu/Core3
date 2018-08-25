nym_domesticated_gurk = Creature:new {
	objectName = "@mob/creature_names:nym_domesticated_gurk",
	socialGroup = "gurk", "nym",
	faction = "nym",
	level = 27,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2830,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {120,125,15,145,145,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 300,
	hideType = "hide_leathery",
	hideAmount = 225,
	boneType = "bone_mammal",
	boneAmount = 250,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gurk_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 0.8,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(nym_domesticated_gurk, "nym_domesticated_gurk")

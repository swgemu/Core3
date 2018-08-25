torton = Creature:new {
	objectName = "@mob/creature_names:torton",
	socialGroup = "torton",
	faction = "",
	level = 24,
	chanceHit = 0.35,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2443,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {10,10,10,-1,-1,-1,-1,145,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_wooly",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 1000,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/torton_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(torton, "torton")

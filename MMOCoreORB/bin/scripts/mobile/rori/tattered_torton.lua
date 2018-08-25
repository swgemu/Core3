tattered_torton = Creature:new {
	objectName = "@mob/creature_names:tattered_torton",
	socialGroup = "torton",
	faction = "",
	level = 17,
	chanceHit = 0.32,
	damageMin = 200,
	damageMax = 210,
	baseXp = 960,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {5,5,5,-1,-1,-1,-1,145,-1},
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
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/torton_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 0.85,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(tattered_torton, "tattered_torton")

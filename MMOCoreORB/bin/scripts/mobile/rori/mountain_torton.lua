mountain_torton = Creature:new {
	objectName = "@mob/creature_names:mountain_torton",
	socialGroup = "torton",
	faction = "",
	level = 34,
	chanceHit = 0.37,
	damageMin = 300,
	damageMax = 310,
	baseXp = 3460,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {140,140,170,-1,-1,160,160,160,-1},
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
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/torton_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_torton, "mountain_torton")

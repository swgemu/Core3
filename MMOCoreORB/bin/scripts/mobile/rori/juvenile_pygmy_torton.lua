juvenile_pygmy_torton = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_juvenile",
	socialGroup = "torton",
	faction = "",
	level = 12,
	chanceHit = 0.28,
	damageMin = 150,
	damageMax = 160,
	baseXp = 514,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {120,120,0,0,0,0,0,135,-1},
	meatType = "meat_carnivore",
	meatAmount = 400,
	hideType = "hide_wooly",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 400,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/torton_hue.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = .45,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(juvenile_pygmy_torton, "juvenile_pygmy_torton")

juvenile_pygmy_torton = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_juvenile",
	socialGroup = "torton",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.28,
	damageMin = 150,
	damageMax = 160,
	baseXp = 514,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {20,20,0,0,0,0,0,35,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/torton_hue.iff"},
	scale = .45,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(juvenile_pygmy_torton, "juvenile_pygmy_torton")

tattered_torton = Creature:new {
	objectName = "@mob/creature_names:tattered_torton",
	socialGroup = "torton",
	pvpFaction = "",
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/torton_hue.iff"},
	scale = 0.85,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tattered_torton, "tattered_torton")

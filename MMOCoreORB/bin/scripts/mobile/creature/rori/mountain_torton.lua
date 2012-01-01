mountain_torton = Creature:new {
	objectName = "@mob/creature_names:mountain_torton",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.37,
	damageMin = 300,
	damageMax = 310,
	baseXp = 3460,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {40,40,70,-1,-1,60,60,60,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_wooly",
	hideAmount = 1000,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/torton.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_torton, "mountain_torton")
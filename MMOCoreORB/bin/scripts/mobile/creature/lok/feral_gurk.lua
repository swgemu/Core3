feral_gurk = Creature:new {
	objectName = "@mob/creature_names:feral_gurk",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.41,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3370,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {35,20,20,20,40,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 350,
	hideType = "hide_leathery",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gurk.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(feral_gurk, "feral_gurk")
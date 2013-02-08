mountain_dewback = Creature:new {
	objectName = "@mob/creature_names:mountain_dewback",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.32,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {40,10,20,50,50,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 330,
	hideType = "hide_leathery",
	hideAmount = 240,
	boneType = "bone_mammal",
	boneAmount = 170,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 5,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mountain_dewback.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_dewback, "mountain_dewback")
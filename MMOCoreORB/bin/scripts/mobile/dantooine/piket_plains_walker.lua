piket_plains_walker = Creature:new {
	objectName = "@mob/creature_names:piket_plains_walker",
	socialGroup = "picket",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.4,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3188,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {40,20,20,20,20,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 450,
	hideType = "hide_scaley",
	hideAmount = 300,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.2,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/piket_plains_walker.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(piket_plains_walker, "piket_plains_walker")
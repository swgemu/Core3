event_bull_rancor = Creature:new {
	objectName = "@mob/creature_names:bull_rancor",
	customName = "a bull rancor (event)",
	socialGroup = "rancor",
	pvpFaction = "",
	faction = "",
	level = 65,
	chanceHit = 0.6,
	damageMin = 455,
	damageMax = 620,
	baseXp = 0,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {35,60,15,80,80,80,15,15,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.01,
	ferocity = 11,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bull_rancor.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareadisease",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(event_bull_rancor, "event_bull_rancor")

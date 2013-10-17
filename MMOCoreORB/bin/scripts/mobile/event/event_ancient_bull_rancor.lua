event_ancient_bull_rancor = Creature:new {
	objectName = "@mob/creature_names:ancient_bull_rancor",
	customName = "an ancient bull rancor (event)",
	socialGroup = "rancor",
	pvpFaction = "",
	faction = "",
	level = 98,
	chanceHit = 0.95,
	damageMin = 620,
	damageMax = 950,
	baseXp = 0,
	baseHAM = 20000,
	baseHAMmax = 25000,
	armor = 3,
	resists = {30,60,30,100,100,100,30,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 20,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bull_rancor.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareableeding",""},
		{"creatureareacombo",""}
	}
}

CreatureTemplates:addCreatureTemplate(event_ancient_bull_rancor, "event_ancient_bull_rancor")

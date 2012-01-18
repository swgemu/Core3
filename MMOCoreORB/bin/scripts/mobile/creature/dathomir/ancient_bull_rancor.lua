ancient_bull_rancor = Creature:new {
	objectName = "@mob/creature_names:ancient_bull_rancor",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 98,
	chanceHit = 0.95,
	damageMin = 620,
	damageMax = 950,
	baseXp = 9336,
	baseHAM = 20000,
	baseHAMmax = 25000,
	armor = 3,
	resists = {30,60,30,100,100,100,30,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 950,
	milk = 0,
	tamingChance = 0,
	ferocity = 20,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,
	lootChance = 4300000,

	templates = {"object/mobile/bull_rancor.iff"},
	lootgroups = {
		{group = "rancor_common", chance = 3300000},
		{group = "pistols", chance = 3300000},
		{group = "rifles", chance = 3400000}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareableeding",""},
		{"creatureareacombo",""}
	}
}

CreatureTemplates:addCreatureTemplate(ancient_bull_rancor, "ancient_bull_rancor")
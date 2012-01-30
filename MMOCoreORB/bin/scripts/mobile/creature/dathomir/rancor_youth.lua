rancor_youth = Creature:new {
	objectName = "@mob/creature_names:rancor_youth",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4370,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {35,60,30,100,100,100,30,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 700,
	hideType = "hide_leathery",
	hideAmount = 753,
	boneType = "bone_mammal",
	boneAmount = 653,
	milk = 0,
	tamingChance = 0,
	ferocity = 8,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor_youth.iff"},
	lootGroups = {
		{
			groups = {
				{group = "rancor_common", chance = 3300000},
				{group = "pistols", chance = 3300000},
				{group = "rifles", chance = 3400000}
			},
			lootChance = 2700000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareableeding",""},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rancor_youth, "rancor_youth")
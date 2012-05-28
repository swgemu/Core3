Nightsister_bull_rancor = Creature:new {
	objectName = "@mob/creature_names:nightsister_bull_rancor",
	socialGroup = "nightsister",
	pvpFaction = "",
	faction = "nightsister",
	level = 65,
	chanceHit = 0.6,
	damageMin = 455,
	damageMax = 620,
	baseXp = 6288,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {15,60,15,100,100,100,15,15,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 900,
	boneType = "bone_mammal",
	boneAmount = 850,
	milk = 0,
	tamingChance = 0,
	ferocity = 11,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bull_rancor.iff"},
	lootGroups = {
		{
			groups = {
				{group = "rancor_common", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "rifles", chance = 1000000},
				{group = "unarmed_melee", chance = 500000}
			},
			lootChance = 4500000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareadisease",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(Nightsister_bull_rancor, "Nightsister_bull_rancor")
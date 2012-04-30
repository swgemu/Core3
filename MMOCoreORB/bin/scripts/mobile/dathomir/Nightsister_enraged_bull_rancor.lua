Nightsister_enraged_bull_rancor = Creature:new {
	objectName = "@mob/creature_names:nightsister_enraged_bull_rancor",
	socialGroup = "Nightsister",
	pvpFaction = "",
	faction = "",
	level = 89,
	chanceHit = 0.85,
	damageMin = 570,
	damageMax = 850,
	baseXp = 8500,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 1,
	resists = {0,70,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 880,
	hideType = "hide_leathery",
	hideAmount = 750,
	boneType = "bone_mammal",
	boneAmount = 670,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bull_rancor.iff"},
	lootGroups = {
		{
			groups = {
				{group = "rancor_common", chance = 2800000},
				{group = "pistols", chance = 2800000},
				{group = "rifles", chance = 2800000},
				{group = "unarmed_melee", chance = 1600000}
			},
			lootChance = 4200000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaknockdown","knockdownChance=30"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(Nightsister_enraged_bull_rancor, "Nightsister_enraged_bull_rancor")
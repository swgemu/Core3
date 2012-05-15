Nightsister_enraged_rancor = Creature:new {
	objectName = "@mob/creature_names:nightsister_enraged_rancor",
	socialGroup = "nightsister",
	pvpFaction = "",
	faction = "nightsister",
	level = 80,
	chanceHit = 0.75,
	damageMin = 570,
	damageMax = 850,
	baseXp = 7668,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 1,
	resists = {30,60,30,100,100,100,30,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 878,
	boneType = "bone_mammal",
	boneAmount = 778,
	milk = 0,
	tamingChance = 0,
	ferocity = 15,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor.iff"},
	lootGroups = {
		{
			groups = {
				{group = "rancor_common", chance = 2800000},
				{group = "pistols", chance = 2800000},
				{group = "rifles", chance = 2800000},
				{group = "unarmed_melee", chance = 1600000}
			},
			lootChance = 4150000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(Nightsister_enraged_rancor, "Nightsister_enraged_rancor")
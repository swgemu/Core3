gnarled_rancor = Creature:new {
	objectName = "@mob/creature_names:gnarled_rancor",
	socialGroup = "rancor",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.47,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4552,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 1,
	resists = {0,30,-1,50,50,50,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 876,
	boneType = "bone_mammal",
	boneAmount = 775,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor_hue.iff"},
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
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gnarled_rancor, "gnarled_rancor")
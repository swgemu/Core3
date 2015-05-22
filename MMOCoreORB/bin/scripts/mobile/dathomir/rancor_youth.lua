rancor_youth = Creature:new {
	objectName = "@mob/creature_names:rancor_youth",
	socialGroup = "rancor",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4370,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {135,160,30,200,200,200,30,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 700,
	hideType = "hide_leathery",
	hideAmount = 753,
	boneType = "bone_mammal",
	boneAmount = 653,
	milk = 0,
	tamingChance = 0,
	ferocity = 8,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor_youth.iff"},
	scale = 0.8,
	lootGroups = {
		{
			groups = {
				{group = "rancor_common", chance = 4000000},
				{group = "armor_all", chance = 2000000},
				{group = "weapons_all", chance = 2500000},
				{group = "wearables_all", chance = 1500000}
			},
			lootChance = 1900000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""},
		{"creatureareableeding",""}
	}
}

CreatureTemplates:addCreatureTemplate(rancor_youth, "rancor_youth")

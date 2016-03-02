grassland_voritor_tracker = Creature:new {
	objectName = "@mob/creature_names:grassland_voritor_tracker",
	socialGroup = "voritor",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 375,
	damageMax = 460,
	baseXp = 4370,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {165,165,30,30,30,30,-1,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 45,
	hideType = "hide_leathery",
	hideAmount = 35,
	boneType = "bone_avian",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/grassland_voritor_tracker.iff"},
	scale = 1.1,
	lootGroups = {
		{
			groups = {
				{group = "voritor_lizard_common", chance = 10000000}
			},
			lootChance = 1900000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(grassland_voritor_tracker, "grassland_voritor_tracker")

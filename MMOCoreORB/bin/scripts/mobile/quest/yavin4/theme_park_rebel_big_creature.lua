theme_park_rebel_big_creature = Creature:new {
	objectName = "@mob/creature_names:mawgax_raptor",
	socialGroup = "mawgax",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 240,
	damageMax = 250,
	baseXp = 3005,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {20,20,10,-1,10,10,30,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 90,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_avian",
	boneAmount = 55,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mawgax_hue.iff"},
	lootGroups = {
		{
			groups = {
				{group = "theme_park_loot_rebel_big_creature", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(theme_park_rebel_big_creature, "theme_park_rebel_big_creature")
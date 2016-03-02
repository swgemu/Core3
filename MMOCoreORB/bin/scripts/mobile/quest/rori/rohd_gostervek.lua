rohd_gostervek = Creature:new {
	objectName = "@mob/creature_names:imperial_army_captain",
	customName = "Captain Rohd Gostervek",
	socialGroup = "imperial",
	faction = "imperial",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,45,0,-1,40,-1,40,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_captain_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "task_loot_booto_lubble_thermal_detonator", chance = 10000000}
			},
			lootChance = 10000000
		}						
	},
	weapons = {"imperial_weapons_medium"},
	attacks = merge(riflemanmaster,carbineermaster,brawlermaster),
	conversationTemplate = "",
	optionsBitmask = AIENABLED
}

CreatureTemplates:addCreatureTemplate(rohd_gostervek, "rohd_gostervek")
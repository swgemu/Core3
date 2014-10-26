xalox_smuggler2 = Creature:new {
	objectName = "@mob/creature_names:smuggler",
	socialGroup = "thug",
	pvpFaction = "thug",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 714,
	baseHAM = 2000,
	baseHAMmax = 3000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_slicer_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "task_loot_xalox_guul_datadisc", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"pirate_weapons_medium"},
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(xalox_smuggler2, "xalox_smuggler2")

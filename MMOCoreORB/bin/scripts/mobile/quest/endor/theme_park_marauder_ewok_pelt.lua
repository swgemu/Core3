theme_park_marauder_ewok_pelt = Creature:new {
	objectName = "@mob/creature_names:masterful_ewok_warrior",
	socialGroup = "gondula_tribe",
	faction = "gondula_tribe",
	mobType = MOB_NPC,
	level = 21,
	chanceHit = 0.28,
	damageMin = 200,
	damageMax = 300,
	baseXp = 988,
	baseHAM = 3000,
	baseHAMmax = 3200,
	armor = 0,
	resists = {5,5,0,15,15,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_ewok_f_03.iff"},
	lootGroups =
	{
		{
			groups = {
				{group = "theme_park_loot_marauder_ewok_pelt", chance = 10000000}
			},
			lootChance = 10000000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "ewok_weapons",
	secondaryWeapon = "unarmed",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlermaster,marksmanmaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_ewok_pelt, "theme_park_marauder_ewok_pelt")

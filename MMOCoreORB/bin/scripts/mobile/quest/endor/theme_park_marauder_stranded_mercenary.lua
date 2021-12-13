theme_park_marauder_stranded_mercenary = Creature:new {
	objectName = "",
	customName = "a stranded mercenary",
	socialGroup = "",
	faction = "",
	mobType = MOB_NPC,
	level = 35,
	chanceHit = 0.35,
	damageMin = 300,
	damageMax = 400,
	baseXp = 3500,
	baseHAM = 6800,
	baseHAMmax = 7200,
	armor = 0,
	resists = {20,20,10,40,-1,40,10,-1,-1},
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
	creatureBitmask = KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dressed_mercenary_warlord_hum_m.iff",
			"object/mobile/dressed_mercenary_elite_hum_m.iff",
			"object/mobile/dressed_mercenary_destroyer_wee_m.iff",
			"object/mobile/dressed_mercenary_commander_nikto_m.iff"
			},
	lootGroups =
	{
		{ groups =
			{ {group = "theme_park_loot_marauder_hyperdrive", chance = 10000000} },
			lootChance = 10000000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "pirate_weapons_heavy",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_stranded_mercenary, "theme_park_marauder_stranded_mercenary")

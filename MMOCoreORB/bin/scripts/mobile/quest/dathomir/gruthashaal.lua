gruthashaal = Creature:new {
	objectName = "",
	socialGroup = "",
	faction = "",
	mobType = MOB_NPC,
	level = 40,
	chanceHit = 10,
	damageMin = 240,
	damageMax = 350,
	baseXp = 3250,
	baseHAM = 4500,
	baseHAMmax = 7800,
	armor = 3,
	resists = {5,5,5,5,5,5,5,5,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = { "object/mobile/dressed_commoner_naboo_human_female_08.iff"
		},

	lootGroups = {
		{
			groups = {
				{group = "task_loot_ancient_lightsaber", chance = 10000000},
				
			},
			lootChance = 10000000
		},
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(tkamaster, brawlermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(gruthashaal, "gruthashaal")

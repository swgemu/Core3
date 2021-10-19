theme_park_marauder_ewok_holy = Creature:new {
	objectName = "@npc_name:ewok_base_male",
	customName = "Ewok Holy One",
	socialGroup = "gondula_tribe",
	faction = "gondula_tribe",
	mobType = MOB_NPC,
	level = 34,
	chanceHit = 0.35,
	damageMin = 400,
	damageMax = 550,
	baseXp = 4000,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {30,30,30,30,30,30,30,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_ewok_m_07.iff"},
	lootGroups =
	{
		{
			groups = {
				{group = "theme_park_loot_marauder_ewok_staff", chance = 10000000}
			},
			lootChance = 10000000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "ewok_weapons",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(riflemanmaster,brawlermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_ewok_holy, "theme_park_marauder_ewok_holy")

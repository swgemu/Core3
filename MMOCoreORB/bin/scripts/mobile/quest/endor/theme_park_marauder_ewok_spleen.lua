theme_park_marauder_ewok_spleen = Creature:new {
	objectName = "@mob/creature_names:masterful_ewok_warrior",
	socialGroup = "gondula_tribe",

	mobType = MOB_NPC,
	faction = "gondula_tribe",
	level = 35,
	chanceHit = 0.41,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3460,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {60,60,60,60,60,60,60,60,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ewok_m_08.iff",
		"object/mobile/dressed_ewok_m_09.iff",
		"object/mobile/dressed_ewok_m_10.iff",
		"object/mobile/dressed_ewok_m_12.iff"},
	lootGroups =
	{
		{
			groups = {
				{group = "theme_park_loot_marauder_ewok_spleen", chance = 10000000}
			},
			lootChance = 10000000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "ewok_weapons",
	secondaryWeapon = "none",

	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(riflemanmaster,brawlermaster),
	secondaryAttacks = { }
}
CreatureTemplates:addCreatureTemplate(theme_park_marauder_ewok_spleen, "theme_park_marauder_ewok_spleen")

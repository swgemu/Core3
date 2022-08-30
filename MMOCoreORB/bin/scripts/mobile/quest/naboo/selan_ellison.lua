selan_ellison = Creature:new {
	objectName = "@mob/creature_names:commoner",
	customName = "Selan Ellison",
	socialGroup = "townsperson",
	mobType = MOB_NPC,
	faction = "townsperson",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {15,15,15,15,15,15,15,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED + CONVERSABLE + JTLINTERESTING,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_commoner_naboo_human_female_01.iff",
		"object/mobile/dressed_commoner_naboo_human_female_02.iff",
		"object/mobile/dressed_commoner_naboo_human_female_03.iff",
		"object/mobile/dressed_commoner_naboo_human_female_04.iff",
		"object/mobile/dressed_commoner_naboo_human_female_05.iff",
		"object/mobile/dressed_commoner_naboo_human_female_06.iff",
		"object/mobile/dressed_commoner_naboo_human_female_07.iff",
		"object/mobile/dressed_commoner_naboo_human_female_08.iff"
	},

	lootGroups = {},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "selan_ellison_convo_template",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = {},
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(selan_ellison, "selan_ellison")

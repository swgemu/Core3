gins_rebel_specforce_sergeant = Creature:new {
	objectName = "@mob/creature_names:rebel_specforce_sergeant",
	socialGroup = "rebel",
	faction = "rebel",
	mobType = MOB_NPC,
	level = 21,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {5,5,5,5,5,5,5,-1,-1},
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

	templates = {
		"object/mobile/dressed_rebel_specforce_sergeant_bothan_male_01.iff",
		"object/mobile/dressed_rebel_specforce_sergeant_human_male_01.iff",
		"object/mobile/dressed_rebel_specforce_sergeant_moncal_female_01.iff",
		"object/mobile/dressed_rebel_specforce_sergeant_moncal_male_01.iff",
		"object/mobile/dressed_rebel_specforce_sergeant_trandoshan_male_01.iff",
		"object/mobile/dressed_rebel_specforce_sergeant_twk_female_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "task_loot_gins_darone_special_forces_vibroknuckler", chance = 10000000}
			},
			lootChance = 10000000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "ranged_weapons",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(marksmanmaster,brawlermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(gins_rebel_specforce_sergeant, "gins_rebel_specforce_sergeant")

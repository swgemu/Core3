archaic_panshee_ritualist = Creature:new {
	objectName = "@mob/creature_names:archaic_panshee_ritualist",
	socialGroup = "panshee_tribe",
	faction = "panshee_tribe",
	mobType = MOB_NPC,
	level = 60,
	chanceHit = 0.6,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5738,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {25,25,45,45,45,45,45,45,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ewok_f_02.iff",
		"object/mobile/dressed_ewok_f_10.iff",
		"object/mobile/dressed_ewok_f_11.iff",
		"object/mobile/dressed_ewok_m_02.iff"},
	lootGroups = {
		 {
	        groups = {
				{group = "panshee_tribe_tier_2", chance = 10000000}
			},
			lootChance = 2200000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "ewok_ranged",
	secondaryWeapon = "ewok_melee",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlermaster,pikemanmaster),
	secondaryAttacks = merge(riflemanmaster,marksmanmaster),
}

CreatureTemplates:addCreatureTemplate(archaic_panshee_ritualist, "archaic_panshee_ritualist")

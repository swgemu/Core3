blood_crazed_plains_marauder = Creature:new {
	objectName = "@mob/creature_names:blood_crazed_plains_marauder",
	socialGroup = "endor_marauder",
	faction = "endor_marauder",
	mobType = MOB_NPC,
	level = 56,
	chanceHit = 0.55,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5464,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {0,0,0,-1,-1,-1,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_blood_crazed_plains_marauder.iff"},
	lootGroups = {
		{
			groups = {
				{group = "endor_marauder_tier_2", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "marauder_melee",
	secondaryWeapon = "pirate_pistol",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(swordsmanmaster,brawlermaster),
	secondaryAttacks = merge(pistoleermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(blood_crazed_plains_marauder, "blood_crazed_plains_marauder")

rogue_marauder = Creature:new {
	objectName = "",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	customName = "a Rogue Marauder",
	socialGroup = "self",
	faction = "",
	level = 44,
	chanceHit = 0.47,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4370,
	baseHAM = 12000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {0,0,0,-1,0,0,-1,0,-1},
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
	scale = 1.35,

	templates = {
		"object/mobile/dressed_marauder.iff",
		"object/mobile/marauder_male.iff",
		"object/mobile/marauder_male_02.iff",
		"object/mobile/marauder_male_03.iff",
		"object/mobile/marauder_female.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "endor_marauder_tier_2", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "pirate_carbine",
	secondaryWeapon = "pirate_sword",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(carbineermaster,marksmanmaster),
	secondaryAttacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(rogue_marauder, "rogue_marauder")

gambler_patrol = Creature:new {
	objectName = "@mob/creature_names:gambler",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "thug",
	faction = "",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 187,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER,
	diet = HERBIVORE,
	customAiMap = "cityPatrol",

	templates = {"object/mobile/dressed_commoner_tatooine_nikto_male_02.iff",
		"object/mobile/dressed_commoner_tatooine_aqualish_female_01.iff",
		"object/mobile/dressed_commoner_naboo_twilek_female_01.iff",
		"object/mobile/dressed_commoner_naboo_human_female_03.iff",
		"object/mobile/dressed_commoner_tatooine_devaronian_male_01.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 2000000},
				{group = "pistols", chance = 1000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "ranged_weapons",
	secondaryWeapon = "unarmed",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = marksmannovice,
	secondaryAttacks = brawlermid
}

CreatureTemplates:addCreatureTemplate(gambler_patrol, "gambler_patrol")
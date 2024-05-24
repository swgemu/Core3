pathfinder = Creature:new {
	objectName = "",
	customName = "Pathfinder",
	socialGroup = "wilder",
	mobType = MOB_NPC,
	faction = "",
	level = 21,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 2006,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {0,0,0,35,35,35,35,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_thug_aqualish_male_01.iff",
			"object/mobile/dressed_criminal_thug_aqualish_male_02.iff",
			"object/mobile/dressed_criminal_thug_aqualish_female_01.iff",
			"object/mobile/dressed_criminal_thug_aqualish_female_02.iff",
			"object/mobile/dressed_criminal_thug_rodian_male_01.iff",
			"object/mobile/dressed_criminal_thug_rodian_female_01.iff", },
	lootGroups = {
		{
			groups = {
				{group = "wilder_tier_1", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "rebel_weapons_heavy",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
	reactionStf = "@npc_reaction/townperson",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlermaster,marksmanmaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(pathfinder, "pathfinder")

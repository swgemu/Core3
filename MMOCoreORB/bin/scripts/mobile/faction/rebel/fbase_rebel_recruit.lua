fbase_rebel_recruit = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_recruit",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "rebel",
	faction = "rebel",
	level = 24,
	chanceHit = 0.37,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2400,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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

	templates = {"object/mobile/dressed_rebel_crewman_human_male_01.iff",
			"object/mobile/dressed_rebel_crewman_human_male_02.iff",
			"object/mobile/dressed_rebel_crewman_human_male_03.iff",
			"object/mobile/dressed_rebel_crewman_human_male_04.iff",
			"object/mobile/dressed_rebel_crewman_human_female_01.iff",
			"object/mobile/dressed_rebel_crewman_human_female_02.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "rebel_tier_1", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "rebel_carbine",
	secondaryWeapon = "rebel_pistol",
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(marksmanmaster,carbineernovice),
	secondaryAttacks = merge(marksmanmaster,pistoleernovice)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_recruit, "fbase_rebel_recruit")

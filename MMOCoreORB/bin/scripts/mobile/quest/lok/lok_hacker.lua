lok_hacker = Creature:new {
       objectName = "@npc_name:human_base_female",
       customName = "Hacker",
       socialGroup = "nym",
       faction = "nym",
	mobType = MOB_NPC,
       level = 22,
       chanceHit = 0.330000,
       damageMin = 190,
       damageMax = 200,
       baseXp = 1803,
       baseHAM = 5000,
       baseHAMmax = 6100,
       armor = 0,
       resists = {20,20,0,-1,-1,40,40,-1,-1},
       meatType = "",
       meatAmount = 0,
       hideType = "",
       hideAmount = 0,
       boneType = "",
       boneAmount = 0,
       milk = 0,
       tamingChance = 0.000000,
       ferocity = 0,
       pvpBitmask = NONE,
       creatureBitmask = NONE,
       optionsBitmask = AIENABLED + CONVERSABLE,
       diet = HERBIVORE,

       templates = { "object/mobile/dressed_criminal_assassin_human_female_01.iff" },
       conversationTemplate = "lokHackerConvoTemplate",
       lootGroups = {},
       primaryWeapon = "unarmed",
	secondaryWeapon = "none",
       
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = {},
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(lok_hacker, "lok_hacker")

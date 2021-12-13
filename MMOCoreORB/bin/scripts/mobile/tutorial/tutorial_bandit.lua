tutorial_bandit = Creature:new {
	objectName = "@mob/creature_names:bandit",
	socialGroup = "",
	faction = "",
	mobType = MOB_NPC,
	level = 1,
	chanceHit = 0.390000,
	damageMin = 5,
	damageMax = 10,
	baseXp = 100,
	baseHAM = 1000,
	baseHAMmax = 1000,
	armor = 0,
	resists = {-1,-1,-1,-1,-1,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + ENEMY,
	optionsBitmask = AIENABLED,
	creatureBitmask = NONE,
	diet = NONE,

	templates = {"object/mobile/dressed_cobral_bandit_bith_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "tutorial_pirate", chance = 10000000}
			},
			lootChance = 10000000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "tutorial_bandit",
	secondaryWeapon = "unarmed",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlernovice,marksmannovice),
	secondaryAttacks = { },
	conversationTemplate = "",
}

CreatureTemplates:addCreatureTemplate(tutorial_bandit, "tutorial_bandit")

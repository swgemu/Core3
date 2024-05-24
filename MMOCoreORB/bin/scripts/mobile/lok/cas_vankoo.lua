cas_vankoo = Creature:new {
	objectName = "@mob/creature_names:cas_vankoo",
	socialGroup = "kimogila",
	faction = "bandit",
	mobType = MOB_NPC,
	level = 117,
	chanceHit = 3.4,
	damageMin = 725,
	damageMax = 1160,
	baseXp = 11109,
	baseHAM = 50000,
	baseHAMmax = 59000,
	armor = 2,
	resists = {75,75,0,10,10,10,10,0,0},
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

	templates = {"object/mobile/dressed_lok_cas_vankoo.iff"},
	lootGroups = {
		{
			groups = {
				{group = "bandit_tier_4", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "cas_vankoo_weapons",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
	reactionStf = "@npc_reaction/townperson",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(pistoleermaster,pikemanmaster,marksmanmaster,brawlermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(cas_vankoo, "cas_vankoo")

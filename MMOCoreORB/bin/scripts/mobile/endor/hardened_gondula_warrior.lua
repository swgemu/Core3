hardened_gondula_warrior = Creature:new {
	objectName = "@mob/creature_names:hardened_gondula_warrior",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "gondula_tribe",
	faction = "gondula_tribe",
	level = 53,
	chanceHit = 0.53,
	damageMin = 410,
	damageMax = 530,
	baseXp = 5190,
	baseHAM = 10000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {30,30,5,5,5,5,-1,5,-1},
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
		"object/mobile/dressed_ewok_m_06.iff",
		"object/mobile/dressed_ewok_m_09.iff"},
	lootGroups = {
		{
			groups = {
				{group = "gondula_tribe_tier_2", chance = 10000000}
			},
			lootChance = 2060000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "ewok_ranged",
	secondaryWeapon = "ewok_melee",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(riflemanmaster,marksmanmaster),
	secondaryAttacks = merge(pikemanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(hardened_gondula_warrior, "hardened_gondula_warrior")

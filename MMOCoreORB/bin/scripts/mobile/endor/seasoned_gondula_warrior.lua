seasoned_gondula_warrior = Creature:new {
	objectName = "@mob/creature_names:seasoned_gondula_warrior",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "gondula_tribe",
	faction = "gondula_tribe",
	level = 45,
	chanceHit = 0.460000,
	damageMin = 360,
	damageMax = 430,
	baseXp = 4370,
	baseHAM = 9500,
	baseHAMmax = 11700,
	armor = 0,
	resists = {50,50,0,-1,0,0,-1,0,-1},
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
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ewok_m_09.iff",
		"object/mobile/dressed_ewok_m_10.iff"},
	lootGroups = {
		{
			groups = {
				{group = "gondula_tribe_tier_2", chance = 10000000}
			},
			lootChance = 1900000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "ewok_ranged",
	secondaryWeapon = "ewok_ranged",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(riflemanmaster,marksmanmaster),
	secondaryAttacks = merge(riflemanmaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(seasoned_gondula_warrior, "seasoned_gondula_warrior")

fbase_rebel_squad_leader_extreme = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_squad_leader_extreme",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "rebel",
	faction = "rebel",
	level = 168,
	chanceHit = 7.8,
	damageMin = 985,
	damageMax = 1680,
	baseXp = 16800,
	baseHAM = 101000,
	baseHAMmax = 141000,
	armor = 2,
	resists = {110,110,40,40,130,40,130,-1,-1},
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

	templates = {
		"object/mobile/dressed_rebel_brigadier_general_bith_male.iff",
		"object/mobile/dressed_rebel_brigadier_general_human_female_01.iff",
		"object/mobile/dressed_rebel_brigadier_general_moncal_female.iff",
		"object/mobile/dressed_rebel_brigadier_general_rodian_female_01.iff",
		"object/mobile/dressed_rebel_brigadier_general_sullustan_male.iff",
		"object/mobile/dressed_rebel_brigadier_general_trandoshan_female.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "rebel_tier_4", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "rebel_carbine",
	secondaryWeapon = "rebel_pistol",
	thrownWeapon = "thrown_weapons",

	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(marksmanmaster,carbineermaster),
	secondaryAttacks = merge(marksmanmaster,pistoleermaster)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_squad_leader_extreme, "fbase_rebel_squad_leader_extreme")

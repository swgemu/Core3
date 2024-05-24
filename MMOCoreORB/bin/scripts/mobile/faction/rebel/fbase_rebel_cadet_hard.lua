fbase_rebel_cadet_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_cadet_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "rebel",
	faction = "rebel",
	level = 66,
	chanceHit = 0.66,
	damageMin = 475,
	damageMax = 660,
	baseXp = 6600,
	baseHAM = 12500,
	baseHAMmax = 18000,
	armor = 1,
	resists = {115,115,10,10,10,-1,10,-1,-1},
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
		"object/mobile/dressed_rebel_pilot_human_female_01.iff",
		"object/mobile/dressed_rebel_pilot_human_male_01.iff",
		"object/mobile/dressed_rebel_pilot_human_male_02.iff",
		"object/mobile/dressed_rebel_pilot_rodian_male_01.iff",
		"object/mobile/dressed_rebel_pilot_sullustan_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "rebel_tier_2", chance = 10000000}
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
	primaryAttacks = merge(carbineermid,marksmanmaster),
	secondaryAttacks = merge(pistoleermid,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_cadet_hard, "fbase_rebel_cadet_hard")

fbase_rebel_heavy_trooper = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_heavy_trooper",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_ANDROID,
	socialGroup = "rebel",
	faction = "rebel",
	level = 50,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 5000,
	baseHAM = 10300,
	baseHAMmax = 12500,
	armor = 0,
	resists = {140,120,115,150,150,150,150,125,-1},
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
	creatureBitmask = PACK + STALKER + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_ris_01.iff",
		"object/mobile/dressed_rebel_ris_02.iff",
		"object/mobile/dressed_rebel_ris_03.iff",
		"object/mobile/dressed_rebel_ris_04.iff",
		"object/mobile/dressed_rebel_crewman_human_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "rebel_commando_tier_2", chance = 10000000}
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
	primaryAttacks = merge(marksmanmaster,carbineernovice),
	secondaryAttacks = merge(marksmanmaster,pistoleernovice)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_heavy_trooper, "fbase_rebel_heavy_trooper")

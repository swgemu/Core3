fbase_rebel_commando = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_commando",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "rebel",
	faction = "rebel",
	level = 44,
	chanceHit = 0.47,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4400,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {30,30,30,130,30,130,-1,-1,-1},
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
		"object/mobile/dressed_rebel_commando_human_female_01.iff",
		"object/mobile/dressed_rebel_commando_human_male_01.iff",
		"object/mobile/dressed_rebel_commando_moncal_male_01.iff",
		"object/mobile/dressed_rebel_commando_rodian_male_01.iff",
		"object/mobile/dressed_rebel_commando_twilek_female_01.iff",
		"object/mobile/dressed_rebel_commando_zabrak_female_01.iff"},
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
	secondaryWeapon = "commando_melee",
	thrownWeapon = "thrown_weapons",

	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(carbineernovice,marksmanmaster),
	secondaryAttacks = merge(tkanovice,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_commando, "fbase_rebel_commando")

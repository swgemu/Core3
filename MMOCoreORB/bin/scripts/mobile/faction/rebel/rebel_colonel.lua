rebel_colonel = Creature:new {
	objectName = "@mob/creature_names:rebel_colonel",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "rebel",
	faction = "rebel",
	level = 24,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {15,15,10,10,10,-1,10,-1,-1},
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
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_colonel_bothan_male.iff",
		"object/mobile/dressed_rebel_colonel_fat_zabrak_male.iff",
		"object/mobile/dressed_rebel_colonel_moncal_female.iff",
		"object/mobile/dressed_rebel_colonel_old_human_female.iff",
		"object/mobile/dressed_rebel_colonel_sullustan_male_01.iff",
		"object/mobile/dressed_rebel_colonel_twk_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "rebel_officer_tier_1", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "rebel_carbine",
	secondaryWeapon = "rebel_pistol",
	conversationTemplate = "rebelRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(carbineernovice,marksmanmaster),
	secondaryAttacks = merge(pistoleernovice,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(rebel_colonel, "rebel_colonel")

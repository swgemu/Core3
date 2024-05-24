fbase_rebel_squad_leader = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_squad_leader",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "rebel",
	faction = "rebel",
	level = 42,
	chanceHit = 0.46,
	damageMin = 355,
	damageMax = 420,
	baseXp = 4200,
	baseHAM = 9500,
	baseHAMmax = 11700,
	armor = 0,
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
		"object/mobile/dressed_rebel_specforce_pathfinder_human_male_01.iff",
		"object/mobile/dressed_rebel_specforce_pathfinder_moncal_female_01.iff",
		"object/mobile/dressed_rebel_specforce_pathfinder_rodian_female_01.iff",
		"object/mobile/dressed_rebel_specforce_pathfinder_twk_female_01.iff",
		"object/mobile/dressed_rebel_specforce_pathfinder_twk_male_01.iff",
		"object/mobile/dressed_rebel_specforce_pathfinder_zabrak_female_fat_01.iff"
		},
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
	thrownWeapon = "thrown_weapons",

	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(marksmanmaster,carbineernovice),
	secondaryAttacks = merge(marksmanmaster,pistoleernovice)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_squad_leader, "fbase_rebel_squad_leader")

fbase_rebel_squad_leader_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_squad_leader_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "rebel",
	faction = "rebel",
	level = 84,
	chanceHit = 0.84,
	damageMin = 565,
	damageMax = 840,
	baseXp = 8400,
	baseHAM = 16500,
	baseHAMmax = 24000,
	armor = 1,
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
		"object/mobile/dressed_rebel_general_fat_human_male_01.iff",
		"object/mobile/dressed_rebel_general_human_female_01.iff",
		"object/mobile/dressed_rebel_general_human_female_02.iff",
		"object/mobile/dressed_rebel_general_moncal_male_01.iff",
		"object/mobile/dressed_rebel_general_old_twilek_male_01.iff",
		"object/mobile/dressed_rebel_general_rodian_female_01.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1250000},
				{group = "armor_all", chance = 1250000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "wearables_all", chance = 1000000}
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
	primaryAttacks = merge(marksmanmaster,carbineermid),
	secondaryAttacks = merge(marksmanmaster,pistoleermid)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_squad_leader_hard, "fbase_rebel_squad_leader_hard")
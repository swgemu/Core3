bh_scientist = Creature:new {
	objectName = "@mob/creature_names:scientist",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3279,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_combatmedic_trainer_human_male_01.iff",
		"object/mobile/dressed_brigade_captain_human_male_01.iff",
		"object/mobile/dressed_hutt_medic2_twilek_male_01.iff",
		"object/mobile/dressed_combatmedic_trainer_human_female_01.iff",
		"object/mobile/dressed_doctor_trainer_moncal_male_01.iff",
		"object/mobile/dressed_combatmedic_trainer_rodian_male_01.iff",
		"object/mobile/dressed_mercenary_medic_rodian_female_01.iff" },
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 2500000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kit_parts", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "power_crystals", chance = 1000000},
				{group = "wearables_all", chance = 1000000},
				{group = "weapons_all", chance = 1000000},
				{group = "armor_all", chance = 1000000},
				{group = "clothing_attachments", chance = 1000000},
				{group = "armor_attachments", chance = 1000000}
			},
			lootChance = 3680000
		},
		{
			groups = {
				{group = "junk", chance = 2500000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kit_parts", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "power_crystals", chance = 500000},
				{group = "power_crystals", chance = 500000},
				{group = "wearables_all", chance = 1000000},
				{group = "weapons_all", chance = 1000000},
				{group = "armor_all", chance = 1000000},
				{group = "clothing_attachments", chance = 1000000},
				{group = "armor_attachments", chance = 1000000}
			},
			lootChance = 3680000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "rebel_weapons_heavy",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
	reactionStf = "@npc_reaction/townperson",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(commandomaster,marksmanmaster,brawlermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(bh_scientist, "bh_scientist")

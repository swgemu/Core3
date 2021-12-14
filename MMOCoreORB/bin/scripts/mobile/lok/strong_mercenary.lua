strong_mercenary = Creature:new {
	objectName = "@mob/creature_names:mercenary_strong",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "lok_mercenaries",
	faction = "lok_mercenaries",
	level = 36,
	chanceHit = 0.42,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3642,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {40,35,25,-1,25,25,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_mercenary_strong_hum_m.iff",
		"object/mobile/dressed_mercenary_strong_hum_f.iff",
		"object/mobile/dressed_mercenary_strong_rod_m.iff",
		"object/mobile/dressed_mercenary_strong_tran_m.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4100000},
				{group = "tailor_components", chance = 1000000},
				{group = "color_crystals", chance = 400000},
				{group = "power_crystals", chance = 400000},
				{group = "melee_unarmed", chance = 600000},
				{group = "melee_polearm", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "rifles", chance = 600000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000},
				{group = "wearables_common", chance = 500000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "rebel_weapons_heavy",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(riflemanmaster,carbineermaster,brawlermaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(strong_mercenary, "strong_mercenary")

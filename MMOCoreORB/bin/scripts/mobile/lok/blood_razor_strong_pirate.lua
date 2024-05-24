blood_razor_strong_pirate = Creature:new {
	objectName = "@mob/creature_names:blood_razor_pirate_strong",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "bloodrazor",
	faction = "bloodrazor",
	level = 26,
	chanceHit = 0.36,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2730,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {20,40,15,-1,-1,-1,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_blood_razor_pirate_strong_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_nikto_m.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_rod_m.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_tran_m.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_wee_m.iff",
		"object/mobile/dressed_blood_razor_pirate_strong_zab_m.iff"
	},

	lootGroups = {
		{
			groups = {
				{group = "bloodrazor_tier_1", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "blood_razer_weapons",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(pistoleermaster,pikemanmaster,tkamaster,brawlermaster,marksmanmaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(blood_razor_strong_pirate, "blood_razor_strong_pirate")

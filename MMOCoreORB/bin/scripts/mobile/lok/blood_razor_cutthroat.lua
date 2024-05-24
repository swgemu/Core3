blood_razor_cutthroat = Creature:new {
	objectName = "@mob/creature_names:blood_razor_cutthroat",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "bloodrazor",
	faction = "bloodrazor",
	level = 34,
	chanceHit = 0.4,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3460,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,45,0,0,-1,0,0,-1,-1},
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
		"object/mobile/dressed_blood_razor_pirate_cutthroat_hum_f.iff",
		"object/mobile/dressed_blood_razor_pirate_cutthroat_hum_m.iff",
		"object/mobile/dressed_blood_razor_pirate_cutthroat_nikto_m.iff",
		"object/mobile/dressed_blood_razor_pirate_cutthroat_tran_m.iff",
		"object/mobile/dressed_blood_razor_pirate_cutthroat_wee_m.iff"
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

CreatureTemplates:addCreatureTemplate(blood_razor_cutthroat, "blood_razor_cutthroat")

teras_kasi_master = Creature:new {
	objectName = "@mob/creature_names:teras_kasi_master",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 21,
	chanceHit = 0.33,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1609,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {40,10,10,10,10,10,-1,-1,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_unarmed_trainer_01.iff",
				 "object/mobile/dressed_unarmed_trainer_02.iff",
				 "object/mobile/dressed_unarmed_trainer_03.iff"},
	lootGroups = {
		{
			groups = {
				{group = "townsperson_tier_1", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed_weapons",
	secondaryWeapon = "none",
	conversationTemplate = "",
	reactionStf = "@npc_reaction/townperson",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlermaster,tkamaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(teras_kasi_master, "teras_kasi_master")

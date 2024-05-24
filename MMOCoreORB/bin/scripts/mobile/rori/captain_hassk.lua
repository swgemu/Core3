captain_hassk = Creature:new {
	objectName = "@mob/creature_names:captain_hassk",
	socialGroup = "rorgungan",
	faction = "rorgungan",
	mobType = MOB_NPC,
	level = 73,
	chanceHit = 0.7,
	damageMin = 495,
	damageMax = 700,
	baseXp = 7023,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {80,0,0,0,20,0,35,0,-1},
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
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/captain_hassk.iff"},
	lootGroups = {
		{
			groups = {
				{group = "rorgungan_tier_3", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "captain_hassk_weapons",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlermaster,swordsmanmaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(captain_hassk, "captain_hassk")

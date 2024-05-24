slave = Creature:new {
	objectName = "@mob/creature_names:slave",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 4,
	chanceHit = 0.240000,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/twilek_female.iff",
				 "object/mobile/twilek_male.iff",
				 "object/mobile/human_male.iff",
				 "object/mobile/human_female.iff",
				 "object/mobile/wookiee_male.iff",
				 "object/mobile/wookiee_female.iff",
				 "object/mobile/rodian_male.iff",
				 "object/mobile/rodian_female.iff",
				 "object/mobile/trandoshan_male.iff",
				 "object/mobile/trandoshan_female.iff",
				 "object/mobile/bothan_male.iff",
				 "object/mobile/bothan_female.iff",},
	lootGroups = {
      	{
			groups = {
				{group = "townsperson_tier_1", chance = 10000000}
			}
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	reactionStf = "@npc_reaction/townperson",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = brawlernovice,
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(slave, "slave")

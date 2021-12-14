brackaset_male = Creature:new {
	objectName = "@mob/creature_names:brackaset_male",
	socialGroup = "brackaset",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 30,
	chanceHit = 0.39,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3005,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {130,130,120,20,20,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 91,
	boneType = "bone_mammal",
	boneAmount = 81,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/brackaset_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/brackaset_hue.iff",
	scale = 1.1,
	lootGroups = {
		 {
	        groups = {
				{group = "brackaset_common", chance = 10000000}
			},
			lootChance = 1600000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"",""}, {"posturedownattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(brackaset_male, "brackaset_male")

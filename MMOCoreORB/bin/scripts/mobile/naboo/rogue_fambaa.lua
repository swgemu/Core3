rogue_fambaa = Creature:new {
	objectName = "@mob/creature_names:rogue_fambaa",
	socialGroup = "self",
	faction = "",
	mobType = MOB_HERBIVORE,
	level = 37,
	chanceHit = 0.42,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3551,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {25,25,25,25,160,160,-1,25,-1},
	meatType = "meat_reptilian",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 700,
	boneType = "bone_mammal",
	boneAmount = 675,
	milkType = "milk_wild",
	milk = 400,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/fambaa_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 1.1,
	lootGroups = {
	 {
	        groups = {
				{group = "fambaa_common", chance = 10000000}
			},
			lootChance = 1740000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "unarmed",
	secondaryWeapon = "none",
	conversationTemplate = "",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"posturedownattack",""} },
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(rogue_fambaa, "rogue_fambaa")

voritor_dasher = Creature:new {
	objectName = "@mob/creature_names:voritor_dasher",
	socialGroup = "voritor",
	faction = "",
	mobType = MOB_CARNIVORE,
	level = 30,
	chanceHit = 0.39,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3005,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {20,-1,20,-1,-1,-1,-1,20,-1},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_leathery",
	hideAmount = 30,
	boneType = "bone_avian",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/voritor_dasher.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 1.05,
	lootGroups = {
		{
			groups = {
				{group = "voritor_lizard_common", chance = 10000000}
			},
			lootChance = 1600000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "object/weapon/ranged/creature/creature_spit_small_red.iff",
	secondaryWeapon = "unarmed",
	conversationTemplate = "",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = { {"dizzyattack",""}, {"creatureareapoison",""} },
	secondaryAttacks = { {"dizzyattack",""}, {"creatureareapoison",""} }
}

CreatureTemplates:addCreatureTemplate(voritor_dasher, "voritor_dasher")

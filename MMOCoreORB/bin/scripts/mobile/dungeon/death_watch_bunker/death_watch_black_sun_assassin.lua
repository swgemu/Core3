death_watch_black_sun_assassin = Creature:new {
	objectName = "@mob/creature_names:mand_bunker_blksun_assassin",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	mobType = MOB_NPC,
	socialGroup = "death_watch",
	faction = "",
	level = 107,
	chanceHit = 1.75,
	damageMin = 670,
	damageMax = 1050,
	baseXp = 10081,
	baseHAM = 40000,
	baseHAMmax = 40000,
	armor = 2,
	resists = {55,55,70,45,75,80,55,45,-1},
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
	creatureBitmask = KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,
	scale = 1.15,

	templates = {"object/mobile/dressed_black_sun_assassin.iff"},
	lootGroups = {
		{
			groups = {
				{group = "death_watch_bunker_commoners", chance = 10000000},
			},
			lootChance = 1000000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "deathwatch_ranged",
	secondaryWeapon = "none",
	conversationTemplate = "",
	thrownWeapon = "thrown_weapons",

	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(bountyhuntermaster,marksmanmaster,carbineermaster),
	secondaryAttacks = {},
}

CreatureTemplates:addCreatureTemplate(death_watch_black_sun_assassin, "death_watch_black_sun_assassin")

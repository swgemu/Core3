death_watch_black_sun_thug = Creature:new {
	objectName = "@mob/creature_names:mand_bunker_blksun_thug",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 86,
	chanceHit = 0.85,
	damageMin = 570,
	damageMax = 850,
	baseXp = 8130,
	baseHAM = 15000,
	baseHAMmax = 15000,
	armor = 1,
	resists = {40,40,60,35,55,70,35,40,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,
	lootChance = 1000000,

	templates = {"object/mobile/dressed_black_sun_thug.iff"},
	lootgroups = {
		{group = "death_watch_bunker_commoners", chance = 9000000},
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(death_watch_black_sun_thug, "death_watch_black_sun_thug")
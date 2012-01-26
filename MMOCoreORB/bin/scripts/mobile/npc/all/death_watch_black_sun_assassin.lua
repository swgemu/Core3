death_watch_black_sun_assassin = Creature:new {
	objectName = "@mob/creature_names:mand_bunker_blksun_assassin",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_black_sun_assassin.iff"},
	lootgroups = {},--slim chance for bh armor drop
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(death_watch_black_sun_assassin, "death_watch_black_sun_assassin")
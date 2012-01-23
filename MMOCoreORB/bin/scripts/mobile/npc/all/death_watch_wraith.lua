death_watch_wraith = Creature:new {
	objectName = "@mob/creature_names:mand_bunker_dthwatch_silver",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 178,
	chanceHit = 12.25,
	damageMin = 1020,
	damageMax = 1750,
	baseXp = 16794,
	baseHAM = 120000,
	baseHAMmax = 120000,
	armor = 2,
	resists = {75,75,90,80,45,45,100,70,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_death_watch_silver.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(death_watch_wraith, "death_watch_wraith")
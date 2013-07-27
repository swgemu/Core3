event_death_watch_bloodguard = Creature:new {
	objectName = "@mob/creature_names:mand_bunker_dthwatch_red",
	customName = "Death Watch Bloodguard (event)",
	socialGroup = "death_watch",
	pvpFaction = "death_watch",
	faction = "",
	level = 121,
	chanceHit = 40,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 0,
	baseHAM = 50000,
	baseHAMmax = 50000,
	armor = 2,
	resists = {55,55,70,60,30,30,100,40,-1},
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

	templates = {"object/mobile/dressed_death_watch_red.iff"},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
		{"defaultattack", ""},
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(event_death_watch_bloodguard, "event_death_watch_bloodguard")

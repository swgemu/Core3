quenker_relic_reaper = Creature:new {
	objectName = "@mob/creature_names:quenker_relic_reaper",
	socialGroup = "quenker",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 380,
	damageMax = 470,
	baseXp = 4370,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {55,55,30,30,-1,30,30,30,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/quenker_relic_reaper.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(quenker_relic_reaper, "quenker_relic_reaper")
quenker_relic_reaper = Creature:new {
	objectName = "@mob/creature_names:quenker_relic_reaper",
	socialGroup = "quenker",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 380,
	damageMax = 470,
	baseXp = 4370,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {155,155,30,30,-1,30,30,30,-1},
	meatType = "meat_wild",
	meatAmount = 35,
	hideType = "hide_scaley",
	hideAmount = 35,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/quenker_relic_reaper.iff"},
	scale = 1.25,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(quenker_relic_reaper, "quenker_relic_reaper")

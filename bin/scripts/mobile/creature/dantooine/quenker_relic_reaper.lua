quenker_relic_reaper = Creature:new {
	objectName = "@mob/creature_names:quenker_relic_reaper",
	socialGroup = "Quenker",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.440000,
	damageMin = 380,
	damageMax = 470,
	baseXp = 4370,
	baseHAM = 10300,
	baseHAMmax = 10300,
	armor = 0,
	resists = {55,55,0,0,-1,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/quenker_relic_reaper.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(quenker_relic_reaper, "quenker_relic_reaper")
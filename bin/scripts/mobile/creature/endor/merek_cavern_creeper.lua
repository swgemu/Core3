merek_cavern_creeper = Creature:new {
	objectName = "@mob/creature_names:merek_cavern_creeper",
	socialGroup = "Merek",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3915,
	baseHAM = 10300,
	baseHAMmax = 10300,
	armor = 0,
	resists = {40,0,0,0,-1,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/merek.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"blindattack","blindChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(merek_cavern_creeper, "merek_cavern_creeper")
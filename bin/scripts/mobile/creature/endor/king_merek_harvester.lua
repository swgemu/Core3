king_merek_harvester = Creature:new {
	objectName = "@mob/creature_names:king_merek_harvester",
	socialGroup = "Merek",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4916,
	baseHAM = 11500,
	baseHAMmax = 11500,
	armor = 0,
	resists = {60,-1,0,100,50,0,50,0,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 50,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/king_merek_harvester.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"creatureareapoison",""},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(king_merek_harvester, "king_merek_harvester")
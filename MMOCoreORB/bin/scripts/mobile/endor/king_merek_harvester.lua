king_merek_harvester = Creature:new {
	objectName = "@mob/creature_names:king_merek_harvester",
	socialGroup = "merek",
	faction = "",
	level = 50,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4916,
	baseHAM = 10000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {160,-1,5,200,150,5,150,5,-1},
	meatType = "meat_wild",
	meatAmount = 65,
	hideType = "hide_leathery",
	hideAmount = 50,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/king_merek_harvester.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 1.1,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"creatureareapoison",""},
		{"blindattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(king_merek_harvester, "king_merek_harvester")

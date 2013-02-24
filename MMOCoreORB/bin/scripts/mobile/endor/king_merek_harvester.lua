king_merek_harvester = Creature:new {
	objectName = "@mob/creature_names:king_merek_harvester",
	socialGroup = "merek",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4916,
	baseHAM = 10000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {60,-1,5,100,50,5,50,5,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/king_merek_harvester.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"creatureareapoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(king_merek_harvester, "king_merek_harvester")

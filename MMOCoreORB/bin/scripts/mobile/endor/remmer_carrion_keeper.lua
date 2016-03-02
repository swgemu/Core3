remmer_carrion_keeper = Creature:new {
	objectName = "@mob/creature_names:remmer_carrion_keeper",
	socialGroup = "remmer",
	faction = "",
	level = 24,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2443,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {130,10,140,-1,-1,-1,150,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 30,
	hideType = "hide_bristley",
	hideAmount = 15,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/remmer_hue.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""},
		{"blindattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(remmer_carrion_keeper, "remmer_carrion_keeper")

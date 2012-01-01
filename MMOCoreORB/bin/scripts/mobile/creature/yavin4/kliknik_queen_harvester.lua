kliknik_queen_harvester = Creature:new {
	objectName = "@mob/creature_names:kliknik_queen_harvester",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.37,
	damageMin = 270,
	damageMax = 280,
	baseXp = 3005,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {40,40,-1,15,15,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"mildpoison",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_queen_harvester, "kliknik_queen_harvester")
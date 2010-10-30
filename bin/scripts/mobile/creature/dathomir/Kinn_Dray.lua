Kinn_Dray = Creature:new {
	objectName = "Kinn`Dray",
	socialGroup = "Gap. Recluse",
	pvpFaction = "",
	faction = "",
	level = 126,
	chanceHit = 4.750000,
	damageMin = 830,
	damageMax = 1370,
	baseXp = 11953,
	baseHAM = 45500,
	baseHAMmax = 45500,
	armor = 0,
	resists = {55,55,35,30,30,30,0,30,-1},
	meatType = "meat_insect",
	meatAmount = 11,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_recluse_giant_kiin_dray.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(Kinn_Dray, "Kinn_Dray")
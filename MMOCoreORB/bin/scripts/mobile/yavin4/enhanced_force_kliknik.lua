enhanced_force_kliknik = Creature:new {
	objectName = "",
	customName = "Force Kliknik",
	socialGroup = "geonosian_creature",
	pvpFaction = "geonosian_creature",
	faction = "",
	level = 109,
	chanceHit = 2.2,
	damageMin = 675,
	damageMax = 1060,
	baseXp = 10360,
	baseHAM = 27000,
	baseHAMmax = 33000,
	armor = 2,
	resists = {35,35,-1,95,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 45,
	hideType = "hide_scaley",
	hideAmount = 40,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 15,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_force_kliknik, "enhanced_force_kliknik")
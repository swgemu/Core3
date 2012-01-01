enhanced_kliknik = Creature:new {
	objectName = "@mob/creature_names:enhanced_kliknik",
	socialGroup = "Geon. Monster",
	pvpFaction = "",
	faction = "",
	level = 109,
	chanceHit = 2.2,
	damageMin = 675,
	damageMax = 1060,
	baseXp = 10360,
	baseHAM = 22000,
	baseHAMmax = 27000,
	armor = 2,
	resists = {40,40,10,95,-1,10,10,10,-1},
	meatType = "meat_carnivore",
	meatAmount = 45,
	hideType = "",
	hideAmount = 40,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 15,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_kliknik, "enhanced_kliknik")
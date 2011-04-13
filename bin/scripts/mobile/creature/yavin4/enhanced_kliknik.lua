enhanced_kliknik = Creature:new {
	objectName = "@mob/creature_names:geonosian_kliknik_force_strong",
	socialGroup = "Geon. Monster",
	pvpFaction = "",
	faction = "",
	level = 109,
	chanceHit = 2.200000,
	damageMin = 675,
	damageMax = 1060,
	baseXp = 10360,
	baseHAM = 38000,
	baseHAMmax = 38000,
	armor = 0,
	resists = {40,40,0,95,-1,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 45,
	hideType = "",
	hideAmount = 40,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"stunattack","stunChance=50"},
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_kliknik, "enhanced_kliknik")
enhanced_kliknik = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:geonosian_kliknik_force_strong",
	socialGroup = "Geon. Monster",
	pvpFaction = "",
	faction = "",
	level = 109,
	chanceHit = 2.200000,
	damageMin = 675,
	damageMax = 1060,
	range = 25,
	baseXp = 10360,
	baseHAM = 38000,
	armor = 0,
	resists = {40,40,0,95,-1,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 45,
	hideType = "hide_scale",
	hideAmount = 40,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_kliknik, "enhanced_kliknik")

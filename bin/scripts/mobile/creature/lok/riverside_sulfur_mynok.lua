riverside_sulfur_mynok = Creature:new {
	objectName = "@mob/creature_names:riverside_sulfur_mynock",
	socialGroup = "Mynock",
	pvpFaction = "",
	faction = "",
	level = 33,
	chanceHit = 0.400000,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3370,
	baseHAM = 9550,
	baseHAMmax = 9550,
	armor = 0,
	resists = {-1,35,0,65,-1,0,65,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 60,
	hideType = "hide_leathery",
	hideAmount = 78,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/riverside_sulfur_mynock.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(riverside_sulfur_mynok, "riverside_sulfur_mynok")
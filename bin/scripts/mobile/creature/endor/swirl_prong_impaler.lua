swirl_prong_impaler = Creature:new {
	objectName = "@mob/creature_names:swirl_prong_impaler",
	socialGroup = "Swirl Prong",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.370000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 3005,
	baseHAM = 9100,
	baseHAMmax = 9100,
	armor = 0,
	resists = {35,30,0,50,50,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/swirl_prong.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(swirl_prong_impaler, "swirl_prong_impaler")
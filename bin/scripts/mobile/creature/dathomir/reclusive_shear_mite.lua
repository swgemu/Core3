reclusive_shear_mite = Creature:new {
	objectName = "@mob/creature_names:reclusive_shear_mite",
	socialGroup = "Shearmite",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.350000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2637,
	baseHAM = 6000,
	baseHAMmax = 6000,
	armor = 0,
	resists = {30,35,-1,60,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 12,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/shear_mite.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(reclusive_shear_mite, "reclusive_shear_mite")
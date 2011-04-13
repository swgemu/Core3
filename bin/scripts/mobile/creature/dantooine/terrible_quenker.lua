terrible_quenker = Creature:new {
	objectName = "@mob/creature_names:quenker_terrible",
	socialGroup = "Quenker",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.380000,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3005,
	baseHAM = 9100,
	baseHAMmax = 9100,
	armor = 0,
	resists = {30,30,0,0,-1,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/quenker.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_green"},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(terrible_quenker, "terrible_quenker")
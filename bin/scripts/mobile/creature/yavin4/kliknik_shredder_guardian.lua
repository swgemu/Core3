kliknik_shredder_guardian = Creature:new {
	objectName = "@mob/creature_names:kliknik_shredder_guardian",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3097,
	baseHAM = 9000,
	baseHAMmax = 9000,
	armor = 0,
	resists = {40,0,0,0,0,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_shredder_guardian, "kliknik_shredder_guardian")
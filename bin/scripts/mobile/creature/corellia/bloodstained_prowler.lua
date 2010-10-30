bloodstained_prowler = Creature:new {
	objectName = "@mob/creature_names:wrix_bloodstained_prowler",
	socialGroup = "Wrix",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 3005,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {35,30,0,50,0,35,-1,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 70,
	hideType = "hide_bristley",
	hideAmount = 40,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/tusk_cat.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bloodstained_prowler, "bloodstained_prowler")
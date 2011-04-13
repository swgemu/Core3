stintaril_prowler = Creature:new {
	objectName = "@mob/creature_names:stintaril_prowler",
	socialGroup = "Stinaril",
	pvpFaction = "",
	faction = "",
	level = 83,
	chanceHit = 0.850000,
	damageMin = 595,
	damageMax = 900,
	baseXp = 7945,
	baseHAM = 13500,
	baseHAMmax = 13500,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 9,
	hideType = "hide_bristley",
	hideAmount = 7,
	boneType = "bone_mammal",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/stintaril.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stintaril_prowler, "stintaril_prowler")
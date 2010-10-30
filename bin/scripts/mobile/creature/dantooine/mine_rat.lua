mine_rat = Creature:new {
	objectName = "@mob/creature_names:death_watch_quenker",
	socialGroup = "Death Watch",
	pvpFaction = "",
	faction = "",
	level = 102,
	chanceHit = 1.000000,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9708,
	baseHAM = 27000,
	baseHAMmax = 27000,
	armor = 0,
	resists = {55,55,80,35,35,35,100,35,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/womp_rat.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mine_rat, "mine_rat")
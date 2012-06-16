mine_rat = Creature:new {
	objectName = "@mob/creature_names:death_watch_quenker",
	socialGroup = "quenker",
	pvpFaction = "",
	faction = "",
	level = 102,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9708,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {55,55,80,35,35,35,100,35,-1},
	meatType = "meat_wild",
	meatAmount = 2,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/quenker.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mine_rat, "mine_rat")
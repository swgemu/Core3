corellian_butterfly_defender = Creature:new {
	objectName = "@mob/creature_names:corellian_butterfly_defender",
	socialGroup = "Cor. Butterfly",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1257,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {5,15,-1,-1,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 16,
	hideType = "hide_scaley",
	hideAmount = 16,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_butterfly_defender.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(corellian_butterfly_defender, "corellian_butterfly_defender")
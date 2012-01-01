bark_mite_burrower_collector = Creature:new {
	objectName = "@mob/creature_names:bark_mite_burrower_collector",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 36,
	chanceHit = 0.4,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3551,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {20,40,-1,70,-1,65,70,20,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.2,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_collector, "bark_mite_burrower_collector")
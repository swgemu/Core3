event_reclusive_gurk_king = Creature:new {
	objectName = "@mob/creature_names:recluse_gurk_king",
	customName = "a reclusive gurk king (event)",
	socialGroup = "gurk",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.47,
	damageMin = 370,
	damageMax = 450,
	baseXp = 0,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {40,20,40,-1,40,40,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/recluse_gurk_king.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(event_reclusive_gurk_king, "event_reclusive_gurk_king")

wood_mite_royal_guard = Creature:new {
	objectName = "@mob/creature_names:wood_mite_royal_guard",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {25,20,-1,-1,5,5,5,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/confused_wood_mite_hatchling.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(wood_mite_royal_guard, "wood_mite_royal_guard")
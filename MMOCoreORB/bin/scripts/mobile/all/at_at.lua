at_at = Creature:new {
	objectName = "@mob/creature_names:at_at",
	socialGroup = "Imperial",
	pvpFaction = "",
	faction = "",
	level = 228,
	chanceHit = 0,
	damageMin = 1270,
	damageMax = 2250,
	baseXp = 21728,
	baseHAM = 0,
	baseHAMmax = 0,
	armor = 3,
	resists = {90,90,10,90,90,90,90,100,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 0,
	diet = NONE,

	templates = {"object/mobile/atat.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(at_at, "at_at")
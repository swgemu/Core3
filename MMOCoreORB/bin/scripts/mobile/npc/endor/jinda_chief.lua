jinda_chief = Creature:new {
	objectName = "@mob/creature_names:jinda_chief",
	socialGroup = "Jinda Tribe",
	pvpFaction = "Jinda Tribe",
	faction = "",
	level = 51,
	chanceHit = 0.55,
	damageMin = 420,
	damageMax = 550,
	baseXp = 5007,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {-1,50,-1,0,0,70,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/jinda_male_01.iff"},
	lootgroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(jinda_chief, "jinda_chief")
enraged_korga = Creature:new {
	objectName = "@mob/creature_names:enraged_korga",
	socialGroup = "korga_tribe",
	pvpFaction = "korga_tribe",
	faction = "korga_tribe",
	level = 32,
	chanceHit = 0.39,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3279,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {20,20,20,100,100,-1,20,-1,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(enraged_korga, "enraged_korga")
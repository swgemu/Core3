kunga_rockshaper = Creature:new {
	objectName = "@mob/creature_names:kunga_rockshaper",
	socialGroup = "Kunga Tribe",
	pvpFaction = "Kunga Tribe",
	faction = "",
	level = 71,
	chanceHit = 0.65,
	damageMin = 470,
	damageMax = 650,
	baseXp = 6747,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {100,20,100,20,20,100,20,-1,-1},
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
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dantari_male.iff"},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(kunga_rockshaper, "kunga_rockshaper")
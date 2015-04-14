crackdown_sand_trooper_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_sand_trooper_hard",
	randomNameType = NAME_STORMTROOPER_TAG,
	socialGroup = "imperial",
	faction = "imperial",
	level = 160,
	chanceHit = 0.53,
	damageMin = 370,
	damageMax = 420,
	baseXp = 4302,
	baseHAM = 100000,
	baseHAMmax = 130000,
	armor = 0,
	resists = {0,0,40,100,-1,-1,-1,-1,-1},
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

	templates = {"object/mobile/dressed_stormtrooper_sand_trooper_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6550000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "stormtrooper_common", chance = 100000},
				{group = "wearables_rare", chance = 1000000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"sandtrooper_weapons"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_sand_trooper_hard, "crackdown_sand_trooper_hard")
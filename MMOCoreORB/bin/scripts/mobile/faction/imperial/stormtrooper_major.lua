stormtrooper_major = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_major",
	randomNameType = NAME_STORMTROOPER_TAG,
	socialGroup = "imperial",
	faction = "imperial",
	level = 32,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3279,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {0,0,0,-1,30,-1,30,-1,-1},
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_major_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 5050000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 250000},
				{group = "armor_attachments", chance = 250000},
				{group = "imperial_officer_common", chance = 450000},
				{group = "stormtrooper_common", chance = 700000},
				{group = "wearables_common", chance = 500000},
				{group = "wearables_uncommon", chance = 500000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "imperialRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/stormtrooper",
	attacks = merge(riflemanmaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(stormtrooper_major, "stormtrooper_major")

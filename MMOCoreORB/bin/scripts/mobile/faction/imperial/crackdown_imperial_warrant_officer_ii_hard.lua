crackdown_imperial_warrant_officer_ii_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_warrant_officer_ii_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 58,
	chanceHit = 0.52,
	damageMin = 470,
	damageMax = 580,
	baseXp = 5645,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_officer_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7650000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"imperial_weapons_medium"},
	conversationTemplate = "imperialRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	attacks = merge(riflemanmid,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_imperial_warrant_officer_ii_hard, "crackdown_imperial_warrant_officer_ii_hard")

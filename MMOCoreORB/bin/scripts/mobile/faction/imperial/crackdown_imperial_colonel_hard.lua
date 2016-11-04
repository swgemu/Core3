crackdown_imperial_colonel_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_colonel_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 63,
	chanceHit = 0.65,
	damageMin = 420,
	damageMax = 630,
	baseXp = 6445,
	baseHAM = 12300,
	baseHAMmax = 17700,
	armor = 1,
	resists = {115,115,10,10,10,-1,10,-1,-1},
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

	templates = {"object/mobile/dressed_imperial_colonel_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7200000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "imperial_officer_common", chance = 450000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "imperialRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(riflemanmaster,carbineermaster,pikemanmaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_imperial_colonel_hard, "crackdown_imperial_colonel_hard")

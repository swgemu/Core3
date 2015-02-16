ruwan_warrant_officer = Creature:new {
  objectName = "@mob/creature_names:imperial_warrant_officer_ii",
  socialGroup = "imperial",
  faction = "imperial",
  level = 18,
  chanceHit = 0.32,
  damageMin = 170,
  damageMax = 180,
  baseXp = 1426,
  baseHAM = 4100,
  baseHAMmax = 5000,
  armor = 0,
  resists = {5,5,5,5,5,5,5,-1,-1},
  meatType = "",
  meatAmount = 0,
  hideType = "",
  hideAmount = 0,
  boneType = "",
  boneAmount = 0,
  milk = 0,
  tamingChance = 0,
  ferocity = 0,
  pvpBitmask = NONE,
  creatureBitmask = NONE,
  optionsBitmask = 136,
  diet = HERBIVORE,

  templates = {
    "object/mobile/dressed_imperial_officer_f.iff",
    "object/mobile/dressed_imperial_officer_m.iff",
    "object/mobile/dressed_imperial_officer_m_2.iff",
    "object/mobile/dressed_imperial_officer_m_3.iff",
    "object/mobile/dressed_imperial_officer_m_4.iff",
    "object/mobile/dressed_imperial_officer_m_5.iff",
    "object/mobile/dressed_imperial_officer_m_6.iff"},
  lootGroups = {
    {
      groups = {
        {group = "color_crystals", chance = 100000},
        {group = "junk", chance = 6650000},
        {group = "rifles", chance = 550000},
        {group = "pistols", chance = 550000},
                {group = "melee_weapons", chance = 550000},
                {group = "carbines", chance = 550000},
        {group = "clothing_attachments", chance = 25000},
        {group = "armor_attachments", chance = 25000},
        {group = "wearables_common", chance = 1000000}
      },
      lootChance = 2800000
    }           
  },
  weapons = {"imperial_weapons_medium"},
  conversationTemplate = "ruwan_tokai_mission_target_convotemplate",
  attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(ruwan_warrant_officer, "ruwan_warrant_officer")

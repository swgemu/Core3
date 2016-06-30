theme_park_imperial_staff_corporal = Creature:new {
  objectName = "@mob/creature_names:imperial_staff_corporal",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  socialGroup = "imperial",
  faction = "imperial",
  level = 17,
  chanceHit = 0.32,
  damageMin = 160,
  damageMax = 170,
  baseXp = 112,
  baseHAM = 3500,
  baseHAMmax = 4300,
  armor = 0,
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
  creatureBitmask = PACK,
  optionsBitmask = AIENABLED + CONVERSABLE + INTERESTING,
  diet = HERBIVORE,

  templates = {"object/mobile/dressed_imperial_soldier_m.iff"},
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
      }
    }
  },
  weapons = {},
  conversationTemplate = "theme_park_nightsister_mission_target_convotemplate",
  attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(theme_park_imperial_staff_corporal, "theme_park_imperial_staff_corporal")
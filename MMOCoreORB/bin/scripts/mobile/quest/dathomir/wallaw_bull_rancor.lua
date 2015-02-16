wallaw_bull_rancor = Creature:new {
  objectName = "@mob/creature_names:bull_rancor",
  socialGroup = "rancor",
  faction = "",
  level = 65,
  chanceHit = 0.6,
  damageMin = 455,
  damageMax = 620,
  baseXp = 6288,
  baseHAM = 11000,
  baseHAMmax = 14000,
  armor = 1,
  resists = {35,60,15,80,80,80,15,15,-1},
  meatType = "meat_carnivore",
  meatAmount = 1000,
  hideType = "hide_leathery",
  hideAmount = 900,
  boneType = "bone_mammal",
  boneAmount = 850,
  milk = 0,
  tamingChance = 0.01,
  ferocity = 11,
  pvpBitmask = NONE,
  creatureBitmask = NONE,
  optionsBitmask = 136,
  diet = CARNIVORE,

  templates = {"object/mobile/bull_rancor.iff"},
  controlDeviceTemplate = "object/intangible/pet/rancor_hue.iff",
  lootGroups = {
    {
      groups = {
        {group = "rancor_common", chance = 4000000},
        {group = "pistols", chance = 750000},
        {group = "heavy_weapons", chance = 500000},
        {group = "rifles", chance = 750000},
        {group = "carbines", chance = 500000},
        {group = "grenades_looted", chance = 500000},
        {group = "armor_all", chance = 1000000},
        {group = "melee_unarmed", chance = 1000000},
        {group = "wearables_common", chance = 500000},
        {group = "wearables_uncommon", chance = 500000}
      },
      lootChance = 2600000
    }
  },
  weapons = {},
  conversationTemplate = "wallaw_loowobbli_mission_target_convotemplate",
  attacks = {
    {"creatureareadisease",""},
    {"dizzyattack","dizzyChance=50"}
  }
}

CreatureTemplates:addCreatureTemplate(wallaw_bull_rancor, "wallaw_bull_rancor")

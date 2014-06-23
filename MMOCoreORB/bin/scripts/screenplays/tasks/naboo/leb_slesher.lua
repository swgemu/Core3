leb_slesher_missions =
  {
    {
      missionType = "retrieve",
      primarySpawns =
      {
        { npcTemplate = "leb_merchant", planetName = "naboo", npcName = "Phinta Lianovi" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/leb_slesher_q1_needed.iff", itemName = "\"Processing Fee\"" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 25 },
      }
    },
    {
      missionType = "retrieve",
      primarySpawns =
      {
        { npcTemplate = "leb_merchant", planetName = "naboo", npcName = "Cornevero Dawlton" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/leb_slesher_q2_needed.iff", itemName = "\"Remediation Fee\"" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    },
  }

npcMapLebSlesher =
  {
    {
      spawnData = { planetName = "naboo", npcTemplate = "leb_slesher", x = 3.1, z = 0.9, y = 5.7, direction = 166, cellID = 64, position = STAND },
      worldPosition = { x = 4973, y = 6709 },
      npcNumber = 1,
      stfFile = "@static_npc/naboo/leb_slesher",
      missions = leb_slesher_missions
    }
  }

LebSlesher = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapLebSlesher,
  className = "LebSlesher",
  screenPlayState = "leb_slesher_quest",
  distance = 600
}

registerScreenPlay("LebSlesher", true)

leb_slesher_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = LebSlesher
}
leb_slesher_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = LebSlesher
}
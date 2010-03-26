
object_weapon_melee_unarmed_unarmed_default_player = object_weapon_melee_unarmed_shared_unarmed_default_player:new {

	attackType = MELEEATTACK,
	damageType = KINETIC,
	
	certificationsRequired = {  },
	
	creatureAccuracyModifiers = { "unarmed_accuracy" },
	defenderDefenseModifiers = { "melee_defense" },
	speedModifiers = { "unarmed_speed" },
	damageModifiers = { "unarmed_damage" }
	
}

ObjectTemplates:addTemplate(object_weapon_melee_unarmed_unarmed_default_player, "object/weapon/melee/unarmed/unarmed_default_player.iff")

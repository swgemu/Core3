CreatureRangedAttackCommand = {
	name = "creaturerangedattack",
	animation = "creature_attack_ranged", 
	animType = GENERATE_INTENSITY,
	damageMultiplier = 1,
	speedMultiplier = 1,
	combatSpam = "attack",
	poolsToDamage = RANDOM_ATTRIBUTE,
	trails = 255,
}

AddCommand(CreatureRangedAttackCommand)

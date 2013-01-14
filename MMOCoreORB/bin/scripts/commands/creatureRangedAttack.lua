CreatureRangedAttackCommand = {
    name = "creaturerangedattack",
	animationCRC = hashCode("creature_attack_ranged_medium"),
	damageMultiplier = 1,
	speedMultiplier = 1,
	combatSpam = "attack",
	poolsToDamage = RANDOM_ATTRIBUTE,
	trails = 255,
}

AddCommand(CreatureRangedAttackCommand)
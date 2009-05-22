tabageAttack1 = {
        attackname = "tabageAttack1",
        animation = "creature_attack_light",
        
        requiredWeaponType = NONE,

        range = 7,

        damageRatio = 1.2,

        speedRatio = 4,

        arearange = 7,
        accuracyBonus = 0,
                
        knockdownChance = 0,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 50,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(tabageAttack1)

---------------------------------------------------------------------------------------

tabageAttack2 = {
        attackname = "tabageAttack2",
        animation = "creature_attack_light",
        
        requiredWeaponType = NONE,

        range = 7,

        damageRatio = 1.2,

        speedRatio = 4,

        arearange = 7,
        accuracyBonus = 0,
                
        knockdownChance = 0,
        postureDownChance = 50,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 0,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(tabageAttack2)

---------------------------------------------------------------------------------------

tabageAttack3 = {
        attackname = "tabageAttack3",
        animation = "creature_attack_light",
        
        requiredWeaponType = NONE,

        range = 7,

        damageRatio = 1.2,

        speedRatio = 4,

        arearange = 7,
        accuracyBonus = 0,

        healthAttackChance = 100,
        actionAttackChance = 0,
        mindAttackChance = 0,

        dotChance = 50,
        tickStrengthOfHit = 1,

        fireStrength = 0,
        fireType = 0,

        bleedingStrength = 0,
		bleedingType = 0,

        poisonStrength = 100,
        poisonType = HEALTH,

        diseaseStrength = 0,
        diseaseType = 0,
                
        knockdownChance = 0,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 0,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddDotPoolAttackTargetSkill(tabageAttack3)

--------------------------------------------------------------------------------------

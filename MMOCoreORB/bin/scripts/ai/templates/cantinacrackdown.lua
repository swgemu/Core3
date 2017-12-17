cantinacrackdown = {
	{"root", "CompositeDefault", "none", SELECTORBEHAVIOR},
	{"attack", "CompositeDefault", "root", SEQUENCEBEHAVIOR},
	{"move", "CompositeDefault", "root", SEQUENCEBEHAVIOR},
	{"attack0", "GetTarget", "attack", BEHAVIOR},
	{"attack1", "SelectWeapon", "attack", BEHAVIOR},
	{"attack2", "SelectAttack", "attack", BEHAVIOR},
	{"attack3", "CombatMove", "attack", BEHAVIOR},
	{"move0", "WalkDefault", "move", BEHAVIOR},
	{"move1", "WaitDefault", "move", BEHAVIOR},
}

addAiTemplate("cantinacrackdown", cantinacrackdown)
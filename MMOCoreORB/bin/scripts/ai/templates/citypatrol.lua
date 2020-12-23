citypatrol = {
	{"idroot", "CompositeCityPatrol", "none", SEQUENCEBEHAVIOR},
	{"move0", "WalkCityPatrol", "idroot", BEHAVIOR},
	{"move1", "WaitCityPatrol", "idroot", BEHAVIOR},
}

addAiTemplate("citypatrol", citypatrol)

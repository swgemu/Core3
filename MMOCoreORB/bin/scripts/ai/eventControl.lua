idleEventcontrol = {
	{id="353070738",	name="Sequence",	pid="none"},
	{id="3863818570",	name="If",	pid="353070738"},
	{id="2164142352",	name="CheckHasPatrol",	pid="3863818570"},
	{id="3868733591",	name="If",	pid="353070738"},
	{id="725675163",	name="CheckDestination",	pid="3868733591",	args={condition=0.0}},
	{id="2811013882",	name="FindNextPosition",	pid="353070738"},
	{id="3440948677",	name="TreeSocket",	pid="353070738",	args={slot=MOVE}}}
addAiTemplate("idleEventcontrol", idleEventcontrol)


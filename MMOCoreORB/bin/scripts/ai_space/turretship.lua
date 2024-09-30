attackTurretship = {
	{id="1295149021",	name="SequenceSpace",	pid="none"},
	{id="1337075883",	name="IfSpace",	pid="1295149021"},
	{id="1839608236",	name="CheckRefireRate",	pid="1337075883",	args={condition=500}},
	{id="652020583",	name="IfSpace",	pid="1295149021"},
	{id="2624176723",	name="CheckWeapons",	pid="652020583"},
	{id="1070459205",	name="EngageTurrets",	pid="1295149021"}}
addAiTemplate("attackTurretship", attackTurretship)


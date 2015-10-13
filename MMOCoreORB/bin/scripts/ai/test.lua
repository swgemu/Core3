succeedTest = {
	{id="succeed", name="AlwaysSucceed", pid="none"},
	{id="dummy",   name="Dummy",		 pid="succeed"}
}
addAiTemplate("succeedTest", succeedTest)

failTest = {
	{id="fail",  name="AlwaysFail", pid="none"},
	{id="dummy", name="Dummy",		pid="fail"}
}
addAiTemplate("failTest", failTest)

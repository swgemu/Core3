# Linux

This is a simplified setup for developing and running a SWGEmu Core3 based server.

## Bootstrap

Launch a linux server (vm, cloud, bare metal) with Debian 11.

Setup a user (e.g., "swgemu"), login and launch a root shell (su -)

Run (in the root shell):
```
wget -O bootstrap.sh https://swgemu.com/getcore3/?p=2
```

Set `RUN_USER` environment variable to the username you will use to run the server:

```
export RUN_USER=swgemu
```

Then run the script:
```
./bootstrap.sh
```

Follow the prompts. See the main [README.md](../README.md) for more details.

When the script is done exit the root shell and loggout of the system.

When you log back in as the `RUN_USER` you'll have the environment ready to build the server.

To run the server you will need to copy the tre files from a client to the server in the /tre directory.

### Commands

`buid` - Compile the server
`run` - run the server


# Core3 REST API

## Overview

The Core3 REST API is based on [cpprestsdk](https://github.com/microsoft/cpprestsdk) and leverages a number of objects to provide API services for Core3.

## Configuration

The Core3 API requires an SSL cert, you can generate a self-signed certificate:

```
$ cd bin/conf
$ openssl genrsa -out ssl.key 2048
$ openssl req -new -key secrets/ssl.key -out ssl.csr -subj "/C=US/ST=NY/L=Somewhere/O=MyOrg/CN=Core3API"
$ openssl x509 -req -days 3650 -in ssl.csr -signkey secrets/ssl.key -out ssl.crt
$ rm -f ssl.csr
$ openssl x509 -text -noout -in ssl.crt
```

To enable Core3 REST API you need to configure it in config-local.lua, an example config is below:

```
Core3.RESTServerPort = 44443
Core3.RESTServer = {
	LogLevel = 4, -- -1 NONE, 0 FATAL, 1 ERROR, 2 WARNING, 3 LOG, 4 INFO, 5 DEBUG
	APIToken = "token",
	SSLKeyFile = "conf/ssl.key",
	SSLCertFile = "conf/ssl.crt",
}
```

Replace APIToken with a cryptographically secure token, a simple way to generate the token is:

```
openssl rand -base64 18
```

Changes to the configuration will take effect on the next server reload. You should a message like this in the console:

```
(17 s) [RESTServer] listening to port 44443
```

This means the server is enabled and listening on 44443.

## Testing

You can do a simple test of the API by calling the version endpoint:

```
curl -s -k -H "Authorization: Bearer {tokenhere}" "https://127.0.0.1:44443/v1/version"
```

The output should be a JSON object with the status of the request and some simple version info (first line of rev.txt etc.)

## API Endpoints

There are numerous endpoints, this documentation will most likely be out of date, use the source Luke. Each endpoint is described by a RESTEndpoint object (more on the objects below) created in RESTServer::registerEndpoints().

Here's an example endpoint as of the writing of this document:

```
RESTEndpoint("POST:/v1/admin/console/(\\w+)/", {"command"}, [this] (APIRequest apiRequest) -> void {
...
```

This declaration defines an endpoint "/v1/admin/console/..." which fires on a POST call, the first "word" is mapped to the path field "command" and is passed to the underlying defined code.

## Call flow

When a call comes in it is handled by RESTServer::routeRequest() which then calls isMatch() on all the RESTEndpoint objects that have been created in RESTServer::registerEndpoints() and chooses the one which returns the highest weight. As of this writing the RESTEndpoint returns the length of the regex as its weight with the idea that the longest match should be the most specific endpoint.

Once the router finds the RESTEndpoint it creates an APIRequest object and calls the RESTEndpoint::handle() function with the APIRequest object.

The RESTEndpoint::handle() function then parses the path fields into the apiRequest and passes control to the handler defined when the RESTEndpoint was declared. At this point the function runs the API endpoint logic and calls apiRequest.fail() or apiRequest.success() with the results of the call.

The results of the call are passed back to the pplx context via http_request::reply() and the cpprestsdk library handles returning the results back to the client.

The call graph looks something like this:

```
RESTServer
 |
 +-- RESTServer::routeRequest
      |
      +-- RESTEndpoint::handle
           |
           +-- APIRequest::success or APIRequest::fail
```

If the call is against an endpoint using a game proxy the endpoint will call APIProxy{ObjectName} as defined in the server/web namespace (more below).

## REST API Objects

### Overview

As of the writing of this document all the REST API Objects are declared in the MMOCoreORB/src/server/web directory with the general design principle that API server logic and game logic should be separated as much as reasonable and game related calls should base their pattern on the BaseAPIProxy class. It's **VERY** important that any game logic interface run in the engine context, to that end the current implementation spawns a Core task before calling the underlying handler. In the handler it's expected that all the usual game logic conventions should be used to protect the game environment (e.g. References, locks etc.) and that this code will **NOT** call cpprestsdk specific objects. At some point in the future the underlying API server may be replaced and the proxy objects should be isolated enough that this change will be trivial. If you find yourself in need of something deeper in the API server, declare it on the APIRequest class and keep the isolation clean.

### RESTServer

This is the actual server itself, it's created and managed by ServerCore and the class interface is simple to avoid pollution between cppresksdk and the game codebase. Inside this object is the registerEndpoints() function which creates each of the RESTEndpoint objects and stores them for later routing. If you're looking to add new endpoints define them in RESTServer.cpp and please avoid adding too much to the class definition to keep the interface clean.

### RESTEndpoint

This is the definition of an API endpoint, as mentioned above the declaration includes a "endpoint key regex" which defines this endpoint's interest in a URI, the path fields it will expose once the URI is parsed and a function to handle the logic of an API request.

### APIRequest

Each API request is transformed into an APIRequest object, this object encapsulates the transaction of a single call / response cycle. The APIRequest object provides methods to handle parsed request data and respond back to the caller.

There are three major data sources defined by the APIRequest:

#### Path Fields

In the declaration of a RESTEndpoint the endpoint declares a number of "path fields" these are parsed out (typically by regex) from the URI and saved on the API request by the RESTEndpoint object before passing to the handler. The goal with these fields is to provide easy access to pre-parsed metadata about the URI without having to know a lot about the request URI itself. There are numerous examples of these in the code base, again, use the source Luke.

#### Query Fields

The URI will often include Query parameters, those are parsed out and provided to the handler through the APIRequest methods for ease of use while processing the hander logic.

#### Request JSON

Endpoints might consume a JSON body (e.g. PUT/POST calls) and this data is parsed (at request of the handler) into a JSON object that can be used by the handler logic to complete the transaction.

#### Example Call

Here is an example call and the resulting APIRequest components:

```
POST URI    : /v1/admin/console/shutdown?args=10 BODY: {"galaxyID"=123}
Endpoint Key: POST:/v1/admin/console/shutdown

APIRequest members:
 mEndpointKey: RESTEndpoint("POST:/v1/admin/console/(\\w+)", {"command"},...
 mPathFields : {"command"="shutdown"}
 mQueryFields: {"args"="10"}
 mRequestJSON: {"galaxyID"="123"}
```

These can be accessed through the various methods in APIRequest:

```
String command = requestData["command"].get<std::string>();

uint32_t galaxyID = apiRequest.getPathFieldUnsignedLong("galaxyID", false, 0ull);
```

### BaseAPIProxy

The is the skeleton of a game proxy object, the intent is to isolate game calls into well defined proxy points where game objects can be handled in a safe manner and the implementation of the API server is not exposed.

### APIProxyPlayerManager

This is an example implementation of a game proxy, it uses the PlayerManager to proxy calls to URI's at the ../admin/account/.. endpoints. The role of this object is to handle all calls in/out of PlayerManager and focus on execution of the transaction requested by the API user within the game context. The interface to the API client is through the APIRequest object (described above) and game specific objects can be used here. Proxy objects are executed in the engine thread context and should **NOT** utilize any cpprestsdk or RESTServer related objects. 

## Summary

The Core3 REST API subsystem is designed to provide flexibility while protecting the game from corruption, allowing for easy extension and future refactoring of the underlying API gateway. Please keep in mind that all of this is exposing your game server to malicious users and could be hacked, keep security in mind, use a good API token, a real ssl cert if you can afford it, avoid exposing the port directly to the internet (i.e. keep it local or on private IP's) and beware that whatever new code you write will be abused.

And most of all, when in doubt: Use the **Source** Luke.

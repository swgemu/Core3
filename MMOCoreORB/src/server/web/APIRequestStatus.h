/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIRequestStatus.h
 * @created     : Mon Jan  6 22:00:06 UTC 2020
 */

#pragma once

namespace server {
 namespace web3 {
	// Inspired by /usr/include/cpprest/http_msg.h status_code class
	typedef unsigned short APIRequestStatusValue;

	class APIRequestStatus {
	public:
		const static APIRequestStatusValue Continue = 100;
		const static APIRequestStatusValue SwitchingProtocols = 101;
		const static APIRequestStatusValue OK = 200;
		const static APIRequestStatusValue Created = 201;
		const static APIRequestStatusValue Accepted = 202;
		const static APIRequestStatusValue NonAuthInfo = 203;
		const static APIRequestStatusValue NoContent = 204;
		const static APIRequestStatusValue ResetContent = 205;
		const static APIRequestStatusValue PartialContent = 206;
		const static APIRequestStatusValue MultipleChoices = 300;
		const static APIRequestStatusValue MovedPermanently = 301;
		const static APIRequestStatusValue Found = 302;
		const static APIRequestStatusValue SeeOther = 303;
		const static APIRequestStatusValue NotModified = 304;
		const static APIRequestStatusValue UseProxy = 305;
		const static APIRequestStatusValue TemporaryRedirect = 307;
		const static APIRequestStatusValue BadRequest = 400;
		const static APIRequestStatusValue Unauthorized = 401;
		const static APIRequestStatusValue PaymentRequired = 402;
		const static APIRequestStatusValue Forbidden = 403;
		const static APIRequestStatusValue NotFound = 404;
		const static APIRequestStatusValue MethodNotAllowed = 405;
		const static APIRequestStatusValue NotAcceptable = 406;
		const static APIRequestStatusValue ProxyAuthRequired = 407;
		const static APIRequestStatusValue RequestTimeout = 408;
		const static APIRequestStatusValue Conflict = 409;
		const static APIRequestStatusValue Gone = 410;
		const static APIRequestStatusValue LengthRequired = 411;
		const static APIRequestStatusValue PreconditionFailed = 412;
		const static APIRequestStatusValue RequestEntityTooLarge = 413;
		const static APIRequestStatusValue RequestUriTooLarge = 414;
		const static APIRequestStatusValue UnsupportedMediaType = 415;
		const static APIRequestStatusValue RangeNotSatisfiable = 416;
		const static APIRequestStatusValue ExpectationFailed = 417;
		const static APIRequestStatusValue InternalError = 500;
		const static APIRequestStatusValue NotImplemented = 501;
		const static APIRequestStatusValue BadGateway = 502;
		const static APIRequestStatusValue ServiceUnavailable = 503;
		const static APIRequestStatusValue GatewayTimeout = 504;
		const static APIRequestStatusValue HttpVersionNotSupported = 505;
	};
 }
}

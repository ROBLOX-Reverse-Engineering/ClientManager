#pragma once
#include "modules/Base/ModuleBase.h"
#include "Addresses.h"

#define CLIENT_VERSION 140

// Version-Based Address
#define VERSION_ADDR(ver, addr) ver == CLIENT_VERSION ? addr : 
// Defines an address with the given name and value
#define ADDR(name, contents) static const unsigned int name = contents;
// Captures a set of arguments (for ignoring commas)
#define ARGS(...) __VA_ARGS__
// Defines a function using the given return type, name, arguments, and address contents
#define FUNC(type, name, args, contents) typedef type(* name ## _ptr)(args); \
const name ## _ptr name = ( name ## _ptr)(contents);

/// <summary>
/// The base class for the ClientManager protection module.
/// Includes original hooked functions needed for the module.
/// </summary>
class ClientManagerBase : public ModuleBase
{
protected:
	ADDR(publicKey,
		// "BgIAAACkAABSU0ExAAQAAAEAAQCjbUyx9OXTBcWEAonZOfAoT7YhMS+L21WwAZlsEjvzHXQpulpasNFhC1U6tBX6c8Qey2fiRBXHpqbh7vAC7u2niT6dMLLqY9UzII0jyxKD/EUODcQHTKpbM18FRobqLcvK0DNdIaHwypr7NRnSWk4NXhtM0v40W7/mr35PxbJ8rQ=="
		VERSION_ADDR(132, 0xC10C30)
		VERSION_ADDR(140, 0xDD7890)
		VERSION_ADDR(146, 0xDB8D38)
		0x0
	)
	ADDR(assetUrl1,
		// "http://www.roblox.com/asset/?"
		VERSION_ADDR(132, 0xB84E60)
		VERSION_ADDR(140, 0xD43C18)
		VERSION_ADDR(146, 0xCEA99C)
		0x0
	)
	ADDR(assetUrl2,
		// "http://roblox.com/asset/"
		VERSION_ADDR(132, 0xB84798)
		VERSION_ADDR(140, 0xD434E8)
		VERSION_ADDR(146, 0xCEA528)
		0x0
	)
	ADDR(assetUrl3,
		// "http://www.roblox.com/asset/?"
		VERSION_ADDR(132, 0xB8477C)
		VERSION_ADDR(140, 0xD43C18)
		VERSION_ADDR(146, 0xCEA544)
		0x0
	)
	ADDR(fileSystem1,
		// "\\Roblox\\" (keep in mind the non-escaped quotes)
		VERSION_ADDR(132, 0xB93EBC)
		VERSION_ADDR(140, 0xD53050)
		VERSION_ADDR(146, 0xCFAC9C)
		0x0
	)
	ADDR(fileSystem2,
		// "Roblox\\" (keep in mind the non-escaped quotes)
		VERSION_ADDR(132, 0xB93EB4)
		VERSION_ADDR(140, 0x0D53048)
		VERSION_ADDR(146, 0xCFACA8)
		0x0
	)

	static const unsigned int test1 =
		/* 0.132 */ //0x1
		/* 0.140 */ 0x2
		/* 0.146 */ //0x3
	;
	static const unsigned int test2 =
		VERSION_ADDR(132, 0x1)
		VERSION_ADDR(140, 0x2)
		VERSION_ADDR(146, 0x3)
	NULL;
	ADDR(test3,
		VERSION_ADDR(132, 0x1)
		VERSION_ADDR(140, 0x2)
		VERSION_ADDR(146, 0x3)
		0x0 // Default value
	)

public:
	ClientManagerBase(const char* const moduleName, bool moduleEnabled);

protected:
	// All RVAs
	FUNC(bool, isTrustedContent, ARGS(const char* url),
		VERSION_ADDR(132, 0x523EA0)
		VERSION_ADDR(140, 0x86640)
		VERSION_ADDR(146, 0x55DA70)
		0x0
	)

	FUNC(bool, trustCheck, ARGS(const char* url, bool externalRequest),
		VERSION_ADDR(132, 0x6322E0)
		VERSION_ADDR(140, 0x19F4B0)
		VERSION_ADDR(146, 0x0F8070)
		0x0
	)

	FUNC(std::string, buildGenericApiUrl, ARGS(const std::string& baseUrl, const std::string& serviceNameIn, const std::string& path, const std::string& key),
		VERSION_ADDR(132, 0x7F0AE0)
		VERSION_ADDR(140, 0x32F660)
		VERSION_ADDR(146, 0x2AEC80)
		0x0
	)

	FUNC(void, cleanUpIfAssetUrl, ARGS(const std::string& url),
		VERSION_ADDR(132, 0x0)
		VERSION_ADDR(140, 0x1E8FF0)
		VERSION_ADDR(146, 0x16EC50)
		0x0
	)

	FUNC(bool, isValidRobloxAssetUrl, ARGS(const std::string& url),
		VERSION_ADDR(132, 0x0)
		VERSION_ADDR(140, 0x1E2920)
		VERSION_ADDR(146, 0x171990)
		0x0
	)

	FUNC(void, getDefaultReportUrl, ARGS(const std::string& baseUrl, const std::string& shard),
		VERSION_ADDR(132, 0x0)
		VERSION_ADDR(140, 0x353980)
		VERSION_ADDR(146, 0x2B3B60)
		0x0
	)

	typedef void(*funcTest1_ptr)(const bool a);
	const funcTest1_ptr funcTest1 = (funcTest1_ptr)
		/* 0.132 */ //0x1
		/* 0.140 */ 0x2
		/* 0.146 */ //0x3
	;
	typedef void(*funcTest2_ptr)(const bool a);
	const funcTest2_ptr funcTest2 = (funcTest2_ptr)(
		VERSION_ADDR(132, 0x1)
		VERSION_ADDR(140, 0x2)
		VERSION_ADDR(146, 0x3)
	NULL);
	FUNC(void, funcTest3, ARGS(const bool a, const bool b),
		VERSION_ADDR(132, 0x1)
		VERSION_ADDR(140, 0x2)
		VERSION_ADDR(146, 0x3)
		0x0 // Default address
	)
};


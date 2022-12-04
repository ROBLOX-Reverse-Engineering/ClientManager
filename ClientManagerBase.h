#pragma once
#include "modules/Base/ModuleBase.h"
#include "Addresses.h"

/// <summary>
/// The base class for the ClientManager protection module.
/// Includes original hooked functions needed for the module.
/// </summary>
class ClientManagerBase : public ModuleBase
{
protected:
	static const unsigned int publicKey =
		/* 0.132 */ //0xC10C30
		/* 0.146 */ 0xDB8D38
	;
	static const unsigned int assetUrl1 =
		/* 0.132 */ //0xB84E60
		/* 0.146 */ 0xCEA99C
	;
	static const unsigned int assetUrl2 =
		/* 0.132 */ //0xB84798
		/* 0.146 */ 0xCEA528
	;
	static const unsigned int assetUrl3 =
		/* 0.132 */ //0xB8477C
		/* 0.146 */ 0xCEA544
	;
	static const unsigned int fileSystem1 =
		/* 0.132 */ //0xB93EBC
		/* 0.146 */ 0xCFAC9C
	;
	static const unsigned int fileSystem2 =
		/* 0.132 */ //0xB93EB4
		/* 0.146 */ 0xCFACA8
	;

public:
	ClientManagerBase(const char* const moduleName, bool moduleEnabled);

protected:
	// All RVAs
	typedef bool(* isTrustedContent_ptr)(const char* url);
	const isTrustedContent_ptr isTrustedContent = (isTrustedContent_ptr)
		/* 0.132 */ //0x523EA0
		/* 0.146 */ 0x55DA70
	;

	typedef bool(* trustCheck_ptr)(const char* url, bool externalRequest);
	const trustCheck_ptr trustCheck = (trustCheck_ptr)
		/* 0.132 */ //0x6322E0
		/* 0.146 */ 0x0F8070
	;

	typedef std::string(* buildGenericApiUrl_ptr)(const std::string& baseUrl, const std::string& serviceNameIn, const std::string& path, const std::string& key);
	const buildGenericApiUrl_ptr buildGenericApiUrl = (buildGenericApiUrl_ptr)
		/* 0.132 */ //0x7F0AE0
		/* 0.146 */ 0x2AEC80
	;

	typedef void(*cleanUpIfAssetUrl_ptr)(const std::string& url);
	const cleanUpIfAssetUrl_ptr cleanUpIfAssetUrl = (cleanUpIfAssetUrl_ptr)
		/* 0.132 */ //0x0
		/* 0.146 */ 0x16EC50
	;

	typedef bool(*isValidRobloxAssetUrl_ptr)(const std::string& url);
	const isValidRobloxAssetUrl_ptr isValidRobloxAssetUrl = (isValidRobloxAssetUrl_ptr)
		/* 0.132 */ //0x0
		/* 0.146 */ 0x171990
	;

	typedef void(*getDefaultReportUrl_ptr)(const std::string& baseUrl, const std::string& shard);
	const getDefaultReportUrl_ptr getDefaultReportUrl = (getDefaultReportUrl_ptr)
		/* 0.132 */ //0x0
		/* 0.146 */ 0x2B3B60
	;
};


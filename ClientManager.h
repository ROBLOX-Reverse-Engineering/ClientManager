#pragma once
#include "ClientManagerBase.h"

/// <summary>
/// A general client-management module.
/// </summary>
class ClientManager : public ClientManagerBase
{
private:
	void patchClient();

public:
	ClientManager();
	void startModule();

	// These will hopefully be dynamic at some point
	static std::string getBaseDomain();
	static std::string getBaseUrl();
	static std::string getRobloxDomain();
	static std::string getRobloxUrl();

	static bool isTrustedContent(const char* url);
	static bool trustCheck(const char* url, bool externalRequest);
	static std::string buildGenericApiUrl(const std::string& baseUrl, const std::string& serviceNameIn, const std::string& path, const std::string& key);
	static bool isHttpUrl(const std::string& s);
	static std::string cleanUpIfAssetUrl(const std::string& url);
	static bool isValidRobloxAssetUrl(const std::string& url);

	static std::string getDefaultReportUrl(const std::string& baseUrl, const std::string& shard);


	// HACK: Prevents the compiler from automatically deconstructing a type ( thanks moded :) )
	template <typename T>
	struct primitive
	{
		unsigned char b[sizeof(T)];
	};

	static std::string buildGenericApiUrlWrapper(primitive<std::string> baseUrl, primitive<std::string> serviceNameIn, primitive<std::string> path, primitive<std::string> key);
	static bool isValidRobloxAssetUrlWrapper(primitive<std::string> url);
};


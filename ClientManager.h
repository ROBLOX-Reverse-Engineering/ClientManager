#pragma once
#include "ClientManagerBase.h"
#include "lpstring.h"

/// <summary>
/// A general client-management module.
/// </summary>
class ClientManager : public ClientManagerBase
{
#define LPSTRING(name) std::string(((string*)&name)->c_str())

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

	// Wrappers //
	// TODO: Figure out a better way...

	static string buildGenericApiUrlWrapper(primitive<string> baseUrl, primitive<string> serviceNameIn, primitive<string> path, primitive<string> key)
	{
		return string(buildGenericApiUrl(
			LPSTRING(baseUrl),
			LPSTRING(serviceNameIn),
			LPSTRING(path),
			LPSTRING(key)
		).c_str());
	}

	static string cleanUpIfAssetUrlWrapper(const string& url)
	{
		return string(cleanUpIfAssetUrl(
			LPSTRING(url)
		).c_str());
	}

	static bool isValidRobloxAssetUrlWrapper(primitive<string> url)
	{
		return isValidRobloxAssetUrl(
			LPSTRING(url)
		);
	}

	static string getDefaultReportUrlWrapper(const string& baseUrl, const string& shard)
	{
		return string(getDefaultReportUrl(
			LPSTRING(baseUrl),
			LPSTRING(shard)
		).c_str());
	}
};


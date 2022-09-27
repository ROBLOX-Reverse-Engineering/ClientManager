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
	//static CallWrapper<0, std::string, std::string, std::string, std::string, std::string> buildGenericApiUrlWrapper;

	static std::string getDefaultReportUrl(const std::string& baseUrl, const std::string& shard);


	// HACK: Prevents the compiler from automatically deconstructing a type ( thanks moded :) )
	template <typename T>
	struct primative
	{
		unsigned char b[sizeof(T)];
	};

	static std::string buildGenericApiUrlWrapper(primative<std::string> baseUrl, primative<std::string> serviceNameIn, primative<std::string> path, primative<std::string> key);
};


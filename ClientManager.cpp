#include <algorithm>

#include "ClientManager.h"
#include "PatchHelper.h"
#include "Addresses.h"
#include "WatchDog.h"

#include "format_string.h"

#define ROBLOX_URL_IDENTIFIER "roblox.com/"
#define ROBLOXLABS_URL_IDENTIFIER ".robloxlabs.com/"

#define BASE_DOMAIN "roblonium.com"
#define BASE_URL "www.roblonium.com"

#define ROBLOX_DOMAIN "roblox.com"
#define ROBLOX_URL "www.roblox.com"


ClientManager::ClientManager()
	: ClientManagerBase(
		"ClientManager", // Module Name
		true	         // Enabled
	)
{
}

void ClientManager::startModule()
{
	ModuleBase::startModule();

	patchClient();

	initEndEvent();
}

std::string ClientManager::getBaseDomain()
{
	return BASE_DOMAIN;
}

std::string ClientManager::getBaseUrl()
{
	return BASE_URL;
}

std::string ClientManager::getRobloxDomain()
{
	return ROBLOX_DOMAIN;
}

std::string ClientManager::getRobloxUrl()
{
	return ROBLOX_URL;
}

void ClientManager::patchClient()
{
	// We could replace the actual pointer here instead of the value it points to (though it doesn't really matter since pubkeys are always the same length)
	PatchHelper::PatchBytes(publicKey, "BgIAAACkAABSU0ExAAQAAAEAAQCRCVQhLSOLCa8zpdnkvM6iYQ/noaVbZgI5gkPUh7eWygShuCXTN+nTAZql7oFrmSWgj86QugP0lBkkl6Gtr1FptfyCKHs9rhBxiJ3wjFbb0tPN11ephsGEPa+JgauM5ZRt52IPNfruzs1r/pYl7yBh/XKLxp+9DKCue1ifYWtc3A==");
	PatchHelper::PatchBytes(assetUrl1, "http://roblonium.com/asset/?");
	PatchHelper::PatchBytes(assetUrl2, "http://roblonium.com/asset/");
	PatchHelper::PatchBytes(assetUrl3, "http://www.roblonium.com/asset/");
	PatchHelper::PatchBytes(fileSystem1, "\\Hexine\\");
	PatchHelper::PatchBytes(fileSystem2, "Hexine\\");

	// Function Hooks
	PatchHelper::HookFunction((unsigned int)ClientManagerBase::isTrustedContent, (unsigned int)&isTrustedContent);
	PatchHelper::HookFunction((unsigned int)ClientManagerBase::trustCheck, (unsigned int)&trustCheck);
	PatchHelper::HookFunction((unsigned int)ClientManagerBase::buildGenericApiUrl, (unsigned int)&buildGenericApiUrlWrapper);
	PatchHelper::HookFunction((unsigned int)ClientManagerBase::cleanUpIfAssetUrl, (unsigned int)&cleanUpIfAssetUrl);
	PatchHelper::HookFunction((unsigned int)ClientManagerBase::getDefaultReportUrl, (unsigned int)&getDefaultReportUrl);

	//print(ClientManagerBase::buildGenericApiUrl(getBaseUrl(), "games", "/v1/GetRelayConfiguration", "test").c_str());
}

bool ClientManager::isTrustedContent(const char* url)
{
	// TODO: ClientManager singleton for this?
	// These have to be static btw, but we could maybe use a singleton?
	//printf("isTrustedContent: %s", url);
	return true;
}

bool ClientManager::trustCheck(const char* url, bool externalRequest)
{
	static const bool kSkipTrustCheck = false;
	if (kSkipTrustCheck)
	{
		return true;
	}

	//printf("trustCheck: %s", url);
	//printf("externalRequest: %s", externalRequest ? "true" : "false");
	return true;
}

std::string ClientManager::buildGenericApiUrlWrapper(primative<std::string> baseUrl, primative<std::string> serviceNameIn, primative<std::string> path, primative<std::string> key)
{
	return buildGenericApiUrl(
		*(std::string*)&baseUrl,
		*(std::string*)&serviceNameIn,
		*(std::string*)&path,
		*(std::string*)&key
	);
}

//CallWrapper<0, std::string, std::string, std::string, std::string, std::string> ClientManager::buildGenericApiUrlWrapper(&buildGenericApiUrl);
std::string ClientManager::buildGenericApiUrl(const std::string& baseUrl, const std::string& serviceNameIn, const std::string& path, const std::string& key) // should be HTTPS
{
	std::string serviceName(serviceNameIn);
	std::string rbxUrl = ".roblox.com";
	size_t pos = baseUrl.find(rbxUrl);
	if (pos == std::string::npos)
	{
		//rbxUrl = ".robloxlabs.com";
		rbxUrl = ".roblonium.com";
		pos =  baseUrl.find(rbxUrl);
	}

	std::string subUrl = baseUrl.substr(0, pos);

	if (subUrl == "www" || subUrl == "http://www" || subUrl == "https://www" || subUrl == "m" || subUrl == "http://m" ) //prod
	{
		subUrl = "";
	}
	std::string httpPrefix = "http://";
	pos = subUrl.find(httpPrefix);
	if (pos != -1)
	{
		subUrl = subUrl.substr(httpPrefix.length(), subUrl.length() - httpPrefix.length());
	}

	if ("" != serviceName)
		serviceName += ".";

	std::string url;
	if (subUrl.empty())
	{
		// production
		//url = format_string("%s://%sapi.roblox.com/%s/?apiKey=%s", scheme, serviceName.c_str(), path.c_str(), key.c_str());
		url = format_string("http://%sapi.roblonium.com/%s/?apiKey=%s", serviceName.c_str(), path.c_str(), key.c_str());
	}
	else
	{
		if (subUrl.find("www") != -1)
		{
			subUrl = subUrl.replace(0, 4, "");
			url = format_string("http://%sapi.%s%s/%s/?apiKey=%s", serviceName.c_str(), subUrl.c_str(), rbxUrl.c_str(), path.c_str(), key.c_str());
		}
		else if(subUrl.find("m.") == 0)
		{
			subUrl = subUrl.replace(0, 2, "");
			url = format_string("http://%sapi.%s%s/%s/?apiKey=%s", serviceName.c_str(), subUrl.c_str(), rbxUrl.c_str(), path.c_str(), key.c_str());
		}
		else if (subUrl.find(".sitetest3") != -1) // Special case for URLs like alberto.sitetest3, navin.sitetest3, etc..
		{
			url = format_string("http://%sapi.sitetest3%s/%s/?apiKey=%s", serviceName.c_str(), rbxUrl.c_str(), path.c_str(), key.c_str());
		}
	}

	WatchDog::singleton()->printf("Built generic base API URL: %s", url.c_str());

	return url;
}

bool ClientManager::isHttpUrl(const std::string& s)
{
	if (s.find("http://") == 0)
		return true;
	if (s.find("https://") == 0)
		return true;
	return false;
}

std::string ClientManager::cleanUpIfAssetUrl(const std::string& url)
{
    std::string lower = url;
    std::transform(lower.begin(), lower.end(), lower.begin(), tolower);
    if (isHttpUrl(lower))
    {
        if (lower.find("/asset") == std::string::npos)
            return url;


		// Upgrades all ROBLOX.com HTTP requests to HTTPS
		size_t pos = lower.find(getRobloxUrl());
		if (pos != std::string::npos)
		{
			// Direct to assetdelivery
			std::string repUrl = format_string("assetdelivery.%s/v1", getRobloxDomain().c_str());
			lower = lower.replace(pos, getRobloxUrl().length(), repUrl);

			pos = lower.find("http://");
			if (pos != std::string::npos)
			{
				// Direct to HTTPS
				lower = lower.replace(pos, 7, "https://");
			}
		}

		//printf("cleanUpIfAssetUrl (original): %s", url.c_str());
		//printf("cleanUpIfAssetUrl: %s", lower.c_str());
		return lower;
    }
	return url;
}

std::string ClientManager::getDefaultReportUrl(const std::string& baseUrlInput, const std::string& shard)
{
	// copy base url, to allow modification
	std::string baseUrl = baseUrlInput;

	//RBXASSERT(baseUrl.substr(0, 7) == "http://");
	if (baseUrl.find(getBaseUrl()) != std::string::npos)
		baseUrl = "http://logging.service." + getBaseDomain() + "/";
	else
		baseUrl.insert(7, "logging.service.");	// Inserted after http://
	return baseUrl + "Gatherer/LogEntry?Shard=" + shard;
}

// create event when handle creation, loop through child-windows and if it contains process name, code red.
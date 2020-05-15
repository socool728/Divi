#ifndef DIRECTORY_NAME_PROVIDER_H
#define DIRECTORY_NAME_PROVIDER_H

#if defined(HAVE_CONFIG_H)
#include "config/divi-config.h"
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include <map>

extern std::map<std::string, std::string> mapArgs;

boost::filesystem::path GetDefaultDataDir();
const boost::filesystem::path& GetDataDir(bool fNetSpecific = true);
void ClearDatadirCache();
#ifdef WIN32
boost::filesystem::path GetSpecialFolderPath(int nFolder, bool fCreate = true);
#endif

#endif
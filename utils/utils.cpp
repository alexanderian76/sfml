#include "utils.h"
#if defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#endif

std::string getResourcePath()
{
#if defined(__APPLE__)
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);

    char path[PATH_MAX];
    CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX);
    CFRelease(resourcesURL);

    return std::string(path) + "/";
#endif
    return "";
}

sf::String toSFString(const std::string &utf8String)
{
    return sf::String::fromUtf8(utf8String.begin(), utf8String.end());
}
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include "environment.hpp"

extern char **Environmentiron;

    
//! Apple does not have a clearenv method.  This is the implementation.
//! FreeBSD might be the same...
#ifdef __APPLE__
    int clearenv(void)
    {
        extern char **environ;
        char **pe;
        char *n;
        
        for(pe = environ; pe && *pe; pe++) {
            n = strchr(*pe, '=');
            if(n) {
                n = strndup(n, (n - *pe));
            } else {
                n = *pe;
            }
            unsetenv(n);
            if(n != *pe)
                free(n);
        }
        return 0;
    }
#endif

namespace hoss {
namespace os {

std::string Environment::get(std::string const& a_key)  {
	return get(a_key.c_str());
}

std::string Environment::get(const char * a_key)  {
	char const *val = getenv(a_key);
	return val == NULL ? std::string() : std::string(val);
}

bool Environment::isExists(const char *a_key) {
	return getenv(a_key) == NULL ? false : true;
}

bool Environment::isExists(std::string &a_key) {
	return isExists(a_key.c_str());
}

const std::string Environment::operator[](const char *a_name) const {
	return get(a_name);
}

const std::string Environment::operator[](const std::string &a_name) const {
	return get(a_name);
}

int Environment::set(std::string const& a_key, std::string const& a_value) {
	return set(a_key.c_str(), a_value.c_str());
}

int Environment::set(const char *a_key, const char *a_value) {
	return setenv( a_key, a_value, 1 );
}

int Environment::erase(std::string const& a_key) {
	return erase( a_key.c_str());
}

int Environment::erase(const char *a_key) {
	return unsetenv(a_key);
}

bool Environment::clearAll() {
	return clearenv();
}

std::string Environment::home_path() {
    // Something as simple as resolving a user's home directory can be
    // a little complicated; the HOME evironment may or may not be defined, such
    // as is the case for a GUI application on OS X.  This works on Linux,
    // and OS X:
    const char *pHome = getenv("HOME");
    
    // If HOME is not defined, check UID.
    if (!pHome) {
        struct passwd* pwd = getpwuid(getuid());
        if (pwd)
            pHome = pwd->pw_dir;
    }
    
    return std::string(pHome);
    
}


}
}


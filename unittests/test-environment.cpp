#include <stdlib.h>
#include <string>
#include "test-environment.h"
#include "environment.hpp"

using namespace std;
using namespace hoss::os;

CPPUNIT_TEST_SUITE_REGISTRATION( utEnv );

void utEnv::test_get() {
	Environment env;
	const char *HOME= "HOME";
	char const *home = getenv("HOME");

	string strhome = env.get(HOME);
	CPPUNIT_ASSERT( strhome == home );

	strhome = HOME;
	CPPUNIT_ASSERT( env.get(strhome) == home);

	CPPUNIT_ASSERT( env[strhome] == home);
	CPPUNIT_ASSERT( env[HOME] == home);
}

void utEnv::test_exists() {
	Environment env;
	const char *xyz="XZVSS123";
	const char *home="HOME";

	CPPUNIT_ASSERT( !env.isExists(xyz) );
	CPPUNIT_ASSERT( env.isExists(home) );

	string tmp = xyz;
	CPPUNIT_ASSERT( !env.isExists( tmp ) );
	tmp = home;
	CPPUNIT_ASSERT( env.isExists(  tmp ) );
}

void utEnv::test_home() {
	Environment env;
	char const *home = getenv("HOME");
	CPPUNIT_ASSERT( env.home_path() == home);
}

void utEnv::test_set_and_erase() {
	Environment env;
	const char *xyz="XZVSS123";
	CPPUNIT_ASSERT( !env.isExists(xyz) );
	CPPUNIT_ASSERT( !env.set(xyz, xyz));
	CPPUNIT_ASSERT( env.get(xyz) == xyz);
	CPPUNIT_ASSERT( env.isExists(xyz) );
	CPPUNIT_ASSERT( !env.erase(xyz));
	CPPUNIT_ASSERT( !env.isExists(xyz) );
}

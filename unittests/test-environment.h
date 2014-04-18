#ifndef UTENV_H_
#define UTENV_H_
#include <cppunit/extensions/HelperMacros.h>


class utEnv : public CppUnit::TestFixture {
public:

	// unit test methods
	void test_get();
	void test_exists();
	void test_home();
	void test_set_and_erase();

	// unit test registration
	CPPUNIT_TEST_SUITE( utEnv );
		CPPUNIT_TEST( test_get );
		CPPUNIT_TEST( test_exists );
		CPPUNIT_TEST( test_home );
		CPPUNIT_TEST( test_set_and_erase );
	CPPUNIT_TEST_SUITE_END();

};

#endif

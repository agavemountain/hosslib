#include <stdio.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int, char ** )
{
    CppUnit::TextUi::TestRunner   runner;
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );

    // Run the tests
    printf("\n\n--------------- UNIT TESTS ------------------------------\n");
    bool fSuccess = runner.run( "", false );

    // Return the result
    return((fSuccess) ? 0 : 1);
}


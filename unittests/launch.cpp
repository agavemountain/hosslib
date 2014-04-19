#include <string>
#include <stdio.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include "environment.hpp"
using namespace boost::filesystem;
using namespace std;
using namespace hoss::os;

int main(int argc, char *argv[]) {

	Environment env;
	cout << env.home_path() << endl;
	path p(env.home_path() + "/.hoss");

   if (exists(p))    // does p actually exist?
	  {
	    if (is_regular_file(p))        // is p a regular file?
	      cout << p << " size is " << file_size(p) << '\n';

	    else if (is_directory(p))   {   // is p a directory? {
	    	remove(p);
	      cout << p << " is a directory removing \n";
	  }
	    else
	      cout << p << " exists, but is neither a regular file nor a directory\n";
	  }
	  else {
		    cout << p << " does not exist\n";
		    create_directory(p);
	  }

	  return 0;
}

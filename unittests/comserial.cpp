#include <iostream>
#include <boost/program_options.hpp>
#include <boost/thread.hpp> 
//#include <instruments/bus_pirate.hpp>
#include <net/serial_port.hpp>

using namespace std;
using namespace boost::program_options;
using namespace hoss::net;

int main(int argc, char **argv) {
    
    options_description desc("Allowed options");
    desc.add_options()
    ("help", "produce help message")
    ;
    
    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);
    
    if (vm.count("help") || argc < 2) {
        std::cout << "SYNTAX : " << argv[0] << " <serial device>\n";
        std::cout << desc << "\n";
        return 1;
    }
    
    //#ifdef POSIX
    //#pragma message "POSIX"
    termios stored_settings;
    tcgetattr(0, &stored_settings);
    termios new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_lflag &= (~ISIG); // don't automatically handle control-C
    tcsetattr(0, TCSANOW, &new_settings);
    //#endif
    
    try
    {
        boost::asio::io_service io_service;
        SerialPort serial( io_service, 115200, argv[1] );

        boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
        while (!serial.isStopped()) // check the internal state of the connection to make sure it's still running
        {
            char ch;
            cin.get(ch); // blocking wait for standard input
            if (ch == 3) // ctrl-C to end program
                break;
            serial.write(ch);
        }
        std::cout << "yeo.\n";
        serial.close(); // close the minicom client connection
        t.join(); // wait for the IO service thread to close
    }
    catch (exception& e)
    {
        cerr << "Exception: " << e.what() << "\n";
    }
    
    //#ifdef POSIX // restore default buffering of standard input
    tcsetattr(0, TCSANOW, &stored_settings);
    //#endif
    
    return 0;
}
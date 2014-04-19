#include <iostream>
#include <boost/program_options.hpp>

//#include <instruments/bus_pirate.hpp>
#include <net/serial_port.hpp>

using namespace std;
using namespace boost::program_options;
using namespace hoss::net;

int main(int argc, char **argv)
{

  options_description desc("Allowed options");
  desc.add_options()
  ("help", "produce help message")
  ;

  variables_map vm;
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);

  if (vm.count("help") || argc < 2)
    {
      std::cout << "SYNTAX : " << argv[0] << " <serial device>\n";
      std::cout << desc << "\n";
      return 1;
    }

  termios stored_settings;
  tcgetattr(0, &stored_settings);
  termios new_settings = stored_settings;
  new_settings.c_lflag &= (~ICANON);
  tcsetattr(0, TCSANOW, &new_settings);

  try
    {
      boost::asio::io_service io_service;
      SerialPort serial( io_service, 115200, argv[1] );
      serial.writeString(string("\n"));
      string result = "";
      while (result != "HiZ>")
        {
          result = serial.readString();
          std::cout << result << std::endl;
        }

      serial.writeString(string("i\n"));
      result = "";
      while (result != "HiZ>")
        {
          result = serial.readString();
          std::cout << result << std::endl;
        }

      serial.close();
    }
  catch (exception& e)
    {
      cerr << "Exception: " << e.what() << "\n";
    }

  tcsetattr(0, TCSANOW, &stored_settings);
  return 0;
}
#ifndef _BUS_PIRATE_HPP_
#define _BUS_PIRATE_HPP_
#include <net/serial_port.hpp>

namespace hoss
{
//! Instruments and Measurement Namespace
namespace instruments
{

//! @brief Bus Pirate
//!
//! "The Bus Pirate is an open source hacker multi-tool that talks to electronic stuff. It's got a bunch
//! of features an intrepid hacker might need to prototype their next project. This manual is an
//! effort to link all available Bus Pirate information in one place."
//!
//! http://dangerousprototypes.com/docs/Bus_Pirate
//!
//! Data Rate: 115200
//! Data Bits: 8
//! Parity: None
//! Stop bits: 1
//!
//! The rest you can leave at the default. [UPDATE] On newer firmware versions you’ll need to deselect Xon/Xoff as per Ian in the comments below.
class BusPirate : public net::SerialPort
{
public:


  void start_selftest();

  //! @brief submit the info command
  std::string query_info()
  {

  }

private:

  std::string m_version;
  std::string m_firmware_version;
  std::string m_bootloader_version;
  std::string m_extra_version_info;
};
}
}
#endif


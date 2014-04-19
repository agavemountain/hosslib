//! HOSS Core Library
//!
//! @author Joe Turner <joe@agavemountain.com>
//!
//! Copyright (C) 2014; All Rights Reserved.
//!
#ifndef _SERIAL_PORT_HPP_
#define _SERIAL_PORT_HPP_
#include <iostream>
#include <deque>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
namespace hoss
{
namespace net
{

//! @brief Multi-platform Serial Port (RS232) Class
//!
//! RS-232 is traditionaly used for connections to modems, terminal servers,
//! routers, servers, mice, data storage and uninterruptable power supplies.
//! A serial port may be local communications ports, virtualized serial port
//! (USB or serial over ethernet).
//!
//!
//! This class contains the code necessary to communicate with local
//! an virtualized serial ports.
//!
//! @todo use enable_shared_from_this<SerialPort>
class SerialPort
{
public:

  //! Specialized constructor
  //!
  //! @param io_service   asio io_service
  //! @param baud         baud rate
  //! @param device       name of the serial device. In windows is will be a COMM port, in Linux
  //!                     or OS X it will be something like, /dev/xxx
  //!
  SerialPort(boost::asio::io_service& io_service, unsigned int baud, const std::string& device)
    : m_active(true),
      m_io_service(io_service),
      m_serial_port(io_service, device)
  {
    std::cout << "SERIAL-OPEN: " << device << std::endl;
    if (!m_serial_port.is_open())
      {
        std::cerr << "Failed to open serial port\n";
        return;
      }
    boost::asio::serial_port_base::baud_rate baud_option(baud);
    m_serial_port.set_option(baud_option); // set the baud rate after the port has been opened
    read_start();
  }

  //! Destructor
  ~SerialPort()
  {
    close();
  }

  //! Write a string to the serial device.
  //!
  //! @param a_str    string to write
  //!
  void writeString(std::string a_str)
  {
    boost::asio::write(m_serial_port,boost::asio::buffer(a_str.c_str(),a_str.size()));
  }

  //! Read until a new line character is received from a serial device.
  //! This function blocks until a line is received from the serial device.
  std::string readString()
  {
    char c;
    std::string result;
    for(;;)
      {
        boost::asio::read(m_serial_port,boost::asio::buffer(&c,1));
        std::cout << std::flush;
        switch(c)
          {
          //case '\r':
          //    break;
          case '>':
            result+=c;
            return result;
            break;
          case '\n':
            return result;
          default:
            result+=c;
          }
      }
  }

  //! Close the ASIO socket and terminate outstanding I/O requests.
  void stop()
  {
    m_serial_port.close();
  }

  bool isStopped() const
  {
    return !m_serial_port.is_open();
  }

  void handle_write()
  {
    if (!m_serial_port.is_open()) return;

  }

  //! Write a character
  //! @param msg  character to write
  void write(const char a_msg)
  {
    m_io_service.post(boost::bind(&SerialPort::do_write, this, a_msg));
  }

  //! close
  void close()
  {
    m_io_service.post(boost::bind(&SerialPort::do_close, this, boost::system::error_code()));
  }

private:

  //! Start an asynchronous read, which will call read_complete when the read completes,
  //! or fails.
  void read_start(void)
  {
    // Start an asynchronous read and call read_complete when it completes or fails
    m_serial_port.async_read_some(boost::asio::buffer(m_read_data, MAX_READ_LENGTH),
                                  boost::bind(&SerialPort::read_complete,
                                      this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
  }

  //! the asynchronous read operation has now completed or failed and returned an error
  void read_complete(const boost::system::error_code& error, size_t bytes_transferred)
  {
    if (!error)
      {
        // read completed, so process the data
        std::cout.write(m_read_data, bytes_transferred); // echo to standard output
        std::cout << std::flush;
        read_start(); // start waiting for another asynchronous read again
      }
    else
      {
        do_close(error);
      }
  }

  //! Close the socket, due to error.
  void do_close(const boost::system::error_code& error)
  {
    // something has gone wrong, so close the socket & make this object inactive
    if (error == boost::asio::error::operation_aborted) // if this call is the result of a timer cancel()
      return; // ignore it because the connection cancelled the timer
    if (error)
      std::cerr << "Error: " << error.message() << std::endl; // show the error message
    else
      std::cout << "Error: Connection did not succeed.\n";
    std::cout << "Press Enter to exit\n";
    m_serial_port.close();
    m_active = false;
  }

  void do_write(const char msg)
  {
    // callback to handle write call from outside this class
    bool write_in_progress = !write_msgs_.empty(); // is there anything currently being written?
    write_msgs_.push_back(msg); // store in write buffer
    if (!write_in_progress) // if nothing is currently being written, then start
      write_start();
  }


  void write_start(void)
  {
    // Start an asynchronous write and call write_complete when it completes or fails
    boost::asio::async_write(m_serial_port,
                             boost::asio::buffer(&write_msgs_.front(), 1),
                             boost::bind(&SerialPort::write_complete,
                                         this,
                                         boost::asio::placeholders::error));
  }

  void write_complete(const boost::system::error_code& error)
  {
    // the asynchronous read operation has now completed or failed and returned an error
    if (!error)
      {
        // write completed, so send next write data
        write_msgs_.pop_front(); // remove the completed data
        if (!write_msgs_.empty()) // if there is anthing left to be written
          write_start(); // then start sending the next item in the buffer
      }
    else
      do_close(error);
  }

private:

  //! maximum amount of data to read in one operation
  static const int MAX_READ_LENGTH = 512;

  //! Flag that remains active while we the port is open.
  bool m_active;
  //! Main I/O service that runs this connection
  boost::asio::io_service& m_io_service;
  //! Serial port object this instance is connected to
  boost::asio::serial_port m_serial_port;
  //! data read from the socket
  char m_read_data[MAX_READ_LENGTH];
  //! data to be written to the socket
  std::deque<char> write_msgs_; //!< buffered write data

};

}
}

#endif
/** @mainpage

    <table>
        <tr><th>Library     <td>hosslib
        <tr><th>File        <td>hosslib.hpp
        <tr><th>Author      <td>Joe Turner [joe@agavemountain.com]
        <tr><th>Source      <td>http://github.com/xxx
        <tr><th>Version     <td>0.01
    </table>

    @section intro INTRODUCTION

    @code
    This code is UNSTABLE and in active development.  Use at your own risk.
    @endcode
 
    This library contains a collection of classes used by the Hardware Open Source System (HOSS) project.
    It includes low level APIs and foundational classes to communicate with hardware devices and 
    instruments such as multimeters, oscilloscopes, etc.
 
    \note Given the severe lack of open source packages for electronics hardware development available 
          on the Mac, I decided on a "Mac first" development philosophy. As a result, this library is 
          coded on Mac OS X first, then Linux and when time allows Windows.
	
    @section supported SUPPORTED HARDWARE
 
    The following hardware/protocols are supported:
 
    - RS-232 serial
    - Bus Pirate

    @section requires REQUIREMENTS

    Although this library is foundational in nature, it does require other libraries and packages to be installed 
    prior to building.  To build this software you will need several packages pre-installed:

    -# CMake. Install CMake for your platform.
    -# Boost.  This library relies on boost::ASIO, boost::system, boost::filesystem, boost::program_options, and other boost libraries.
    -# Doxygen.  This is used to generate the API documentation.
    -# git. This is for obvious reasons

    @section install INSTALLING
 
    To build hosslib:
 
    @code
    mkdir build
    cd build
    cmake ..
    make
    make doc        # to build documentation
    ctest           # to execute unit tests
    make install    # to install
    @endcode
 
    @section contrib CONTRIBUTIONS

    - none (yet)

    @section license MIT LICENCE

    The license text below is the boilerplate "MIT License" used from:
    http://www.opensource.org/licenses/mit-license.php

    Copyright (c) 2014, Joe Turner

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is furnished
    to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
    COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
    IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
#ifndef _HOSSLIB_HPP_
#define _HOSSLIB_HPP_

//! Hardware Open Source System (HOSS) Namespace.
namespace hoss {
    
    //! Network and Communications Namespace.
    namespace net {
        
    }
    
    //! Instruments and Measurement Namespace.
    namespace instruments {
        
    }
    
    //! Operating System Specific Namespace.
    namespace os {
        
    }
}

#endif 



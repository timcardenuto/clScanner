/*
    clScanner does a simple scan of the local machine for devices that support OpenCL execution.
    Copyright (C) 2017  Tim Cardenuto

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    To build this program:
      g++ scan.cpp -o scan -lOpenCL
*/

#include <iostream>
#include <vector>
#include <string>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

int main() {

    try {
        std::cout << '\n';

        // Get list of OpenCL platforms.
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        if (platforms.empty()) {
            std::cerr << "OpenCL platforms not found." << std::endl;
            return 1;
        }

        for(int i = 0; i < platforms.size(); i++) {
            cl::Platform default_platform = platforms[i];
            std::cout << "Platform[" << i << "] Name:     " << default_platform.getInfo<CL_PLATFORM_NAME>() << '\n';
            std::cout << "Platform[" << i << "] Vendor:   " << default_platform.getInfo<CL_PLATFORM_VENDOR>() << '\n';
            std::cout << "Platform[" << i << "] Version:  " << default_platform.getInfo<CL_PLATFORM_VERSION>() << '\n';

            // Get list of OpenCL devices
            std::vector<cl::Device> devices;
            default_platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

            if (devices.empty()) {
                std::cerr << "  OpenCL devices not found." << std::endl;
                return 1;
            }

            for(int j = 0; j < devices.size(); j++) {
                cl::Device default_device = devices[j];
                std::cout << "  Device[" << j << "] Name:     " << default_device.getInfo<CL_DEVICE_NAME>() << '\n';
                std::cout << "  Device[" << j << "] Type:     " << default_device.getInfo<CL_DEVICE_TYPE>() << '\n';
                std::cout << "  Device[" << j << "] Version:  " << default_device.getInfo<CL_DEVICE_VERSION>() << '\n';
                //  std::cout << "  Device[" << j << "] Spir Version: " << default_device.getInfo<CL_DEVICE_SPIR_VERSIONS>() << '\n';
            }

            std::cout << '\n';
        }

    } catch (const cl::Error &err) {
        std::cerr
        << "OpenCL error: "
        << err.what() << "(" << err.err() << ")"
        << std::endl;
        return 1;
    }
}

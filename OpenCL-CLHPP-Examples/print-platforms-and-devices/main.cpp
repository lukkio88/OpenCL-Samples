#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 300

#include <CL/opencl.hpp>
#include <iostream>

void printPlatformsAndDevices(const cl_device_type& deviceType = CL_DEVICE_TYPE_GPU)
{
    std::vector<cl::Platform> platforms;
    std::vector<cl::Device> devices;
    
    cl::Platform::get(&platforms);
    for (auto& currentPlatform : platforms) {
        std::cout << currentPlatform.getInfo<CL_PLATFORM_NAME>() << ": " << std::endl;
        currentPlatform.getDevices(deviceType, &devices);
        for (auto& currentDevice : devices)
        {
            std::cout << "- " << currentDevice.getInfo<CL_DEVICE_NAME>() << std::endl;
        }
    }    
}

int main(int argc, char** argv)
{
    printPlatformsAndDevices();
    return 0;
}
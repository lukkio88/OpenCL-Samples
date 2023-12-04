#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 300

#include <CL/opencl.hpp>
#include <iostream>

void printPlatformsAndDevices()
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl::Platform platform;

    for (auto& p : platforms) {
        const std::string& currentPlatformName = p.getInfo<CL_PLATFORM_NAME>();
        std::cout << currentPlatformName << ": " << std::endl;
        std::vector<cl::Device> devices;
        p.getDevices(CL_DEVICE_TYPE_ALL, &devices);
        for (auto& d : devices)
        {
            std::cout << "- " << d.getInfo<CL_DEVICE_NAME>() << std::endl;
        }
    }
}

int main(int argc, char** argv)
{
    printPlatformsAndDevices();
}
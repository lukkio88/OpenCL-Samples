#ifndef UTILS_H
#define UTILS_H
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 300
#include <vector>
#include <CL/opencl.hpp>

void printVector(const std::vector<float>& v);
std::string readFile(const std::string& path);

struct OpenCLData
{
    cl::Platform platform;
    cl::Device device;
    std::string kernelSource;
    cl::Context context;
    cl::Program program;
};

OpenCLData basicSetup(
    const std::string& platformName,
    const cl_device_type& deviceType,
    const std::string& deviceName,
    const std::string& sourcePath
);

#endif
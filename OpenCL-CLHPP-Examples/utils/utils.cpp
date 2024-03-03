#include <utils.h>
#include <fstream>
#include <iostream>
#include <sstream>

void printVector(const std::vector<float>& v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

std::string readFile(const std::string& path)
{
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

OpenCLData basicSetup(
    const std::string& platformName,
    const cl_device_type& deviceType,
    const std::string& deviceName,
    const std::string& sourcePath
)
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl::Platform platform;

    for (auto& p : platforms) {
        const std::string& currentPlatformName = p.getInfo<CL_PLATFORM_NAME>();
        if (currentPlatformName == platformName)
        {
            platform = p;
        }
    }

    std::vector<cl::Device> devices;
    platform.getDevices(deviceType, &devices);
    cl::Device device;
    for (auto& d : devices)
    {
        const std::string& currentDeviceName = d.getInfo<CL_DEVICE_NAME>();
        if (deviceName == currentDeviceName)
        {
            std::cout << d.getInfo<CL_DEVICE_NAME>() << std::endl;
            device = d;
        }
    }

    const cl::string& kernelSource = readFile(sourcePath);

    cl::Context context(device);
    cl::Device d = context.getInfo<CL_CONTEXT_DEVICES>()[0];
    std::cout << d.getInfo<CL_DEVICE_NAME>() << std::endl;
    cl::Program program(context, kernelSource);

    auto buildResult = program.build(device);

    if (buildResult != CL_SUCCESS)
    {
        std::cout << "Cannot build program" << std::endl;
        exit(1);
    }

    return OpenCLData{ platform,device,kernelSource,context,program };

}
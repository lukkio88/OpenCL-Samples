#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 300

#include <CL/opencl.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

void printVector(std::vector<float>& v)
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

void printPlatformsAndDevices(
    const std::string& platformName = "NVIDIA CUDA",
    const cl_device_type& deviceType = CL_DEVICE_TYPE_GPU,
    const std::string& deviceName = "GeForce GT 730")
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl::Platform platform;

    for (auto& p : platforms) {
        const std::string& currentPlatformName = p.getInfo<CL_PLATFORM_NAME>();
        if (currentPlatformName == platformName)
        {
            std::cout << p.getInfo<CL_PLATFORM_NAME>() << std::endl;
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

    const cl::string& kernelSource = readFile(CL_KERNEL_PATH + std::string("/v2scalar.cl"));

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

    const int DIM = 8;
	std::vector<float> x;
    x.reserve(DIM);
    for (int i = 0; i < DIM; ++i)
    {
        x.push_back(i + 1);
    }

    cl::Buffer xBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * DIM * 2);
    cl::Buffer tmpBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * DIM * 2);
    std::vector<cl::Kernel> kernel = {
        cl::Kernel(program,"calculateSum"),
        cl::Kernel(program,"maxArray"),
        cl::Kernel(program,"minArray")
    };
    
    for (int i = 0; i < kernel.size(); ++i)
    {
        kernel[i].setArg(0, xBuffer);
        kernel[i].setArg(1, tmpBuffer);
    }

    cl::CommandQueue queue(context, device, cl::QueueProperties::Profiling);
    queue.enqueueWriteBuffer(xBuffer, CL_TRUE, 0, sizeof(float) * DIM, x.data());

    for (int i = 0; i < kernel.size(); ++i)
    {
        queue.enqueueNDRangeKernel(kernel[i], cl::NullRange, cl::NDRange(DIM));
        queue.finish();
        queue.flush();
        float result;
        queue.enqueueReadBuffer(tmpBuffer, CL_TRUE, 0, sizeof(float), &result);
        std::cout << result << " ";
    }
    std::cout << std::endl;

}

int main(int argc, char** argv)
{
    printPlatformsAndDevices();
}
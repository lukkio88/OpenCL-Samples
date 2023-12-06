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

    const cl::string& kernelSource = readFile(CL_KERNEL_PATH + std::string("/vadd.cl"));

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

    int DIM = 4;
    cl::Buffer aBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * DIM);
    cl::Buffer bBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * DIM);
    cl::Buffer cBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * DIM);

    std::vector<float> a{1.0,2.0,3.0,4.0};
    std::vector<float> b{ 4.0,3.0,2.0,1.0 };
    std::vector<float> c(DIM);

    cl::Kernel kernel(program, "vadd");
    kernel.setArg(0, aBuffer);
    kernel.setArg(1, bBuffer);
    kernel.setArg(2, cBuffer);

    cl::CommandQueue queue(context, device, cl::QueueProperties::Profiling);
    queue.enqueueWriteBuffer(aBuffer, CL_TRUE, 0, sizeof(float) * DIM, a.data());
    queue.enqueueWriteBuffer(bBuffer, CL_TRUE, 0, sizeof(float) * DIM, b.data());

    queue.enqueueNDRangeKernel(kernel,cl::NullRange,cl::NDRange(DIM));
    queue.finish();
    queue.flush();

    queue.enqueueReadBuffer(cBuffer, CL_TRUE, 0, sizeof(float) * DIM, c.data());

    printVector(a);
    printVector(b);
    printVector(c);
}

int main(int argc, char** argv)
{
    printPlatformsAndDevices();
}
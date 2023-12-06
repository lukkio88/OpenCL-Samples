#include <iostream>
#include <fstream>
#include <sstream>
#include <utils.h>

void vec2ScalarExample(
    const std::string& platformName = "NVIDIA CUDA",
    const cl_device_type& deviceType = CL_DEVICE_TYPE_GPU,
    const std::string& deviceName = "GeForce GT 730")
{

    OpenCLData setupData = basicSetup(
        platformName, 
        deviceType, 
        deviceName, 
        CL_KERNEL_PATH + std::string("/v2scalar.cl")
    );

    const int DIM = 8;
	std::vector<float> x;
    x.reserve(DIM);
    for (int i = 0; i < DIM; ++i)
    {
        x.push_back(i + 1);
    }

    cl::Buffer xBuffer(setupData.context, CL_MEM_READ_ONLY, sizeof(float) * DIM * 2);
    cl::Buffer tmpBuffer(setupData.context, CL_MEM_READ_WRITE, sizeof(float) * DIM * 2);
    std::vector<cl::Kernel> kernel = {
        cl::Kernel(setupData.program,"calculateSum"),
        cl::Kernel(setupData.program,"maxArray"),
        cl::Kernel(setupData.program,"minArray")
    };
    
    for (int i = 0; i < kernel.size(); ++i)
    {
        kernel[i].setArg(0, xBuffer);
        kernel[i].setArg(1, tmpBuffer);
    }

    cl::CommandQueue queue(setupData.context, setupData.device, cl::QueueProperties::Profiling);
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
    vec2ScalarExample();
    return 0;
}
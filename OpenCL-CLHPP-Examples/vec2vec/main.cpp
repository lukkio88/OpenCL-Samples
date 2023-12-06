#include <utils.h>

void vec2vecExample(
    const std::string& platformName = "NVIDIA CUDA",
    const cl_device_type& deviceType = CL_DEVICE_TYPE_GPU,
    const std::string& deviceName = "GeForce GT 730")
{
    
    OpenCLData setupData = basicSetup(
        platformName,
        deviceType,
        deviceName,
        CL_KERNEL_PATH + std::string("/vadd.cl")
    );

    const int DIM = 4;
    cl::Buffer aBuffer(setupData.context, CL_MEM_READ_ONLY, sizeof(float) * DIM);
    cl::Buffer bBuffer(setupData.context, CL_MEM_READ_ONLY, sizeof(float) * DIM);
    cl::Buffer cBuffer(setupData.context, CL_MEM_WRITE_ONLY, sizeof(float) * DIM);

    std::vector<float> a{1.0,2.0,3.0,4.0};
    std::vector<float> b{ 4.0,3.0,2.0,1.0 };
    std::vector<float> c(DIM);

    cl::Kernel kernel = cl::Kernel(setupData.program, "vadd");
    kernel.setArg(0, aBuffer);
    kernel.setArg(1, bBuffer);
    kernel.setArg(2, cBuffer);

    cl::CommandQueue queue(setupData.context, setupData.device, cl::QueueProperties::Profiling);
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
    vec2vecExample();
    return 0;
}
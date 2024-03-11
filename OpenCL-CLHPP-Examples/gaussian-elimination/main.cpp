#include <iostream>
#include <fstream>
#include <sstream>
#include <utils.h>

void gaussEliminationExample(
    const std::string& platformName = "Intel(R) OpenCL HD Graphics",
    const cl_device_type& deviceType = CL_DEVICE_TYPE_GPU,
    const std::string& deviceName = "Intel(R) Iris(R) Xe Graphics")
{

    OpenCLData setupData = basicSetup(
        platformName,
        deviceType,
        deviceName,
        CL_KERNEL_PATH + std::string("/gaussElimination.cl")
    );

    const int ORDER_MATRIX = 4;
    const int NUMBER_OF_ENTRIES = ORDER_MATRIX * ORDER_MATRIX;
    std::vector<float> A = {
        2, 5, 0, 8,
        1, 4, 2, 6,
        7, 8, 9, 3,
        1, 5, 7, 8
    };
    int initIteration = 0;

    cl::Buffer ABuffer(setupData.context, CL_MEM_READ_WRITE, sizeof(float) * NUMBER_OF_ENTRIES);
    cl::Buffer iteration(setupData.context, CL_MEM_READ_WRITE, sizeof(int));
    cl::Buffer orderOfMatrix(setupData.context, CL_MEM_READ_ONLY, sizeof(int));
    cl::Kernel gaussKernel = cl::Kernel(setupData.program, "gaussElimination");

    gaussKernel.setArg(0, ABuffer);
    gaussKernel.setArg(1, iteration);
    gaussKernel.setArg(2, orderOfMatrix);

    cl::CommandQueue queue(setupData.context, setupData.device, cl::QueueProperties::Profiling);
    queue.enqueueWriteBuffer(iteration, CL_TRUE, 0, sizeof(int), &initIteration);
    queue.enqueueWriteBuffer(orderOfMatrix, CL_TRUE, 0, sizeof(int), &ORDER_MATRIX);
    queue.enqueueWriteBuffer(ABuffer, CL_TRUE, 0, sizeof(float) * NUMBER_OF_ENTRIES, A.data());

    std::vector<cl::Event> events;

    for (int i = 1; i < ORDER_MATRIX; ++i)
    {
        cl::Event newEvent;
        queue.enqueueNDRangeKernel(
            gaussKernel, 0, cl::NullRange, 
            cl::NDRange{ cl::size_type(ORDER_MATRIX - i), cl::size_type(ORDER_MATRIX - i + 1) },
            &events, &events[0]);
    }
   
    
    queue.finish();
    queue.flush();
    queue.enqueueReadBuffer(ABuffer, CL_TRUE, 0, sizeof(float) * NUMBER_OF_ENTRIES, A.data());
    
    for (int i = 0; i < ORDER_MATRIX; ++i)
    {
        for (int j = 0; j < ORDER_MATRIX; ++j)
        {
            std::cout << A[i * ORDER_MATRIX + j] << ", ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv)
{
    gaussEliminationExample();
    return 0;
}
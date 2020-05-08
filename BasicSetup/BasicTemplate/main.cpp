#include <CL/cl.h>
#include <cstdio>
#include <cstring>

/*
 * Simplest openCL program that execute a simple kernel for vector addition using GPU
 * This example is mostly written in C style, there's no error checking because the focus
 * is on the basic structure of a OpenCL program.
*/

cl_int basicProgram(
        double * inputA,
        double * inputB,
        double * output,
        int vectorSize, //this is common for A,B and output
        const char * platformName = "NVIDIA CUDA",
        cl_device_type deviceType = CL_DEVICE_TYPE_GPU,
        const char * deviceName = "GeForce GTX 1070")
{
    //Selecting the platform and device
    cl_uint numPlatforms;
    cl_int error = clGetPlatformIDs(0,nullptr,&numPlatforms);

    cl_platform_id *platform = new cl_platform_id[numPlatforms];
    error = clGetPlatformIDs(numPlatforms,platform,nullptr);

    int platformIdx;
    for(platformIdx = 0; platformIdx < numPlatforms; ++platformIdx)
    {
        char * currentPlatformName;
        size_t size;
        error = clGetPlatformInfo(platform[platformIdx],CL_PLATFORM_NAME,0,nullptr,&size);
        currentPlatformName = new char[size];
        error = clGetPlatformInfo(platform[platformIdx],CL_PLATFORM_NAME,size,currentPlatformName,nullptr);

        if(strcmp(currentPlatformName,platformName) == 0)
        {
            delete [] currentPlatformName;
            break;
        }
        delete [] currentPlatformName;

    }

    if(platformIdx == numPlatforms)
    {
        printf("Could not find platform %s\n",platformName);
    }
    else
    {
        printf("Platform %s found\n",platformName);
    }

    cl_platform_id platformId = platform[platformIdx];
    delete[] platform;

    cl_device_id * device;
    cl_uint numDevices;
    error = clGetDeviceIDs(platformId,deviceType,0,nullptr,&numDevices);
    device = new cl_device_id[numDevices];
    error = clGetDeviceIDs(platformId,deviceType,numDevices,device,nullptr);

    int deviceIdx;
    for(deviceIdx = 0; deviceIdx < numDevices; ++deviceIdx)
    {
        char * currentDeviceName;
        size_t size;
        error = clGetDeviceInfo(device[deviceIdx],CL_DEVICE_NAME,0,nullptr,&size);
        currentDeviceName = new char[size];
        error = clGetDeviceInfo(device[deviceIdx],CL_DEVICE_NAME,size,currentDeviceName,nullptr);
        if(strcmp(currentDeviceName,deviceName) == 0)
        {
            delete [] currentDeviceName;
            break;
        }
        delete [] currentDeviceName;
    }

    if(deviceIdx == numDevices)
    {
        printf("Cannot find device %s\n",deviceName);
    }
    else
    {
        printf("Device %s found\n",deviceName);
    }

    cl_device_id deviceId = device[deviceIdx];
    delete []device;

    //Creating context and command queue
    cl_context context = clCreateContext(nullptr,1,&deviceId,nullptr,nullptr,&error);
    cl_command_queue commandQueue = clCreateCommandQueue(context,deviceId,0,&error);

    //Create program, build and create kernel
    const char * programSource =
            "__kernel void vecAdd(\n"
            "       __global double * inputA,\n"
            "       __global double * inputB,\n"
            "       __global double * outputC) {\n"
            "    size_t idx = get_global_id(0);\n"
            "   outputC[idx] = inputA[idx] + inputB[idx];\n"
            "}";
    const size_t sourceLength = strlen(programSource);
    cl_program program = clCreateProgramWithSource(context,1,&programSource,&sourceLength,&error);
    error = clBuildProgram(program,1,&deviceId,nullptr,nullptr,nullptr);
    cl_kernel kernel = clCreateKernel(program,"vecAdd",&error);

    //Create input and output clBuffers
    cl_mem mem_A = clCreateBuffer(context,CL_MEM_READ_ONLY,vectorSize*sizeof(double),inputA,&error);
    cl_mem mem_B = clCreateBuffer(context,CL_MEM_READ_ONLY,vectorSize*sizeof(double),inputB,&error);
    cl_mem mem_C = clCreateBuffer(context,CL_MEM_READ_WRITE,vectorSize*sizeof(double),output,&error);
    clEnqueueWriteBuffer(commandQueue,mem_A,CL_TRUE,0,vectorSize*sizeof(double),inputA,0,nullptr,nullptr);
    clEnqueueWriteBuffer(commandQueue,mem_B,CL_TRUE,0,vectorSize*sizeof(double),inputB,0,nullptr,nullptr);

    clFinish(commandQueue);

    //Setting kernel argument and NDRange
    clSetKernelArg(kernel,0,sizeof(cl_mem),&mem_A);
    clSetKernelArg(kernel,1,sizeof(cl_mem),&mem_B);
    clSetKernelArg(kernel,2,sizeof(cl_mem),&mem_C);

    const size_t globalWorkSize = vectorSize;
    clEnqueueNDRangeKernel(commandQueue,kernel,1,nullptr,&globalWorkSize,nullptr,0,nullptr,nullptr);

    clEnqueueReadBuffer(commandQueue,mem_C,CL_TRUE,0,vectorSize*sizeof(double),output,0,nullptr,nullptr);

    clFinish(commandQueue);

    //Teardown
    clReleaseCommandQueue(commandQueue);
    clReleaseContext(context);

}

int main(int argc, char** argv)
{

    double arrayA[] = {1.0,2.0,3.0,4.0,5.0};
    double arrayB[] = {5.0,4.0,3.0,2.0,1.0};
    double arrayC[] = {0.0,0.0,0.0,0.0,0.0};
    int numberOfElements = 5;

    basicProgram(arrayA,arrayB,arrayC,numberOfElements);

    for(int i = 0; i < numberOfElements; ++i)
    {
        printf("%f + %f = %f\n",arrayA[i],arrayB[i],arrayC[i]);
    }
    return 0;
}
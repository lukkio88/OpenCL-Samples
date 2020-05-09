#include <CL/cl.h>
#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <algorithm>

//Getting platform, device, context and command queue
void setup(
        cl_platform_id &platformId, cl_device_id &deviceId, cl_context& context, cl_command_queue& commandQueue,
        std::string platformName = "NVIDIA CUDA",  cl_device_type deviceType = CL_DEVICE_TYPE_GPU,
        std::string deviceName = "GeForce GTX 1070")
{

    using std::vector;
    using std::string;
    using std::cout;
    using std::endl;

    cl_uint numberOfPlatforms, numberOfDevices;
    cl_int error;

    //Finding platform id
    error = clGetPlatformIDs(0,nullptr,&numberOfPlatforms);
    vector<cl_platform_id> platform(numberOfPlatforms);
    error = clGetPlatformIDs(numberOfPlatforms,platform.data(),nullptr);

    for(const auto & currentPlatform : platform)
    {
        size_t stringSize;
        error = clGetPlatformInfo(currentPlatform,CL_PLATFORM_NAME,0,nullptr,&stringSize);
        char * currentPlatformName = new char[stringSize];
        error = clGetPlatformInfo(currentPlatform,CL_PLATFORM_NAME,stringSize,currentPlatformName,nullptr);
        if(string(currentPlatformName).compare(platformName) == 0)
        {
            cout << "Platform " << platformName << " found!" << endl;
            delete [] currentPlatformName;
            platformId = currentPlatform;
            break;
        }
        delete [] currentPlatformName;
    }

    error = clGetDeviceIDs(platformId,deviceType,0,nullptr,&numberOfDevices);
    vector<cl_device_id> device(numberOfDevices);
    error = clGetDeviceIDs(platformId,deviceType,numberOfDevices,device.data(),nullptr);

    for(const auto & currentDevice : device)
    {
        size_t stringSize;
        error = clGetDeviceInfo(currentDevice,CL_DEVICE_NAME,0,nullptr,&stringSize);
        char * currentDeviceName = new char[stringSize];
        error = clGetDeviceInfo(currentDevice,CL_DEVICE_NAME,stringSize,currentDeviceName,nullptr);

        if(string(currentDeviceName).compare(deviceName) == 0)
        {
            cout << "Device " << deviceName << " found!" << endl;
            delete [] currentDeviceName;
            deviceId = currentDevice;
            break;
        }
        delete [] currentDeviceName;
    }

    context = clCreateContext(nullptr,1,&deviceId,nullptr,nullptr,&error);
    commandQueue = clCreateCommandQueue(context,deviceId,0,&error);

}

void run(const std::string & imagePath, const std::string& programSource, const cl_device_id deviceId,
        const cl_context& context, const cl_command_queue& commandQueue, int histogram[256])
{
    cl_int error;
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load(imagePath.c_str(),
                                     &width,
                                     &height,
                                     &channels,
                                     STBI_grey);

    unsigned char min = 255;
    unsigned char max = 0;
    for(int i = 0; i < width*height; ++i)
    {
        min = (image[i] < min) ? image[i]:min;
        max = (image[i] > max) ? image[i]:max;
    }

    std::cout << "(min, max) := (" << static_cast<int>(min) << ", " << static_cast<int>(max) << ")" << std::endl;

    //create buffers
    cl_mem memImage = clCreateBuffer(context,CL_MEM_READ_ONLY,width*height*sizeof(unsigned char),image,&error);
    cl_mem memHistogram = clCreateBuffer(context,CL_MEM_READ_WRITE,256*sizeof(int),&histogram,&error);

    //Create program, kernel and setting kernel args
    size_t programSize = programSource.length();
    const char * source = programSource.c_str();
    cl_program program = clCreateProgramWithSource(context,1,&source,&programSize,&error);
    error = clBuildProgram(program,1,&deviceId,nullptr,nullptr,nullptr);
    cl_kernel kernel = clCreateKernel(program,"computeHistogram",&error);

    error = clEnqueueWriteBuffer(commandQueue,memImage,CL_TRUE,0,width*height*sizeof(unsigned char),image,0,nullptr,nullptr);

    error = clSetKernelArg(kernel,0,sizeof(cl_mem),&memImage);
    error = clSetKernelArg(kernel,1,sizeof(cl_mem),&memHistogram);

    clFinish(commandQueue);

    const size_t globalWorkSize = width*height;
    error = clEnqueueNDRangeKernel(commandQueue,kernel,1,nullptr,&globalWorkSize,nullptr,0,nullptr,nullptr);

    error = clEnqueueReadBuffer(commandQueue,memHistogram,CL_TRUE,0,256*sizeof(int),histogram,0,nullptr,nullptr);

    clFinish(commandQueue);
    clReleaseCommandQueue(commandQueue);
    clReleaseContext(context);

}

int main(int argc, char** argv)
{
    cl_platform_id platformId;
    cl_device_id deviceId;
    cl_context context;
    cl_command_queue commandQueue;
    setup(platformId,deviceId,context,commandQueue);

    std::string filename = "gray.jpeg";
    std::string programSource =
            "__kernel void computeHistogram(\n"
            " __global unsigned char * image, __global int * histogram)\n"
            "{\n"
            "   size_t idx = get_global_id(0);\n"
            "   unsigned char pixelValue = image[idx];\n"
            "   atomic_inc(&histogram[pixelValue]);\n"
            "   barrier(CLK_GLOBAL_MEM_FENCE);"
            "}\n";

    int histogram[256] = {0};

    run(filename,programSource, deviceId, context, commandQueue,histogram);

    std::cout << "histogram = [";
    int i;
    for(i = 0; i < 255; ++i)
    {
        std::cout << histogram[i] << ", ";
    }
    std::cout << histogram[i] << "];" << std::endl;

    return 0;
}
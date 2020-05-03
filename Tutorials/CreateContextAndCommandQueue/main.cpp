#include <CL/cl.h>
#include <iostream>
#include <vector>

inline const char* TranslateOpenCLError(cl_int errorCode)
{
    switch (errorCode)
    {
        case CL_SUCCESS:                            return "CL_SUCCESS";
        case CL_DEVICE_NOT_FOUND:                   return "CL_DEVICE_NOT_FOUND";
        case CL_DEVICE_NOT_AVAILABLE:               return "CL_DEVICE_NOT_AVAILABLE";
        case CL_COMPILER_NOT_AVAILABLE:             return "CL_COMPILER_NOT_AVAILABLE";
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:      return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
        case CL_OUT_OF_RESOURCES:                   return "CL_OUT_OF_RESOURCES";
        case CL_OUT_OF_HOST_MEMORY:                 return "CL_OUT_OF_HOST_MEMORY";
        case CL_PROFILING_INFO_NOT_AVAILABLE:       return "CL_PROFILING_INFO_NOT_AVAILABLE";
        case CL_MEM_COPY_OVERLAP:                   return "CL_MEM_COPY_OVERLAP";
        case CL_IMAGE_FORMAT_MISMATCH:              return "CL_IMAGE_FORMAT_MISMATCH";
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:         return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
        case CL_BUILD_PROGRAM_FAILURE:              return "CL_BUILD_PROGRAM_FAILURE";
        case CL_MAP_FAILURE:                        return "CL_MAP_FAILURE";
        case CL_MISALIGNED_SUB_BUFFER_OFFSET:       return "CL_MISALIGNED_SUB_BUFFER_OFFSET";                          //-13
        case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:    return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";   //-14
        case CL_COMPILE_PROGRAM_FAILURE:            return "CL_COMPILE_PROGRAM_FAILURE";                               //-15
        case CL_LINKER_NOT_AVAILABLE:               return "CL_LINKER_NOT_AVAILABLE";                                  //-16
        case CL_LINK_PROGRAM_FAILURE:               return "CL_LINK_PROGRAM_FAILURE";                                  //-17
        case CL_DEVICE_PARTITION_FAILED:            return "CL_DEVICE_PARTITION_FAILED";                               //-18
        case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:      return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";                         //-19
        case CL_INVALID_VALUE:                      return "CL_INVALID_VALUE";
        case CL_INVALID_DEVICE_TYPE:                return "CL_INVALID_DEVICE_TYPE";
        case CL_INVALID_PLATFORM:                   return "CL_INVALID_PLATFORM";
        case CL_INVALID_DEVICE:                     return "CL_INVALID_DEVICE";
        case CL_INVALID_CONTEXT:                    return "CL_INVALID_CONTEXT";
        case CL_INVALID_QUEUE_PROPERTIES:           return "CL_INVALID_QUEUE_PROPERTIES";
        case CL_INVALID_COMMAND_QUEUE:              return "CL_INVALID_COMMAND_QUEUE";
        case CL_INVALID_HOST_PTR:                   return "CL_INVALID_HOST_PTR";
        case CL_INVALID_MEM_OBJECT:                 return "CL_INVALID_MEM_OBJECT";
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:    return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
        case CL_INVALID_IMAGE_SIZE:                 return "CL_INVALID_IMAGE_SIZE";
        case CL_INVALID_SAMPLER:                    return "CL_INVALID_SAMPLER";
        case CL_INVALID_BINARY:                     return "CL_INVALID_BINARY";
        case CL_INVALID_BUILD_OPTIONS:              return "CL_INVALID_BUILD_OPTIONS";
        case CL_INVALID_PROGRAM:                    return "CL_INVALID_PROGRAM";
        case CL_INVALID_PROGRAM_EXECUTABLE:         return "CL_INVALID_PROGRAM_EXECUTABLE";
        case CL_INVALID_KERNEL_NAME:                return "CL_INVALID_KERNEL_NAME";
        case CL_INVALID_KERNEL_DEFINITION:          return "CL_INVALID_KERNEL_DEFINITION";
        case CL_INVALID_KERNEL:                     return "CL_INVALID_KERNEL";
        case CL_INVALID_ARG_INDEX:                  return "CL_INVALID_ARG_INDEX";
        case CL_INVALID_ARG_VALUE:                  return "CL_INVALID_ARG_VALUE";
        case CL_INVALID_ARG_SIZE:                   return "CL_INVALID_ARG_SIZE";
        case CL_INVALID_KERNEL_ARGS:                return "CL_INVALID_KERNEL_ARGS";
        case CL_INVALID_WORK_DIMENSION:             return "CL_INVALID_WORK_DIMENSION";
        case CL_INVALID_WORK_GROUP_SIZE:            return "CL_INVALID_WORK_GROUP_SIZE";
        case CL_INVALID_WORK_ITEM_SIZE:             return "CL_INVALID_WORK_ITEM_SIZE";
        case CL_INVALID_GLOBAL_OFFSET:              return "CL_INVALID_GLOBAL_OFFSET";
        case CL_INVALID_EVENT_WAIT_LIST:            return "CL_INVALID_EVENT_WAIT_LIST";
        case CL_INVALID_EVENT:                      return "CL_INVALID_EVENT";
        case CL_INVALID_OPERATION:                  return "CL_INVALID_OPERATION";
        case CL_INVALID_GL_OBJECT:                  return "CL_INVALID_GL_OBJECT";
        case CL_INVALID_BUFFER_SIZE:                return "CL_INVALID_BUFFER_SIZE";
        case CL_INVALID_MIP_LEVEL:                  return "CL_INVALID_MIP_LEVEL";
        case CL_INVALID_GLOBAL_WORK_SIZE:           return "CL_INVALID_GLOBAL_WORK_SIZE";                           //-63
        case CL_INVALID_PROPERTY:                   return "CL_INVALID_PROPERTY";                                   //-64
        case CL_INVALID_IMAGE_DESCRIPTOR:           return "CL_INVALID_IMAGE_DESCRIPTOR";                           //-65
        case CL_INVALID_COMPILER_OPTIONS:           return "CL_INVALID_COMPILER_OPTIONS";                           //-66
        case CL_INVALID_LINKER_OPTIONS:             return "CL_INVALID_LINKER_OPTIONS";                             //-67
        case CL_INVALID_DEVICE_PARTITION_COUNT:     return "CL_INVALID_DEVICE_PARTITION_COUNT";                     //-68
            //    case CL_INVALID_PIPE_SIZE:                  return "CL_INVALID_PIPE_SIZE";                                  //-69
            //    case CL_INVALID_DEVICE_QUEUE:               return "CL_INVALID_DEVICE_QUEUE";                               //-70
        default:
            return "UNKNOWN ERROR CODE";
    }

}

bool checkError(cl_int error, const std::string errorString)
{
    if(error != CL_SUCCESS)
    {
        std::cout << errorString << std::endl;
        return false;
    }
    return true;
}

cl_int findPlatform(cl_platform_id& outPlatformId, const std::string & inPlatformVendor = "NVIDIA Corporation")
{
    cl_uint numPlatforms;

    cl_int error = clGetPlatformIDs(0,nullptr,&numPlatforms);
    if(error != CL_SUCCESS)
    {
        std::cout << "error : " << std::string(TranslateOpenCLError(error)) << std::endl;
        return error;
    }

    std::cout << "numPlatforms available : " << numPlatforms << std::endl;
    std::vector<cl_platform_id> platform(numPlatforms);

    error = clGetPlatformIDs(numPlatforms,platform.data(),nullptr);

    if(error != CL_SUCCESS)
    {
        std::cout << "error :" << std::string(TranslateOpenCLError(error)) << std::endl;
        return error;
    }

    for(const auto & id : platform)
    {
        size_t strLen;
        error = clGetPlatformInfo(id,CL_PLATFORM_NAME,0,nullptr,&strLen);
        if(error != CL_SUCCESS)
        {
            std::cout << "Error quering platform name" << std::endl;
            return error;
        }
        std::vector<char> string(strLen);
        error = clGetPlatformInfo(id,CL_PLATFORM_NAME,strLen,string.data(),nullptr);

        if(error != CL_SUCCESS)
        {
            std::cout << "Error printing platform name : " << std::string(TranslateOpenCLError(error)) << std::endl;
        }

        std::string platformName(string.data());

        error = clGetPlatformInfo(id,CL_PLATFORM_VENDOR,0,nullptr,&strLen);

        if(error != CL_SUCCESS)
        {
            std::cout << "Error finding platform vendor" << std::string(TranslateOpenCLError(error)) << std::endl;
        }

        string.resize(strLen);
        error = clGetPlatformInfo(id,CL_PLATFORM_VENDOR,strLen,string.data(),nullptr);

        std::string platformVendor(string.data());

        error = clGetPlatformInfo(id,CL_PLATFORM_VERSION,0,nullptr,&strLen);

        if(error != CL_SUCCESS)
        {
            std::cout << "Error finding platform version" << std::string(TranslateOpenCLError(error)) << std::endl;
        }

        string.resize(strLen);
        error = clGetPlatformInfo(id,CL_PLATFORM_VERSION,strLen,string.data(),nullptr);

        std::string platformVersion(string.data());

        std::cout << "Platform name : " << platformName << std::endl;
        std::cout << "Platform vendor : " << platformVendor << std::endl;
        std::cout << "Platform version : " << platformVersion << std::endl;

        if(platformVendor == inPlatformVendor)
        {
            outPlatformId = id;
        }

        std::cout << std::endl;

    }

    return error;

}

cl_int findDevice(cl_platform_id platformId, cl_device_id& outDeviceId)
{
    cl_uint numDevices;
    cl_int error;

    error = clGetDeviceIDs(platformId,CL_DEVICE_TYPE_GPU,0,nullptr,&numDevices);
    if(error != CL_SUCCESS)
    {
        std::cout << "Error when getting device id : " << TranslateOpenCLError(error) << std::endl;
        return error;
    }

    std::vector<cl_device_id> deviceId(numDevices);
    error = clGetDeviceIDs(platformId,CL_DEVICE_TYPE_GPU,numDevices,deviceId.data(),nullptr);

    if(error != CL_SUCCESS)
    {
        std::cout << "Error when getting device id : " << TranslateOpenCLError(error) << std::endl;
        return error;
    }

    for(const auto & id : deviceId)
    {

        size_t sizeStr;
        std::vector<char> string;

        error = clGetDeviceInfo(id,CL_DEVICE_NAME,0,nullptr,&sizeStr);
        if(error != CL_SUCCESS)
        {
            std::cout << "Error when quering device name : " << TranslateOpenCLError(error) << std::endl;
            return error;
        }

        string.resize(sizeStr);
        error = clGetDeviceInfo(id,CL_DEVICE_NAME,sizeStr,string.data(),nullptr);

        if(error != CL_SUCCESS)
        {
            std::cout << "Error when quering device name : " << TranslateOpenCLError(error) << std::endl;
            return error;
        }

        std::string deviceName(string.data());
        std::cout << "Device name : " <<  deviceName << std::endl;

        //Work group size
        size_t size;
        error = clGetDeviceInfo(id,CL_DEVICE_MAX_WORK_GROUP_SIZE,sizeof(size_t),&size,nullptr);
        if(error != CL_SUCCESS)
        {
            std::cout << "Error when quering max work group size : " << TranslateOpenCLError(error) << std::endl;
            return error;
        }
        std::cout << "Max work group size : " << size << std::endl;

        std::vector<size_t> workItemSizes(3);
        error = clGetDeviceInfo(id,CL_DEVICE_MAX_WORK_ITEM_SIZES,3*sizeof(size_t),workItemSizes.data(),nullptr);

        if(error != CL_SUCCESS)
        {
            std::cout << "Error when quering work item size : " << TranslateOpenCLError(error) << std::endl;
            return error;
        }

        std::cout << "Max work item size : (" << workItemSizes[0] << ", " << workItemSizes[1] << ", "
                  << workItemSizes[2] << ")" << std::endl;

        cl_uint dimension;
        error = clGetDeviceInfo(id,CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,sizeof(cl_uint),&dimension,nullptr);
        if(error != CL_SUCCESS)
        {
            std::cout << "Error when quering work item dimension : " << TranslateOpenCLError(error) << std::endl;
            return error;
        }

        outDeviceId = id;
        std::cout << "Max work item dimension : " << dimension << std::endl;
    }

}

cl_int createContextAndCommandQueue(cl_device_id deviceId, cl_context& outContext, cl_command_queue& outCommandQueue)
{
    cl_int error;

    outContext = clCreateContext(nullptr,1,&deviceId,nullptr,nullptr,&error);

    if(error != CL_SUCCESS)
    {
        std::cout << "Error when creating command queue" << std::endl;
        return error;
    }

    outCommandQueue = clCreateCommandQueue(outContext,deviceId,0,&error);

    if(error != CL_SUCCESS)
    {
        std::cout << "Error when creating command queue" << std::endl;
    }
}

int main(int argc, char** argv)
{

    cl_platform_id platformId;
    cl_device_id deviceId;
    cl_context context;
    cl_command_queue command_queue;

    findPlatform(platformId,"Intel(R) Corporation");
    findDevice(platformId,deviceId);
    createContextAndCommandQueue(deviceId, context, command_queue);
    return 0;
}
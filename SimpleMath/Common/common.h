//
// Created by l.gagliano on 09/01/20.
//

#ifndef OPENCL_TEST_COMMON_H
#define OPENCL_TEST_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <CL/cl.h>

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

inline void LogError(const char* str, ...)
{
    if (str)
    {
        va_list args;
        //va_start(args, str);

        printf("This is an error");

        //va_end(args);
    }
}

inline bool check_error(cl_uint err, std::string error_message) {
    if (err != CL_SUCCESS) {
        std::cout << error_message << std::endl;
        std::cout << "Error : " << TranslateOpenCLError(err) << std::endl;
        return true;
    }
    return false;
}

int ReadSourceFromFile(const char* fileName, std::string& fileContent, size_t* sourceSize);

/*
 * Split into
 *      Platform
 *      Device
 *      Context
 *      Kernel compilation
 *      Kernel run
 */

struct BufferDescriptor
{
  void * mHostMem;
  cl_uint mType; //such as CL_MEM_READ_ONLY, CL_MEM_READ_WRITE, etc...
  size_t mBufferSize;
  cl_mem mClMem;
};

struct KernelArgDescriptor
{
    cl_mem *mCLMem;
    size_t size;
    cl_uint mType;
};

class OpenCLPipelineManager
{
public:
    OpenCLPipelineManager(cl_int deviceType = CL_DEVICE_TYPE_GPU) {
        initializePlatform();
        initializeDevice(deviceType);
    }

    ~OpenCLPipelineManager() {
        //Teardown
        clReleaseCommandQueue(mCmdQueue);
        clReleaseContext(mContext);
    }

    void initContextAndCommandQueue(std::vector<BufferDescriptor>& bufferDescr)
    {
        //Now I know the device, I can create context and command queue
        mContext = clCreateContext(0, 1, &mDeviceId[mIdxDevice], nullptr, nullptr, nullptr);
        mCmdQueue = clCreateCommandQueue(mContext, mDeviceId[mIdxDevice], 0, nullptr);

        //Let's allocate memory
        for (auto & descriptor : bufferDescr)
        {
            descriptor.mClMem = clCreateBuffer(mContext, descriptor.mType, descriptor.mBufferSize, nullptr, nullptr);
            if (descriptor.mType == CL_MEM_READ_ONLY && check_error(
                    clEnqueueWriteBuffer(mCmdQueue, descriptor.mClMem, CL_TRUE, 0, descriptor.mBufferSize,
                                         descriptor.mHostMem, 0, nullptr, nullptr),
                    "Error in creating clEnqueueWriteBuffer for some cl_mem"))
            {
                exit(1);
            }
        }

        clFinish(mCmdQueue);
    }

    void initProgram(std::string clFilename)
    {
        cl_int err;
        //char* source = NULL;
        std::string source;
        size_t src_size = 0;
        if (check_error(ReadSourceFromFile(clFilename.c_str(), source, &src_size), "Error in ReadSourceFromFile"))
            exit(1);
        const char *cstr_source = source.c_str();
        mProgram[0] = clCreateProgramWithSource(mContext, 1, (const char **) &cstr_source, nullptr,
                                                &err);
        if (check_error(err, "Error in clCreateProgramWithSource"))
            exit(1);
        if (check_error(clBuildProgram(mProgram[0], 1, mDeviceId.data(), nullptr, nullptr, nullptr),
                        "Error in clBuildProgram"))
        {
            // Determine the size of the log
            size_t log_size;
            clGetProgramBuildInfo(mProgram[0], mDeviceId[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

            // Allocate memory for the log
            char *log = (char *) malloc(log_size);

            // Get the log
            clGetProgramBuildInfo(mProgram[0], mDeviceId[0], CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

            // Print the log
            printf("%s\n", log);
            exit(1);
        }
    }

    void initKernelAndRun(std::string kernelName, std::vector<KernelArgDescriptor>& argDescrs, size_t globalWorkSize)
    {
        cl_int err;
        mKernel[0] = clCreateKernel(mProgram[0], kernelName.c_str(), &err);

        if (check_error(err, "Error in clCreateKernel"))
            exit(1);

        //Setting kernel args
        int argIndex = 0;
        for(auto & argDescr : argDescrs)
        {

            if (check_error(clSetKernelArg(mKernel[0], argIndex++, argDescr.size, argDescr.mCLMem),
                            "Error in clSetKernelArg"))
                exit(1);
        }

        if (check_error(clEnqueueNDRangeKernel(mCmdQueue, mKernel[0], 1, nullptr, &globalWorkSize, nullptr, 0, nullptr, nullptr), "Error in clEnqueueNDRangeKernel"))
            exit(1);

        for(auto & argDescr : argDescrs)
        {
            if ((argDescr.mType == CL_MEM_READ_WRITE) && check_error(
                    clEnqueueReadBuffer(mCmdQueue, *(argDescr.mCLMem), CL_TRUE, 0, argDescr.size, &temp_out_val, 0, nullptr,
                                        nullptr), "Error in clEnqueueReadBuffer"))
                exit(1);
        }

        clFinish(mCmdQueue);
    }

private:

    void initializePlatform()
    {

        if (check_error(clGetPlatformIDs(0, nullptr, &mNumPlatforms), "Error in retrieving platforms number"))
            exit(1);

        mPlatform = std::vector<cl_platform_id>(mNumPlatforms);

        if (check_error(clGetPlatformIDs(mNumPlatforms, &mPlatform[0], nullptr), "Error in retrieving platform ID"))
            exit(1);

        //Let's print the platforms
        size_t strLen;
        for (auto i = 0; i < mNumPlatforms; ++i)
        {
            if (check_error(clGetPlatformInfo(mPlatform[i], CL_PLATFORM_NAME, 0, nullptr, &strLen),
                            "Error in first call getPlatformInfo"))
                exit(1);
            mPlatformName = std::vector<char>(strLen);
            if (check_error(clGetPlatformInfo(mPlatform[i], CL_PLATFORM_NAME, strLen, &mPlatformName[0], nullptr),
                            "Error in second call getPlatformInfo"))
                exit(1);
        }
    }

    void initializeDevice(cl_int deviceType = CL_DEVICE_TYPE_GPU)
    {
        mIdxPlatform = 0;
        while (mIdxPlatform < mNumPlatforms) {
            if (!check_error(clGetDeviceIDs(mPlatform[mIdxPlatform], deviceType, 0, nullptr, &mNumDevices), "Error in clGetDeviceIDs loop"))
                break;
            ++mIdxPlatform;
        }

        mDeviceId = std::vector<cl_device_id>(mNumDevices);
        if (check_error(clGetDeviceIDs(mPlatform[mIdxPlatform], deviceType, mNumDevices, &mDeviceId[0], nullptr), "Error in calling clGetDeviceIDs"))
            exit(1);

        //TODO: Check if the lines above should be moved in the "Platform"

        mIdxDevice = 0;
        size_t strLen;
        while (mIdxDevice < mNumDevices) {
            if (!check_error(clGetDeviceInfo(mDeviceId[mIdxDevice], CL_DEVICE_NAME, 0, nullptr, &strLen), "Error in calling clGetDeviceInfo"))
            {
                mDeviceName = std::vector<char>(strLen);
                if (!check_error(clGetDeviceInfo(mDeviceId[mIdxDevice], CL_DEVICE_NAME, strLen, &mDeviceName[0], nullptr), "")) {
                    std::cout << "device[" << mIdxDevice << "] = " << std::string(mDeviceName.data()) << std::endl;
                    break;
                }
            }
            ++mIdxDevice;
        }
    }

public:
    double temp_out_val;

private:
    //For the platform
    cl_uint mNumPlatforms;
    std::vector<cl_platform_id> mPlatform;
    std::vector<char> mPlatformName;

    //For the device
    cl_uint mIdxPlatform;
    cl_uint mIdxDevice;
    cl_uint mNumDevices;
    cl_device_id mDevice;
    std::vector<cl_device_id> mDeviceId;
    std::vector<char> mDeviceName;

    //for context and command queue
    cl_context mContext;
    cl_command_queue mCmdQueue;

    //for the program
    cl_program mProgram[1];

    //for the kernel
    cl_kernel mKernel[1];

};

#endif //OPENCL_TEST_COMMON_H
...
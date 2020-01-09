// Host code

#include <stdio.h>
#include <stdlib.h>
//#include <tchar.h>
#include <memory.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
//#include <Windows.h>
#include <CL/cl.h>

const char* TranslateOpenCLError(cl_int errorCode)
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

void LogError(const char* str, ...)
{
	if (str)
	{
		va_list args;
		//va_start(args, str);

		printf("This is an error");

		//va_end(args);
	}
}

int ReadSourceFromFile(const char* fileName, std::string& fileContent, size_t* sourceSize)
{

	std::fstream kernelFile(fileName);
	fileContent = std::string (
		(std::istreambuf_iterator<char>(kernelFile)),
		std::istreambuf_iterator<char>()
	);

	return CL_SUCCESS;

}

bool check_error(cl_uint err, std::string error_message) {
	if (err != CL_SUCCESS) {
		std::cout << error_message << std::endl;
		std::cout << "Error : " << TranslateOpenCLError(err) << std::endl;
		return true;
	}
	return false;
}

//The functions above can be re-factored

bool runCL(double * a, double * b, double * c, const int & n) {

	cl_int err;
	cl_uint numEntries;
	cl_uint numPlatforms;

	err = clGetPlatformIDs(0, nullptr, &numPlatforms);
	//check err
	std::vector<cl_platform_id> platform(numPlatforms);
	err = clGetPlatformIDs(numPlatforms, &platform[0], nullptr);

	//Let's print the platforms
	size_t strLen;
	for (auto i = 0; i < numPlatforms; ++i) {
		if (check_error(clGetPlatformInfo(platform[i], CL_PLATFORM_NAME, 0, nullptr, &strLen), "Error in first call getPlatformInfo"))
			return true;
		//Check err
		std::vector<char> platformName(strLen);
		if (check_error(clGetPlatformInfo(platform[i], CL_PLATFORM_NAME, strLen, &platformName[0], nullptr), "Error in second call getPlatformInfo"))
			return true;
	}

	//We now know what the platforms are let's pick a specific device

	cl_uint numDevices;
	cl_device_id device;

	cl_uint idx_platform = 0;
	while (idx_platform < numPlatforms) {
		if (!check_error(clGetDeviceIDs(platform[idx_platform], CL_DEVICE_TYPE_GPU, 0, nullptr, &numDevices), "Error in clGetDeviceIDs loop"))
			break;
		++idx_platform;
	}

	std::vector<cl_device_id> deviceId(numDevices);
	if (check_error(clGetDeviceIDs(platform[idx_platform], CL_DEVICE_TYPE_GPU, numDevices, &deviceId[0], nullptr), "Error in calling clGetDeviceIDs"))
		return true;

	cl_uint idx_device = 0;
	while (idx_device < numDevices) {
		if (!check_error(clGetDeviceInfo(deviceId[idx_device], CL_DEVICE_NAME, 0, nullptr, &strLen), "Error in calling clGetDeviceInfo"))
		{
			std::vector<char> deviceName(strLen);
			if (!check_error(clGetDeviceInfo(deviceId[idx_device], CL_DEVICE_NAME, strLen, &deviceName[0], nullptr), "")) {
				std::cout << "device[" << idx_device << "] = " << std::string(deviceName.data()) << std::endl;
				break;
			}
		}
		++idx_device;
	}

	//Now I know the device, I can create context and command queue
	cl_context context;
	cl_command_queue cmd_queue;

	context = clCreateContext(0, 1, &deviceId[idx_device], nullptr, nullptr, nullptr);
	cmd_queue = clCreateCommandQueue(context, deviceId[idx_device], 0, nullptr);

	//Let's allocate memory
	size_t bufferSize = sizeof(double)*n;
	cl_mem a_mem = clCreateBuffer(context, CL_MEM_READ_ONLY, bufferSize, nullptr, nullptr);
	if (check_error(clEnqueueWriteBuffer(cmd_queue, a_mem, CL_TRUE, 0, bufferSize, (void*)a, 0, nullptr, nullptr), "Error in creating clEnqueueWriteBuffer for a_mem"))
		return true;

	cl_mem b_mem = clCreateBuffer(context, CL_MEM_READ_ONLY, bufferSize, nullptr, nullptr);
	if (check_error(clEnqueueWriteBuffer(cmd_queue, b_mem, CL_TRUE, 0, bufferSize, (void*)b, 0, nullptr, nullptr), "Error in creating clEnqueWriteBuffer for b_mem"))
		return true;

	cl_mem c_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, bufferSize, nullptr, nullptr);

	clFinish(cmd_queue);

	//Now let's create the program (compiling kernels)
	cl_program program[1];
	cl_kernel kernel[1];

	const char * filename = "device.cl";
	//char* source = NULL;
	std::string source;
	size_t src_size = 0;
	if (check_error(ReadSourceFromFile(filename, source, &src_size), "Error in ReadSourceFromFile"))
		return true;
	const char* cstr_source = source.c_str();
	program[0] = clCreateProgramWithSource(context, 1, (const char**)&cstr_source, nullptr, &err);
	if (check_error(err, "Error in clCreateProgramWithSource"))
		return true;
	if (check_error(clBuildProgram(program[0], 1, deviceId.data(), nullptr, nullptr, nullptr), "Error in clBuildProgram")) {
		// Determine the size of the log
		size_t log_size;
		clGetProgramBuildInfo(program[0], deviceId[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

		// Allocate memory for the log
		char *log = (char *)malloc(log_size);

		// Get the log
		clGetProgramBuildInfo(program[0], deviceId[0], CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

		// Print the log
		printf("%s\n", log);
		return true;
	}

	kernel[0] = clCreateKernel(program[0], "vecAdd", &err);

	if (check_error(err, "Error in clCreateKernel"))
		return true;

	//Setting kernel args
	if (check_error(clSetKernelArg(kernel[0], 0, sizeof(cl_mem), &a_mem), "Error in clSetKernelArg for a_mem"))
		return true;
	if (check_error(clSetKernelArg(kernel[0], 1, sizeof(cl_mem), &b_mem), "Error in clSetKernelArg for b_mem"))
		return true;
	if (check_error(clSetKernelArg(kernel[0], 2, sizeof(cl_mem), &c_mem), "Error in clSetKernelArg for c_mem"))
		return true;

	//Actual execution
	size_t globalWorkSize = n;

	if (check_error(clEnqueueNDRangeKernel(cmd_queue, kernel[0], 1, nullptr, &globalWorkSize, nullptr, 0, nullptr, nullptr), "Error in clEnqueueNDRangeKernel"))
		return true;

	if (check_error(clEnqueueReadBuffer(cmd_queue, c_mem, CL_TRUE, 0, bufferSize, c, 0, nullptr, nullptr), "Error in clEnqueueReadBuffer"))
		return true;
	clFinish(cmd_queue);

	//Teardown
	clReleaseCommandQueue(cmd_queue);
	clReleaseContext(context);

}

int main(int argc, char **argv) {
	//stuff before running openCL

	const int n = 32;

	std::vector<double> a(n);
	std::vector<double> b(n);
	double * c = new double[n];

	for (auto i = 0; i < n; ++i) {
		a[i] = static_cast<double>(i + 1);
		b[i] = static_cast<double>(n - i - 1);
	}

	runCL(a.data(), b.data(), c, n);

	for(int i = 0; i < n; ++i)
    {
	    std::cout << c[i] << " ";
    }
    std::cout << std::endl;

	return 0;
}
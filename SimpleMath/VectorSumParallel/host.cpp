// Host code
#include "../Common/common.h"

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
#include <CL/opencl.hpp>
#include <iostream>
#include <vector>

//Program to explore all the platforms and devices available

struct OpenCLDescriptor
{
	cl::Platform platform;
	cl::Device device;
};

void printPlatformsAndDevices()
{
	std::vector<cl::Platform> platform;
	cl::Platform::get(&platform);

	for (const auto& currentPlatform : platform)
	{
		std::string platformName = currentPlatform.getInfo<CL_PLATFORM_NAME>().c_str();
		std::cout << "Platform " << platformName << std::endl;
		std::vector<cl::Device> device;
		currentPlatform.getDevices(CL_DEVICE_TYPE_GPU,&device);

		for (const auto& currentDevice : device)
		{
			std::string deviceName = currentDevice.getInfo<CL_DEVICE_NAME>().c_str();
			std::cout << "  Device " << deviceName << std::endl;
		}
	}
}

void setupDescriptor(int argc, char** argv, OpenCLDescriptor& descriptor)
{
	std::vector<cl::Platform> platform;
	cl::Platform::get(&platform);

	for (const auto& currentPlatform : platform)
	{
		std::string platformName = currentPlatform.getInfo<CL_PLATFORM_NAME>().c_str();
		if (platformName == argv[1])
		{
			descriptor.platform = currentPlatform;
			break;
		}
	}

	std::vector<cl::Device> device;
	descriptor.platform.getDevices(CL_DEVICE_TYPE_ALL, &device);

	for (const auto& currentDevice : device)
	{
		std::string deviceName = currentDevice.getInfo<CL_DEVICE_NAME>().c_str();
		if (deviceName == argv[2])
		{
			descriptor.device = currentDevice;
			break;
		}
	}
}

std::string kernelSource = 
R"CLC(
__kernel void parallelSum( __global float* a, __global float* b, __global float* c)
{
	size_t id = get_global_id(0);
	c[id] = a[id] + b[id];
}

__kernel void reduceSum( __global float* a)
{
	size_t globalSize = get_global_size(0);
	size_t id = get_global_id(0);
	for(int size = globalSize; size > 0; size /= 2)
	{
		a[id] += a[id + size];
		barrier(CLK_LOCAL_MEM_FENCE);
	}
}
)CLC";

int main(int argc, char** argv)
{

	size_t size = 8;
	std::vector<float> hostA{ 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };
	std::vector<float> hostB{ 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f };
	std::vector<float> hostC(size);


	try {
		OpenCLDescriptor descriptor;
		setupDescriptor(argc, argv, descriptor);

		std::cout << "Chosen platform : " << descriptor.platform.getInfo<CL_PLATFORM_NAME>().c_str() << std::endl;
		std::cout << "Chosen device : " << descriptor.device.getInfo<CL_DEVICE_NAME>().c_str() << std::endl;

		cl::Context context{ descriptor.device };
		cl::CommandQueue commandQueue{ context, descriptor.device };

		cl::Program program{ context, kernelSource };
		program.build();

		cl::Kernel kernelSum{ program,"parallelSum" };
		cl::Kernel kernelReduce{ program, "reduceSum" };

		cl::Buffer aBuffer{ context, CL_MEM_READ_ONLY, size * sizeof(float) };
		cl::Buffer bBuffer{ context, CL_MEM_READ_ONLY, size * sizeof(float) };
		cl::Buffer cBuffer{ context, CL_MEM_READ_WRITE, size * sizeof(float) };

		commandQueue.enqueueWriteBuffer(aBuffer, CL_TRUE, 0, size * sizeof(float), hostA.data());
		commandQueue.enqueueWriteBuffer(bBuffer, CL_TRUE, 0, size * sizeof(float), hostB.data());

		commandQueue.finish();

		kernelSum.setArg(0, aBuffer);
		kernelSum.setArg(1, bBuffer);
		kernelSum.setArg(2, cBuffer);

		commandQueue.enqueueNDRangeKernel(kernelSum, cl::NullRange, cl::NDRange{ size }, cl::NDRange{ size });
		commandQueue.enqueueReadBuffer(cBuffer, CL_TRUE, 0, size * sizeof(float), hostC.data());

		commandQueue.finish();

		kernelReduce.setArg(0, cBuffer);
		commandQueue.enqueueNDRangeKernel(kernelReduce, cl::NullRange, cl::NDRange{ size / 2 }, cl::NDRange{ size / 2 });
		float reduceSum;
		commandQueue.enqueueReadBuffer(cBuffer, CL_TRUE, 0, sizeof(float), &reduceSum);

		commandQueue.finish();


		for (const auto& val : hostC)
		{
			std::cout << val << " ";
		}
		std::cout << std::endl;

		std::cout << reduceSum << std::endl;
	}
	catch (cl::BuildError& e)
	{
		for (const auto& log : e.getBuildLog())
		{
			printf("Build log for device %s:\n",
				log.first.getInfo<CL_DEVICE_NAME>().c_str());
			printf("%s\n", log.second.c_str());
		}
	}
	catch (cl::Error& e)
	{
		printf("OpenCL Error: %s returned %d\n", e.what(), e.err());
	}

	system("pause");
	return 0;
}
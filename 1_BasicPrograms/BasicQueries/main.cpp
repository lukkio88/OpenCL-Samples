#include <CL/opencl.hpp>
#include <iostream>
#include <vector>

//Program to explore all the platforms and devices available

int main(int argc, char** argv)
{

	std::vector<cl::Platform> platform;
	cl::Platform::get(&platform);

	for (const auto& currentPlatform : platform)
	{
		std::cout << "Platform " << currentPlatform.getInfo<CL_PLATFORM_NAME>().c_str() << std::endl;
		std::vector<cl::Device> device;
		currentPlatform.getDevices(CL_DEVICE_TYPE_ALL, &device);

		for (const auto& currentDevice : device)
		{
			std::cout << "  Device " << currentDevice.getInfo<CL_DEVICE_NAME>().c_str() << std::endl;
		}
	}

	system("pause");
	return 0;
}
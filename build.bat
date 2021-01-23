@echo off
set rootDirectory=%cd%
set OpenCL-SDK-install=%rootDirectory%\OpenCL-SDK\install
set OpenCL-SDK-build=%rootDirectory%\OpenCL-SDK\build
IF EXIST %OpenCL-SDK-build% (
echo Build folder exists nothing to be done
) ELSE (
if EXIST %OpenCL-SDK-install% (
	rmdir /s/q %OpenCL-SDK-install%
)
echo building OpenCL-SDK
echo %OpenCL-SDK-build%
mkdir %OpenCL-SDK-build%
cd %OpenCL-SDK-build%
cmake ..
cmake --build . --target install --config Release
cd %rootDirectory%
)
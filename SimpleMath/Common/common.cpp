//
// Created by l.gagliano on 09/01/20.
//

#include <common.h>

int ReadSourceFromFile(const char* fileName, std::string& fileContent, size_t* sourceSize)
{

    std::fstream kernelFile(fileName);
    fileContent = std::string (
            (std::istreambuf_iterator<char>(kernelFile)),
            std::istreambuf_iterator<char>()
    );

    return CL_SUCCESS;

}
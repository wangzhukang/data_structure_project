#ifndef folder_H
#define folder_H

#include <iostream>
#include <io.h>
#include <direct.h>
#include "ErrorMessage.hpp"

inline void createfolder(const std::string& folderPath)
{
    if (0 != _access(folderPath.c_str(), 0))
    {
        // if this folder not exist, create a new one.
        if (_mkdir(folderPath.c_str()) == -1)
        {
            std::string message = "Error creating folder ";
            throw ErrorMessage(message + folderPath + " !");
        }
    }
}


#endif

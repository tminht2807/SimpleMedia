#pragma once
#include "File.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class PlayList{
private:
    std::string PlayListName;
    //vector of reference for files
    std::vector<std::shared_ptr<File>> Files;
public:
    PlayList(const std::string& _name);
    
    // method to get a file from vector by index
    std::shared_ptr<File> getFile(int _index);
    
    // method to add a file to the vector
    /**/void addFile(std::shared_ptr<File> _file);

    // method to remove all files from the vector
    /**/void clear_PlayList();

    // method to get Files
    std::vector<std::shared_ptr<File>> get_Files() const { return Files; }

    // method to remove a file from the vector
    /**/void removeFile(int _File_index);

    // method to get the playlist name
    /**/std::string get_PlayList_Name();
};
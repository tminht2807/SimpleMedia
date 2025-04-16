#pragma once
#include "File.hpp"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <filesystem>

class PlayList{
private:
    std::string PlayListName;

    std::vector<std::shared_ptr<File>> List_Files;
public:
    PlayList(const std::string& _name): PlayListName(_name){}
    
    // method to get Files
    std::vector<std::shared_ptr<File>> Get_PlayList() const;

    // method to get a file from vector by index
    std::shared_ptr<File> Get_A_File(int _index);

    // method to get the playlist name
    std::string Get_PlayList_Name();

    std::vector<std::string> Get_List_Names();
    
    // method to add a file to the vector
    void Add_File(std::shared_ptr<File> _file);

    // method to add media files from a directory
    void Add_By_Directory(std::string _directory);

    void Add_By_File_Path(std::string _file_path);

    // method to remove all files from the vector
    void Clear_PlayList();

    // method to remove a file from the vector
    void Remove_File(int _File_index);

    void Set_PlayList_Name(const std::string& _name);
};
#include "PlayList.hpp"

// Constructor to initialize the playlist with a name
PlayList::PlayList(const std::string& _name) : PlayListName(_name) {
    // 
}

// Method to get a file from the vector by index
std::shared_ptr<File> PlayList::getFile(int _index) {
        return Files[_index];
    return nullptr; // Return nullptr if index is out of bounds
}

// Method to add a file to the vector
void PlayList::addFile(std::shared_ptr<File> _file) {
    Files.push_back(_file);
}

// Method to remove all files from the vector
void PlayList::clear_PlayList() {
    Files.clear();
}

// Method to get the playlist name
std::string PlayList::get_PlayList_Name() {
    return PlayListName;
}

// Method to remove a file from the vector
void PlayList::removeFile(int _File_index) {
    Files.erase(Files.begin() + _File_index);
}
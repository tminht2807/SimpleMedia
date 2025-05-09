#include "List.hpp"
#include <filesystem>

// Constructor
List::List(){
    // Initialize the list of playlists
    List_PlayLists = std::vector<std::shared_ptr<PlayList>>();
    // Create a default playlist which name "Current directory: (current directory of folder where the program executed)"
    std::string current_directory = std::filesystem::current_path().string();
    std::string playlist_name = "Current directory: " + current_directory;
    auto defaultPlaylist = std::make_shared<PlayList>(playlist_name);

    // check the current folder and subfolder where the program executed for all media files .mp3 to push back to the List_PlayLists[0]
    for (const auto& entry : std::filesystem::recursive_directory_iterator(current_directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
            std::string file_path = entry.path().string();
            auto file = std::make_shared<File>(file_path);
            defaultPlaylist->Add_File(file);
        }
    }
    // List_Names.push_back(playlist_name);
    List_PlayLists.push_back(defaultPlaylist);
}

// Method to get the list of playlists
std::vector<std::shared_ptr<PlayList>> List::Get_List() const{
    return List_PlayLists;
}

// Return a PlayList of input index
std::shared_ptr<PlayList> List::Get_A_PlayList(int _PlayList_Index) const{
    return List_PlayLists[_PlayList_Index];
}

// Add PlayList name _PlayList_Name to the List_PlayLists
bool List::Add_PlayList(std::string& _PlayList_Name){
    // Check if the playlist name already exists
    for (const auto& playlist : List_PlayLists) {
        if (playlist->Get_PlayList_Name() == _PlayList_Name) {
            return false;
        }
    }

    // Create a new playlist and add it to the list
    auto newPlaylist = std::make_shared<PlayList>(_PlayList_Name);
    // List_Names.push_back(_PlayList_Name);
    List_PlayLists.push_back(newPlaylist);
    return true;
}

// delete the PlayList: List_PlayLists[_PlayList_index]
void List::Remove_PlayList(size_t _PlayList_index){
    List_PlayLists.erase(List_PlayLists.begin() + _PlayList_index);
    // List_Names.erase(List_Names.begin() + _PlayList_index);
}

std::vector<std::string> List::Get_List_Names() const{
    std::vector<std::string> temp;
    for (const auto& playlist : List_PlayLists) {
        temp.push_back(playlist->Get_PlayList_Name());
    }
    return temp;
}

// void List::Set_List_Names(std::string _New_Name, size_t _PlayList_index){
//     List_Names[_PlayList_index] = _New_Name;
// }

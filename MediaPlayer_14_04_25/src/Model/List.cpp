#include "List.hpp"
#include <filesystem>

// Constructor
List::List(){
    // Initialize the list of playlists
    List_PlayList = std::vector<std::shared_ptr<PlayList>>();
    // Create a default playlist which name "Current directory: (current directory of folder where the program executed)"
    std::string current_directory = std::filesystem::current_path().string();
    std::string playlist_name = "Current directory: " + current_directory;
    auto defaultPlaylist = std::make_shared<PlayList>(playlist_name);

    // check the current folder and subfolder where the program executed for all media files to push back to the List_PlayList[0]
    for (const auto& entry : std::filesystem::recursive_directory_iterator(current_directory)) {
        if (entry.is_regular_file()) {
            std::string file_path = entry.path().string();
            auto file = std::make_shared<File>(file_path);
            defaultPlaylist->Add_File(file);
        }
    }
    List_PlayList.push_back(defaultPlaylist);
}

// Method to get the list of playlists
std::vector<std::shared_ptr<PlayList>> List::Get_List() const{
    return List_PlayList;
}

// Return a PlayList of input index
std::shared_ptr<PlayList> List::Get_A_PlayList(int _PlayList_Index) const{
    return List_PlayList[_PlayList_Index];
}

// Add PlayList name _PlayList_Name to the List_PlayList
void List::Add_PlayList(std::string& _PlayList_Name){
    // Check if the playlist name already exists
    for (const auto& playlist : List_PlayList) {
        if (playlist->get_PlayList_Name() == _PlayList_Name) {
            std::cout << "Playlist with this name already exists!" << std::endl;
            return;
        }
    }

    // Create a new playlist and add it to the list
    auto newPlaylist = std::make_shared<PlayList>(_PlayList_Name);
    List_PlayList.push_back(newPlaylist);
}

// delete the PlayList: List_PlayList[_PlayList_index]
void List::Remove_PlayList(size_t _PlayList_index){
    List_PlayList.erase(List_PlayList.begin() + _PlayList_index);
}
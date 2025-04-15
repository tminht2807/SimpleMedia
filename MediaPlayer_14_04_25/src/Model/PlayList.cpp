#include "PlayList.hpp"

// method to get Files
std::vector<std::shared_ptr<File>> PlayList::Get_PlayList() const{
    return List_Files;
}

// method to get a file from vector by index
std::shared_ptr<File> PlayList::Get_A_File(int _index){
    return List_Files[_index];
}

// method to get the playlist name
std::string PlayList::Get_PlayList_Name(){
    return PlayListName;
}

void PlayList::Add_By_Directory(std::string _directory){
    for (const auto& entry : std::filesystem::recursive_directory_iterator(_directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
            std::string file_path = entry.path().string();
            auto file = std::make_shared<File>(file_path);
            List_Files.push_back(file);
        }
    }
}

// method to add a file to the vector
void PlayList::Add_File(std::shared_ptr<File> _file){
    List_Files.push_back(_file);
}

// method to remove all List_files from the vector
void PlayList::Clear_PlayList(){
    List_Files.clear();
}

// method to remove a file from the vector
void PlayList::Remove_File(int _File_index){
    List_Files.erase(List_Files.begin() + _File_index);
}

void PlayList::Set_PlayList_Name(const std::string& _name){
    this->PlayListName = _name;
}
    
std::vector<std::string> PlayList::Get_List_Names(){
    std::vector<std::string> temp;
    for (const auto& entry : List_Files){
        temp.push_back(entry.get()->Get_Title());
    }
    return temp;
}

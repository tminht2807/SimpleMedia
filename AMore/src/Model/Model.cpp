#include "Model.hpp"
#include <filesystem>

Model::Model() : current_File_Index(0), current_PlayList_Index(0), isPlaying(false) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    }
    // Initialize SDL_mixer with audio format settings
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_Quit();
    }
    isPlaying = false;
    currentMusic = nullptr;
}

// Method to get the list of playlists
std::vector<std::shared_ptr<PlayList>> Model::getPlaylists() const {
    return List_PlayList;
}

// Method to add a playlist
void Model::Add_New_PlayList(std::string& _PlayList_Name) {
    std::shared_ptr<PlayList> newPlaylist = std::make_shared<PlayList>(_PlayList_Name);
    List_PlayList.push_back(newPlaylist);
}

// Getter Setter for current_File_Index, current_PlayList_Index
size_t Model::getCurrentFileIndex() const{
    return this->current_File_Index;
}
void Model::setCurrentFileIndex(size_t index){
    if (index < List_PlayList[current_PlayList_Index]->get_Files().size()) { 
        this->current_File_Index = index;
    } else {
        std::cerr << "Index out of bounds for current_File_Index" << std::endl;
    }
}
size_t Model::getCurrentPlayListIndex() const{
    return this->current_PlayList_Index;
}
void Model::setCurrentPlayListIndex(size_t index){
    if (index < List_PlayList.size()) { 
        this->current_PlayList_Index = index;
    } else {
        std::cerr << "Index out of bounds for current_PlayList_Index" << std::endl;
    }
}

void Model::playCurrentFile(size_t _current_PlayList_Index,size_t _current_File_Index){
    if (_current_PlayList_Index < List_PlayList.size()) {
        if (_current_File_Index < List_PlayList[_current_PlayList_Index]->get_Files().size()) {
            // Get the file from the playlist
            std::shared_ptr<File> file = List_PlayList[_current_PlayList_Index]->getFile(_current_File_Index);
            if (file) {
                // Play the file using SDL_mixer
                currentMusic = Mix_LoadMUS(file->getFilePath().c_str());
                if (currentMusic) {
                    Mix_PlayMusic(currentMusic, 1);
                    isPlaying = true;
                    setCurrentFileIndex(_current_File_Index);           // Update the current file index
                    setCurrentPlayListIndex(_current_PlayList_Index);   // Update the current playlist index
                } else {
                    std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
                }
            }
        } else {
            std::cerr << "Index out of bounds for current_File_Index" << std::endl;
        }
    } else {
        std::cerr << "Index out of bounds for current_PlayList_Index" << std::endl;
    }
}

void Model::Add_A_File_To_PlayList(size_t _PlayList_index){
    // add a file to List_PlayList[_PlayList_index] 
    
    std::string file_path;
    // std::cout << "Enter the path: ";
    std::cin >> file_path;
    
    // ask user to input a path
    // if it ends with .mp3, add it to the playlist
    // if it is a folder directory, add all the files in the folder and sub-folder to the playlist
    if (std::filesystem::is_directory(file_path)) {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(file_path)) {
            if (entry.path().extension() == ".mp3") {
                std::shared_ptr<File> newFile = std::make_shared<File>(entry.path().string());
                List_PlayList[_PlayList_index]->addFile(newFile);
            }
        }
    } 
    else if (std::filesystem::is_regular_file(file_path) ) {
        std::shared_ptr<File> newFile = std::make_shared<File>(file_path);
        List_PlayList[_PlayList_index]->addFile(newFile);
    } 
    else {
        std::cerr << "Invalid file or directory" << std::endl;
    }
}

void Model::Remove_From_PlayList(size_t _PlayList_index, size_t _File_index){
    // delete a file in List_PlayList[_PlayList_index]
    List_PlayList[_PlayList_index]->removeFile(_File_index);
}

void Model::Remove_A_PlayList(size_t _PlayList_index){
    // delete a PlayList in List_PlayList[_PlayList_index]
    List_PlayList.erase(List_PlayList.begin() + _PlayList_index);
}

std::shared_ptr<PlayList>  Model::getCurrentPlayList() const{
    return List_PlayList[current_PlayList_Index];
}
#include "Model.hpp"
#include <filesystem>

Model::Model() : current_File_Index(0), current_PlayList_Index(0), isPlaying(false) {
    fake_taxi = this;
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
    
    // Initialize the first playlist
    // List_PlayList.push_back(std::make_shared<PlayList>("Current Directory"));

    // capture current folder and subfolder where program executed directory for .mp3 files
    std::string current_directory = std::filesystem::current_path().string();
    std::shared_ptr<PlayList> newPlaylist = std::make_shared<PlayList>(current_directory);

    List_PlayList.push_back(newPlaylist);
        // browse current_directory, for every file .mp3, create File and push back to the List_PlayList[0]
    for (const auto& entry : std::filesystem::recursive_directory_iterator(current_directory)) {
        if (entry.path().extension() == ".mp3") {
            std::shared_ptr<File> newFile = std::make_shared<File>(entry.path().string());
            List_PlayList[0]->addFile(newFile);
        }
    }
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
    } 
    else {
        std::cerr << "Index out of bounds for current_PlayList_Index" << std::endl;
    }
}

bool Model::playCurrentFile(){
    // Get the file from the playlist
    std::shared_ptr<File> file = List_PlayList[current_PlayList_Index]->getFile(current_File_Index);
    if (file) {
        // Play the file using SDL_mixer
        currentMusic = Mix_LoadMUS(file->getFilePath().c_str());
        if (currentMusic) {
            Mix_PlayMusic(currentMusic, 1);
            isPlaying = true;
            setCurrentFileIndex(current_File_Index);           // Update the current file index
            setCurrentPlayListIndex(current_PlayList_Index);   // Update the current playlist index
            // Feature to play next file in the playlist if the current one ends
            Mix_HookMusicFinished(StaticOnMediaFinished);
            return true;
        } 
        else {
            std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        }
    }
    // if (_current_PlayList_Index < List_PlayList.size()) {
    //     if (_current_File_Index < List_PlayList[_current_PlayList_Index]->get_Files().size()) {
    //         /**/ Logic
    //     }
    //     else {
    //         std::cerr << "Index out of bounds for current_File_Index" << std::endl;
    //     }
    // }
    // else {
    //     std::cerr << "Index out of bounds for current_PlayList_Index" << std::endl;
    // }
}

void Model::StaticOnMediaFinished(){
    // This function is called when the media finishes playing
    // You can implement any logic you want here, such as moving to the next media
    fake_taxi->NextMedia();
}

void Model::NextMedia(){
    // if current File index is less than the size of the current playlist
    // if (current_File_Index + 1 < List_PlayList[current_PlayList_Index]->get_Files().size()) {
    if (current_File_Index + 1 < List_PlayList[current_PlayList_Index]->get_Files().size()) {
        current_File_Index++;
    } else {
        current_File_Index = 0; // Loop back to the first media file
    }
    playCurrentFile();
}

void Model::PrevMedia(){

}

void Model::PauseResumeMedia(){
    if (isPlaying) { // Check if music is currently playing
        Mix_PauseMusic();
        isPlaying = false;   
    }
    else{
        Mix_ResumeMusic();
        isPlaying = true;
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

std::shared_ptr<PlayList>  Model::get_CurrentPlayList() const{
    return List_PlayList[current_PlayList_Index];
}

std::shared_ptr<PlayList> Model::get_PlayList(int _PlayList_Index) const{
    // Return a PlayList of input index
    return List_PlayList[_PlayList_Index];
}

std::vector<std::shared_ptr<PlayList>> Model::get_List_PlayList() const {
    return List_PlayList;
}
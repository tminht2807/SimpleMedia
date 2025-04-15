#include "ControllerMediaPlay.hpp"

std::shared_ptr<ViewMediaPlay> ControllerMediaPlay::Get_View(){
    return std::make_shared<ViewMediaPlay>(view);
}

void ControllerMediaPlay::Show(){
    view.Show_Screen(   Get_Current_PlayList_Name(),current_PlayList_Index,
                        Get_Current_File_Title(),current_File_Index,
                        Get_Current_File_Duration());
}

std::shared_ptr<PlayList> ControllerMediaPlay::Get_PlayList(){
    return playlist;
}

std::string ControllerMediaPlay::Get_Current_PlayList_Name() const{
    return playlist.get()->get_PlayList_Name();
}
std::string ControllerMediaPlay::Get_Current_File_Title() const{
    return playlist.get()->getFile(current_File_Index).get()->getMetadata().Title;
}
size_t ControllerMediaPlay::Get_Current_PlayList_Index() const{
    return current_PlayList_Index;
}
size_t ControllerMediaPlay::Get_Current_File_Index() const{
    return current_File_Index;
}
double ControllerMediaPlay::Get_Current_File_Duration() const{
    return playlist.get()->getFile(current_File_Index).get()->getMetadata().Duration;
}
void ControllerMediaPlay::Set_Current_PlayList_Index(const size_t _PlayList_Index){
    this->current_PlayList_Index = _PlayList_Index;
}

void ControllerMediaPlay::Set_PlayList(std::shared_ptr<PlayList> _PlayList){
    this->playlist = _PlayList;
}

void ControllerMediaPlay::Set_View(ViewMediaPlay _view){
    this->view = _view;
}

void ControllerMediaPlay::ControlPlayMedia(){
    if (Get_PlayList()){
        currentMusic = Mix_LoadMUS(Get_PlayList().get()->getFile(current_File_Index).get()->getFilePath().c_str());
        if (currentMusic) {
            Mix_PlayMusic(currentMusic, 1);
            isPlaying = true;
            // Feature to play next file in the playlist if the current one ends
            Mix_HookMusicFinished(StaticOnMediaFinished);
        } 
        else {
            std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        }
    }
}

// Method when Finished playing a media
void ControllerMediaPlay::StaticOnMediaFinished(){
    fake_taxi->OnMediaFinished();
}

// Method when Finished playing a media
void ControllerMediaPlay::OnMediaFinished(){
    Get_View().get()->Set_Console("Media finished playing.");
    ControlNextMedia();
}

void ControllerMediaPlay::ControlPauseResumeMedia(){
    if (isPlaying) { // Check if music is currently playing
        Mix_PauseMusic();
        isPlaying = false;   
    } else {
        Mix_ResumeMusic();
        isPlaying = true;
    }
}
void ControllerMediaPlay::ControlNextMedia(){
    if (current_File_Index + 1 < playlist.get()->get_Files().size()) current_File_Index ++;
    else current_File_Index = 0;
    ControlPlayMedia();
}
void ControllerMediaPlay::ControlPreviousMedia(){
    if (current_File_Index == 0) current_File_Index = playlist.get()->get_Files().size() - 1;
    else current_File_Index --;
    ControlPlayMedia();
}
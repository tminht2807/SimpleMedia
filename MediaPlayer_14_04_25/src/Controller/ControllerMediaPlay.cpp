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
    return playlist.get()->Get_PlayList_Name();
}
std::string ControllerMediaPlay::Get_Current_File_Title() const{
    if (playlist.get()->Get_PlayList().size() == 0) return "No media file";
    else return playlist.get()->Get_A_File(current_File_Index).get()->Get_Title();
}
size_t ControllerMediaPlay::Get_Current_PlayList_Index() const{
    return current_PlayList_Index;
}
size_t ControllerMediaPlay::Get_Current_File_Index() const{
    return current_File_Index;
}
double ControllerMediaPlay::Get_Current_File_Duration() const{
    if (playlist.get()->Get_PlayList().size() == 0) return 0;
    else return playlist.get()->Get_A_File(current_File_Index).get()->Get_Duration();
}
void ControllerMediaPlay::Set_Current_PlayList_Index(const size_t _PlayList_Index){
    this->current_PlayList_Index = _PlayList_Index;
}

void ControllerMediaPlay::Set_PlayList(std::shared_ptr<PlayList> _PlayList, size_t _PlayList_Index){
    this->playlist = _PlayList;
    this->current_PlayList_Index =_PlayList_Index;
    this->current_File_Index = 0;
}

void ControllerMediaPlay::Set_View(ViewMediaPlay _view){
    this->view = _view;
}

void ControllerMediaPlay::ControlPlayMedia(){
    if (Get_PlayList().get()->Get_PlayList().size() != 0){
        currentMusic = Mix_LoadMUS(Get_PlayList().get()->Get_A_File(current_File_Index).get()->Get_FilePath().c_str());
        if (currentMusic) {
            Mix_PlayMusic(currentMusic, 1);
            isPlaying = true;
            // Feature to play next file in the playlist if the current one ends
            Mix_HookMusicFinished(StaticOnMediaFinished);
        } 
    }
    else {
        Get_View().get()->Set_Console("No media available in playlist");
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
    if (current_File_Index + 1 < playlist.get()->Get_PlayList().size()) current_File_Index ++;
    else current_File_Index = 0;
    ControlPlayMedia();
}
void ControllerMediaPlay::ControlPreviousMedia(){
    if (current_File_Index == 0) current_File_Index = playlist.get()->Get_PlayList().size() - 1;
    else current_File_Index --;
    ControlPlayMedia();
}
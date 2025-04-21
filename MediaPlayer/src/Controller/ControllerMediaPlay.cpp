#include "ControllerMediaPlay.hpp"

ViewMediaPlay* ControllerMediaPlay::Get_View(){
    return &view;
}

void ControllerMediaPlay::Show(){
    view.Show_Screen(   Get_Current_PlayList_Name(),current_PlayList_Index,
                        Get_Current_File_Title(),current_File_Index,
                        Get_Current_File_Duration(), this->volume, this->isConnected, this->isPlaying);
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

void ControllerMediaPlay::ControlPlayMedia(std::shared_ptr<PlayList> _playlist, size_t _PlayList_Index){
    Set_PlayList(_playlist,_PlayList_Index);
    ControlPlayMedia();
}    void uartListener();

void ControllerMediaPlay::ControlPlayMedia(std::shared_ptr<PlayList> _playlist, size_t _PlayList_Index, size_t _File_Index){
    Set_PlayList(_playlist,_PlayList_Index);
    this->current_File_Index = _File_Index;
    ControlPlayMedia();
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

    else if (Get_PlayList().get()->Get_PlayList().size() == 0 ){
        // stop media playing at the moment
        // Mix_FreeMusic(currentMusic);
        Mix_HaltMusic();
        Get_View()->Set_Console("No media available in playlist");
    }
}

// Method when Finished playing a media
void ControllerMediaPlay::StaticOnMediaFinished(){
    fake_taxi->OnMediaFinished();
}

// Method when Finished playing a media
void ControllerMediaPlay::OnMediaFinished(){
    Get_View()->Set_Console("Media finished playing.");
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

void ControllerMediaPlay::uartListener() {
    this->isConnected = false;
    const char* port = "/dev/ttyACM0"; // Adjust for your system
    int serial_port;
    struct termios tty;
    
    while (true) {
        while (!isConnected) {
            sleep(1);
            // Check if the serial port is open
            serial_port = open(port, O_RDWR);

            if (serial_port >= 0) {

                isConnected = true;
                // Clear the tty structure
                memset(&tty, 0, sizeof(tty));

                // Get current attributes
                tcgetattr(serial_port, &tty);

                // Set baud rate
                cfsetispeed(&tty, B115200);
                cfsetospeed(&tty, B115200);

                // Configure 8N1 (8 data bits, no parity, 1 stop bit)
                tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8 data bits
                tty.c_cflag &= ~PARENB;                    // No parity
                tty.c_cflag &= ~CSTOPB;                    // 1 stop bit
                tty.c_cflag &= ~CRTSCTS;                   // No hardware flow control

                // Enable receiver and set local mode
                tty.c_cflag |= (CLOCAL | CREAD);

                // Disable canonical mode, echo, and signal chars
                tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

                // Disable software flow control
                tty.c_iflag &= ~(IXON | IXOFF | IXANY);

                // Raw output
                tty.c_oflag &= ~OPOST;

                // Set read timeout (in deciseconds)
                tty.c_cc[VMIN] = 1;  // Minimum number of characters to read
                tty.c_cc[VTIME] = 1; // Timeout in deciseconds (0.1 seconds)

                // Apply the attributes
                tcsetattr(serial_port, TCSANOW, &tty);
            }
        }
    
        uint8_t data; // 1-byte data bus
        int bytes_read = read(serial_port, &data, 1); // Read one byte
        
        if (bytes_read > 0) { // Ensure full byte is received

            if (data == 0xBF) ControlPauseResumeMedia();
            else if (data == 0x3F) ControlPreviousMedia();
            else if (data == 0x7F) ControlNextMedia();
            else {
                this->volume = data & 0x3F; // match the volume value with the 0-5 bits of the data
                ControlChangeVolume(); // Change volume
            }

            tcflush(serial_port, TCIFLUSH);
        } 
        if (tcgetattr(serial_port, &tty) < 0){
            isConnected = false;
            close(serial_port);
            serial_port = -1;
        } 
    }
}

void ControllerMediaPlay::ControlChangeVolume(){
    int _vol = static_cast<int>(this->volume * (MIX_MAX_VOLUME / 64));
    Mix_VolumeMusic(_vol);
}
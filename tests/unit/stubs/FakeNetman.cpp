#include <Net2Com.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
const int NULL_CHAR = 1;

void Write(Net2Com* channel, unsigned char byte){
    channel->WriteToInfoPipe(sizeof(unsigned char));
    channel->WriteToDataPipe(byte);
}
void Write(Net2Com* channel, const char* data){
    channel->WriteToInfoPipe(strlen(data) + NULL_CHAR);
    channel->WriteToDataPipe(data);
}
void Write(Net2Com* channel, const void* data, int size){
    channel->WriteToInfoPipe(size);
    channel->WriteToDataPipe(data, size);
}
int main(){
    union int_to_charArr{
        unsigned int i;
        unsigned char arr[4];
    };
    Net2Com* channel =  new Net2Com(PIPE_ONE, PIPE_TWO, PIPE_THREE, PIPE_FOUR);

    #ifdef LONELY   //***********************************************************//
                    // Test FakeNetman
    pid_t pid;
    pid = fork();

    if (pid == 0){
        Net2Com* commander = new Net2Com(PIPE_TWO, PIPE_ONE, PIPE_FOUR, PIPE_THREE);
        char* info = new char;
        char buffer[100];

        commander->ReadFromInfoPipe(info);
        printf("Info : %d\t", (unsigned char)(*info) );

        commander->ReadFromDataPipe(buffer); 
        printf("Data : %d\n", (unsigned char)buffer[0] );
    
        commander->ReadFromInfoPipe(info);
        printf("Info : %d\t", *info );
        commander->ReadFromDataPipe(buffer);
        int_to_charArr year;
        for (int i=0; i<4; i++){
            year.arr[i] = (unsigned char)buffer[1 + i];
            printf("char : %d, buffer : %d\n", (int)(year.arr[i]), (int)buffer[1 + i]);
        }
        printf("date : %d/%d/%d\n", year.i, (unsigned char)buffer[5], (unsigned char)buffer[6]);
        delete commander;
        return 0;
    }
    #endif          //***********************************************************//
    
    unsigned char settime_command[] = {0,0xF,0xF,0xF,0xF,12,1,12,59,59};
    int_to_charArr convert;
    convert.i = 2012;
    for (int i=0; i<4; i++){
        settime_command[1 + i] = convert.arr[i];
    }

    Write(channel, 252);    // Start session signal.
    Write(channel, settime_command, sizeof(settime_command)); // send setsettime_command command.


    delete channel;

    return 0;
}

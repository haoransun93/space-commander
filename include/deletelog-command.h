/*=============================================================================
*
*   AUTHOR      : Space Concordia 2014  -  Joseph
*
*   PURPOSE     : The DeleteLogCommand deletes the specified file  located in
*                 CS1_LOGS or CS1_TGZ directory.
*                 N.B.  We should NEVER have to delete files in the CS1_LOGS
*                       folder, only in the CS1_TGZ folder, but we keep the 
*                       functionnality just in case.
*
*============================================================================*/
#ifndef DELETELOG_COMMAND_H
#define DELETELOG_COMMAND_H

#include <sys/types.h>
#include "icommand.h"

#define LOG 0x0
#define TGZ 0x1

class DeleteLogCommand : public ICommand 
{
    private :

        char* filename;
        char type;

    public :

        DeleteLogCommand(const char* filename);
        DeleteLogCommand(ino_t inode);
        virtual void* Execute();
        virtual ~DeleteLogCommand();
        char FindType();
        void SaveFilename(ino_t inode);
        char* ExtractFilenameFromFile();
};

#endif
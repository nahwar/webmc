#ifndef COMMAND_H
#define COMMAND_H

#include<iostream>
#include<string>

using namespace std;


int runcommand(string filein,
                       string fileout,
                       string width,
                       string height,
                       bool muted,
                bool startfromcheck,
                string startfrom,
                bool durationcheck,
                string duration
                       )
{

string command = "xterm -e ffmpeg ";

if(startfromcheck){
    command += "-ss "+startfrom+" ";
}

if(durationcheck){
    command += "-t "+duration+" ";
}

command +="-i \""+filein+"\" -c:v libvpx -crf 32 -b:v 900K -threads 1 ";

if(muted)
{
    command += "-an ";
}
else
{
    command += "-c:a libvorbis ";
}

command += "-vf scale="+width+":"+height+" -y -nostdin \""+fileout+"\"";






const char* p = command.c_str();
system(p);

return 1;
}


#endif // COMMAND_H

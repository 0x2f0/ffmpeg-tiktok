#include <stdio.h>
#include <stdlib.h>

#define OUTPUT "./out/output.mp4"
#define divisor 5 
#define image "./assets/input.jpeg"
#define music "./assets/music.aac"

const char *emojies[5] = {
  "./emojies/eye.png",
  "./emojies/lemon.png",
  "./emojies/khursani.png",
  "./emojies/om.png",
  "./emojies/chears.png"
};

int main() {
  char *ffmpeg; 
  char *overlay;
           
  asprintf(&overlay,
           "-vf \"drawtext=text=emojies"
           ":fontcolor=white"
           ":fontsize=h/10"
           ":x='st(0, min(W,H)*0.3); W/2 + ld(0)*cos((t/%d)*2*PI)'"
           ":y='st(0, min(W,H)*0.3); H/2 + ld(0)*sin((t/%d)*2*PI)'\" ",
            divisor,
            divisor);
  
  asprintf(&ffmpeg, 
           "ffmpeg -loop 1 -i %s "
           "-i %s "
           "%s "
           /* "-shortest %s ", */
           "-t 5s %s ",
           image,
           music,
           overlay,
           OUTPUT);

  system(ffmpeg);
  return 0;
}

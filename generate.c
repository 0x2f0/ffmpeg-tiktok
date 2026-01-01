#include <stddef.h>
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
  char *overlay = "";
  int length = sizeof(emojies) / sizeof(emojies[0]);
  int radius_y = 150;
  int factor = 40;

  // loading the emojies first;
  for (int i = 0; i < length; i++) {
    asprintf(&overlay,
             "%s -i %s",
             overlay,
             emojies[i]);
  } 
  printf("after emojies [%s]\n", overlay);

  // starting the filter
  asprintf(&overlay, "%s -filter_complex \"[0:v]", overlay);

  // Overlaying the emojies 
  for (int i = 0; i < length; i++) {
    int asset_index =  i + 2;
    int emoji_number =  i + 1;
    char *chain_key_start = "";
    char *chain_key_end = "";

    if(i == 0 ) {
      chain_key_start = "";
    } else {
      asprintf(&chain_key_start, "[v%d]", i);
    }

    if(emoji_number == length) {
      chain_key_end = "";
    } else {
      asprintf(&chain_key_end, "[v%d]", emoji_number);
    }

    asprintf(&overlay,
             "%s "
             "%s[%d:v]overlay="
             "x='st(0, 32*%d);(W/2-%d+ld(0)) + ((W/2.5)*cos(2*PI*n/%d))':" // h+rcos0
             "y='H/1.5 + (%d*sin(2*PI*n/%d))' %s;", //K + rsin0 
             overlay,
             chain_key_start,
             asset_index,
             emoji_number,
             length * 32, // whole emojies_width
             factor,
             radius_y,
             factor,
             chain_key_end
             );
  } 

  asprintf(&overlay, "%s\"", overlay);
  printf("overlay: [%s]\n", overlay);

  asprintf(&ffmpeg, 
           "ffmpeg -loop 1 -i %s "
           "-i %s "
           "%s "
            "-shortest %s ",
           image,
           music,
           overlay,
           OUTPUT);
  printf("Final Command: [%s]\n",ffmpeg);

  system(ffmpeg);
  return 0;
}

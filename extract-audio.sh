#!/usr/bin/env bash 

set -e
seconds=18s
ffmpeg -t $seconds   \
    -ss 24s          \
    -i ./full_video  \
    -t $seconds      \
    -vn -acodec      \
    copy music.aac

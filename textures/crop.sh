#!/bin/bash

input_image="ground.png"
sprite_width=$((772 / 3))
sprite_height=$((1286 / 5))
num_columns=3
num_rows=5
num_sprites=$((num_columns * num_rows))

# Loop to crop each sprite
for ((i = 0; i < num_sprites; i++)); do
    row=$((i / num_columns))
    col=$((i % num_columns))
    offset_x=$((col * sprite_width))
    offset_y=$((row * sprite_height))
    convert "$input_image" -crop "${sprite_width}x${sprite_height}+${offset_x}+${offset_y}" -resize 256x256 +repage "ground_$i.xpm"
done
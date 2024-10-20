#!/bin/bash

# Define the input image and sprite dimensions
input_image="spritesheet.png"
sprite_width=$((517 / 4))
sprite_height=$((388 / 3))
num_columns=4
num_rows=3
num_sprites=$((num_columns * num_rows))

# Loop to crop each sprite
for ((i = 0; i < num_sprites; i++)); do
    row=$((i / num_columns))
    col=$((i % num_columns))
    offset_x=$((col * sprite_width))
    offset_y=$((row * sprite_height))
    convert "$input_image" -crop "${sprite_width}x${sprite_height}+${offset_x}+${offset_y}" +repage "sprite_$i.xpm"
done
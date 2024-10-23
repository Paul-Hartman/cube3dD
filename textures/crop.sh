#!/bin/bash

# Define the input image and sprite dimensions
input_image="HealthBar.png"
sprite_width=$((240 / 5))
sprite_height=$((96 / 2))
num_columns=5
num_rows=2
num_sprites=$((num_columns * num_rows))

# Loop to crop each sprite
for ((i = 0; i < num_sprites; i++)); do
    row=$((i / num_columns))
    col=$((i % num_columns))
    offset_x=$((col * sprite_width))
    offset_y=$((row * sprite_height))
    convert "$input_image" -crop "${sprite_width}x${sprite_height}+${offset_x}+${offset_y}" -resize 100x100 +repage "healthbar_$i.xpm"
done
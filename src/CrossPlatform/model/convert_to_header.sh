#!/bin/bash

if ! command -v xxd >/dev/null 2>&1; then
    echo "Ошибка: утилита xxd не найдена. Установите ее."
    exit 1
fi

mkdir -p ./include

to_snake_case() {
    echo "$1" | sed -E 's/([A-Z])/_\1/g' | tr '[:upper:]' '[:lower:]' | sed 's/^_//'
}

find . -type f ! -name "*.h" ! -name "convert_to_header.sh" | while read -r input_file; do
    dir=$(dirname "$input_file")
    basename=$(basename "$input_file")
    filename_no_ext=$(echo "$basename" | cut -f 1 -d '.')
    ext=$(echo "$basename" | cut -s -f 2 -d '.')

    snake_filename=$(to_snake_case "$filename_no_ext")
    if [ -n "$ext" ]; then
        snake_filename="${snake_filename}_${ext}"
    fi

    temp_output_file="./tmp_$snake_filename.h"
    final_output_dir="./include/$dir"
    final_output_file="$final_output_dir/$snake_filename.h"

    array_name="$snake_filename"
    upper_array_name=$(echo "$array_name" | tr '[:lower:]' '[:upper:]')

    if ! xxd -i "$input_file" > tmp.h 2>/dev/null; then
        echo "Пропуск $input_file: не удалось обработать xxd"
        continue
    fi

    sed -i '' "s/unsigned char .*\[/unsigned char ${array_name}\[/" tmp.h
    sed -i '' "s/unsigned int .*_len/unsigned int ${array_name}_len/" tmp.h

    cat << EOF > "$temp_output_file"
#ifndef ${upper_array_name}_H
#define ${upper_array_name}_H

$(cat tmp.h)

#endif // ${upper_array_name}_H
EOF

    mkdir -p "$final_output_dir"
    mv "$temp_output_file" "$final_output_file"
    echo "Создан и перемещен $input_file -> $final_output_file"

    rm tmp.h
done

echo "Конвертация и перемещение завершены"
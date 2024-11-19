#!/bin/bash

# Function to process each directory recursively
process_directory() {
    local dir="$1"

    # Check if the directory contains a "clean.py" file
    if [[ -f "${dir}/clean.py" ]]; then
        echo "Executing clean.py in ${dir}"
        pushd ${dir}
        # Execute the clean.py script
        python "${dir}/clean.py"
        popd
    fi

    # Recursively process subdirectories
    for subdir in "${dir}"/*/; do
        # Check if it's a directory before processing
        if [[ -d "${subdir}" ]]; then
            process_directory "${subdir%/}" # Remove trailing slash
        fi
    done
}

# Start the recursion from the current directory
process_directory "$(pwd)"
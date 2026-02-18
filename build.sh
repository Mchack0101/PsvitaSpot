#!/bin/bash

# Script to build PsvitaSpot and generate VPK file

# Set variables
SOURCE_DIR="src"
BUILD_DIR="build"
VPK_FILE="PsvitaSpot.vpk"

# Create build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Compile the source code
make -C $SOURCE_DIR
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Generate VPK file
vpk_tool create $BUILD_DIR/$VPK_FILE $SOURCE_DIR/*
if [ $? -ne 0 ]; then
    echo "VPK generation failed!"
    exit 1
fi

echo "Build and VPK generation completed successfully!"
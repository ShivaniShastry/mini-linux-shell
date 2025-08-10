FROM debian:bookworm-slim

# Use Ubuntu as the base image
FROM ubuntu:22.04

# Install g++ and make
RUN apt-get update && apt-get install -y g++ make && rm -rf /var/lib/apt/lists/*

# Set working directory inside container
WORKDIR /app

# Copy all project files into the container
COPY . .

# Build the project using your existing Makefile
RUN make clean&& make

# Run your compiled shell when the container starts
CMD ["./shell"]

FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Base build tools and dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    cmake \
    git \
    mingw-w64 \
    zlib1g-dev \
    libz-mingw-w64-dev \
    zip \
    unzip \
    curl \
    wget \
    libgtest-dev \
    pkg-config \
    && apt-get clean

# Qt dependencies
RUN apt-get update && apt-get install -y \
    qtbase5-dev \
    qt5-qmake \
    qttools5-dev-tools \
    && apt-get clean

# GTK dependencies
RUN apt-get update && apt-get install -y \
    libgtk-3-dev \
    && apt-get clean

# wxWidgets dependencies
RUN apt-get update && apt-get install -y \
    libwxgtk3.0-gtk3-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp lib/*.a /usr/lib

WORKDIR /src

CMD ["bash"]

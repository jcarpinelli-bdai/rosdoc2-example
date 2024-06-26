FROM osrf/ros:humble-desktop-full


ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y git make graphviz python3-pip

RUN cd /tmp \
    && git clone --recursive https://github.com/ros2/ros2_documentation \
    && pip install --requirement ros2_documentation/requirements.txt \
    && rm -rf ros2_documentation

RUN cd /tmp \ 
    && git clone --recursive https://github.com/ros-infrastructure/rosdoc2 \
    && pip install --upgrade ./rosdoc2 \
    && rm -rf rosdoc2

# Add vscode user with same UID and GID as your host system
# (copied from https://code.visualstudio.com/remote/advancedcontainers/add-nonroot-user#_creating-a-nonroot-user)
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME
# Switch from root to user
USER $USERNAME

# Add user to video group to allow access to webcam
RUN sudo usermod --append --groups video $USERNAME

# Update all packages
RUN sudo apt update && sudo apt upgrade -y

# Install Git
RUN sudo apt install -y git

# Rosdep update
RUN rosdep update

# Source the ROS setup file
RUN echo "source /opt/ros/${ROS_DISTRO}/setup.bash" >> ~/.bashrc

# Remove apt lists
RUN sudo apt-get autoremove -y && sudo apt-get clean -y && rm -rf /var/lib/lists/*

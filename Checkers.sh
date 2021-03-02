if [ ! -d "executable_linux" ]; then
    wget https://github.com/adam-choragwicki/Checkers_Game_Qt_Cplusplus/releases/latest/download/executable_linux.zip
    unzip executable_linux.zip && rm executable_linux.zip
    chmod +x executable_linux/Checkers.sh executable_linux/Checkers
fi

./executable_linux/Checkers

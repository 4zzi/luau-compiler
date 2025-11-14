#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../include/executor/utils.h"

bool CopyToClipboard(const std::string& text) {
    if (!OpenClipboard(nullptr))
        return false;
    EmptyClipboard();
    HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    if (!hGlob) {
        CloseClipboard();
        return false;
    }
    memcpy(GlobalLock(hGlob), text.c_str(), text.size() + 1);
    GlobalUnlock(hGlob);
    SetClipboardData(CF_TEXT, hGlob);
    CloseClipboard();
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "[*] LuaUCompiler.exe requires a Lua script as argument.\n";
        std::cout << "[*] Usage: LuaUCompiler.exe <script file>\n";
        std::cout << "[*] Press any key to exit...\n";
        std::cin.get();
        return 1;
    }

    std::string scriptPath = argv[1];
    std::ifstream file(scriptPath, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "[!] Failed to open script: " << scriptPath << "\n";
        std::cout << "[*] Press any key to exit...\n";
        std::cin.get();
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();

    try {
        std::string bytecode = Compile(source);

        if (CopyToClipboard(bytecode)) {
            std::cout << "[+] Compilation finished, bytecode copied to clipboard.\n";
        } else {
            std::cout << "[!] Failed to copy bytecode to clipboard.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "[!] Compilation failed: " << e.what() << "\n";
    }

    return 0;
}

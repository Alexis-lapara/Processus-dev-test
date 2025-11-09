// Cracker.cpp
#include "Cracker.h"
#include <openssl/md5.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <iostream>

std::string MD5Cracker::computeMD5(const std::string& input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)input.c_str(), input.length(), digest);

    std::ostringstream oss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    return oss.str();
}

bool MD5Cracker::loadDictionary(const std::string& path) { // A CHANGER SI DICTIONNAIRE GIGANTESQUE
    std::ifstream file(path);
    std::cout << "[Info] Chargement du dictionnaire depuis : " << path << std::endl;
    if (!file.is_open()) {
        std::cerr << "[Erreur] Impossible d'ouvrir le dictionnaire : " << path << std::endl;
        return false;
    }

    std::string line;
    dictionary.clear();
    while (std::getline(file, line)) {
        if (!line.empty()) {
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            if (!line.empty()) {
                dictionary.push_back(line);
            }
        }
    }
    file.close();

    std::cout << "[Info] Dictionnaire chargé : " << dictionary.size() << " mots." << std::endl;
    return true;
}

bool MD5Cracker::crack_dictionary(const std::string& target_hash, json& result) {
    if (target_hash.length() != 32) {
        result = {
            {"status", "error"},
            {"message", "Hash MD5 doit faire 32 caractères"}
        };
        return false;
    }

    // Normaliser le hash cible
    std::string target_lower = target_hash;
    std::transform(target_lower.begin(), target_lower.end(), target_lower.begin(), ::tolower);

    for (const auto& word : dictionary) {
        std::string hash = computeMD5(word);
        std::string hash_lower = hash;
        std::transform(hash_lower.begin(), hash_lower.end(), hash_lower.begin(), ::tolower);

        if (hash_lower == target_lower) {
            result = {
                {"status", "success"},
                {"password", word},
                {"hash", hash}
            };
            return true;
        }
    }

    result = {
        {"status", "not_found"},
        {"message", "Mot de passe non trouvé dans le dictionnaire"}
    };
    return false;
}
// string de 4 chiffres de 0 à 9999
bool MD5Cracker::crack_force(const std::string& target_hash, json& result) {
    if (target_hash.length() != 32) {
        result = {
            {"status", "error"},
            {"message", "Hash MD5 doit faire 32 caractères"}
        };
        return false;
    }
    // Normaliser le hash cible
    std::string target_lower = target_hash;
    std::transform(target_lower.begin(), target_lower.end(), target_lower.begin(), ::tolower);// faire une fonction potentiellement

    for (int i = 0; i <= 9999; ++i) {
        std::string candidate = std::to_string(i);
        std::string hash = computeMD5(candidate);
        std::string hash_lower = hash;
        std::transform(hash_lower.begin(), hash_lower.end(), hash_lower.begin(), ::tolower);
        if (hash_lower == target_lower) {
            result = {
                {"status", "success"},
                {"password", candidate},
                {"hash", hash}
            };
            return true;
        }
    }
    result = {
        {"status", "not_found"},
        {"message", "Mot de passe non trouvé (force brute 0-9999)"}
    };
    return false;
}
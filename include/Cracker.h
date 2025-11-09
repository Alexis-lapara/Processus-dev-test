// Cracker.h
#ifndef CRACKER_H
#define CRACKER_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * @brief Classe pour gérer l'attaque par dictionnaire MD5
 */
class MD5Cracker {
public:
    /**
     * @brief Charge un dictionnaire depuis un fichier
     * @param path Chemin du fichier
     * @return true si chargé, false sinon
     */
    bool loadDictionary(const std::string& path);

    /**
     * @brief Tente de cracker un hash MD5
     * @param target_hash Hash cible (32 caractères hex, peut être en majuscules)
     * @param result JSON de résultat (succès ou échec)
     * @return true si trouvé, false sinon
     * deux methodes: dictionnaire et force brute
     */
    bool crack_dictionary(const std::string& target_hash, json& result);
    bool crack_force(const std::string& target_hash, json& result);
private:
    std::vector<std::string> dictionary;

    // Fonction MD5
    std::string computeMD5(const std::string& input);
};

#endif // CRACKER_H
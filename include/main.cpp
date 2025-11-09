// main.cpp
#include <crow.h>
#include "Cracker.h"
#include <iostream>

int main() {
    crow::SimpleApp app;
    MD5Cracker cracker;

    // Charger le dictionnaire au démarrage
    if (!cracker.loadDictionary("dictionary.txt")) {
        return 1;
    }

    // === Route POST /api/crack ===
    CROW_ROUTE(app, "/api/crack/dictionary").methods("POST"_method) // a refactorer avec l'autre route peut-etre 
    ([&cracker](const crow::request& req) {
        try {
            auto body = json::parse(req.body);

            if (!body.contains("hash") || !body["hash"].is_string()) {
                return crow::response(400, R"({"error": "Champ 'hash' requis et doit être une chaîne"})");
            }

            std::string target_hash = body["hash"].get<std::string>();
            json result;

            if (cracker.crack_dictionary(target_hash, result)) {
                if (result["status"] == "success") {
                    return crow::response(200, result.dump());
                } else {
                    return crow::response(400, result.dump());
                }
            } else {
                return crow::response(404, result.dump());
            }

        } catch (const std::exception& e) {
            return crow::response(400, R"({"error": "JSON invalide"})");
        }
    });
    CROW_ROUTE(app, "/api/crack/force").methods("POST"_method)
    ([&cracker](const crow::request& req) {
        try {
            auto body = json::parse(req.body);

            if (!body.contains("hash") || !body["hash"].is_string()) {
                return crow::response(400, R"({"error": "Champ 'hash' requis et doit être une chaîne"})");
            }

            std::string target_hash = body["hash"].get<std::string>();
            json result;

            if (cracker.crack_force(target_hash, result)) {
                if (result["status"] == "success") {
                    return crow::response(200, result.dump());
                } else {
                    return crow::response(400, result.dump());
                }
            } else {
                return crow::response(404, result.dump());
            }

        } catch (const std::exception& e) {
            return crow::response(400, R"({"error": "JSON invalide"})");
        }
    });

    // === Page d'accueil ===
    CROW_ROUTE(app, "/")([](){
        return R"(
            <h1>MD5 Dictionary Attack API</h1>
            <p><code>POST /api/crack</code> avec :</p>
            <pre>
{
  "hash": "5f4dcc3b5aa765d61d8327deb882cf99"
}
            </pre>
            <p>Réponse : mot de passe ou erreur</p>
        )";
    });


    app.port(8080).multithreaded().run();
    std::cout << "API démarrée → http://localhost:8080" << std::endl;
    return 0;
}
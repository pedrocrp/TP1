// DatabaseManager.cpp

#include "DatabaseManager.hpp"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& dbPath) : dbPath(dbPath), db(nullptr) {}

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
    }
}

bool DatabaseManager::abrirConexao() {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Erro ao abrir banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

void DatabaseManager::criarTabelas() {
    const char* sqlUsuarios = 
        "CREATE TABLE IF NOT EXISTS Usuarios ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Email TEXT UNIQUE NOT NULL, "
        "Senha TEXT NOT NULL);";

    const char* sqlQuadros = 
        "CREATE TABLE IF NOT EXISTS Quadros ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Nome TEXT NOT NULL, "
        "Descricao TEXT);";

    const char* sqlCartoes = 
        "CREATE TABLE IF NOT EXISTS Cartoes ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Titulo TEXT NOT NULL, "
        "Conteudo TEXT, "
        "IDQuadro INTEGER, "
        "FOREIGN KEY (IDQuadro) REFERENCES Quadros(ID));";

    executarConsulta(sqlUsuarios);
    executarConsulta(sqlQuadros);
    executarConsulta(sqlCartoes);
}

std::optional<std::vector<std::map<std::string, std::string>>> DatabaseManager::executarConsulta(const std::string& sql) {
    // Verificar se é um comando SELECT
    if (sql.find("SELECT") == 0) {
        sqlite3_stmt* stmt;
        std::vector<std::map<std::string, std::string>> results;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
            std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
            return std::nullopt;
        }

        int cols = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::map<std::string, std::string> row;
            for (int i = 0; i < cols; i++) {
                std::string colName = sqlite3_column_name(stmt, i);
                std::string colValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                row[colName] = colValue;
            }
            results.push_back(row);
        }

        sqlite3_finalize(stmt);
        return results;
    } else {
        // Para comandos que não são SELECT
        char* zErrMsg = 0;
        if (sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg) != SQLITE_OK) {
            std::cerr << "Erro SQL: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
            return std::nullopt;
        }
        return std::nullopt; // Retorna nullopt para indicar que não há dados a retornar
    }
}



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
    const char* sqlContas = 
        "CREATE TABLE IF NOT EXISTS Conta ("
                "Email TEXT PRIMARY KEY, "
                "Nome TEXT, "
                "Senha TEXT);";

    const char* sqlQuadros = 
        "CREATE TABLE IF NOT EXISTS Quadro ("
                "Codigo TEXT PRIMARY KEY, "
                "EmailConta TEXT, " 
                "Nome TEXT, "
                "Descricao TEXT, "
                "Limite INTEGER, "
                "FOREIGN KEY (EmailConta) REFERENCES Conta(Email) ON DELETE CASCADE);";

    const char* sqlCartoes = 
        "CREATE TABLE IF NOT EXISTS Cartao ("
                "Codigo TEXT PRIMARY KEY, "
                "CodigoQuadro TEXT, " 
                "Nome TEXT, "
                "Descricao TEXT, "
                "Coluna TEXT, "
                "FOREIGN KEY (CodigoQuadro) REFERENCES Quadro(Codigo) ON DELETE CASCADE);";

    executarConsulta(sqlContas);
    executarConsulta(sqlQuadros);
    executarConsulta(sqlCartoes);
}


std::optional<std::vector<std::map<std::string, std::string>>> DatabaseManager::executarConsulta(const std::string& sql) {
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



void DatabaseManager::prepararConsulta(const std::string& sql) {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erro ao preparar consulta: " + std::string(sqlite3_errmsg(db)));
    }
    this->stmt = stmt;  // Salvar stmt como membro da classe
}

void DatabaseManager::vincularValor(int posicao, const std::string& valor) {
    if (sqlite3_bind_text(this->stmt, posicao, valor.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        throw std::runtime_error("Erro ao vincular valor: " + std::string(sqlite3_errmsg(db)));
    }
}

bool DatabaseManager::executarConsultaPreparada() {
    if (sqlite3_step(this->stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao executar consulta preparada: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(this->stmt);
        return false;
    }
    sqlite3_finalize(this->stmt);
    return true;
}

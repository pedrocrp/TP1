// DatabaseManager.hpp

#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <sqlite3.h>
#include <string>
#include <vector>
#include <map>
#include <optional>

class DatabaseManager {
public:
    DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();

    bool abrirConexao();
    void criarTabelas();
    std::optional<std::vector<std::map<std::string, std::string>>> executarConsulta(const std::string& sql);

private:
    sqlite3* db;
    std::string dbPath;
};

#endif // DATABASE_MANAGER_HPP

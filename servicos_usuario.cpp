#include "DatabaseManager.hpp"
#include "interfaces.hpp"
#include <stdexcept>
#include <optional>

class ControladorUsuario : public IGerenciamentoUsuario {
private:
    DatabaseManager dbManager;

public:
    ControladorUsuario(const std::string& dbPath) : dbManager(dbPath) {
        if (!dbManager.abrirConexao()) {
            throw std::runtime_error("Falha ao abrir conexão com o banco de dados.");
        }
    }

    void criarUsuario(const std::string& nome, const std::string& email, const std::string& senha) override {
        std::string sql = "INSERT INTO Usuarios (Email, Nome, Senha) VALUES ('" + email + "', '" + nome + "', '" + senha + "');";
        auto resultado = dbManager.executarConsulta(sql);
        if (!resultado) {
            throw std::runtime_error("Erro ao criar usuário.");
        }
    }

    void editarUsuario(const std::string& email, const std::string& novoNome, const std::string& novaSenha) override {
        std::string sql = "UPDATE Usuarios SET Nome = '" + novoNome + "', Senha = '" + novaSenha + "' WHERE Email = '" + email + "';";
        auto resultado = dbManager.executarConsulta(sql);
        if (!resultado) {
            throw std::runtime_error("Erro ao editar usuário.");
        }
    }

    void excluirUsuario(const std::string& email) override {
        std::string sql = "DELETE FROM Usuarios WHERE Email = '" + email + "';";
        auto resultado = dbManager.executarConsulta(sql);
        if (!resultado) {
            throw std::runtime_error("Erro ao excluir usuário.");
        }
    }
};

// #include "DatabaseManager.hpp"
// #include "interfaces.hpp"
// #include <stdexcept>
// #include <optional>
// #include "entidades.h"

// class ControladorQuadro : public IGerenciamentoQuadro {
// private:
//     DatabaseManager dbManager;

// public:
//     ControladorQuadro(const std::string& dbPath) : dbManager(dbPath) {
//         if (!dbManager.abrirConexao()) {
//             throw std::runtime_error("Falha ao abrir conexão com o banco de dados.");
//         }
//     }

//     void criarQuadro(const std::string& nome, const std::string& descricao) override {
//         std::string sql = "INSERT INTO Quadros (Nome, Descricao) VALUES ('" + nome + "', '" + descricao + "');";
//         auto resultado = dbManager.executarConsulta(sql);
//         if (!resultado) {
//             throw std::runtime_error("Erro ao criar quadro.");
//         }
//     }

//     void editarQuadro(int id, const std::string& novoNome, const std::string& novaDescricao) override {
//         std::string sql = "UPDATE Quadros SET Nome = '" + novoNome + "', Descricao = '" + novaDescricao + "' WHERE ID = " + std::to_string(id) + ";";
//         auto resultado = dbManager.executarConsulta(sql);
//         if (!resultado) {
//             throw std::runtime_error("Erro ao editar quadro.");
//         }
//     }

//     void excluirQuadro(int id) override {
//         std::string sql = "DELETE FROM Quadros WHERE ID = " + std::to_string(id) + ";";
//         auto resultado = dbManager.executarConsulta(sql);
//         if (!resultado) {
//             throw std::runtime_error("Erro ao excluir quadro.");
//         }
//     }
// };

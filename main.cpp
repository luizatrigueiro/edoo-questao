#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int TAMANHO = 100003;

struct Node {
    string bloco;
    int contagem;
    Node* proximo;

    Node(string b) {
        bloco = b;
        contagem = 1;
        proximo = NULL;
    }
};

class HashTable {
private:
    vector<Node*> tabela;

    int converterBase(char c) {
        if (c == 'A') return 0;
        else if (c == 'C') return 1;
        else if (c == 'G') return 2;
        else if (c == 'T') return 3;
        else return 0;
    }

    int hash(string bloco) {
        int valorHash = 0;
        for (int i = 0; i < bloco.size(); i++) {
            valorHash = (valorHash * 4 + converterBase(bloco[i])) % TAMANHO;
        }
        return valorHash;
    }

public:
    HashTable() {
        tabela.resize(TAMANHO, NULL);
    }

    void inserir(string bloco) {
        int indice = hash(bloco);
        Node* atual = tabela[indice];

        while (atual != NULL) {
            if (atual->bloco == bloco) {
                atual->contagem++;
                return;
            }
            atual = atual->proximo;
        }

        Node* novo = new Node(bloco);
        novo->proximo = tabela[indice];
        tabela[indice] = novo;
    }

    void salvarResultado(const string& nomeArquivo) {
        ofstream exibirOutput(nomeArquivo);
        if (!exibirOutput.is_open()) {
            cout << "Erro ao abrir o arquivo de output" << endl;
            return;
        }

        for (int i = 0; i < tabela.size(); i++) {
            Node* atual = tabela[i];
            while (atual != NULL) {
                exibirOutput << atual->bloco << " " << atual->contagem << endl;
                atual = atual->proximo;
            }
        }

        exibirOutput.close();
    }

    ~HashTable() {
        for (int i = 0; i < tabela.size(); i++) {
            Node* atual = tabela[i];
            while (atual != NULL) {
                Node* noTemporario = atual;
                atual = atual->proximo;
                delete noTemporario;
            }
        }
    }
};

void processarGenoma(const string& entrada, const string& saida) {
    ifstream receberInput(entrada);
    if (!receberInput.is_open()) {
        cout << "Erro ao abrir o arquivo de input" << endl;
        return;
    }

    string linha;
    HashTable tabela;

    while (getline(receberInput, linha)) {
        if (linha.size() < 60) continue;

        for (int i = 0; i + 6 <= linha.size(); i += 6) {
            string bloco = linha.substr(i, 6);
            tabela.inserir(bloco);
        }
    }

    receberInput.close();
    tabela.salvarResultado(saida);
}

int main() {
    string entrada1 = "genoma.txt";
    string saida1 = "saida.txt";
    processarGenoma(entrada1, saida1);

    string entrada2 = "genoma2.txt";
    string saida2 = "saida2.txt";
    processarGenoma(entrada2, saida2);
    
    cout << "Analise feita" << endl;
    return 0;
}

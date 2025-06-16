#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class SuperPoder{
    string nome;
    float poder;
public:
    SuperPoder(string n,float p): nome(n), poder(p) {}
    float getPoder() const {
        return poder;
    }
};

class Personagem{
    string nome;
    vector<SuperPoder> poderes;
public:
    Personagem(string n): nome(n) {}
    void adicionarSuperPoder(const SuperPoder& p) {
        poderes.emplace_back(p);
    }
    string getNome() const {
        return nome;
    }
    vector<SuperPoder> getPoderes() const {
        return poderes;
    }
    virtual float getPoderTotal() const {
        if (poderes.empty()) {
            return 0;
        }
        else{
            float total = 0;
            for (const auto& poder : poderes) {
                total += poder.getPoder();
            }
            return total;
        }
    }
    bool operator <(Personagem* p1){
        return getPoderTotal() < p1->getPoderTotal();
    }
    friend ostream& operator<<(ostream& os, const Personagem* p){
        os << p->getNome() << " - " << p->getPoderTotal() << endl;
        return os;
    }
    friend ostream& operator<<(ostream& os, const vector<Personagem*> personagens){
        int count = 1;
        for(const auto* p:personagens){
            os << count++ << ") " << p << endl;
        }
        return os;
    }
    friend class Heroi;
    friend class Vilao;
};
class Heroi : public Personagem{
public:
    Heroi(string n): Personagem(n) {}
    float getPoderTotal() const override {
        float total = Personagem::getPoderTotal();
        return total * 1.1; // Heróis um bônus de 10% do poder total
    }
    Heroi operator+(const Heroi &outro){
        Heroi novoHeroi(nome + " e " + outro.nome);
        for(auto& poder:outro.poderes){
            novoHeroi.adicionarSuperPoder(poder);
        }
        for(auto& poder:poderes){
            novoHeroi.adicionarSuperPoder(poder);
        }
        return novoHeroi;
    }
    bool operator <(Heroi& h1){
        return getPoderTotal() < h1.getPoderTotal();
    } 
    friend ostream& operator<<(ostream& os, const Heroi& h){
        os << h.getNome() << " - " << h.getPoderTotal() << endl;
        return os;
    }
    friend ostream& operator<<(ostream& os, const vector<Heroi> &herois){
        int count = 1;
        for(const auto& h:herois){
            os << count++ <<") "<< h << endl;
        }
        return os;
    }

};
class Vilao : public Personagem{
    float tempoDeCadeia=0;
public:
    Vilao(string n): Personagem(n) {}
    float getPoderTotal() const override {
        float total = Personagem::getPoderTotal();
        return total * (1+0.04*tempoDeCadeia); // Vilões um bônus de 4% do poder total para cada ano de cadeia
    }
    float getTempoDeCadeia() const {
        return tempoDeCadeia;
    }
    void setTempoDeCadeia(float tempo) {
        tempoDeCadeia = tempo;
    }
    Vilao operator+(const Vilao &outro){
        Vilao novoVilao(nome + " e " + outro.nome);
        for(auto& poder:outro.poderes){
            novoVilao.adicionarSuperPoder(poder);
        }
        for(auto& poder:poderes){
            novoVilao.adicionarSuperPoder(poder);
        }
        return novoVilao;
    }
    bool operator <(Vilao& v1){
        return getPoderTotal() < v1.getPoderTotal();
    } 
    friend ostream& operator<<(ostream& os, const Vilao& v){
        os << v.getNome() << " - " << v.getPoderTotal() << endl;
        return os;
    }
    friend ostream& operator<<(ostream& os, const vector<Vilao> &viloes){
        int count = 1;
        for(const auto& v:viloes){
            os << count++ <<") "<< v << endl;
        }
        return os;
    }
};
class Confronto{
public:
    void enfrentar(Personagem& p1, Personagem& p2){
        float poderp1 = p1.getPoderTotal();
        float poderp2 = p2.getPoderTotal();

        Vilao* v1 = dynamic_cast<Vilao*>(&p1); // dynamic_cast para tentar converter o perdedor em tempo de execução para o tipo Vilao* e, consequentemente, acrescentar o tempo de cadeia
        Vilao* v2 = dynamic_cast<Vilao*>(&p2);
        cout << "Confronto entre " << p1.getNome() << " (" << p1.getPoderTotal() << " de poder)" << " e " << p2.getNome() << " (" << p2.getPoderTotal() << " de poder)" << endl;
        if (poderp1 > poderp2) {
            cout << p1.getNome() << " vence!" << endl;
            if(v2){
                v2->setTempoDeCadeia(v2->getTempoDeCadeia() + 2); // se o vilão perder, ele ganha mais 2 anos de cadeia
            }
        } else if (poderp2 > poderp1) {
            cout << p2.getNome() << " vence!" << endl;
            if(v1){
                v1->setTempoDeCadeia(v1->getTempoDeCadeia() + 2); // se o vilão perder, ele ganha mais 2 anos de cadeia
            }
        } else {
            cout << "Empate!" << endl;
        }
    }
};


int main(){

    Heroi homemAranha("Homem-Aranha");
    homemAranha.adicionarSuperPoder(SuperPoder("Soltar teia", 2));
    homemAranha.adicionarSuperPoder(SuperPoder("Sentido apurado", 2));

    Heroi superHomem("Super-Homem");
    superHomem.adicionarSuperPoder(SuperPoder("Voar", 2));
    superHomem.adicionarSuperPoder(SuperPoder("Forca", 4));
    superHomem.adicionarSuperPoder(SuperPoder("Sopro Congelante", 3));

    Heroi mulherMaravilha("Mulher Maravilha");
    mulherMaravilha.adicionarSuperPoder(SuperPoder("Voar", 2));
    mulherMaravilha.adicionarSuperPoder(SuperPoder("Forca", 4));
    mulherMaravilha.adicionarSuperPoder(SuperPoder("Laco", 2));

    Heroi hulk("Hulk");
    hulk.adicionarSuperPoder(SuperPoder("Forca", 4));
    hulk.adicionarSuperPoder(SuperPoder("Regeneracao", 3));
    hulk.adicionarSuperPoder(SuperPoder("Artilheiro do Galo", 1));

    Heroi tempestade("Tempestade");
    tempestade.adicionarSuperPoder(SuperPoder("Controlar o clima", 5));

    Heroi wolverine("Wolverine");
    wolverine.adicionarSuperPoder(SuperPoder("Regeneracao", 3));
    wolverine.adicionarSuperPoder(SuperPoder("Sentido apurado", 2));
    wolverine.adicionarSuperPoder(SuperPoder("Adamantium", 2));

    Vilao duende("Duende Verde");
    duende.adicionarSuperPoder(SuperPoder("Tecnologia", 3));
    duende.adicionarSuperPoder(SuperPoder("Durabilidade", 1));

    Vilao cheetah("Cheetah");
    cheetah.adicionarSuperPoder(SuperPoder("Sentido apurado", 2));
    cheetah.adicionarSuperPoder(SuperPoder("Durabilidade", 1));
    cheetah.adicionarSuperPoder(SuperPoder("Velocidade", 3));

    Vilao magneto("Magneto");
    magneto.adicionarSuperPoder(SuperPoder("Magnetismo", 5));

    Vilao bizarro("Bizarro");
    bizarro.adicionarSuperPoder(SuperPoder("Voar", 2));
    bizarro.adicionarSuperPoder(SuperPoder("Forca", 4));
    bizarro.adicionarSuperPoder(SuperPoder("Sopro Congelante", 3));

    Confronto confronto;
    confronto.enfrentar(duende, homemAranha);
    confronto.enfrentar(cheetah, wolverine);
    confronto.enfrentar(wolverine, duende);
    confronto.enfrentar(cheetah, hulk);
    confronto.enfrentar(cheetah, superHomem);
    confronto.enfrentar(cheetah, mulherMaravilha);
    confronto.enfrentar(magneto, mulherMaravilha);
    confronto.enfrentar(magneto, hulk);
    confronto.enfrentar(magneto, superHomem);
    confronto.enfrentar(tempestade, magneto);
    confronto.enfrentar(bizarro, hulk);
    confronto.enfrentar(homemAranha, duende);

    Vilao duende_cheetah = duende + cheetah;
    Vilao magneto_bizarro = magneto + bizarro;
    Heroi superHomem_hulk = superHomem + hulk;

    confronto.enfrentar(duende_cheetah, mulherMaravilha);
    confronto.enfrentar(magneto_bizarro, wolverine);
    confronto.enfrentar(superHomem_hulk, magneto_bizarro);

    // Para fazer o ranking de vilões e de heróis separados, faremos um vector para heróis e um vector para vilões
    // para ordenar o vector, faremos uma sobrecarga no operador <

    vector<Heroi> herois;

    herois.emplace_back(homemAranha);
    herois.emplace_back(superHomem);
    herois.emplace_back(mulherMaravilha);
    herois.emplace_back(hulk);
    herois.emplace_back(tempestade);
    herois.emplace_back(wolverine);
    herois.emplace_back(superHomem_hulk);
    sort(herois.begin(),herois.end()); // ordem crescente
    reverse(herois.begin(),herois.end()); // ordem decrescente

    cout << "=== RANKING Herois ===" << endl;
    cout << herois;

    vector<Vilao> viloes;

    viloes.emplace_back(duende);
    viloes.emplace_back(cheetah);
    viloes.emplace_back(magneto);
    viloes.emplace_back(bizarro);
    viloes.emplace_back(duende_cheetah);
    viloes.emplace_back(magneto_bizarro);
    sort(viloes.begin(),viloes.end()); // Ordem crescente
    reverse(viloes.begin(),viloes.end()); // Ordem decrescente

    cout << "=== RANKING Viloes ===" << endl;
    cout << viloes;

    ofstream arqHeroi("Ranking Herois.txt");
    arqHeroi << "=== RANKING Herois ===" << endl;
    arqHeroi << herois;
    arqHeroi.close();

    ofstream arqVilao("Ranking Viloes.txt");
    arqVilao << "=== RANKING Viloes ===" << endl;
    arqVilao << viloes;
    arqVilao.close();

    // Resolvendo o desafio:
    // Criar um vector de ponteiros que apontam para a classe Personagem permite que o vector guarde tanto objetos da classe Heroi como da classe Vilao
    // OBS: Pq não vector<Personagem>?
    // Se tentar adicionar um objeto Heroi a um vector<Personagem>, o C++ copia apenas a parte que é Personagem e descarta tudo o que é específico da classe Heroi (como a redefinição do método getPoderTotal com o bônus de 10%)

    vector<Personagem*> personagens;

    personagens.emplace_back(&homemAranha);
    personagens.emplace_back(&superHomem);
    personagens.emplace_back(&mulherMaravilha);
    personagens.emplace_back(&hulk);
    personagens.emplace_back(&tempestade);
    personagens.emplace_back(&wolverine);
    personagens.emplace_back(&superHomem_hulk);
    personagens.emplace_back(&duende);
    personagens.emplace_back(&cheetah);
    personagens.emplace_back(&magneto);
    personagens.emplace_back(&bizarro);
    personagens.emplace_back(&duende_cheetah);
    personagens.emplace_back(&magneto_bizarro);
    sort(personagens.begin(), personagens.end());

    ofstream arqPersonagem("Ranking.txt");
    arqPersonagem << "=== RANKING Personagens ===" << endl;
    arqPersonagem << personagens; // sobrecarregar << para ponteiros da classe Personagem e enfim sobrecarregar << para vetores de ponteiros da classe Personagem
    arqPersonagem.close();

    return 0;
}
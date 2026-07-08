#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;

struct Player {
    string player_id;
    string player_name;
    string sort_key;
    string date_of_birth;
    string citizenship;
    string position;
    double height;
};

string normalizeString(const string& s) {
    static const vector<pair<string,char>> table = {
        {"á",'a'},{"à",'a'},{"â",'a'},{"ã",'a'},{"ä",'a'},{"å",'a'},
        {"é",'e'},{"è",'e'},{"ê",'e'},{"ë",'e'},
        {"í",'i'},{"ì",'i'},{"î",'i'},{"ï",'i'},
        {"ó",'o'},{"ò",'o'},{"ô",'o'},{"õ",'o'},{"ö",'o'},
        {"ú",'u'},{"ù",'u'},{"û",'u'},{"ü",'u'},
        {"ý",'y'},{"ÿ",'y'},{"ñ",'n'},{"ç",'c'},{"ß",'s'},
        {"Á",'a'},{"À",'a'},{"Â",'a'},{"Ã",'a'},{"Ä",'a'},{"Å",'a'},
        {"É",'e'},{"È",'e'},{"Ê",'e'},{"Ë",'e'},
        {"Í",'i'},{"Ì",'i'},{"Î",'i'},{"Ï",'i'},
        {"Ó",'o'},{"Ò",'o'},{"Ô",'o'},{"Õ",'o'},{"Ö",'o'},
        {"Ú",'u'},{"Ù",'u'},{"Û",'u'},{"Ü",'u'},
        {"Ý",'y'},{"Ñ",'n'},{"Ç",'c'},
    };
    string result;
    result.reserve(s.size());
    size_t i = 0;
    while (i < s.size()) {
        bool replaced = false;
        for (const auto& p : table) {
            const string& utf = p.first;
            if (s.compare(i, utf.size(), utf) == 0) {
                result += p.second;
                i += utf.size();
                replaced = true;
                break;
            }
        }
        if (!replaced) {
            result += (char)tolower((unsigned char)s[i]);
            i++;
        }
    }
    return result;
}

string parseField(stringstream& ss) {
    string field;
    if (ss.peek() == '"') {
        ss.ignore();
        getline(ss, field, '"');
        ss.ignore();
    } else {
        getline(ss, field, ',');
    }
    return field;
}

vector<Player> loadCSV(const string& filename, int limit = -1) {
    vector<Player> players;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return players;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<string> cols;
        for (int i = 0; i < 34; i++)
            cols.push_back(parseField(ss));
        Player p;
        p.player_id     = cols[0];
        p.player_name   = cols[2];
        p.sort_key      = normalizeString(cols[2]);
        p.date_of_birth = cols[5];
        p.citizenship   = cols[9];
        p.position      = cols[11];
        try {
            p.height = cols[8].empty() ? 0.0 : stod(cols[8]);
        } catch (...) { p.height = 0.0; }
        if (p.player_name.empty()) continue;
        players.push_back(p);
        if (limit > 0 && (int)players.size() >= limit) break;
    }
    return players;
}

vector<Player> makeSorted(vector<Player> v) {
    sort(v.begin(), v.end(), [](const Player& a, const Player& b){
        return a.sort_key < b.sort_key;
    });
    return v;
}
vector<Player> makeReversed(vector<Player> v) {
    sort(v.begin(), v.end(), [](const Player& a, const Player& b){
        return a.sort_key > b.sort_key;
    });
    return v;
}
vector<Player> makeRandom(vector<Player> v) {
    mt19937 rng(42);
    shuffle(v.begin(), v.end(), rng);
    return v;
}

//Insertion Sort
void insertionSort(vector<Player>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        Player key = v[i];
        int j = (int)i - 1;
        while (j >= 0 && v[j].sort_key > key.sort_key) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

//Selection Sort
void selectionSort(vector<Player>& v) {
    size_t n = v.size();
    for (size_t i = 0; i < n - 1; i++) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (v[j].sort_key < v[minIdx].sort_key)
                minIdx = j;
        }
        if (minIdx != i) swap(v[i], v[minIdx]);
    }
}

//Merge-Sort
void mergeSort(vector<Player>& v, int, int) {
    int n = (int)v.size();
    vector<Player> buf(n);
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int l = i;
            int m = min(i + width, n);
            int r = min(i + 2 * width, n);
            if (m >= r) continue;
            // early-exit: último do bloco esquerdo <= primeiro do direito
            if (v[m-1].sort_key <= v[m].sort_key) continue;
            int a = l, b = m, k = l;
            while (a < m && b < r) {
                if (v[a].sort_key <= v[b].sort_key) buf[k++] = v[a++];
                else buf[k++] = v[b++];
            }
            while (a < m) buf[k++] = v[a++];
            while (b < r) buf[k++] = v[b++];
            for (int x = l; x < r; x++) v[x] = buf[x];
        }
    }
}

//Quick-Sort
int partition(vector<Player>& v, int low, int high) {
    int mid = low + (high - low) / 2;
    if (v[mid].sort_key < v[low].sort_key)  swap(v[low], v[mid]);
    if (v[high].sort_key < v[low].sort_key) swap(v[low], v[high]);
    if (v[mid].sort_key < v[high].sort_key) swap(v[mid], v[high]);
    const string pivot = v[high].sort_key;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (v[j].sort_key <= pivot) { i++; swap(v[i], v[j]); }
    }
    swap(v[i + 1], v[high]);
    return i + 1;
}
void quickSort(vector<Player>& v, int low, int high) {
    if (low < high) {
        int pi = partition(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

double runBenchmark(vector<Player> data, const string& algo) {
    auto start = chrono::high_resolution_clock::now();
    if      (algo == "Insertion Sort") insertionSort(data);
    else if (algo == "Selection Sort") selectionSort(data);
    else if (algo == "Merge Sort")     mergeSort(data, 0, (int)data.size()-1);
    else if (algo == "Quick Sort")     quickSort(data, 0, (int)data.size()-1);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0;
}

int main() {
    const string filename = "BD_Jogadores/player_profiles/player_profiles.csv";

    cout << "==================================================" << endl;
    cout << "  BENCHMARK DE ALGORITMOS DE ORDENACAO" << endl;
    cout << "  Dataset: Transfermarkt - player_profiles.csv" << endl;
    cout << "  Atributo: player_name (ordem alfabetica)" << endl;
    cout << "==================================================" << endl;

    vector<int>    sizes     = {1000, 10000, 50000, 92000};
    vector<string> slowAlgos = {"Insertion Sort", "Selection Sort"};
    vector<string> fastAlgos = {"Merge Sort", "Quick Sort"};
    int slowLimit = 10000;

    cout << fixed << setprecision(3);

    for (int size : sizes) {
        cout << "\n--------------------------------------------------" << endl;
        cout << "  Tamanho: " << size << " jogadores" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << setw(18) << "Algoritmo"
             << setw(15) << "Aleatorio(ms)"
             << setw(15) << "Ordenado(ms)"
             << setw(15) << "Reverso(ms)" << endl;
        cout << string(63, '-') << endl;

        cout << "  Carregando " << size << " registros..." << flush;
        vector<Player> base = loadCSV(filename, size);
        cout << " OK (" << base.size() << " carregados)" << endl;

        auto sorted   = makeSorted(base);
        auto reversed = makeReversed(base);
        auto rnd      = makeRandom(base);

        if (size <= slowLimit) {
            for (const auto& algo : slowAlgos) {
                double tRand = runBenchmark(rnd,      algo);
                double tSort = runBenchmark(sorted,   algo);
                double tRev  = runBenchmark(reversed, algo);
                cout << setw(18) << algo
                     << setw(15) << tRand
                     << setw(15) << tSort
                     << setw(15) << tRev << endl;
            }
        } else {
            for (const auto& algo : slowAlgos)
                cout << setw(18) << algo
                     << setw(15) << "N/A (lento)"
                     << setw(15) << "N/A (lento)"
                     << setw(15) << "N/A (lento)" << endl;
        }

        for (const auto& algo : fastAlgos) {
            double tRand = runBenchmark(rnd,      algo);
            double tSort = runBenchmark(sorted,   algo);
            double tRev  = runBenchmark(reversed, algo);
            cout << setw(18) << algo
                 << setw(15) << tRand
                 << setw(15) << tSort
                 << setw(15) << tRev << endl;
        }
    }

    cout << "\n==================================================" << endl;
    cout << "  Benchmark concluido!" << endl;
    cout << "==================================================" << endl;

    return 0;
}
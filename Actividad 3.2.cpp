#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <iomanip> // Para setw()
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // Definimos INF como infinito

// Implementación del algoritmo de Dijkstra como lo tenías
void dijkstra(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF); // Distancia mínima inicializada a infinito
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != -1) { // Hay una arista de u a v
                int alt = dist[u] + graph[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    pq.push({ alt, v });
                }
            }
        }
    }

    // Imprimimos las distancias desde el nodo start
    for (int i = 0; i < n; i++) {
        if (i != start) {
            cout << "node " << setw(1) << start + 1 << " to node " << setw(1) << i + 1 << " : ";
            if (dist[i] == INF) {
                cout << setw(3) << "-1" << endl;
            }
            else {
                cout << setw(3) << dist[i] << endl;
            }
        }
    }
}

// Implementación del algoritmo de Floyd-Warshall
void floydWarshall(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist = graph;

    // Inicializamos las distancias: -1 en la matriz se convierte en INF (infinito)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == -1 && i != j) {
                dist[i][j] = INF;
            }
        }
    }

    // Algoritmo de Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Imprimimos la matriz de distancias con formato
    cout << "Floyd-Warshall:\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << setw(4) << "-1";
            }
            else {
                cout << setw(4) << dist[i][j];
            }
        }
        cout << endl;
    }
}

int main() {
    ifstream inputFile("in.txt");
    if (!inputFile) {
        cerr << "Error al abrir el archivo 'in.txt'" << endl;
        return 1;
    }

    int n;
    inputFile >> n;
    vector<vector<int>> graph(n, vector<int>(n));

    // Lectura de la matriz de adyacencia desde el archivo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> graph[i][j];
        }
    }

    inputFile.close();

    // Aplicamos Dijkstra para cada nodo
    cout << "Dijkstra :" << endl;
    for (int i = 0; i < n; i++) {
        dijkstra(graph, i);
    }

    // Aplicamos Floyd-Warshall para obtener la matriz de distancias mínimas
    floydWarshall(graph);

    return 0;

}

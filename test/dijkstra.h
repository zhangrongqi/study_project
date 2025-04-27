#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

void dijkstra(const vector<vector<pii>>& graph, int start_vertex) {
    int num_vertices = graph.size();
    vector<int> distances(num_vertices, INT_MAX);
    distances[start_vertex] = 0;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({ 0, start_vertex });

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();

        if (current_distance > distances[current_vertex]) {
            continue;
        }

        for (const auto& neighbor : graph[current_vertex]) {
            int neighbor_vertex = neighbor.first;
            int weight = neighbor.second;
            int distance = current_distance + weight;

            if (distance < distances[neighbor_vertex]) {
                distances[neighbor_vertex] = distance;
                pq.push({ distance, neighbor_vertex });
            }
        }
    }

    // 输出结果
    for (int i = 0; i < num_vertices; ++i) {
        cout << "顶点 " << i << " 到起点的最短距离是: " << distances[i] << endl;
    }
}

//#include "dijkstra.h"   
//
//int main() {
//    int num_vertices = 4;
//    vector<vector<pii>> graph(num_vertices);
//
//    // 添加边
//    graph[0].push_back({ 1, 1 });
//    graph[0].push_back({ 2, 4 });
//    graph[1].push_back({ 0, 1 });
//    graph[1].push_back({ 2, 2 });
//    graph[1].push_back({ 3, 5 });
//    graph[2].push_back({ 0, 4 });
//    graph[2].push_back({ 1, 2 });
//    graph[2].push_back({ 3, 1 });
//    graph[3].push_back({ 1, 5 });
//    graph[3].push_back({ 2, 1 });
//
//    dijkstra(graph, 0);
//
//    return 0;
//}
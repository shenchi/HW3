#include <iostream>

#include "Array.h"
#include "BinaryHeap.h"
#include "Graph.h"
#include "Dijkstra.h"

using namespace std;


void TestArray()
{
	cout << "Test for Array<int>:" << endl;
	hw3::Array<int> a(10);

	cout << "current size: " << a.Size() << endl;
	cout << "content: [ ";
	for (size_t i = 0; i < a.Size(); ++i)
		cout << a[i] << ' ';
	cout << ']' << endl;

	a.Clear();
	a.Push(5);
	a.Push(4);
	a.Push(3);
	a.Push(2);
	a.Push(1);
	cout << "current size: " << a.Size() << endl;
	cout << "content: [ ";
	for (size_t i = 0; i < a.Size(); ++i)
		cout << a[i] << ' ';
	cout << ']' << endl << endl;
}

void TestBinaryHeap()
{
	cout << "Test for BinearyHeap<int>:" << endl;
	hw3::BinaryHeap<int> bin;

	bin.Insert(1);
	bin.Insert(3);
	bin.Insert(5);
	bin.Insert(4);
	bin.Insert(2);

	cout << "delete sequence: [ ";
	while (!bin.Empty())
	{
		cout << bin.Delete() << ' ';
	}
	cout << ']' << endl << endl;
}

void TestGraphAndDijkstra()
{
	cout << "Test for Graph<float> and Dijkstra:" << endl;
	hw3::Graph<float> graph(6);
	graph.SetWeight(0, 1, 7);
	graph.SetWeight(0, 2, 9);
	graph.SetWeight(0, 5, 14);
	graph.SetWeight(1, 2, 10);
	graph.SetWeight(1, 3, 15);
	graph.SetWeight(2, 3, 11);
	graph.SetWeight(2, 5, 2);
	graph.SetWeight(3, 4, 6);
	graph.SetWeight(4, 5, 9);

	auto path = hw3::Dijkstra<hw3::Graph, float>(graph, 0, 4);

	cout << "Path found: [ ";
	while (!path.Empty())
	{
		cout << path.Pop() << ' ';
	}
	cout << ']' << endl << endl;
}

int main(int argc, char** argv)
{
	TestArray();

	TestBinaryHeap();

	TestGraphAndDijkstra();

	system("Pause");
	return 0;
}

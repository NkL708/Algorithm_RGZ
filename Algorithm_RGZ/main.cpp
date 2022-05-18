#include <iostream>
#include "graph.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Graph<int, std::string> graph(Graph<int, std::string>::PresentationForm::mGraph);
	std::vector<int> vertexes;
	int value;
	int sw = 0;
	bool exit = false;

	std::string menu[] =
	{
		"1. Вывести граф\n",
		"2. Вставить вершину\n"
	};

	//std::string iteratorMenu[]
	//{

	//};

	//std::string reverseIteratorMenu[]
	//{

	//};

	//std::string extraMenu[]
	//{

	//};

	while (!exit)
	{
		for (int i = 0; i < sizeof(menu) / sizeof(std::string); i++)
		{
			std::cout << menu[i];
		}
		std::cin >> sw;
		switch (sw)
		{
		case 1:
			graph.printGraph();
			break;
		case 2:
			std::cout << "Введите смежные вершины ";
			while (std::cin >> value && value != -1) 
			{
				vertexes.insert(vertexes.begin(), value);
			}
			graph.insertVertex(vertexes);
			break;
		default:
			break;
		}
	}
	return 0;
}
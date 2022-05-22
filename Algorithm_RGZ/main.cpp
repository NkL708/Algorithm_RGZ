#include "graph.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	Graph<int, std::string> graph(Graph<int, std::string>::GraphForm::listGraph);
	Graph<int, std::string>::EdgeIterator edgeIterator;
	Graph<int, std::string>::VertexIterator vertexIterator;
	std::vector<int> v;
	int dir;
	int begin, end;
	int value;
	int sw = 0;
	bool exit = false;
	
	// Debug
	//graph.insertVertex(std::vector<int> { });
	//graph.insertVertex(std::vector<int> {0});
	//graph.insertVertex(std::vector<int> {1});
	//graph.insertVertex(std::vector<int> {0, 1, 2});

	graph.insertVertex(std::vector<int> { });
	graph.insertVertex(std::vector<int> {0});
	graph.insertVertex(std::vector<int> {1});
	graph.insertVertex(std::vector<int> {2});
	graph.insertVertex(std::vector<int> {0, 1, 3});
	graph.insertVertex(std::vector<int> {3});

	std::string menu[] =
	{
		"\n\tМЕНЮ\n",
		"\t1. Вывести граф\n",
		"\t2. Добавить вершину\n",
		"\t3. Удалить вершину\n",
		"\t4. Добавить ребро\n",
		"\t5. Удалить ребро\n",
		"\t6. Очистить граф\n",
		"\t7. Меню статистики\n",
		"\t8. Меню преобразований\n",
		"\t9. Меню итератора рёбер\n",
		"\t10. Меню итератора вершин\n",
		"\t11. Меню дополнительных операций\n",
		"\t0. Выход из программы\n\n"
	};

	std::string constructorMenu[]
	{
		"\n\t1. Создать граф без рёбер\n",
		"\t2. Преобразовать матрицу в список рёбер\n",
		"\t3. Преобразовать список рёбер в матрицу\n",
		"\t4. Создать граф со случайными рёбрами\n",
		"\t0. Вернуться обратно\n\n"
	};

	std::string statisticMenu[]
	{
		"\n\t1. Вывести количество вершин\n",
		"\t2. Вывести количество рёбер\n",
		"\t3. Вывести коэффициент насыщенности графа\n",
		"\t4. Форма представления графа\n",
		"\t0. Вернуться обратно\n\n"
	};

	std::string eIteratorMenu[]
	{
		"\n\t1. Установить итератор в начало\n",
		"\t2. Установить итератор в конец\n",
		"\t3. Выполнить ++\n",
		"\t4. Вывести значение итератора\n",
		"\t0. Вернуться обратно\n\n"
	};

	std::string vIteratorMenu[]
	{
		"\n\t1. Установить итератор в начало\n",
		"\t2. Установить итератор в конец\n",
		"\t3. Выполнить ++\n",
		"\t4. Вывести значение итератора\n",
		"\t0. Вернуться обратно\n\n"
	};

	std::string extraMenu[]
	{
		"\n\t1. Найти все простые циклы, включающие заданную вершину орграфа\n",
		"\t2. Найти периферии взвешенного орграфа на основе алгоритма Дейкстры\n",
		"\t0. Вернуться обратно\n\n"
	};

	while (!exit)
	{
		for (int i = 0; i < sizeof(menu) / sizeof(std::string); i++)
		{
			std::cout << menu[i];
		}
		std::cout << "Введите номер операции: ";
		std::cin >> sw;
		switch (sw)
		{
		case 1:
			graph.printGraph();
			break;
		case 2:
			std::cout << "Введите смежные вершины\n";
			while (std::cin >> value && value != -1) 
			{
				v.insert(v.begin(), value);
			}
			graph.insertVertex(v);
			v.clear();
			break;
		case 3:
			std::cout << "Введите номер вершины: ";
			std::cin >> value;
			graph.deleteVertex(value);
			break;
		case 4:
			std::cout << "Введите номер первой вершины: ";
			std::cin >> begin;
			std::cout << "Введите номер второй вершины: ";
			std::cin >> end;
			std::cout << "\n0. В обе стороны\n"
				<< "1. В сторону начала ребра\n"
				<< "2. В сторону конца ребра\n"
				<< "Введите направление ребра: ";
			std::cin >> dir;
			std::cout << "Введите вес ребра: ";
			std::cin >> value;
			graph.insertEdge(begin, end, (Graph<int, std::string>::Direction)dir, value);
			break;
		case 5:
			std::cout << "Введите номер первой вершины: ";
			std::cin >> begin;
			std::cout << "Введите номер второй вершины: ";
			std::cin >> end;
			graph.deleteEdge(begin, end);
			break;
		case 6:
			graph.clear();
			break;
		case 7:
			while (!exit)
			{
				for (int i = 0; i < sizeof(statisticMenu) / sizeof(std::string); i++)
				{
					std::cout << statisticMenu[i];
				}
				std::cout << "Введите номер операции: ";
				std::cin >> sw;
				switch (sw)
				{
				case 1:
					std::cout << graph.getGraphVCount() << "\n";
					break;
				case 2:
					std::cout << graph.getGraphECount() << "\n";
					break;
				case 3:
					std::cout << graph.countSaturation() << "\n";
					break;
				case 4:
					if (graph.getGraphForm() == Graph<int, std::string>::GraphForm::matrixGraph)
						std::cout << "M - граф\n";
					else
						std::cout << "L - граф\n";
					break;
				case 0:
					exit = true;
					break;
				default:
					std::cout << "Данной операции не существует\n";
					break;
				}
			}
			exit = false;
			break;
		case 8:
			while (!exit)
			{
				int form;
				int orientation;
				for (int i = 0; i < sizeof(constructorMenu) / sizeof(std::string); i++)
				{
					std::cout << constructorMenu[i];
				}
				std::cout << "Введите номер операции: ";
				std::cin >> sw;
				switch (sw)
				{
				case 1:
					std::cout << "\nВведите количество вершин: ";
					std::cin >> value;
					std::cout << "\n0. Ориентированный\n"
						<< "1. Не ориентированный\n"
						<< "Введите ориентацию графа: ";
					std::cin >> orientation;
					std::cout << "\n0. L-граф\n"
						<< "1. M-граф\n"
						<< "Введите форму представления: ";
					std::cin >> form;
					graph.clear();
					graph = Graph<int, std::string>(value, (Graph<int, std::string>::GraphForm) form);
					break;
				case 2:
					graph.toListGraph();
					break;
				case 3:
					graph.toMatrixGraph();
					break;
				case 4:
					std::cout << "Не реализовано\n";
					break;
				case 0:
					exit = true;
					break;
				default:
					std::cout << "Данной операции не существует\n";
					break;
				}
			}
			exit = false;
			break;
		case 9:
			while (!exit)
			{
				for (int i = 0; i < sizeof(eIteratorMenu) / sizeof(std::string); i++)
				{
					std::cout << eIteratorMenu[i];
				}
				std::cout << "Введите номер операции: ";
				std::cin >> sw;
				switch (sw)
				{
				case 1:
					edgeIterator = graph.eBegin();
					break;
				case 2:
					edgeIterator = graph.eEnd();
					break;
				case 3:
					edgeIterator++;
					break;
				case 4:
					std::cout << (*edgeIterator)->getBegin()->getData() << " " 
						<< (*edgeIterator)->getEnd()->getData() << std::endl;
					break;
				case 0:
					exit = true;
					break;
				default:
					std::cout << "Данной операции не существует\n";
					break;
				}
			}
			exit = false;
			break;
		case 10:
			while (!exit)
			{
				for (int i = 0; i < sizeof(vIteratorMenu) / sizeof(std::string); i++)
				{
					std::cout << vIteratorMenu[i];
				}
				std::cout << "Введите номер операции: ";
				std::cin >> sw;
				switch (sw)
				{
				case 1:
					vertexIterator = graph.vBegin();
					break;
				case 2:
					vertexIterator = graph.vEnd();
					break;
				case 3:
					vertexIterator++;
					break;
				case 4:
					std::cout << (* vertexIterator)->getData() << std::endl;
					break;
				case 0:
					exit = true;
					break;
				default:
					std::cout << "Данной операции не существует\n";
					break;
				}
			}
			exit = false;
			break;
		case 11:
			while (!exit)
			{
				for (int i = 0; i < sizeof(extraMenu) / sizeof(std::string); i++)
				{
					std::cout << extraMenu[i];
				}
				std::cout << "Введите номер операции: ";
				std::cin >> sw;
				switch (sw)
				{
				case 1:
					std::cout << "Введите номер вершины: ";
					std::cin >> value;
					graph.findCycles(value, value, value, v);
					v.clear();
					break;
				case 2:
					graph.findGraphPCycles();
					break;
				case 0:
					exit = true;
					break;
				default:
					std::cout << "Данной операции не существует\n";
					break;
				}
			}
			exit = false;
			break;
		case 0:
			exit = true;
			break;
		default:
			std::cout << "Данной операции не существует\n";
			break;
		}
	}
	return 0;
}
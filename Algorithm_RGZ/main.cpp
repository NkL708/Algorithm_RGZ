#include <iostream>
#include "graph.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Graph<int, std::string> graph(Graph<int, std::string>::GraphForm::lGraph);
	std::vector<int> v;
	int begin, end;
	int value;
	int sw = 0;
	bool exit = false;

	std::string menu[] =
	{
		"\n\t����\n"
		"\t1. ������� ����\n",
		"\t2. �������� �������\n",
		"\t3. ������� �������\n",
		"\t4. �������� �����\n",
		"\t5. ������� �����\n",
		"\t6. �������� ����\n",
		"\t7. ���� ����������\n",
		"\t8. ���� �������������\n",
		"\t9. ���� �������������\n",
		"\t10. ���� �������������\n",
		"\t0. ����� �� ���������\n\n"
	};

	std::string constructorMenu[]
	{
		"\n\t1. ������� ���� ��� ����\n",
		"\t2. ������� ���� �� ���������� ������\n",
		"\t0. ��������� �������\n\n"
	};

	std::string statisticMenu[]
	{
		"\n\t1. ������� ���������� ������\n",
		"\t2. ������� ���������� ����\n",
		"\t3. ������� ����������� ������������ �����\n",
		"\t4. ����� ������������� �����\n",
		"\t5. ���������� �����\n",
		"\t0. ��������� �������\n\n"
	};

	std::string iteratorMenu[]
	{
		"\n\t1. ������� ��������\n",
		"\n\t2. ��������� iterator++\n",
		"\t0. ��������� �������\n\n"
	};

	std::string reverseIteratorMenu[] 
	{
		"\n\t1. ������� �������� ��������\n",
		"\n\t2. ��������� reverseIterator++\n",
		"\t0. ��������� �������\n\n"
	};

	//graph.insertVertex(std::vector<int> { });
	//graph.insertVertex(std::vector<int> {0});
	//graph.insertVertex(std::vector<int> {1});
	//graph.insertVertex(std::vector<int> {0, 1, 2});

	while (!exit)
	{
		for (int i = 0; i < sizeof(menu) / sizeof(std::string); i++)
		{
			std::cout << menu[i];
		}
		std::cout << "������� ����� ��������: ";
		std::cin >> sw;
		switch (sw)
		{
		case 1:
			graph.printGraph();
			break;
		case 2:
			std::cout << "������� ������� �������\n";
			while (std::cin >> value && value != -1) 
			{
				v.insert(v.begin(), value);
			}
			graph.insertVertex(v);
			v.clear();
			break;
		case 3:
			std::cout << "������� ����� �������: ";
			std::cin >> value;
			graph.deleteVertex(value);
			break;
		case 4:
			std::cout << "������� ����� ������ �������: ";
			std::cin >> begin;
			std::cout << "������� ����� ������ �������: ";
			std::cin >> end;
			graph.insertEdge(begin, end);
			break;
		case 5:
			std::cout << "������� ����� ������ �������: ";
			std::cin >> begin;
			std::cout << "������� ����� ������ �������: ";
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
				std::cout << "������� ����� ��������: ";
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
					if (graph.getGraphForm() == Graph<int, std::string>::GraphForm::mGraph)
						std::cout << "M - ����\n";
					else
						std::cout << "L - ����\n";
					break;
				case 5:
					if (graph.getGraphOrientation() == Graph<int, std::string>::GraphOrientation::oriented)
						std::cout << "��������������� ����\n";
					else
						std::cout << "�� ��������������� ����\n";
					break;
				case 0:
					exit = true;
					break;
				default:
					std::cout << "������ �������� �� ����������\n";
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
				std::cout << "������� ����� ��������: ";
				std::cin >> sw;
				switch (sw)
				{
				case 1:
					std::cout << "\n������� ���������� ������: ";
					std::cin >> value;
					std::cout << "\n0. ���������������\n"
						<< "1. �� ���������������\n"
						<< "������� ���������� �����: ";
					std::cin >> orientation;
					std::cout << "\n0. L-����\n"
						<< "1. M-����\n"
						<< "������� ����� �������������: ";
					std::cin >> form;
					graph.clear();
					graph = Graph<int, std::string>(value, (Graph<int, std::string>::GraphOrientation) orientation,
						(Graph<int, std::string>::GraphForm) form);
					break;
				case 0:
					exit = true;
					break;
				default:
					std::cout << "������ �������� �� ����������\n";
					break;
				}
			}
			exit = false;
			break;
		case 0:
			exit = true;
			break;
		default:
			std::cout << "������ �������� �� ����������\n";
			break;
		}
	}
	return 0;
}
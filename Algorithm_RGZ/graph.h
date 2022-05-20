#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

// L-���� = ������ ����
// M-���� = ������� ���������

template <typename Data, typename Name>
class Graph
{
public:

	enum class GraphForm
	{
		listGraph,
		matrixGraph
	};

	enum class Direction 
	{
		toBoth,
		toBeg,
		toEnd
	};
private:
	class Vertex
	{
		Name name;
		Data data;
		int index;
	public:
		Vertex();
		Vertex(Name name, Data data);
		std::string getName();
		Data getData();
		void setName(std::string name);
		void setData(Data data);
	};
	class Edge
	{
		Vertex* begin;
		Vertex* end;
		int weight = 0;
		Data data = 0;
	public:
		Edge(Vertex* begin, Vertex* end);
		Edge(Vertex* begin, Vertex* end, int weight);
		Edge(Vertex* begin, Vertex* end, int weight, Data data);
		Vertex* getBegin();
		Vertex* getEnd();
		int getWeight();
		void setWeight(int weight);
		Data getData();
		void setData(Data data);
	};
public:
	class VertexIterator
	{
	public:
		Graph* gPtr;
		Vertex* vPtr;
		VertexIterator(Vertex* vPtr = nullptr, Graph* gPtr = nullptr);
		// To do
		Vertex* operator*();
		void operator++(int);
	};
	VertexIterator vBegin();
	VertexIterator vEnd();

	class EdgeIterator
	{
	public:
		Graph* gPtr;
		Edge* ePtr;
		EdgeIterator(Edge* ePtr = nullptr, Graph* gPtr = nullptr);
		// To do
		Edge* operator*();
		void operator++(int);
	};
	EdgeIterator eBegin();
	EdgeIterator eEnd();
private:
	// Types of graphs
	GraphForm form = GraphForm::listGraph;
	// For M-graph
	std::vector<Vertex*> vList;
	std::vector<std::vector<int>> matrix;
	std::vector<Data> vNumList;
	// For L-graph
	std::vector<Edge*> eList;
	int vCount = 0;
	int eCount = 0;

public:
	// Constructors
	Graph();
	Graph(GraphForm form);
	Graph(int vertexCount, GraphForm form);
	Graph(int vertexCount, int edgeCount, GraphForm form);
	Graph(const Graph& obj);
	~Graph();
	
	GraphForm getGraphForm();
	// Statistic
	int getGraphVCount();
	int getGraphECount();
	double countSaturation();
	// Basic methods
	void toListGraph();
	void toMatrixGraph();
	void insertVertex(std::vector<Data> vEdges);
	void deleteVertex(Data vertex);
	void insertEdge(Data begin, Data end, Direction dir);
	void deleteEdge(Data begin, Data end);
	Edge* getEdge(Data begin, Data end);
	Vertex* getVertex(Data vertex);
	void printGraph();
	void clear();
	// My option task
	void findCycles(int vNum);
};

template<typename Data, typename Name>
Graph<Data, Name>::Graph()
{
	form = GraphForm::listGraph;
}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(int vertexCount, GraphForm form)
{
	this->form = form;
	for (int i = 0; i < vertexCount; i++)
	{
		this->insertVertex(std::vector<Data> {});
	}
}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(int vertexCount, int edgeCount, GraphForm form)
{
	this->vCount = vertexCount;
	this->eCount = edgeCount;
	this->form = form;
}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(GraphForm form)
{
	this->form = form;
}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(const Graph& obj)
{

}

template<typename Data, typename Name>
Graph<Data, Name>::~Graph()
{
	clear();
}

template<typename Data, typename Name>
inline int Graph<Data, Name>::getGraphVCount()
{
	return vCount;
}

template<typename Data, typename Name>
inline int Graph<Data, Name>::getGraphECount()
{
	return eCount;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::GraphForm Graph<Data, Name>::getGraphForm()
{
	return form;
}

template<typename Data, typename Name>
inline double Graph<Data, Name>::countSaturation()
{
	return eCount / (double) vCount;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::toListGraph()
{
	eList.clear();
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == 1)
			{
				matrix[i][j] = 0;
				matrix[j][i] = 0;
				Edge* edge = new Edge(vList[i], vList[j]);
				eList.insert(eList.end(), edge);
			}
		}
	}
	form = GraphForm::listGraph;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::toMatrixGraph()
{
	// create matrix
	matrix.clear();
	for (int i = 0; i < eCount - 1; i++)
	{
		matrix.insert(matrix.end(), std::vector<int>(eCount - 1));
	}
	for (int i = 0; i < eList.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			for (int k = 0; k < matrix[j].size(); k++)
			{
				if ((eList[i]->getBegin()->getData() == vNumList[k] && eList[i]->getEnd()->getData() == vNumList[j]) ||
					(eList[i]->getBegin()->getData() == vNumList[j] && eList[i]->getEnd()->getData() == vNumList[k]))
				{
					matrix[j][k] = 1;
					matrix[k][j] = 1;
				}
			}
		}
	}
	form = GraphForm::matrixGraph;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::insertVertex(std::vector<Data> vEdges)
{
	// generating unique graphVNum
	int vertexNum = 0;
	if (vNumList.size()) 
	{
		int maxVnum = *std::max_element(vNumList.begin(), vNumList.end());
		for (int i = 0; i <= maxVnum + 1; i++)
		{
			if (std::find(vNumList.begin(), vNumList.end(), i) == vNumList.end())
			{
				vertexNum = i;
				break;
			}
		}
	}
	Vertex* newVertex = new Vertex(std::to_string(vertexNum), vertexNum);
	vList.insert(vList.end(), newVertex);
	vNumList.insert(vNumList.end(), vertexNum);
	std::vector<int> newRow;
	if (form == GraphForm::matrixGraph)
	{
		if (vCount > 0) 
		{
			// appending to rows
			for (int i = 0; i < vNumList.size() - 1; i++)
			{
				if (std::find(vEdges.begin(), vEdges.end(), vNumList[i]) != vEdges.end())
					matrix[i].insert(matrix[i].end(), 1);
				else 
					matrix[i].insert(matrix[i].end(), 0);
			}
			// new row
			matrix.insert(matrix.end(), newRow);
			int rowI = vCount;
			for (int i = 0; i < vNumList.size(); i++)
			{
				if (std::find(vEdges.begin(), vEdges.end(), vNumList[i]) != vEdges.end())
					matrix[rowI].insert(matrix[rowI].end(), 1);
				else
					matrix[rowI].insert(matrix[rowI].end(), 0);
			}
		}
		// empty matrix
		else
		{
			newRow.insert(newRow.begin(), 0);
			matrix.insert(matrix.begin(), newRow);
		}
	}
	else 
	{
		if (vCount > 0) 
		{
			for (int i = 0; i < vEdges.size(); i++)
			{
				Vertex* end = nullptr;
				for (int j = 0; j < vList.size(); j++)
				{
					if (vList[j]->getData() == vEdges[i])
						end = vList[j];
				}
				Edge* newEdge = new Edge(newVertex, end);
				eList.insert(eList.end(), newEdge);
			}
		}
	}
	eCount += vEdges.size();
	vCount++;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::deleteVertex(Data vertex)
{
	if (form == GraphForm::matrixGraph)
	{
		// deleting row
		for (int i = 0; i < matrix.size(); i++)
		{
			if (vNumList[i] == vertex) 
			{
				matrix.erase(matrix.begin() + i);
				break;
			}
		}
		// deleting columns from rows
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if (vNumList[j] == vertex)
				{
					matrix[i].erase(matrix[i].begin() + j);
					eCount--;
					break;
				}
			}
		}
		// delete vertex from vList
		for (int i = 0; i < vList.size(); i++)
		{
			if (vList[i]->getData() == vertex)
				vList.erase(vList.begin() + i);
		}
	}
	else
	{
		for (int i = 0; i < eList.size(); i++)
		{
			if (eList[i]->getBegin()->getData() == vertex || eList[i]->getEnd()->getData() == vertex) 
			{
				eList.erase(eList.begin() + i);
				i--;
				continue;
			}
		}
	}
	vNumList.erase(std::find(vNumList.begin(), vNumList.end(), vertex));
	vCount--;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::insertEdge(Data begin, Data end, Direction dir)
{
	if (form == GraphForm::matrixGraph)
	{
		// add edge to row and column
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if (vNumList[i] == begin && vNumList[j] == end) 
				{
					if (dir == Direction::toBoth) 
					{
						matrix[i][j] = 1;
						matrix[j][i] = 1;
					}
					else if (dir == Direction::toEnd)
						matrix[i][j] = 1;
					else if (dir == Direction::toBeg)
						matrix[j][i] = 1;
				}
			}
		}
	}
	else
	{
		Vertex* vBegin = nullptr, * vEnd = nullptr;
		for (int i = 0; i < vList.size(); i++)
		{
			if (vList[i]->getData() == begin)
				vBegin = vList[i];
		}
		for (int i = 0; i < vList.size(); i++)
		{
			if (vList[i]->getData() == end)
				vEnd = vList[i];
		}
		Edge* edge = new Edge(vBegin, vEnd);
		eList.insert(eList.end(), edge);
	}
	eCount++;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::deleteEdge(Data begin, Data end)
{
	if (form == GraphForm::matrixGraph)
	{
		// add edge to row and column
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if ((vNumList[i] == begin && vNumList[j] == end) ||
					(vNumList[i] == end && vNumList[j] == begin))
				{
					matrix[i][j] = 0;
				}
			}
		}
	}
	else
	{
		Vertex* vBegin = nullptr, * vEnd = nullptr;
		for (int i = 0; i < eList.size(); i++)
		{
			if ((eList[i]->getBegin()->getData() == begin && eList[i]->getEnd()->getData() == end) ||
				(eList[i]->getBegin()->getData() == end && eList[i]->getEnd()->getData() == begin))
				eList.erase(eList.begin() + i);
		}
	}
	eCount--;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Edge* Graph<Data, Name>::getEdge(Data begin, Data end)
{
	for (int i = 0; i < eList.size(); i++)
	{
		if ((eList[i]->getBegin()->getData() == begin && eList[i]->getEnd()->getData() == end) ||
			(eList[i]->getBegin()->getData() == end && eList[i]->getEnd()->getData() == begin))
			return eList[i];
	}
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Vertex* Graph<Data, Name>::getVertex(Data vertex)
{
	for (int i = 0; i < vList.size(); i++)
	{
		if (vList[i]->getData() == vertex)
			return vList[i];
	}
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::printGraph()
{
	if (form == GraphForm::matrixGraph)
	{
		if (!vCount) 
		{
			std::cout << "������� ��������� �����!\n";
			return;
		}
		std::cout << "\n������� ���������:\n" << std::setw(5);
		// Vertexes numbers
		for (int i = 0; i < vNumList.size(); i++)
		{
			std::cout << vNumList[i] << " ";
		}
		std::cout << "\n" << std::setw(5);
		for (int i = 0; i < matrix[0].size(); i++)
		{
			std::cout << "--";
		}
		// matrix print
		for (int i = 0; i < matrix.size(); i++)
		{
			std::cout << "\n" << vNumList[i] << " | ";
			for (int j = 0; j < matrix[i].size(); j++)
			{
				std::cout << matrix[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	else 
	{
		if (!eCount)
		{
			std::cout << "������ ��������� ����!\n";
			return;
		}
		std::cout << "\n������ ���������:\n";
		// Vertexes numbers
		std::cout << std::setw(10) << "begin ";
		std::cout << "end ";
		std::cout << "\n" << std::setw(5);
		for (int i = 0; i < eList.size(); i++)
		{
			std::cout << "--";
		}
		// matrix print
		for (int i = 0; i < eList.size(); i++)
		{
			std::cout << "\n" << i << " | ";
			std::cout << std::setw(3) << eList[i]->getBegin()->getData() 
				<< std::setw(5) << eList[i]->getEnd()->getData();
		}
		std::cout << std::endl;
	}
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::clear()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		matrix[i].clear();
	}
	matrix.clear();
	vNumList.clear();
	vList.clear();
	eList.clear();
	vCount = 0;
	eCount = 0;
}

// �������� 21.05.22
template<typename Data, typename Name>
inline void Graph<Data, Name>::findCycles(int vNum)
{
	std::vector<int> results;
	int rowI;
	// get index in matrix
	for (int i = 0; i < vNumList.size(); i++)
	{
		if (vNumList[i] == vNum)
			rowI = i;
	}
	int vNumPrev;
	for (int colI = 0; colI < vNumList.size(); colI++)
	{
		vNumPrev = vNumList[rowI];

	}
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Vertex::Vertex()
{

}

template<typename Data, typename Name>
inline Graph<Data, Name>::Vertex::Vertex(Name name, Data data)
{
	this->name = name;
	this->data = data;
}

template<typename Data, typename Name>
inline std::string Graph<Data, Name>::Vertex::getName()
{
	return name;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::Vertex::setName(std::string name)
{
	this->name = name;
}

template<typename Data, typename Name>
inline Data Graph<Data, Name>::Vertex::getData()
{	
	return data;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::Vertex::setData(Data data)
{
	this->data = data;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Edge::Edge(Vertex* begin, Vertex* end)
{
	this->begin = begin;
	this->end = end;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Edge::Edge(Vertex* begin, Vertex* end, int weight)
{
	this->begin = begin;
	this->end = end;
	this->weight = weight;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Edge::Edge(Vertex* begin, Vertex* end, int weight, Data data)
{
	this->begin = begin;
	this->end = end;
	this->weight = weight;
	this->data = data;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Vertex* Graph<Data, Name>::Edge::getBegin()
{
	return begin;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Vertex* Graph<Data, Name>::Edge::getEnd()
{
	return end;
}

template<typename Data, typename Name>
inline int Graph<Data, Name>::Edge::getWeight()
{
	return weight;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::Edge::setWeight(int weight)
{
	this->weight = weight;
}

template<typename Data, typename Name>
inline Data Graph<Data, Name>::Edge::getData()
{
	return data;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::Edge::setData(Data data)
{
	this->data = data;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::VertexIterator::VertexIterator(Vertex* vPtr, Graph* gPtr)
{
	this->vPtr = vPtr;
	this->gPtr = gPtr;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Vertex* Graph<Data, Name>::VertexIterator::operator*()
{
	return vPtr;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::VertexIterator::operator++(int)
{
	for (int i = 0; i < gPtr->vList.size() - 1; i++)
	{
		if (gPtr->vList[i]->getData() == vPtr->getData()) 
		{
			this->vPtr = gPtr->vList[i + 1];
			return;
		}
	}
}

template<typename Data, typename Name>
inline Graph<Data, Name>::EdgeIterator::EdgeIterator(Edge* ePtr, Graph* gPtr)
{
	this->ePtr = ePtr;
	this->gPtr = gPtr;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Edge* Graph<Data, Name>::EdgeIterator::operator*()
{
	return ePtr;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::EdgeIterator::operator++(int)
{
	for (int i = 0; i < gPtr->eList.size() - 1; i++)
	{
		if ((gPtr->eList[i]->getBegin()->getData() == ePtr->getBegin()->getData()) &&
			(gPtr->eList[i]->getEnd()->getData() == ePtr->getEnd()->getData())) 
		{
			this->ePtr = gPtr->eList[i + 1];
			return;
		}
	}
}

template<typename Data, typename Name>
inline Graph<Data, Name>::VertexIterator Graph<Data, Name>::vBegin()
{
	VertexIterator it{};
	it.vPtr = vList.front();
	it.gPtr = this;
	return it;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::VertexIterator Graph<Data, Name>::vEnd()
{
	VertexIterator it{};
	it.vPtr = vList.back();
	it.gPtr = this;
	return it;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::EdgeIterator Graph<Data, Name>::eBegin()
{
	EdgeIterator it{};
	it.ePtr = eList.front();
	it.gPtr = this;
	return it;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::EdgeIterator Graph<Data, Name>::eEnd()
{
	EdgeIterator it{};
	it.ePtr = eList.back();
	it.gPtr = this;
	return it;
}
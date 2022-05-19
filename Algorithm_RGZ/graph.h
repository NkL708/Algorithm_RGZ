#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

// L-граф = список рёбер
// M-граф = матрица смежности

template <typename Data, typename Name>
class Graph
{
public:
	enum class GraphOrientation
	{
		oriented,
		notOriented
	};

	enum class GraphForm
	{
		lGraph,
		mGraph
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
		int weight;
		Data data;
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
	class VertexIterator
	{
		Vertex* ptr;
	public:
		VertexIterator();
		// To do
		Data& operator*();
		void operator++(int);
	};
	VertexIterator vBegin();
	VertexIterator vEnd();

	class EdgeIterator
	{
		Edge* ptr;
	public:
		EdgeIterator();
		// To do
		Data& operator*();
		void operator++(int);
	};
	EdgeIterator eBegin();
	EdgeIterator eEnd();

	// Types of graphs
	GraphOrientation orientation = GraphOrientation::notOriented;
	GraphForm form = GraphForm::lGraph;
	// For M-graph
	std::vector<Vertex*> graphVertexes;
	std::vector<std::vector<int>> matrix;
	std::vector<Data> graphVNums;
	// For L-graph
	std::vector<Edge*> graphEdges;
	int vCount = 0;
	int eCount = 0;

public:
	// Constructors
	Graph();
	Graph(GraphForm form);
	Graph(int vertexCount, GraphOrientation orientation, GraphForm form);
	Graph(int vertexCount, int edgeCount, GraphOrientation orientation, GraphForm form);
	Graph(const Graph& obj);
	~Graph();
	
	GraphOrientation getGraphOrientation();
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
	void insertEdge(Data begin, Data end);
	void deleteEdge(Data begin, Data end);
	Edge* getEdge(Data begin, Data end);
	Vertex* getVertex(Data vertex);
	void printGraph();
	void clear();
};

template<typename Data, typename Name>
Graph<Data, Name>::Graph()
{
	form = GraphForm::lGraph;
}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(int vertexCount, GraphOrientation orientation, GraphForm form)
{
	this->orientation = orientation;
	this->form = form;
	for (int i = 0; i < vertexCount; i++)
	{
		this->insertVertex(std::vector<Data> {});
	}
}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(int vertexCount, int edgeCount, GraphOrientation orientation, GraphForm form)
{
	this->vCount = vertexCount;
	this->eCount = edgeCount;
	this->orientation = orientation;
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
inline Graph<Data, Name>::GraphOrientation Graph<Data, Name>::getGraphOrientation()
{
	return orientation;
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

}

template<typename Data, typename Name>
inline void Graph<Data, Name>::toMatrixGraph()
{

}

template<typename Data, typename Name>
inline void Graph<Data, Name>::insertVertex(std::vector<Data> vEdges)
{
	// generating unique graphVNum
	int vertexNum = 0;
	if (graphVNums.size()) 
	{
		int maxVnum = *std::max_element(graphVNums.begin(), graphVNums.end());
		for (int i = 0; i <= maxVnum + 1; i++)
		{
			if (std::find(graphVNums.begin(), graphVNums.end(), i) == graphVNums.end())
			{
				vertexNum = i;
				break;
			}
		}
	}
	Vertex* newVertex = new Vertex(std::to_string(vertexNum), vertexNum);
	graphVertexes.insert(graphVertexes.end(), newVertex);
	graphVNums.insert(graphVNums.end(), vertexNum);
	if (form == GraphForm::mGraph)
	{
		std::vector<int> newRow;
		if (vCount > 0) 
		{
			// appending to rows
			for (int i = 0; i < graphVNums.size() - 1; i++)
			{
				if (std::find(vEdges.begin(), vEdges.end(), graphVNums[i]) != vEdges.end())
					matrix[i].insert(matrix[i].end(), 1);
				else 
					matrix[i].insert(matrix[i].end(), 0);
			}
			// new row
			matrix.insert(matrix.end(), newRow);
			// last row
			int rowI = vCount;
			for (int i = 0; i < graphVNums.size(); i++)
			{
				if (std::find(vEdges.begin(), vEdges.end(), graphVNums[i]) != vEdges.end())
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

	}
	eCount += vEdges.size();
	vCount++;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::deleteVertex(Data vertex)
{
	if (form == GraphForm::mGraph)
	{
		// deleting row
		for (int i = 0; i < matrix.size(); i++)
		{
			if (graphVNums[i] == vertex) 
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
				if (graphVNums[j] == vertex)
				{
					matrix[i].erase(matrix[i].begin() + j);
					eCount--;
					break;
				}
			}
		}
	}
	else
	{

	}
	// delete vertex from graphVertexes
	for (int i = 0; i < graphVertexes.size(); i++)
	{
		if (graphVertexes[i]->getData() == vertex)
			graphVertexes.erase(graphVertexes.begin() + i);
	}
	graphVNums.erase(std::find(graphVNums.begin(), graphVNums.end(), vertex));
	vCount--;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::insertEdge(Data begin, Data end)
{
	if (form == GraphForm::mGraph)
	{
		// add edge to row and column
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if ((graphVNums[i] == begin && graphVNums[j] == end) ||
					(graphVNums[i] == end && graphVNums[j] == begin))
				{
					matrix[i][j] = 1;
				}
			}
		}
	}
	else
	{

	}
	eCount++;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::deleteEdge(Data begin, Data end)
{
	if (form == GraphForm::mGraph)
	{
		// add edge to row and column
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if ((graphVNums[i] == begin && graphVNums[j] == end) ||
					(graphVNums[i] == end && graphVNums[j] == begin))
				{
					matrix[i][j] = 0;
				}
			}
		}
	}
	else
	{

	}
	eCount--;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Edge* Graph<Data, Name>::getEdge(Data begin, Data end)
{
	// Для M графа нет реализации
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Vertex* Graph<Data, Name>::getVertex(Data vertex)
{
	Vertex* result = nullptr;
	for (int i = 0; i < graphVertexes.size(); i++)
	{
		if (graphVertexes[i]->getData() == vertex)
			result = graphVertexes[i];
	}
	return result;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::printGraph()
{
	if (form == GraphForm::mGraph)
	{
		if (!vCount) 
		{
			std::cout << "Граф пуст!\n";
			return;
		}
		std::cout << "\nТаблица графа:\n" << std::setw(5);
		// Vertexes numbers
		for (int i = 0; i < matrix[0].size(); i++)
		{
			std::cout << graphVNums[i] << " ";
		}
		std::cout << "\n" << std::setw(5);
		for (int i = 0; i < matrix[0].size(); i++)
		{
			std::cout << "--";
		}
		// matrix print
		for (int i = 0; i < matrix.size(); i++)
		{
			std::cout << "\n" << graphVNums[i] << " | ";
			for (int j = 0; j < matrix[i].size(); j++)
			{
				std::cout << matrix[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	else 
	{
		//
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
	graphVNums.clear();
	vCount = 0;
	eCount = 0;
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
inline Graph<Data, Name>::VertexIterator::VertexIterator()
{

}

template<typename Data, typename Name>
inline Data& Graph<Data, Name>::VertexIterator::operator*()
{
	return ptr->getData();
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::VertexIterator::operator++(int)
{

}

template<typename Data, typename Name>
inline Graph<Data, Name>::EdgeIterator::EdgeIterator()
{

}

template<typename Data, typename Name>
inline Data& Graph<Data, Name>::EdgeIterator::operator*()
{
	return ptr->getData();
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::EdgeIterator::operator++(int)
{

}

template<typename Data, typename Name>
inline Graph<Data, Name>::VertexIterator Graph<Data, Name>::vBegin()
{
	return VertexIterator();
}

template<typename Data, typename Name>
inline Graph<Data, Name>::VertexIterator Graph<Data, Name>::vEnd()
{
	return VertexIterator();
}

template<typename Data, typename Name>
inline Graph<Data, Name>::EdgeIterator Graph<Data, Name>::eBegin()
{
	return EdgeIterator();
}

template<typename Data, typename Name>
inline Graph<Data, Name>::EdgeIterator Graph<Data, Name>::eEnd()
{
	return EdgeIterator();
}
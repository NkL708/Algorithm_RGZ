#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

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
	size_t vCount = 0;
	size_t eCount = 0;

public:
	// Constructors
	Graph();
	Graph(GraphForm form);
	Graph(size_t vertexCount, GraphForm form);
	Graph(size_t vertexCount, int edgeCount, GraphForm form);
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
	void insertEdge(Data begin, Data end, Direction dir, int weight);
	void deleteEdge(Data begin, Data end);
	Edge* getEdge(Data begin, Data end);
	Vertex* getVertex(Data vertex);
	void printGraph();
	void clear();
	// My option task
	void findCycles(const Data vNum, Data curNum, Data pVNum, std::vector<int> result);
	void findGraphPCycles();
private:
	void findPCycles(const Data vNum, Data curNum, Data pVNum, std::vector<int> result);
	bool isPeripheral(std::vector<int> result);
};

template<typename Data, typename Name>
Graph<Data, Name>::Graph()
{
	form = GraphForm::listGraph;
}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(size_t vertexCount, GraphForm form)
{
	this->form = form;
	for (size_t i = 0; i < vertexCount; i++)
	{
		this->insertVertex(std::vector<Data> {});
	}
}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(size_t vertexCount, int edgeCount, GraphForm form)
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
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[i].size(); j++)
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
	for (size_t i = 0; i < vCount; i++)
	{
		matrix.insert(matrix.end(), std::vector<int>(vCount));
	}
	for (size_t i = 0; i < eList.size(); i++)
	{
		for (size_t j = 0; j < matrix.size(); j++)
		{
			for (size_t k = 0; k < matrix[j].size(); k++)
			{
				if (eList[i]->getBegin()->getData() == vNumList[k] && eList[i]->getEnd()->getData() == vNumList[j])
					matrix[k][j] = 1;
				if (eList[i]->getBegin()->getData() == vNumList[j] && eList[i]->getEnd()->getData() == vNumList[k])
					matrix[j][k] = 1;
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
		size_t maxVnum = *std::max_element(vNumList.begin(), vNumList.end());
		for (size_t i = 0; i <= maxVnum + 1; i++)
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
			for (size_t i = 0; i < vNumList.size() - 1; i++)
			{
				if (std::find(vEdges.begin(), vEdges.end(), vNumList[i]) != vEdges.end())
					matrix[i].insert(matrix[i].end(), 1);
				else 
					matrix[i].insert(matrix[i].end(), 0);
			}
			// new row
			matrix.insert(matrix.end(), newRow);
			int rowI = vCount;
			for (size_t i = 0; i < vNumList.size(); i++)
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
			for (size_t i = 0; i < vEdges.size(); i++)
			{
				Vertex* end = nullptr;
				for (size_t j = 0; j < vList.size(); j++)
				{
					if (vList[j]->getData() == vEdges[i])
						end = vList[j];
				}
				Edge* edge1 = new Edge(newVertex, end);
				Edge* edge2 = new Edge(end, newVertex);
				eList.insert(eList.end(), edge1);
				eList.insert(eList.end(), edge2);
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
		for (size_t i = 0; i < matrix.size(); i++)
		{
			if (vNumList[i] == vertex) 
			{
				matrix.erase(matrix.begin() + i);
				break;
			}
		}
		// deleting columns from rows
		for (size_t i = 0; i < matrix.size(); i++)
		{
			for (size_t j = 0; j < matrix[i].size(); j++)
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
		for (size_t i = 0; i < vList.size(); i++)
		{
			if (vList[i]->getData() == vertex)
				vList.erase(vList.begin() + i);
		}
	}
	else
	{
		for (size_t i = 0; i < eList.size(); i++)
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
inline void Graph<Data, Name>::insertEdge(Data begin, Data end, Direction dir, int weight)
{
	if (form == GraphForm::matrixGraph)
	{
		// add edge to row and column
		for (size_t i = 0; i < matrix.size(); i++)
		{
			for (size_t j = 0; j < matrix[i].size(); j++)
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
		for (size_t i = 0; i < vList.size(); i++)
		{
			if (vList[i]->getData() == begin)
				vBegin = vList[i];
		}
		for (size_t i = 0; i < vList.size(); i++)
		{
			if (vList[i]->getData() == end)
				vEnd = vList[i];
		}
		Edge* edge = new Edge(vBegin, vEnd, weight);
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
		for (size_t i = 0; i < matrix.size(); i++)
		{
			for (size_t j = 0; j < matrix[i].size(); j++)
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
		for (size_t i = 0; i < eList.size(); i++)
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
	for (size_t i = 0; i < eList.size(); i++)
	{
		if ((eList[i]->getBegin()->getData() == begin && eList[i]->getEnd()->getData() == end) ||
			(eList[i]->getBegin()->getData() == end && eList[i]->getEnd()->getData() == begin))
			return eList[i];
	}
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Vertex* Graph<Data, Name>::getVertex(Data vertex)
{
	for (size_t i = 0; i < vList.size(); i++)
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
			std::cout << "Matrix is empty\n";
			return;
		}
		std::cout << "\nGraph martix:\n" << std::setw(5);
		// Vertexes numbers
		for (size_t i = 0; i < vNumList.size(); i++)
		{
			std::cout << vNumList[i] << " ";
		}
		std::cout << "\n" << std::setw(5);
		for (size_t i = 0; i < matrix[0].size(); i++)
		{
			std::cout << "--";
		}
		// matrix print
		for (size_t i = 0; i < matrix.size(); i++)
		{
			std::cout << "\n" << vNumList[i] << " | ";
			for (size_t j = 0; j < matrix[i].size(); j++)
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
			std::cout << "List of edges is empty\n";
			return;
		}
		std::cout << "\nList of edges:\n";
		// Vertexes numbers
		std::cout << std::setw(10) << "begin ";
		std::cout << "end ";
		std::cout << "weight ";
		std::cout << "\n" << std::setw(5);
		for (size_t i = 0; i < eList.size(); i++)
		{
			std::cout << "--";
		}
		// matrix print
		for (size_t i = 0; i < eList.size(); i++)
		{
			std::cout << "\n" << i << " | ";
			std::cout << std::setw(3) << eList[i]->getBegin()->getData() 
				<< std::setw(5) << eList[i]->getEnd()->getData()
				<< std::setw(5) << eList[i]->getWeight();
		}
		std::cout << std::endl;
	}
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::clear()
{
	for (size_t i = 0; i < matrix.size(); i++)
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
	for (size_t i = 0; i < gPtr->vList.size() - 1; i++)
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
	for (size_t i = 0; i < gPtr->eList.size() - 1; i++)
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

template<typename Data, typename Name>
inline void Graph<Data, Name>::findCycles(const Data vNum, Data curNum, Data pVNum, std::vector<int> result) 
{
	// find index
	int vNumI = 0;
	for (size_t i = 0; i < vNumList.size(); i++)
	{
		if(vNumList[i] == curNum) 
		{
			vNumI = i;
			break;
		}
	}
	for (size_t i = 0; i < vNumList.size(); i++)
	{
		// End of Cycle
		if (matrix[vNumI][i] && curNum == vNum && curNum != pVNum)
		{
			result.insert(result.end(), curNum);
			for (size_t j = 0; j < result.size(); j++)
			{
				std::cout << result[j] << " ";
			}
			std::cout << std::endl;
			return;
		}
		if (curNum == pVNum && vNum != curNum)
			return;
		if (std::find(result.begin(), result.end(), curNum) != result.end() && curNum != vNum)
			return;
		// If "1" in a row
		if (matrix[vNumI][i] && vNumList[i] != pVNum)
		{
			// create and copy vector
			std::vector<int> newVector;
			for (size_t j = 0; j < result.size(); j++)
			{
				newVector.insert(newVector.end(), result[j]);
			}
			newVector.insert(newVector.end(), curNum);
			findCycles(vNum, vNumList[i], curNum, newVector);
		}
	}
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::findPCycles(const Data vNum, Data curNum, Data pVNum, std::vector<int> result)
{
	int eNumI = 0;
	for (size_t i = 0; i < eList.size(); i++)
	{
		if (eList[i]->getBegin()->getData() == curNum)
		{
			eNumI = i;
		}
		else
			continue;
		if (curNum == vNum && curNum != pVNum)
		{
			result.insert(result.end(), curNum);
			// Check periphery
			if (!isPeripheral(result))
				return;
			for (size_t j = 0; j < result.size(); j++)
			{
				std::cout << result[j] << " ";
			}
			std::cout << std::endl;
			return;
		}
		if (curNum == pVNum && vNum != curNum)
			return;
		if (std::find(result.begin(), result.end(), curNum) != result.end() && curNum != vNum)
			return;
		int nextNum = eList[eNumI]->getEnd()->getData();
		if (nextNum != pVNum)
		{
			// create and copy vector
			std::vector<int> newVector;
			for (size_t j = 0; j < result.size(); j++)
			{
				newVector.insert(newVector.end(), result[j]);
			}
			newVector.insert(newVector.end(), curNum);
			findPCycles(vNum, nextNum, curNum, newVector);
		}
	}
}

template<typename Data, typename Name>
inline bool Graph<Data, Name>::isPeripheral(std::vector<int> result)
{
	// Collect all edges that not peripheral
	std::vector<Edge*> edges(eList);
	for (std::vector<int>::iterator it = result.begin(); it < result.end() - 1; it++)
	{
		int begin = *it;
		int end = *(it + 1);
		for (size_t j = 0; j < edges.size(); j++)
		{
			// Remove or if don't match
			if (edges[j]->getBegin()->getData() == begin && edges[j]->getEnd()->getData() == end ||
				edges[j]->getBegin()->getData() == end && edges[j]->getEnd()->getData() == begin)
			{
				edges.erase(edges.begin() + j);
				j--;
			}
		}
	}
	// Check each edge on connection with others
	int pECount = 0;
	for (size_t i = 0; i < edges.size(); i++)
	{
		for (size_t j = 0; j < edges.size(); j++)
		{
			if (i == j)
				continue;
			// If edges have common vertex but edges not from the same vertexes
			if ((edges[i]->getBegin()->getData() == edges[j]->getBegin()->getData() ||
				edges[i]->getEnd()->getData() == edges[j]->getEnd()->getData() ||
				edges[i]->getBegin()->getData() == edges[j]->getEnd()->getData() ||
				edges[i]->getEnd()->getData() == edges[j]->getBegin()->getData()) &&
				!(edges[i]->getEnd()->getData() == edges[j]->getBegin()->getData() &&
					edges[i]->getBegin()->getData() == edges[j]->getEnd()->getData()))
			{
				pECount++;
				break;
			}
		}
	}
	if (pECount < edges.size())
		return false;
	else
		return true;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::findGraphPCycles()
{
	for (size_t i = 0; i < vNumList.size(); i++)
	{
		std::vector<int> vector;
		findPCycles(vNumList[i], vNumList[i], vNumList[i], vector);
		std::cout << std::endl;
	}
}
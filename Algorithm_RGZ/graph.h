#pragma once
#include <string>

// L-граф = список рёбер
// M-граф = матрица смежности
template <typename Data, typename Name>
class Graph
{
	enum GraphOrientation
	{
		oriented,
		notOriented
	};

	enum PresentationForm
	{
		lGraph,
		mGraph
	};
	
	class Vertex
	{
		Name name;
		Data data;
		int index;
	public:
		Vertex();
		Vertex(std::string name, Data data);
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
	public:
		VertexIterator();
		// To do
		void operator++(int);
		void operator--(int);
		bool operator==(const VertexIterator& it);
		bool operator!=(const VertexIterator& it);
	};
	// To do
	VertexIterator vBegin();
	VertexIterator vEnd();
	class EdgeIterator
	{

	public:
		EdgeIterator();
		// To do
		void operator++(int);
		void operator--(int);
		bool operator==(const EdgeIterator& it);
		bool operator!=(const EdgeIterator& it);
	};
	GraphOrientation orientation;
	PresentationForm form;

public:
	// To do
	EdgeIterator eBegin();
	EdgeIterator eEnd();
	// Graph methods
	Graph();
	Graph(int vertexCount, GraphOrientation orientation, PresentationForm form);
	Graph(int vertexCount, int edgeCount, GraphOrientation orientation, PresentationForm form);
	Graph(const Graph& obj);
	~Graph();
	// To do
	int getGraphVCount();
	int getGraphECount();
	// Done
	GraphOrientation getGraphOrientation();
	PresentationForm getGraphForm();
	// To do
	int K();
	void toListGraph();
	void toMatrixGraph();
	void insertVertex();
	void deleteVertex(/* v? */);
	void insertEdge(Vertex* begin, Vertex* end);
	void deleteEdge(Vertex* begin, Vertex* end);
	Edge getEdge(Vertex* begin, Vertex* end);
};

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

template<typename Data, typename Name>
Graph<Data, Name>::Graph()
{

}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(int vertexCount, GraphOrientation orientation, PresentationForm form)
{

}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(int vertexCount, int edgeCount, GraphOrientation orientation, PresentationForm form)
{

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
	return 0;
}

template<typename Data, typename Name>
inline int Graph<Data, Name>::getGraphECount()
{
	return 0;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::GraphOrientation Graph<Data, Name>::getGraphOrientation()
{
	return orientation;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::PresentationForm Graph<Data, Name>::getGraphForm()
{
	return form;
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
inline void Graph<Data, Name>::insertVertex()
{

}

template<typename Data, typename Name>
inline void Graph<Data, Name>::deleteVertex()
{

}

template<typename Data, typename Name>
inline void Graph<Data, Name>::insertEdge(Vertex* begin, Vertex* end)
{

}

template<typename Data, typename Name>
inline void Graph<Data, Name>::deleteEdge(Vertex* begin, Vertex* end)
{

}

template<typename Data, typename Name>
inline Graph<Data, Name>::Edge Graph<Data, Name>::getEdge(Vertex* begin, Vertex* end)
{
	return Edge();
}

template<typename Data, typename Name>
inline Graph<Data, Name>::Vertex::Vertex()
{

}

template<typename Data, typename Name>
inline Graph<Data, Name>::Vertex::Vertex(std::string name, Data data)
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
inline void Graph<Data, Name>::VertexIterator::operator++(int)
{

}

template<typename Data, typename Name>
inline void Graph<Data, Name>::VertexIterator::operator--(int)
{

}

template<typename Data, typename Name>
inline bool Graph<Data, Name>::VertexIterator::operator==(const VertexIterator& it)
{
	return false;
}

template<typename Data, typename Name>
inline bool Graph<Data, Name>::VertexIterator::operator!=(const VertexIterator& it)
{
	return false;
}

template<typename Data, typename Name>
inline Graph<Data, Name>::EdgeIterator::EdgeIterator()
{

}

template<typename Data, typename Name>
inline void Graph<Data, Name>::EdgeIterator::operator++(int)
{

}

template<typename Data, typename Name>
inline void Graph<Data, Name>::EdgeIterator::operator--(int)
{

}

template<typename Data, typename Name>
inline bool Graph<Data, Name>::EdgeIterator::operator==(const EdgeIterator& it)
{
	return false;
}

template<typename Data, typename Name>
inline bool Graph<Data, Name>::EdgeIterator::operator!=(const EdgeIterator& it)
{
	return false;
}
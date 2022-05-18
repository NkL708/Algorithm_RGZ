#pragma once
#include <string>
#include <vector>

// L-граф = список рёбер
// M-граф = матрица смежности
template <typename Data, typename Name>
class Graph
{
public:
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
	std::vector<std::vector<Vertex*>> matrix;
	int vCount = 0;
	int eCount = 0;

public:
	// To do
	EdgeIterator eBegin();
	EdgeIterator eEnd();
	// Graph methods
	Graph();
	Graph(PresentationForm form);
	// ?
	Graph(int vertexCount, GraphOrientation orientation, PresentationForm form);
	Graph(int vertexCount, int edgeCount, GraphOrientation orientation, PresentationForm form);
	// ?
	// to do
	Graph(const Graph& obj);
	// done
	~Graph();
	int getGraphVCount();
	int getGraphECount();
	GraphOrientation getGraphOrientation();
	PresentationForm getGraphForm();
	// To do
	int K();
	void toListGraph();
	void toMatrixGraph();
	void insertVertex(std::vector<Data> vertexes);
	void deleteVertex(Vertex* vertex);
	void insertEdge(Vertex* begin, Vertex* end);
	void deleteEdge(Vertex* begin, Vertex* end);
	Edge getEdge(Vertex* begin, Vertex* end);
	void printGraph();
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
	this->vCount = vertexCount;
	this->orientation = orientation;
	this->form = form;
}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(int vertexCount, int edgeCount, GraphOrientation orientation, PresentationForm form)
{
	this->vCount = vertexCount;
	this->eCount = edgeCount;
	this->orientation = orientation;
	this->form = form;
}

template<typename Data, typename Name>
Graph<Data, Name>::Graph(PresentationForm form)
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
inline void Graph<Data, Name>::insertVertex(std::vector<Data> vertexes)
{
	if (form == mGraph)
	{
		if (vCount) 
		{
			Vertex* newVertex = new Vertex(std::to_string(vCount + 1), vCount + 1);
			for (int i = 0; i < vCount; i++)
			{
				for (int j = 0; j < matrix.size(); j++)
				{
					if (matrix[j].at(0)->getData())
					{

					}
				}
			}
		}
		else
		{
			Vertex* vertex = new Vertex("0", 0);
			// new row
			std::vector<Vertex*> temp;
			temp.insert(temp.begin(), vertex);
			matrix.insert(matrix.begin(), temp);
		}
	}
	//else 
	//{
	//
	//}
	vCount++;
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::deleteVertex(Vertex* vertex)
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
	//return Edge();
}

template<typename Data, typename Name>
inline void Graph<Data, Name>::printGraph()
{
	if (form = mGraph) 
	{

	}
	else 
	{

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
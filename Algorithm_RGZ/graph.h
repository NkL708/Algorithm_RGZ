#pragma once
#include <string>

template <typename T>
class Graph
{
public:
	Graph();
	~Graph();

private:
	class Vertex
	{
		std::string name;
		T data;
		int index;
	public:
		Vertex();
		Vertex(std::string name, T data);
		std::string getName();
		void setName(std::string name);
		T getData();
		void setData(T data);
	};
	class Edge
	{
		Vertex* begin;
		Vertex* end;
		int weight;
		T data;
	public:
		Edge(Vertex* begin, Vertex* end);
		Edge(Vertex* begin, Vertex* end, int weight);
		Edge(Vertex* begin, Vertex* end, int weight, T data);
		Vertex* getBegin();
		Vertex* getEnd();
		int getWeight();
		void setWeight(int weight);
		T getData();
		void setData(T data);
	};
	class VertexIterator
	{
	public:

	private:

	};
	class EdgeIterator
	{
	public:

	private:

	};
};

template<typename T>
Graph<T>::Graph()
{

}

template<typename T>
Graph<T>::~Graph()
{

}

template<typename T>
inline std::string Graph<T>::Vertex::getName()
{
	return name;
}

template<typename T>
inline void Graph<T>::Vertex::setName(std::string name)
{
	this->name = name;
}

template<typename T>
inline T Graph<T>::Vertex::getData()
{
	return data;
}

template<typename T>
inline void Graph<T>::Vertex::setData(T data)
{
	this->data = data;
}

template<typename T>
inline Graph<T>::Vertex* Graph<T>::Edge::getBegin()
{
	return begin;
}

template<typename T>
inline Graph<T>::Vertex* Graph<T>::Edge::getEnd()
{
	return nullptr;
}

template<typename T>
inline int Graph<T>::Edge::getWeight()
{
	return weight;
}

template<typename T>
inline void Graph<T>::Edge::setWeight(int weight)
{
	this->weight = weight;
}

template<typename T>
inline T Graph<T>::Edge::getData()
{
	return data;
}

template<typename T>
inline void Graph<T>::Edge::setData(T data)
{
	this->data = data;
}

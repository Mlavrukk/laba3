#include <iostream>
#include <unordered_set>
#include <vector>

template<typename Vertex_type, typename Distance = double>
struct Edge //ребро графа
{
	Distance dist;
	Vertex_type from;
	Vertex_type to;
	Edge(const Vertex_type& from, const Vertex_type& to, const Distance& d) : from(from), to(to), dist(d) {}
};

template<typename Vertex_type, typename Distance = double>
class Top
{
private:
	Vertex_type name;
	mutable std::vector<Edge<Vertex_type, Distance>> edges;
public: 
	Vertex_type get_name() const { return name; }

	Top(const Vertex_type& name) : name(name) {} 

	using Iterator = typename std::vector<Edge<Vertex_type, Distance>>::iterator;

	Iterator begin_edge() const 
	{
		return edges.begin();
	}

	Iterator end_edge() const {
		return edges.end();
	}

	void add_edge_top(const Vertex_type& to,const Distance& dist)const { 
		edges.push_back(Edge<Vertex_type, Distance>(name, to, dist));
	}



};

template<typename Vertex_type, typename Distance>
struct TopHasher
{
	size_t operator()(const Top<Vertex_type, Distance>& obj) const
	{
		return std::hash<Vertex_type>()(obj.get_name());
	}
};

template<typename Vertex_type, typename Distance>
struct TopComparator
{
	bool operator()(const Top<Vertex_type, Distance>& obj1, const Top<Vertex_type, Distance>& obj2) const
	{
		if (obj1.get_name() == obj2.get_name())
			return true;
		return false;
	}
};



template<typename Vertex_type, typename Distance = double>
class Graph 
{
private:
	std::unordered_set<Top<Vertex_type, Distance>, TopHasher<Vertex_type, Distance>, TopComparator<Vertex_type, Distance>> graph;

public:
	bool has_vertex(const Vertex_type& v) const{
		if (graph.find({ v }) != graph.end())
			return true;
		return false;
	}

	void add_vertex(const Vertex_type& v) { graph.insert(Top<Vertex_type, Distance>(v)); }

	bool remove_vertex(const Vertex_type& v){
		auto iter = graph.find({ v });
		if (iter != graph.end()) {
			graph.erase(iter);
			return true;
		}
		return false;
	}

	bool has_edge(const Vertex_type& from, const Vertex_type& to) const {
		auto iter = graph.find({ from });
		if (iter != graph.end()) {
			for (auto begin_edge = iter->begin_edge(); begin_edge != iter->end_edge(); begin_edge++)
			{
				if (begin_edge->to == to)
					return true;
			}
		}
		return false;

	}
	bool has_edge(const Edge<Vertex_type, Distance>& edge) const {
		auto iter = graph.find({ edge.from });
		if (iter != graph.end()) {
			for(auto begin_edge = iter->begin_edge(); begin_edge != iter->end_edge(); begin_edge++)
			{
				if (begin_edge->to == edge.to && begin_edge->dist == edge.dist)
					return true;
			}
		}
		return false;


	}

	void add_edge(const Vertex_type& from, const Vertex_type& to, const Distance& d){
		auto iter = graph.find({ from });
		if (iter != graph.end()) {
			iter->add_edge_top(to, d);
		}
	
		//add_edge_top

	}
	//std::vector<Vertex> vertices() const;


	//проверка-добавление-удаление ребер
	//не работает это
	
	bool remove_edge(const Vertex_type& from, const Vertex_type& to) const {
		auto iter = graph.find({ from });
		if (iter != graph.end()) {
			auto& edges = iter->second;
			auto edge_it = std::find(edges.begin(), edges.end(), to);
			if (edge_it != edges.end()) {
				edges.erase(edge_it);
			}
			return true;
		}
		return false;

	}
	bool remove_edge(const Edge<Vertex_type, Distance>& e) const//c учетом расстояния 
	{
		auto iter = graph.find({ from });
		if (iter != graph.end()) {
			auto& edges = iter->second;
			auto edge_it = std::find(edges.begin(), edges.end(), to);
			if (edge_it != edges.end()) {
				edges.erase(edge_it);
			}
			return true;
		}
		return false;
		auto& iter = graph.find(e.from)->second;
		auto it = iter.begin();
		bool is_any_erases = false;

		while (it != iter.end()) {
			if (it->from == e.from and it->to == e.to and it->dist == e.dist) {
				it = iter.erase(it);
				is_any_erases = true;
			}
			else { ++it; }
		}
		return is_any_erases;
	}

	/*std::vector<Edge<Vertex_type, Distance>> edges(const Vertex& from) {
		if (!has_vertex(from))
			throw std::invalid_argument("Has not vertex");
		return get_vertex(from)->get_edges();
	}*/


	//получение всех ребер, выходящих из вершины
	//std::vector<Edge> edges(const Vertex_type& vertex);
	size_t order() const {//порядок
		return graph.size();
	}

	size_t degree(const Vertex_type& v) const {//степень
		if (!has_vertex(v)) { throw std::invalid_argument("The graph has no given vertex!"); }
		return graph.find(v)->second.size();
	}


	//поиск кратчайшего пути
	//std::vector<Edge> shortest_path(const Vertex_type& from,
		//const Vertex_type& to) const;
	//обход
	//std::vector<Vertex_type>  walk(const Vertex_type& start_vertex)const;

};




int main() {
	Graph<std::string, double> graph;
	graph.add_vertex("Пирогово");
    graph.add_vertex("13123");
    graph.add_vertex("hhh");


	graph.add_edge("13123", "hhh", 17.5);
	graph.add_edge("Пирогово", "hhh", 12.435);
	graph.add_edge("Пирогово", "hhh", 1567.435);
	graph.add_edge("Пирогово", "hhh", 12131.435);
	graph.add_edge("Пирогово", "13123", 23);
	graph.add_edge("13123", "Пирогово", 10);

	std::cout << graph.has_edge(Edge<std::string, double>("Пирогово", "hhh", 15665577.435));
	//std::cout << graph.has_edge(Vertex_type<std::string, double>("Пирогово", "hhh"));
	std::cout << graph.remove_edge(Edge<std::string, double>("Пирогово", "hhh", 15665577.435));
	int aboba = 0;

}


#include <boost/program_options.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

#include <iostream>
#include <fstream>
#include <iosfwd>

//struct VertexProperties {
//	static const std::string RED;
//	static const std::string BLUE;
//	static const std::string BLACK;
//
//	int index = 0;
//	std::string color = VertexProperties::BLACK;
//
//	VertexProperties(int index, std::string color) : index(index), color(color) {}
//	VertexProperties() {}
//};

//const std::string VertexProperties::RED = "red";
//const std::string VertexProperties::BLUE = "blue";
//const std::string VertexProperties::BLACK = "black";

namespace detail {
	template <class GraphT>
	class vertex_writer {
		const GraphT& g_;

	public:
		explicit vertex_writer(const GraphT& g) : g_(g) {}

		template <class VertexDescriptorT>
		void operator ()(std::ostream& out, const VertexDescriptorT& d) const {
			out << "[label = " << boost::get(boost::vertex_index, g_)[d] << "]";
		}
	};

	template <class GraphT>
	class edge_writer {
		const GraphT& g_;

	public:
		explicit edge_writer(const GraphT& g) : g_(g) {}

		template <class EdgeDescriptorT>
		void operator ()(std::ostream& out, const EdgeDescriptorT& d) const {
			out << "[weight = " << boost::get(boost::edge_weight, g_)[d] << "]";
		}
	};
}

namespace opt = boost::program_options;

typedef boost::adjacency_list<
	boost::vecS
	, boost::vecS
	, boost::bidirectionalS
	, boost::property<boost::vertex_index_t, int>
	, boost::property<boost::edge_weight_t, int>
> graph_type;

typedef
boost::graph_traits <
	graph_type
>::vertex_descriptor descriptor_t;

opt::variables_map read_cmd_parameters(int argc, char* argv[]) {
	opt::options_description desc("All options");

	desc.add_options()
		("inputGraph", opt::value<std::string>()->default_value("input.txt"), "Name of the input file")
		("outputGraph.dot", opt::value<std::string>()->default_value("output.dot"), "Name of the output file for graph")
		("outputMST.dot", opt::value<std::string>()->default_value("output_mst.dot"), "Name of the output file for MST")
		("outputCriticalAndPseudocriticalEdges.dot", opt::value<std::string>()->default_value("output_critical.dot"),
			"Name of the output file for critical and pseudo-critical nodes")
		("help", "Help for parameters")
	;

	opt::variables_map vm;

	opt::store(opt::parse_command_line(argc, argv, desc), vm);
	opt::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << std::endl;
	}

	return vm;
}

std::ostream& operator <<(std::ostream& out, const graph_type& g) {
	detail::vertex_writer <graph_type> vw(g);
	detail::edge_writer <graph_type> ew(g);
	boost::write_graphviz(out, g, vw, ew);
	return out;
}

graph_type get_graph(const std::string& file_name) {
	std::ifstream input_file(file_name);
	graph_type graph;

	int num_vertices = 0;
	input_file >> num_vertices;

	graph.m_vertices.reserve(num_vertices);

	std::vector<descriptor_t> descriptors(num_vertices);
	for (int i = 0; i < num_vertices; ++i) {
		descriptors[i] = boost::add_vertex(i, graph);
	}

	int from = 0;
	int to = 0;
	int weight = 0;

	while (input_file >> from >> to >> weight) {
		boost::add_edge(descriptors[from], descriptors[to], weight, graph);
	}

	return graph;
}

void output_graph(graph_type& graph, const std::string& file_name) {
	std::ofstream output_file(file_name);

	output_file << graph;
}

typedef typename boost::graph_traits<graph_type>::vertex_descriptor Vertex;
typedef typename boost::graph_traits<graph_type>::edge_descriptor Edge;

int main(int argc, char* argv[]) {
	opt::variables_map vm = read_cmd_parameters(argc, argv);

	if (vm.count("help")) {
		return 1;
	}

	graph_type graph = get_graph(vm["inputGraph"].as<std::string>());
	output_graph(graph, vm["outputGraph.dot"].as<std::string>());

	boost::property_map<graph_type, boost::vertex_index_t>::type indexmap = boost::get(boost::vertex_index, graph);
	boost::property_map<graph_type, boost::edge_weight_t>::type weightmap = boost::get(boost::edge_weight, graph);
	std::vector<int> p(graph.m_vertices.size());
	
	std::vector <Edge> spanning_tree;
	boost::kruskal_minimum_spanning_tree(graph, std::back_inserter(spanning_tree));
	
	graph_type mst;
	boost::graph_traits<graph_type>::vertex_iterator it, end;
	boost::tie(it, end) = boost::vertices(graph);

	for (; it != end; ++it) {
		Vertex vertex = *it;
		boost::add_vertex(vertex, mst);
	}

	boost::get(boost::vertex_index, graph);
	for (std::vector < Edge >::iterator ei = spanning_tree.begin();
		ei != spanning_tree.end(); ++ei) {
		boost::add_edge(boost::source(*ei, graph), boost::target(*ei, graph), boost::get(boost::edge_weight, graph)[*ei], mst);
	}
	output_graph(mst, vm["outputMST.dot"].as<std::string>());
}
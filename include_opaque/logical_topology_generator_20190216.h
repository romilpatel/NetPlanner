# ifndef LOGICAL_TOPOLOGY_GENERATOR_H_
# define LOGICAL_TOPOLOGY_GENERATOR_H_


# include "netxpto_20190130.h"


class LogicalTopologyGenerator : public Block {

	// Input Parameters
	transport_mode transportMode;
	t_matrix adjacencyMatrix;
	
	// State variables
	bool generate{ true };
	

public:

	// Methods (Constructors)
	LogicalTopologyGenerator() {};
	LogicalTopologyGenerator(initializer_list<Signal *> inputSig, initializer_list<Signal *> outputSig) :Block(inputSig, outputSig) {};

	void initialize(void);
	bool runBlock(void);

	void setTransportMode(transport_mode tMode) { transportMode = tMode; }
	transport_mode getTransportMode(void) { return transportMode; };

	void setAdjacencyMatrix(t_matrix aMatrix) { adjacencyMatrix = aMatrix; }
	t_matrix getAdjacencyMatrix(void) { return adjacencyMatrix; };

};

# endif
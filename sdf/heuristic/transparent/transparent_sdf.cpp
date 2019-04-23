# include "..\..\..\include\netxpto_20190130.h"
# include "..\..\..\include\scheduler_20190122.h"
# include "..\..\..\include\logical_topology_generator_20190216.h"
# include "..\..\..\include\physical_topology_generator_20190227.h"
# include "..\..\..\include\sink_20180815.h"
# include "..\..\..\include\logical_topology_manager_20190420.h"
# include "..\..\..\include\physical_topology_manager_20190421.h"


//##########################################################################################
//######################## Simulation Input Parameters #####################################
//##########################################################################################

// devera ser feito de acordo com IPS do netxpto

class NetworkSimulatorInputParameters : public SystemInputParameters {
public:

	// INPUT PARAMETERS (with default values)
	int numberOfNodes{ 0 }; // Number of nodes existent in the network
	t_matrix odu0{ 0 };
	t_matrix odu1{ 0 };
	t_matrix odu2{ 0 };
	t_matrix odu3{ 0 };
	t_matrix odu4{ 0 };
	ordering_rule orderingRule{ ordering_rule::descendingOrder };
	t_matrix physicalTopologyAdjacencyMatrix{ 0 };
	transport_mode transportMode{transport_mode::transparent};
	int numberOfOMSPerLink{ 0 };
	int numberOfOpticalChannelsPerOMS{ 0 };
	double initialWavelenght{ 1550 };
	double wavelenghtSpacing{ 0.8 };
	int opticalChannelCapacity{ 0 };
	routing_criterion_logical_topology routingCriterionLogicalTopology{ routing_criterion_logical_topology::hops };
	int blockingCriterionLogicalTopology{ 1 };
	routing_criterion_physical_topology routingCriterionPhysicalTopology{ routing_criterion_physical_topology::hops };
	int blockingCriterionPhysicalTopology{ 3 };

	/* Initializes default input parameters*/
	NetworkSimulatorInputParameters() : SystemInputParameters() {
		initializeInputParameterMap();
	}

	/* Initializes input parameters according to the program arguments */
	/* Usage: .\network_simulator.exe <InpuParameters.txt> <output_directory>*/
	NetworkSimulatorInputParameters(int argc, char *argv[]) : SystemInputParameters(argc, argv) {
		initializeInputParameterMap();
		readSystemInputParameters();
	}

	NetworkSimulatorInputParameters(string fName) : SystemInputParameters(fName) {
		initializeInputParameterMap();
		readSystemInputParameters();
	}

	// Each parameter must be added to the parameter map by calling this function
	void initializeInputParameterMap() {
		addInputParameter("numberOfNodes", &numberOfNodes);
		addInputParameter("odu0", &odu0);
		addInputParameter("odu1", &odu1);
		addInputParameter("odu2", &odu2);
		addInputParameter("odu3", &odu3);
		addInputParameter("odu4", &odu4);
		addInputParameter("orderingRule", &orderingRule);
		addInputParameter("physicalTopologyAdjacencyMatrix", &physicalTopologyAdjacencyMatrix);
		addInputParameter("transportMode", &transportMode);
		addInputParameter("numberOfOMSPerLink", &numberOfOMSPerLink);
		addInputParameter("numberOfOpticalChannelsPerOMS", &numberOfOpticalChannelsPerOMS);
		addInputParameter("initialWavelenght", &initialWavelenght);
		addInputParameter("wavelenghtSpacing", &wavelenghtSpacing);
		addInputParameter("opticalChannelCapacity", &opticalChannelCapacity);
		addInputParameter("routingCriterionLogicalTopology", &routingCriterionLogicalTopology);
		addInputParameter("blockingCriterionLogicalTopology", &blockingCriterionLogicalTopology);
		addInputParameter("routingCriterionPhysicalTopology", &routingCriterionPhysicalTopology);
		addInputParameter("blockingCriterionPhysicalTopology", &blockingCriterionPhysicalTopology);
	}
};


//##########################################################################################
//##########################################################################################
//##########################################################################################


//int main(int argc, char *argv[])
int main()
{

	NetworkSimulatorInputParameters param("input_parameters_values.txt");


	/* Signals Declaration */
	DemandRequest Scheduler_Out{"Scheduler_Out.sgn"};
	Scheduler_Out.setSaveInAscii(true);

	LogicalTopology LogicalTopologyGenerator_Out{ "LogicalTopologyGenerator_Out.sgn"};
	LogicalTopologyGenerator_Out.setSaveInAscii(true);

	PhysicalTopology PhysicalTopologyGenerator_Out{ "PhysicalTopologyGenerator_Out.sgn"};
	PhysicalTopologyGenerator_Out.setSaveInAscii(true);

	LogicalTopology FinalLogicalTopology{ "FinalLogicalTopology.sgn"};
	FinalLogicalTopology.setSaveInAscii(true);

	PhysicalTopology FinalPhysicalTopology{ "FinalPhysicalTopology.sgn" };
	FinalPhysicalTopology.setSaveInAscii(true);

	DemandRequest ProcessedDemand{ "ProcessedDemand.sgn", 5};
	ProcessedDemand.setSaveInAscii(true);

	/* Blocks Decalration */
	Scheduler Scheduler_{ {},{ &Scheduler_Out} };
	Scheduler_.setNumberOfNodes(param.numberOfNodes);
	Scheduler_.setODU0(param.odu0);
	Scheduler_.setODU1(param.odu1);
	Scheduler_.setODU2(param.odu2);
	Scheduler_.setODU3(param.odu3);
	Scheduler_.setODU4(param.odu4);
	Scheduler_.setOrderingRule(param.orderingRule);

	Sink SinkScheduler_{ { &Scheduler_Out },{} };
	SinkScheduler_.setDisplayNumberOfSamples(true);


	LogicalTopologyGenerator LogicalTopologyGenerator_{ {},{&LogicalTopologyGenerator_Out} };
	LogicalTopologyGenerator_.setTransportMode(param.transportMode);
	LogicalTopologyGenerator_.setPhysicalTopologyAjacencyMatrix(param.physicalTopologyAdjacencyMatrix);

	Sink SinkLogicalTopologyGenerator_{ { &LogicalTopologyGenerator_Out },{} };
	SinkLogicalTopologyGenerator_.setDisplayNumberOfSamples(true);

	PhysicalTopologyGenerator PhysicalTopologyGenerator_{ {},{&PhysicalTopologyGenerator_Out} };
	PhysicalTopologyGenerator_.setNumberOfOpticalChannelsPerOMS(param.numberOfOpticalChannelsPerOMS);
	PhysicalTopologyGenerator_.setInitialWavelenght(param.initialWavelenght);
	PhysicalTopologyGenerator_.setWavelenghtSpacing(param.wavelenghtSpacing);
	PhysicalTopologyGenerator_.setPhysicalTopologyAdjacencyMatrix(param.physicalTopologyAdjacencyMatrix);
	PhysicalTopologyGenerator_.setNumberOfOMSPerLink(param.numberOfOMSPerLink);
	PhysicalTopologyGenerator_.setOpticalChannelCapacity(param.opticalChannelCapacity);

	Sink SinkPhysicalTopologyGenerator_{ { &PhysicalTopologyGenerator_Out },{} };
	SinkPhysicalTopologyGenerator_.setDisplayNumberOfSamples(true);


	LogicalTopologyManager LogicalTopologyManager_{ {&LogicalTopologyGenerator_Out, &Scheduler_Out},{&FinalLogicalTopology, &ProcessedDemand} };
	LogicalTopologyManager_.setRoutingCriterionLogicalTopology(param.routingCriterionLogicalTopology);
	LogicalTopologyManager_.setBlockingCriterionLogicalTopology(param.blockingCriterionLogicalTopology);

	Sink SinkLogicalTopology_{ {&FinalLogicalTopology},{} };
	SinkLogicalTopology_.setDisplayNumberOfSamples(true);

	Sink SinkRoutedOrBlocked_{ {&ProcessedDemand},{} };
	SinkRoutedOrBlocked_.setDisplayNumberOfSamples(true);

	PhysicalTopologyManager PhysicalTopologyManager_{ {&PhysicalTopologyGenerator_Out},{&FinalPhysicalTopology} };
	PhysicalTopologyManager_.setRoutingCriterionPhysicalTopology(param.routingCriterionPhysicalTopology);
	PhysicalTopologyManager_.setBlockingCriterionPhysicalTopology(param.blockingCriterionPhysicalTopology);

	Sink SinkPhysicalTopology_{ {&FinalPhysicalTopology},{} };
	SinkPhysicalTopology_.setDisplayNumberOfSamples(true);


	System MainSystem{
		// BLOCKS
		&Scheduler_,
		//&SinkScheduler_,
		&LogicalTopologyGenerator_,
		//&SinkLogicalTopologyGenerator_,
		&PhysicalTopologyGenerator_,
		//&SinkPhysicalTopologyGenerator_,
		&LogicalTopologyManager_,
		&SinkLogicalTopology_,
		&SinkRoutedOrBlocked_,
		&PhysicalTopologyManager_,
		&SinkPhysicalTopology_
};
	
	MainSystem.run();
	MainSystem.terminate();

	system("pause");

	return 0;
}

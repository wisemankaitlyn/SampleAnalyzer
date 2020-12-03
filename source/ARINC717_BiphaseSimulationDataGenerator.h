#ifndef ARINC717_BIPHASE_SIMULATION_DATA_GENERATOR
#define ARINC717_BIPHASE_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class ARINC717_BiphaseAnalyzerSettings;

class ARINC717_BiphaseSimulationDataGenerator
{
public:
	ARINC717_BiphaseSimulationDataGenerator();
	~ARINC717_BiphaseSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, ARINC717_BiphaseAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	ARINC717_BiphaseAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //ARINC717_BIPHASE_SIMULATION_DATA_GENERATOR
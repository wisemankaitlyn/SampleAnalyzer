#ifndef ARINC717_BIPHASE_ANALYZER_H
#define ARINC717_BIPHASE_ANALYZER_H

#include <Analyzer.h>
#include "ARINC717_BiphaseAnalyzerResults.h"
#include "ARINC717_BiphaseSimulationDataGenerator.h"

class ARINC717_BiphaseAnalyzerSettings;
class ANALYZER_EXPORT ARINC717_BiphaseAnalyzer : public Analyzer2
{
public:
	ARINC717_BiphaseAnalyzer();
	virtual ~ARINC717_BiphaseAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< ARINC717_BiphaseAnalyzerSettings > mSettings;
	std::auto_ptr< ARINC717_BiphaseAnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	ARINC717_BiphaseSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //ARINC717_BIPHASE_ANALYZER_H

#ifndef ARINC717_BIPHASE_ANALYZER_RESULTS
#define ARINC717_BIPHASE_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class ARINC717_BiphaseAnalyzer;
class ARINC717_BiphaseAnalyzerSettings;

class ARINC717_BiphaseAnalyzerResults : public AnalyzerResults
{
public:
	ARINC717_BiphaseAnalyzerResults( ARINC717_BiphaseAnalyzer* analyzer, ARINC717_BiphaseAnalyzerSettings* settings );
	virtual ~ARINC717_BiphaseAnalyzerResults();

	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );

protected: //functions

protected:  //vars
	ARINC717_BiphaseAnalyzerSettings* mSettings;
	ARINC717_BiphaseAnalyzer* mAnalyzer;
};

#endif //ARINC717_BIPHASE_ANALYZER_RESULTS

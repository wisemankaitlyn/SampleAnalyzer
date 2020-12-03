#ifndef ARINC717_BIPHASE_ANALYZER_SETTINGS
#define ARINC717_BIPHASE_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class ARINC717_BiphaseAnalyzerSettings : public AnalyzerSettings
{
public:
	ARINC717_BiphaseAnalyzerSettings();
	virtual ~ARINC717_BiphaseAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
	U32 mBitRate;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mBitRateInterface;
};

#endif //ARINC717_BIPHASE_ANALYZER_SETTINGS

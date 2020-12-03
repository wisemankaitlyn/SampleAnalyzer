#include "ARINC717_BiphaseAnalyzer.h"
#include "ARINC717_BiphaseAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

ARINC717_BiphaseAnalyzer::ARINC717_BiphaseAnalyzer()
:	Analyzer2(),  
	mSettings( new ARINC717_BiphaseAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

ARINC717_BiphaseAnalyzer::~ARINC717_BiphaseAnalyzer()
{
	KillThread();
}

void ARINC717_BiphaseAnalyzer::SetupResults()
{
	mResults.reset( new ARINC717_BiphaseAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );
}

void ARINC717_BiphaseAnalyzer::WorkerThread()
{
	mSampleRateHz = GetSampleRate();

	mSerial = GetAnalyzerChannelData( mSettings->mInputChannel );

	if( mSerial->GetBitState() == BIT_LOW )
		mSerial->AdvanceToNextEdge();

	U32 samples_per_bit = mSampleRateHz / mSettings->mBitRate;
	U32 samples_to_first_center_of_first_data_bit = U32( 0.25 * double( mSampleRateHz ) / double( mSettings->mBitRate ) );
	U32 samples_to_second_center_of_first_data_bit = U32(0.75 * double(mSampleRateHz) / double(mSettings->mBitRate));

	for( ; ; )
	{
		U8 data = 0;
		U8 mask = 1 << 7;
		
		//mSerial->AdvanceToNextEdge(); //falling edge -- beginning of the start bit

		U64 starting_sample = mSerial->GetSampleNumber();

		mSerial->Advance( samples_to_first_center_of_first_data_bit );

		for( U32 i=0; i<8; i++ )
		{
			bool firstHalf = false;
			bool secondHalf = false;
			//let's put a dot exactly where we sample this bit:
			mResults->AddMarker( mSerial->GetSampleNumber(), AnalyzerResults::Dot, mSettings->mInputChannel );

			//if( mSerial->GetBitState() == BIT_HIGH )
			//	data |= mask;

			if (mSerial->GetBitState() == BIT_HIGH)
			{
				firstHalf = true;
			}


			mSerial->Advance( samples_per_bit/2.0 );

			mResults->AddMarker(mSerial->GetSampleNumber(), AnalyzerResults::Dot, mSettings->mInputChannel);

			if (mSerial->GetBitState() == BIT_HIGH)
			{
				secondHalf = true;
			}

			if (firstHalf != secondHalf)
			{
				data |= mask;
			}

			mask = mask >> 1;
			if (i == 7)
			{
				mSerial->Advance(samples_to_first_center_of_first_data_bit);
			}
			else
			{
				mSerial->Advance(samples_per_bit / 2);
			}
		}

		

		//we have a byte to save. 
		Frame frame;
		frame.mData1 = data;
		frame.mFlags = 0;
		frame.mStartingSampleInclusive = starting_sample;
		frame.mEndingSampleInclusive = mSerial->GetSampleNumber();

		mResults->AddFrame( frame );
		mResults->CommitResults();
		ReportProgress( frame.mEndingSampleInclusive );
	}
}

bool ARINC717_BiphaseAnalyzer::NeedsRerun()
{
	return false;
}

U32 ARINC717_BiphaseAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 ARINC717_BiphaseAnalyzer::GetMinimumSampleRateHz()
{
	return mSettings->mBitRate * 4;
}

const char* ARINC717_BiphaseAnalyzer::GetAnalyzerName() const
{
	return "ARINC717_Biphase";
}

const char* GetAnalyzerName()
{
	return "ARINC717_Biphase";
}

Analyzer* CreateAnalyzer()
{
	return new ARINC717_BiphaseAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}
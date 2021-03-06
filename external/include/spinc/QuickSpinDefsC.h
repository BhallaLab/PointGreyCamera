//=============================================================================
// Copyright � 2016 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of
// Point Grey Research, Inc. ("Confidential Information"). You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the "License Agreement" that you
// entered into with PGR in connection with this software.
//
// UNLESS OTHERWISE SET OUT IN THE LICENSE AGREEMENT, THIS SOFTWARE IS
// PROVIDED ON AN "AS-IS" BASIS AND POINT GREY RESEARCH INC. MAKES NO
// REPRESENTATIONS OR WARRANTIES ABOUT THE SOFTWARE, EITHER EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OR
// CONDITIONS OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// NON-INFRINGEMENT. POINT GREY RESEARCH INC. SHALL NOT BE LIABLE FOR ANY
// DAMAGES, INCLUDING BUT NOT LIMITED TO ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, PUNITIVE, OR CONSEQUENTIAL DAMAGES, OR ANY LOSS OF PROFITS,
// REVENUE, DATA OR DATA USE, ARISING OUT OF OR IN CONNECTION WITH THIS
// SOFTWARE OR OTHERWISE SUFFERED BY YOU AS A RESULT OF USING, MODIFYING
// OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
   
/* Auto-generated file. Do not modify. */
/* Generated Fri Aug 19 10:27:56 2016 */

#ifndef PGR_SPINNAKER_QUICKSPINDEFS_C_H
#define PGR_SPINNAKER_QUICKSPINDEFS_C_H

#include "SpinnakerGenApiDefsC.h"

typedef spinNodeHandle quickSpinStringNode;
typedef spinNodeHandle quickSpinIntegerNode;
typedef spinNodeHandle quickSpinFloatNode;
typedef spinNodeHandle quickSpinBooleanNode;
typedef spinNodeHandle quickSpinEnumerationNode;
typedef spinNodeHandle quickSpinCommandNode;
typedef spinNodeHandle quickSpinRegisterNode;

typedef struct _quickSpin
{
	quickSpinEnumerationNode DeviceType;
	quickSpinEnumerationNode DeviceScanType;
	quickSpinStringNode DeviceVendorName;
	quickSpinStringNode DeviceModelName;
	quickSpinStringNode DeviceFamilyName;
	quickSpinStringNode DeviceManufacturerInfo;
	quickSpinStringNode DeviceVersion;
	quickSpinStringNode DeviceFirmwareVersion;
	quickSpinStringNode DeviceSerialNumber;
	quickSpinStringNode DeviceUserID;
	quickSpinIntegerNode DeviceSFNCVersionMajor;
	quickSpinIntegerNode DeviceSFNCVersionMinor;
	quickSpinIntegerNode DeviceSFNCVersionSubMinor;
	quickSpinIntegerNode DeviceManifestEntrySelector;
	quickSpinIntegerNode DeviceManifestXMLMajorVersion;
	quickSpinIntegerNode DeviceManifestXMLMinorVersion;
	quickSpinIntegerNode DeviceManifestXMLSubMinorVersion;
	quickSpinIntegerNode DeviceManifestSchemaMajorVersion;
	quickSpinIntegerNode DeviceManifestSchemaMinorVersion;
	quickSpinStringNode DeviceManifestPrimaryURL;
	quickSpinStringNode DeviceManifestSecondaryURL;
	quickSpinEnumerationNode DeviceTLType;
	quickSpinIntegerNode DeviceTLVersionMajor;
	quickSpinIntegerNode DeviceTLVersionMinor;
	quickSpinIntegerNode DeviceTLVersionSubMinor;
	quickSpinIntegerNode DeviceGenCPVersionMajor;
	quickSpinIntegerNode DeviceGenCPVersionMinor;
	quickSpinIntegerNode DeviceMaxThroughput;
	quickSpinIntegerNode DeviceConnectionSelector;
	quickSpinIntegerNode DeviceConnectionSpeed;
	quickSpinEnumerationNode DeviceConnectionStatus;
	quickSpinIntegerNode DeviceLinkSelector;
	quickSpinIntegerNode DeviceLinkSpeed;
	quickSpinEnumerationNode DeviceLinkThroughputLimitMode;
	quickSpinIntegerNode DeviceLinkThroughputLimit;
	quickSpinIntegerNode DeviceLinkConnectionCount;
	quickSpinEnumerationNode DeviceLinkHeartbeatMode;
	quickSpinFloatNode DeviceLinkHeartbeatTimeout;
	quickSpinFloatNode DeviceLinkCommandTimeout;
	quickSpinIntegerNode DeviceStreamChannelCount;
	quickSpinIntegerNode DeviceStreamChannelSelector;
	quickSpinEnumerationNode DeviceStreamChannelType;
	quickSpinIntegerNode DeviceStreamChannelLink;
	quickSpinEnumerationNode DeviceStreamChannelEndianness;
	quickSpinIntegerNode DeviceStreamChannelPacketSize;
	quickSpinIntegerNode DeviceEventChannelCount;
	quickSpinEnumerationNode DeviceCharacterSet;
	quickSpinCommandNode DeviceReset;
	quickSpinEnumerationNode DeviceIndicatorMode;
	quickSpinCommandNode DeviceFeaturePersistenceStart;
	quickSpinCommandNode DeviceFeaturePersistenceEnd;
	quickSpinCommandNode DeviceRegistersStreamingStart;
	quickSpinCommandNode DeviceRegistersStreamingEnd;
	quickSpinCommandNode DeviceRegistersCheck;
	quickSpinBooleanNode DeviceRegistersValid;
	quickSpinEnumerationNode DeviceRegistersEndianness;
	quickSpinEnumerationNode DeviceTemperatureSelector;
	quickSpinFloatNode DeviceTemperature;
	quickSpinEnumerationNode DeviceClockSelector;
	quickSpinFloatNode DeviceClockFrequency;
	quickSpinEnumerationNode DeviceSerialPortSelector;
	quickSpinEnumerationNode DeviceSerialPortBaudRate;
	quickSpinIntegerNode Timestamp;
	quickSpinCommandNode TimestampReset;
	quickSpinCommandNode TimestampLatch;
	quickSpinIntegerNode TimestampLatchValue;
	quickSpinIntegerNode SensorWidth;
	quickSpinIntegerNode SensorHeight;
	quickSpinEnumerationNode SensorTaps;
	quickSpinEnumerationNode SensorDigitizationTaps;
	quickSpinIntegerNode WidthMax;
	quickSpinIntegerNode HeightMax;
	quickSpinEnumerationNode RegionSelector;
	quickSpinEnumerationNode RegionMode;
	quickSpinEnumerationNode RegionDestination;
	quickSpinEnumerationNode ImageComponentSelector;
	quickSpinBooleanNode ImageComponentEnable;
	quickSpinIntegerNode Width;
	quickSpinIntegerNode Height;
	quickSpinIntegerNode OffsetX;
	quickSpinIntegerNode OffsetY;
	quickSpinIntegerNode LinePitch;
	quickSpinEnumerationNode BinningSelector;
	quickSpinEnumerationNode BinningHorizontalMode;
	quickSpinIntegerNode BinningHorizontal;
	quickSpinEnumerationNode BinningVerticalMode;
	quickSpinIntegerNode BinningVertical;
	quickSpinEnumerationNode DecimationHorizontalMode;
	quickSpinIntegerNode DecimationHorizontal;
	quickSpinEnumerationNode DecimationVerticalMode;
	quickSpinIntegerNode DecimationVertical;
	quickSpinBooleanNode ReverseX;
	quickSpinBooleanNode ReverseY;
	quickSpinEnumerationNode PixelFormat;
	quickSpinEnumerationNode PixelFormatInfoSelector;
	quickSpinIntegerNode PixelFormatInfoID;
	quickSpinEnumerationNode PixelSize;
	quickSpinEnumerationNode PixelColorFilter;
	quickSpinIntegerNode PixelDynamicRangeMin;
	quickSpinIntegerNode PixelDynamicRangeMax;
	quickSpinEnumerationNode TestPatternGeneratorSelector;
	quickSpinEnumerationNode TestPattern;
	quickSpinEnumerationNode Deinterlacing;
	quickSpinEnumerationNode ImageCompressionMode;
	quickSpinEnumerationNode ImageCompressionRateOption;
	quickSpinIntegerNode ImageCompressionQuality;
	quickSpinFloatNode ImageCompressionBitrate;
	quickSpinEnumerationNode ImageCompressionJPEGFormatOption;
	quickSpinEnumerationNode SensorShutterMode;
	quickSpinEnumerationNode AcquisitionMode;
	quickSpinCommandNode AcquisitionStart;
	quickSpinCommandNode AcquisitionStop;
	quickSpinCommandNode AcquisitionAbort;
	quickSpinCommandNode AcquisitionArm;
	quickSpinIntegerNode AcquisitionFrameCount;
	quickSpinIntegerNode AcquisitionBurstFrameCount;
	quickSpinFloatNode AcquisitionFrameRate;
	quickSpinFloatNode AcquisitionLineRate;
	quickSpinEnumerationNode AcquisitionStatusSelector;
	quickSpinBooleanNode AcquisitionStatus;
	quickSpinEnumerationNode TriggerSelector;
	quickSpinEnumerationNode TriggerMode;
	quickSpinCommandNode TriggerSoftware;
	quickSpinEnumerationNode TriggerSource;
	quickSpinEnumerationNode TriggerActivation;
	quickSpinEnumerationNode TriggerOverlap;
	quickSpinFloatNode TriggerDelay;
	quickSpinIntegerNode TriggerDivider;
	quickSpinIntegerNode TriggerMultiplier;
	quickSpinEnumerationNode ExposureMode;
	quickSpinEnumerationNode ExposureTimeMode;
	quickSpinEnumerationNode ExposureTimeSelector;
	quickSpinFloatNode ExposureTime;
	quickSpinEnumerationNode ExposureAuto;
	quickSpinEnumerationNode GainSelector;
	quickSpinFloatNode Gain;
	quickSpinEnumerationNode GainAuto;
	quickSpinEnumerationNode GainAutoBalance;
	quickSpinEnumerationNode BlackLevelSelector;
	quickSpinFloatNode BlackLevel;
	quickSpinEnumerationNode BlackLevelAuto;
	quickSpinEnumerationNode BlackLevelAutoBalance;
	quickSpinEnumerationNode WhiteClipSelector;
	quickSpinFloatNode WhiteClip;
	quickSpinEnumerationNode BalanceRatioSelector;
	quickSpinFloatNode BalanceRatio;
	quickSpinEnumerationNode BalanceWhiteAuto;
	quickSpinFloatNode Gamma;
	quickSpinEnumerationNode LUTSelector;
	quickSpinBooleanNode LUTEnable;
	quickSpinIntegerNode LUTIndex;
	quickSpinIntegerNode LUTValue;
	quickSpinRegisterNode LUTValueAll;
	quickSpinEnumerationNode ColorTransformationSelector;
	quickSpinBooleanNode ColorTransformationEnable;
	quickSpinEnumerationNode ColorTransformationValueSelector;
	quickSpinFloatNode ColorTransformationValue;
	quickSpinEnumerationNode LineSelector;
	quickSpinEnumerationNode LineMode;
	quickSpinBooleanNode LineInverter;
	quickSpinBooleanNode LineStatus;
	quickSpinIntegerNode LineStatusAll;
	quickSpinEnumerationNode LineSource;
	quickSpinEnumerationNode LineFormat;
	quickSpinEnumerationNode UserOutputSelector;
	quickSpinBooleanNode UserOutputValue;
	quickSpinIntegerNode UserOutputValueAll;
	quickSpinIntegerNode UserOutputValueAllMask;
	quickSpinEnumerationNode CounterSelector;
	quickSpinEnumerationNode CounterEventSource;
	quickSpinEnumerationNode CounterEventActivation;
	quickSpinEnumerationNode CounterResetSource;
	quickSpinEnumerationNode CounterResetActivation;
	quickSpinCommandNode CounterReset;
	quickSpinIntegerNode CounterValue;
	quickSpinIntegerNode CounterValueAtReset;
	quickSpinIntegerNode CounterDuration;
	quickSpinEnumerationNode CounterStatus;
	quickSpinEnumerationNode CounterTriggerSource;
	quickSpinEnumerationNode CounterTriggerActivation;
	quickSpinEnumerationNode TimerSelector;
	quickSpinFloatNode TimerDuration;
	quickSpinFloatNode TimerDelay;
	quickSpinCommandNode TimerReset;
	quickSpinFloatNode TimerValue;
	quickSpinEnumerationNode TimerStatus;
	quickSpinEnumerationNode TimerTriggerSource;
	quickSpinEnumerationNode TimerTriggerActivation;
	quickSpinEnumerationNode EncoderSelector;
	quickSpinEnumerationNode EncoderSourceA;
	quickSpinEnumerationNode EncoderSourceB;
	quickSpinEnumerationNode EncoderMode;
	quickSpinIntegerNode EncoderDivider;
	quickSpinEnumerationNode EncoderOutputMode;
	quickSpinEnumerationNode EncoderStatus;
	quickSpinFloatNode EncoderTimeout;
	quickSpinEnumerationNode EncoderResetSource;
	quickSpinEnumerationNode EncoderResetActivation;
	quickSpinCommandNode EncoderReset;
	quickSpinIntegerNode EncoderValue;
	quickSpinIntegerNode EncoderValueAtReset;
	quickSpinEnumerationNode SoftwareSignalSelector;
	quickSpinCommandNode SoftwareSignalPulse;
	quickSpinEnumerationNode ActionUnconditionalMode;
	quickSpinIntegerNode ActionDeviceKey;
	quickSpinIntegerNode ActionQueueSize;
	quickSpinIntegerNode ActionSelector;
	quickSpinIntegerNode ActionGroupMask;
	quickSpinIntegerNode ActionGroupKey;
	quickSpinEnumerationNode EventSelector;
	quickSpinEnumerationNode EventNotification;
	quickSpinIntegerNode EventAcquisitionTrigger;
	quickSpinIntegerNode EventAcquisitionTriggerTimestamp;
	quickSpinIntegerNode EventAcquisitionTriggerFrameID;
	quickSpinIntegerNode EventAcquisitionStart;
	quickSpinIntegerNode EventAcquisitionStartTimestamp;
	quickSpinIntegerNode EventAcquisitionStartFrameID;
	quickSpinIntegerNode EventAcquisitionEnd;
	quickSpinIntegerNode EventAcquisitionEndTimestamp;
	quickSpinIntegerNode EventAcquisitionEndFrameID;
	quickSpinIntegerNode EventAcquisitionTransferStart;
	quickSpinIntegerNode EventAcquisitionTransferStartTimestamp;
	quickSpinIntegerNode EventAcquisitionTransferStartFrameID;
	quickSpinIntegerNode EventAcquisitionTransferEnd;
	quickSpinIntegerNode EventAcquisitionTransferEndTimestamp;
	quickSpinIntegerNode EventAcquisitionTransferEndFrameID;
	quickSpinIntegerNode EventAcquisitionError;
	quickSpinIntegerNode EventAcquisitionErrorTimestamp;
	quickSpinIntegerNode EventAcquisitionErrorFrameID;
	quickSpinIntegerNode EventFrameTrigger;
	quickSpinIntegerNode EventFrameTriggerTimestamp;
	quickSpinIntegerNode EventFrameTriggerFrameID;
	quickSpinIntegerNode EventFrameStart;
	quickSpinIntegerNode EventFrameStartTimestamp;
	quickSpinIntegerNode EventFrameStartFrameID;
	quickSpinIntegerNode EventFrameEnd;
	quickSpinIntegerNode EventFrameEndTimestamp;
	quickSpinIntegerNode EventFrameEndFrameID;
	quickSpinIntegerNode EventFrameBurstStart;
	quickSpinIntegerNode EventFrameBurstStartTimestamp;
	quickSpinIntegerNode EventFrameBurstStartFrameID;
	quickSpinIntegerNode EventFrameBurstEnd;
	quickSpinIntegerNode EventFrameBurstEndTimestamp;
	quickSpinIntegerNode EventFrameBurstEndFrameID;
	quickSpinIntegerNode EventFrameTransferStart;
	quickSpinIntegerNode EventFrameTransferStartTimestamp;
	quickSpinIntegerNode EventFrameTransferStartFrameID;
	quickSpinIntegerNode EventFrameTransferEnd;
	quickSpinIntegerNode EventFrameTransferEndTimestamp;
	quickSpinIntegerNode EventFrameTransferEndFrameID;
	quickSpinIntegerNode EventExposureStart;
	quickSpinIntegerNode EventExposureStartTimestamp;
	quickSpinIntegerNode EventExposureStartFrameID;
	quickSpinIntegerNode EventExposureEnd;
	quickSpinIntegerNode EventExposureEndTimestamp;
	quickSpinIntegerNode EventExposureEndFrameID;
	quickSpinIntegerNode EventStream0TransferStart;
	quickSpinIntegerNode EventStream0TransferStartTimestamp;
	quickSpinIntegerNode EventStream0TransferStartFrameID;
	quickSpinIntegerNode EventStream0TransferEnd;
	quickSpinIntegerNode EventStream0TransferEndTimestamp;
	quickSpinIntegerNode EventStream0TransferEndFrameID;
	quickSpinIntegerNode EventStream0TransferPause;
	quickSpinIntegerNode EventStream0TransferPauseTimestamp;
	quickSpinIntegerNode EventStream0TransferPauseFrameID;
	quickSpinIntegerNode EventStream0TransferResume;
	quickSpinIntegerNode EventStream0TransferResumeTimestamp;
	quickSpinIntegerNode EventStream0TransferResumeFrameID;
	quickSpinIntegerNode EventStream0TransferBlockStart;
	quickSpinIntegerNode EventStream0TransferBlockStartTimestamp;
	quickSpinIntegerNode EventStream0TransferBlockStartFrameID;
	quickSpinIntegerNode EventStream0TransferBlockEnd;
	quickSpinIntegerNode EventStream0TransferBlockEndTimestamp;
	quickSpinIntegerNode EventStream0TransferBlockEndFrameID;
	quickSpinIntegerNode EventStream0TransferBlockTrigger;
	quickSpinIntegerNode EventStream0TransferBlockTriggerTimestamp;
	quickSpinIntegerNode EventStream0TransferBlockTriggerFrameID;
	quickSpinIntegerNode EventStream0TransferBurstStart;
	quickSpinIntegerNode EventStream0TransferBurstStartTimestamp;
	quickSpinIntegerNode EventStream0TransferBurstStartFrameID;
	quickSpinIntegerNode EventStream0TransferBurstEnd;
	quickSpinIntegerNode EventStream0TransferBurstEndTimestamp;
	quickSpinIntegerNode EventStream0TransferBurstEndFrameID;
	quickSpinIntegerNode EventStream0TransferOverflow;
	quickSpinIntegerNode EventStream0TransferOverflowTimestamp;
	quickSpinIntegerNode EventStream0TransferOverflowFrameID;
	quickSpinIntegerNode EventSequencerSetChange;
	quickSpinIntegerNode EventSequencerSetChangeTimestamp;
	quickSpinIntegerNode EventSequencerSetChangeFrameID;
	quickSpinIntegerNode EventCounter0Start;
	quickSpinIntegerNode EventCounter0StartTimestamp;
	quickSpinIntegerNode EventCounter0StartFrameID;
	quickSpinIntegerNode EventCounter1Start;
	quickSpinIntegerNode EventCounter1StartTimestamp;
	quickSpinIntegerNode EventCounter1StartFrameID;
	quickSpinIntegerNode EventCounter0End;
	quickSpinIntegerNode EventCounter0EndTimestamp;
	quickSpinIntegerNode EventCounter0EndFrameID;
	quickSpinIntegerNode EventCounter1End;
	quickSpinIntegerNode EventCounter1EndTimestamp;
	quickSpinIntegerNode EventCounter1EndFrameID;
	quickSpinIntegerNode EventTimer0Start;
	quickSpinIntegerNode EventTimer0StartTimestamp;
	quickSpinIntegerNode EventTimer0StartFrameID;
	quickSpinIntegerNode EventTimer1Start;
	quickSpinIntegerNode EventTimer1StartTimestamp;
	quickSpinIntegerNode EventTimer1StartFrameID;
	quickSpinIntegerNode EventTimer0End;
	quickSpinIntegerNode EventTimer0EndTimestamp;
	quickSpinIntegerNode EventTimer0EndFrameID;
	quickSpinIntegerNode EventTimer1End;
	quickSpinIntegerNode EventTimer1EndTimestamp;
	quickSpinIntegerNode EventTimer1EndFrameID;
	quickSpinIntegerNode EventEncoder0Stopped;
	quickSpinIntegerNode EventEncoder0StoppedTimestamp;
	quickSpinIntegerNode EventEncoder0StoppedFrameID;
	quickSpinIntegerNode EventEncoder1Stopped;
	quickSpinIntegerNode EventEncoder1StoppedTimestamp;
	quickSpinIntegerNode EventEncoder1StoppedFrameID;
	quickSpinIntegerNode EventEncoder0Restarted;
	quickSpinIntegerNode EventEncoder0RestartedTimestamp;
	quickSpinIntegerNode EventEncoder0RestartedFrameID;
	quickSpinIntegerNode EventEncoder1Restarted;
	quickSpinIntegerNode EventEncoder1RestartedTimestamp;
	quickSpinIntegerNode EventEncoder1RestartedFrameID;
	quickSpinIntegerNode EventLine0RisingEdge;
	quickSpinIntegerNode EventLine0RisingEdgeTimestamp;
	quickSpinIntegerNode EventLine0RisingEdgeFrameID;
	quickSpinIntegerNode EventLine1RisingEdge;
	quickSpinIntegerNode EventLine1RisingEdgeTimestamp;
	quickSpinIntegerNode EventLine1RisingEdgeFrameID;
	quickSpinIntegerNode EventLine0FallingEdge;
	quickSpinIntegerNode EventLine0FallingEdgeTimestamp;
	quickSpinIntegerNode EventLine0FallingEdgeFrameID;
	quickSpinIntegerNode EventLine1FallingEdge;
	quickSpinIntegerNode EventLine1FallingEdgeTimestamp;
	quickSpinIntegerNode EventLine1FallingEdgeFrameID;
	quickSpinIntegerNode EventLine0AnyEdge;
	quickSpinIntegerNode EventLine0AnyEdgeTimestamp;
	quickSpinIntegerNode EventLine0AnyEdgeFrameID;
	quickSpinIntegerNode EventLine1AnyEdge;
	quickSpinIntegerNode EventLine1AnyEdgeTimestamp;
	quickSpinIntegerNode EventLine1AnyEdgeFrameID;
	quickSpinIntegerNode EventLinkTrigger0;
	quickSpinIntegerNode EventLinkTrigger0Timestamp;
	quickSpinIntegerNode EventLinkTrigger0FrameID;
	quickSpinIntegerNode EventLinkTrigger1;
	quickSpinIntegerNode EventLinkTrigger1Timestamp;
	quickSpinIntegerNode EventLinkTrigger1FrameID;
	quickSpinIntegerNode EventActionLate;
	quickSpinIntegerNode EventActionLateTimestamp;
	quickSpinIntegerNode EventActionLateFrameID;
	quickSpinIntegerNode EventLinkSpeedChange;
	quickSpinIntegerNode EventLinkSpeedChangeTimestamp;
	quickSpinIntegerNode EventLinkSpeedChangeFrameID;
	quickSpinIntegerNode EventError;
	quickSpinIntegerNode EventErrorTimestamp;
	quickSpinIntegerNode EventErrorFrameID;
	quickSpinIntegerNode EventErrorCode;
	quickSpinEnumerationNode UserSetSelector;
	quickSpinCommandNode UserSetLoad;
	quickSpinCommandNode UserSetSave;
	quickSpinEnumerationNode UserSetDefault;
	quickSpinEnumerationNode UserSetFeatureSelector;
	quickSpinBooleanNode UserSetFeatureEnable;
	quickSpinEnumerationNode SequencerMode;
	quickSpinEnumerationNode SequencerConfigurationMode;
	quickSpinEnumerationNode SequencerFeatureSelector;
	quickSpinBooleanNode SequencerFeatureEnable;
	quickSpinIntegerNode SequencerSetSelector;
	quickSpinCommandNode SequencerSetSave;
	quickSpinCommandNode SequencerSetLoad;
	quickSpinIntegerNode SequencerSetActive;
	quickSpinIntegerNode SequencerSetStart;
	quickSpinIntegerNode SequencerPathSelector;
	quickSpinIntegerNode SequencerSetNext;
	quickSpinEnumerationNode SequencerTriggerSource;
	quickSpinEnumerationNode SequencerTriggerActivation;
	quickSpinEnumerationNode FileSelector;
	quickSpinEnumerationNode FileOperationSelector;
	quickSpinCommandNode FileOperationExecute;
	quickSpinEnumerationNode FileOpenMode;
	quickSpinRegisterNode FileAccessBuffer;
	quickSpinIntegerNode FileAccessOffset;
	quickSpinIntegerNode FileAccessLength;
	quickSpinEnumerationNode FileOperationStatus;
	quickSpinIntegerNode FileOperationResult;
	quickSpinIntegerNode FileSize;
	quickSpinIntegerNode SourceCount;
	quickSpinEnumerationNode SourceSelector;
	quickSpinEnumerationNode TransferSelector;
	quickSpinEnumerationNode TransferControlMode;
	quickSpinEnumerationNode TransferOperationMode;
	quickSpinIntegerNode TransferBlockCount;
	quickSpinIntegerNode TransferBurstCount;
	quickSpinIntegerNode TransferQueueMaxBlockCount;
	quickSpinIntegerNode TransferQueueCurrentBlockCount;
	quickSpinEnumerationNode TransferQueueMode;
	quickSpinCommandNode TransferStart;
	quickSpinCommandNode TransferStop;
	quickSpinCommandNode TransferAbort;
	quickSpinCommandNode TransferPause;
	quickSpinCommandNode TransferResume;
	quickSpinEnumerationNode TransferTriggerSelector;
	quickSpinEnumerationNode TransferTriggerMode;
	quickSpinEnumerationNode TransferTriggerSource;
	quickSpinEnumerationNode TransferTriggerActivation;
	quickSpinEnumerationNode TransferStatusSelector;
	quickSpinBooleanNode TransferStatus;
	quickSpinEnumerationNode TransferComponentSelector;
	quickSpinIntegerNode TransferStreamChannel;
	quickSpinEnumerationNode Scan3dDistanceUnit;
	quickSpinEnumerationNode Scan3dCoordinateSystem;
	quickSpinEnumerationNode Scan3dOutputMode;
	quickSpinEnumerationNode Scan3dCoordinateSystemReference;
	quickSpinEnumerationNode Scan3dCoordinateSelector;
	quickSpinFloatNode Scan3dCoordinateScale;
	quickSpinFloatNode Scan3dCoordinateOffset;
	quickSpinBooleanNode Scan3dInvalidDataFlag;
	quickSpinFloatNode Scan3dInvalidDataValue;
	quickSpinFloatNode Scan3dAxisMin;
	quickSpinFloatNode Scan3dAxisMax;
	quickSpinEnumerationNode Scan3dCoordinateTransformSelector;
	quickSpinFloatNode Scan3dTransformValue;
	quickSpinEnumerationNode Scan3dCoordinateReferenceSelector;
	quickSpinFloatNode Scan3dCoordinateReferenceValue;
	quickSpinBooleanNode ChunkModeActive;
	quickSpinEnumerationNode ChunkSelector;
	quickSpinBooleanNode ChunkEnable;
	quickSpinIntegerNode ChunkPartSelector;
	quickSpinEnumerationNode ChunkImageComponent;
	quickSpinRegisterNode ChunkImage;
	quickSpinIntegerNode ChunkOffsetX;
	quickSpinIntegerNode ChunkOffsetY;
	quickSpinIntegerNode ChunkWidth;
	quickSpinIntegerNode ChunkHeight;
	quickSpinEnumerationNode ChunkPixelFormat;
	quickSpinIntegerNode ChunkPixelDynamicRangeMin;
	quickSpinIntegerNode ChunkPixelDynamicRangeMax;
	quickSpinIntegerNode ChunkTimestamp;
	quickSpinIntegerNode ChunkTimestampLatchValue;
	quickSpinIntegerNode ChunkLineStatusAll;
	quickSpinEnumerationNode ChunkCounterSelector;
	quickSpinIntegerNode ChunkCounterValue;
	quickSpinEnumerationNode ChunkTimerSelector;
	quickSpinFloatNode ChunkTimerValue;
	quickSpinEnumerationNode ChunkEncoderSelector;
	quickSpinIntegerNode ChunkScanLineSelector;
	quickSpinIntegerNode ChunkEncoderValue;
	quickSpinEnumerationNode ChunkEncoderStatus;
	quickSpinEnumerationNode ChunkExposureTimeSelector;
	quickSpinFloatNode ChunkExposureTime;
	quickSpinEnumerationNode ChunkGainSelector;
	quickSpinFloatNode ChunkGain;
	quickSpinEnumerationNode ChunkBlackLevelSelector;
	quickSpinFloatNode ChunkBlackLevel;
	quickSpinIntegerNode ChunkLinePitch;
	quickSpinIntegerNode ChunkFrameID;
	quickSpinEnumerationNode ChunkSourceID;
	quickSpinEnumerationNode ChunkRegionID;
	quickSpinIntegerNode ChunkTransferBlockID;
	quickSpinEnumerationNode ChunkTransferStreamID;
	quickSpinIntegerNode ChunkTransferQueueCurrentBlockCount;
	quickSpinIntegerNode ChunkStreamChannelID;
	quickSpinIntegerNode ChunkSequencerSetActive;
	quickSpinEnumerationNode ChunkScan3dDistanceUnit;
	quickSpinEnumerationNode ChunkScan3dOutputMode;
	quickSpinEnumerationNode ChunkScan3dCoordinateSystem;
	quickSpinEnumerationNode ChunkScan3dCoordinateSystemReference;
	quickSpinEnumerationNode ChunkScan3dCoordinateSelector;
	quickSpinFloatNode ChunkScan3dCoordinateScale;
	quickSpinFloatNode ChunkScan3dCoordinateOffset;
	quickSpinBooleanNode ChunkScan3dInvalidDataFlag;
	quickSpinFloatNode ChunkScan3dInvalidDataValue;
	quickSpinFloatNode ChunkScan3dAxisMin;
	quickSpinFloatNode ChunkScan3dAxisMax;
	quickSpinEnumerationNode ChunkScan3dCoordinateTransformSelector;
	quickSpinFloatNode ChunkScan3dTransformValue;
	quickSpinEnumerationNode ChunkScan3dCoordinateReferenceSelector;
	quickSpinFloatNode ChunkScan3dCoordinateReferenceValue;
	quickSpinIntegerNode TestPendingAck;
	quickSpinCommandNode TestEventGenerate;
	quickSpinIntegerNode PayloadSize;
	quickSpinEnumerationNode DeviceTapGeometry;
	quickSpinEnumerationNode GevPhysicalLinkConfiguration;
	quickSpinEnumerationNode GevCurrentPhysicalLinkConfiguration;
	quickSpinIntegerNode GevActiveLinkCount;
	quickSpinEnumerationNode GevSupportedOptionSelector;
	quickSpinBooleanNode GevSupportedOption;
	quickSpinIntegerNode GevInterfaceSelector;
	quickSpinIntegerNode GevMACAddress;
	quickSpinBooleanNode GevPAUSEFrameReception;
	quickSpinBooleanNode GevPAUSEFrameTransmission;
	quickSpinBooleanNode GevCurrentIPConfigurationLLA;
	quickSpinBooleanNode GevCurrentIPConfigurationDHCP;
	quickSpinBooleanNode GevCurrentIPConfigurationPersistentIP;
	quickSpinIntegerNode GevCurrentIPAddress;
	quickSpinIntegerNode GevCurrentSubnetMask;
	quickSpinIntegerNode GevCurrentDefaultGateway;
	quickSpinEnumerationNode GevIPConfigurationStatus;
	quickSpinStringNode GevFirstURL;
	quickSpinStringNode GevSecondURL;
	quickSpinIntegerNode GevPersistentIPAddress;
	quickSpinIntegerNode GevPersistentSubnetMask;
	quickSpinIntegerNode GevPersistentDefaultGateway;
	quickSpinIntegerNode GevDiscoveryAckDelay;
	quickSpinBooleanNode GevIEEE1588;
	quickSpinEnumerationNode GevIEEE1588ClockAccuracy;
	quickSpinEnumerationNode GevIEEE1588Status;
	quickSpinEnumerationNode GevGVCPExtendedStatusCodesSelector;
	quickSpinBooleanNode GevGVCPExtendedStatusCodes;
	quickSpinBooleanNode GevGVCPPendingAck;
	quickSpinIntegerNode GevPrimaryApplicationSwitchoverKey;
	quickSpinEnumerationNode GevGVSPExtendedIDMode;
	quickSpinEnumerationNode GevCCP;
	quickSpinIntegerNode GevPrimaryApplicationSocket;
	quickSpinIntegerNode GevPrimaryApplicationIPAddress;
	quickSpinIntegerNode GevMCPHostPort;
	quickSpinIntegerNode GevMCDA;
	quickSpinIntegerNode GevMCTT;
	quickSpinIntegerNode GevMCRC;
	quickSpinIntegerNode GevMCSP;
	quickSpinIntegerNode GevStreamChannelSelector;
	quickSpinBooleanNode GevSCCFGPacketResendDestination;
	quickSpinBooleanNode GevSCCFGAllInTransmission;
	quickSpinBooleanNode GevSCCFGUnconditionalStreaming;
	quickSpinBooleanNode GevSCCFGExtendedChunkData;
	quickSpinIntegerNode GevSCPInterfaceIndex;
	quickSpinIntegerNode GevSCPHostPort;
	quickSpinBooleanNode GevSCPSFireTestPacket;
	quickSpinBooleanNode GevSCPSDoNotFragment;
	quickSpinIntegerNode GevSCPD;
	quickSpinIntegerNode GevSCDA;
	quickSpinIntegerNode GevSCSP;
	quickSpinIntegerNode GevSCZoneCount;
	quickSpinIntegerNode GevSCZoneDirectionAll;
	quickSpinBooleanNode GevSCZoneConfigurationLock;
	quickSpinIntegerNode aPAUSEMACCtrlFramesTransmitted;
	quickSpinIntegerNode aPAUSEMACCtrlFramesReceived;
	quickSpinEnumerationNode ClConfiguration;
	quickSpinEnumerationNode ClTimeSlotsCount;
	quickSpinEnumerationNode CxpLinkConfigurationStatus;
	quickSpinEnumerationNode CxpLinkConfigurationPreferred;
	quickSpinEnumerationNode CxpLinkConfiguration;
	quickSpinIntegerNode CxpConnectionSelector;
	quickSpinEnumerationNode CxpConnectionTestMode;
	quickSpinIntegerNode CxpConnectionTestErrorCount;
	quickSpinIntegerNode CxpConnectionTestPacketCount;
	quickSpinCommandNode CxpPoCxpAuto;
	quickSpinCommandNode CxpPoCxpTurnOff;
	quickSpinCommandNode CxpPoCxpTripReset;
	quickSpinEnumerationNode CxpPoCxpStatus;
} quickSpin;

#endif // PGR_SPINNAKER_QUICKSPINDEFS_C_H

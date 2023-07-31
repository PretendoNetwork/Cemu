#pragma once

#include "Cemu/ncrypto/ncrypto.h"
#include "config/ActiveSettings.h"

#include "Cafe/OS/libs/nn_olv/nn_olv_Common.h"
#include "Cafe/OS/libs/coreinit/coreinit_MCP.h"


namespace nn
{
	namespace olv
	{

		class InitializeParam
		{
		public:
			static const inline uint32 FLAG_OFFLINE_MODE = (1 << 0);

			InitializeParam()
			{
				this->m_Flags = 0;
				this->m_ReportTypes = 7039;
				this->m_SysArgsSize = 0;
				this->m_Work = MEMPTR<uint8_t>(nullptr);
				this->m_SysArgs = MEMPTR<const void>(nullptr);
				this->m_WorkSize = 0;
			}
			static InitializeParam* __ctor(InitializeParam* _this)
			{
				if (!_this)
				{
					assert_dbg(); // DO NOT CONTINUE, SHOULD NEVER HAPPEN
					return nullptr;
				}
				else
					return new (_this) InitializeParam();
			}

			sint32 SetFlags(uint32 flags)
			{
				this->m_Flags = flags;
				return OLV_RESULT_SUCCESS;
			}
			static sint32 __SetFlags(InitializeParam* _this, uint32 flags)
			{
				return _this->SetFlags(flags);
			}

			sint32 SetWork(MEMPTR<uint8_t> pWorkData, uint32 workDataSize)
			{
				if (!pWorkData)
					return OLV_RESULT_INVALID_PTR;
				if (workDataSize < 0x10000)
					return OLV_RESULT_NOT_ENOUGH_SIZE;

				this->m_Work = pWorkData;
				this->m_WorkSize = workDataSize;
				return OLV_RESULT_SUCCESS;
			}
			static uint32 __SetWork(InitializeParam* _this, MEMPTR<uint8> pWorkData, uint32 workDataSize)
			{
				return _this->SetWork(pWorkData, workDataSize);
			}

			sint32 SetReportTypes(uint32 reportTypes)
			{
				this->m_ReportTypes = reportTypes;
				return OLV_RESULT_SUCCESS;
			}
			static sint32 __SetReportTypes(InitializeParam* _this, uint32 reportTypes)
			{
				return _this->SetReportTypes(reportTypes);
			}

			sint32 SetSysArgs(MEMPTR<const void> pSysArgs, uint32 sysArgsSize)
			{
				if (!pSysArgs)
					return OLV_RESULT_INVALID_PTR;

				if (!sysArgsSize)
					return OLV_RESULT_INVALID_PARAMETER;

				this->m_SysArgs = pSysArgs;
				this->m_SysArgsSize = sysArgsSize;

				return OLV_RESULT_SUCCESS;
			}
			static sint32 __SetSysArgs(InitializeParam* _this, MEMPTR<const void> pSysArgs, uint32 sysArgsSize)
			{
				return _this->SetSysArgs(pSysArgs, sysArgsSize);
			}

			uint32be m_Flags;
			uint32be m_ReportTypes;
			MEMPTR<uint8_t> m_Work;
			uint32be m_WorkSize;
			MEMPTR<const void> m_SysArgs;
			uint32be m_SysArgsSize;
			char unk[0x28];
		};
		static_assert(sizeof(nn::olv::InitializeParam) == 0x40, "sizeof(nn::olv::InitializeParam) != 0x40");

		class PortalAppParam
		{
		public:
			PortalAppParam()
			{
				this->m_serviceToken = ""; // todo
				this->m_startUrl = "https://discovery.olv.pretendo.cc/v1/endpoint";
			}
			static PortalAppParam* __ctor(PortalAppParam* _this)
			{
				if (!_this)
				{
					assert_dbg(); // DO NOT CONTINUE, SHOULD NEVER HAPPEN
					return nullptr;
				}
				else
					return new (_this) PortalAppParam();
			}

			std::string GetStartUrl()
			{
				return this->m_startUrl;
			}
			static std::string __GetStartUrl(PortalAppParam* _this)
			{
				return _this->GetStartUrl();
			}

			std::string GetDefaultBodyMemo()
			{
				// todo - i dont think this is right
				return "Default Body Baby";
			}
			static std::string __GetDefaultBodyMemo(PortalAppParam* _this)
			{
				return _this->GetDefaultBodyMemo();
			}

			std::string m_serviceToken;
			std::string m_startUrl;
		};


		namespace Report
		{
			uint32 GetReportTypes();
			void SetReportTypes(uint32 reportTypes);
		}

		bool IsInitialized();
		sint32 Initialize(nn::olv::InitializeParam* pParam);
		sint32 InitializePortalApp(nn::olv::PortalAppParam* pPortalAppParam, nn::olv::InitializeParam* pInitializeParam);

		static void loadOliveInitializeTypes()
		{
			cafeExportRegisterFunc(Initialize, "nn_olv", "Initialize__Q2_2nn3olvFPCQ3_2nn3olv15InitializeParam", LogType::None);
			cafeExportRegisterFunc(InitializePortalApp, "nn_olv", "InitializePortalApp__Q3_2nn3olv6hiddenFPQ4_2nn3olv6hidden14PortalAppParamPCQ3_2nn3olv15InitializeParam", LogType::None);
			cafeExportRegisterFunc(IsInitialized, "nn_olv", "IsInitialized__Q2_2nn3olvFv", LogType::None);
			cafeExportRegisterFunc(Report::GetReportTypes, "nn_olv", "GetReportTypes__Q3_2nn3olv6ReportFv", LogType::None);
			cafeExportRegisterFunc(Report::SetReportTypes, "nn_olv", "SetReportTypes__Q3_2nn3olv6ReportFUi", LogType::None);

			cafeExportRegisterFunc(InitializeParam::__ctor, "nn_olv", "__ct__Q3_2nn3olv15InitializeParamFv", LogType::None);
			cafeExportRegisterFunc(InitializeParam::__SetFlags, "nn_olv", "SetFlags__Q3_2nn3olv15InitializeParamFUi", LogType::None);
			cafeExportRegisterFunc(InitializeParam::__SetWork, "nn_olv", "SetWork__Q3_2nn3olv15InitializeParamFPUcUi", LogType::None);
			cafeExportRegisterFunc(InitializeParam::__SetReportTypes, "nn_olv", "SetReportTypes__Q3_2nn3olv15InitializeParamFUi", LogType::None);
			cafeExportRegisterFunc(InitializeParam::__SetSysArgs, "nn_olv", "SetSysArgs__Q3_2nn3olv15InitializeParamFPCvUi", LogType::None);

			cafeExportRegisterFunc(PortalAppParam::__ctor, "nn_olv", "__ct__Q4_2nn3olv6hidden14PortalAppParamFv", LogType::None);
			cafeExportRegisterFunc(PortalAppParam::__GetStartUrl, "nn_olv", "GetStartUrl__Q4_2nn3olv6hidden14PortalAppParamCFv", LogType::None);
			cafeExportRegisterFunc(PortalAppParam::__GetDefaultBodyMemo, "nn_olv", "GetDefaultBodyMemo__Q4_2nn3olv6hidden14PortalAppParamCFv", LogType::None);
		}
	}
}
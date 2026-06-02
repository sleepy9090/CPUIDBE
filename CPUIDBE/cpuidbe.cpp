/*
    File           cpuidbe.cpp
    Brief          CPUID Backend DLL implementation for Windows
    Copyright      2026 Shawn M. Crawford [sleepy]
    Date           05/29/2026
    Author         Shawn M. Crawford [sleepy]
*/
#include <iomanip>
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <intrin.h>

using namespace std;

unsigned int ExtractBits(unsigned int num,
                         unsigned int pos,
                         unsigned int k)
{
    // Right shift 'num' by 'pos' bits
    unsigned int shifted = (num >> pos);

    // Create a mask with 'k' bits set to 1
    unsigned int mask = (1 << k) - 1;

    // Apply the mask to the shifted number
    return (shifted & mask);
}

#pragma region EAX=0x0: Highest Function Parameter and Manufacturer ID

extern "C" __declspec(dllexport) int __cdecl GetEAX0EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x0, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX0EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x0, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX0ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x0, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX0EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x0, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX0EAXHightestFunctionParameter()
{
    // EAX=0: Highest Function Parameter
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x0, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec (dllexport) char* __cdecl GetEAX0EBXEDXECXCpuVendor()
{
	// EAX=0: Manufacturer ID
	int cpuInfo[4];
	char vendor[13] = { 0 }; // 12 characters + null terminator
	__cpuidex(cpuInfo, 0x0, 0); // Get CPU vendor
	*reinterpret_cast<int*>(vendor) = cpuInfo[1]; // EBX
	*reinterpret_cast<int*>(vendor + 4) = cpuInfo[3]; // EDX
	*reinterpret_cast<int*>(vendor + 8) = cpuInfo[2]; // ECX
	return vendor;
}
#pragma endregion

#pragma region EAX=0x1: Processor Info and Feature Bits
extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX0_3_SteppingId()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int steppingId = ExtractBits(cpuInfo[0], 0, 4);

    return steppingId;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX4_7_ModelId()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int modelId = ExtractBits(cpuInfo[0], 4, 4);

    return modelId;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX8_11_FamilyId()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int familyId = ExtractBits(cpuInfo[0], 8, 4);

    return familyId;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX12_13_ProcessorType()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int processorType = ExtractBits(cpuInfo[0], 12, 2);

    return processorType;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX14_15_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int reserved14_15 = ExtractBits(cpuInfo[0], 14, 2);

    return reserved14_15;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX16_19_ExtendedModelId()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int extendedModelId = ExtractBits(cpuInfo[0], 16, 4);

    return extendedModelId;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX16_19_ExtendedModelIdLeftShifted()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int extendedModelId = ExtractBits(cpuInfo[0], 16, 4);
    unsigned int familyId = ExtractBits(cpuInfo[0], 8, 4);
    //unsigned int extendedModelIdLeftShifted = 0;
    //if (familyId == 0x6 || familyId == 0xF)
    //{
        unsigned int extendedModelIdLeftShifted = extendedModelId << 4;
    //}

    return extendedModelIdLeftShifted;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAXCalculatedProcessorModel()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int extendedModelId = ExtractBits(cpuInfo[0], 16, 4);
    unsigned int extendedModelIdLeftShifted = extendedModelId << 4;
    unsigned int modelId = ExtractBits(cpuInfo[0], 4, 4);
    //if (familyId == 0x6 || familyId == 0xF)
    //{
        unsigned int processorModel = modelId + extendedModelIdLeftShifted;
    //}
    return processorModel;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX20_27_ExtendedFamilyId()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int extendedFamilyId = ExtractBits(cpuInfo[0], 20, 8);

    return extendedFamilyId;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX28_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int reserved28_31 = ExtractBits(cpuInfo[0], 28, 4);

    return reserved28_31;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EBX0_7_BrandIndex()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int brandIndex = ExtractBits(cpuInfo[1], 0, 8);

    return brandIndex;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EBX8_15_CLFLUSHLineSize()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int clflushLineSize = ExtractBits(cpuInfo[1], 8, 8);

    return clflushLineSize;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EBX16_23_MaxNumAddrIdsLogProcsInPhyPckg()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int maxNumAddrIdsLogProcsInPhyPckg = ExtractBits(cpuInfo[1], 16, 8);

    return maxNumAddrIdsLogProcsInPhyPckg;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EBX24_31_LocalAPICID()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int localAPICID = ExtractBits(cpuInfo[1], 24, 8);

    return localAPICID;
}

// ECX feature bits
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX00SSE3IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sse3Supported = ExtractBits(cpuInfo[2], 0, 1);

    return (bool)sse3Supported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX01PCLMULQDQIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pclmulqdqSupported = ExtractBits(cpuInfo[2], 1, 1);

    return (bool)pclmulqdqSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX02DTES64IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int dtes64Supported = ExtractBits(cpuInfo[2], 2, 1);

    return (bool)dtes64Supported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX03MONITORIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int monitorSupported = ExtractBits(cpuInfo[2], 3, 1);

    return (bool)monitorSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX04DSCPLIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int dscplSupported = ExtractBits(cpuInfo[2], 4, 1);

    return (bool)dscplSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX05VMXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int vmxSupported = ExtractBits(cpuInfo[2], 5, 1);

    return (bool)vmxSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX06SMXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int smxSupported = ExtractBits(cpuInfo[2], 6, 1);

    return (bool)smxSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX07ESTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int estSupported = ExtractBits(cpuInfo[2], 7, 1);

    return (bool)estSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX08TM2IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int tm2Supported = ExtractBits(cpuInfo[2], 8, 1);

    return (bool)tm2Supported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX09SSSE3IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int ssse3Supported = ExtractBits(cpuInfo[2], 9, 1);

    return (bool)ssse3Supported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX10CNXTIDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int cnxtidSupported = ExtractBits(cpuInfo[2], 10, 1);

    return (bool)cnxtidSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX11SDBGIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sdbgSupported = ExtractBits(cpuInfo[2], 11, 1);

    return (bool)sdbgSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX12FMAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int fmaSupported = ExtractBits(cpuInfo[2], 12, 1);

    return (bool)fmaSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX13CMPXCHG16BIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int cmpxchg16bSupported = ExtractBits(cpuInfo[2], 13, 1);

    return (bool)cmpxchg16bSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX14xTPRUpdateControlIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int xtpRUpdateControlSupported = ExtractBits(cpuInfo[2], 14, 1);

    return (bool)xtpRUpdateControlSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX15PDCMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pdcmsupported = ExtractBits(cpuInfo[2], 15, 1);

    return (bool)pdcmsupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX16ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 16, 1);

    return (bool)reservedSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX17PCIDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pcidSupported = ExtractBits(cpuInfo[2], 17, 1);

    return (bool)pcidSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX18DCAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int dcaSupported = ExtractBits(cpuInfo[2], 18, 1);

    return (bool)dcaSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX19SSE41IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sse41Supported = ExtractBits(cpuInfo[2], 19, 1);

    return (bool)sse41Supported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX20SSE42IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sse42Supported = ExtractBits(cpuInfo[2], 20, 1);

    return (bool)sse42Supported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX21X2APICIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int x2apicSupported = ExtractBits(cpuInfo[2], 21, 1);

    return (bool)x2apicSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX22MOVBEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int movbeSupported = ExtractBits(cpuInfo[2], 22, 1);

    return (bool)movbeSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX23POPCNTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int popcntSupported = ExtractBits(cpuInfo[2], 23, 1);

    return (bool)popcntSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX24TSCDeadlineIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int tscDeadlineSupported = ExtractBits(cpuInfo[2], 24, 1);

    return (bool)tscDeadlineSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX25AESNIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int aesniSupported = ExtractBits(cpuInfo[2], 25, 1);

    return (bool)aesniSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX26XSAVEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int xsaveSupported = ExtractBits(cpuInfo[2], 26, 1);

    return (bool)xsaveSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX27OSXSAVEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int osxsaveSupported = ExtractBits(cpuInfo[2], 27, 1);

    return (bool)osxsaveSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX28AVXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int avxSupported = ExtractBits(cpuInfo[2], 28, 1);

    return (bool)avxSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX29F16CIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int f16cSupported = ExtractBits(cpuInfo[2], 29, 1);

    return (bool)f16cSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX30RDRANDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int rdrandSupported = ExtractBits(cpuInfo[2], 30, 1);

    return (bool)rdrandSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX31HypervisorIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int hypervisorSupported = ExtractBits(cpuInfo[2], 31, 1);

    return (bool)hypervisorSupported;
}

// EDX feature bits


#pragma endregion





#pragma region EAX=0x2: Cache and TLB Descriptor Information
#pragma endregion




#pragma region EAX=0x3: Processor Serial Number
#pragma endregion




#pragma region EAX=0x4 and EAX=0x8000001D: Cache Hierarchy and Topology
#pragma endregion





#pragma region EAX=0x4 and EAX=0xB: Intel Thread/Core and Cache Topology
#pragma endregion

#pragma region EAX=0x5: MONITOR/MWAIT Features
#pragma endregion

#pragma region EAX=0x6: Thermal and Power Management
#pragma endregion

#pragma region EAX=0x7, ECX=0x0: Extended Features
#pragma endregion

#pragma region EAX=0x7, ECX=0x1: Extended Features
#pragma endregion

#pragma region EAX=0x7, ECX=0x2: Extended Features
#pragma endregion

#pragma region EAX=0x0D: XSAVE Features and State Components
#pragma endregion

#pragma region EAX=0x12: SGX Capabilities
#pragma endregion

#pragma region EAX=0x14, ECX=0x0: Processor Trace feature bits in EBX and ECX
#pragma endregion

#pragma region EAX=0x14, ECX=0x1: Processor Trace packet generation information in EAX, EBX and ECX
#pragma endregion

#pragma region EAX=0x15: TSC and Core Crystal frequency information
#pragma endregion

#pragma region EAX=0x16: Processor and Bus specification frequencies
#pragma endregion

#pragma region EAX=0x17: SoC Vendor Attribute Enumeration
#pragma endregion

#pragma region EAX=0x18: TLB Hierarchy and Topology
#pragma endregion

#pragma region EAX=0x19: Intel Key Locker Features
#pragma endregion

#pragma region EAX=0x1D: Intel AMX Tile Information
#pragma endregion

#pragma region EAX=0x1E: Intel AMX Tile Multiplier (TMUL) Information
#pragma endregion

#pragma region EAX=0x21: Reserved for TDX enumeration
#pragma endregion

#pragma region EAX=0x24, ECX=0x0: AVX10 Converged Vector ISA
#pragma endregion

#pragma region EAX=0x24, ECX=0x1: Discrete AVX10 Features
#pragma endregion

#pragma region EAX=0x20000000: Highest Xeon Phi Function Implemented
#pragma endregion

#pragma region EAX=0x20000001: Xeon Phi Feature Bits
#pragma endregion

#pragma region EAX=0x40000000h-0x4FFFFFFFh: Reserved for Hypervisors
#pragma endregion

#pragma region EAX=0x80000000: Highest Extended Function Implemented
#pragma endregion

#pragma region EAX=0x80000001: Extended Processor Info and Feature Bits
#pragma endregion

#pragma region EAX=0x80000002,0x80000003,0x80000004: Processor Brand String
#pragma endregion

#pragma region EAX=0x80000005: L1 Cache and TLB Identifiers
#pragma endregion

#pragma region EAX=0x80000006: Extended L2 Cache Features
#pragma endregion

#pragma region EAX=0x80000007: Processor Power Management Information and RAS Capabilities
#pragma endregion

#pragma region EAX=0x80000008: Virtual and Physical Address Sizes
#pragma endregion

#pragma region EAX=0x8000000A: SVM features
#pragma endregion

#pragma region EAX=0x8000001F: Encrypted Memory Capabilities
#pragma endregion

#pragma region EAX=0x80000021: Extended Feature Identification
#pragma endregion

#pragma region EAX=0x80000025: Encrypted Memory Capabilities 2
#pragma endregion

#pragma region EAX=0x8C860000: Hygon Extended Feature Flags
#pragma endregion

#pragma region EAX=0x8FFFFFFE: AMD Easter Eggs
#pragma endregion

#pragma region EAX=0x8FFFFFFF: AMD Easter Eggs
#pragma endregion

#pragma region EAX=0xC0000000: Highest Centaur Extended Function
#pragma endregion

#pragma region EAX=0xC0000001: Centaur Feature Information
#pragma endregion

#pragma region EAX=0xC0000002: Centaur Extended CPUID Performance Data
#pragma endregion

#pragma region EAX=0xC0000006, ECX=0: Zhaoxin Feature Information
#pragma endregion

#pragma region
#pragma endregion

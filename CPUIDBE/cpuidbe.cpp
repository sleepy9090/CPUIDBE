#include <iomanip>
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <intrin.h>

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

// TODO: Implement functions for ECX feature bits

// TODO: Implement functions for EDX feature bits


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

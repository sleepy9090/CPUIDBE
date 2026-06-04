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
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX00FPUIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int fpuSupported = ExtractBits(cpuInfo[3], 0, 1);

    return (bool)fpuSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX01VMEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int vmeSupported = ExtractBits(cpuInfo[3], 1, 1);

    return (bool)vmeSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX02DEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int deSupported = ExtractBits(cpuInfo[3], 2, 1);

    return (bool)deSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX03PSEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pseSupported = ExtractBits(cpuInfo[3], 3, 1);

    return (bool)pseSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX04TSCIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int tscSupported = ExtractBits(cpuInfo[3], 4, 1);

    return (bool)tscSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX05MSRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int msrSupported = ExtractBits(cpuInfo[3], 5, 1);

    return (bool)msrSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX06PAEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int paeSupported = ExtractBits(cpuInfo[3], 6, 1);

    return (bool)paeSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX07MCEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int mceSupported = ExtractBits(cpuInfo[3], 7, 1);

    return (bool)mceSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX08CX8IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int cx8Supported = ExtractBits(cpuInfo[3], 8, 1);

    return (bool)cx8Supported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX09APICIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int apicSupported = ExtractBits(cpuInfo[3], 9, 1);

    return (bool)apicSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX10ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 10, 1);

    return (bool)reservedSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX11SEPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sepSupported = ExtractBits(cpuInfo[3], 11, 1);

    return (bool)sepSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX12MTRRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int mtrrSupported = ExtractBits(cpuInfo[3], 12, 1);

    return (bool)mtrrSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX13PGEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pgeSupported = ExtractBits(cpuInfo[3], 13, 1);

    return (bool)pgeSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX14MCAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int mcaSupported = ExtractBits(cpuInfo[3], 14, 1);

    return (bool)mcaSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX15CMOVIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int cmovSupported = ExtractBits(cpuInfo[3], 15, 1);

    return (bool)cmovSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX16PATIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int patSupported = ExtractBits(cpuInfo[3], 16, 1);

    return (bool)patSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX17PSE36IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pse36Supported = ExtractBits(cpuInfo[3], 17, 1);

    return (bool)pse36Supported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX18PSNIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int psnSupported = ExtractBits(cpuInfo[3], 18, 1);

    return (bool)psnSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX19CLFSHIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int clflushSupported = ExtractBits(cpuInfo[3], 19, 1);

    return (bool)clflushSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX20NXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int nxSupported = ExtractBits(cpuInfo[3], 20, 1);

    return (bool)nxSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX21DSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int dsSupported = ExtractBits(cpuInfo[3], 21, 1);

    return (bool)dsSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX22ACPIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int acpiSupported = ExtractBits(cpuInfo[3], 22, 1);

    return (bool)acpiSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX23MMXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int mmxSupported = ExtractBits(cpuInfo[3], 23, 1);

    return (bool)mmxSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX24FXSRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int fxsrSupported = ExtractBits(cpuInfo[3], 24, 1);

    return (bool)fxsrSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX25SSEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sseSupported = ExtractBits(cpuInfo[3], 25, 1);

    return (bool)sseSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX26SSE2IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sse2Supported = ExtractBits(cpuInfo[3], 26, 1);

    return (bool)sse2Supported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX27SSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int ssSupported = ExtractBits(cpuInfo[3], 27, 1);

    return (bool)ssSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX28HTTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int httSupported = ExtractBits(cpuInfo[3], 28, 1);

    return (bool)httSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX29TMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int tmSupported = ExtractBits(cpuInfo[3], 29, 1);

    return (bool)tmSupported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX30IA64IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int ia64Supported = ExtractBits(cpuInfo[3], 30, 1);

    return (bool)ia64Supported;
}

extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX31PBEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pbeSupported = ExtractBits(cpuInfo[3], 31, 1);

    return (bool)pbeSupported;
}

#pragma endregion

















#pragma region EAX=0x2: Cache and TLB Descriptor Information

extern "C" __declspec(dllexport) int __cdecl GetEAX2EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX2EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX2ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX2EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion
























#pragma region EAX=0x3: Processor Serial Number

extern "C" __declspec(dllexport) int __cdecl GetEAX3EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x3, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX3EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x3, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX3ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x3, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX3EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x3, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion













#pragma region EAX=0x4 and EAX=0x8000001D: Cache Hierarchy and Topology

// EAX=0x4
extern "C" __declspec(dllexport) int __cdecl GetEAX4EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX4EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX4ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX4EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}







//EAX=0x8000001D
extern "C" __declspec(dllexport) int __cdecl GetEAX8000001DEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001D, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8000001DEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001D, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8000001DECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001D, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8000001DEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001D, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}





#pragma endregion
















#pragma region EAX=0x4 and EAX=0xB: Intel Thread/Core and Cache Topology

/*
// EAX=0x4
extern "C" __declspec(dllexport) int __cdecl GetEAX4EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX4EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX4ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX4EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}
*/

extern "C" __declspec(dllexport) int __cdecl GetEAXBEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xB, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXBEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xB, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXBECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xB, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXBEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xB, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion












#pragma region EAX=0x5: MONITOR/MWAIT Features

extern "C" __declspec(dllexport) int __cdecl GetEAX5EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX5EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX5ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX5EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion




















#pragma region EAX=0x6: Thermal and Power Management

extern "C" __declspec(dllexport) int __cdecl GetEAX6EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX6EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX6ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX6EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion
















#pragma region EAX=0x7, ECX=0x0: Extended Features

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX0EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX0EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX0ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX0EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion














#pragma region EAX=0x7, ECX=0x1: Extended Features

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX1EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX1EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX1ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX1EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion










#pragma region EAX=0x7, ECX=0x2: Extended Features

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX2EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX2EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX2ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX7ECX2EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion










#pragma region EAX=0x0D: XSAVE Features and State Components

extern "C" __declspec(dllexport) int __cdecl GetEAXDEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xD, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXDEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xD, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXDECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xD, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXDEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xD, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion













#pragma region EAX=0x12: SGX Capabilities

extern "C" __declspec(dllexport) int __cdecl GetEAX12EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x12, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX12EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x12, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX12ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x12, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX12EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x12, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion















#pragma region EAX=0x14, ECX=0x0: Processor Trace feature bits in EBX and ECX

extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX0EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX0EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX0ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX0EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}








// EBX Feature Bits
/* CR3 filtering supported - (cr3_filter). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX0_Cr3FilterIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int cr3FilterSupported = ExtractBits(cpuInfo[1], 0, 1);

    return (bool)cr3FilterSupported;
}

/* Configurable PSB (Packet Stream Boundary) packet rate and Cycle-Accurate Mode (CYC packets) supported. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX1_ConfigurablePSBIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int configurablePSBSupported = ExtractBits(cpuInfo[1], 1, 1);

    return (bool)configurablePSBSupported;
}

/* IP filtering, TraceStop filtering and preservation of PT MSRs across warm reset supported - (ip_filter). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX2_IPFilterIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int ipFilterSupported = ExtractBits(cpuInfo[1], 2, 1);

    return (bool)ipFilterSupported;
}

/* MTC (Mini Time Counter) timing packets supported, and suppression of COFI (Change of Flow Instructions) packets supported. - (mtc). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX3_MtcIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int mtcSupported = ExtractBits(cpuInfo[1], 3, 1);

    return (bool)mtcSupported;
}

/* PTWRITE instruction supported - (ptwrite). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX4_PtwriteIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int ptwriteSupported = ExtractBits(cpuInfo[1], 4, 1);

    return (bool)ptwriteSupported;
}

/* Power Event Trace supported - (pwr_evt_­trace). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX5_PwrEvtTraceIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int pwrEvtTraceSupported = ExtractBits(cpuInfo[1], 5, 1);

    return (bool)pwrEvtTraceSupported;
}

/* Preservation of PSB and PMI (performance monitoring interrupt) supported - (pmi_preserve). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX6_PmiPreserveIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int pmiPreserveSupported = ExtractBits(cpuInfo[1], 6, 1);

    return (bool)pmiPreserveSupported;
}

/* Event Trace packet generation supported (event_trace). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX7_EventTraceIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int eventTraceSupported = ExtractBits(cpuInfo[1], 7, 1);

    return (bool)eventTraceSupported;
}

/* TNT (Branch Taken-Not-Taken) packet generation disable supported. - (tnt_dis). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX8_TntDisIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int tntDisSupported = ExtractBits(cpuInfo[1], 8, 1);

    return (bool)tntDisSupported;
}

/* PTTT (Processor Trace Trigger Tracing) supported - (PTTT). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX9_PtttIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int ptttSupported = ExtractBits(cpuInfo[1], 9, 1);

    return (bool)ptttSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX10_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 10, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX11_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 11, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX12_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 12, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX13_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 13, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX14_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 14, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX15_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 15, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX16_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 16, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX17_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 17, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX18_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 18, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX19_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 19, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX20_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 20, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX21_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 21, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX22_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 22, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX23_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 23, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX24_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 24, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX25_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 25, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX26_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 26, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX27_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 27, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX28_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 28, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX29_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 29, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX30_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 30, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_EBX31_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 31, 1);

    return (bool)reservedSupported;
}

// ECX Feature Bits





#pragma endregion










#pragma region EAX=0x14, ECX=0x1: Processor Trace packet generation information in EAX, EBX and ECX

extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

/* Number of configurable address ranges for filtering = (rangecnt). */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EAX0_2_Rangecnt()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int rangecnt = ExtractBits(cpuInfo[0], 0, 2);

    return rangecnt;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EAX3_5_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int reserved = ExtractBits(cpuInfo[0], 3, 5);

    return reserved;
}

/* Number of IA32_RTIT_TRIGGERx_CFG MSRs. (Number of triggers supported is 4x this value) - (TRIGGER_CFG_CNT). */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EAX8_10_TriggerConfigCount()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int triggerConfigCount = ExtractBits(cpuInfo[0], 8, 3);

    return triggerConfigCount;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EAX11_14_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int reserved = ExtractBits(cpuInfo[0], 11, 4);

    return reserved;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EAX15_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int reserved = ExtractBits(cpuInfo[0], 15, 1);

    return reserved;
}

/* Bitmap of supported MTC period encodings - (mtc_rate). */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EAX16_31_MtcRate()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int mtcRate = ExtractBits(cpuInfo[0], 16, 16);

    return mtcRate;
}

/* Bitmap of supported cycle threshold value encodings - (cyc_thresholds). */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EBX0_15_CycThresholds()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int cycThresholds = ExtractBits(cpuInfo[1], 0, 16);

    return cycThresholds;
}

/* Bitmap of supported Configurable PSB frequency encodings - (psb_rate). */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1EBX16_31_PsbRate()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int psbRate = ExtractBits(cpuInfo[1], 16, 16);

    return psbRate;
}

/* Trigger Action EN_ICNT supported. */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1ECX0_Icnt()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int icnt = ExtractBits(cpuInfo[2], 0, 1);

    return icnt;
}

/* Trigger actions TRACE_PAUSE and TRACE_RESUME supported = (TRIGGER_PAUSE). */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1ECX1_TriggerPause()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int triggerPause = ExtractBits(cpuInfo[2], 1, 1);

    return triggerPause;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1ECX2_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int reserved = ExtractBits(cpuInfo[2], 2, 1);

    return reserved;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1ECX3_7_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int reserved = ExtractBits(cpuInfo[2], 3, 5);

    return reserved;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1ECX8_10_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int reserved = ExtractBits(cpuInfo[2], 8, 3);

    return reserved;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1ECX11_14_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int reserved = ExtractBits(cpuInfo[2], 11, 4);

    return reserved;
}

/* Trigger input DR match supported - (TRIGGER_­DR_MATCH). */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1ECX15_TriggerDrMatch()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int triggerDrMatch = ExtractBits(cpuInfo[2], 15, 1);

    return triggerDrMatch;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX14ECX1ECX16_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    unsigned int reserved = ExtractBits(cpuInfo[2], 16, 16);

    return reserved;
}

#pragma endregion













#pragma region EAX=0x15: TSC and Core Crystal frequency information

extern "C" __declspec(dllexport) int __cdecl GetEAX15EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX15EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX15ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX15EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX15EAX_RatioOfTSCFrequencyToCoreCrystalClockFrequency_Denominator()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);

    return cpuInfo[0];
}

extern "C" __declspec(dllexport) int __cdecl GetEAX15EBX_RatioOfTSCFrequencyToCoreCrystalClockFrequency_Numerator()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);

    return cpuInfo[1];
}

extern "C" __declspec(dllexport) int __cdecl GetEAX15ECX_CoreCrystalClockFrequencyInHz()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);

    return cpuInfo[2];
}

extern "C" __declspec(dllexport) int __cdecl GetEAX15EDX_TSCFrequencyInUnitsOfHz()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);

    return cpuInfo[3];
}

#pragma endregion













#pragma region EAX=0x16: Processor and Bus specification frequencies

extern "C" __declspec(dllexport) int __cdecl GetEAX16EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX16EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX16ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX16EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX16EAX0_15_ProcessorBaseFrequencyInMHz()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    unsigned int processorBaseFrequency = ExtractBits(cpuInfo[0], 0, 16);

    return processorBaseFrequency;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX16EAX16_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    unsigned int reserved = ExtractBits(cpuInfo[0], 16, 16);

    return reserved;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX16EBX0_15_ProcessorMaxFrequencyInMHz()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    unsigned int processorMaxFrequency = ExtractBits(cpuInfo[1], 0, 16);

    return processorMaxFrequency;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX16EBX16_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    unsigned int reserved = ExtractBits(cpuInfo[1], 16, 16);

    return reserved;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX16ECX0_15_BusReferenceFrequencyInMHz()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    unsigned int busReferenceFrequency = ExtractBits(cpuInfo[2], 0, 16);

    return busReferenceFrequency;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX16ECX16_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    unsigned int reserved = ExtractBits(cpuInfo[2], 16, 16);

    return reserved;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX16EDX0_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    unsigned int reserved = ExtractBits(cpuInfo[3], 0, 32);

    return reserved;
}

#pragma endregion















#pragma region EAX=0x17: SoC Vendor Attribute Enumeration

extern "C" __declspec(dllexport) int __cdecl GetEAX17EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x17, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX17EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x17, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX17ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x17, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX17EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x17, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion

















#pragma region EAX=0x18: TLB Hierarchy and Topology

extern "C" __declspec(dllexport) int __cdecl GetEAX18EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x18, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX18EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x18, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX18ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x18, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX18EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x18, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion












#pragma region EAX=0x19: Intel Key Locker Features

extern "C" __declspec(dllexport) int __cdecl GetEAX19EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x19, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX19EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x19, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX19ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x19, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX19EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x19, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion










#pragma region EAX=0x1D: Intel AMX Tile Information

extern "C" __declspec(dllexport) int __cdecl GetEAX1DEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1D, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1DEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1D, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1DECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1D, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1DEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1D, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion













#pragma region EAX=0x1E: Intel AMX Tile Multiplier (TMUL) Information

extern "C" __declspec(dllexport) int __cdecl GetEAX1EEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1E, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1E, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1E, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX1EEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1E, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion











#pragma region EAX=0x21: Reserved for TDX enumeration

extern "C" __declspec(dllexport) int __cdecl GetEAX21EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x21, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX21EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x21, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX21ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x21, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX21EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x21, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion






#pragma region EAX=0x24, ECX=0x0: AVX10 Converged Vector ISA

extern "C" __declspec(dllexport) int __cdecl GetEAX24ECX0EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX24ECX0EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX24ECX0ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX24ECX0EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion










#pragma region EAX=0x24, ECX=0x1: Discrete AVX10 Features

extern "C" __declspec(dllexport) int __cdecl GetEAX24ECX1EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 1);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX24ECX1EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 1);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX24ECX1ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 1);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX24ECX1EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 1);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion





















#pragma region EAX=0x20000000: Highest Xeon Phi Function Implemented

extern "C" __declspec(dllexport) int __cdecl GetEAX20000000EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000000, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX20000000EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000000, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX20000000ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000000, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX20000000EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000000, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX20000000EAX_HighestXeonPhiFunctionImplemented()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000000, 0);

    return cpuInfo[0];
}

#pragma endregion

















#pragma region EAX=0x20000001: Xeon Phi Feature Bits

extern "C" __declspec(dllexport) int __cdecl GetEAX20000001EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000001, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX20000001EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000001, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX20000001ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000001, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX20000001EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000001, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion





















#pragma region EAX=0x40000000h-0x4FFFFFFFh: Reserved for Hypervisors

extern "C" __declspec(dllexport) int __cdecl GetEAX40000000EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x40000000, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX40000000EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x40000000, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX40000000ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x40000000, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX40000000EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x40000000, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion














#pragma region EAX=0x80000000: Highest Extended Function Implemented

extern "C" __declspec(dllexport) int __cdecl GetEAX80000000EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000000, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000000EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000000, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000000ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000000, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000000EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000000, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000000EAX_HighestExtendedFunctionImplemented()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000000, 0);

    return cpuInfo[0];
}

#pragma endregion

















#pragma region EAX=0x80000001: Extended Processor Info and Feature Bits

extern "C" __declspec(dllexport) int __cdecl GetEAX80000001EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000001, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000001EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000001, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000001ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000001, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000001EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000001, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion












#pragma region EAX=0x80000002,0x80000003,0x80000004: Processor Brand String

extern "C" __declspec(dllexport) int __cdecl GetEAX80000002EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000002, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000002EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000002, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000002ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000002, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000002EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000002, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000003EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000003, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000003EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000003, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000003ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000003, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000003EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000003, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000004EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000004, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000004EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000004, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000004ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000004, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000004EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000004, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

extern "C" __declspec (dllexport) char* __cdecl GetEAX80000002_3_4EAXEBXECXEDXProcessorBrandString()
{
    
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000002, 0);
    unsigned int regs[12]{};
    char processorBrandString[sizeof(regs) + 1];
    regs[0] = cpuInfo[0];
    regs[1] = cpuInfo[1];
    regs[2] = cpuInfo[2];
    regs[3] = cpuInfo[3];

    __cpuidex(cpuInfo, 0x80000003, 0);
    regs[4] = cpuInfo[0];
    regs[5] = cpuInfo[1];
    regs[6] = cpuInfo[2];
    regs[7] = cpuInfo[3];

    __cpuidex(cpuInfo, 0x80000004, 0);
    regs[8] = cpuInfo[0];
    regs[9] = cpuInfo[1];
    regs[10] = cpuInfo[2];
    regs[11] = cpuInfo[3];

    //__cpuidex(cpuInfo, 0x80000000, 0);
    //int pbsFeatureAvailable = cpuInfo[0];

	// TODO: Check if the processor supports the brand string before copying it
    //if (pbsFeatureAvailable >= 0x80000004)
    //{
        memcpy(processorBrandString, regs, sizeof(regs));
        processorBrandString[sizeof(regs)] = '\0';
    //}

    return processorBrandString;
}

#pragma endregion

















#pragma region EAX=0x80000005: L1 Cache and TLB Identifiers

extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000005ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion








#pragma region EAX=0x80000006: Extended L2 Cache Features

extern "C" __declspec(dllexport) int __cdecl GetEAX80000006EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000006EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000006ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000006EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000006ECX_LineSize()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    unsigned int lineSize = cpuInfo[2] & 0xff;

    return lineSize;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000006ECX_Associativity()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    unsigned int associativity = (cpuInfo[2] >> 12) & 0x0f;

    return associativity;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000006ECX_CacheSize()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    unsigned int cacheSize = (cpuInfo[2] >> 16) & 0xffff;

    return cacheSize;
}

#pragma endregion











#pragma region EAX=0x80000007: Processor Power Management Information and RAS Capabilities

extern "C" __declspec(dllexport) int __cdecl GetEAX80000007EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000007, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000007EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000007, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000007ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000007, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000007EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000007, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion















#pragma region EAX=0x80000008: Virtual and Physical Address Sizes

extern "C" __declspec(dllexport) int __cdecl GetEAX80000008EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000008EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000008ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000008EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion
















#pragma region EAX=0x8000000A: SVM features

extern "C" __declspec(dllexport) int __cdecl GetEAX8000000AEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000000A, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8000000AEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000000A, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8000000AECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000000A, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8000000AEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000000A, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion













#pragma region EAX=0x8000001F: Encrypted Memory Capabilities

extern "C" __declspec(dllexport) int __cdecl GetEAX8000001FEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001F, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8000001FEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001F, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8000001FECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001F, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8000001FEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001F, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion















#pragma region EAX=0x80000021: Extended Feature Identification

extern "C" __declspec(dllexport) int __cdecl GetEAX80000021EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000021, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000021EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000021, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000021ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000021, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000021EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000021, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion












#pragma region EAX=0x80000025: Encrypted Memory Capabilities 2

extern "C" __declspec(dllexport) int __cdecl GetEAX80000025EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000025, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000025EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000025, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000025ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000025, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000025EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000025, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion

















#pragma region EAX=0x8C860000: Hygon Extended Feature Flags

extern "C" __declspec(dllexport) int __cdecl GetEAX8C860000EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8C860000, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8C860000EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8C860000, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8C860000ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8C860000, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8C860000EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8C860000, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion













#pragma region EAX=0x8FFFFFFE: AMD Easter Eggs

extern "C" __declspec(dllexport) int __cdecl GetEAX8FFFFFFEEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFE, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8FFFFFFEEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFE, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8FFFFFFEECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFE, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8FFFFFFEEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFE, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion










#pragma region EAX=0x8FFFFFFF: AMD Easter Eggs

extern "C" __declspec(dllexport) int __cdecl GetEAX8FFFFFFFEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFF, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8FFFFFFFEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFF, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8FFFFFFFECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFF, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAX8FFFFFFFEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFF, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion












#pragma region EAX=0xC0000000: Highest Centaur Extended Function

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000000EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000000, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000000EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000000, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000000ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000000, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000000EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000000, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion












#pragma region EAX=0xC0000001: Centaur Feature Information

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000001EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000001, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000001EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000001, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000001ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000001, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000001EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000001, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion









#pragma region EAX=0xC0000002: Centaur Extended CPUID Performance Data

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000002EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000002, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000002EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000002, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000002ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000002, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000002EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000002, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion










#pragma region EAX=0xC0000006, ECX=0: Zhaoxin Feature Information

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000006ECX0EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000006, 0);
    std::bitset<32> eaxBits = std::bitset<32>(cpuInfo[0]);

    return eaxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000006ECX0EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000006, 0);
    std::bitset<32> ebxBits = std::bitset<32>(cpuInfo[1]);

    return ebxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000006ECX0ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000006, 0);
    std::bitset<32> ecxBits = std::bitset<32>(cpuInfo[2]);

    return ecxBits.to_ulong();
}

extern "C" __declspec(dllexport) int __cdecl GetEAXC0000006ECX0EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000006, 0);
    std::bitset<32> edxBits = std::bitset<32>(cpuInfo[3]);

    return edxBits.to_ulong();
}

#pragma endregion















#pragma region
#pragma endregion

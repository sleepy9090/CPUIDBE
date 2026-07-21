/*
    File           cpuidbe.cpp
    Brief          CPUID Backend DLL implementation for Windows
    Copyright      2026 Shawn M. Crawford [sleepy]
    Date           05/29/2026
    Author         Shawn M. Crawford [sleepy]
*/
#include <bitset>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h>
#include <cstring>
#include <sstream>
#include <intrin.h>
#include "pch.h"
#include "cpuidbe.h"
#include <string.h>
#include <vector>
//#include <ios>

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

// Pad a number with zeros to make it 8 characters long, return the padded hex string
/*
string ZeroPadNumber(int num, int zeros) {
    std::stringstream ss;
    // Convert integer to string
    ss << std::hex << num;
    std::string paddedString;
    // Get the string from stringstream
    ss >> paddedString;

    int stringLength = paddedString.length();
    for (int i = 0; i < zeros - stringLength; i++)
    {
        paddedString = "0" + paddedString;
    }
    return paddedString;
}
*/

void IntToBinary32(int num, char* str, bool nullTerminate = true) {
    // Loop through all 32 bits, starting from the Most Significant Bit (MSB)
    for (int i = 31; i >= 0; i--) {
        // Shift the bit to the 1st position and check if it is 1 or 0
        str[31 - i] = ((num >> i) & 1) ? '1' : '0';
    }
    // Append the null terminator to make it a valid C string
    if (nullTerminate) {
        str[32] = '\0';
    }
}

char* Concat(const char* a, const char* b) {
    int lena = strlen(a);
    int lenb = strlen(b);
    char* con = (char*)malloc(lena + lenb + 1);
    // copy & concat (including string termination)
    memcpy(con, a, lena);
    memcpy(con + lena, b, lenb + 1);
    return con;
}

#pragma region EAX=0x0: Highest Function Parameter and Manufacturer ID
extern "C" __declspec(dllexport) const char* __cdecl GetEAX0EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x0, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }

    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX0EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x0, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);
    
    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }

    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX0ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x0, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX0EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x0, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);
    
    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX0EAXHightestFunctionParameter()
{
    // EAX=0: Highest Function Parameter
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x0, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);
    
    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX0EBXEDXECXCpuVendor()
{
    int cpuInfo[4] = {0};

    // Call CPUID with EAX = 0 to get vendor string information
    __cpuid(cpuInfo, 0);

    // The vendor string is stored across EBX, EDX, and ECX in that order
    // EBX (4 bytes) + EDX (4 bytes) + ECX (4 bytes) = 12 bytes
    char vendor[13];
    memcpy(vendor, &cpuInfo[1], 4); // EBX
    memcpy(vendor + 4, &cpuInfo[3], 4); // EDX
    memcpy(vendor + 8, &cpuInfo[2], 4); // ECX
    vendor[12] = '\0'; // Null-terminate the string

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(13);
    if (result) {
        strcpy_s(result, 13, vendor);
    }

    return result;
}

#pragma endregion

#pragma region EAX=0x1: Processor Info and Feature Bits

extern "C" __declspec(dllexport) char* __cdecl GetEAX1EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);
    
    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX1EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);
    
    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX1ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);
    
    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX1EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);
    
    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
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

extern "C" __declspec(dllexport) int __cdecl GetEAX1EAX_CalculatedProcessorModel()
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
/* SSE3 (Prescott New Instructions - PNI) - (SSE3). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX0_SSE3IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sse3Supported = ExtractBits(cpuInfo[2], 0, 1);

    return (bool)sse3Supported;
}

/* PCLMULQDQ (carry-less multiply) instruction - (PCLMULQDQ). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX1_PCLMULQDQIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pclmulqdqSupported = ExtractBits(cpuInfo[2], 1, 1);

    return (bool)pclmulqdqSupported;
}

/* 64-bit debug store (edx bit 21) - (DTES64). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX2_DTES64IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int dtes64Supported = ExtractBits(cpuInfo[2], 2, 1);

    return (bool)dtes64Supported;
}

/* MONITOR and MWAIT instructions (PNI) - (MONITOR). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX3_MONITORIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int monitorSupported = ExtractBits(cpuInfo[2], 3, 1);

    return (bool)monitorSupported;
}

/* CPL qualified debug store - (DS-CPL). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX4_DSCPLIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int dscplSupported = ExtractBits(cpuInfo[2], 4, 1);

    return (bool)dscplSupported;
}

/* Virtual Machine eXtensions - (VMX). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX5_VMXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int vmxSupported = ExtractBits(cpuInfo[2], 5, 1);

    return (bool)vmxSupported;
}

/* Safer Mode Extensions (LaGrande) (GETSEC instruction) - (SMX). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX6_SMXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int smxSupported = ExtractBits(cpuInfo[2], 6, 1);

    return (bool)smxSupported;
}

/* Enhanced SpeedStep Technology - (EST). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX7_ESTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int estSupported = ExtractBits(cpuInfo[2], 7, 1);

    return (bool)estSupported;
}

/* Thermal Monitor 2 - (TM2).*/
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX8_TM2IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int tm2Supported = ExtractBits(cpuInfo[2], 8, 1);

    return (bool)tm2Supported;
}

/* Supplemental SSE3 instructions - (SSSE3). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX9_SSSE3IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int ssse3Supported = ExtractBits(cpuInfo[2], 9, 1);

    return (bool)ssse3Supported;
}

/* L1 Context ID - (CNXT-ID). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX10_CNXTIDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int cnxtidSupported = ExtractBits(cpuInfo[2], 10, 1);

    return (bool)cnxtidSupported;
}

/* Silicon Debug interface - (SDBG). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX11_SDBGIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sdbgSupported = ExtractBits(cpuInfo[2], 11, 1);

    return (bool)sdbgSupported;
}

/* Fused multiply-add (FMA3) - (FMA). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX12_FMAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int fmaSupported = ExtractBits(cpuInfo[2], 12, 1);

    return (bool)fmaSupported;
}

/* CMPXCHG16B instruction - (CMPXCHG16B).*/
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX13_CMPXCHG16BIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int cmpxchg16bSupported = ExtractBits(cpuInfo[2], 13, 1);

    return (bool)cmpxchg16bSupported;
}

/* Can disable sending task priority messages - (xTPR Update Control). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX14_xTPRUpdateControlIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int xtpRUpdateControlSupported = ExtractBits(cpuInfo[2], 14, 1);

    return (bool)xtpRUpdateControlSupported;
}

/* Perfmon & debug capability - (PDCM). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX15_PDCMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pdcmsupported = ExtractBits(cpuInfo[2], 15, 1);

    return (bool)pdcmsupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX16_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 16, 1);

    return (bool)reservedSupported;
}

/* Process context identifiers (CR4 bit 17) - (PCID). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX17_PCIDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pcidSupported = ExtractBits(cpuInfo[2], 17, 1);

    return (bool)pcidSupported;
}

/* Direct cache access for DMA writes - (DCA). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX18_DCAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int dcaSupported = ExtractBits(cpuInfo[2], 18, 1);

    return (bool)dcaSupported;
}

/* SSE4.1 instructions - (SSE4.1). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX19_SSE41IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sse41Supported = ExtractBits(cpuInfo[2], 19, 1);

    return (bool)sse41Supported;
}

/* SSE4.2 instructions - (SSE4.2). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX20_SSE42IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sse42Supported = ExtractBits(cpuInfo[2], 20, 1);

    return (bool)sse42Supported;
}

/* x2APIC (enhanced APIC) - (X2APIC). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX21_X2APICIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int x2apicSupported = ExtractBits(cpuInfo[2], 21, 1);

    return (bool)x2apicSupported;
}

/* MOVBE instruction (big-endian) - (MOVBE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX22_MOVBEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int movbeSupported = ExtractBits(cpuInfo[2], 22, 1);

    return (bool)movbeSupported;
}

/* POPCNT instruction - (POPCNT).*/
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX23_POPCNTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int popcntSupported = ExtractBits(cpuInfo[2], 23, 1);

    return (bool)popcntSupported;
}

/* APIC implements one-shot operation using a TSC deadline value - (TSC-Deadline). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX24_TSCDeadlineIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int tscDeadlineSupported = ExtractBits(cpuInfo[2], 24, 1);

    return (bool)tscDeadlineSupported;
}

/* AES instruction set - (AES-NI). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX25_AESNIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int aesniSupported = ExtractBits(cpuInfo[2], 25, 1);

    return (bool)aesniSupported;
}

/* Extensible processor state save/restore: XSAVE, XRSTOR, XSETBV, XGETBV instructions - (XSAVE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX26_XSAVEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int xsaveSupported = ExtractBits(cpuInfo[2], 26, 1);

    return (bool)xsaveSupported;
}

/* XSAVE enabled by OS - (OSXSAVE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX27_OSXSAVEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int osxsaveSupported = ExtractBits(cpuInfo[2], 27, 1);

    return (bool)osxsaveSupported;
}

/* Advanced Vector Extensions (256-bit SIMD) - (AVX). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX28_AVXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int avxSupported = ExtractBits(cpuInfo[2], 28, 1);

    return (bool)avxSupported;
}

/* Floating-point conversion instructions to/from FP16 format - (F16C). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX29_F16CIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int f16cSupported = ExtractBits(cpuInfo[2], 29, 1);

    return (bool)f16cSupported;
}

/* RDRAND (on-chip random number generator) feature - (RDRAND). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX30_RDRANDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int rdrandSupported = ExtractBits(cpuInfo[2], 30, 1);

    return (bool)rdrandSupported;
}

/* Hypervisor present (always zero on physical CPUs) - (Hypervisor). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1ECX31_HypervisorIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int hypervisorSupported = ExtractBits(cpuInfo[2], 31, 1);

    return (bool)hypervisorSupported;
}

// EDX feature bits
/* Onboard x87 FPU - (FPU). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX0_FPUIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int fpuSupported = ExtractBits(cpuInfo[3], 0, 1);

    return (bool)fpuSupported;
}

/* Virtual 8086 mode extensions (such as VIF, VIP, PVI) - (VME). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX1_VMEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int vmeSupported = ExtractBits(cpuInfo[3], 1, 1);

    return (bool)vmeSupported;
}

/* Debugging extensions (CR4 bit 3) - (DE).*/
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX2_DEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int deSupported = ExtractBits(cpuInfo[3], 2, 1);

    return (bool)deSupported;
}

/* Page Size Extension (4 MB pages) - (PSE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX3_PSEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pseSupported = ExtractBits(cpuInfo[3], 3, 1);

    return (bool)pseSupported;
}

/* Time Stamp Counter and RDTSC instruction - (TSC). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX4_TSCIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int tscSupported = ExtractBits(cpuInfo[3], 4, 1);

    return (bool)tscSupported;
}

/* Model-specific registers and RDMSR/WRMSR instructions  - (MSR). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX5_MSRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int msrSupported = ExtractBits(cpuInfo[3], 5, 1);

    return (bool)msrSupported;
}

/* Physical Address Extension - (PAE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX6_PAEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int paeSupported = ExtractBits(cpuInfo[3], 6, 1);

    return (bool)paeSupported;
}

/* Machine Check Exception - (MCE).*/
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX7_MCEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int mceSupported = ExtractBits(cpuInfo[3], 7, 1);

    return (bool)mceSupported;
}

/* CMPXCHG8B (compare-and-swap) instruction - (CX8). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX8_CX8IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int cx8Supported = ExtractBits(cpuInfo[3], 8, 1);

    return (bool)cx8Supported;
}

/* Onboard Advanced Programmable Interrupt Controller - (APIC). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX9_APICIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int apicSupported = ExtractBits(cpuInfo[3], 9, 1);

    return (bool)apicSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX10_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 10, 1);

    return (bool)reservedSupported;
}

/* SYSENTER and SYSEXIT fast system call instructions  - (SEP). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX11_SEPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sepSupported = ExtractBits(cpuInfo[3], 11, 1);

    return (bool)sepSupported;
}

/* Memory Type Range Registers - (MTRR).*/
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX12_MTRRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int mtrrSupported = ExtractBits(cpuInfo[3], 12, 1);

    return (bool)mtrrSupported;
}

/* Page Global Enable bit in CR4 - (PGE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX13_PGEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pgeSupported = ExtractBits(cpuInfo[3], 13, 1);

    return (bool)pgeSupported;
}

/* Machine Check Architecture - (MCA).*/
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX14_MCAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int mcaSupported = ExtractBits(cpuInfo[3], 14, 1);

    return (bool)mcaSupported;
}

/* Conditional move: CMOV, FCMOV and FCOMI instructions - (CMOV). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX15_CMOVIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int cmovSupported = ExtractBits(cpuInfo[3], 15, 1);

    return (bool)cmovSupported;
}

/* Page Attribute Table - (PAT).*/
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX16_PATIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int patSupported = ExtractBits(cpuInfo[3], 16, 1);

    return (bool)patSupported;
}

/* 36-bit Page Size Extension - (PSE-36). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX17_PSE36IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pse36Supported = ExtractBits(cpuInfo[3], 17, 1);

    return (bool)pse36Supported;
}

/* Processor Serial Number supported and enable - (PSN). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX18_PSNIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int psnSupported = ExtractBits(cpuInfo[3], 18, 1);

    return (bool)psnSupported;
}

/* CLFLUSH cache line flush instruction (SSE2)  - (CLFSH). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX19_CLFSHIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int clflushSupported = ExtractBits(cpuInfo[3], 19, 1);

    return (bool)clflushSupported;
}

/* No-execute (NX) bit (Itanium only, reserved on other CPUs - (NX). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX20_NXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int nxSupported = ExtractBits(cpuInfo[3], 20, 1);

    return (bool)nxSupported;
}

/* Debug store: save trace of executed jumps - (DS). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX21_DSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int dsSupported = ExtractBits(cpuInfo[3], 21, 1);

    return (bool)dsSupported;
}

/* Onboard thermal control MSRs for ACPI - (ACPI). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX22_ACPIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int acpiSupported = ExtractBits(cpuInfo[3], 22, 1);

    return (bool)acpiSupported;
}

/* MMX instructions (64-bit SIMD) - (MMX). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX23_MMXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int mmxSupported = ExtractBits(cpuInfo[3], 23, 1);

    return (bool)mmxSupported;
}

/* FXSAVE, FXRSTOR instructions, CR4 bit 9 - (FXSR). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX24_FXSRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int fxsrSupported = ExtractBits(cpuInfo[3], 24, 1);

    return (bool)fxsrSupported;
}

/* Streaming SIMD Extensions (SSE) / Katmai New Instructions 128-bit SIMD - (SSE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX25_SSEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sseSupported = ExtractBits(cpuInfo[3], 25, 1);

    return (bool)sseSupported;
}

/* SSE2 instructions - (SSE2). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX26_SSE2IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int sse2Supported = ExtractBits(cpuInfo[3], 26, 1);

    return (bool)sse2Supported;
}

/* CPU cache implements self-snoop - (SS). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX27_SSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int ssSupported = ExtractBits(cpuInfo[3], 27, 1);

    return (bool)ssSupported;
}

/* Max APIC IDs reserved field is Valid - (HTT). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX28_HTTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int httSupported = ExtractBits(cpuInfo[3], 28, 1);

    return (bool)httSupported;
}

/* Thermal monitor automatically limits temperature - (TM). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX29_TMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int tmSupported = ExtractBits(cpuInfo[3], 29, 1);

    return (bool)tmSupported;
}

/* IA64 processor emulating x86 - (IA64). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX30_IA64IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int ia64Supported = ExtractBits(cpuInfo[3], 30, 1);

    return (bool)ia64Supported;
}

/* Pending Break Enable (PBE# pin) wakeup capability - (PBE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX1EDX31_PBEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1, 0);

    unsigned int pbeSupported = ExtractBits(cpuInfo[3], 31, 1);

    return (bool)pbeSupported;
}

#pragma endregion

#pragma region EAX=0x2: Cache and TLB Descriptor Information

extern "C" __declspec(dllexport) char* __cdecl GetEAX2EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX2EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX2ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX2EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

/* If the cache and TLB descriptors are invalid (EAX). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EAX31_IsInvalidCacheAndTblDescriptorsEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int isInvalidCacheAndTblDescriptors = ExtractBits(cpuInfo[0], 31, 1);

    return (bool)isInvalidCacheAndTblDescriptors;
}

/* Number of times to query CPUID with 0x2 (should be 1). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EAX0_7_NumberOfTimeToQueryCPUIDWithEAX2()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int timesToQuery = ExtractBits(cpuInfo[0], 0, 8);

    return timesToQuery;
}

/* Cache and TLB Descriptor Information (EAX byte 1). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EAX8_15_CacheAndTLBDescriptorInformation1()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[0], 8, 8);

    return cacheAndTLBDescriptorInformation;
}

/* Cache and TLB Descriptor Information (EAX byte 2). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EAX16_23_CacheAndTLBDescriptorInformation2()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[0], 16, 8);

    return cacheAndTLBDescriptorInformation;
}

/* Cache and TLB Descriptor Information (EAX byte 3). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EAX24_31_CacheAndTLBDescriptorInformation3()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[0], 24, 8);

    return cacheAndTLBDescriptorInformation;
}

/* If the cache and TLB descriptors are invalid (EBX). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EBX31_IsInvalidCacheAndTblDescriptorsEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int isInvalidCacheAndTblDescriptors = ExtractBits(cpuInfo[1], 31, 1);

    return (bool)isInvalidCacheAndTblDescriptors;
}

/* Cache and TLB Descriptor Information (EBX byte 1). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EBX8_15_CacheAndTLBDescriptorInformation1()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[1], 8, 8);

    return cacheAndTLBDescriptorInformation;
}

/* Cache and TLB Descriptor Information (EBX byte 2). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EBX16_23_CacheAndTLBDescriptorInformation2()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[1], 16, 8);

    return cacheAndTLBDescriptorInformation;
}

/* Cache and TLB Descriptor Information (EBX byte 3). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EBX24_31_CacheAndTLBDescriptorInformation3()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[1], 24, 8);

    return cacheAndTLBDescriptorInformation;
}

/* If the cache and TLB descriptors are invalid (ECX). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_ECX31_IsInvalidCacheAndTblDescriptorsECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int isInvalidCacheAndTblDescriptors = ExtractBits(cpuInfo[2], 31, 1);

    return (bool)isInvalidCacheAndTblDescriptors;
}

/* Cache and TLB Descriptor Information (ECX byte 1). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_ECX8_15_CacheAndTLBDescriptorInformation1()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[2], 8, 8);

    return cacheAndTLBDescriptorInformation;
}

/* Cache and TLB Descriptor Information (ECX byte 2). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_ECX16_23_CacheAndTLBDescriptorInformation2()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[2], 16, 8);

    return cacheAndTLBDescriptorInformation;
}

/* Cache and TLB Descriptor Information (ECX byte 3). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_ECX24_31_CacheAndTLBDescriptorInformation3()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[2], 24, 8);

    return cacheAndTLBDescriptorInformation;
}

/* If the cache and TLB descriptors are invalid (EDX). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EDX31_IsInvalidCacheAndTblDescriptorsEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int isInvalidCacheAndTblDescriptors = ExtractBits(cpuInfo[3], 31, 1);

    return (bool)isInvalidCacheAndTblDescriptors;
}

/* Cache and TLB Descriptor Information (EDX byte 1). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EDX8_15_CacheAndTLBDescriptorInformation1()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[3], 8, 8);

    return cacheAndTLBDescriptorInformation;
}

/* Cache and TLB Descriptor Information (EDX byte 2). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EDX16_23_CacheAndTLBDescriptorInformation2()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[3], 16, 8);

    return cacheAndTLBDescriptorInformation;
}

/* Cache and TLB Descriptor Information (EDX byte 3). */
extern "C" __declspec(dllexport) int __cdecl GetEAX2_EDX24_31_CacheAndTLBDescriptorInformation3()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x2, 0);

    unsigned int cacheAndTLBDescriptorInformation = ExtractBits(cpuInfo[3], 24, 8);

    return cacheAndTLBDescriptorInformation;
}

#pragma endregion























#pragma region EAX=0x3: Processor Serial Number

extern "C" __declspec(dllexport) char* __cdecl GetEAX3EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x3, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX3EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x3, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX3ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x3, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX3EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x3, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

/* Pentium 3 CPUs - 96-bit Serial Number. */
extern "C" __declspec(dllexport) char* __cdecl GetEAX3_EAX_EDX_ECX_Pentium3CPU96BitSerialNumber()
{
    int cpuInfo[4] = { 0 };
    __cpuidex(cpuInfo, 0x3, 0);

    char eaxBinaryStr[33];
    IntToBinary32(cpuInfo[0], eaxBinaryStr);

    char edxBinaryStr[33];
    IntToBinary32(cpuInfo[3], edxBinaryStr);
    
    char ecxBinaryStr[33];
    IntToBinary32(cpuInfo[2], ecxBinaryStr);
	
    char* con = Concat(eaxBinaryStr, edxBinaryStr);
    con = Concat(con, ecxBinaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(strlen(con) + 1);
    if (result) {
        strcpy_s(result, strlen(con) + 1, con);
    }

    return result;
}



/* Transmeta Crusoe and Efficeon CPUs - 128-bit Serial Number. */
extern "C" __declspec(dllexport) char* __cdecl GetEAX3_EAX_EDX_ECX_TransmetaCrusoeAndEfficeonCPU128BitSerialNumber()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x3, 0);

    char eaxBinaryStr[33];
    IntToBinary32(cpuInfo[0], eaxBinaryStr);

    char ebxBinaryStr[33];
    IntToBinary32(cpuInfo[1], ebxBinaryStr);

    char ecxBinaryStr[33];
    IntToBinary32(cpuInfo[2], ecxBinaryStr);

    char edxBinaryStr[33];
    IntToBinary32(cpuInfo[3], edxBinaryStr);

    char* con = Concat(eaxBinaryStr, ebxBinaryStr);
    con = Concat(con, ecxBinaryStr);
    con = Concat(con, edxBinaryStr);

    char* result = (char*)malloc(strlen(con) + 1);
    if (result) {
        strcpy_s(result, strlen(con) + 1, con);
    }

    return result;
}

#pragma endregion













#pragma region EAX=0x4 and EAX=0x8000001D: Cache Hierarchy and Topology

// EAX=0x4
extern "C" __declspec(dllexport) char* __cdecl GetEAX4EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX4EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX4ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX4EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x4, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}







//EAX=0x8000001D
extern "C" __declspec(dllexport) char* __cdecl GetEAX8000001DEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001D, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000001DEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001D, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000001DECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001D, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000001DEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001D, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
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

extern "C" __declspec(dllexport) char* __cdecl GetEAXBEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xB, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXBEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xB, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXBECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xB, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXBEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xB, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion












#pragma region EAX=0x5: MONITOR/MWAIT Features

extern "C" __declspec(dllexport) char* __cdecl GetEAX5EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX5EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX5ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX5EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

/* Smallest monitor-line size in bytes. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EAX0_15_SmallestMonitorLineSize()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int smallestMonitorLineSize = ExtractBits(cpuInfo[0], 0, 16);

    return smallestMonitorLineSize;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EAX16_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 16, 16);

    return reserved;
}

/* Largest monitor-line size in bytes. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EBX0_15_LargestMonitorLineSize()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int largestMonitorLineSize = ExtractBits(cpuInfo[1], 0, 16);

    return largestMonitorLineSize;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EBX16_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int reserved = ExtractBits(cpuInfo[1], 16, 16);

    return reserved;
}

/* Enumeration of MONITOR/MWAIT extensions in ECX and EDX supported (EMX). */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_ECX0_EnumOfMonitorMWAITExtensionsInECXAndEDXSupported_EMX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int emx = ExtractBits(cpuInfo[2], 0, 1);

    return emx;
}

/* Supports treating interrupts as break-events for MWAIT even when interrupts are disabled (IBE). */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_ECX1_SupportsTreatingInterruptsAsBreakEventsForMWAITEvenWhenInterruptsAreDisabled_IBE()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int ibe = ExtractBits(cpuInfo[2], 1, 1);

    return ibe;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_ECX2_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int reserved = ExtractBits(cpuInfo[2], 2, 1);

    return reserved;
}

/* Allow MWAIT to be used for power management without setting up memory monitoring with MONITOR (Monitorless_­MWAIT). */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_ECX3_AllowMWAITToBeUsedForPowerManagementWithoutSettingUpMemoryMonitoringWithMONITOR_Monitorless_MWAIT()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int monitorlessMWAIT = ExtractBits(cpuInfo[2], 3, 1);

    return monitorlessMWAIT;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_ECX4_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int reserved = ExtractBits(cpuInfo[2], 4, 28);

    return reserved;
}

/* Number of C0 sub-states supported for MWAIT. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EDX0_3_NumberOfC0SubStatesSupportedForMWAIT()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int numberOfC0SubStates = ExtractBits(cpuInfo[3], 0, 4);

    return numberOfC0SubStates;
}

/* Number of C1 sub-states supported for MWAIT. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EDX4_7_NumberOfC1SubStatesSupportedForMWAIT()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int numberOfC1SubStates = ExtractBits(cpuInfo[3], 4, 4);

    return numberOfC1SubStates;
}

/* Number of C2 sub-states supported for MWAIT. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EDX8_11_NumberOfC2SubStatesSupportedForMWAIT()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int numberOfC2SubStates = ExtractBits(cpuInfo[3], 8, 4);

    return numberOfC2SubStates;
}

/* Number of C3 sub-states supported for MWAIT. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EDX12_15_NumberOfC3SubStatesSupportedForMWAIT()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int numberOfC3SubStates = ExtractBits(cpuInfo[3], 12, 4);

    return numberOfC3SubStates;
}

/* Number of C4 sub-states supported for MWAIT. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EDX16_19_NumberOfC4SubStatesSupportedForMWAIT()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int numberOfC4SubStates = ExtractBits(cpuInfo[3], 16, 4);

    return numberOfC4SubStates;
}

/* Number of C5 sub-states supported for MWAIT. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EDX20_23_NumberOfC5SubStatesSupportedForMWAIT()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int numberOfC5SubStates = ExtractBits(cpuInfo[3], 20, 4);

    return numberOfC5SubStates;
}

/* Number of C6 sub-states supported for MWAIT. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EDX24_27_NumberOfC6SubStatesSupportedForMWAIT()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int numberOfC6SubStates = ExtractBits(cpuInfo[3], 24, 4);

    return numberOfC6SubStates;
}

/* Number of C7 sub-states supported for MWAIT. */
extern "C" __declspec(dllexport) int __cdecl GetEAX5_EDX28_31_NumberOfC7SubStatesSupportedForMWAIT()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x5, 0);

    unsigned int numberOfC7SubStates = ExtractBits(cpuInfo[3], 28, 4);

    return numberOfC7SubStates;
}

#pragma endregion

#pragma region EAX=0x6: Thermal and Power Management

extern "C" __declspec(dllexport) char* __cdecl GetEAX6EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX6EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX6ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX6EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

/* [Thermal/power management feature bits in EAX]. */

/* Digital Thermal Sensor capability - (DTS). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX0_DTSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int dtsSupported = ExtractBits(cpuInfo[0], 0, 1);

    return (bool)dtsSupported;
}

/* Intel Turbo Boost Technology capability - (TURBO_BOOST). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX1_TURBO_BOOSTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int turboBoostSupported = ExtractBits(cpuInfo[0], 1, 1);

    return (bool)turboBoostSupported;
}

/* Always Running APIC Timer capability  - (ARAT). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX2_ARATIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int aratSupported = ExtractBits(cpuInfo[0], 2, 1);

    return (bool)aratSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX3_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 3, 1);

    return (bool)reserved;
}

/* Power Limit Notification capability - (PLN). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX4_PowerLimitNotificationCapability_PLNIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int plnSupported = ExtractBits(cpuInfo[0], 4, 1);

    return (bool)plnSupported;
}

/* Extended Clock Modulation Duty capability - (ECMD). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX5_ExtendedClockModulationDutyCapability_ECMDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int ecmdSupported = ExtractBits(cpuInfo[0], 5, 1);

    return (bool)ecmdSupported;
}

/* Package Thermal Management capability - (PTM). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX6_PackageThermalManagementCapability_PTMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int ptmSupported = ExtractBits(cpuInfo[0], 6, 1);

    return (bool)ptmSupported;
}

/* Hardware-controlled Performance States. MSRs added: IA32_PM_ENABLE(770h), IA32_HWP_CAPABILITIES(771h), IA32_HWP_REQUEST(774h), IA32_HWP_STATUS(777h) - (HWP). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX7_HardwareControlledPerformanceStatesCapability_HWPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwpSupported = ExtractBits(cpuInfo[0], 7, 1);

    return (bool)hwpSupported;
}

/* HWP notification of dynamic guaranteed performance change - IA32_HWP_INTERRUPT(773h) MSR - (HWP_Notification). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX8_HWPNotificationCapability_HWP_NotificationIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwpNotificationSupported = ExtractBits(cpuInfo[0], 8, 1);

    return (bool)hwpNotificationSupported;
}

/* HWP Activity Window control - bits 41:32 of IA32_HWP_REQUEST MSR - (HWP_Activity_Window). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX9_HWPActivityWindowCapability_HWP_Activity_WindowIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwpActivityWindowSupported = ExtractBits(cpuInfo[0], 9, 1);

    return (bool)hwpActivityWindowSupported;
}

/* HWP Energy/performance preference control - bits 31:24 of IA32_HWP_REQUEST MSR - (HWP_Energy_Performance_Preference). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX10_HWPEnergyPerformancePreferenceCapability_HWP_Energy_Performance_PreferenceIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwpEnergyPerformancePreferenceSupported = ExtractBits(cpuInfo[0], 10, 1);

    return (bool)hwpEnergyPerformancePreferenceSupported;
}

/* HWP Package-level control - IA32_HWP_REQUEST_PKG(772h) MSR - (HWP_Package_Level_Request). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX11_HWPPackageLevelRequestCapability_HWP_Package_Level_RequestIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwpPackageLevelRequestSupported = ExtractBits(cpuInfo[0], 11, 1);

    return (bool)hwpPackageLevelRequestSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX12_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 12, 1);

    return (bool)reserved;
}

/* Hardware Duty Cycling supported. MSRs added: IA32_PKG_HDC_CTL(DB0h), IA32_PM_CTL1(DB1h), IA32_THREAD_STALL(DB2h) - (HDC). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX13_HardwareDutyCyclingCapability_HDCIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hdcSupported = ExtractBits(cpuInfo[0], 13, 1);

    return (bool)hdcSupported;
}

/* Intel Turbo Boost Max Technology 3.0 available - (TURBO_BOOST_MAX). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX14_IntelTurboBoostMaxTechnology30Availability_TURBO_BOOST_MAXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int turboBoostMaxSupported = ExtractBits(cpuInfo[0], 14, 1);

    return (bool)turboBoostMaxSupported;
}

/* Interrupts upon changes to IA32_HWP_CAPABILITIES.Highest_Performance (bits 7:0) supported - (HWP_CAP). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX15_HWP_CAPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwpCapSupported = ExtractBits(cpuInfo[0], 15, 1);

    return (bool)hwpCapSupported;
}

/* HWP PECI override supported - bits 63:60 of IA32_HWP_PECI_REQUEST_INFO(775h) MSR - (HWP_PECI_OVERRIDE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX16_HWP_PECI_OVERRIDEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwpPeciOverrideSupported = ExtractBits(cpuInfo[0], 16, 1);

    return (bool)hwpPeciOverrideSupported;
}

/* Flexible HWP - bits 63:59 of IA32_HWP_REQUEST MSR - (FLEXIBLE_HWP). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX17_FlexibleHWPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int flexibleHwpSupported = ExtractBits(cpuInfo[0], 17, 1);

    return (bool)flexibleHwpSupported;
}

/* Fast access mode for IA32_HWP_REQUEST MSR supported - (HWP_REQUEST_FAST_ACCESS). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX18_HWP_REQUEST_FAST_ACCESSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwpRequestFastAccessSupported = ExtractBits(cpuInfo[0], 18, 1);

    return (bool)hwpRequestFastAccessSupported;
}

/* Hardware Feedback Interface. Added MSRs: IA32_HW_FEEDBACK_PTR(17D0h), IA32_HW_FEEDBACK_CONFIG(17D1h) (bit 0 enables HFI, bit 1 enables Intel Thread Director) - (HW_FEEDBACK). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX19_HW_FEEDBACKIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwFeedbackSupported = ExtractBits(cpuInfo[0], 19, 1);

    return (bool)hwFeedbackSupported;
}

/* IA32_HWP_REQUEST of idle logical processor ignored when only one of two logical processors that share a physical processor is active. - (HWP_REQUEST_IGNORE_IDLE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX20_HWP_REQUEST_IGNORE_IDLEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwpRequestIgnoreIdleSupported = ExtractBits(cpuInfo[0], 20, 1);

    return (bool)hwpRequestIgnoreIdleSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX21_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 21, 1);

    return (bool)reserved;
}

/* IA32_HWP_CTL(776h) MSR supported - (HWP Control MSR). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX22_HWP_CTLIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hwpCtlSupported = ExtractBits(cpuInfo[0], 22, 1);

    return (bool)hwpCtlSupported;
}

/* Intel Thread Director supported. Added MSRs: IA32_THREAD_FEEDBACK_CHAR(17D2h), IA32_HW_FEEDBACK_THREAD_CONFIG(17D4h) - (THREAD_DIRECTOR). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX23_THREAD_DIRECTORIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int threadDirectorSupported = ExtractBits(cpuInfo[0], 23, 1);

    return (bool)threadDirectorSupported;
}

/* (IA32_THERM_INTERRUPT MSR bit 25 supported). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX24_IA32_THERM_INTERRUPTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int ia32ThermInterruptSupported = ExtractBits(cpuInfo[0], 24, 1);

    return (bool)ia32ThermInterruptSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX25_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 25, 1);

    return (bool)reserved;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX26_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 26, 1);

    return (bool)reserved;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX27_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 27, 1);

    return (bool)reserved;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX28_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 28, 1);

    return (bool)reserved;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX29_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 29, 1);

    return (bool)reserved;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX30_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 30, 1);

    return (bool)reserved;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EAX31_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 31, 1);

    return (bool)reserved;
}

/* Thermal / power management feature fields in EBX, ECX and EDX. */
/* Number of Interrupt Thresholds in Digital Thermal Sensor: EBX Bits 3:0. */
extern "C" __declspec(dllexport) int __cdecl GetEAX6_EBX0_3_NumberOfInterruptThresholdsInDigitalThermalSensor()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int numberOfInterruptThresholdsInDigitalThermalSensor = ExtractBits(cpuInfo[1], 28, 4);

    return numberOfInterruptThresholdsInDigitalThermalSensor;
}

/* Reserved: EBX Bits 31:4. */
extern "C" __declspec(dllexport) int __cdecl GetEAX6_EBX4_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[1], 4, 28);

    return reserved;
}

/* Effective frequency interface supported - IA32_MPERF(0E7h) and IA32_APERF(0E8h) MSRs. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6ECX0_EffectiveFrequencyInterfaceIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int effectiveFrequencyInterfaceSupported = ExtractBits(cpuInfo[2], 0, 1);

    return (bool)effectiveFrequencyInterfaceSupported;
}

/* ACNT2 Capability supported. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6ECX1_ACNT2CapabilityIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int acnt2CapabilitySupported = ExtractBits(cpuInfo[2], 1, 1);

    return (bool)acnt2CapabilitySupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6ECX2_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[2], 2, 1);

    return (bool)reserved;
}

/* Performance-Energy Bias capability - IA32_ENERGY_PERF_BIAS(1B0h) MSR. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6ECX3_PerformanceEnergyBiasCapabilityMSRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int performanceEnergyBiasCapabilityMSRSupported = ExtractBits(cpuInfo[2], 3, 1);

    return (bool)performanceEnergyBiasCapabilityMSRSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX6ECX4_7_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[2], 4, 4);

    return reserved;
}

/* Number of Intel Thread Director classes supported by hardware. */
extern "C" __declspec(dllexport) int __cdecl GetEAX6ECX8_15_NumberOfIntelThreadDirectorClasses()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int numberOfIntelThreadDirectorClasses = ExtractBits(cpuInfo[2], 8, 8);

    return numberOfIntelThreadDirectorClasses;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX6ECX16_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[2], 16, 16);

    return reserved;
}

/* Hardware Feedback reporting: Performance Capability Reporting supported. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EDX0_HardwareFeedbackReportingPerformanceCapabilityReportingIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hardwareFeedbackReportingPerformanceCapabilityReportingSupported = ExtractBits(cpuInfo[3], 0, 1);

    return (bool)hardwareFeedbackReportingPerformanceCapabilityReportingSupported;
}

/* Hardware Feedback reporting: Efficiency Capability Reporting supported. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EDX1_HardwareFeedbackReportingEfficiencyCapabilityReportingIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int hardwareFeedbackReportingEfficiencyCapabilityReportingSupported = ExtractBits(cpuInfo[3], 1, 1);

    return (bool)hardwareFeedbackReportingEfficiencyCapabilityReportingSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EDX2_7_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[3], 2, 6);

    return (bool)reserved;
}

/* Size of Hardware Feedback interface structure (in units of 4 KiB) minus 1. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EDX8_11_SizeOfHardwareFeedbackInterfaceStructure()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int sizeOfHardwareFeedbackInterfaceStructure = ExtractBits(cpuInfo[3], 8, 4);

    return (bool)sizeOfHardwareFeedbackInterfaceStructure;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EDX12_15_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int reserved = ExtractBits(cpuInfo[3], 12, 4);

    return (bool)reserved;
}

/* Index of this logical processor's row in hardware feedback interface structure. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX6EDX16_31_IndexOfThisLogicalProcessorsRowInHardwareFeedbackInterfaceStructure()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x6, 0);

    unsigned int indexOfThisLogicalProcessorsRowInHardwareFeedbackInterfaceStructure = ExtractBits(cpuInfo[3], 16, 16);

    return (bool)indexOfThisLogicalProcessorsRowInHardwareFeedbackInterfaceStructure;
}

#pragma endregion
















#pragma region EAX=0x7, ECX=0x0: Extended Features

/* Returns the maximum ECX value for EAX=7 in EAX. */
extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX0EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX0EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX0ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX0EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

/* EAX=7, ECX=0: Extended Features. */
/* EBX. */
/* Access to base of %fs and %gs - (fsgsbase). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX0_FSGSBaseIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int fsgsbaseSupported = ExtractBits(cpuInfo[1], 0, 1);

    return (bool)fsgsbaseSupported;
}

/* IA32_TSC_ADJUST MSR - (tsc_adjust). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX1_TSCAdjustIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int tscAdjustSupported = ExtractBits(cpuInfo[1], 1, 1);

    return (bool)tscAdjustSupported;
}

/* Software Guard Extensions - (sgx). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX2_SGXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int sgxSupported = ExtractBits(cpuInfo[1], 2, 1);

    return (bool)sgxSupported;
}

/* Bit Manipulation Instruction Set 1 - (bmi1). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX3_BMI1IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int bmi1Supported = ExtractBits(cpuInfo[1], 3, 1);

    return (bool)bmi1Supported;
}

/* TSX Hardware Lock Elision - (hle). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX4_HLEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int hleSupported = ExtractBits(cpuInfo[1], 4, 1);

    return (bool)hleSupported;
}

/* Advanced Vector Extensions 2 - (avx2). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX5_AVX2IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx2Supported = ExtractBits(cpuInfo[1], 5, 1);

    return (bool)avx2Supported;
}

/* x87 FPU data pointer register updated on exceptions only - (fdp-excptn-only). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX6_FDPExcptnOnlyIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int fdpExcptnOnlySupported = ExtractBits(cpuInfo[1], 6, 1);

    return (bool)fdpExcptnOnlySupported;
}

/* Supervisor Mode Execution Prevention - (smep). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX7_SMEPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int smepSupported = ExtractBits(cpuInfo[1], 7, 1);

    return (bool)smepSupported;
}

/* Bit Manipulation Instruction Set 2 - (bmi2). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX8_BMI2IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int bmi2Supported = ExtractBits(cpuInfo[1], 8, 1);

    return (bool)bmi2Supported;
}

/* Enhanced REP MOVSB/STOSB - (erms). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX9_ERMSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int ermsSupported = ExtractBits(cpuInfo[1], 9, 1);

    return (bool)ermsSupported;
}

/* INVPCID instruction - (invpcid). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX10_INVPCIDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int invpcidSupported = ExtractBits(cpuInfo[1], 10, 1);

    return (bool)invpcidSupported;
}

/* TSX Restricted Transactional Memory - (rtm). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX11_RTMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int rtmSupported = ExtractBits(cpuInfo[1], 11, 1);

    return (bool)rtmSupported;
}

/* Intel Resource Director (RDT) Monitoring or AMD Platform QOS Monitoring - (rdt-m/pqm). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX12_RDTMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int rdtmSupported = ExtractBits(cpuInfo[1], 12, 1);

    return (bool)rdtmSupported;
}

/* x87 FPU CS and DS deprecated - (fcs_fds_­deprecation). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX13_FCSFDSDeprecationIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int fcs_fds_deprecationSupported = ExtractBits(cpuInfo[1], 13, 1);

    return (bool)fcs_fds_deprecationSupported;
}

/* Intel MPX (Memory Protection Extensions) - (mpx). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX14_MPXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int mpxSupported = ExtractBits(cpuInfo[1], 14, 1);

    return (bool)mpxSupported;
}

/* Intel Resource Director (RDT) Allocation or AMD Platform QOS Enforcement - (rdt-a/pqe). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX15_RDTAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int rdtASupported = ExtractBits(cpuInfo[1], 15, 1);

    return (bool)rdtASupported;
}

/* AVX-512 Foundation - (avx512-f). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX16_AVX512FIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512fSupported = ExtractBits(cpuInfo[1], 16, 1);

    return (bool)avx512fSupported;
}

/* AVX-512 Doubleword and Quadword Instructions - (avx512-dq). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX17_AVX512DQIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512dqSupported = ExtractBits(cpuInfo[1], 17, 1);

    return (bool)avx512dqSupported;
}

/* RDSEED instruction - (rdseed). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX18_RDSEEDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int rdseedSupported = ExtractBits(cpuInfo[1], 18, 1);

    return (bool)rdseedSupported;
}

/* Intel ADX (Multi-Precision Add-Carry Instruction Extensions) - (adx). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX19_ADXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int adxSupported = ExtractBits(cpuInfo[1], 19, 1);

    return (bool)adxSupported;
}

/* Supervisor Mode Access Prevention - (smap). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX20_SMAPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int smapSupported = ExtractBits(cpuInfo[1], 20, 1);

    return (bool)smapSupported;
}

/* AVX-512 Integer Fused Multiply-Add Instructions - (avx512-ifma). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX21_AVX512IFMAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512ifmaSupported = ExtractBits(cpuInfo[1], 21, 1);

    return (bool)avx512ifmaSupported;
}

/* (PCOMMIT instruction, deprecated) - (pcommit). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX22_PCOMMITIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int pcommitSupported = ExtractBits(cpuInfo[1], 22, 1);

    return (bool)pcommitSupported;
}

/* CLFLUSHOPT instruction - (clflushopt). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX23_CLFLUSHOPTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int clflushoptSupported = ExtractBits(cpuInfo[1], 23, 1);

    return (bool)clflushoptSupported;
}

/* CLWB (Cache line writeback) instruction - (clwb). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX24_CLWBIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int clwbSupported = ExtractBits(cpuInfo[1], 24, 1);

    return (bool)clwbSupported;
}

/* Intel Processor Trace - (pt). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX25_PTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int ptSupported = ExtractBits(cpuInfo[1], 25, 1);

    return (bool)ptSupported;
}

/* AVX-512 Prefetch Instructions - (avx512-pf). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX26_AVX512PFIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512pfSupported = ExtractBits(cpuInfo[1], 26, 1);

    return (bool)avx512pfSupported;
}

/* AVX-512 Exponential and Reciprocal Instructions - (avx512-er). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX27_AVX512ERIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512erSupported = ExtractBits(cpuInfo[1], 27, 1);

    return (bool)avx512erSupported;
}

/* AVX-512 Conflict Detection Instructions - (avx512-cd). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX28_AVX512CDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512cdSupported = ExtractBits(cpuInfo[1], 28, 1);

    return (bool)avx512cdSupported;
}

/* SHA-1 and SHA-256 extensions - (sha). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX29_SHAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int shaSupported = ExtractBits(cpuInfo[1], 29, 1);

    return (bool)shaSupported;
}

/* AVX-512 Byte and Word Instructions - (avx512-bw). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX30_AVX512BWIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512bwSupported = ExtractBits(cpuInfo[1], 30, 1);

    return (bool)avx512bwSupported;
}

/* AVX-512 Vector Length Extensions - (avx512-vl). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EBX31_AVX512VLIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512vlSupported = ExtractBits(cpuInfo[1], 31, 1);

    return (bool)avx512vlSupported;
}

/* ECX. */
/* PREFETCHWT1 instruction - (prefetchwt1). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX0_PREFETCHWT1IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int prefetchwt1Supported = ExtractBits(cpuInfo[2], 0, 1);

    return (bool)prefetchwt1Supported;
}

/* AVX-512 Vector Bit Manipulation Instructions - (avx512-vbmi). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX1_AVX512VBMIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512vbmiSupported = ExtractBits(cpuInfo[2], 1, 1);

    return (bool)avx512vbmiSupported;
}

/* User-mode Instruction Prevention - (umip). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX2_UMIPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int umipSupported = ExtractBits(cpuInfo[2], 2, 1);

    return (bool)umipSupported;
}

/* Memory Protection Keys for User-mode pages - (pku). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX3_PKUIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int pkuSupported = ExtractBits(cpuInfo[2], 3, 1);

    return (bool)pkuSupported;
}

/* PKU enabled by OS - (ospke). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX4_OSPKEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int ospkeSupported = ExtractBits(cpuInfo[2], 4, 1);

    return (bool)ospkeSupported;
}

/* Timed pause and user-level monitor/wait instructions (TPAUSE, UMONITOR, UMWAIT) - (waitpkg). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX5_WAITPKGIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int waitpkgSupported = ExtractBits(cpuInfo[2], 5, 1);

    return (bool)waitpkgSupported;
}

/* AVX-512 Vector Bit Manipulation Instructions 2 - (avx512-vbmi2). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX6_AVX512VBMI2IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512vbmi2Supported = ExtractBits(cpuInfo[2], 6, 1);

    return (bool)avx512vbmi2Supported;
}

/* Control flow enforcement (CET): shadow stack (SHSTK alternative name) - (cet_ss/shstk). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX7_CETSSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int cetssSupported = ExtractBits(cpuInfo[2], 7, 1);

    return (bool)cetssSupported;
}

/* Galois Field instructions - (gfni). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX8_GFNIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int gfniSupported = ExtractBits(cpuInfo[2], 8, 1);

    return (bool)gfniSupported;
}

/* Vector AES instruction set (VEX-256/EVEX) - (vaes). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX9_VAESIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int vaesSupported = ExtractBits(cpuInfo[2], 9, 1);

    return (bool)vaesSupported;
}

/* CLMUL instruction set (VEX-256/EVEX) - (vpclmulqdq). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX10_VPCLMULQDQIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int vpclmulqdqSupported = ExtractBits(cpuInfo[2], 10, 1);

    return (bool)vpclmulqdqSupported;
}

/* AVX-512 Vector Neural Network Instructions - (avx512-vnni). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX11_AVX512VNNIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512vnniSupported = ExtractBits(cpuInfo[2], 11, 1);

    return (bool)avx512vnniSupported;
}

/* AVX-512 BITALG instructions - (avx512-bitalg). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX12_AVX512BITALGIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512bitalgSupported = ExtractBits(cpuInfo[2], 12, 1);

    return (bool)avx512bitalgSupported;
}

/* Total Memory Encryption MSRs available - (tme_en). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX13_TME_ENIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int tme_enSupported = ExtractBits(cpuInfo[2], 13, 1);

    return (bool)tme_enSupported;
}

/* AVX-512 Vector Population Count Double and Quad-word - (avx512-vpopcntdq). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX14_AVX512VPOPCNTDQIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512vpopcntdqSupported = ExtractBits(cpuInfo[2], 14, 1);

    return (bool)avx512vpopcntdqSupported;
}

/* ? - (fzm). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX15_FZMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int fzmSupported = ExtractBits(cpuInfo[2], 15, 1);

    return (bool)fzmSupported;
}

/* 5-level paging (57 address bits) - (la57). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX16_LA57IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int la57Supported = ExtractBits(cpuInfo[2], 16, 1);

    return (bool)la57Supported;
}

/* The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX17_MAWAUIsSupported1()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int mawauSupported = ExtractBits(cpuInfo[2], 17, 1);

    return (bool)mawauSupported;
}

/* The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX18_MAWAUIsSupported2()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int mawauSupported = ExtractBits(cpuInfo[2], 18, 1);

    return (bool)mawauSupported;
}

/* The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX19_MAWAUIsSupported3()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int mawauSupported = ExtractBits(cpuInfo[2], 19, 1);

    return (bool)mawauSupported;
}

/* The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX20_MAWAUIsSupported4()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int mawauSupported = ExtractBits(cpuInfo[2], 20, 1);

    return (bool)mawauSupported;
}

/* The value of userspace MPX Address-Width Adjust used by the BNDLDX and BNDSTX Intel MPX instructions in 64-bit mode - (mawau). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX21_MAWAUIsSupported5()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int mawauSupported = ExtractBits(cpuInfo[2], 21, 1);

    return (bool)mawauSupported;
}

/* RDPID (Read Processor ID) instruction and IA32_TSC_AUX MSR - (rdpid). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX22_RDPIDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int rdpidSupported = ExtractBits(cpuInfo[2], 22, 1);

    return (bool)rdpidSupported;
}

/* AES Key Locker - (kl). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX23_KLIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int klSupported = ExtractBits(cpuInfo[2], 23, 1);

    return (bool)klSupported;
}

/* Bus lock debug exceptions - (bus-lock-detect). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX24_BusLockDetectIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int busLockDetectSupported = ExtractBits(cpuInfo[2], 24, 1);

    return (bool)busLockDetectSupported;
}

/* CLDEMOTE (Cache line demote) instruction - (cldemote). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX25_CLDEMOTEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int cldemoteSupported = ExtractBits(cpuInfo[2], 25, 1);

    return (bool)cldemoteSupported;
}

/* ? - (mprr). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX26_MPRRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int mprSupported = ExtractBits(cpuInfo[2], 26, 1);

    return (bool)mprSupported;
}

/* MOVDIRI instruction - (movdiri). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX27_MOVDIRIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int movdiriSupported = ExtractBits(cpuInfo[2], 27, 1);

    return (bool)movdiriSupported;
}

/* MOVDIR64B (64-byte direct store) instruction - (movdir64b). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX28_MOVDIR64BIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int movdir64bSupported = ExtractBits(cpuInfo[2], 28, 1);

    return (bool)movdir64bSupported;
}

/* Enqueue Stores and EMQCMD/EMQCMDS instructions - (enqcmd). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX29_ENQCMDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int enqcmdSupported = ExtractBits(cpuInfo[2], 29, 1);

    return (bool)enqcmdSupported;
}

/* SGX Launch Configuration - (sgx-lc). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX30_SGXLcIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int sgxlcSupported = ExtractBits(cpuInfo[2], 30, 1);

    return (bool)sgxlcSupported;
}

/* Protection keys for supervisor-mode pages - (pks). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_ECX31_PKSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int pksSupported = ExtractBits(cpuInfo[2], 31, 1);

    return (bool)pksSupported;
}

/* EDX. */
/* ? - (sgx-tem). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX0_SGXTEMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int sgxtemSupported = ExtractBits(cpuInfo[3], 0, 1);

    return (bool)sgxtemSupported;
}

/* Attestation Services for Intel SGX - (sgx-keys). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX1_SGXKEYIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int sgxkeysSupported = ExtractBits(cpuInfo[3], 1, 1);

    return (bool)sgxkeysSupported;
}

/* AVX-512 4-register Neural Network Instructions - (avx512-4vnniw). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX2_AVX5124VNNIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx5124vnniSupported = ExtractBits(cpuInfo[3], 2, 1);

    return (bool)avx5124vnniSupported;
}

/* AVX-512 4-register Multiply Accumulation Single precision - (avx512-4fmaps). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX3_AVX5124FMAPSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx5124fmapsSupported = ExtractBits(cpuInfo[3], 3, 1);

    return (bool)avx5124fmapsSupported;
}

/* Fast Short REP MOVSB - (fsrm). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX4_FSRMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int fsrmSupported = ExtractBits(cpuInfo[3], 4, 1);

    return (bool)fsrmSupported;
}

/* User Inter-processor Interrupts - (uintr). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX5_UINTRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int uintrSupported = ExtractBits(cpuInfo[3], 5, 1);

    return (bool)uintrSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX6_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 6, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX7_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 7, 1);

    return (bool)reservedSupported;
}

/* AVX-512 vector intersection instructions on 32/64-bit integers - (avx512-vp2intersect). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX8_AVX512VP2INTERSECTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512vp2intersectSupported = ExtractBits(cpuInfo[3], 8, 1);

    return (bool)avx512vp2intersectSupported;
}

/* Special Register Buffer Data Sampling Mitigations - (srbds-ctrl). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX9_SRBDSCtrlIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int srbdsCtrlSupported = ExtractBits(cpuInfo[3], 9, 1);

    return (bool)srbdsCtrlSupported;
}

/* VERW instruction clears CPU buffers - (md-clear). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX10_MDClearIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int mdClearSupported = ExtractBits(cpuInfo[3], 10, 1);

    return (bool)mdClearSupported;
}

/* All TSX transactions are aborted - (rtm-always-abort). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX11_RTMAlwaysAbortIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int rtmAlwaysAbortSupported = ExtractBits(cpuInfo[3], 11, 1);

    return (bool)rtmAlwaysAbortSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX12_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 12, 1);

    return (bool)reservedSupported;
}

/* TSX_FORCE_ABORT (MSR 0x10f) is available - (rtm-force-abort). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX13_RTMForceAbortIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int rtmForceAbortSupported = ExtractBits(cpuInfo[3], 13, 1);

    return (bool)rtmForceAbortSupported;
}

/* SERIALIZE instruction - (serialize). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX14_SERIALIZEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int serializeSupported = ExtractBits(cpuInfo[3], 14, 1);

    return (bool)serializeSupported;
}

/* Mixture of CPU types in processor topology (e.g. Alder Lake) - (hybrid). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX15_HYBRIDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int hybridSupported = ExtractBits(cpuInfo[3], 15, 1);

    return (bool)hybridSupported;
}

/* TSX load address tracking suspend/resume instructions (TSUSLDTRK and TRESLDTRK) - (tsxldtrk). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX16_TSXLDTRKIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int tsxldtrkSupported = ExtractBits(cpuInfo[3], 16, 1);

    return (bool)tsxldtrkSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX17_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 17, 1);

    return (bool)reservedSupported;
}

/* Platform configuration (Memory Encryption Technologies Instructions) - (pconfig). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX18_PCONFIGIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int pconfigSupported = ExtractBits(cpuInfo[3], 18, 1);

    return (bool)pconfigSupported;
}

/* Architectural Last Branch Records - (lbr). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX19_LBRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int lbrSupported = ExtractBits(cpuInfo[3], 19, 1);

    return (bool)lbrSupported;
}

/* Control flow enforcement (CET): indirect branch tracking - (cet-ibt). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX20_CETIBTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int cetIbtSupported = ExtractBits(cpuInfo[3], 20, 1);

    return (bool)cetIbtSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX21_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 21, 1);

    return (bool)reservedSupported;
}

/* AMX tile computation on bfloat16 numbers - (amx-bf16). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX22_AMXBF16IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int amxBf16Supported = ExtractBits(cpuInfo[3], 22, 1);

    return (bool)amxBf16Supported;
}

/* AVX-512 half-precision floating-point arithmetic instructions - (avx512-fp16). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX23_AVX512FP16IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int avx512fp16Supported = ExtractBits(cpuInfo[3], 23, 1);

    return (bool)avx512fp16Supported;
}

/* AMX tile load/store instructions - (amx-tile). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX24_AMXTILEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int amxTileSupported = ExtractBits(cpuInfo[3], 24, 1);

    return (bool)amxTileSupported;
}

/* AMX tile computation on 8-bit integers - (amx-int8). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX25_AMXINT8IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int amxInt8Supported = ExtractBits(cpuInfo[3], 25, 1);

    return (bool)amxInt8Supported;
}

/* Speculation Control, part of Indirect Branch Control (IBC): Indirect Branch Restricted Speculation (IBRS) and Indirect Branch Prediction Barrier (IBPB) - (ibrs / spec_ctrl). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX26_SPEC_CTRLIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int specCtrlSupported = ExtractBits(cpuInfo[3], 26, 1);

    return (bool)specCtrlSupported;
}

/* Single Thread Indirect Branch Predictor, part of IBC - (stibp). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX27_STIBPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int stibpSupported = ExtractBits(cpuInfo[3], 27, 1);

    return (bool)stibpSupported;
}

/* IA32_FLUSH_CMD MSR - L1D_FLUSH. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX28_L1D_FLUSHIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int l1dFlushSupported = ExtractBits(cpuInfo[3], 28, 1);

    return (bool)l1dFlushSupported;
}

/* IA32_ARCH_CAPABILITIES MSR (lists speculative side channel mitigations) - (arch_­capabilities). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX29_ARCH_CAPABILITIESIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int archCapabilitiesSupported = ExtractBits(cpuInfo[3], 29, 1);

    return (bool)archCapabilitiesSupported;
}

/* IA32_CORE_CAPABILITIES MSR (lists model-specific core capabilities) - (core_­capabilities). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX30_CORE_CAPABILITIESIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int coreCapabilitiesSupported = ExtractBits(cpuInfo[3], 30, 1);

    return (bool)coreCapabilitiesSupported;
}

/* Speculative Store Bypass Disable, as mitigation for Speculative Store Bypass (IA32_SPEC_CTRL) - (ssbd). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX0_EDX31_SSBDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 0);

    unsigned int ssbdSupported = ExtractBits(cpuInfo[3], 31, 1);

    return (bool)ssbdSupported;
}

/* EAX=0x7, ECX=0x1: Extended Features. */
extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX1EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX1EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX1ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX1EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

/* EAX. */
/* SHA-512 extensions - (sha512). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX0_SHA512IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int sha512Supported = ExtractBits(cpuInfo[0], 0, 1);

    return (bool)sha512Supported;
}

/* SM3 hash extensions - (sm3). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX1_SM3IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int sm3Supported = ExtractBits(cpuInfo[0], 1, 1);

    return (bool)sm3Supported;
}

/* SM4 cipher extensions - (sm4). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX2_SM4IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int sm4Supported = ExtractBits(cpuInfo[0], 2, 1);

    return (bool)sm4Supported;
}

/* Remote Atomic Operations on integers: AADD, AAND, AOR, AXOR instructions - (rao-int). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX3_RAO_INTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int raoIntSupported = ExtractBits(cpuInfo[0], 3, 1);

    return (bool)raoIntSupported;
}

/* AVX Vector Neural Network Instructions (VNNI) (VEX encoded) - (avx-vnni). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX4_AVX_VNNIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int avxVnniSupported = ExtractBits(cpuInfo[0], 4, 1);

    return (bool)avxVnniSupported;
}

/* AVX-512 instructions for bfloat16 numbers - (avx512-bf16). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX5_AVX512_BF16IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int avx512Bf16Supported = ExtractBits(cpuInfo[0], 5, 1);

    return (bool)avx512Bf16Supported;
}

/* Linear Address Space Separation (CR4 bit 27) - (lass). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX6_LASSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int lassSupported = ExtractBits(cpuInfo[0], 6, 1);

    return (bool)lassSupported;
}

/* CMPccXADD instructions - (cmpccxadd). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX7_CMPCCXADDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int cmpccxaddSupported = ExtractBits(cpuInfo[0], 7, 1);

    return (bool)cmpccxaddSupported;
}

/* Architectural Performance Monitoring Extended Leaf (EAX=23h) - (archperf­monext). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX8_ARCHPERFMONEXTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int archperfMonextSupported = ExtractBits(cpuInfo[0], 8, 1);

    return (bool)archperfMonextSupported;
}

/* ? - (dedup). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX9_DEDUPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int dedupSupported = ExtractBits(cpuInfo[0], 9, 1);

    return (bool)dedupSupported;
}

/* Fast zero-length REP MOVSB - (fzrm). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX10_FZRMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int fzrmSupported = ExtractBits(cpuInfo[0], 10, 1);

    return (bool)fzrmSupported;
}

/* Fast short REP STOSB - (fsrs). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX11_FSRSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int fsrsSupported = ExtractBits(cpuInfo[0], 11, 1);

    return (bool)fsrsSupported;
}

/* Fast short REP CMPSB and REP SCASB - (rsrcs). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX12_RSRCSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int rsrcsSupported = ExtractBits(cpuInfo[0], 12, 1);

    return (bool)rsrcsSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX13_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[0], 13, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX14_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[0], 14, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX15_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[0], 15, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX16_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[0], 16, 1);

    return (bool)reservedSupported;
}

/* Flexible Return and Event Delivery - (fred). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX17_FREDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int fredSupported = ExtractBits(cpuInfo[0], 17, 1);

    return (bool)fredSupported;
}

/* LKGS Instruction - (lkgs). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX18_LKGSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int lkgsSupported = ExtractBits(cpuInfo[0], 18, 1);

    return (bool)lkgsSupported;
}

/* WRMSRNS instruction (non-serializing write to MSRs) - (wrmsrns). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX19_WRMSRNSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int wrmsrnsSupported = ExtractBits(cpuInfo[0], 19, 1);

    return (bool)wrmsrnsSupported;
}

/* NMI source reporting - (nmi_src). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX20_NMI_SRCIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int nmi_srcSupported = ExtractBits(cpuInfo[0], 20, 1);

    return (bool)nmi_srcSupported;
}

/* AMX instructions for FP16 numbers - (amx-fp16). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX21_AMX_FP16IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int amx_fp16Supported = ExtractBits(cpuInfo[0], 21, 1);

    return (bool)amx_fp16Supported;
}

/* HRESET instruction, IA32_HRESET_ENABLE (17DAh) MSR, and Processor History Reset Leaf (EAX=20h) - (hreset). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX22_HRESETIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int hresetSupported = ExtractBits(cpuInfo[0], 22, 1);

    return (bool)hresetSupported;
}

/* AVX IFMA instructions - (avx-ifma). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX23_AVX_IFMAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int avx_ifmaSupported = ExtractBits(cpuInfo[0], 23, 1);

    return (bool)avx_ifmaSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX24_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[0], 24, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX25_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[0], 25, 1);

    return (bool)reservedSupported;
}

/* Linear Address Masking - (lam). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX26_LAMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int lamSupported = ExtractBits(cpuInfo[0], 26, 1);

    return (bool)lamSupported;
}

/* RDMSRLIST and WRMSRLIST instructions, and the IA32_BARRIER (02Fh) MSR - (msrlist). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX27_MSRListIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int msrlistSupported = ExtractBits(cpuInfo[0], 27, 1);

    return (bool)msrlistSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX28_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[0], 28, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX29_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[0], 29, 1);

    return (bool)reservedSupported;
}

/* If 1, supports INVD instruction execution prevention after BIOS Done. - (invd_­disable_­post_­bios_done). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX30_INVD_DISABLE_POST_BIOS_DONEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int invd_­disable_­post_­bios_doneSupported = ExtractBits(cpuInfo[0], 30, 1);

    return (bool)invd_­disable_­post_­bios_doneSupported;
}

/* MOVRS and PREFETCHRST2 instructions supported (memory read/prefetch with read-shared hint) - (MOVRS). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EAX31_MOVRSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int movrsSupported = ExtractBits(cpuInfo[0], 31, 1);

    return (bool)movrsSupported;
}

/* EBX. */
/* Intel PPIN (Protected Processor Inventory Number): IA32_PPIN_CTL (04Eh) and IA32_PPIN (04Fh) MSRs. - (ppin). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX0_PPINIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int ppinSupported = ExtractBits(cpuInfo[1], 0, 1);

    return (bool)ppinSupported;
}

/* Total Storage Encryption: PBNDKB instruction and TSE_CAPABILITY (9F1h) MSR. - (pbndkb). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX1_PBNDKBIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int pbndkbSupported = ExtractBits(cpuInfo[1], 1, 1);

    return (bool)pbndkbSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX2_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 2, 1);

    return (bool)reservedSupported;
}

/* If 1, then bit 22 of IA32_MISC_ENABLE cannot be set to 1 to limit the value returned by CPUID.(EAX=0):EAX[7:0]. - (CPUID­MAXVAL_­LIM_RMV). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX3_CPUID­MAXVAL_­LIM_RMVIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int cpuid_maxval_lim_rmvSupported = ExtractBits(cpuInfo[1], 3, 1);

    return (bool)cpuid_maxval_lim_rmvSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX4_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 4, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX5_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 5, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX6_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 6, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX7_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 7, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX8_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 8, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX9_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 9, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX10_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 10, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX11_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 11, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX12_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 12, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX13_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 13, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX14_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 14, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX15_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 15, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX16_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 16, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX17_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 17, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX18_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 18, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX19_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 19, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX20_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 20, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX21_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 21, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX22_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 22, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX23_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 23, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX24_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 24, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX25_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 25, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX26_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 26, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX27_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 27, 1);

    return (bool)reservedSupported;
}

/* Reserved / ? - (mpsadbw_512). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX28_Reserved_MPSADBW_512IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reserved_mpsadbw_512Supported = ExtractBits(cpuInfo[1], 28, 1);

    return (bool)reserved_mpsadbw_512Supported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX29_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 29, 1);

    return (bool)reservedSupported;
}

/* Reserved / ? - (avx512-rao-fp). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX30_Reserved_AVX512_RAO_FPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reserved_avx512_rao_fpSupported = ExtractBits(cpuInfo[1], 30, 1);

    return (bool)reserved_avx512_rao_fpSupported;
}

/* Reserved / ? - (avx512-rao-fp). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EBX31_Reserved_AVX512_RAO_FPIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reserved_avx512_rao_fpSupported = ExtractBits(cpuInfo[1], 31, 1);

    return (bool)reserved_avx512_rao_fpSupported;
}

/* ECX. */
/* Asymmetric RDT Monitoring capability - (RDT_M_­ASYM). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX0_RDT_M_­ASYMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int rdt_m_asymSupported = ExtractBits(cpuInfo[2], 0, 1);

    return (bool)rdt_m_asymSupported;
}

/* Asymmetric RDT Monitoring capability - (RDT_M_­ASYM). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX1_RDT_M_­ASYMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int rdt_m_asymSupported = ExtractBits(cpuInfo[2], 1, 1);

    return (bool)rdt_m_asymSupported;
}

/* Reserved / (X86S, cancelled) - (legacy_­reduced_­isa). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX2_Reserved_LEGACY_REDUCED_ISAIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reserved_legacy_reducde_isaSupported = ExtractBits(cpuInfo[2], 2, 1);

    return (bool)reserved_legacy_reducde_isaSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX3_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 3, 1);

    return (bool)reservedSupported;
}

/* 64-bit SIPI (Startup InterProcessor Interrupt) (part of cancelled X86S) - (sipi64). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX4_SIPI64IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int sipi64Supported = ExtractBits(cpuInfo[2], 4, 1);

    return (bool)sipi64Supported;
}

/* Immediate forms of the RDMSR and WRMSRNS instructions - (MSR_IMM). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX5_MSR_IMMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int msr_immSupported = ExtractBits(cpuInfo[2], 5, 1);

    return (bool)msr_immSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX6_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 6, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX7_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 7, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX8_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 8, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX9_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 9, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX10_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 10, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX11_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 11, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX12_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 12, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX13_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 13, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX14_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 14, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX15_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 15, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX16_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 16, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX17_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 17, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX18_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 18, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX19_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 19, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX20_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 20, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX21_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 21, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX22_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 22, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX23_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 23, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX24_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 24, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX25_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 25, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX26_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 26, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX27_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 27, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX28_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 28, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX29_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 29, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX30_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 30, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_ECX31_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 31, 1);

    return (bool)reservedSupported;
}

/* EDX. */
/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX0_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 0, 1);

    return (bool)reservedSupported;
}

/* Reserved / ? - (avx512-vnni-fp16). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX1_Reserved_AVX512_VNNI_FP16IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reserved_avx512_vnni_fp16Supported = ExtractBits(cpuInfo[3], 1, 1);

    return (bool)reserved_avx512_vnni_fp16Supported;
}

/* Reserved / ? - (avx512-vnni-int8). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX2_Reserved_AVX512_VNNI_INT8IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reserved_avx512_vnni_int8Supported = ExtractBits(cpuInfo[3], 2, 1);

    return (bool)reserved_avx512_vnni_int8Supported;
}

/* Reserved / ? - (avx512-ne-convert). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX3_Reserved_AVX512_NE_CONVERTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reserved_avx512_ne_convertSupported = ExtractBits(cpuInfo[3], 3, 1);

    return (bool)reserved_avx512_ne_convertSupported;
}

/* AVX VNNI INT8 instructions - (avx-vnni-int8). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX4_AVX_VNNI_INT8IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int avx_vnni_int8Supported = ExtractBits(cpuInfo[3], 4, 1);

    return (bool)avx_vnni_int8Supported;
}

/* AVX no-exception FP conversion instructions (bfloat16-FP32 and FP16->FP32) - (avx-ne-convert). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX5_AVX_NE_CONVERTIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int avx_ne_convertSupported = ExtractBits(cpuInfo[3], 5, 1);

    return (bool)avx_ne_convertSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX6_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 6, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX7_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 7, 1);

    return (bool)reservedSupported;
}

/* AMX support for "complex" tiles (TCMMIMFP16PS and TCMMRLFP16PS) - (amx-complex). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX8_AMX_COMPLEXIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int amx_complexSupported = ExtractBits(cpuInfo[3], 8, 1);

    return (bool)amx_complexSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX9_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 9, 1);

    return (bool)reservedSupported;
}

/* AVX VNNI INT16 instructions - (avx-vnni-int16). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX10_AVX_VNNI_INT16IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int avx_vnni_int16Supported = ExtractBits(cpuInfo[3], 10, 1);

    return (bool)avx_vnni_int16Supported;
}

/* Reserved / ? - (avx512-vnni-int16). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX11_Reserved_AVX512_VNNI_INT16IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reserved_avx512_vnni_int16Supported = ExtractBits(cpuInfo[3], 11, 1);

    return (bool)reserved_avx512_vnni_int16Supported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX12_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 12, 1);

    return (bool)reservedSupported;
}

/* User-timer events: IA32_UINTR_TIMER (1B00h) MSR - (utmr). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX13_UTMRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int utmrSupported = ExtractBits(cpuInfo[3], 13, 1);

    return (bool)utmrSupported;
}

/* Instruction-cache prefetch instructions (PREFETCHIT0 and PREFETCHIT1) - (prefetchi). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX14_PREFETCHIIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int prefetchiSupported = ExtractBits(cpuInfo[3], 14, 1);

    return (bool)prefetchiSupported;
}

/* User-mode MSR access instructions (URDMSR and UWRMSR) - (user_msr). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX15_USER_MSRIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int user_msrSupported = ExtractBits(cpuInfo[3], 15, 1);

    return (bool)user_msrSupported;
}

/* Reserved / ? - (avx512-bf16-ne). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX16_Reserved_AVX512_BF16_NEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reserved_avx512_bf16_neSupported = ExtractBits(cpuInfo[3], 16, 1);

    return (bool)reserved_avx512_bf16_neSupported;
}

/* If 1, the UIRET (User Interrupt Return) instruction will set UIF (User Interrupt Flag) to the value of bit 1 of the RFLAGS image popped off the stack. - (uiret-uif-from-rflags). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX17_UIRET_UIF_FROM_RFLAGSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int uiret_uif_from_rflagsSupported = ExtractBits(cpuInfo[3], 17, 1);

    return (bool)uiret_uif_from_rflagsSupported;
}

/* If 1, then Control-Flow Enforcement (CET) Supervisor Shadow Stacks (SSS) are guaranteed not to become prematurely busy as long as shadow stack switching does not cause page faults on the stack being switched to. - (cet-sss). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX18_CET_SSSIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int cet_sssSupported = ExtractBits(cpuInfo[3], 18, 1);

    return (bool)cet_sssSupported;
}

/* AVX10 Converged Vector ISA (see also leaf 24h) - (avx10). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX19_AVX10IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int avx10Supported = ExtractBits(cpuInfo[3], 19, 1);

    return (bool)avx10Supported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX20_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 20, 1);

    return (bool)reservedSupported;
}

/* Advanced Performance Extensions, Foundation (adds REX2 and extended EVEX prefix encodings to support 32 GPRs, as well as some new instructions) - (APX_F). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX21_APX_FIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int apx_fSupported = ExtractBits(cpuInfo[3], 21, 1);

    return (bool)apx_fSupported;
}

/* If 1, then trusted execution environment technologies (Intel TDX and Intel SGX) support attestation rooted in the on-chip Security Engine. - (SEC_TEE_­ATTESTATION). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX22_SEC_TEE_ATTESTATIONIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int sec_tee_attestationSupported = ExtractBits(cpuInfo[3], 22, 1);

    return (bool)sec_tee_attestationSupported;
}

/* MWAIT instruction - (mwait). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX23_MWAITIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int mwaitSupported = ExtractBits(cpuInfo[3], 23, 1);

    return (bool)mwaitSupported;
}

/* Static Lockstep Mode (bit 0 of IA32_INTEGRITY_STATUS MSR is available) - (slsm). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX24_SLSMIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int slsmSupported = ExtractBits(cpuInfo[3], 24, 1);

    return (bool)slsmSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX25_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 25, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX26_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 26, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX27_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 27, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX28_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 28, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX29_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 29, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX30_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 30, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX1_EDX31_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 1);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 31, 1);

    return (bool)reservedSupported;
}

/* EAX=0x7, ECX=0x2: Extended Features. */
extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX2EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX2EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX2ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX7ECX2EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

/* EDX. */
/* Fast Store Forwarding Predictor disable supported. (SPEC_CTRL (MSR 48h) bit 7) - (psfd). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX0_PSFDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int psfdSupported = ExtractBits(cpuInfo[3], 0, 1);

    return (bool)psfdSupported;
}

/* IPRED_DIS controls supported. (SPEC_CTRL bits 3 and 4) IPRED_DIS prevents instructions at an indirect branch target from speculatively executing until the branch target address is resolved. - (ipred_ctrl). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX1_IPREDIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int ipredSupported = ExtractBits(cpuInfo[3], 1, 1);

    return (bool)ipredSupported;
}

/* RRSBA behavior disable supported. (SPEC_CTRL bits 5 and 6) - (rrsba_ctrl). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX2_RRSBA_CTRLIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int rrsba_ctrlSupported = ExtractBits(cpuInfo[3], 2, 1);

    return (bool)rrsba_ctrlSupported;
}

/* Data Dependent Prefetcher disable supported. (SPEC_CTRL bit 8) - (ddpd_u). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX3_DDPD_UIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int ddpd_uSupported = ExtractBits(cpuInfo[3], 3, 1);

    return (bool)ddpd_uSupported;
}

/* BHI_DIS_S behavior[128] enable supported. (SPEC_CTRL bit 10) BHI_DIS_S prevents predicted targets of indirect branches executed in ring 0 / 1 / 2 from being selected based on branch history from branches executed in ring 3. - (bhi_ctrl). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX4_BHI_CTRLIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int bhi_ctrlSupported = ExtractBits(cpuInfo[3], 4, 1);

    return (bool)bhi_ctrlSupported;
}

/* If set, the processor does not exhibit MXCSR configuration dependent timing. - (mcdt_no). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX5_MCDT_NOIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int mcdt_noSupported = ExtractBits(cpuInfo[3], 5, 1);

    return (bool)mcdt_noSupported;
}

/* UC-lock disable feature (with UC-lock exceptions reported as #AC) supported. - (UC_LOCK_DISABLE). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX6_UC_LOCK_DISABLEIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int uc_lock_disableSupported = ExtractBits(cpuInfo[3], 6, 1);

    return (bool)uc_lock_disableSupported;
}

/* If set, indicates that the MONITOR/UMONITOR instructions are not affected by performance/power issues caused by the instructions exceeding the capacity of an internal monitor tracking table. - (monitor_­mitg_no). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX7_MONITOR_MITG_NOIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int monitor_mitg_noSupported = ExtractBits(cpuInfo[3], 7, 1);

    return (bool)monitor_mitg_noSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX8_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 8, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX9_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 9, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX10_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 10, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX11_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 11, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX12_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 12, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX13_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 13, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX14_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 14, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX15_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 15, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX16_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 16, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX17_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 17, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX18_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 18, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX19_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 19, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX20_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 20, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX21_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 21, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX22_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 22, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX23_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 23, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX24_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 24, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX25_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 25, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX26_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 26, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX27_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 27, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX28_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 28, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX29_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 29, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX30_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 30, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX7ECX2_EDX31_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x7, 2);

    unsigned int reservedSupported = ExtractBits(cpuInfo[3], 31, 1);

    return (bool)reservedSupported;
}

#pragma endregion

#pragma region EAX=0x0D: XSAVE Features and State Components

extern "C" __declspec(dllexport) char* __cdecl GetEAXDEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xD, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXDEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xD, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXDECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xD, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXDEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xD, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion













#pragma region EAX=0x12: SGX Capabilities

extern "C" __declspec(dllexport) char* __cdecl GetEAX12EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x12, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX12EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x12, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX12ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x12, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX12EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x12, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion















#pragma region EAX=0x14, ECX=0x0: Processor Trace feature bits in EBX and ECX

extern "C" __declspec(dllexport) char* __cdecl GetEAX14ECX0EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX14ECX0EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX14ECX0ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX14ECX0EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
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
/* ToPA (Table of Physical Addresses) output mechanism for trace packets supported - (topaout). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX0_TopaOutIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int topaOutSupported = ExtractBits(cpuInfo[2], 0, 1);

    return (bool)topaOutSupported;
}

/* ToPA tables can contain hold multiple output entries - (mentry). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX1_MentryIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int mentrySupported = ExtractBits(cpuInfo[2], 1, 1);

    return (bool)mentrySupported;
}

/* Single-Range Output scheme supported - (sngl_rng_out). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX2_SnglRngOutIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int snglRngOutSupported = ExtractBits(cpuInfo[2], 2, 1);

    return (bool)snglRngOutSupported;
}

/* Output to Trace Transport subsystem supported - (trace_transport_subsystem). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX3_TraceTransportSubsystemIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int traceTransportSubsystemSupported = ExtractBits(cpuInfo[2], 3, 1);

    return (bool)traceTransportSubsystemSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX4_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 4, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX5_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 5, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX6_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 6, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX7_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 7, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX8_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 8, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX9_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 9, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX10_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 10, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX11_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 11, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX12_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 12, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX13_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 13, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX14_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 14, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX15_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 15, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX16_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 16, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX17_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 17, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX18_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 18, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX19_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 19, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX20_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 20, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX21_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 21, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX22_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 22, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX23_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 23, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX24_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 24, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX25_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 25, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX26_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 26, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX27_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 27, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX28_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 28, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX29_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 29, 1);

    return (bool)reservedSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX30_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[2], 30, 1);

    return (bool)reservedSupported;
}

/* IP (Instruction Pointer) format for trace packets that contain IP payloads. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX14ECX0_ECX31_IPFormatForTracePacketsThatContainIPPayloadsIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 0);

    unsigned int iPFormatForTracePacketsThatContainIPPayloadsSupported = ExtractBits(cpuInfo[2], 31, 1);

    return (bool)iPFormatForTracePacketsThatContainIPPayloadsSupported;
}

#pragma endregion










#pragma region EAX=0x14, ECX=0x1: Processor Trace packet generation information in EAX, EBX and ECX

extern "C" __declspec(dllexport) char* __cdecl GetEAX14ECX1EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX14ECX1EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX14ECX1ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX14ECX1EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x14, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
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

extern "C" __declspec(dllexport) char* __cdecl GetEAX15EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX15EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX15ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX15EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x15, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
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

extern "C" __declspec(dllexport) char* __cdecl GetEAX16EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX16EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX16ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX16EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x16, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
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

extern "C" __declspec(dllexport) char* __cdecl GetEAX17EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x17, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX17EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x17, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX17ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x17, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX17EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x17, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion

















#pragma region EAX=0x18: TLB Hierarchy and Topology

extern "C" __declspec(dllexport) char* __cdecl GetEAX18EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x18, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX18EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x18, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX18ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x18, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX18EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x18, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion












#pragma region EAX=0x19: Intel Key Locker Features

extern "C" __declspec(dllexport) char* __cdecl GetEAX19EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x19, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX19EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x19, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX19ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x19, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX19EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x19, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion










#pragma region EAX=0x1D: Intel AMX Tile Information

extern "C" __declspec(dllexport) char* __cdecl GetEAX1DEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1D, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX1DEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1D, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX1DECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1D, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX1DEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1D, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion













#pragma region EAX=0x1E: Intel AMX Tile Multiplier (TMUL) Information

extern "C" __declspec(dllexport) char* __cdecl GetEAX1EEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1E, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX1EEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1E, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX1EECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1E, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX1EEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x1E, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion











#pragma region EAX=0x21: Reserved for TDX enumeration

extern "C" __declspec(dllexport) char* __cdecl GetEAX21EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x21, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX21EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x21, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX21ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x21, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX21EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x21, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion






#pragma region EAX=0x24, ECX=0x0: AVX10 Converged Vector ISA

extern "C" __declspec(dllexport) char* __cdecl GetEAX24ECX0EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX24ECX0EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX24ECX0ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX24ECX0EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion










#pragma region EAX=0x24, ECX=0x1: Discrete AVX10 Features

extern "C" __declspec(dllexport) char* __cdecl GetEAX24ECX1EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX24ECX1EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX24ECX1ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX24ECX1EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x24, 1);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion





















#pragma region EAX=0x20000000: Highest Xeon Phi Function Implemented

extern "C" __declspec(dllexport) char* __cdecl GetEAX20000000EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX20000000EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX20000000ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX20000000EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX20000000EAX_HighestXeonPhiFunctionImplemented()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000000, 0);

    return cpuInfo[0];
}

#pragma endregion

















#pragma region EAX=0x20000001: Xeon Phi Feature Bits

extern "C" __declspec(dllexport) char* __cdecl GetEAX20000001EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX20000001EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX20000001ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX20000001EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x20000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion





















#pragma region EAX=0x40000000h-0x4FFFFFFFh: Reserved for Hypervisors

extern "C" __declspec(dllexport) char* __cdecl GetEAX40000000EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x40000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX40000000EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x40000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX40000000ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x40000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX40000000EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x40000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion














#pragma region EAX=0x80000000: Highest Extended Function Implemented

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000000EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000000EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000000ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000000EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) int __cdecl GetEAX80000000EAX_HighestExtendedFunctionImplemented()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000000, 0);

    return cpuInfo[0];
}

#pragma endregion

















#pragma region EAX=0x80000001: Extended Processor Info and Feature Bits

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000001EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000001EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000001ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000001EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion












#pragma region EAX=0x80000002,0x80000003,0x80000004: Processor Brand String

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000002EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000002, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000002EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000002, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000002ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000002, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000002EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000002, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000003EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000003, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000003EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000003, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000003ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000003, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000003EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000003, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000004EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000004, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000004EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000004, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000004ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000004, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000004EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000004, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
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

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(sizeof(processorBrandString));
    if (result) {
        strcpy_s(result, sizeof(processorBrandString), processorBrandString);
    }
    return result;
}

#pragma endregion

















#pragma region EAX=0x80000005: L1 Cache and TLB Identifiers

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000005EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000005EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000005ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000005EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

/* L1 Cache/TLB information in EAX,EBX,ECX,EDX. */
/* Number of instruction TLB entries. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EAX0_7_NumberOfInstructionTLBEntries()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int numberOfInstructionTLBEntries = ExtractBits(cpuInfo[0], 0, 7);

    return numberOfInstructionTLBEntries;
}

/* Instruction TLB associativity. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EAX8_15_InstructionTLBAssociativity()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int instructionTLBAssociativity = ExtractBits(cpuInfo[0], 8, 15);

    return instructionTLBAssociativity;
}

/* Number of data TLB entries. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EAX16_23_DataTLBEntries()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int dataTLBEntries = ExtractBits(cpuInfo[0], 16, 23);

    return dataTLBEntries;
}

/* Data TLB associativity. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EAX24_31_DataTLBAssociativity()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int dataTLBAssociativity = ExtractBits(cpuInfo[0], 24, 31);

    return dataTLBAssociativity;
}

/* Number of instruction TLB entries. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EBX0_7_NumberOfInstructionTLBEntries()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int numberOfInstructionTLBEntries = ExtractBits(cpuInfo[1], 0, 7);

    return numberOfInstructionTLBEntries;
}

/* Instruction TLB associativity. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EBX8_15_InstructionTLBAssociativity()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int instructionTLBAssociativity = ExtractBits(cpuInfo[1], 8, 15);

    return instructionTLBAssociativity;
}

/* Number of data TLB entries. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EBX16_23_DataTLBEntries()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int dataTLBEntries = ExtractBits(cpuInfo[1], 16, 23);

    return dataTLBEntries;
}

/* Data TLB associativity. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EBX24_31_DataTLBAssociativity()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int dataTLBAssociativity = ExtractBits(cpuInfo[1], 24, 31);

    return dataTLBAssociativity;
}

/* Cache line size in bytes. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005ECX0_7_CacheLineSizeInBytes()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int cacheLineSizeInBytes = ExtractBits(cpuInfo[2], 0, 7);

    return cacheLineSizeInBytes;
}

/* Number of cache lines per tag. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005ECX8_15_NumberOfCacheLinesPerTag()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int numberOfCacheLinesPerTag = ExtractBits(cpuInfo[2], 8, 15);

    return numberOfCacheLinesPerTag;
}

/* Cache associativity. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005ECX16_23_CacheAssociativity()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int cacheAssociativity = ExtractBits(cpuInfo[2], 16, 23);

    return cacheAssociativity;
}

/* Cache size in kibibytes. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005ECX24_31_CacheSize()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int cacheSize = ExtractBits(cpuInfo[2], 24, 31);

    return cacheSize;
}

/* Cache line size in bytes. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EDX0_7_CacheLineSizeInBytes()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int cacheLineSizeInBytes = ExtractBits(cpuInfo[3], 0, 7);

    return cacheLineSizeInBytes;
}

/* Number of cache lines per tag. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EDX8_15_NumberOfCacheLinesPerTag()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int numberOfCacheLinesPerTag = ExtractBits(cpuInfo[3], 8, 15);

    return numberOfCacheLinesPerTag;
}

/* Cache associativity. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EDX16_23_CacheAssociativity()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int cacheAssociativity = ExtractBits(cpuInfo[3], 16, 23);

    return cacheAssociativity;
}

/* Cache size in kibibytes. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000005EDX24_31_CacheSize()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000005, 0);

    unsigned int cacheSize = ExtractBits(cpuInfo[3], 24, 31);

    return cacheSize;
}
#pragma endregion








#pragma region EAX=0x80000006: Extended L2 Cache Features

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000006EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000006EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000006ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000006EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000006, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
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

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000007EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000007, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000007EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000007, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000007ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000007, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000007EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000007, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion















#pragma region EAX=0x80000008: Virtual and Physical Address Sizes

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000008EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000008EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000008ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000008EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

/* Size and range fields in EAX. */
/* Number of Physical Address Bits. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008EAX0_7_NumberOfPhysicalAddressBits()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int numberOfPhysicalAddressBits = ExtractBits(cpuInfo[0], 0, 7);

    return numberOfPhysicalAddressBits;
}

/* Number of Linear Address Bits. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008EAX8_15_NumberOfLinearAddressBits()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int numberOfLinearAddressBits = ExtractBits(cpuInfo[0], 8, 15);

    return numberOfLinearAddressBits;
}

/* Guest Physical Address Size. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008EAX16_23_GuestPhysicalAddressSize()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int guestPhysicalAddressSize = ExtractBits(cpuInfo[0], 16, 23);

    return guestPhysicalAddressSize;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008EAX24_31_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int reserved = ExtractBits(cpuInfo[0], 24, 31);

    return reserved;
}

/* Feature bits in EBX. */
/* CLZERO instruction - (clzero). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX0_CLZERO_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int clzeroSupported = ExtractBits(cpuInfo[1], 0, 1);

    return (bool)clzeroSupported;
}

/* Retired instruction count MSR (C000_00E9h) supported - (retired_instr). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX1_RetiredInstr_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int retiredInstrSupported = ExtractBits(cpuInfo[1], 1, 1);

    return (bool)retiredInstrSupported;
}

/* XRSTOR restores FP errors - (xrstor_fp_err). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX2_XRSTOR_FP_ERR_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int xrstorFpErrSupported = ExtractBits(cpuInfo[1], 2, 1);

    return (bool)xrstorFpErrSupported;
}

/* INVLPGB and TLBSYNC instructions - (invlpgb). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX3_INVLPGB_TLBSYNC_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int invlpgbTlbsyncSupported = ExtractBits(cpuInfo[1], 3, 1);

    return (bool)invlpgbTlbsyncSupported;
}

/* RDPRU instruction - (rdpru). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX4_RDPRU_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int rdpruSupported = ExtractBits(cpuInfo[1], 4, 1);

    return (bool)rdpruSupported;
}

/* PlayStation 5: Execute-Only Memory - (xotext). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX5_XOTEXT_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int xotextSupported = ExtractBits(cpuInfo[1], 5, 1);

    return (bool)xotextSupported;
}

/* Memory Bandwidth Enforcement - (mbe). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX6_MBE_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int mbeSupported = ExtractBits(cpuInfo[1], 6, 1);

    return (bool)mbeSupported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX7_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 7, 1);

    return (bool)reservedSupported;
}

/* MCOMMIT instruction - (mcommit). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX8_MCOMMIT_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int mcommitSupported = ExtractBits(cpuInfo[1], 8, 1);

    return (bool)mcommitSupported;
}

/* WBNOINVD instruction - (wbnoinvd). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX9_WBNOINVD_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int wbnoinvdSupported = ExtractBits(cpuInfo[1], 9, 1);

    return (bool)wbnoinvdSupported;
}

/* LBR extensions v1 - (LBR_EXT_V1). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX10_LBR_EXT_V1_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int lbrExtV1Supported = ExtractBits(cpuInfo[1], 10, 1);

    return (bool)lbrExtV1Supported;
}

/* Reserved. */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX11_ReservedIsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int reservedSupported = ExtractBits(cpuInfo[1], 11, 1);

    return (bool)reservedSupported;
}

/* Indirect Branch Prediction Barrier (performed by writing 1 to bit 0 of PRED_CMD (MSR 049h)) - (IBPB). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX12_IBPB_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int ibpbSupported = ExtractBits(cpuInfo[1], 12, 1);

    return (bool)ibpbSupported;
}

/* WBINVD and WBNOINVD are interruptible - (wbinvd_int). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX13_WBINVD_INT_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int wbinvdIntSupported = ExtractBits(cpuInfo[1], 13, 1);

    return (bool)wbinvdIntSupported;
}

/* Indirect Branch Restricted Speculation - (IBRS). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX14_IBRS_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int ibrsSupported = ExtractBits(cpuInfo[1], 14, 1);

    return (bool)ibrsSupported;
}

/* Single Thread Indirect Branch Prediction mode - (STIBP). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX15_STIBP_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int stibpSupported = ExtractBits(cpuInfo[1], 15, 1);

    return (bool)stibpSupported;
}

/* IBRS mode has enhanced performance and should be left always on - (IbrsAlwaysOn). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX16_IBRS_ALWAYS_ON_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int ibrsAlwaysOnSupported = ExtractBits(cpuInfo[1], 16, 1);

    return (bool)ibrsAlwaysOnSupported;
}

/* STIBP mode has enhanced performance and should be left always on - (STIBPAlwaysOn). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX17_STIBP_ALWAYS_ON_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int stibpAlwaysOnSupported = ExtractBits(cpuInfo[1], 17, 1);

    return (bool)stibpAlwaysOnSupported;
}

/* IBRS preferred over software - (ibrs_preferred). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX18_IBRS_PREFERRED_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int ibrsPreferredSupported = ExtractBits(cpuInfo[1], 18, 1);

    return (bool)ibrsPreferredSupported;
}

/* IBRS provides Same Mode Protection - (ibrs_same_mode_protection). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX19_IBRS_SAME_MODE_PROTECTION_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int ibrsSameModeProtectionSupported = ExtractBits(cpuInfo[1], 19, 1);

    return (bool)ibrsSameModeProtectionSupported;
}

/* EFER.LMSLE is unsupported - (no_efer_lmsle). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX20_NO_EFER_LMSLE_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int noEferLmsleSupported = ExtractBits(cpuInfo[1], 20, 1);

    return (bool)noEferLmsleSupported;
}

/* INVLPGB support for nested pages - (invlpgb_nested). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX21_INVLPGB_NESTED_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int invlpgbNestedSupported = ExtractBits(cpuInfo[1], 21, 1);

    return (bool)invlpgbNestedSupported;
}

/* LBR TSX info - (LBR_TSX). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX22_LBR_TSX_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int lbrTsxBits = ExtractBits(cpuInfo[1], 22, 1);

    return (bool)lbrTsxBits;
}

/* Protected Processor Inventory Number - PPIN_CTL(C001_02F0) and PPIN(C001_02F1) MSRs are present - (ppin). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX23_PPIN_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int ppinSupported = ExtractBits(cpuInfo[1], 23, 1);

    return (bool)ppinSupported;
}

/* Speculative Store Bypass Disable - (ssbd). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX24_SSBD_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int ssbdSupported = ExtractBits(cpuInfo[1], 24, 1);

    return (bool)ssbdSupported;
}

/* Speculative Store Bypass Disable Legacy - (ssbd_legacy). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX25_SSBD_LEGACY_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int ssbdLegacySupported = ExtractBits(cpuInfo[1], 25, 1);

    return (bool)ssbdLegacySupported;
}

/* Speculative Store Bypass Disable Not Required - (ssbd_no). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX26_SSBD_NO_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int ssbdNoSupported = ExtractBits(cpuInfo[1], 26, 1);

    return (bool)ssbdNoSupported;
}

/* Collaborative Processor Performance Control - (cppc). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX27_CPPC_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int cppcSupported = ExtractBits(cpuInfo[1], 27, 1);

    return (bool)cppcSupported;
}

/* Predictive Store Forward Disable - (psfd). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX28_PSFD_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int psfdSupported = ExtractBits(cpuInfo[1], 28, 1);

    return (bool)psfdSupported;
}

/* Branch Type Confusion: Processor not affected - (btc_no). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX29_BTC_NO_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int btcNoSupported = ExtractBits(cpuInfo[1], 29, 1);

    return (bool)btcNoSupported;
}

/* IBPB (see bit 12) also clears return address predictor - (IBPB_RET). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX30_IBPB_RET_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int ibpbRetSupported = ExtractBits(cpuInfo[1], 30, 1);

    return (bool)ibpbRetSupported;
}

/* Branch Sampling Support - (branch_sampling). */
extern "C" __declspec(dllexport) bool __cdecl GetEAX80000008EBX31_BRANCH_SAMPLING_IsSupported()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int branchSamplingSupported = ExtractBits(cpuInfo[1], 31, 1);

    return (bool)branchSamplingSupported;
}

/* Size and range fields in ECX. */
/* Number of Physical Threads in processor (minus 1). */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008ECX0_7_NumberOfPhysicalThreadsInProcessorMinus1()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int numberOfPhysicalThreads = ExtractBits(cpuInfo[2], 0, 7);

    return numberOfPhysicalThreads;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008ECX8_11_Reserved()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int reserved = ExtractBits(cpuInfo[2], 8, 3);

    return reserved;
}

/* APIC ID Size. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008ECX12_15_APIC_IDSize()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int apicIdSize = ExtractBits(cpuInfo[2], 12, 3);

    return apicIdSize;
}

/* Performance Timestamp Counter size. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008ECX16_17_PerformanceTimestampCounterSize()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int performanceTimestampCounterSize = ExtractBits(cpuInfo[2], 16, 1);

    return performanceTimestampCounterSize;
}

/* Reserved. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008ECX18_31_Reserverd()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int reserved = ExtractBits(cpuInfo[2], 18, 13);

    return reserved;
}

/* Size and range fields in EDX. */
/* Maximum page count for INVLPGB instruction. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008EDX0_15_MaximumPageCountForINVLPGBInstruction()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int maximumPageCount = ExtractBits(cpuInfo[3], 0, 16);

    return maximumPageCount;
}

/* Maximum ECX value recognized by RDPRU instruction. */
extern "C" __declspec(dllexport) int __cdecl GetEAX80000008EDX16_31_MaximumECXValueForRDPRUInstruction()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000008, 0);

    unsigned int maximumECXValue = ExtractBits(cpuInfo[3], 16, 16);

    return maximumECXValue;
}

#pragma endregion
















#pragma region EAX=0x8000000A: SVM features

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000000AEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000000A, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000000AEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000000A, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000000AECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000000A, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000000AEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000000A, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion













#pragma region EAX=0x8000001F: Encrypted Memory Capabilities

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000001FEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001F, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000001FEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001F, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000001FECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001F, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8000001FEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8000001F, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion















#pragma region EAX=0x80000021: Extended Feature Identification

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000021EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000021, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000021EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000021, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000021ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000021, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000021EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000021, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion












#pragma region EAX=0x80000025: Encrypted Memory Capabilities 2

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000025EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000025, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000025EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000025, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000025ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000025, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX80000025EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x80000025, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion

















#pragma region EAX=0x8C860000: Hygon Extended Feature Flags

extern "C" __declspec(dllexport) char* __cdecl GetEAX8C860000EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8C860000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8C860000EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8C860000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8C860000ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8C860000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8C860000EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8C860000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion













#pragma region EAX=0x8FFFFFFE: AMD Easter Eggs

extern "C" __declspec(dllexport) char* __cdecl GetEAX8FFFFFFEEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFE, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8FFFFFFEEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFE, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8FFFFFFEECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFE, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8FFFFFFEEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFE, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion










#pragma region EAX=0x8FFFFFFF: AMD Easter Eggs

extern "C" __declspec(dllexport) char* __cdecl GetEAX8FFFFFFFEAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFF, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8FFFFFFFEBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFF, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8FFFFFFFECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFF, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAX8FFFFFFFEDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0x8FFFFFFF, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion












#pragma region EAX=0xC0000000: Highest Centaur Extended Function

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000000EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000000EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000000ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000000EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000000, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion












#pragma region EAX=0xC0000001: Centaur Feature Information

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000001EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000001EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000001ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000001EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000001, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion









#pragma region EAX=0xC0000002: Centaur Extended CPUID Performance Data

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000002EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000002, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000002EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000002, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000002ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000002, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000002EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000002, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion










#pragma region EAX=0xC0000006, ECX=0: Zhaoxin Feature Information

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000006ECX0EAX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000006, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[0], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000006ECX0EBX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000006, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[1], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000006ECX0ECX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000006, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[2], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

extern "C" __declspec(dllexport) char* __cdecl GetEAXC0000006ECX0EDX()
{
    int cpuInfo[4];
    __cpuidex(cpuInfo, 0xC0000006, 0);
    char binaryStr[33];
    IntToBinary32(cpuInfo[3], binaryStr);

    // Allocate memory for the string that the caller can clean up
    char* result = (char*)malloc(33);
    if (result) {
        strcpy_s(result, 33, binaryStr);
    }
    return result;
}

#pragma endregion















/*----------------------------------------------------------------------------------------------------
// NAME:          FFT.
// PURPOSE:       Быстрое преобразование Фурье: Комплексный сигнал в комплексный спектр и обратно.
//                В случае действительного сигнала в мнимую часть (Idat) записываются нули.
//                Количество отсчетов - кратно 2**К - т.е. 2, 4, 8, 16, ... (см. комментарии ниже).
//
// PARAMETERS:
//
//    float *Rdat    [in, out] - Real part of Input and Output Data (Signal or Spectrum)
//    float *Idat    [in, out] - Imaginary part of Input and Output Data (Signal or Spectrum)
//    int    N       [in]      - Input and Output Data length (Number of samples in arrays)
//    int    LogN    [in]      - Logarithm2(N)
//    int    Ft_Flag [in]      - Ft_Flag = FT_ERR_DIRECT  (i.e. -1) - Direct  FFT  (Signal to Spectrum)
//							   - Ft_Flag = FT_ERR_INVERSE (i.e.  1) - Inverse FFT  (Spectrum to Signal)
//
// RETURN VALUE: false on parameter error
//---------------------------------------------------------------------------------------------------
// NOTE: In this algorithm N and LogN can be only:
//       N    = 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384;
//       LogN = 2, 3,  4,  5,  6,   7,   8,   9,   10,   11,   12,   13,    14;
//---------------------------------------------------------------------------------------------------*/

#pragma once
#include <cmath>

#define  NUMBER_IS_2_POW_K(x)   ((!((x)&((x)-1)))&&((x)>1))  // x is pow(2, k), k=1,2, ...

#define  FT_MAX_N      16384
#define  FT_MAX_LOGN	  14

#define  FT_DIRECT        -1    // Direct transform.
#define  FT_INVERSE        1    // Inverse transform.

class clFFT
{
public:
    bool  FFT(float* Rdat, float* Idat, int N, int LogN, int Ft_Flag);

private:

};


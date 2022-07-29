#ifndef __HM600_H
#define __HM600_H

#define HM600
#define HM700

/*float calcEheute (float *measure) { return measure[8] + measure[9]; }

float calcIpv    (float *measure) { return (measure[10] != 0 ? measure[12]/measure[10] : 0); }

float calcTotal  (float *measure) { return (measure[6] + measure[7]); }

float calcEffi   (float *measure) {
  float sumDc = (measure[2] + measure[5]);
  if (sumDc == 0) 
    return 0;
  else
    return measure[12] / sumDc * 100.0;
}
*/

float calcEheute (uint8_t wr) { return inverters[wr].values[8] + inverters[wr].values[9]; }

float calcIpv    (uint8_t wr) { return (inverters[wr].values[10] != 0 ? inverters[wr].values[12]/inverters[wr].values[10] : 0); }

float calcTotal  (uint8_t wr) { return (inverters[wr].values[6] + inverters[wr].values[7]); }

float calcEffi   (uint8_t wr) {
  float sumDc = (inverters[wr].values[2] + inverters[wr].values[5]);
  if (sumDc == 0) 
    return 0;
  else
    return inverters[wr].values[12] / sumDc * 100.0;
}

float calcIrradiation1 (uint8_t wr) {
  return inverters[wr].values[2] / inverters[wr].modPeaks[1] * 100.0;  
}

float calcIrradiation2 (uint8_t wr) {
  return inverters[wr].values[5] / inverters[wr].modPeaks[2] * 100.0;  
}

const measureDef_t hm600_measureDef[] = {
  { IDX_UDC,    CH1, UNIT_V,  CMD01, 14, BYTES2, DIV10  },
  { IDX_IDC,    CH1, UNIT_A,  CMD01, 16, BYTES2, DIV100 },
  { IDX_PDC,    CH1, UNIT_W,  CMD01, 18, BYTES2, DIV10  },
  { IDX_UDC,    CH2, UNIT_V,  CMD01, 20, BYTES2, DIV10  },
  { IDX_IDC,    CH2, UNIT_A,  CMD01, 22, BYTES2, DIV100 },
  { IDX_PDC,    CH2, UNIT_W,  CMD01, 24, BYTES2, DIV10  },
  { IDX_E_TOTAL,CH1, UNIT_KWH, CMD01, 26, BYTES4, DIV1000 },
  
  { IDX_E_TOTAL,CH2, UNIT_KWH, CMD02, 14, BYTES4, DIV1000 },
  { IDX_E_TAG,  CH1, UNIT_WH, CMD02, 18, BYTES2, DIV1   },
  { IDX_E_TAG,  CH2, UNIT_WH, CMD02, 20, BYTES2, DIV1   },
  { IDX_UAC,    CH0, UNIT_V,  CMD02, 22, BYTES2, DIV10  },
  { IDX_FREQ,   CH0, UNIT_HZ, CMD02, 24, BYTES2, DIV100 },
  { IDX_PAC,    CH0, UNIT_W,  CMD02, 26, BYTES2, DIV10  },

  { IDX_IPV,    CH0, UNIT_A,  CMD83, 14, BYTES2, DIV100 },
  { IDX_WR_TEMP,CH0, UNIT_C,  CMD83, 18, BYTES2, DIV10  }
//  ,{ IDX_STATUS, CH0, UNIT_NIX, CMD83, 16, BYTES2, DIV1  }     
};


measureCalc_t hm600_measureCalc[] = {
  { IDX_E_HEUTE,  CH0, UNIT_WH,  DIV1,    &calcEheute},
  { IDX_E_TOTAL,  CH0, UNIT_KWH, DIV1000, &calcTotal},
  { IDX_WR_EFF,   CH0, UNIT_PCT, DIV1,    &calcEffi},
  { IDX_IRR,      CH1, UNIT_PCT, DIV1,    &calcIrradiation1},
  { IDX_IRR,      CH2, UNIT_PCT, DIV1,    &calcIrradiation2}
};

uint8_t hm600_fragmentLen[] = { 3, 16, 16, 12 };      // 3 = Anzahl

#define HM600_MEASURE_LIST_LEN  sizeof(hm600_measureDef)/sizeof(measureDef_t)
#define HM600_CALCED_LIST_LEN   sizeof(hm600_measureCalc)/sizeof(measureCalc_t)

#endif

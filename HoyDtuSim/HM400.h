#ifndef __HM400_H
#define __HM400_H

#define HM300
#define HM400

const measureDef_t hm400_measureDef[] = {
  { IDX_UDC,    CH1, UNIT_V,  CMD01, 14, BYTES2, DIV10  },
  { IDX_IDC,    CH1, UNIT_A,  CMD01, 16, BYTES2, DIV100 },
  { IDX_PDC,    CH1, UNIT_W,  CMD01, 18, BYTES2, DIV10  },
  { IDX_E_TAG,  CH1, UNIT_WH, CMD01, 24, BYTES2, DIV1   },
  { IDX_E_TOTAL,CH1, UNIT_KWH, CMD01, 20, BYTES4, DIV1000 },
  { IDX_UAC,    CH0, UNIT_V,  CMD01, 26, BYTES2, DIV10  },

  { IDX_IPV,    CH0, UNIT_A,  CMD82, 18, BYTES2, DIV100 },
  { IDX_PAC,    CH0, UNIT_W,  CMD82, 14, BYTES2, DIV10  },
  { IDX_FREQ,   CH0, UNIT_HZ, CMD82, 12, BYTES2, DIV100 },
  { IDX_WR_TEMP,CH0, UNIT_C,  CMD82, 22, BYTES2, DIV10  }
};


measureCalc_t hm400_measureCalc[] = {};

uint8_t hm400_fragmentLen[] = { 2, 16, 16 };      // 2 = Anzahl

#define HM400_MEASURE_LIST_LEN  sizeof(hm400_measureDef)/sizeof(measureDef_t)
#define HM400_CALCED_LIST_LEN   sizeof(hm400_measureCalc)/sizeof(measureCalc_t)

#endif

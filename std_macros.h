#define SET_BIT(reg,bit)				reg|=(1<<bit)
#define CLR_BIT(reg,bit)			reg&=~(1<<bit)
#define toggelBit(reg,bit)			reg^=(1<<bit)
#define READ_BIT(reg,bit)			(reg&(1<<bit))>>bit
#define IsBitClear(reg,bit)		!(reg&(1<<bit))>>bit

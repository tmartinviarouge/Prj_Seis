#ifndef ADS1115_H
#define ADS1115_H

#define OFFSET_ZERO	0x001f  


class ADS1115
{
    public:
	enum ADS1115_REGISTRES {
		REG_CONVERSION	= 0x00 ,
		REG_CONFIG	= 0x01
	};

	enum ADS1115_DIVERS {
		ADRESSE_I2C_DEFAUT	= 0x48 ,
		DELAI_CONVERTION	= 8000	// en mS
	};

	enum ADS1115_REG_CONFIG_OS {
		OS_MASK  = 0x8000,
		OS_SINGLE   = 0x8000,   // Write: Set to start a single-conversion
		OS_BUSY     = 0x0000,   // Read: Bit = 0 convertion en cours
		OS_NOTBUSY  = 0x8000    // Read: Bit = 1 conversion terminée
	};

	enum ADS1115_REG_CONFIG_MUX {
		MUX_MASK  = 0x7000 ,
		MUX_DIFF_0_1  = 0x0000 ,  // Differentiel P = entrée 0, N = entrée 1 (default)
		MUX_DIFF_0_3  = 0x1000 ,  // Differentiel P = entrée 0, N = entrée 3
		MUX_DIFF_1_3  = 0x2000 ,  // Differentiel P = entrée 1, N = entrée 3
		MUX_DIFF_2_3  = 0x3000 ,  // Differentiel P = entrée 2, N = entrée 3
		MUX_SINGLE_0 = 0x4000  ,  // entrée 0 seule
		MUX_SINGLE_1 = 0x5000  ,  // entrée 1 seule
		MUX_SINGLE_2 = 0x6000  ,  // entrée 2 seule
		MUX_SINGLE_3 = 0x7000     // entrée 3 seule
	};

	enum ADS1115_REG_CONFIG_PGA {
		PGA_MASK = 0x0E00 ,
		PGA_6_144V   = 0x0000 ,  // +/-6.144V range
		PGA_4_096V   = 0x0200 ,  // +/-4.096V range
		PGA_2_048V   = 0x0400 ,  // +/-2.048V range (default)
		PGA_1_024V   = 0x0600 ,  // +/-1.024V range
		PGA_0_512V   = 0x0800 ,  // +/-0.512V range
		PGA_0_256V   = 0x0A00 ,  // +/-0.256V range
	};

	enum ADS1115_REG_CONFIG_MODE {
		MODE_MASK    = 0x0100 ,
		MODE_CONTIN  = 0x0000 ,  // Continuous conversion mode
		MODE_SINGLE  = 0x0100 ,  // Power-down single-shot mode (default)
	};

	enum ADS1115_REG_CONFIG_DR {
		DR_MASK      = 0x00E0 ,
		DR_128SPS    = 0x0000 ,  // 128 samples per second
		DR_250SPS    = 0x0020 ,  // 250 samples per second
		DR_490SPS    = 0x0040 ,  // 490 samples per second
		DR_920SPS    = 0x0050 ,  // 920 samples per second
		DR_1600SPS   = 0x0080 ,  // 1600 samples per second (default)
		DR_2400SPS   = 0x00A0 ,  // 2400 samples per second
		DR_3300SPS   = 0x00C0    // 3300 samples per second
	};

	enum ADS1115_REG_CONFIG_CMODE {
		CMODE_MASK   = 0x0010 ,
		CMODE_TRAD   = 0x0000 ,  // Traditional comparator with hysteresis (default)
		CMODE_WINDOW = 0x0010 ,  // Window comparator
	};

	enum ADS1115_REG_CONFIG_CPOL {
		CPOL_MASK    = 0x0008 ,
		CPOL_ACTVLOW = 0x0000 ,  // ALERT/RDY pin is low when active (default)
		CPOL_ACTVHI  = 0x0008 ,  // ALERT/RDY pin is high when active
	};

	enum ADS1115_REG_CONFIG_CLATL {
		CLAT_MASK    = 0x0004 ,  // Determines if ALERT/RDY pin latches once asserted
		CLAT_NONLAT  = 0x0000 ,  // Non-latching comparator (default)
		CLAT_LATCH   = 0x0004 ,  // Latching comparator
	};

	enum ADS1115_REG_CONFIG_CQUE {
		CQUE_MASK    = 0x0003 ,
		CQUE_1CONV   = 0x0000 ,  // Assert ALERT/RDY after one conversions
		CQUE_2CONV   = 0x0001 ,  // Assert ALERT/RDY after two conversions
		CQUE_4CONV   = 0x0002 ,  // Assert ALERT/RDY after four conversions
		CQUE_NONE    = 0x0003    // Disable the comparator and put ALERT/RDY in high state (default)
	};
		

	enum ADS1115_CODES_ERREURS {
		SANS_ERREUR	= 0,
		ERREUR_I2CINIT	,
		ERREUR_I2CBUSY,
		ERREUR_CANAL_INVALIDE,
		FIN_LIST_ERREURS
	};
		
	ADS1115(unsigned char I2Cadresse);
	ADS1115();
	virtual ~ADS1115();
	bool init(unsigned char I2Cadresse);
	bool init();
	int lireEntree(int num);
	int getCodeErreur();

    private:
	int adresseI2C ;
	int config ;
	int fd;
	int codeErreur;
};

#endif

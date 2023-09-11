#include "../all.h"

typedef struct LoongarchOp LoongarchOp;

enum LoongarchReg {
	/* caller-save */
	T0 = RXX + 1, T1, T2, T3, T4, T5, T6, T7, T8,
	A0, A1, A2, A3, A4, A5, A6, A7,

	/* callee-save */
	S0, S1, S2, S3, S4, S5, S6, S7, S8,

	/* globally live */
	FP, SP, TP, RA,

	/* FP caller-save */
	FT0, FT1, FT2, FT3, FT4, FT5, FT6, FT7, FT8, FT9, FT10, FT11, FT12, FT13, FT14,
	FA0, FA1, FA2, FA3, FA4, FA5, FA6, FA7,

	/* FP callee-save */
	FS0, FS1, FS2, FS3, FS4, FS5, FS6, FS7,

	/* reserved (see rv64/emit.c) */
	R21, F23,

	NFPR = FS7 - FT0 + 1,
	NGPR = RA - T0 + 1,
	NGPS = A7 - T0 + 1,
	NFPS = FA7 - FT0 + 1,
	NCLR = (S8 - S0 + 1) + (FS7 - FS0 + 1),
};
MAKESURE(reg_not_tmp, FT11 < (int)Tmp0);

struct LoongarchOp {
	char imm;
};

/* targ.c */
extern int loongarch_rsave[];
extern int loongarch_rclob[];
extern LoongarchOp loongarch_op[];

/* abi.c */
bits loongarch_retregs(Ref, int[2]);
bits loongarch_argregs(Ref, int[2]);
void loongarch_abi(Fn *);

/* isel.c */
void loongarch_isel(Fn *);

/* emit.c */
void loongarch_emitfn(Fn *, FILE *);

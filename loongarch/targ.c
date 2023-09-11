#include "all.h"

LoongarchOp loongarch_op[NOp] = {
#define O(op, t, x) [O##op] =
#define V(imm) { imm },
#include "../ops.h"
};

int loongarch_rsave[] = {
	T0, T1, T2, T3, T4, T5, T6, T7, T8,
	A0, A1, A2, A3, A4, A5, A6, A7,
	FA0, FA1, FA2,  FA3,  FA4, FA5, FA6, FA7,
	FT0, FT1, FT2,  FT3,  FT4, FT5, FT6, FT7,
	FT8, FT9, FT10, FT11, FT12, FT13, FT14,
	-1
};
int loongarch_rclob[] = {
	S0,  S1,  S2,   S3,   S4,  S5,  S6,  S7,
	S8,
	FS0, FS1, FS2,  FS3,  FS4, FS5, FS6, FS7,
	-1
};

#define RGLOB (BIT(FP) | BIT(SP) | BIT(TP) | BIT(RA))

static int
loongarch_memargs(int op)
{
	(void)op;
	return 0;
}

Target T_loongarch = {
	.name = "loongarch",
	.gpr0 = T0,
	.ngpr = NGPR,
	.fpr0 = FT0,
	.nfpr = NFPR,
	.rglob = RGLOB,
	.nrglob = 4,
	.rsave = loongarch_rsave,
	.nrsave = {NGPS, NFPS},
	.retregs = loongarch_retregs,
	.argregs = loongarch_argregs,
	.memargs = loongarch_memargs,
	.abi0 = elimsb,
	.abi1 = loongarch_abi,
	.isel = loongarch_isel,
	.emitfn = loongarch_emitfn,
	.emitfin = elf_emitfin,
	.asloc = ".L",
};

MAKESURE(rsave_size_ok, sizeof loongarch_rsave == (NGPS+NFPS+1) * sizeof(int));
MAKESURE(rclob_size_ok, sizeof loongarch_rclob == (NCLR+1) * sizeof(int));

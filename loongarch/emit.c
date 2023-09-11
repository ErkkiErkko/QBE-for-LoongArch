#include "all.h"

enum {
	Ki = -1, /* matches Kw and Kl */
	Ka = -2, /* matches all classes */
};

static struct {
	short op;
	short cls;
	char *asm;
} omap[] = {
	{ Oadd,    Ki, "add%t.%k %=, %0, %1" },
	{ Oadd,    Ka, "fadd.%k %=, %0, %1" },
	{ Osub,    Ki, "sub%t.%k %=, %0, %1" },
	{ Osub,    Ka, "fsub.%k %=, %0, %1" },
	{ Oneg,    Ki, "sub.%k %=, r0, %0" },
	{ Oneg,    Ka, "fneg.%k %=, %0" },
	{ Odiv,    Ki, "div.%k %=, %0, %1" },
	{ Odiv,    Ka, "fdiv.%k %=, %0, %1" },
	{ Orem,    Ki, "mod.%k %=, %0, %1" },
	{ Orem,    Kl, "rem %=, %0, %1" }, // TODO: 这个指令什么时候用到？
	{ Oudiv,   Ki, "div.%ku %=, %0, %1" },
	{ Ourem,   Ki, "mod.%ku %=, %0, %1" },
	{ Omul,    Ki, "mul.%k %=, %0, %1" },
	{ Omul,    Ka, "fmul.%k %=, %0, %1" },
	{ Oand,    Ki, "and%t %=, %0, %1" },
	{ Oor,     Ki, "or%t %=, %0, %1" },
	{ Oxor,    Ki, "xor%t %=, %0, %1" },
	{ Osar,    Ki, "sra%t.%k %=, %0, %1" },
	{ Oshr,    Ki, "srl%t.%k %=, %0, %1" },
	{ Oshl,    Ki, "sll%t.%k %=, %0, %1" },
	{ Ocsltl,  Ki, "slt%t %=, %0, %1" },
	{ Ocultl,  Ki, "sltu%t %=, %0, %1" },
	{ Oceqs,   Ki, "fcmp.seq.s $fcc0, %0, %1\n\tmovcf2gr %=, $fcc0" },
	{ Ocges,   Ki, "fcmp.sle.s $fcc0, %1, %0\n\tmovcf2gr %=, $fcc0" },
	{ Ocgts,   Ki, "fcmp.slt.s $fcc0, %1, %0\n\tmovcf2gr %=, $fcc0" },
	{ Ocles,   Ki, "fcmp.sle.s $fcc0, %0, %1\n\tmovcf2gr %=, $fcc0" },
	{ Oclts,   Ki, "fcmp.slt.s $fcc0, %0, %1\n\tmovcf2gr %=, $fcc0" },
	{ Oceqd,   Ki, "fcmp.seq.d $fcc0, %0, %1\n\tmovcf2gr %=, $fcc0" },
	{ Ocged,   Ki, "fcmp.sle.d $fcc0, %1, %0\n\tmovcf2gr %=, $fcc0" },
	{ Ocgtd,   Ki, "fcmp.slt.d $fcc0, %1, %0\n\tmovcf2gr %=, $fcc0" },
	{ Ocled,   Ki, "fcmp.sle.d $fcc0, %0, %1\n\tmovcf2gr %=, $fcc0" },
	{ Ocltd,   Ki, "fcmp.slt.d $fcc0, %0, %1\n\tmovcf2gr %=, $fcc0" },
	{ Ostoreb, Kw, "st.b %0, %M1" },
	{ Ostoreh, Kw, "st.h %0, %M1" },
	{ Ostorew, Kw, "st.w %0, %M1" },
	{ Ostorel, Ki, "st.d %0, %M1" },
	{ Ostores, Kw, "fst.s %0, %M1" },
	{ Ostored, Kw, "fst.d %0, %M1" },
	{ Oloadsb, Ki, "ld.b %=, %M0" },
	{ Oloadub, Ki, "ld.bu %=, %M0" },
	{ Oloadsh, Ki, "ld.h %=, %M0" },
	{ Oloaduh, Ki, "ld.hu %=, %M0" },
	{ Oloadsw, Ki, "ld.w %=, %M0" },
	/* riscv64 always sign-extends 32-bit
	 * values stored in 64-bit registers
	 */
	{ Oloaduw, Kw, "ld.w %=, %M0" },
	{ Oloaduw, Kl, "ld.wu %=, %M0" },
	{ Oload,   Kw, "ld.w %=, %M0" },
	{ Oload,   Kl, "ld.d %=, %M0" },
	{ Oload,   Ks, "fld.s %=, %M0" },
	{ Oload,   Kd, "fld.d %=, %M0" },
	{ Oextsb,  Ki, "ext.w.b %=, %0\n\taddi.w %=, %0, 0" },
	{ Oextub,  Ki, "andi %=, %0, 255" },
	{ Oextsh,  Ki, "ext.w.h %=, %0\n\taddi.w %=, %0, 0" },
	{ Oextuh,  Ki, "bstrpick.d %=, %0, 15, 0" },
	{ Oextsw,  Kl, "addi.w %=, %0, 0" },
	{ Oextuw,  Kl, "bstrpick.d %=, %0, 31, 0" },
	{ Otruncd, Ks, "fcvt.s.d %=, %0" },
	{ Oexts,   Kd, "fcvt.d.s %=, %0" },
	{ Ostosi,  Kw, "ftintrz.w.s $f23, %0\n\tmovfr2gr.s %=, $f23" },
	{ Ostosi,  Kl, "ftintrz.l.s $f23, %0\n\tmovfr2gr.s %=, $f23" },
	{ Ostoui,  Kw, "ftintrz.w.s $f23, %0\n\tmovfr2gr.s %=, $f23" },
	{ Ostoui,  Kl, "ftintrz.l.s $f23, %0\n\tmovfr2gr.s %=, $f23" },
	{ Odtosi,  Kw, "ftintrz.w.d $f23, %0\n\tmovfr2gr.d %=, $f23" },
	{ Odtosi,  Kl, "ftintrz.l.d $f23, %0\n\tmovfr2gr.d %=, $f23" },
	{ Odtoui,  Kw, "ftintrz.w.d $f23, %0\n\tmovfr2gr.d %=, $f23" },
	{ Odtoui,  Kl, "ftintrz.l.d $f23, %0\n\tmovfr2gr.d %=, $f23" },
	{ Oswtof,  Ka, "movgr2fr.w %=, %0\n\tffint.%k.w %=, %=" },
	{ Ouwtof,  Ka, "movgr2fr.w %=, %0\n\tffint.%k.w %=, %=" },
	{ Osltof,  Ka, "movgr2fr.d %=, %0\n\tffint.%k.l %=, %=" },
	{ Oultof,  Ka, "movgr2fr.d %=, %0\n\tffint.%k.l %=, %=" },
	{ Ocast,   Kw, "movfr2gr.s %=, %0" },
	{ Ocast,   Kl, "movfr2gr.d %=, %0" },
	{ Ocast,   Ks, "movgr2fr.w %=, %0" },
	{ Ocast,   Kd, "movgr2fr.d %=, %0" },
	{ Ocopy,   Ki, "addi.%k %=, %0, 0" },
	{ Ocopy,   Ka, "fmov.%k %=, %0" },
	{ Oswap,   Ki, "addi.%k %?, %0, 0\n\taddi.%k %0, %1, 0\n\taddi.%k %1, %?, 0" },
	{ Oswap,   Ka, "fmov.%k %?, %0\n\tfmov.%k %0, %1\n\tfmov.%k %1, %?" },
	{ Oreqz,   Ki, "sltui %=, %0, 1" },
	{ Ornez,   Ki, "sltu %=, $r0, %0" },
	{ Ocall,   Kw, "jirl $r1, %0" },
	{ NOp, 0, 0 }
};

static char *rname[] = {
	[FP] = "$r22",
	[SP] = "$r3",
	[TP] = "$r2",
	[RA] = "$r1",
	[T0] = "$r12", "$r13", "$r14", "$r15", "$r16", "$r17", "$r18", "$r19", "$r20",
	[A0] = "$r4", "$r5", "$r6", "$r7", "$r8", "$r9", "$r10", "$r11",
	[S0] = "$r23", "$r24", "$r25", "$r26", "$r27", "$r28", "$r29", "$r30", "$r31",
	[FT0] = "$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15",
	        "$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22",
	[FA0] = "$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7",
	[FS0] = "$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31",
	[R21] = "$r21",
	[F23] = "$f23",
};

static int64_t
slot(Ref r, Fn *fn)
{
	int s;

	s = rsval(r);
	assert(s <= fn->slot);
	if (s < 0)
		return 8 * -s;
	else
		return -4 * (fn->slot - s);
}

static void
emitaddr(Con *c, FILE *f, char *rn)
{
	assert(c->sym.type == SGlo);
	fputs(str(c->sym.id), f);
	if (c->bits.i)
		fprintf(f, "\n\taddi.d %s, %s, %"PRIi64, rn, rn, c->bits.i);
}

static void
emitf(char *s, Ins *i, Fn *fn, FILE *f)
{
	static char clschr[] = {'w', 'd', 's', 'd'};
	Ref r;
	int k, c;
	Con *pc;
	int64_t offset;

	if(i->op >= 51 && i->op <= 63) {
		r = i->arg[i->op <= 56? 1 : 0];
		pc = &fn->con[r.val];
		if(rtype(r) == RCon) {
			fprintf(f, "\tla.global $r21, ");
			emitaddr(pc, f, "$r21");
			fprintf(f, "\n\t");
			for (;;) {
				k = i->cls;
				while ((c = *s++) != '%')
					if (!c) {
						fputc('\n', f);
						return;
					} else
						fputc(c, f);
				switch ((c = *s++)) {
				default:
					die("invalid escape");
				case '=':
				case '0':
					r = c == '=' ? i->to : i->arg[0];
					assert(isreg(r));
					fputs(rname[r.val], f);
					break;
				case '1':
					r = i->arg[1];
					switch (rtype(r)) {
					default:
						die("invalid second argument");
					case RTmp:
						assert(isreg(r));
						fputs(rname[r.val], f);
						break;
					case RCon:
						pc = &fn->con[r.val];
						assert(pc->type == CBits);
						assert(pc->bits.i >= -2048 && pc->bits.i < 2048);
						fprintf(f, "%d", (int)pc->bits.i);
						break;
					}
					break;
				case 'M':
					s++;
					fprintf(f, "$r21, 0");
					break;
				}
			}
			return;
		}
	}

	fputc('\t', f);
	for (;;) {
		k = i->cls;
		while ((c = *s++) != '%')
			if (!c) {
				fputc('\n', f);
				return;
			} else
				fputc(c, f);
		switch ((c = *s++)) {
		default:
			die("invalid escape");
		case '?':
			if (KBASE(k) == 0)
				fputs("$r21", f);
			else
				fputs("$f23", f);
			break;
		case 'k':
//			if (i->cls != Kl)
				fputc(clschr[i->cls], f);
			break;
		case 't':
			r = i->arg[1];
			switch (rtype(r)) {
			default:
				die("invalid second argument");
			case RTmp:
				break;
			case RCon:
				pc = &fn->con[r.val];
				assert(pc->type == CBits);
				assert(pc->bits.i >= -2048 && pc->bits.i < 2048);
				fprintf(f, "i");
				break;
			}
			break;
		case '=':
		case '0':
			r = c == '=' ? i->to : i->arg[0];
			assert(isreg(r));
			fputs(rname[r.val], f);
			break;
		case '1':
			r = i->arg[1];
			switch (rtype(r)) {
			default:
				die("invalid second argument");
			case RTmp:
				assert(isreg(r));
				fputs(rname[r.val], f);
				break;
			case RCon:
				pc = &fn->con[r.val];
				assert(pc->type == CBits);
				assert(pc->bits.i >= -2048 && pc->bits.i < 2048);
				if(i -> op >= 9 && i -> op <= 11 && pc->bits.i < 0) fprintf(f, "%d", (int)pc->bits.i + 4096);
				else fprintf(f, "%d", (int)pc->bits.i);
				break;
			}
			break;
		case 'M':
			c = *s++;
			assert(c == '0' || c == '1');
			r = i->arg[c - '0'];
			switch (rtype(r)) {
			default:
				die("invalid address argument");
			case RTmp:
				fprintf(f, "%s, 0", rname[r.val]);
				break;
			case RCon:
				pc = &fn->con[r.val];
				assert(pc->type == CAddr);
				if (isstore(i->op)
				|| (isload(i->op) && KBASE(i->cls) == 1)) {
					/* store (and float load)
					 * pseudo-instructions need a
					 * temporary register in which to
					 * load the address
					 */
					fprintf(f, "$r0, ");
				}
				die("unreachable place");
				emitaddr(pc, f, "$rx");
				break;
			case RSlot:
				offset = slot(r, fn);
				assert(offset >= -2048 && offset <= 2047);
				fprintf(f, "$r22, %d", (int)offset);
				break;
			}
			break;
		}
	}
}

static void
loadaddr(Con *c, char *rn, FILE *f)
{
	char off[32];

	if (c->sym.type == SThr) {
		if (c->bits.i)
			sprintf(off, "\taddi.d %s, %s, %"PRIi64"\n", rn, rn, c->bits.i);
		else
			off[0] = 0;
		// fprintf(f, "\tlui %s, %%tprel_hi(%s)%s\n",
		// 	rn, str(c->sym.id), off);
		// fprintf(f, "\tadd %s, %s, tp, %%tprel_add(%s)%s\n",
		// 	rn, rn, str(c->sym.id), off);
		// fprintf(f, "\taddi %s, %s, %%tprel_lo(%s)%s\n",
		// 	rn, rn, str(c->sym.id), off);
		fprintf(f, "\tla.tls.le %s, %s\n%s\tadd.d %s, %s, $r2\n", rn, str(c->sym.id), off, rn, rn);
	} else {
		fprintf(f, "\tla.global %s, ", rn);
		emitaddr(c, f, rn);
		fputc('\n', f);
	}
}

static void
loadcon(Con *c, int r, int k, FILE *f)
{
//	fprintf(f, "lc");
	char *rn;
	int64_t n;

	rn = rname[r];
	switch (c->type) {
	case CAddr:
		loadaddr(c, rn, f);
		break;
	case CBits:
		n = c->bits.i;
		if (!KWIDE(k))
			n = (int32_t)n;
		fprintf(f, "\tli.d %s, %"PRIi64"\n", rn, n);
		break;
	default:
		die("invalid constant");
	}
}

static void
fixmem(Ref *pr, Fn *fn, FILE *f)
{
	Ref r;
	int64_t s;
	Con *c;

	r = *pr;
	if (rtype(r) == RCon) {
		c = &fn->con[r.val];
		if (c->type == CAddr)
		if (c->sym.type == SThr) {
			loadcon(c, R21, Kl, f);
			*pr = TMP(R21);
		}
	}
	if (rtype(r) == RSlot) {
		s = slot(r, fn);
		if (s < -2048 || s > 2047) {
			fprintf(f, "\tli.d $r21, %"PRId64"\n", s);
			fprintf(f, "\tadd.d $r21, $r22, $r21\n");
			*pr = TMP(R21);
		}
	}
}

static void
emitins(Ins *i, Fn *fn, FILE *f)
{
	// fprintf(f, ">");
	int o;
	char *rn;
	int64_t s;
	Con *con;

	switch (i->op) {
	default:
		if (isload(i->op))
			fixmem(&i->arg[0], fn, f);
		else if (isstore(i->op))
			fixmem(&i->arg[1], fn, f);
	Table:
		/* most instructions are just pulled out of
		 * the table omap[], some special cases are
		 * detailed below */
		// fprintf(f, "t");
		for (o=0;; o++) {
			/* this linear search should really be a binary
			 * search */
			if (omap[o].op == NOp)
				die("no match for %s(%c)",
					optab[i->op].name, "wlsd"[i->cls]);
			if (omap[o].op == i->op)
			if (omap[o].cls == i->cls || omap[o].cls == Ka
			|| (omap[o].cls == Ki && KBASE(i->cls) == 0))
				break;
		}
		emitf(omap[o].asm, i, fn, f);
		break;
	case Ocopy:
		if (req(i->to, i->arg[0]))
			break;
		if (rtype(i->to) == RSlot) {
			switch (rtype(i->arg[0])) {
			case RSlot:
			case RCon:
				die("unimplemented");
				break;
			default:
				assert(isreg(i->arg[0]));
				i->arg[1] = i->to;
				i->to = R;
				switch (i->cls) {
				case Kw: i->op = Ostorew; break;
				case Kl: i->op = Ostorel; break;
				case Ks: i->op = Ostores; break;
				case Kd: i->op = Ostored; break;
				}
				fixmem(&i->arg[1], fn, f);
				goto Table;
			}
			break;
		}
		assert(isreg(i->to));
		switch (rtype(i->arg[0])) {
		case RCon:
			loadcon(&fn->con[i->arg[0].val], i->to.val, i->cls, f);
			break;
		case RSlot:
			i->op = Oload;
			fixmem(&i->arg[0], fn, f);
			goto Table;
		default:
			assert(isreg(i->arg[0]));
			goto Table;
		}
		break;
	case Onop:
		break;
	case Oaddr:
		assert(rtype(i->arg[0]) == RSlot);
		rn = rname[i->to.val];
		s = slot(i->arg[0], fn);
		if (-s < 2048) {
			fprintf(f, "\taddi.d %s, $r22, %"PRId64"\n", rn, s);
		} else {
			fprintf(f,
				"\tli.d %s, %"PRId64"\n"
				"\tadd.d %s, $r22, %s\n",
				rn, s, rn, rn
			);
		}
		break;
	case Ocall:
		switch (rtype(i->arg[0])) {
		case RCon:
			con = &fn->con[i->arg[0].val];
			if (con->type != CAddr
			|| con->sym.type != SGlo
			|| con->bits.i)
				goto Invalid;
			fprintf(f, "\tbl %s\n", str(con->sym.id));
			break;
		case RTmp:
			emitf("jirl $r1, %0, 0", i, fn, f);
			break;
		default:
		Invalid:
			die("invalid call argument");
		}
		break;
	case Osalloc:
		emitf("sub.d $r3, $r3, %0", i, fn, f);
		if (!req(i->to, R))
			emitf("addi.d %=, $r3, 0", i, fn, f);
		break;
	}
}

/*

  Stack-frame layout:

  +=============+
  | varargs     |
  |  save area  |
  +-------------+
  |  saved ra   |
  |  saved fp   |
  +-------------+ <- fp
  |    ...      |
  | spill slots |
  |    ...      |
  +-------------+
  |    ...      |
  |   locals    |
  |    ...      |
  +-------------+
  |   padding   |
  +-------------+
  | callee-save |
  |  registers  |
  +=============+

*/

void
loongarch_emitfn(Fn *fn, FILE *f)
{
	static int id0;
	int lbl, neg, off, frame, *pr, r;
	Blk *b, *s;
	Ins *i;

	emitfnlnk(fn->name, &fn->lnk, f);

	if (fn->vararg) {
		/* TODO: only need space for registers
		 * unused by named arguments
		 */
		fprintf(f, "\taddi.d $r3, $r3, -64\n");
		for (r=A0; r<=A7; r++)
			fprintf(f,
				"\tst.d %s, $r3, %d\n",
				rname[r], 8 * (r - A0)
			);
	}
	fprintf(f, "\tst.d $r22, $r3, -16\n");
	fprintf(f, "\tst.d $r1, $r3, -8\n");
	fprintf(f, "\taddi.d $r22, $r3, -16\n");

	frame = (16 + 4 * fn->slot + 15) & ~15;
	for (pr=loongarch_rclob; *pr>=0; pr++) {
		if (fn->reg & BIT(*pr))
			frame += 8;
	}
	frame = (frame + 15) & ~15;

	if (frame <= 2048)
		fprintf(f,
			"\taddi.d $r3, $r3, -%d\n",
			frame
		);
	else
		fprintf(f,
			"\tli.d $r21, %d\n"
			"\tsub.d $r3, $r3, $r21\n",
			frame
		);
	for (pr=loongarch_rclob, off=0; *pr>=0; pr++) {
		if (fn->reg & BIT(*pr)) {
			fprintf(f,
				"\t%s %s, $r3, %d\n",
				*pr < FT0 ? "st.d" : "fst.d",
				rname[*pr], off
			);
			off += 8;
		}
	}

	for (lbl=0, b=fn->start; b; b=b->link) {
		if (lbl || b->npred > 1)
			fprintf(f, ".L%d:\n", id0+b->id);
		for (i=b->ins; i!=&b->ins[b->nins]; i++)
			emitins(i, fn, f);
		lbl = 1;
		switch (b->jmp.type) {
		case Jhlt:
			fprintf(f, "\tbreak\n");
			break;
		case Jret0:
			if (fn->dynalloc) {
				if (frame - 16 <= 2048)
					fprintf(f,
						"\taddi.d $r3, $r22, -%d\n",
						frame - 16
					);
				else
					fprintf(f,
						"\tli.d $r21, %d\n"
						"\tsub.d $r3, $r22, $r21\n",
						frame - 16
					);
			}
			for (pr=loongarch_rclob, off=0; *pr>=0; pr++) {
				if (fn->reg & BIT(*pr)) {
					fprintf(f,
						"\t%s %s, $r3, %d\n",
						*pr < FT0 ? "ld.d" : "fld.d",
						rname[*pr], off
					);
					off += 8;
				}
			}
			fprintf(f,
				"\taddi.d $r3, $r22, %d\n"
				"\tld.d $r1, $r22, 8\n"
				"\tld.d $r22, $r22, 0\n"
				"\tjirl $r0, $r1, 0\n",
				16 + fn->vararg * 64
			);
			break;
		case Jjmp:
		Jmp:
			if (b->s1 != b->link)
				fprintf(f, "\tb .L%d\n", id0+b->s1->id);
			else
				lbl = 0;
			break;
		case Jjnz:
			neg = 0;
			if (b->link == b->s2) {
				s = b->s1;
				b->s1 = b->s2;
				b->s2 = s;
				neg = 1;
			}
			assert(isreg(b->jmp.arg));
			fprintf(f,
				"\tb%sz %s, .L%d\n",
				neg ? "ne" : "eq",
				rname[b->jmp.arg.val],
				id0+b->s2->id
			);
			goto Jmp;
		}
	}
	id0 += fn->nblk;
}

// TODO: break是这么用的吗？
ds1052e: ds1052e.c instr.c capture.c measure.c
	cc ds1052e.c instr.c capture.c measure.c -o ds1052e

clean:
	rm -f ds1052e

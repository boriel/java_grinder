
#JOBJS=$(shell ls *.java | sed 's/\.java/\.class/')

default:
	@+make -C build

tests:
	@+make -C testing

.PHONY: java
java:
	@+make -C java
	@make -C build jar

%.class: %.java
	javac $*.java

grind: tests
	./java_grinder testing/LCD.class out.asm msp430g2231
	naken_asm -I /storage/git/naken_asm/include/msp430 -l out.asm

dsp: tests
	./java_grinder testing/DSPTest.class out.asm dspic33fj06gs101a
	naken_asm -l -I /storage/git/naken_asm/include out.asm

clean:
	@rm -f *.o java_grinder build/*.o *.asm *.lst *.hex
	@rm -f java/*.class testing/*.class build/*.jar
	@rm -rf build/net
	@echo "Clean!"




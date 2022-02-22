gcc:
	g++ -std=c++11 -g -o wks_gen.exe -I../ -g Source.cpp

run:
	./wks_gen.exe
clean:
	rm -rf wks_gen.exe  *Worksheet*txt worksheet*txt

gen_all: gcc
	./wks_gen.exe 20 ArithmeticWorksheet.txt arithmetic
	./wks_gen 20 PercentageWorksheet.txt percentage
	./wks_gen 20 AlgebricExpressionWorksheet.txt algebric_expression
	./wks_gen 20 LinearEquationWorksheet.txt linear_equation
